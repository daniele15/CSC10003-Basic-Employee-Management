#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef SUB_FUNCTION_H
#define SUB_FUNCTION_H

#include <iostream>
#include "MyException.h"
#include <string.h>
#include "Date.h"

using namespace std;

int countDigits(int n)
{
	int temp = n;
	int count = 0;
	while (temp >= 10)
	{
		temp /= 10;
		count++;
	}
	return count;
}

int inputNumber()
{
	string value;
	cin >> value;
	cin.ignore();
	bool status = false;
	int times = 0;
	while (times < 3 && !status)
	{
		status = true;
		for (int i = 0; i < value.length(); i++)
		{
			if (value[i] > '9' || value[i] < '0')
			{
				status = false;
				break;
			}
		}
		times++;
		if (!status && times < 3)
		{
			cout << "Error: input must be a number!\n";
			if (times == 2)
			{
				cout << "Re-enter (last time): ";
			}
			else
			{
				cout << "Re-enter: ";
			}
			cin >> value;
			cin.ignore();
		}
	}
	if (!status)
	{
		MyException e;
		cout << "Error: input must be a number!";
		cout << "\nError: " << e.ExceededAttempt() << endl;
		cout << "Input value default set to 0!\n";
		return 0;
	}
	int result = stoi(value);
	return result;
}

char* inputID()
{
	cout << "Note: NVSX ID dang 1xxxx\n\tNVCN ID dang 2xxxx\nDuoc nhap lai toi da 2 lan!\n";
	cout << "ID: ";
	string ID;
	cin >> ID;
	cin.ignore();

	//--------- Check if ID is correct type ----------
	int times = 0;
	bool status = false;
	while (times < 3 && !status)
	{
		if (ID.length() == 5)
		{
			status = true;
			if (ID[0] != '1' && ID[0] != '2')
			{
				status = false;
				goto firstFalse;
			}
			for (int i = 1; i < 5; i++)
			{
				if (ID[i] > '9' || ID[i] < '0')
				{
					status = false;
					break;
				}
			}
			
		}
	firstFalse:
		times++;
		if (times < 3 && !status)
		{
			cout << "Error: ID must be 5 numeric characters! (1st char must = 1 (NVSX) or = 2 (NVCN)\n";
			if (times == 2)
			{
				cout << "Re-enter ID (last time): ";
			}
			else
			{
				cout << "Re-enter ID: ";
			}
			cin >> ID;
			cin.ignore();
		}
	}
	if (status == false)
	{
		MyException e;
		cout << "Error: ID must be 5 numeric characters!";
		cout << "\nError: " << e.ExceededAttempt() << endl;
		cout << "Input value default set to 00000!\n";
		ID = "00000";
	}
	//--------- Check if ID is correct type (done) ----------
	char* result = new char[6];
	strcpy(result,ID.c_str());
	return result;
}

string inputGender()
{
	string _gender;
	//--------- Check if gender is correct type ----------
	int times = 0;
	bool status = false;
	cout << "Gender (Male/Female or Nam/Nu): ";
	cin >> _gender;
	cin.ignore();
	status = false;
	times = 0;
	while (times < 3 && !status)
	{
		if (_gender == "Nam" || _gender == "nam" || _gender == "Male" || _gender == "male")
		{
			_gender = "Nam";
			status = true;
			break;
		}
		else if (_gender == "Nu" || _gender == "nu" || _gender == "Female" || _gender == "female")
		{
			_gender = "Nu";
			status = true;
			break;
		}
		else
		{
			status = false;
		}
		times++;
		if (times < 3 && !status)
		{
			cout << "Error: Gender must be (Male/Female or Nam/Nu)!\n";
			if (times == 2)
			{
				cout << "Re-enter gender (last time): ";
			}
			else
			{
				cout << "Re-enter gender: ";
			}
			cin >> _gender;
			cin.ignore();
		}
	}
	if (status == false)
	{
		MyException e;
		cout << "Error: Gender must be (Male/Female or Nam/Nu)!\n";
		cout << "\nError: " << e.ExceededAttempt() << endl;
		cout << "Input value default set to N/A!\n";
		_gender = "N/A";
	}
	//--------- Check if gender is correct type (done) ----------
	return _gender;
}

Date inputDateWithGender(string _gender)
{
	Date tempD;
	//--------- Check if Age is in range ----------
	int times = 0;
	bool status = false;
	cout << "Birthday ";
	tempD.inputCstring();
	int Age = tempD.cal_Age();
	while (times < 3 && !status)
	{
		status = true;
		if (_gender == "Nam" || _gender=="N/A")
		{
			if (Age < 18 || Age>60)
			{
				status = false;
				cout << "Error: Age not in range 18-60. Please re-enter birthday.\n";
			}
		}
		else if (_gender == "Nu")
		{
			if (Age < 18 || Age>55)
			{
				status = false;
				cout << "Error: Age not in range 18-55. Please re-enter birthday.\n";
			}
		}
		times++;
		if (times < 3 && !status)
		{
			if (times == 2)
			{
				cout << "Re-enter birthday (last time) ";
			}
			else
			{
				cout << "Re-enter birthday ";
			}
			tempD.inputCstring();
			Age = tempD.cal_Age();
		}
	}
	if (status == false)
	{
		MyException e;
		cout << "Error: Age not in range!";
		cout << "\nError: " << e.ExceededAttempt() << endl;
		cout << "Input value default set to 01/01/1900!\n";
		Date temp2(01, 01, 1900);
		tempD = temp2;
	}
	//--------- Check if Age is in range (done)----------
	return tempD;
}

void checkID(char*& _ID)
{
	string ID(_ID, 6);

	//--------- Check if ID is correct type ----------
	if (ID.length() == 5)
	{
		for (int i = 0; i < 5; i++)
		{
			if (ID[i] > '9' || ID[i] < '0')
			{
				ID = "ERROR";
				break;
			}
		}
	}
	//--------- Check if ID is correct type (done) ----------
	strcpy(_ID, ID.c_str());
}

void checkGender(string& _gender)
{
	//--------- Check if gender is correct type ----------
	if (_gender == "Nam" || _gender == "nam" || _gender == "Male" || _gender == "male")
	{
		_gender = "Nam";
	}
	else if (_gender == "Nu" || _gender == "nu" || _gender == "Female" || _gender == "female")
	{
		_gender = "Nu";
	}
	else
	{
		_gender = "N/A";
	}
}

void checkDateWithGender(string _gender, Date& tempD)
{
	//--------- Check if Age is in range ----------
	int Age = tempD.cal_Age();

	if (_gender == "Nam" || _gender == "N/A")
	{
		if (Age < 18 || Age>60)
		{
			cout << "Error: Age not in range 18-60. Please re-enter birthday.\n";
			Date temp2(01, 01, 1990);
			tempD = temp2;
		}
	}
	else if (_gender == "Nu")
	{
		if (Age < 18 || Age>55)
		{
			cout << "Error: Age not in range 18-55. Please re-enter birthday.\n";
			Date temp2(01, 01, 1990);
			tempD = temp2;
		}
	}
}


int inputMenuNumber()
{
	string value;
	cin >> value;
	cin.ignore();
	bool status = false;
	int times = 0;
	while (times < 3 && !status)
	{
		status = true;
		if (value.length()>2)
		{
			status = false;
		}
		else {
			for (int i = 0; i < value.length(); i++)
			{
				if (value[i] > '9' || value[i] < '0')
				{
					status = false;
					break;
				}
			}
		}
		times++;
		if (!status && times < 3)
		{
			cout << "Error: input must be a number between 0 and 12!\n";
			if (times == 2)
			{
				cout << "Re-enter (last time): ";
			}
			else
			{
				cout << "Re-enter: ";
			}
			cin >> value;
			cin.ignore();
		}
	}
	if (!status)
	{
		MyException e;
		cout << "Error: input must be a number between 0 and 12!";
		cout << "\nError: " << e.ExceededAttempt() << endl;
		cout << "Input value default set to 0!\n";
		return 0;
	}
	int result = stoi(value);
	return result;
}
int inputNum(int min, int max)
{
	string value;
	cin >> value;
	cin.ignore();
	int status = 0;
	int times = 0;
	while (times < 3 && !status)
	{
		status = 1;
		if (value.length() > countDigits(max))
		{
			status = -1;
			cout << "Error: input must be a number between " << min << " and " << max << "!\n";
		}
		else {
			for (int i = 0; i < value.length(); i++)
			{
				if (value[i] > '9' || value[i] < '0')
				{
					status = 0;
					cout << "Error: input must be a number!\n";
					break;
				}
			}
		}
		times++;
		if (status != 1 && times < 3)
		{
			if (times == 2)
			{
				cout << "Re-enter (last time): ";
			}
			else
			{
				cout << "Re-enter: ";
			}
			cin >> value;
			cin.ignore();
		}
	}
	if (!status)
	{
		MyException e;
		cout << "Error: input must be a number between "<<min<<" and "<< max<< " !\n";
		cout << "\nError: " << e.ExceededAttempt() << endl;
		cout << "Input value default set to " << min << "!\n";
		return min;
	}
	int result = stoi(value);
	
	if (result <min or result >max)
	{
		cout << "Error: input must be a number between " << min << " and " << max << " !\n";
		cout << "Re-enter (last time): ";
		cin >> value;
		cin.ignore();
		if (value.length() > countDigits(max))
		{
			cout << "Error: input must be a number between " << min << " and " << max << "!\n";
			cout << "Input value default set to " << min << "!\n";
			return min;
		}
		else {
			for (int i = 0; i < value.length(); i++)
			{
				if (value[i] > '9' || value[i] < '0')
				{
					status = 0;
					cout << "Error: input must be a number!\n";
					cout << "Input value default set to " << min << "!\n";
					return min;
				}
			}
		}
	}
	return result;
}

int Menu()
{
	    system("cls");
		cout << "==========\tCHUONG TRINH QUAN LY CONG TY DON GIAN\t==========\n";
		cout << "0.  THOAT CHUONG TRINH.\n";
		cout << "1.  GHI DANH SACH NHAN VIEN VAO FILE 'ds_NhanVien.dat'.\n";
		cout << "2.  DOC DANH SACH NHAN VIEN TU FILE 'ds_NhanVien.dat'.\n";
		cout << "3.  XUAT DANH SACH NHAN VIEN RA MAN HINH.\n";
		cout << "4.  TINH TONG TIEN LUONG CUA TAT CA NHAN VIEN.\n";
		cout << "5.  TIM NHAN VIEN CO LUONG CAO NHAT.\n";
		cout << "6.  TINH LUONG TRUNG BINH TRONG CONG TY.\n";
		cout << "7.  NHAP VAO MA, TIM NHAN VIEN TUONG UNG.\n";
		cout << "8.  NHAP VAO TEN, TIM NHAN VIEN TUONG UNG.\n";
		cout << "9.  THONG KE NHAN VIEN THEO THANG SINH.\n";
		cout << "10. THEM MOT NHAN VIEN VAO DANH SACH, CAP NHAT RA FILE.\n";
		cout << "11. XOA MOT NHAN VIEN KHOI DANH SACH, CAP NHAT RA FILE.\n";
		cout << "12. GHI DANH SACH CAC NHAN VIEN CO LUONG NHO HON LUONG TRUNG BINH CUA CONG TY RA FILE emp_LowerAvgSalary.dat.\n";

		cout << "\nMoi nhap lua chon (0-12): \n";
		int n = inputNum(0, 12);
		return n;
}

#endif