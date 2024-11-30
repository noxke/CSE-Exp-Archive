package main

import (
	"encoding/json"
	"fmt"

	"github.com/hyperledger/fabric/core/chaincode/shim"
	pb "github.com/hyperledger/fabric/protos/peer"
)

// SimpleChaincode example simple Chaincode implementation
type SimpleChaincode struct {
}

// 投票结构体
type Vote struct {
	Voter  string `json:"Voter"`  // 投票者
	Option string `json:"Option"` // 投票选项
}

// 话题结构体
type Topic struct {
	Topic   string `json:"Topic"`   // 投票主题
	Content string `json:"Content"` // 投票内容
	Creator string `json:"Creator"` // 投票发起者
	Votes   []Vote `json:"Votes"`   // 投票情况
}

// Init方法，实例化时被调用
func (t *SimpleChaincode) Init(stub shim.ChaincodeStubInterface) pb.Response {
	fmt.Println("Init")
	return shim.Success(nil)
}

// Invoke方法，query或invoke时调用
func (t *SimpleChaincode) Invoke(stub shim.ChaincodeStubInterface) pb.Response {
	fmt.Println("Invoke")
	function, args := stub.GetFunctionAndParameters()
	// 调用不同的函数
	if function == "createVoteTopic" {
		return t.createVoteTopic(stub, args)
	} else if function == "queryAllVoteTopic" {
		return t.queryAllVoteTopic(stub, args)
	} else if function == "voteTopic" {
		return t.voteTopic(stub, args)
	} else if function == "queryVoteTopic" {
		return t.queryVoteTopic(stub, args)
	}

	return shim.Error("Invalid invoke function name.")
}

// 发起投票话题
func (t *SimpleChaincode) createVoteTopic(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	if len(args) != 3 {
		return shim.Error("Incorrect arguments, need topic content creator!")
	}
	// 投票的话题
	topic := args[0]
	// 投票内容
	content := args[1]
	// 发起投票者的名称
	creator := args[2]
	// 查询该投票主题是否存在
	topicExist, _ := stub.GetState(topic)
	if topicExist != nil {
		return shim.Error("Topic " + topic + " already exists!")
	}
	voteTopic := Topic{
		Topic:   topic,
		Content: content,
		Creator: creator,
		Votes:   nil,
	}
	byteVoteTopic, _ := json.Marshal(voteTopic)
	err := stub.PutState(topic, byteVoteTopic)
	if err != nil {
		return shim.Error(err.Error())
	}
	return shim.Success(nil)
}

// 查询所有投票话题
func (t *SimpleChaincode) queryAllVoteTopic(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	resultIterator, err := stub.GetStateByRange("", "")
	if err != nil {
		return shim.Error("Get state failed!")
	}
	// 函数返回之前关闭迭代器
	defer resultIterator.Close()

	var topics []Topic
	// 遍历迭代器
	for resultIterator.HasNext() {
		query, _ := resultIterator.Next()
		var topic Topic
		err = json.Unmarshal(query.Value, &topic)
		if err == nil {
			// 不显示投票情况
			topic.Votes = nil
			topics = append(topics, topic)
		}
	}
	// 带缩进的格式显示
	byteData, _ := json.MarshalIndent(topics, "", "    ")
	return shim.Success(byteData)
}

// 为话题投票投票
func (t *SimpleChaincode) voteTopic(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	if len(args) != 3 {
		return shim.Error("Incorrect arguments, need topic option voter!")
	}
	topic := args[0]
	option := args[1]
	voter := args[2]
	// 查询投票是否存在
	topicExist, _ := stub.GetState(topic)
	if topicExist == nil {
		return shim.Error("Topic " + topic + " not exists!")
	}
	var topicExi Topic
	err := json.Unmarshal(topicExist, &topicExi)
	if err != nil {
		return shim.Error(err.Error())
	}
	// 获取已投票的情况
	votesExi := topicExi.Votes
	// 遍历投票情况确认投票者是否已投票
	for i := 0; i < len(votesExi); i++ {
		if voter == votesExi[i].Voter {
			return shim.Error(voter + " has already voted for topic: " + topic)
		}
	}
	vote := Vote{
		Voter:  voter,
		Option: option,
	}
	// 将新的投票加入到话题投票中
	votesExi = append(votesExi, vote)
	topicExi.Votes = votesExi
	// 将投票写入账本
	byteVoteTopic, _ := json.Marshal(topicExi)
	err = stub.PutState(topic, byteVoteTopic)
	if err != nil {
		return shim.Error(err.Error())
	}
	return shim.Success(nil)
}

// 查询投票话题
func (t *SimpleChaincode) queryVoteTopic(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	if len(args) != 1 {
		return shim.Error("Incorrect arguments, need topic!")
	}
	topic := args[0]

	byteData, err := stub.GetState(topic)
	if err != nil {
		shim.Error(err.Error())
	}
	var topicData Topic
	err = json.Unmarshal(byteData, &topicData)
	byteData, _ = json.MarshalIndent(topicData, "", "    ")
	return shim.Success(byteData)
}

// main函数
func main() {
	err := shim.Start(new(SimpleChaincode))
	if err != nil {
		fmt.Printf("Error starting Simple chaincode: %s", err)
	}
}
