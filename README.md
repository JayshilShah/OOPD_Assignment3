# OOPD_Assignment3

In this assignment, I was supposed to write the code for the 4-ary Search Tree and along with the Basic Operations like Insertion, Deletion of the node , Pre-order and Post-order traversal. I needed to makesure that it should also auto initialize the basic values when program boots up. and I was supposed to have an object with non-primitive data-type also So I created one object with the another class also which included the key as a one parameter.


# Error-Handling and Assert

Along with the given task I was supposed to use assert for user input validation and needed to create custom error exception classes. So I created 2 separate branches for that also. and the name of the branches are self explamatory.

*Code Snippet :*
```
C++
// Custom exception for invalid input
class InvalidInputException : public exception
{
public:
    const char *what() const throw()
    {
        return "Invalid input. Please enter a valid choice.";
    }
};
```