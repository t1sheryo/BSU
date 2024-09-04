#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

typedef std::map <int, int> map_type;
typedef std::map <int, int>::iterator it_type;
typedef std::pair <std::map <int, int>::iterator, std::map <int, int>::iterator> pair_it_type;

typedef std::multimap <int, int> multimap_type;
typedef std::multimap <int, int>::iterator multi_it;
typedef std::pair <std::multimap <int, int>::iterator, std::multimap <int, int>::iterator> multi_pair_it_type;

int main() {
    setlocale(LC_ALL, ".1251");


//    Practic.Problem 1

    int n = 0;
    std::cout << "¬ведите число: ";
    std::cin >> n;
    std::set <int> nums {1};
    std::set <int>::iterator it, end_it;
    for(int i = 2; i <= n; ++i){
        nums.insert(i);
    }
    for(int i = 2; i <= n; ++i){
        for(it = nums.begin(); it != nums.end(); it++){
            if((*it) % i == 0 && (*it) != i){
                nums.erase(*it);
            }
            if(it == (--nums.end())){
                break;
            }
        }
    }
    for(auto a : nums){
        std::cout << a << " ";
    }
    std::cout << "\n";



//    Practic.Problem 2

    std::ifstream fin("set.txt");
    if(!fin.is_open()){
        std::cerr << "File set.txt is not opened!\n";
        exit(1);
    }
    std::map <std::string, int> words;
    std::map <std::string, int>::iterator iter;
    std::string s = "", s_copy = "", str = "", tmp = "";
    char del;
    std::cout << "¬ведите символ-разделитель: ";
    std::cin >> del;
    while(std::getline(fin, str)){
        for(auto c : str) {
            if(c == del) {
                std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
                if (words.find(tmp) == words.end()) {
                    words.emplace(tmp, 1);
                } else {
                    iter = words.find(tmp);
                    iter->second++;
                }
                tmp.clear();
            }
            else{
                tmp.push_back(c);
            }
        }
    }

    for(auto m : words){
        std::cout << m.first << " " << m.second << "\n";
    }
    fin.close();




    return 0;
}
