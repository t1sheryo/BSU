#include <algorithm>
#include <cstdio>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

struct student {
    std::string fio = "";
    int course = 0;
    int group = 0;
};

class train {
public:
    train(){
        this->number = 0;
        this->destination = "";
        this->type = "";
        this->time_to_go = "";
        this->time_in_way = "";
        this->hours_time = 0;
        this->minutes_time = 0;
        this->hours_travel = 0;
        this->minutes_travel = 0;
    }
    train(int number, std::string destination, std::string type, std::string time_to_go, std::string time_in_way){
        this->number = number;
        this->destination = destination;
        this->type = type;
        this->time_to_go = time_to_go;
        this->time_in_way = time_in_way;
        this->hours_time = stoi(time_to_go.substr(0,2));
        this->minutes_time = stoi(time_to_go.substr(3,2));
        this->hours_travel = stoi(time_in_way.substr(0,2));
        this->minutes_travel = stoi(time_in_way.substr(3,2));
    }
    int GetNumber(){
        return number;
    }
    std::string GetDestination(){
        return destination;
    }
    std::string GetType(){
        return type;
    }
    std::string GetTimeToGo(){
        return time_to_go;
    }
    std::string GetTimeInWay(){
        return time_in_way;
    }
    int GetHours_time(){
        return hours_time;
    }
    int GetMinutes_time(){
        return minutes_time;
    }
    int GetHours_travel(){
        return hours_travel;
    }
    int GetMinutes_travel(){
        return minutes_travel;
    }

    void Print(){
        std::cout << "����� ������: " << number << "\n";
        std::cout << "�������� ������ ����������: " << destination << "\n";
        std::cout << "��� ������: " << type << "\n";
        std::cout << "����� �����������: " << time_to_go << "\n";
        std::cout << "����� � ����: " << time_in_way << "\n\n";
    }
private:
    int number;
    std::string destination;
    std::string type;
    std::string time_to_go;
    std::string time_in_way;
    int hours_time = 0;
    int minutes_time = 0;
    int hours_travel = 0;
    int minutes_travel = 0;
};

int main() {
    setlocale(LC_ALL, ".1251");

//    Practic.Problem1

//    ������� ��������� vector <int>, ������ � ���������� � �������� � ���� �����, �� ������� ���������� ��������� ��� �����.��������� ��������������� ��������� � ������, ����������:
    std::vector <int> nums;
    int c = 0;
    int tmp;
    while (std::cin >> c) {
        nums.push_back(c);
    }
    std::cin.clear();
    std::cin.ignore();
    for (auto i : nums) {
        std::cout << i << " ";
    }
    std::cout << "\n";
//    ? ����� �����;
    int sum = 0;
    std::for_each(nums.begin(), nums.end(), [&sum](int a) { sum += a; });
    std::cout << "����� �����: " << sum << "\n";
//    ? ����� ���������� �����;
    std::cout << "����� ���������� �����: " << nums.size() << "\n";
    std::cout << "������� �������� �����, � ������� ���������� ��������: ";
//    ? ���������� �����, ������ ���������;
    int k = 0;
    std::cin >> k;
    std::cout << "���������� �����, ������ " << k << " : " << std::count_if(nums.begin(), nums.end(), [k](int a) { return k == a; }) << "\n";
    //? ���������� �����, ��������������� �������, ��������, �������, ��� N�;
    std::cout << "������� �������� �����, � ������� ���������� ��������(>): ";
    int N = 0;
    std::cin >> N;
    printf("���������� �����, ��������������� �������, ��������, �������, ��� %d�: ", N);
    std::cout << " " << std::count_if(nums.begin(), nums.end(), [N](int a) { return a > N; }) << "\n";
//    ? �������� ��� ���� ������� ��������������(����� ����� �����);
    int middle = sum / nums.size();
    std::cout << "������� ��������������: " << middle << "\n";
    std::cout << "�������� ��� ���� ������� ��������������: " << "\n";
    for (int i = 0; i < nums.size(); ++i) {
        if(nums[i] == 0){
            nums[i] = middle;
        }
        std::cout << nums[i] << " ";
    }
    std::cout << "\n";
//    ? �������� � ������� �������� ������� ����� ���� ����� �� ��������� ��������� ����� �� �������(�� �������� ���, � �������);
    std::cout << "������� ������� ���������: ";
    auto p1 = nums.begin();
    auto p2 = nums.begin();
    int pos1 = 0, pos2 = 0;
    std::cin >> pos1 >> pos2;
    p1 = p1 + pos1 - 1;    p2 = p2 + pos2;
    int sum_interval = 0;
    std::for_each(p1, p2, [&sum_interval](int a) {sum_interval += a; });
    std::for_each(nums.begin(), nums.end(), [sum_interval](int& a) { a += sum_interval; });
    for (auto i : nums) {
      std::cout << i << " ";
    }
    std::cout << "\n";
//    ? �������� ��� �����, ������ ������� ���� ������ �����, �� �������� ������������� � ������������ �������� ����� �������;
    int dif = *(max_element(nums.begin(), nums.end())) - *(min_element(nums.begin(), nums.end()));
    for_each(nums.begin(), nums.end(), [dif](int& a) { if (abs(a) % 2 == 0) { a = dif; }});
    std::cout << "�������� ��� �����, ������ ������� ���� ������ �����, �� �������� ������������� � ������������ �������� ����� �������: " << dif << "\n";
    for (auto i : nums) {
      std::cout << i << " ";
    }
    std::cout << "\n";
//    ? ������� �� ������������������ ��� ������ �� ������ �����, ����� ������� �� ���.
    std::cout << "������������: ";
    std::sort(nums.begin(), nums.end());
    auto forwardpointer = std::unique(nums.begin(), nums.end());
    nums.resize(std::distance(nums.begin(), forwardpointer));
    for (auto i : nums) {
      std::cout << i << " ";
    }
    std::cout << "\n\n\n";


//    Practic.Problem2

    std::ifstream fin1("students.txt");
    std::ofstream fout1("Fio.txt");
    std::ofstream fout2("Groups.txt");
    if (!fin1.is_open()) {
        std::cerr << "Input file is not open!\n";
        exit(1);
    }
    if (!fout1.is_open()) {
        std::cerr << "Output file 1 is not open!\n";
        exit(1);
    }
    if (!fout2.is_open()) {
        std::cerr << "Output file 2 is not open!\n";
        exit(1);
    }
    std::string s = "";
    std::vector<student> studs;
    std::vector<std::string> three;
    while (std::getline(fin1, s)) {
        s += ";";
        std::string tmp = "";
        int count = 0;
        student stud;
        for (auto c: s) {
            if (c == ';') {
                three.push_back(tmp);
                tmp.clear();
                count++;
            } else {
                tmp.push_back(c);
            }
            if (count == 3) {
                stud.fio = three[0];
                stud.course = stoi(three[1]);
                stud.group = stoi(three[2]);
                studs.push_back(student{three[0], stoi(three[1]), stoi(three[2])});
                three.clear();
            }
        }
    }
//    for (auto c : studs) {
//      std::cout << c.fio;
//    }
    sort(studs.begin(), studs.end(), [](student &a, student &b) { return a.fio < b.fio; });
    for (auto st: studs) {
        fout1 << st.fio << ";" << st.course << ";" << st.group << "\n";
    }
    std::cout << "File \"Fio.txt\" was successfully created!\n";
    sort(studs.begin(), studs.end(), [](student &a, student &b) {
        if (a.course == b.course) {
            return a.group < b.group;
        } else {
            return a.course < b.course;
        }
    });
    for (auto c: studs) {
        fout2 << c.fio << ";" << c.course << ";" << c.group << ";\n";
    }
    std::cout << "File \"Groups.txt\" was successfully created!\n";
    fin1.close();
    fout1.close();
    fout2.close();



//    Practic.Problem3

    std::ifstream fin2("trains.txt");
    if(!fin2.is_open()){
        std::cerr << "Fin2 is not opened\n";
        exit(1);
    }
    std::vector <train> trains;
    std::string ss = "";
    std::cout << "������� �����������:";
    char del;
    std::cin >> del;
    while(std::getline(fin2, ss)){
        int num = 0;
        ss += del;
        std::string dest = "", type = "", time = "", travel = "", tmp = "", time1 = "", time2 = "";
        int hours_time = 0, minutes_time = 0, hours_tr = 0, cnt = 0, minutes_tr = 0;
        for(auto c : ss){
            if(c == del){
                std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
                cnt++;
                switch(cnt){
                    case 1:
                        num = stoi(tmp);
                        break;
                    case 2:
                        dest = tmp;
                        break;
                    case 3:
                        type = tmp;
                        break;
                    case 4:
                        time1 = tmp;
                        hours_time = stoi(tmp.substr(0,2));
                        minutes_time = stoi(tmp.substr(3,2));
                        break;
                    case 5:
                        time2 = tmp;
                        hours_tr = stoi(tmp.substr(0,2));
                        minutes_tr = stoi(tmp.substr(3,2));
                        break;
                    default:
                        break;
                }
                tmp.clear();
            }
            else {
                tmp.push_back(c);
            }
            if(cnt == 5){
                trains.emplace_back(num, dest, type, time1, time2);
            }
        }
    }

    sort(trains.begin(), trains.end(), [] (train a, train b) { return a.GetTimeToGo() < b.GetTimeToGo(); });

    bool flag = false;
    std::cout << "������� �������� �������:\n";
    std::string left = "", right = "";
    std::cin >> left >> right;
    for(auto a : trains){
        std::string temp_time = a.GetTimeToGo();
        if((temp_time >= left) && (temp_time <= right)){
            a.Print();
            flag = true;
        }
    }
    if(!flag){
        std::cout << "��� ����������� ������!\n";
    }

    flag = false;
    std::cout << "������� ������ ����� ����������:\n";
    std::string need_dest = "";
    std::cin >> need_dest;
    std::transform(need_dest.begin(), need_dest.end(), need_dest.begin(), ::tolower);
    for(auto a : trains){
        std::string temp_dest = a.GetDestination();
        if(need_dest == temp_dest){
            a.Print();
            flag = true;
        }
    }
    if(!flag){
        std::cout << "��� ����������� ������!\n";
    }

    flag = false;
    std::cout << "������� ������ ����� ���������� (������ �����):\n";
    std::string need_desty = "";
    std::cin >> need_desty;
    std::transform(need_desty.begin(), need_desty.end(), need_desty.begin(), ::tolower);
    for(auto a : trains){
        std::string temp_desty = a.GetDestination();
        if((need_desty == temp_desty) && (a.GetType() == "speedy")){
            a.Print();
            flag = true;
        }
    }
    if(!flag){
        std::cout << "��� ����������� ������!\n";
    }

    flag = false;
    std::cout << "������� ������ ����� ���������� (����� �������):\n";
    std::string need = "";
    std::cin >> need;
    std::transform(need.begin(), need.end(), need.begin(), ::tolower);
    train fast;
    std::string comp_time = "23:59";
    for(auto a : trains){
        std::string temp = a.GetDestination();
        if((need == temp) && (a.GetTimeInWay() <= comp_time)){
            fast = a;
            comp_time = a.GetTimeInWay();
            flag = true;
        }
    }
    if(!flag){
        std::cout << "��� ����������� ������!\n";
    }
    fast.Print();
    fin2.close();



    return 0;
}