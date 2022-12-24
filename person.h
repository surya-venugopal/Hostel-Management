#include <iostream>

using namespace std;
class Person
{
    string name;
    string phone;
    string roll;

public:
    Person(string name, string phone, string roll)
    {
        this->name = name;
        this->phone = phone;
        this->roll = roll;
    }

    string getName()
    {
        return name;
    }
    string getPhone()
    {
        return phone;
    }
    string getRoll()
    {
        return roll;
    }
};