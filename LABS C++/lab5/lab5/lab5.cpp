#include <iostream>
#include <vector>
#include <string>

int main() {
	setlocale(LC_ALL, ".1251");
	std::string s, new_s, cur_s, temp;
	bool flag = true, simplicity = true, str_is_empty = false;   /* flag - говорит, является ли строка числом*/
	int num = 0, simple = 0;
	getline(std::cin, s);
	std::cout << "Знаки препинания: !  \"  (  )  , .  /  :  ;  ?\n";
	s += ".";
	for (size_t i = 0; i < s.size(); ++i) {
		num = (int)s[i];
		switch (num) {
		case 33:
		case 34:
		case 40:
		case 41:
		case 44:
		case 46:
		case 47:
		case 58:
		case 59:
		case 63:                /* проверка на знаки препинания*/
			if (temp.size() == 0)
				str_is_empty = true;
			if (flag == true && str_is_empty == false) {
				simple = stoi(temp);
				for (int i = 2; i < simple; ++i) {
					if (simple % i == 0) {
						simplicity = false;
						break;
					}
				}
			}
			if (simplicity == true && str_is_empty == false) {
				new_s.append(temp);
				new_s.push_back(' ');
			}
			temp.resize(0);
			simplicity = true;
			flag = true; 
			str_is_empty = false;
			break;
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
			temp.push_back(s[i]);
			break;
		default:
			temp.push_back(s[i]);
			flag = false;
			simplicity = false;
			break;
		}
	}
	if (new_s.size() == 0) {
		std::cout << "Строка пуста! Простых чисел не найдено";
	}
	else{ 
		std::cout << new_s; 
	}
	return 0;
}