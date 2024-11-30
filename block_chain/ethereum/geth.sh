#!/bin/bash
#
# init and start geth block

if [ -z "$1" ] || [ -z "$2" ]
then
	echo "./geth.sh command id"
	exit
fi

cd /root/block-chain

id=$(expr "$2")
datadir="data$2"
port=$(expr "$id" + 30303)
rpc_port=$(expr "$id" + 8551)
http_port=$(expr "$id" + 8541)

if [ "$1" = "init" ]
then
	geth --datadir $datadir init noxke-private-chain.json
elif [ "$1" = "start" ]
then
	geth --datadir $datadir --port $port --authrpc.port $rpc_port --http --http.addr "0.0.0.0" --http.port $http_port --http.corsdomain="https://remix.ethereum.org" --http.api web3,eth,debug,personal,net --vmdebug --allow-insecure-unlock --nodiscover --networkid 1101
elif [ "$1" = "attach" ]
then
	geth attach ipc:$datadir/geth.ipc
else
	echo unknown command
fi
exit

