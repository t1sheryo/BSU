#include <iostream>
#include "iterator.h"

int mismatch(const Set& l, const Set& r){
    SetIterator* itl = l.createIterator();
    SetIterator* itr = r.createIterator();
    for ( itl->first(), itr->first();
          !itl->isDone();
          itl->next(), itr->next() ) {
        if (itl->currentItem() != itr->currentItem())
            return itl->getIterIndex();
    }
    if(itl->isDone() != itr->isDone()){
        return itl->getIterIndex();
    }
    delete itl;
    delete itr;
    return -1;
}

int main() {

    try {
        Set s1;
        for (size_t i = 1; i < 5; ++i) {
            s1 >> i;
        }

        Set s2(s1), s3(s1), s4(s1), s5(s1);
        s2 >> 119;
        s3 >> 10329103;
        s4 >> -19301;

        std::cout << s1 << "\n";

        std::cout << "1 == 2 is " << mismatch(s1, s2) << '\n';
        std::cout << "1 == 3 is " << mismatch(s1, s3) << '\n';
        std::cout << "1 == 4 is " << mismatch(s1, s4) << '\n';
        std::cout << "1 == 5 is " << mismatch(s1, s5) << '\n';

        Set s6 = s2 / s1;
        std::cout << s6;

        s4 |= s3;
        std::cout << s4;

        std::cout << (s6 &= s4);

        s5 &= s4;
        std::cout << s5;

    }catch (const char* ex){
        std::cout << ex;
    }

    return 0;
}
