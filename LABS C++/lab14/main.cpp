#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iomanip>


struct StudMark{
    std::string subject;
    int mark;
};

struct StudData{
    std::string name;
    int number;
    std::vector <StudMark> marks;
    double average_mark;
    friend bool operator< (StudData& a, StudData& b){
        bool flag = false;
        if(a.name < b.name){
            flag = true;
        }
        else if(a.name == b.name){
            if(a.average_mark > b.average_mark){
                flag = true;
            }
        }
        return flag;
    }
};

int main() {

    setlocale(LC_ALL, ".1251");

    std::ifstream fin("students.txt");
    if(!fin.is_open()){
        std::cerr << "File \"students.txt\" is not opened!\n";
        exit(1);
    }

    std::map <int, StudData> studs;
    std::string s, tmp;
    char del;
    std::cout << "Введите символ-разделитель: ";
    std::cin >> del;
    while(std::getline(fin, s)){
        s = s + del;
        std::string fio, subj;
        StudData cur_data;
        StudMark cur_mark;
        std::vector <StudMark> grades;
        int number_zachet = 0, grade = 0, cnt = 0, rem = 0;
        for(size_t c = 0; c < s.length(); ++c){
            if(s[c] == del){
                switch(cnt){
                    case 0:
                        fio = tmp;
                        break;
                    case 1:
                        number_zachet = stoi(tmp);
                        break;
                    default:
                        switch (cnt % 2) {
                            case 0:
                                subj = tmp;
                                break;
                            case 1:
                                grade = stoi(tmp);
                                cur_mark.mark = grade;
                                cur_mark.subject = subj;
                                grades.push_back(cur_mark);
                                break;
                        }
                }
                tmp.clear();
                cnt++;
            }
            else{
                tmp.push_back(s[c]);
            }
            if(c == s.length() - 1){
                cur_data.name = fio;
                cur_data.number = number_zachet;
                cur_data.marks = grades;
                studs.emplace(number_zachet, cur_data);
            }
        }
    }


//    2. Отсортировать по номеру зачетки и вывести.
    for(auto it = studs.begin(); it != studs.end(); ++it){
        std::cout << it->first << " - " << it->second.name << "\n";
    }
    std::cout << "\n\n";


////    3. Вычислить средний балл по каждому студенту.
    for(auto it = studs.begin(); it != studs.end(); ++it){
        double average = 0, sum = 0;
        for(size_t i = 0; i < it->second.marks.size(); ++i){
            sum += it->second.marks[i].mark;
        }
        average = sum / it->second.marks.size();
        it->second.average_mark = average;
    }


//    4. Вывести список всех студентов в виде «Номер по порядку,
//    Фамилия, Номер_зачетки, Средний_балл» в алфавитном порядке, для
//    одинаковых фамилий и инициалов – по убыванию среднего балла.

    std::vector <StudData> students;
    for(auto it : studs){
        StudData a = it.second;
        students.push_back(a);
    }
    sort(students.begin(), students.end());
    for(size_t i = 0; i < students.size(); ++i){
        std::cout << i << ") " << students[i].name << "; " << students[i].number << "; " << students[i].average_mark << ";\n";
    }
    std::cout << "\n\n";


//    5. Вывести список студентов, средний балл которых принадлежит
//    заданному диапазону. Порядок – по убыванию среднего балла.
    std::multimap <double, std::string, std::greater<double>> sorted_grade;
    std::cout << "Введите границы баллов: ";
    double left = 0, right = 0;
    std::cin >> left >> right;
    for(auto a : studs){
        double temp_grade = 0;
        std::string temp_name;
        temp_grade = a.second.average_mark;
        temp_name = a.second.name;
        if(temp_grade <= right && temp_grade >= left) {
            sorted_grade.emplace(temp_grade, temp_name);
        }
    }
    for(auto a : sorted_grade){
        std::cout << a.second << ": " << a.first << "\n";
    }
    std::cout << "\n\n";


////    6. Вывести список студентов, которые сдавали заданный предмет.
    std::cout << "Введите предмет: ";
    std::string comp_subj;
    std::cin >> comp_subj;
    std::cout << "Сдавали предмет " << comp_subj << ":\n";
    for(auto a : studs){
        for(size_t i = 0; i < a.second.marks.size(); ++i){
            if(a.second.marks[i].subject == comp_subj){
                std::cout << a.second.name << "; " << a.second.number << "; " << a.second.average_mark << ";\n";
            }
        }
    }
    std::cout << "\n\n";


//    7. Определить, сколько студентов сдавало каждый предмет.
    std::map <std::string, int> subjects;
    for(auto a : studs){
        for(size_t i = 0; i < a.second.marks.size(); ++i){
            int cnt = 0;
            std::string cur_subject = a.second.marks[i].subject;
            auto it = subjects.find(cur_subject);
            if(it == subjects.end()){
                subjects.emplace(cur_subject, 1);
            }
            else {
                cnt = it->second;
                cnt++;
                subjects.insert_or_assign(cur_subject, cnt);
            }
        }
    }
    for(auto a : subjects){
        std::cout << a.first << ": " << a.second << "\n";
    }
    std::cout << "\n\n";


//    8. Для каждого предмета определить средний балл, и вывести
//    предметы и баллы в порядке убывания баллов.
    std::map <std::string , std::pair<int, double>> subjects_average;
    for(auto a : studs){
        for(size_t i = 0; i < a.second.marks.size(); ++i){
            std::string cur_subj = a.second.marks[i].subject;
            double cur_mark = a.second.marks[i].mark;
            double cur_sum = 0;
            int cnt = 0;
            auto it = subjects_average.find(cur_subj);
            if(it != subjects_average.end()){
                cur_sum = subjects_average.find(cur_subj)->second.second;
                cnt = subjects_average.find(cur_subj)->second.first;
            }
            cur_sum = cur_sum * cnt + cur_mark;
            cnt++;
            double new_average = cur_sum / cnt;
            std::pair<int, double> p1(cnt, new_average);
            subjects_average.insert_or_assign(cur_subj, p1);
        }
    }
    for(auto a : subjects_average){
        std::cout << a.first << ": " << a.second.second << "\n";
//        std::cout << a.first << ": " << std::setw(5) <<std::setprecision(5) << a.second.second << "\n";
    }
    std::cout << "\n\n";


//    9. Найти всех студентов с максимальной суммой баллов.
    std::cout << "Студенты с максимальной суммой баллов: ";
    int max_sum = 0;
    for(auto s : studs){
        int cur_sum = 0;
        for(size_t i = 0; i < s.second.marks.size(); ++i){
            cur_sum += s.second.marks[i].mark;
        }
        if(cur_sum > max_sum){
            max_sum = cur_sum;
        }
    }
    for(auto s : studs){
        int cur_sum = 0;
        for(size_t i = 0; i < s.second.marks.size(); ++i){
            cur_sum += s.second.marks[i].mark;
        }
        if(cur_sum == max_sum){
            std::cout << s.second.name << "; " << s.second.number << "; " << s.second.average_mark << ";\n";
        }
    }
    std::cout << "\n";


//    10. Найти всех студентов с неудовлетворительными оценками(1,2,3)
    for(auto s : studs){
        std::map <std::string , int> current;
        bool flag = false;
        for(size_t i = 0; i < s.second.marks.size(); ++i){
            if(s.second.marks[i].mark == 1 || s.second.marks[i].mark == 2 || s.second.marks[i].mark == 3){
                std::pair<std::string, int> p(s.second.marks[i].subject, s.second.marks[i].mark);
                current.insert(p);
                flag = true;
            }
        }
        if(flag){
            std::cout << s.second.name << ":\n";
            for(auto b : current){
                std::cout << b.first << " - " << b.second << "\n";
            }
        }
        current.clear();
    }

    return 0;
}
