#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

// ======== Class Declaration ==========
class MyException
{
public:
	string Date_WrongInputType() { return string("Wrong input type!"); }
	string Date_invalidDay() { return string("Invalid day!"); }
	string Date_invalidMonth() { return string("Invalid month!"); }
	string Date_invalidYear() { return string("Invalid year!"); }
	string Date_invalid() { return string("Invalid Date!"); }

	string ExceededAttempt() { return string("Exceeded the number of allowed attempts to re-enter!"); }

};

#endif
