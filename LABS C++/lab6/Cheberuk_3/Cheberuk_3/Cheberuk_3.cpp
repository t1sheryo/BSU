#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {
    std::string s = "", temp = "", in = "";
    int count = 0;
    std::vector <std::string> v;
    std::ifstream fin("input.txt");
    std::getline(fin, s);
    while (std::getline(fin, in)) {
        for (auto c : in) {
            if (c == ' ' || c == '\n') {
                if (s == temp) {
                    count++;
                }
                temp = "";
                continue;
            }
            else {
                temp.push_back(c);
            }
        }
    }
    std::cout << count << "\n" << s;
    return 0;
}