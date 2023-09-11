#define _CRT_SECURE_NO_WARNINGS

#pragma once
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <ctime>
#include "MyException.h"

using namespace std;

// =========== CLASS DEFINITION ==========
class Date
{
private:
	int _day;
	int _month;
	int _year;
public:
	Date();
	Date(int dd, int mm, int yyyy);
	Date(char* date);
	Date(const Date&);
	~Date();

	void inputCstring();
	string toString();
	int getD();
	int getM();
	int getY();
	bool operator ==(const Date& date);
	bool operator >=(const Date& date);
	bool operator <=(const Date& date);
	bool operator <(const Date& date);
	bool operator >(const Date& date);
	bool checkDate();
	int cal_Age();
};

// ======== Class Declaration ==========
Date::Date()
{
	_day = 0;
	_month = 0;
	_year = 0;
}
Date::Date(int dd, int mm, int yyyy)
{
	_day = dd;
	_month = mm;
	_year = yyyy;
}
Date::Date(char* date)
{
	char* dd = strtok(date, "/");
	char* mm = strtok(NULL, "/");
	char* yyyy = strtok(NULL, "/");
	bool flag = false;
	MyException e;
	int times = 0;
	while (times < 3 && !flag)
	{
		if (!(dd == NULL || mm == NULL || yyyy == NULL))
		{
			flag = true;
			break;
		}
		else
		{			
			cout << "\nError: " << e.Date_WrongInputType() << endl;
			//cin.ignore('\n');
			cout << "\nRe-Enter Date (dd/mm/yyyy): ";
			cin.getline(date, 15);
			dd = strtok(date, "/");
			mm = strtok(NULL, "/");
			yyyy = strtok(NULL, "/");
			times++;
			if (!(dd == NULL || mm == NULL || yyyy == NULL))
			{
				flag = true;
				break;
			}
		}
	}

	if (flag == false)
	{
		cout << "\nError: " << e.ExceededAttempt() << endl;
		cout << "Input value default set to 01/01/1900!\n";
		Date temp(01, 01, 1990);
		*this = temp;
	}

	// convert char to int:
	try {
		_day = stoi(dd);
		_month = stoi(mm);
		_year = stoi(yyyy);
	}
	catch (exception e)
	{
		cout << "\nError: " << e.what() << endl;
	}
}
Date::Date(const Date& date)
{
	_day = date._day;
	_month = date._month;
	_year = date._year;
}
Date::~Date()
{
	//cout <<"\nDate destructed"<<endl;
}

void Date::inputCstring()
{
	char* date = new char[15];
	cout << "(dd/mm/yyyy): ";
	cin.getline(date, 15);
	Date temp(date);
	*this = temp;
	int times = 0;
	bool flagDate = checkDate();
	while (!flagDate)
	{
		try {
			if (times == 3 && !flagDate)
			{
				throw MyException();
			}
		}
		catch (MyException e)
		{
			cout << "\nError: " << e.ExceededAttempt() << endl;
			cout << "Input value default set to 01/01/1900!\n";
			Date temp2(01,01,1990);
			*this = temp2;
		}
		if (!flagDate)
		{
			cout << "Re-Enter Date ";
			inputCstring();
			flagDate = checkDate();
			times++;
		}
	}
}
string Date::toString()
{
	stringstream builder;
	if (_day < 10)
	{
		builder << "0" << _day << "/";
	}
	else {
		builder << _day << "/";
	}
	if (_month < 10)
	{
		builder << "0" << _month << "/";
	}
	else {
		builder << _month << "/";
	}
	builder << _year;

	string result = builder.str();
	return result;
}

int Date::getD() { return _day; }
int Date::getM() { return _month; }
int Date::getY() { return _year; }

// ===== Operator =====
bool Date::operator<(const Date& date)
{
	if (_year > date._year)
	{
		return true;
	}
	else if (_year == date._year)
	{
		if (_month > date._month)
		{
			return true;
		}
		else if (_month == date._month)
		{
			if (_day > date._day)
				return true;
		}
	}
	return false;
}
bool Date::operator>(const Date& date)
{
	if (_year < date._year)
	{
		return true;
	}
	else if (_year == date._year)
	{
		if (_month < date._month)
		{
			return true;
		}
		else if (_month == date._month)
		{
			if (_day < date._day)
				return true;
		}
	}
	return false;
}
bool Date::operator==(const Date& date)
{
	if (_year == date._year)
	{
		if (_month == date._month)
		{
			if (_day == date._day)
			{
				return true;
			}
		}
	}
	return false;
}
bool Date::operator<=(const Date& date)
{
	if (_year > date._year)
	{
		return true;
	}
	else if (_year == date._year)
	{
		if (_month > date._month)
		{
			return true;
		}
		else if (_month == date._month)
		{
			if (_day >= date._day)
				return true;
		}
	}
	return false;
}
bool Date::operator>=(const Date& date)
{
	if (_year < date._year)
	{
		return true;
	}
	else if (_year == date._year)
	{
		if (_month < date._month)
		{
			return true;
		}
		else if (_month == date._month)
		{
			if (_day <= date._day)
				return true;
		}
	}
	return false;
}
bool Date::checkDate()
{
	try {
		if (_day < 1 || _month < 1 || _month > 12 || _year < 0)
		{
			throw MyException();
		}
	}
	catch (MyException e)
	{
		cout << "\nError: " << e.Date_invalid() << endl;	
		return false;
	}
	// Check invalid day
	if (_month == 1 || _month == 3 || _month == 5 || _month == 7 || _month == 8 || _month == 10 || _month == 12)
	{
		try {
			if (_day > 31)
				throw MyException();
		}
		catch (MyException e)
		{
			cout << "\nError: " << e.Date_invalidDay() << endl;
			return false;
		}
	}
	if (_month == 4 || _month == 6 || _month == 9 || _month == 11)
	{
		try {
			if (_day > 30)
				throw MyException();
		}
		catch (MyException e)
		{
			cout << "\nError: " << e.Date_invalidDay() << endl;
			return false;
		}
	}
	if (_month == 2)
	{
		try {
			if (_day > 29)
				throw MyException();
		}
		catch (MyException e)
		{
			cout << "\nError: " << e.Date_invalidDay() << endl;
			return false;
		}

		if (_day == 29)
		{
			try {
				// Check Leap Year
				if (!((_year % 4 == 0 && _year % 100 != 0) || _year % 400 == 0))
					throw MyException();
			}
			catch (MyException e)
			{
				cout << "\nError: " << e.Date_invalidDay() << endl;
				return false;
			}
		}
	}
	return true;
}

// calculate date
int Date::cal_Age()
{
	time_t t = time(0); // get current time
	tm* current = localtime(&t);
	// year start with 0 (from 1900)
	int currentYear = current->tm_year + 1900;
	// month start with 0
	int currentMonth = current->tm_mon + 1;
	int currentDay = current->tm_mday;

	int Age;

	if (currentMonth > _month)
	{
		Age = currentYear - _year;
	}
	else if (currentMonth < _month)
	{
		Age = currentYear - _year - 1;
	}
	else
	{
		if (currentDay >= _day)
		{
			Age = currentYear - _year;
		}
		else {
			Age = currentYear - _year - 1;
		}
	}
	return Age;
}

#endif
