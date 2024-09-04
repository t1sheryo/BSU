#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::string s = "", temp = "", input = "";
    int count = 0;
    std::ifstream fin("input.txt");
    if (!fin.is_open()) {
        std::cerr << "Error!";
        exit(1);
    }
    std::getline(fin, s);
    while (std::getline(fin, input)) {
        input += " ";
        for (auto c : input) {
            if (c == ' ') {
                if (s == temp) {
                    count++;
                }
                temp.clear();
                continue;
            }
            else {
                temp.push_back(c);
            }
        }
    }
    fin.close();
    std::cout << "String we need to count in our text: \"" << s << "\"" << "\n" << "Number of repetitions: " << count;
    return 0;
}