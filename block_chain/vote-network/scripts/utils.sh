# chaincode路径
CC_SRC_PATH="github.com/chaincode/vote/"

ORDERER_CA=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem
PEER0_ORG1_CA=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt
PEER1_ORG1_CA=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/peerOrganizations/org1.example.com/peers/peer1.org1.example.com/tls/ca.crt
PEER0_ORG2_CA=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt
PEER1_ORG2_CA=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/peerOrganizations/org2.example.com/peers/peer1.org2.example.com/tls/ca.crt


# verify the result of the end-to-end test
verifyResult() {
    if [ $1 -ne 0 ]; then
        echo "!!!!!!!!!!!!!!! "$2" !!!!!!!!!!!!!!!!"
        echo "========= ERROR !!! FAILED to execute End-2-End Scenario ==========="
        echo
        exit 1
    fi
}

# Set OrdererOrg.Admin globals
setOrdererGlobals() {
    CORE_PEER_LOCALMSPID="OrdererMSP"
    CORE_PEER_TLS_ROOTCERT_FILE=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem
    CORE_PEER_MSPCONFIGPATH=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/ordererOrganizations/example.com/users/Admin@example.com/msp
}

setGlobals() {
    PEER=$1
    ORG=$2
    if [ $ORG -eq 1 ]; then
        CORE_PEER_LOCALMSPID="Org1MSP"
        CORE_PEER_MSPCONFIGPATH=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/peerOrganizations/org1.example.com/users/Admin@org1.example.com/msp
        if [ $PEER -eq 0 ]; then
        CORE_PEER_TLS_ROOTCERT_FILE=$PEER0_ORG1_CA
        CORE_PEER_ADDRESS=peer0.org1.example.com:7051
        else
        CORE_PEER_TLS_ROOTCERT_FILE=$PEER1_ORG1_CA
        CORE_PEER_ADDRESS=peer1.org1.example.com:7051
        fi
    elif [ $ORG -eq 2 ]; then
        CORE_PEER_LOCALMSPID="Org2MSP"
        CORE_PEER_MSPCONFIGPATH=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/peerOrganizations/org2.example.com/users/Admin@org2.example.com/msp
        if [ $PEER -eq 0 ]; then
        CORE_PEER_TLS_ROOTCERT_FILE=$PEER0_ORG2_CA
        CORE_PEER_ADDRESS=peer0.org2.example.com:7051
        else
        CORE_PEER_TLS_ROOTCERT_FILE=$PEER1_ORG2_CA
        CORE_PEER_ADDRESS=peer1.org2.example.com:7051
        fi
    else
        echo "================== ERROR !!! ORG Unknown =================="
    fi

    if [ "$VERBOSE" == "true" ]; then
        env | grep CORE
    fi
}

updateAnchorPeers() {
    PEER=$1
    ORG=$2
    setGlobals $PEER $ORG

    if [ -z "$CORE_PEER_TLS_ENABLED" -o "$CORE_PEER_TLS_ENABLED" = "false" ]; then
        set -x
        peer channel update -o orderer.example.com:7050 -c $CHANNEL_NAME -f ./channel-artifacts/${CORE_PEER_LOCALMSPID}anchors.tx >&log.txt
        res=$?
        set +x
    else
        set -x
        peer channel update -o orderer.example.com:7050 -c $CHANNEL_NAME -f ./channel-artifacts/${CORE_PEER_LOCALMSPID}anchors.tx --tls $CORE_PEER_TLS_ENABLED --cafile $ORDERER_CA >&log.txt
        res=$?
        set +x
    fi
    cat log.txt
    verifyResult $res "Anchor peer update failed"
    echo "===================== Anchor peers updated for org '$CORE_PEER_LOCALMSPID' on channel '$CHANNEL_NAME' ===================== "
    sleep $DELAY
    echo
}

## Sometimes Join takes time hence RETRY at least 5 times
joinChannelWithRetry() {
    PEER=$1
    ORG=$2
    setGlobals $PEER $ORG

    set -x
    peer channel join -b $CHANNEL_NAME.block >&log.txt
    res=$?
    set +x
    cat log.txt
    if [ $res -ne 0 -a $COUNTER -lt $MAX_RETRY ]; then
        COUNTER=$(expr $COUNTER + 1)
        echo "peer${PEER}.org${ORG} failed to join the channel, Retry after $DELAY seconds"
        sleep $DELAY
        joinChannelWithRetry $PEER $ORG
    else
        COUNTER=1
    fi
    verifyResult $res "After $MAX_RETRY attempts, peer${PEER}.org${ORG} has failed to join channel '$CHANNEL_NAME' "
}

createChannel() {
	setGlobals 0 1

	if [ -z "$CORE_PEER_TLS_ENABLED" -o "$CORE_PEER_TLS_ENABLED" = "false" ]; then
                set -x
		peer channel create -o orderer.example.com:7050 -c $CHANNEL_NAME -f ./channel-artifacts/channel.tx >&log.txt
		res=$?
                set +x
	else
				set -x
		peer channel create -o orderer.example.com:7050 -c $CHANNEL_NAME -f ./channel-artifacts/channel.tx --tls $CORE_PEER_TLS_ENABLED --cafile $ORDERER_CA >&log.txt
		res=$?
				set +x
	fi
	cat log.txt
	verifyResult $res "Channel creation failed"
	echo "===================== Channel '$CHANNEL_NAME' created ===================== "
	echo
}

joinChannel () {
	for org in 1 2; do
	    for peer in 0 1; do
		joinChannelWithRetry $peer $org
		echo "===================== peer${peer}.org${org} joined channel '$CHANNEL_NAME' ===================== "
		sleep $DELAY
		echo
	    done
	done
}

# 安装chaincode
installChaincode() {
    PEER=$1
    ORG=$2
    setGlobals $PEER $ORG
    VERSION=${3:-1.0}
    set -x
    peer chaincode install -n mycc -v ${VERSION} -l ${LANGUAGE} -p ${CC_SRC_PATH} >&log.txt
    res=$?
    set +x
    cat log.txt
    verifyResult $res "Chaincode installation on peer${PEER}.org${ORG} has failed"
    echo "===================== Chaincode is installed on peer${PEER}.org${ORG} ===================== "
    echo
}


# 实例化chaincode
instantiateChaincode() {
    PEER=$1
    ORG=$2
    setGlobals $PEER $ORG
    VERSION=${3:-1.0}
    PEER_NAME="peer${PEER}.org${ORG}"

    # while 'peer chaincode' command can get the orderer endpoint from the peer
    # (if join was successful), let's supply it directly as we know it using
    # the "-o" option
    if [ -z "$CORE_PEER_TLS_ENABLED" -o "$CORE_PEER_TLS_ENABLED" = "false" ]; then
        set -x
        peer chaincode instantiate -o orderer.example.com:7050 -C $CHANNEL_NAME -n mycc -l ${LANGUAGE} -v ${VERSION} -c '{"Args":["Init"]}' -P "AND ('Org1MSP.peer','Org2MSP.peer')" >&log.txt
        res=$?
        set +x
    else
        set -x
        peer chaincode instantiate -o orderer.example.com:7050 --tls $CORE_PEER_TLS_ENABLED --cafile $ORDERER_CA -C $CHANNEL_NAME -n mycc -l ${LANGUAGE} -v 1.0 -c '{"Args":["Init"]}' -P "AND ('Org1MSP.peer','Org2MSP.peer')" >&log.txt
        res=$?
        set +x
    fi
    cat log.txt
    verifyResult $res "Chaincode instantiation on peer${PEER}.org${ORG} on channel '$CHANNEL_NAME' failed"
    echo "===================== Chaincode is instantiated on peer${PEER}.org${ORG} on channel '$CHANNEL_NAME' ===================== "
    echo
}


# 发起投票
createVoteTopic() {
    PEER=$1
    ORG=$2
    TOPIC=$3
    CONTENT=$4
    PEER_NAME="peer${PEER}.org${ORG}"
    CREATOR=$PEER_NAME
    METHOD="invoke"
    ARGS="{\"Args\":[\"createVoteTopic\",\"$TOPIC\",\"$CONTENT\",\"$CREATOR\"]}"

    if [ -z "$CORE_PEER_TLS_ENABLED" -o "$CORE_PEER_TLS_ENABLED" = "false" ]; then
        PEER_CONN_PARMS="--peerAddresses peer0.org1.example.com:7051 --peerAddresses peer1.org1.example.com:7051 --peerAddresses peer0.org2.example.com:7051 --peerAddresses peer1.org2.example.com:7051"
        set -x
        peer chaincode $METHOD -o orderer.example.com:7050 -C $CHANNEL_NAME -n mycc $PEER_CONN_PARMS -c $ARGS >&log.txt
        res=$?
        set +x
    else
        PEER_CONN_PARMS="--peerAddresses peer0.org1.example.com:7051 --tlsRootCertFiles $PEER0_ORG1_CA --peerAddresses peer1.org1.example.com:7051 --tlsRootCertFiles $PEER1_ORG1_CA --peerAddresses peer0.org2.example.com:7051 --tlsRootCertFiles $PEER0_ORG2_CA --peerAddresses peer1.org2.example.com:7051 --tlsRootCertFiles $PEER1_ORG2_CA"
        set -x
        peer chaincode $METHOD -o orderer.example.com:7050 --tls $CORE_PEER_TLS_ENABLED --cafile $ORDERER_CA -C $CHANNEL_NAME -n mycc $PEER_CONN_PARMS -c $ARGS >&log.txt
        res=$?
        set +x
    fi
    cat log.txt
}

# 查询所有投票
queryAllVoteTopic() {
    PEER=$1
    ORG=$2
    PEER_NAME="peer${PEER}.org${ORG}"
    setGlobals $PEER $ORG
    METHOD="query"
    ARGS='{"Args":["queryAllVoteTopic"]}'

    set -x
    peer chaincode $METHOD -C $CHANNEL_NAME -n mycc -c $ARGS >&log.txt
    res=$?
    set +x
    cat log.txt
}

# 查询指定话题投票
queryVoteTopic() {
    PEER=$1
    ORG=$2
    TOPIC=$3
    PEER_NAME="peer${PEER}.org${ORG}"
    setGlobals $PEER $ORG
    METHOD="query"
    ARGS="{\"Args\":[\"queryVoteTopic\",\"$TOPIC\"]}"

    set -x
    peer chaincode $METHOD -C $CHANNEL_NAME -n mycc -c $ARGS >&log.txt
    res=$?
    set +x
    cat log.txt
}

# 为话题投票
voteTopic() {
    PEER=$1
    ORG=$2
    TOPIC=$3
    OPTION=$4
    PEER_NAME="peer${PEER}.org${ORG}"
    VOTER=$PEER_NAME
    METHOD="invoke"
    ARGS="{\"Args\":[\"voteTopic\",\"$TOPIC\",\"$OPTION\",\"$VOTER\"]}"

    if [ -z "$CORE_PEER_TLS_ENABLED" -o "$CORE_PEER_TLS_ENABLED" = "false" ]; then
        PEER_CONN_PARMS="--peerAddresses peer0.org1.example.com:7051 --peerAddresses peer1.org1.example.com:7051 --peerAddresses peer0.org2.example.com:7051 --peerAddresses peer1.org2.example.com:7051"
        set -x
        peer chaincode $METHOD -o orderer.example.com:7050 -C $CHANNEL_NAME -n mycc $PEER_CONN_PARMS -c $ARGS >&log.txt
        res=$?
        set +x
    else
        PEER_CONN_PARMS="--peerAddresses peer0.org1.example.com:7051 --tlsRootCertFiles $PEER0_ORG1_CA --peerAddresses peer1.org1.example.com:7051 --tlsRootCertFiles $PEER1_ORG1_CA --peerAddresses peer0.org2.example.com:7051 --tlsRootCertFiles $PEER0_ORG2_CA --peerAddresses peer1.org2.example.com:7051 --tlsRootCertFiles $PEER1_ORG2_CA"
        set -x
        peer chaincode $METHOD -o orderer.example.com:7050 --tls $CORE_PEER_TLS_ENABLED --cafile $ORDERER_CA -C $CHANNEL_NAME -n mycc $PEER_CONN_PARMS -c $ARGS >&log.txt
        res=$?
        set +x
    fi
    cat log.txt
}