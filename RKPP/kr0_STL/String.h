#ifndef KR0_STL_STRING_H
#define KR0_STL_STRING_H

#include <string>
#include <algorithm>

class String{
private:
    std::string str;
public:
    explicit String(const std::string& s) : str(s) {}
    String() : str("") {}
    bool operator>(const String& other) const{
        std::string ls = str;
        std::transform(ls.begin(), ls.end(), ls.begin(), tolower);
        std::string rs = other.str;
        std::transform(rs.begin(), rs.end(), rs.begin(), tolower);
        return ls > rs;
    }
    bool operator<(const String& other) const{
        std::string ls = str;
        std::transform(ls.begin(), ls.end(), ls.begin(), tolower);
        std::string rs = other.str;
        std::transform(rs.begin(), rs.end(), rs.begin(), tolower);
        return ls < rs;
    }
    bool operator==(const String& other) const{
        std::string ls = str;
        std::transform(ls.begin(), ls.end(), ls.begin(), tolower);
        std::string rs = other.str;
        std::transform(rs.begin(), rs.end(), rs.begin(), tolower);
        return ls == rs;
    }
    bool operator!=(const String& other) const{
        std::string ls = str;
        std::transform(ls.begin(), ls.end(), ls.begin(), tolower);
        std::string rs = other.str;
        std::transform(rs.begin(), rs.end(), rs.begin(), tolower);
        return ls != rs;
    }
    friend std::ostream& operator<<(std::ostream& out, const String& other){
        out << other.str;
        return out;
    }
};

#endif //KR0_STL_STRING_H
