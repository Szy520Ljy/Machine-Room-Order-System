#include<iostream>
using namespace std;
#include"Identity.h"
#include<fstream>
#include<string>
#include"globalFile.h"
#include"Student.h"
#include"Manager.h"
#include"Teacher.h"
//进入学生子菜单
void studentMenu(Identity*& student)
{
	while (true)
	{
		student->operMenu();
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) //申请预约
		{
			stu->applyOrder();

		}
		else if (select == 2) //查看自身预约
		{
			stu->showMyOrder();
		}
		else if (select == 3) //查看所有人预约
		{
			stu->showAllOrder();
		}
		else if(select == 4)
		{
			stu->cancelOrder();
		}
		else //注销登录
		{
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//进入教师子菜单
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1)//查看所有预约
		{
			tea->showAllOrder();
		}
		else if (select == 2)//审核预约
		{
			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//进入管理员子菜单
void managerMenu(Identity*& manager)
{
	while (true)
	{
		manager->operMenu();
		//将父类指针专为子类指针，调用子类其他接口
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		if (select == 1) //添加账号
		{
			//cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2) //查看账号
		{
			//cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3) //查看机房
		{
			//cout << "查看机房" << endl;
			man->showComputer();

		}
		else if (select == 4) //清空预约
		{
			//cout << "清空预约" << endl;
			man->cleanFile();
		}
		else //注销
		{
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//登录功能
void LoginIn(string fileName, int type)
{
	Identity* person = NULL;
	ifstream ifs;
	ifs.open(fileName, ios::in);
	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//准备接收用户信息
	int id = 0;
	string name;
	string pwd;
	if (type == 1)
	{
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入您的职工号" << endl;
		cin >> id;
	}
	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	if (type == 1)
	{
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证登录成功!" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生子菜单
				studentMenu(person);
				return;
			}
			else
			{
				cout << "您输入的信息有误" << endl;
				break;
			}
		}
	}
	else if (type == 2)
	{
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "教师验证登录成功!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师子菜单
				teacherMenu(person);
				return;
			}
			else
			{
				cout << "您输入的信息有误" << endl;
				break;
			}
		}
	}
	else if (type == 3)
	{
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员验证登录成功!" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//进入管理员子菜单
				managerMenu(person);
				return;
			}
			else
			{
				cout << "您输入的信息有误" << endl;
				break;
			}
		}
	}
	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
	return;
}
int main()
{
	int select = 0;
	
	while (true)
	{
		cout << "----------  欢迎来到机房预约系统  ----------" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "-------------------------" << endl;
		cout << "1.学生代表" << endl;
		cout << "2.老    师" << endl;
		cout << "3.管 理 员" << endl;
		cout << "0.退    出" << endl;
		cout << "-------------------------" << endl;
		cout << "请输入您的选择：";
		cin >> select;
		switch (select)
		{
		case 1:
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}