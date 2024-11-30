#!/bin/bash

# bash test-docker.sh
apt install iptables libip6tc2 libmnl0 libnetfilter-conntrack3 libnfnetlink0 libnftnl11 libxtables12 -y
dpkg -i containerd.io_1.2.13-2_amd64.deb
dpkg -i docker-ce-cli_19.03.15~3-0~ubuntu-focal_amd64.deb
dpkg -i docker-ce_19.03.15~3-0~ubuntu-focal_amd64.deb

service docker start

apt install docker-compose libtool libltdl-dev -y
