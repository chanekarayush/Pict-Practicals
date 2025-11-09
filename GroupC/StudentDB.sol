// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

/// @title Student Data Smart Contract
/// @author Ayush Chanekar
/// @notice Please find the youtube video explaining this program here:- https://youtu.be/4nlUAwgO6UQ

contract StudentData {
    struct Student{
        string name;
        string className;
        uint256 age;
        uint256 rollNo;
    }

    Student[] public students; 
    mapping(uint256 => bool) private _rollExists;

    address public owner;
    event StudentAdd(string name, uint256 indexed rollNo);

    modifier onlyOwner(){
        require(msg.sender == owner);
        _;
    }
    constructor() {
        owner = msg.sender;
    }


    function addStudent(
        string calldata _name,
        uint256 _age,
        string calldata  _className,
        uint256 _rollNo 
    ) external onlyOwner{
        require(bytes(_name).length > 0 && bytes(_className).length > 0, "Invalid Name or Class field");
        require(_age > 0 && _age <= 150, "Invalid Age Field");
        require(!_rollExists[_rollNo], "The Roll Number already Exists");

        Student memory tempStudent = Student({
            name: _name,
            age: _age,
            className: _className,
            rollNo: _rollNo
        });
        students.push(tempStudent);
        _rollExists[_rollNo] = true;
        emit StudentAdd(_name,  _rollNo);
    }

    function getTotalStudents() public view returns(uint256) { return students.length;}

    function getStudent(uint256 index) public view returns(string memory, uint256, string memory, uint256){
        require(index < students.length, "Invalid Index Entered");
        Student storage s = students[index];
        return (s.name, s.age, s.className, s.rollNo);
    }
}
