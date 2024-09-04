#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <vector>


class Author{
private:
    std::string name;
    std::string surname;
    std::string dad_name;
    std::string full_name;
public:

    explicit Author(const std::string& full){
        std::string tmp;
        int cnt = 0;
        for(size_t c = 0; c < full.length(); ++c){
            if( full[c] == ' ' || c == (full.length() - 1) ){
                if(c == (full.length() - 1)){
                    tmp.push_back(full[c]);
                }
                switch (cnt) {
                    case 0:
                        surname = tmp;
                        break;
                    case 1:
                        name = tmp;
                        break;
                    case 2:
                        dad_name = tmp;
                        break;
                }
                cnt++;
                tmp.clear();
            }
            else{
                tmp.push_back(full[c]);
            }
        }
        full_name = surname + " " + name + " " + dad_name;
    }

    Author(const std::string& name, const std::string& surname, const std::string& dad_name){
        full_name = surname + " " + name + " " + dad_name;
    }

    friend bool operator< (const Author& a, const Author& b){
        return a.surname < b.surname;
    }

    [[nodiscard]] std::string GetFullName() const {
        return full_name;
    }

    friend std::ostream& operator<< (std::ostream& out, Author& author){
        out << author.full_name;
        return out;
    }

    friend bool operator== (const Author& a, const Author& b){
        return a.full_name == b.full_name;
    }
};



class Authors_List{
private:
    std::set <Author> aus;
public:

    Authors_List() = default;

    Authors_List(const std::vector <std::string>& cheta){
        for(auto a : cheta){
            Author aut(a);
            aus.emplace(aut);
        }
    }

    auto GetSetAuthorsPointer(){
        return &aus;
    }

    friend std::ostream& operator<< (std::ostream& out, Authors_List& l){
        for(auto b : l.aus){
            out << "\n" << b;
        }
        return out;
    }

    friend bool operator== (Authors_List& a, Authors_List& b){
        if(a.aus == b.aus){
            return true;
        }
        else{
            return false;
        }
    }

    [[nodiscard]] std::set <Author>::iterator BeginIter () const{
        return aus.begin();
    }

    [[nodiscard]] std::set <Author>::iterator EndIter () const{
        return aus.end();
    }

    [[nodiscard]] std::pair <std::set <Author>::iterator, std::set <Author>::iterator> GetList() const{
        return make_pair(aus.begin(), aus.end());
    }

};



class Book : public std::basic_string<char> {
private:
    int udk;
    std::string title;
    int date;
    Authors_List lst;
public:

    Book(){
        udk = -1;
        title = "NoTitle";
        date = -1;
    }

    Book(int& udk, std::string& title, int& date, Authors_List& lst){
        this->udk = udk;
        this->title = title;
        this->date = date;
        this->lst = lst;
    }

    Book(const Book &b){
        this->udk = b.udk;
        this->title = b.title;
        this->date = b.date;
        this->lst = b.lst;
    }

    [[nodiscard]] std::string GetTitle() const{
        return this->title;
    }

    [[nodiscard]] int GetUdk() const{
        return this->udk;
    }

    [[nodiscard]] int GetDate() const{
        return this->date;
    }

    [[nodiscard]] auto GetLst() const{
        return this->lst;
    }

    void Print(){
        std::cout << "\nNumber UDK: " << udk << "\nBook Name: " << title << "\nYear of release: " << date << "\nList of authors: " << lst << "\n";
    }

    friend bool operator< (const Book& a, const Book& b){
        return a.title < b.title;
    }

    bool SearchByAuthor(const std::string& str){
        bool flag = false;
        for(auto it = lst.BeginIter(); it != lst.EndIter(); ++it){
            if((*it).GetFullName() == str) {
                this->Print();
                flag = true;
            }
        }
        return flag;
    }

    auto GetAuthorsListPointer(){
        return lst.GetSetAuthorsPointer();
    }

};



class Library{
private:
    std::map <std::string, Book> books;
public:

    void AddBook(int udk, std::string title, int date, Authors_List lst){
        Book b(udk, title,date ,lst);
        books.emplace(title, b);

    }

    void DeleteBook(std::string title){
        bool flag = false;
        for(auto it = books.begin(); it != books.end(); ++it){
            if(it->first == title){
                books.erase(it);
                flag = true;
                break;
            }
        }
        if(!flag){
            std::cerr << "\nError! No book named \"" << title << "\" with such characteristics in library to delete!\n";
        }
    }

    bool SearchByTitle(const std::string& title){
        bool flag = false;
        for(auto a : books){
            if(a.second.GetTitle() == title){
                a.second.Print();
                flag = true;
            }
        }
        if(!flag){
            std::cerr << "\nNo book \"" << title << "\" is found!\n";
        }
        return flag;
    }

    bool SearchByAuthor(const std::string& str){
        bool flag = false;
        for(auto a : books){
            if (a.second.SearchByAuthor(str))
                flag = true;
        }
        if(!flag){
            std::cerr << "\nNo book by " << str << " is found!\n";
        }
        return flag;
    }

    bool AddAuthor(const std::string& title, const std::string& author_name){
        bool flag = false;
        for(auto & book : books) {
            if (book.first == title) {
                flag = book.second.GetAuthorsListPointer()->emplace(Author(author_name)).second;
            }
        }
        return flag;
    }

    bool DeleteAuthor(const std::string& title,const std::string& author_name){
        bool flag = false;
        Author a_name(author_name);
        for(auto & book : books){
            if(book.first == title){
                book.second.GetAuthorsListPointer()->erase(Author(author_name));
                flag = true;
            }
        }
        return flag;
    }

    void Print(){
        for(auto a : books){
            a.second.Print();
        }
    }
};