#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>	
#include <list>
#include <memory>
#include <algorithm>
#include <functional>
#include <array>

using namespace std;


namespace filePATHS
{
	const string studPATH = "students.txt";
}

class Student
{
private:
	string name;
	int age;
	int course;
	double averageRating;
public:
	Student() : name("unknown"), age(-1), course(-1), averageRating(-1) {}
	Student(string name, int age, int course, double averageRating) : name(name), age(age), course(course), averageRating(averageRating) {}

	Student(const Student& other) : name(other.name), age(other.age), course(other.course), averageRating(other.averageRating) {}
	Student& operator=(const Student& other)
	{
		name = other.name;
		age = other.age;
		course = other.course;
		averageRating = other.averageRating;
		return *this;
	}
	~Student() {}
	Student(Student&& other)
	{
		name = other.name;
		age = other.age;
		course = other.course;
		averageRating = other.averageRating;
		
		other.name = "";
		other.age = 0;
		other.course = 0;
		other.averageRating = 0;
	}
	Student& operator=(Student&& other)
	{
		if (this != &other)
		{
			name = other.name;
			age = other.age;
			course = other.course;
			averageRating = other.averageRating;

			other.name = "";
			other.age = 0;
			other.course = 0;
			other.averageRating = 0;
		}
		return *this;
	}

	string getName() { return name; }
	int getAge() { return age; }
	int getCourse() { return course; }
	double getAverageRating() { return averageRating; }

	void setName(string name) { this->name = name; }
	void setAge(int age) { this->age = age; }
	void setCourse(int course) { this->course = course; }
	void setAverageRating(double averageRating) { this->averageRating = averageRating; }

	friend bool operator<(const shared_ptr<Student>& student1, const shared_ptr<Student>& student2)
	{
		return student1->averageRating < student2->averageRating;
	}
	friend bool operator==(const shared_ptr<Student>& student1, const shared_ptr<Student>& student2)
	{
		return student1->averageRating == student2->averageRating;
	}

	friend ostream& operator<<(ostream& buf, const shared_ptr<Student>& student)
	{
		buf << student->name << ' ' << student->age << ' ' << student->course << ' ' << student->averageRating << endl;
		return buf;
	}
	friend istream& operator>>(istream& buf, shared_ptr<Student>& student)
	{
		buf >> student->name >> student->age >> student->course >> student->averageRating;
		return buf;
	}
};



using Vstudents = vector<shared_ptr<Student>>;
using Lstudents = list<shared_ptr<Student>>;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//===================================== ������ � �������� =====================================//
	Vstudents VBASE;
	
	VBASE.push_back(make_shared<Student>("����", 18, 2, 8.5));
	VBASE.push_back(make_shared<Student>("������", 19, 3, 7.2));
	VBASE.push_back(make_shared<Student>("ϸ��", 17, 1, 6.9));

	cout << "������ ����� ����������: " << endl;
	for (const auto& item: VBASE)
	{
		cout << item;
	}

	cout << endl;
	Vstudents::iterator iter1 = VBASE.begin() + 1;
	VBASE.erase(iter1);

	cout << endl;
	cout << "������ ����� �������� ������� ��������: " << endl;
	for (const auto& item : VBASE)
	{
		cout << item;
	}
	cout << endl;

	cout << endl;
	cout << "������ ����� ���������� �� �������� ����� � ������� �����������: " << endl;
	sort(VBASE.begin(), VBASE.end(), less<shared_ptr<Student>>());

	for (const auto& item : VBASE)
	{
		cout << item;
	}
	cout << endl;
	string name = "ϸ��";

	cout << "������: ���� ������: " << endl;
	Vstudents::iterator iter2 = find_if(VBASE.begin(), VBASE.end(), [&name](const shared_ptr<Student> a) { return name == a->getName(); });

	cout << (*iter2);
	cout << endl;
	//===================================================================================================//


	//===================================== ������ � ��������������� ������� =====================================//
	Lstudents LBASE;

	LBASE.push_back(make_shared<Student>("�������", 20, 4, 4.0));
	LBASE.push_front(make_shared<Student>("���������", 19, 3, 6.7));
	LBASE.push_back(make_shared<Student>("��������", 17, 1, 5.7));

	cout << "������ ����� ����������: " << endl;
	for (const auto& item : LBASE)
	{
		cout << item;
	} 
	cout << endl;

	cout << "������ ����� ���������� (�����) � ������� �������� �� �������� �����: " << endl;
	LBASE.sort([](const shared_ptr<Student>& a, const shared_ptr<Student>& b) { return a->getAverageRating() > b->getAverageRating(); });
	for (const auto& item : LBASE)
	{
		cout << item;
	}
	cout << endl;

	LBASE.pop_front();

	cout << "������ ����� �������� 1-�� ��������: " << endl;
	for (const auto& item : LBASE)
	{
		cout << item;
	}
	cout << endl;

	cout << "������� ������ ������: " << LBASE.size() << endl;

	cout << "�������� ���������� ������: " << endl;
	Lstudents::iterator Liter = LBASE.begin();
	while (Liter != LBASE.end())
	{
		cout << (*Liter)->getName() << ' ' << (*Liter)->getAge() << ' ' << (*Liter)->getCourse() << ' ' << (*Liter)->getAverageRating() << endl;
		Liter++;
	}
	//============================================================================================================//

	//===================================== ������ � ��������������� ������� =====================================//
	shared_ptr<Student> student1 = make_shared<Student>("�������", 20, 4, 4.0);
	shared_ptr<Student> student2 = make_shared<Student>("����", 20, 4, 8.0);
	shared_ptr<Student> student3 = make_shared<Student>("����", 19, 3, 7.0);
	array<shared_ptr<Student>, 3> ABASE {student1, student2, student3};
	cout << endl;
	cout << "������� ������ ������������ �������: " << ABASE.size() << endl;
	cout << endl;
	cout << "2-�� �������: " << ABASE.at(1) << endl;
	cout << endl;
	cout << "�������� ���� ��������� ���������� �� 3-��: ";
	ABASE.fill(student3);
	cout << endl;
	for (const auto& item : ABASE)
	{
		cout << item;
	}
	//============================================================================================================//
	return 0;
}