#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef CONGTY_H
#define CONGTY_H

#include "DynamicArray.h"
#include "NhanVien.h"
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

class CongTy
{
private:
	DynamicArray<NhanVien*> _list;
	double _totalSalary;
	double _avgSalary;
public:
	CongTy();
	~CongTy();
	CongTy(CongTy& cty);
	CongTy(DynamicArray<NhanVien*> list);
	
	bool isEmpty();
	void clear();
	void input();
	// 1. Xuat danh sach ra file ‘ds_NhanVien.dat’
	void printFile(string FileName);
	void printCSV(string FileName);
	// 2. Doc danh sach tu file ‘ds_NhanVien.dat’
	void inputFile(string FileName);
	// 3. Xuat danh sach ra man hinh
	void print();
	// 4. Tinh tong tien luong cua tat ca nhan vien (luu vao bien _totalSalary)
	void calTotalSalary();
	double getTotalSalary();
	// 5. Nhan vien co luong cao nhat
	NhanVien* highestSalaryMember();
	// 6. Tim luong trung binh (luu vao bien _avgSalary)
	void calAVGSalary();
	double getAVGSalary();
	// 7. Nhap ma, tim nv tuong ung
	NhanVien* findMember_ID();
	// 8. Nhap ten, tim nv tuong ung
	NhanVien* findMember_Name();
	// 9. So nhan vien sinh trong thang 5
	int calMemberBornInMonth();
	// 10. them nhan vien moi, cap nhat ra file 'ds_NhanVien'
	void insertMember();
	// 11. Xoa nhan vien khoi danh sach, cap nhat ra file 'ds_NhanVien'
	void removeMember();
	// 12. DS nhan vien co luong < luong trung binh
	CongTy lowerSalaryList();
	
};


//==========
CongTy::CongTy()
{
	DynamicArray<NhanVien*> newList;
	_list = newList;
	_totalSalary = 0;
	_avgSalary = 0;
}
CongTy::~CongTy() {}
CongTy::CongTy(CongTy& cty)
{
	_list = cty._list;
	_totalSalary = cty.getTotalSalary();
	_avgSalary = cty.getAVGSalary();
}

CongTy::CongTy(DynamicArray<NhanVien*> list)
{
	_list = list;
	calTotalSalary();
	calAVGSalary();
}
bool CongTy::isEmpty()
{
	if (_list.size() == 0)
		return true;
	return false;
}
void CongTy::clear()
{
	_list.clear();
	_totalSalary = 0;
	_avgSalary = 0;
	
}
void CongTy::input()
{
	char key;
	int i = 0;
	cout << "Nhan phim \"Esc\" sau khi nhap xong!\n";
	while (true)
	{
		cout << "Nhap nhan vien thu " << i + 1 << ": \n";
		cin.ignore();
		NhanVien temp;
		int value=0;
		temp.input();
		if (temp.getID()[0] == '2')
		{
			cout << "Number of working days: ";
			value = inputNumber();
			NhanVien* A = new NVCongNhat(temp, value);
			_list.push_back(A);
		}
		else if (temp.getID()[0] == '1')
		{
			cout << "Number of product: ";
			value = inputNumber();
			NhanVien* B = new NVSanXuat(temp, value);
			_list.push_back(B);
		}
		cout << "Nhan phim \"Enter\" de nhap tiep, nhap xong nhan \"Esc\"\n";
		key = _getch();
		if (key != 13) {
			break;
		}
		i++;
	}
}
void CongTy::print()
{
	cout << left;
	cout << setw(7) << "ID" << setw(21) << "Ho Ten" << setw(6) << "Gioi" << setw(12) << "Ngay sinh" << setw(30) << "Dia chi" << setw(8) << "SP/NC" << right << "Luong (VND)\n";

	for (int i = 0; i < _list.size(); i++)
	{
		cout << _list[i]->toString() << endl;
	}
}

void CongTy::printFile(string FileName)
{
	ofstream fout;
	fout.open(FileName);
	fout << left;
	fout << setw(7) << "ID" << setw(21) << "Ho Ten" << setw(6) << "Gioi" << setw(12) << "Ngay sinh" << setw(30) << "Dia chi" << setw(13) << "SP/NC" << right << "Luong (VND)\n";
	for (int i = 0; i < _list.size(); i++)
	{
		fout << _list[i]->toString() << endl;
	}
	fout.close();
}
void CongTy::printCSV(string FileName)
{
	ofstream fout;
	fout.open(FileName);
	fout << left;
	//fout << setw(7) << "ID" << setw(21) << "Ho Ten" << setw(6) << "Gioi" << setw(12) << "Ngay sinh" << setw(30) << "Dia chi" << setw(6) << "SP/NC" << right << "Luong\n";
	fout << _list[0]->toStringCSV();
	for (int i = 1; i < _list.size()-1; i++)
	{
		fout << endl;
		fout << _list[i]->toStringCSV();
	}
	fout.close();
}

void CongTy::calTotalSalary()
{
	double total = 0;
	for (int i = 0; i < _list.size(); i++)
	{
		total += _list[i]->getSalary();
	}
	_totalSalary = total;
}
void CongTy::calAVGSalary()
{
	double avg = _totalSalary / _list.size();
	_avgSalary = avg;
}
double CongTy::getTotalSalary()
{
	return _totalSalary;
}
double CongTy::getAVGSalary()
{
	return _avgSalary;
}

void CongTy::inputFile(string FileName)
{
	ifstream fin;
	fin.open(FileName);
	while (!fin.eof())
	{
		char* line = new char[150];
		fin.getline(line, 150);
		
		const char* ID = strtok(line, ",");
		const char* name = strtok(NULL, ",");
		char* gend = strtok(NULL, ",");
		char* birth = strtok(NULL, ",");
		const char* addr = strtok(NULL, ",");
		char* num = strtok(NULL, ",");

		string gender(gend);
		Date birthD(birth);
		int value = stoi(num);
		double sala = 0;
		NhanVien temp(ID, name, birthD, gender, addr, sala);
		

		if (temp.getID()[0] == '2')
		{
			NhanVien* A = new NVCongNhat(temp, value);
			_list.push_back(A);
		}
		else if (temp.getID()[0] == '1')
		{
			NhanVien* B = new NVSanXuat(temp, value);
			_list.push_back(B);
		}
	}
	calTotalSalary();
	calAVGSalary();
	fin.close();
}

// 5. Nhan vien co luong cao nhat
NhanVien* CongTy::highestSalaryMember()
{
	double max = 0;
	NhanVien* ans= new NhanVien;
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i]->getSalary() > max)
		{
			max = _list[i]->getSalary();
			ans = _list[i];
		}
	}
	return ans;
}
// 7. Nhap ma, tim nv tuong ung
NhanVien* CongTy::findMember_ID()
{
	int index = -1;
	char* ID = inputID();
	if (strcmp(ID, "00000") == 0)
	{
		return NULL;
	}
	NhanVien* ans=new NhanVien;
	for (int i = 0; i < _list.size(); i++)
	{
		if (strcmp(_list[i]->getID(),ID)==0)
		{
			ans = _list[i];
			index = i;
			break;
		}
	}
	if (index == -1)
		return NULL;
	return ans;
}
// 8. Nhap ten, tim nv tuong ung
NhanVien* CongTy::findMember_Name()
{
	int index = -1;
	char* name = new char[31];
	cout << "Full Name: ";
	cin.getline(name, 31);
	NhanVien* ans = new NhanVien;
	for (int i = 0; i < _list.size(); i++)
	{
		if (strcmp(_list[i]->getName(), name) == 0)
		{
			ans = _list[i];
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return NULL;
	}
	return ans;
}
// 9. So nhan vien sinh trong thang 5
// Neu nhap thang sai qua 3 lan hoac nhap so 0 se tra ve -1 => loi
int CongTy::calMemberBornInMonth()
{
	int month = inputMenuNumber(); // Tinh nang tuong tu, do co 12 thang (= 12 yeu cau)
	if (month == 0)
		return -1; // input month is wrong 
	int result = 0;
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i]->getBirthday().getM() == month)
		{
			result++;
		}
	}
	return result;
}
// 10. them nhan vien moi, cap nhat ra file 'ds_NhanVien.dat'
// Chi can goi ham, khong can truyen thong tin nhan vien, chuc nang nhap co san trong ham.
// Luu y: ma nhan vien san xuat bat dau la 1, co dang: 1xxxx
//		  ma nhan vien cong nhat bat dau la 2, co dang: 2xxxx
void CongTy::insertMember()
{
	cout << "Nhap nhan vien muon them vao:\n";
	NhanVien temp;
	int value = 0;
	temp.input();
	if (temp.getBirthday().getY() == 1900)
	{
		cout << "Error! Invalid input data!\n";
	}
	else if (temp.getID()[0] == '2')
	{
		cout << "Number of working days: ";
		value = inputNum(22, 26);
		NhanVien* A = new NVCongNhat(temp, value);
		_list.push_back(A);
		cout << "Successfully added new member!\n";
		cout << _list[_list.size() - 1]->toString() << endl;
		
		// BEAUTI VIEW
		printFile("OUTPUT.TXT");
		printCSV("ds_NhanVien.dat");
	}
	else if (temp.getID()[0] == '1')
	{
		cout << "Number of product: ";
		value = inputNum(10, 15);
		NhanVien* B = new NVSanXuat(temp, value);
		_list.push_back(B);
		cout << "Successfully added new member!\n";
		cout << _list[_list.size() - 1]->toString() << endl;
		
		// BEAUTI VIEW
		printFile("OUTPUT.TXT");
		printCSV("ds_NhanVien.dat");
	}
	else {
		cout << "Error! ID not match any type of staff!\nMa nhan vien khong phu hop!\n";
	}
	
}
// 11. Xoa nhan vien khoi danh sach, cap nhat ra file 'ds_NhanVien'
// Nhap ma nhan vien muon xoa trong ham
void CongTy::removeMember()
{
	int index=-1;
	cout << "Nhap ID cua nhan vien muon xoa: ";
	char* ID = inputID();
	for (int i = 0; i < _list.size(); i++)
	{
		if (strcmp(_list[i]->getID(), ID) == 0)
		{
			index=i;
			break;
		}
	}
	if (index == -1)
	{
		cout << "Not found member!\n";
	}
	else
	{
		_list.removeAt(index);
		cout << "Successfully delete member ID = "<<ID<<" !\n";
		printCSV("ds_NhanVien.dat");
		// BEAUTI VIEW
		printFile("OUTPUT.TXT");
	}
}
// 12. DS nhan vien co luong < luong trung binh
// Du lieu tra ve dang CongTy
CongTy CongTy::lowerSalaryList()
{
	DynamicArray<NhanVien*> result;
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i]->getSalary()<_avgSalary)
		{
			result.push_back(_list[i]);
		}
	}
	CongTy Res(result);
	return Res;
}

#endif