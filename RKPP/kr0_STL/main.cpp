#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include "String.h"

bool compare(std::pair<String, int>& p1, String& s){
    return s == p1.first;
}

int main() {

    std::string data = "data.txt", query = "query.txt", answer = "answer.txt";
    std::map <std::string, std::vector<std::pair<std::string, int>>> storage;

    std::ifstream input(data);
    if(!input.is_open()){
        std::cerr << "File is opened!";
        exit(1);
    }
    std::string s;

    while(std::getline(input, s)){   // parsing data.txt
        std::vector<std::string> cont;
        std::string tmp;
        for(size_t i = 0; i < s.size(); ++i){
            bool flag = false;
            if(s[i] == ';') flag = true;
            if(i + 1 == s.size()){
                tmp += s[i];
                flag = true;
            }
            if(flag){
                cont.push_back(tmp);
                tmp.clear();
            }
            else{
                tmp += s[i];
            }
        }
        std::pair<std::string, int> cur_p;
        //String conv(cont[1]);
        cur_p.first = cont[1];
        cur_p.second = stoi(cont[2]);
        //String con(cont[0]);
        storage[cont[0]].push_back(cur_p);
    }

    std::ifstream qu(query);
    if(!qu.is_open()){
        std::cerr << "File is opened!";
        exit(1);
    }
    while(std::getline(qu, s)){   // parsing data.txt
        int choice;
        choice = s[0] - '0';
        std::string temp = s.substr(2, s.size() - 2);
        String tmp(temp);
        int count = 0;
        //std::set <int> un;
        std::map <String, std::set<int>> uniq;
        std::set<int>::iterator st;
        switch (choice) {
            case 1:
                for(auto it = storage.begin(); it != storage.end(); ++it) {
                    String key(it->first);
                    if (key == tmp) {
                        for(auto a : storage[it->first]){
                            std::cout << "Hotel name: " << a.first << " - " << a.second << " stars\n";
                        }
                    }
                }
                std::cout << "\n-------------------------------------\n";
                break;
            case 2:
                count = 0;
                for(auto it = storage.begin(); it != storage.end(); ++it){
                    auto res = std::find_if(it->second.begin(), it->second.end(), [tmp](std::pair<std::string, int>& p) {
                        String tmp_comp(p.first);
                        return tmp == tmp_comp;
                    });
                    if(res != it->second.end()) count ++;
                }
                std::cout << "City: " << temp << "- Count: " << count << '\n';
                std::cout << "\n-------------------------------------\n";
                break;
            case 3:
                for(auto it = storage.begin(); it != storage.end(); ++it){
                    uniq.clear();
                    String s(it->first);
                    for(auto a : it->second){
                        uniq[s].emplace(a.second);
                    }
                    for(auto it = uniq.begin(); it != uniq.end(); ++it){
                        for(st = it->second.begin(); st != it->second.end(); ++st){
                            std::cout << "City: " << it->first << "- Stars: " << *st << '\n';
                        }
                    }
                }
                std::cout << "\n-------------------------------------\n";
                break;
        }
    }

    return 0;
}
