/**
* Solution to homework assignment 1
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Daniel Halachev
* @idnumber 62547
* @task 2
* @compiler GCC
*/

#include "StringOperations.hpp"

int stringLength(const char string[]) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}

char *stringCopy(const char source[], char destination[]) {
    if (destination == nullptr) {
        return nullptr;
    }
    if (source == nullptr) {
        return destination;
    }
    while ((*destination++ = *source++) != '\0');
    return destination;
}