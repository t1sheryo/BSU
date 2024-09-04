#ifndef KR1_MUSICALCOMPOSITION_H
#define KR1_MUSICALCOMPOSITION_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

enum Genre {song = 0, opera, symphony, dance};

inline std::vector<std::string> convertGenre {"song", "opera", "symphony", "dance"};

class MusicalComposition{
private:
    inline static int generalID = 0;
    const int ID;
    std::string nameComp;
    const Genre genre;
    int year;

public:
    MusicalComposition() = delete;
    MusicalComposition(std::string name, Genre _genre, int _year);
    MusicalComposition(const MusicalComposition& a);

    MusicalComposition(MusicalComposition&& a) noexcept;
    MusicalComposition& operator=(MusicalComposition&& a) noexcept;

    MusicalComposition& operator=(const MusicalComposition& a);
    bool operator==(const MusicalComposition& a);
    friend std::ostream& operator<<(std::ostream& out, MusicalComposition& a);

    virtual void Print() const;

    [[nodiscard]] int getID() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] Genre getGenre() const;
    [[nodiscard]] int getYear() const;

    void setName(std::string a);
    void setYear(int a);

    virtual ~MusicalComposition() = default;
};

#endif //KR1_MUSICALCOMPOSITION_H
