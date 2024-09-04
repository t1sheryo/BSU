#include "Library.h"


int main() {

    setlocale(LC_ALL, ".1251");

    Library lib;

    std::ifstream fin("Books.txt");
    if(!fin.is_open()){
        std::cerr << "Error! File is not opened!\n";
        exit(1);
    }
    std::string s, tmp;
    char del;
    std::cout << "Введите символ-разделитель: ";
    std::cin >> del;
    while(std::getline(fin, s)){
        s += del;
        int cnt = 0;
        int cur_udk = 0, cur_data = 0;
        std::string cur_title;
        std::vector <std::string> cut_lst;
        for(size_t i = 0; i < s.length(); ++i){
            if(s[i] == del){
                switch (cnt) {
                    case 0:
                        cur_udk = stoi(tmp);
                        cnt++;
                        break;
                    case 1:
                        cur_title = tmp;
                        cnt++;
                        break;
                    case 2:
                        cur_data = stoi(tmp);
                        cnt++;
                        break;
                    case 3:
                        cut_lst.push_back(tmp);
                        break;
                }
                tmp.clear();
            }
            else {
                tmp.push_back(s[i]);
            }
        }
        lib.AddBook(cur_udk, cur_title, cur_data, cut_lst);
    }
    fin.close();

    lib.Print();

    std::vector <std::string> Au1 = {"Cheberuk Timofey Sergeevich", "Petrov Vasiliy Ivanovich"};
    std::vector <std::string> Au2 = {"Yay Chung Main", "Pin Ling Yang", "Dung Mung Chung"};
//    lib.AddBook(101, "Princess", 1920, Au1);
//    lib.AddBook(23, "China", 1011, Au2);
//    lib.AddBook(10, "Family",2000, Au1);
//    lib.SearchByTitle("China");
//    std::cout << "\n\n\n";
//    lib.SearchByAuthor("Cheberuk Timofey Sergeevich");
//    lib.DeleteBook("Princes");
//    std::cout << "\n\n\n";
//    lib.SearchByTitle("China");
//    std::cout << "\n\n\n";
//    lib.SearchByAuthor("Cheberuk Timofey Sergeevich");
//    lib.SearchByTitle("Princess");
//    lib.DeleteBook("Princess");
//    lib.SearchByTitle("Princess");
//    lib.DeleteBook("Family");
//    lib.SearchByAuthor("Cheberuk Timofey Sergeevich");
//    lib.SearchByTitle("Princess");
//    lib.SearchByTitle("Family");
//    lib.SearchByTitle("China");
//    lib.DeleteAuthor("China", "Pin Ling Yang");
//    lib.AddAuthor("China", "Ivanov Alex Albertovich");
//    lib.DeleteAuthor("China", "Pin Ling Yang");
//    lib.SearchByTitle("China");
//    std::cout << "\n\n\n";
//    lib.SearchByAuthor("Ivanov Alex Albertovich");

    std::cout << "\n\n\n";

    return 0;
}