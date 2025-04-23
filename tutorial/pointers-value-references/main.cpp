// main.cpp
#include <iostream>
#include "MyClass.h"

using namespace std;

int main()
{
    MyClass obj(10);  // Create object with initial value 10
    obj.printValue(); // Output: Current value: 10

    int newValue = 15;
    obj.setValue(newValue); // Change value to 15
    obj.printValue();       // Output: Current value: 15

    // Demonstrate pointer
    int valueForPointer = 100;
    obj.changeValueByPointer(&valueForPointer);                        // Pass pointer to the method
    cout << "Value after pointer change: " << valueForPointer << endl; // Output: 20

    // Demonstrate reference
    int valueForReference = 100;
    obj.changeValueByReference(valueForReference);                         // Pass reference to the method
    cout << "Value after reference change: " << valueForReference << endl; // Output: 30

    return 0;
}
