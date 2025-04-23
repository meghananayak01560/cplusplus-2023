// main.cpp
#include <iostream>

using namespace std;

// pass by value
int alpha(int x)
{
    x += 1;
    return x;
}

// pass by reference
int beta(int &x)
{
    x += 1;
    return x;
}

// pass by pointer
int gamma(int *x)
{
    *x += 1;
    return *x;
}

int dada(int &x) {
    x = x * 2;
    return x;
}

int franklinResult(int x) {
    x = x * 2;
    return x;
}

int main()
{
    int x = 1;

    int alphaResult = alpha(x);
    cout << "Value after pass by value: x = " << x << " alphaResult = " << alphaResult << endl; 
    // Output: Value after pass by value: x = 1 alphaResult = 2

    // int 
    int betaResult = beta(x);
    cout << "Value after pass by reference: x = " << x << " betaResult = " << betaResult << endl; 
    // Output: Value after pass by reference: x = 2 betaResult = 2

    // &x is the address of x  (address is basically the location in memory where x is stored)
    int gammaResult = gamma(&x);
    cout << "Value after pass by pointer: x = " << x << " gammaResult = " << gammaResult << endl; 
    // Output: Value after pass by pointer: x = 3 gammaResult = 3

    int dadaResult = dada(x);
    cout << "Value after pass by reference: x = " << x << " dadaResult = " << dadaResult << endl; 
    // Output: Value after pass by reference: x = 6 dadaResult = 6

    int franklinRes = franklinResult(x);
    cout << "Value after pass by value: x = " << x << " franklinRes = " << franklinRes << endl; 
    // Output: Value after pass by value: x = 12 franklinRes = 12
    return 0;
}
