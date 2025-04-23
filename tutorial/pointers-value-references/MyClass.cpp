// MyClass.cpp
#include <iostream>
#include "MyClass.h"

using namespace std;

MyClass::MyClass(int val) : value(val)
{
    // Constructor initializes value
}

void MyClass::setValue(int val)
{
    value = val;
}

void MyClass::printValue()
{
    cout << "Current value: " << value << endl;
}

void MyClass::changeValueByPointer(int *ptr)
{
    *ptr = 20; // Dereference pointer to change the value it points to
}

void MyClass::changeValueByReference(int &ref)
{
    ref = 30; // Change the reference directly
}