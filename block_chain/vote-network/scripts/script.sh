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


## 创建channel
echo "Creating channel..."
createChannel

## 将所有的peer加入channel
echo "Having all peers join the channel..."
joinChannel

## 为channel中的每个组织设置锚点对等点
echo "Updating anchor peers for org1..."
updateAnchorPeers 0 1
echo "Updating anchor peers for org2..."
updateAnchorPeers 0 2

## 安装chaincode
echo "Install chaincode..."
installChaincode 0 1
installChaincode 1 1
installChaincode 0 2
installChaincode 1 2

# 实例化chaincode
echo "Instantiating chaincode on peer0.org1..."
instantiateChaincode 0 1

# 初始化完毕
echo "===================== Init Network Successful ====================="

exit 0
