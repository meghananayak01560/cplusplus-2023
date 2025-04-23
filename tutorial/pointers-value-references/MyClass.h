// MyClass.h
#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass
{
public:
    MyClass(int value);                    // Constructor with a parameter
    void setValue(int value);              // Method to set value
    void printValue();                     // Method to print value
    void changeValueByPointer(int *ptr);   // Method to change value using a pointer
    void changeValueByReference(int &ref); // Method to change value using a reference

private:
    int value; // This is the value we will change using pointers and references
};

#endif