#pragma once
#include <string>
#include <iostream>
#include <fstream>

//class MyException {
//private:
//	std::string text;
//public:
//	MyException(std::string text) {
//		this->text = text;
//	}
//	std::string what() {
//		return text;
//	}
//};

class List {
private:
	struct File {
		std::string name, extension;
		File* next;
	};
	File* first;

	void Clone(const List& other);

	void Erase();
public:
	/*����������� ��� ����������, ��������� ������ ������;*/
	List();

	/*����������� �����������;*/
	List(const List& other);

	/*���������� ��������� ������������;*/
	List& operator= (const List& other);

	/*����������;*/
	~List();

	/*������� ������ �������� � ������ ������;*/
	void InsertFirst(const std::string& name, const std::string& extension);

	/*������� ������ �������� � ����� ������;*/
	void InsertLast(const std::string& name, const std::string& extension);

	/*�������� ������� �������� ������;*/
	bool DeleteFirst();

	/*�������� ���������� �������� ������;*/
	bool DeleteLast();

	/*�������� �������� �� ��������;*/
	bool Delete(const std::string& name, const std::string& extension);

	/*����� �������� �� �������� � ��������� ����� ���������, ����������� � �������� ������;*/
	bool Contains(const std::string& name, const std::string& extension, int& count);

	/*�������� ������ � ���������� ���� ��������;*/
	void ForEach(void f(std::string&, std::string&));

	/*�������� ������ � ������� callback - �������, ������� �� �������� ���������� ��������*/
	void ForEach(void f(const std::string&, const std::string&)) const;

	void Print() const;
};