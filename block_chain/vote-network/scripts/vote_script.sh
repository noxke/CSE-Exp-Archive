#!/bin/bash

CHANNEL_NAME="$1"
DELAY="$2"
LANGUAGE="$3"
TIMEOUT="$4"
VERBOSE="$5"
: ${CHANNEL_NAME:="mychannel"}
: ${DELAY:="3"}
: ${LANGUAGE:="golang"}
: ${TIMEOUT:="10"}
: ${VERBOSE:="false"}
LANGUAGE=`echo "$LANGUAGE" | tr [:upper:] [:lower:]`
COUNTER=1
MAX_RETRY=10

# 导入utils.sh
. scripts/utils.sh

echo "=============================================================================="
echo
echo " ____    _____      _      ____    _____ "
echo "/ ___|  |_   _|    / \    |  _ \  |_   _|"
echo "\___ \    | |     / _ \   | |_) |   | |  "
echo " ___) |   | |    / ___ \  |  _ <    | |  "
echo "|____/    |_|   /_/   \_\ |_| \_\   |_|  "
echo
echo
echo "=============================================================================="


createVoteTopic 0 1 "testTopic" "testContent"
sleep $DELAY

queryAllVoteTopic 1 1
sleep $DELAY

queryVoteTopic 0 2 "testTopic"
sleep $DELAY

voteTopic 1 2 "testTopic" "true"
sleep $DELAY

queryVoteTopic 0 2 "testTopic"
sleep $DELAY

voteTopic 0 1 "testTopic" "false"
sleep $DELAY

queryVoteTopic 0 1 "testTopic"
sleep $DELAY

echo "=============================================================================="
echo
echo " _____   _   _   ____   "
echo "| ____| | \ | | |  _ \  "
echo "|  _|   |  \| | | | | | "
echo "| |___  | |\  | | |_| | "
echo "|_____| |_| \_| |____/  "
echo
echo "=============================================================================="
exit 0