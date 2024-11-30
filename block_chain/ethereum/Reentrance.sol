pragma solidity ^0.4.26;

contract Reentrance{
    address _owner;
    mapping (address => uint256) balances; // balance 是存放其他账户在该合约中的存款的数组

    function Reentrance() {
        _owner = msg.sender; // 构造函数中的msg.sender只能是创建者
    }
    function deposit() public payable { // 存款功能
        balances[msg.sender] += msg.value; // 消息调用者在该合约中的存款加上账户当前余额
    }
    function withdraw(uint256 amount) public payable { // 提款功能
        require(balances[msg.sender] >= amount); // 判断调用者的余额是否足够
        require(this.balance >= amount); // 判断合约资产是否足够

        msg.sender.call.value(amount)();
        balances[msg.sender] -= amount; // 修改余额状态变量
    }
    function balanceof(address addr) constant returns(uint256) {
        return balances[addr]; // 查看余额状态变量
    }
    function wallet() constant returns(uint256 result) {
        return this.balance; // 查看合约的余额
    }
}
