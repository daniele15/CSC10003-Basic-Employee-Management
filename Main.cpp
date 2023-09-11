#include "CongTy.h"

int main()
{
	CongTy Company;
	char key = '1';
	int choice = 0;
	int result_value = 0;

	NhanVien* maxSala = NULL;
	NhanVien* FoundMember = NULL;
	

	while (key == '1')
	{
		choice = Menu();
		switch (choice)
		{
		case 0:
			cout << "0.THOAT CHUONG TRINH.\n";
			system("pause");
			return 0;
		case 1:
			cout << "1.  GHI DANH SACH NHAN VIEN VAO FILE 'ds_NhanVien.dat'.\n";
			if (Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				// BEAUTI VIEW
				Company.printFile("OUTPUT.TXT");
				// CSV FORMAT (EASY TO READ)
				Company.printCSV("ds_NhanVien.dat");
				cout << "Successfully write on file 'ds_NhanVien.dat' (Da ghi danh sach ra file thanh cong).\n";
			}
			break;
		case 2:
			cout << "2.  DOC DANH SACH NHAN VIEN TU FILE 'ds_NhanVien.dat'.\n";
			if (!Company.isEmpty())
			{
				cout << "Data existed / Dang ton tai du lieu.\n";
				cout << "Xoa de nhap moi hay khong?\t0. Khong xoa\t1.Xoa, nhap du lieu moi!\n";
				cout << "Nhap lua chon cua ban: "; 
				cin >> key;
				if (key == '1')
				{
					Company.clear();
					Company.inputFile("ds_NhanVien.dat");
					cout << "Successfully read from file 'ds_NhanVien.dat' (Da doc danh sach tu file).\n";
				}
				else
				{
					cout << "Khong nhap du lieu moi!\n";
				}
			}
			else
			{
				Company.inputFile("ds_NhanVien.dat");
				cout << "Successfully read from file 'ds_NhanVien.dat' (Da doc danh sach tu file).\n";
			}
			
			break;
		case 3:
			cout << "3.  XUAT DANH SACH NHAN VIEN RA MAN HINH.\n";
			if(Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				Company.print();
			}
			break;
		case 4:
			cout << "4.  TINH TONG TIEN LUONG CUA TAT CA NHAN VIEN.\n";
			if (Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				Company.calTotalSalary();
				cout << "Tong tien luong cua cong ty = " << setprecision(0) << fixed << Company.getTotalSalary() <<"VND." << endl;
			}
			break;
		case 5:
			cout << "5.  TIM NHAN VIEN CO LUONG CAO NHAT.\n";
			if (Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				maxSala = Company.highestSalaryMember();
				cout << "Nhan vien co luong cao nhat la:\n";
				cout << maxSala->toString() << endl;
				/*if (maxSala != NULL)
					delete maxSala;*/
			}
			break;
		case 6:
			cout << "6.  TINH LUONG TRUNG BINH TRONG CONG TY.\n";
			if (Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				Company.calAVGSalary();
				cout << "Luong trung binh cua cong ty = " << setprecision(0) << fixed << Company.getAVGSalary() << endl;
			}
			break;
		case 7:
			cout << "7.  NHAP VAO MA, TIM NHAN VIEN TUONG UNG.\n";
			if (Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				FoundMember = Company.findMember_ID();
				if (FoundMember == NULL)
					cout << "Khong tim thay.\n";
				else
				{
					cout << "Tim thay:\n";
					cout << FoundMember->toString() << endl;
				}
				/*if (FoundMember != NULL)
					delete FoundMember;*/
			}
			break;
		case 8:
			cout << "8.  NHAP VAO TEN, TIM NHAN VIEN TUONG UNG.\n";
			if (Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				FoundMember = Company.findMember_Name();
				if (FoundMember == NULL)
					cout << "Khong tim thay.\n";
				else
				{
					cout << "Tim thay:\n";
					cout << FoundMember->toString() << endl;
				}
				/*if (FoundMember != NULL)
					delete FoundMember;*/
			}
			break;
		case 9: 
			cout << "9.  THONG KE SO NHAN VIEN THEO THANG SINH (NHAP THANG MUON THONG KE).\n";
			if (Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				result_value = 0;
				result_value = Company.calMemberBornInMonth();
				if (result_value == -1)
				{
					cout << "Input month is in valid./ Thang nhap vao khong ton tai!\n";
				}
				else
				{
					cout << "So nhan vien co sinh nhat trong thang la: " << result_value << ".\n";
				}
			}
			break;
		case 10:
			cout << "10. THEM MOT NHAN VIEN VAO DANH SACH, CAP NHAT RA FILE.\n";
			Company.insertMember();
			break;
		case 11:
			cout << "11. XOA MOT NHAN VIEN KHOI DANH SACH, CAP NHAT RA FILE.\n";
			if (Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				Company.removeMember();
			}
			
			break;
		case 12:
			cout << "12. GHI DANH SACH CAC NHAN VIEN CO LUONG NHO HON LUONG TRUNG BINH CUA CONG TY RA FILE emp_LowerAvgSalary.dat.\n";
			if (Company.isEmpty())
			{
				cout << "Data is empty / Du lieu khong ton tai.\n";
				cout << "Moi chon chuc nang khac!\n";
			}
			else
			{
				Company.lowerSalaryList().print();
				Company.lowerSalaryList().printFile("emp_LowerAvgSalary.dat");
			}
			break;
		default:
			cout << "Lua chon khong phu hop!\nMac dinh chon 0.\n";
			cout << "0.THOAT CHUONG TRINH.\n";
			system("pause");
			return 0;
		}
		cout << "\nTiep tuc su dung: \n0. Khong\t1.Co\n";
		cin >> key;
	}
	cout << "Ket thuc chuong trinh!\n";

	system("pause");
	return 0;
}
