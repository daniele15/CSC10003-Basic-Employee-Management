#define _CRT_SECURE_NO_WARNINGS
#pragma once 
#ifndef NHANVIEN_H
#define NHANVIEN_H

#include <iostream>
#include <iomanip>
#include "Date.h"
#include "sub_Function.h"

using namespace std;

// ========== CLASS DECLARATION ==========
// class NhanVien
class NhanVien
{
protected:
	char* _ID;
	char* _name;
	Date _birthday;
	string _gender;
	char* _address;
	double _salary;
public:
	NhanVien();
	NhanVien(const char*& ID, const char*& name, const Date& birthday, const string& gender, const char*& address, const double& salary);
	NhanVien(const NhanVien& nv);
	~NhanVien();

	virtual void input();
	virtual string toString();
	virtual string toStringCSV();
	virtual double cal_Salary();

	char* getID();
	char* getName();
	Date getBirthday();
	string getGender();
	char* getAddress();
	double getSalary();

};

// class NVSanXuat inherited from class NhanVien
class NVSanXuat : public NhanVien
{
private:
	int _product;
public:
	NVSanXuat();
	NVSanXuat(const char*& ID, const char*& name, const Date& birthday, const string& gender,const char*& address, const double& salary, int product);
	NVSanXuat(const NVSanXuat& nv);
	NVSanXuat(const NhanVien& nv, int product);
	~NVSanXuat();

	NVSanXuat operator=(const NVSanXuat& sx);
	void input();
	string toString();
	string toStringCSV();
	double cal_Salary();
	int getProduct();
};

//class NVCongNhat inherited from class NhanVien
class NVCongNhat : public NhanVien
{
private:
	int _dayWork;
public:
	NVCongNhat();
	NVCongNhat(const char*& ID, const char*& name, const Date& birthday, const string& gender,const char*& address, const double& salary, int dayWork);
	NVCongNhat(const NVCongNhat& nv);
	NVCongNhat(const NhanVien& nv, int dayWork);
	~NVCongNhat();
	NVCongNhat operator=(const NVCongNhat& cn);
	void input();
	string toString();
	string toStringCSV();
	double cal_Salary();

	int getDayWork();
};

// ========== CLASS NHANVIEN IMPLEMENTATION ==========
NhanVien::NhanVien()
{
	_ID = new char[6];
	_name = new char[31];
	_address = new char[51];
	_gender = "";
	_salary = 0;
}
NhanVien::NhanVien(const char*& ID, const char*& name, const Date& birthday, const string& gender,const char*& address, const double& salary)
{
	_ID = new char[6];
	_name = new char[31];
	_address = new char[51];
	strcpy(_ID, ID);
	strcpy(_name, name);
	_birthday = birthday;
	_gender = gender;
	strcpy(_address, address);
	_salary = salary;
}
NhanVien::NhanVien(const NhanVien& nv)
{
	_ID = new char[6];
	_name = new char[31];
	_address = new char[51];
	strcpy(_ID, nv._ID);
	strcpy(_name, nv._name);
	strcpy(_address, nv._address);
	_birthday = nv._birthday;
	_gender = nv._gender;
	_salary = nv._salary;
}
NhanVien::~NhanVien()
{
	delete[] _ID;
	delete[] _name;
	delete[] _address;
}
void NhanVien::input()
{
	char* ID = inputID();
	strcpy(_ID, ID);

	cout << "Full Name: ";
	cin.getline(_name, 31);

	_gender = inputGender();
	_birthday = inputDateWithGender(_gender);

	cout << "Address: ";
	cin.getline(_address, 51);
}
string NhanVien::toString()
{
	stringstream builder;
	builder << left;
	builder << setw(7) << _ID << setw(21) << _name << setw(6) <<_gender<<setw(12) << _birthday.toString() << setw(30) << _address;
	string result = builder.str();
	return result;
}
string NhanVien::toStringCSV()
{
	stringstream builder;
	builder << left;
	builder << _ID <<"," << _name << "," << _gender << "," << _birthday.toString() << "," << _address;
	string result = builder.str();
	return result;
}
double NhanVien::cal_Salary() { _salary = 0; return 0; };
char* NhanVien::getID() { return _ID; }
char* NhanVien::getName() { return _name; }
Date NhanVien::getBirthday() { return _birthday; }
string NhanVien::getGender() { return _gender; }
char* NhanVien::getAddress() { return _address; }
double NhanVien::getSalary() { return _salary; }
// ========== CLASS NVSANXUAT IMPLEMENTATION ==========
NVSanXuat::NVSanXuat():NhanVien()
{
	_product = 0;
}
NVSanXuat::NVSanXuat(const char*& ID, const char*& name, const Date& birthday, const string& gender,const char*& address, const double& salary, int product)
	:NhanVien(ID, name, birthday, gender, address,salary) 
{
	_product = product;
}
NVSanXuat::NVSanXuat(const NVSanXuat& nv) : NhanVien(nv)
{
	_product = nv._product;
}
NVSanXuat::NVSanXuat(const NhanVien& nv, int product) :NhanVien(nv)
{
	_product = product;
	cal_Salary();
}
NVSanXuat::~NVSanXuat()
{
	//cout << "Destructed NVSanXuat\n";
}
NVSanXuat NVSanXuat::operator=(const NVSanXuat& sx)
{
	strcpy(_ID, sx._ID);
	strcpy(_name, sx._name);
	strcpy(_address, sx._address);
	_birthday = sx._birthday;
	_gender = sx._gender;
	_product = sx._product;
	_salary = sx._salary;
	return *this;
}
void NVSanXuat::input()
{
	NhanVien::input();
	cout << "Number of products: ";
	_product = inputNum(10,15);
	_salary = cal_Salary();
}
string NVSanXuat::toString()
{
	stringstream builder;
	builder << left;
	builder << NhanVien::toString() << setw(6) << _product;
	builder << right << setw(13) <<setprecision(0) << fixed << _salary;
	string result = builder.str();
	return result;
}
string NVSanXuat::toStringCSV()
{
	stringstream builder;
	builder << left;
	builder << NhanVien::toStringCSV() << "," << _product;
	string result = builder.str();
	return result;
}
double NVSanXuat::cal_Salary()
{
	double result = _product * 50000;
	_salary = result;
	return result;
}
int NVSanXuat::getProduct() { return _product; }
// ========== CLASS NVCONGNHAT IMPLEMENTATION ==========
NVCongNhat::NVCongNhat() :NhanVien()
{
	_dayWork = 0;
}
NVCongNhat::NVCongNhat(const char*& ID, const char*& name, const Date& birthday, const string& gender,const char*& address, const double& salary, int dayWork)
	:NhanVien(ID, name, birthday, gender, address,salary)
{
	_dayWork = dayWork;
}
NVCongNhat::NVCongNhat(const NVCongNhat& nv) : NhanVien(nv)
{
	_dayWork = nv._dayWork;
}
NVCongNhat::NVCongNhat(const NhanVien& nv, int dayWork) :NhanVien(nv)
{
	_dayWork = dayWork;
	cal_Salary();
}
NVCongNhat::~NVCongNhat()
{
	//cout << "Destructed NVCongNhat\n";
}
NVCongNhat NVCongNhat::operator=(const NVCongNhat& cn)
{
	strcpy(_ID, cn._ID);
	strcpy(_name, cn._name);
	strcpy(_address, cn._address);
	_birthday = cn._birthday;
	_gender = cn._gender;
	_dayWork = cn._dayWork;
	_salary = cn._salary;
	return *this;
}
void NVCongNhat::input()
{
	NhanVien::input();
	cout << "Number of working days: ";
	_dayWork = inputNum(22,26);
	_salary = cal_Salary();
}
string NVCongNhat::toString()
{
	stringstream builder;
	builder << left;
	builder << NhanVien::toString() << setw(6) << _dayWork << right << setw(13) << setprecision(0) << fixed << _salary;
	string result = builder.str();
	return result;
}
string NVCongNhat::toStringCSV()
{
	stringstream builder;
	builder << left;
	builder << NhanVien::toStringCSV() << "," << _dayWork;
	string result = builder.str();
	return result;
}
double NVCongNhat::cal_Salary()
{
	double result = _dayWork * 500000;
	_salary = result;
	return result;
}
int NVCongNhat::getDayWork() { return _dayWork; }
#endif

