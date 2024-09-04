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
	/*конструктор без параметров, создающий пустой список;*/
	List();

	/*конструктор копирования;*/
	List(const List& other);

	/*перегрузка оператора присваивания;*/
	List& operator= (const List& other);

	/*деструктор;*/
	~List();

	/*вставка нового элемента в начало списка;*/
	void InsertFirst(const std::string& name, const std::string& extension);

	/*вставка нового элемента в конец списка;*/
	void InsertLast(const std::string& name, const std::string& extension);

	/*удаление первого элемента списка;*/
	bool DeleteFirst();

	/*удаление последнего элемента списка;*/
	bool DeleteLast();

	/*удаление элемента по значению;*/
	bool Delete(const std::string& name, const std::string& extension);

	/*поиск элемента по значению с подсчетом числа сравнений, выполненных в процессе поиска;*/
	bool Contains(const std::string& name, const std::string& extension, int& count);

	/*просмотр списка с изменением всех значений;*/
	void ForEach(void f(std::string&, std::string&));

	/*просмотр списка с вызовом callback - функции, которая не изменяет хранящееся значение*/
	void ForEach(void f(const std::string&, const std::string&)) const;

	void Print() const;
};