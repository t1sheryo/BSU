#include "list.h"

List::List() {
	first = nullptr;
}

List::List(const List& other) : List() {
	Clone(other);
}

void List::Clone(const List& other) {
	for (auto it = other.first; it != nullptr; it = it->next) {
		InsertLast(it->name, it->extension);
	}
}

void List::Erase() {
	File* f, * l;
	f = first;
	while (f != nullptr) {
		l = f->next;
		delete f;
		f = l;
	}
	first = nullptr;
};

List::~List() {
	Erase();
}

List& List::operator= (const List& other) {
	if (&other == this) {
		return *this;
	}
	Erase();
	Clone(other);
	return *this;
}

void List::InsertFirst(const std::string& name, const std::string& extension) {
	File* item = new File;
	item->name = name;
	item->extension = extension;
	item->next = first;
	first = item;
}

void List::InsertLast(const std::string& name, const std::string& extension) {
	File* item = new File;
	item->name = name;
	item->extension = extension;
	auto p = first;
	auto prev = p;
	if (p == nullptr) {
		item->next = first;
		first = item;
	}
	else {
		while (p != nullptr) {
			prev = p;
			p = p->next;
		}
		item->next = prev->next;
		prev->next = item;
	}
}

bool List::DeleteFirst() {
	if (first == nullptr) {
		return false;
	}
	File* p = first;
	first = first->next;
	delete p;
	return true;
}

bool List::DeleteLast() {
	auto p = first;
	auto last = p;
	auto prelast = p;
	if (p == nullptr) {
		return false;
	}
	else {
		while (p != nullptr) {
			last = p;
			p = p->next;
		}
		p = first;
		prelast = first;
		while (p != last) {
			prelast = p;
			p = p->next;
		}
	}
	/*if (last == nullptr) {
		return false;
	}*/
	if (last == first) {
		delete first;
		first = nullptr;
	}
	else {
		File* item = prelast->next;
		prelast->next = item->next;
		delete item;
	}
	return true;
}

bool List::Delete(const std::string& name, const std::string& extension) {
	auto cur = first;
	auto prev = first;
	if (cur == nullptr) {
		return false;
	}
	while (cur != nullptr) {
		if (cur->name == name && cur->extension == extension) {
			break;
		}
		prev = cur;
		cur = cur->next;
	}
	if (cur == first) {
		DeleteFirst();
		return true;
	}
	else if (cur == nullptr) {
		return true;
	}
	else {
		prev->next = cur->next;
		delete cur;
		return true;
	}
}

bool List::Contains(const std::string& name, const std::string& extension, int& count) {
	if (first == nullptr) {
		return false;
	}
	auto cur = first;
	while (cur != nullptr) {
		count++;
		if (cur->name == name && cur->extension == extension) {
			break;
		}
		cur = cur->next;
	}
	if (cur != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

void List::Print() const {
	File* p = first;
	if (p == nullptr)
		std::cout << "list is empty\n";
	if (p != nullptr) {
		/*std::cout << "list:\n";*/
		while (p != nullptr) {
			std::cout << p->name << p->extension << '\n';
			p = p->next;
		}
	}
}

void List::ForEach(void f(std::string&, std::string&)) {
	File* p = first;
	while (p != nullptr) {
		f(p->name, p->extension);
		p = p->next;
	}
}

void List::ForEach(void f(const std::string&, const std::string&)) const {
	File* p = first;
	while (p != nullptr) {
		f(p->name, p->extension);
		p = p->next;
	}
}
