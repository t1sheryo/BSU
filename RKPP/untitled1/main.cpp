#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <locale>

class Solution {
private:
    std::string data;
    std::string query;
    std::string answer;
    std::map < std::string, std::vector<std::pair<std::string, std::string>>> storage;

    void ParseInput(std::ifstream& input) {
        std::string s;
        while (std::getline(input, s)) {  // обрабатываем DATA.txt
            std::vector <std::string> cont;
            std::string tmp;
            for (size_t i = 0; i < s.size(); ++i) {
                if (s[i] == ';') {
                    cont.push_back(tmp);
                    tmp.clear();
                }
                else if (i + 1 == s.size()) {
                    tmp += s[i];
                    cont.push_back(tmp);
                    tmp.clear();
                }
                else {
                    tmp += s[i];
                }
            }
            storage[cont[1]].push_back(std::pair<std::string, std::string>(cont[0], cont[2]));
        }
    }

    void MakeQuery(std::ifstream& qu, std::ofstream& output) {
        std::set<std::pair<std::string, std::string>> trety;
        std::string s;

        while (std::getline(qu, s)) {   // обрабатываем QUERY.txt
            int choice = s[0] - '0';
            std::string tmp = s.substr(2, s.size() - 2);
            std::string trans;
            int count = 0;
            trans = tmp;
            std::transform(trans.begin(), trans.end(), trans.begin(), tolower);
            output << "Query: " << s << '\n';

            switch (choice) {
                case 1:
                    CASE1(output, trans);
                    break;
                case 2:
                    CASE2(output, trans, tmp, count);
                    break;
                case 3:
                    CASE3(output, trety);
                    break;
            }
        }
    }

    void CASE1(std::ofstream& output, std::string& trans) {
        for (auto it = storage.begin(); it != storage.end(); ++it) {
            std::string key = it->first;
            std::transform(key.begin(), key.end(), key.begin(), tolower);
            if (key == trans) {
                for (auto a : it->second) {
                    output << "Patient: " << a.first << " - Time: " << a.second << '\n';
                }
            }
        }
        output << "----------------------------------------------\n";
    }

    void CASE2(std::ofstream& output, std::string& trans, std::string& tmp, int& count) {
        for (auto it = storage.begin(); it != storage.end(); ++it) {
            auto iter = std::find_if(it->second.begin(), it->second.end(), [&trans](std::pair<std::string, std::string>& p) {
                std::string ss = p.first;
                std::transform(ss.begin(), ss.end(), ss.begin(), tolower);
                return ss == trans;
            });
            if (iter != it->second.end()) count++;
        }
        output << "Patient: " << tmp << " - Visits: " << count << '\n';
        output << "----------------------------------------------\n";
    }

    void CASE3(std::ofstream& output, std::set<std::pair<std::string, std::string>>& trety) {
        std::set<std::pair<std::string, std::string>>::iterator st;
        std::pair<std::string, std::string> p;
        for (auto it = storage.begin(); it != storage.end(); ++it) {
            p.first = it->first;
            for (auto a : it->second) {
                p.second = a.second;
                trety.emplace(p);
            }
        }
        for (st = trety.begin(); st != trety.end(); ++st) {
            output << "Date: " << st->second << " - Doctor: " << st->first << '\n';
        }
        output << "----------------------------------------------\n";
    }
public:
    Solution(std::string _data, std::string _query, std::string _answer) : data(_data), query(_query), answer(_answer) {
        std::ifstream input(data);
        if (!input.is_open()) {
            std::cerr << "DATA.txt is not opened!";
            exit(1);
        }

        std::ifstream qu(query);
        if (!qu.is_open()) {
            std::cerr << "QUERY.txt is not opened!";
            exit(1);
        }

        std::ofstream output(answer);
        if (!output.is_open()) {
            std::cerr << "ANSWER.txt is not opened!";
            exit(1);
        }

        ParseInput(input);
        MakeQuery(qu, output);
    }

    ~Solution() {
        std::cout << "SUCCESS!\n";
    }
};

int main() {
    setlocale(LC_ALL, ".1251");

    std::string data = "DATA.txt", query = "QUERY.txt", answer = "ANSWER.txt";

    Solution sol(data, query, answer);

    return 0;
}