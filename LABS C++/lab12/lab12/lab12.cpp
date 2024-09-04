#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <fstream>

struct student {
    std::string fio = "";
    int course = 0;
    int group = 0;
};

int main() {
    setlocale(LC_ALL, ".1251");
    /*Создать контейнер vector <int>, ввести с клавиатуры и записать в него числа, не задавая количество элементов при вводе.Используя соответствующие алгоритмы и методы, подсчитать:*/
    std::vector <int> nums;
    int c = 0;
    int tmp;
    while (std::cin >> c) {
      nums.push_back(c);
    }
    //std::cin.clear();
    //std::cin.ignore();
    //for (auto i : nums) {
    //  std::cout << i << " ";
    //}
    //std::cout << "\n";
    ///* сумму чисел;*/
    //int sum = 0;
    ///*for (auto a : nums) {
    //  sum += a;
    //}
    //std::cout << "сумма чисел: " << sum << "\n";*/
    //std::for_each(nums.begin(), nums.end(), [&sum](int a) { sum += a; });
    //std::cout << "сумма чисел: " << sum << "\n";
    ///* общее количество чисел;*/
    //std::cout << "общее количество чисел: " << nums.size() << "\n";
    ///* количество чисел, равных заданному;*/
    //int k = 0;
    //std::cin >> k;
    //std::cout << "количество чисел, равных " << k << " : " << std::count_if(nums.begin(), nums.end(), [k](int a) { return k == a; }) << "\n";
    //// количество чисел, удовлетворяющих условию, например, «больше, чем N»;
    //int N = 0;
    //std::cin >> N;
    //printf("количество чисел, удовлетворяющих условию, например, «больше, чем »: ", N);
    //std::cout << " " << std::count_if(nums.begin(), nums.end(), [N](int a) { return a > N; }) << "\n";
    ///* заменить все нули средним арифметическим(взять целую часть);*/
    //int middle = sum / nums.size();
    //std::cout << "среднее арифметическое: " << middle << "\n";
    //std::cout << "заменить все нули средним арифметическим: " << "\n";
    //for (auto i : nums) {
    //  std::cout << i << " ";
    //}
    ///* добавить к каждому элементу вектора сумму всех чисел из заданного интервала этого же вектора(не числовой оси, а вектора);*/
    //auto p1 = nums.begin();
    //auto p2 = nums.begin();
    //int pos1 = 0, pos2 = 0;
    //std::cin >> pos1 >> pos2;
    //p1 = p1 + pos1 - 1;    p2 = p2 + pos2 - 1;
    //int sum_interval = 0;
    //std::for_each(p1, p2, [&sum_interval](int a) {sum_interval += a; });
    //std::for_each(nums.begin(), nums.end(), [sum_interval](int& a) { a += sum_interval; });
    //for (auto i : nums) {
    //  std::cout << i << " ";
    //}
    ///* заменить все числа, модуль которых есть четное число, на разность максимального и минимального элемента этого вектора;*/
    //int dif = *(max_element(nums.begin(), nums.end())) - *(min_element(nums.begin(), nums.end()));
    //for_each(nums.begin(), nums.end(), [dif](int a) { if (a % 2 == 0) { a = dif; }});
    //std::cout << "заменить все числа, модуль которых есть четное число, на разность максимального и минимального элемента этого вектора: ";
    //for (auto i : nums) {
    //  std::cout << i << " ";
    //}
    ///* удалить из последовательности все равные по модулю числа, кроме первого из них.*/
    std::unique(nums.begin(), nums.end());
    for (auto i : nums) {
      std::cout << i << " ";
    }



    //std::ifstream fin("text.txt");
    //std::ofstream fout1("Fio.txt");
    //std::ofstream fout2("Groups.txt");
    //if (!fin.is_open()) {
    //    std::cerr << "Input file is not open!\n";
    //    exit(1);
    //}
    //if (!fout1.is_open()) {
    //    std::cerr << "Output file 1 is not open!\n";
    //    exit(1);
    //}
    //if (!fout2.is_open()) {
    //    std::cerr << "Output file 2 is not open!\n";
    //    exit(1);
    //}
    //std::string s = "";
    //std::vector <student> studs;
    //std::vector <std::string> three;
    //while (std::getline(fin, s)) {
    //    s += ";";
    //    std::string tmp = "";
    //    int count = 0;
    //    student stud;
    //    for (auto c : s) {
    //        if (c == ';') {
    //            three.push_back(tmp);
    //            tmp.clear();
    //            count++;
    //        }
    //        else {
    //            tmp.push_back(c);
    //        }
    //        if (count == 3) {
    //            /*stud.fio = three[0];
    //            stud.course = stoi(three[1]);
    //            stud.group = stoi(three[2]);*/
    //            studs.push_back(student{ three[0], stoi(three[1]), stoi(three[2]) });
    //            three.clear();
    //        }
    //    }
    //}
    /*for (auto c : studs) {
      std::cout << c.fio;
    }*/
   /* sort(studs.begin(), studs.end(), [](student& a, student& b) { return a.fio < b.fio; });
    for (auto st : studs) {
        fout1 << st.fio << ";" << st.course << ";" << st.group << "\n";
        std::cout << st.fio << ";" << st.course << ";" << st.group << "\n";
    }

    sort(studs.begin(), studs.end(), [](student& a, student& b) {
        if (a.course == b.course) {
            return a.group < b.group;
        }
        else {
            return a.course < b.course;
        }
        });
    for (auto c : studs) {
        fout2 << c.fio << ";" << c.course << ";" << c.group << ";\n";
    }*/

    return 0;
}