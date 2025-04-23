#include <iostream>
#include "functions.h"
using namespace std;

void function_one(int i, int &j) {
    i += 2; 
    j += 1; 
}

void function_two(example &foo) {
    foo.value += 1;
}

void function_three(int *k, int &l) {
    (*k)++;
    l++;
}

void function_four(int *arr, int size, int &lowest, int &highest) {
    for (int i = 0; i < size; i++) {
        arr[i] += 2;
    }
    
    lowest = arr[0];
    highest = arr[0];
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < lowest) {
            lowest = arr[i];
        }
        if (arr[i] > highest) {
            highest = arr[i];
        }
    }
}
