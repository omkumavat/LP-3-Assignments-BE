// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;


contract BankAccount {
    address public customer;          // account owner
    uint256 private balance;          // customer's balance in wei

    // Events for transaction logging
    event Deposited(address indexed customer, uint256 amount);
    event Withdrawn(address indexed customer, uint256 amount);

    // Constructor: sets the deploying address as the customer
    constructor() {
        customer = msg.sender;
    }

    // Deposit money into the account
    function deposit() public payable {
        require(msg.value > 0, "Deposit must be greater than 0");
        balance += msg.value;  // increase internal balance
        emit Deposited(msg.sender, msg.value);
    }

    // Withdraw money from the account
    function withdraw(uint256 amount) public {
        require(msg.sender == customer, "Only owner can withdraw");
        require(amount <= balance, "Insufficient balance");
        balance -= amount;  // deduct from internal balance
        payable(customer).transfer(amount);  // send Ether
        emit Withdrawn(customer, amount);
    }

    // Show account balance
    function showBalance() public view returns (uint256) {
        return balance;
    }
}
