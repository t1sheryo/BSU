#include <iostream>
#include "iterator.h"
#include "user_class.h"

template<class T1, class T2>
int mismatch(const T1& l, const T1& r){
    T2* itl = l.createIterator();
    T2* itr = r.createIterator();
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
        Set<int> s1;
        for (size_t i = 1; i < 5; ++i) {
            s1 >> i;
        }

        Set<int> s2, s3(s1), s4(s1), s5(s1);
        s2 >> 119;
        s3 >> 10329103;
        s4 >> -19301;

        std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3 << "\ns4: " << s4 << "\ns5: " << s5 << "\n";

        std::cout << "s1 == s2 is " << mismatch<Set<int>, SetIterator<int>>(s1, s2) << '\n';
        std::cout << "s1 == s3 is " << mismatch<Set<int>, SetIterator<int>>(s1, s3) << '\n';
        std::cout << "s1 == s4 is " << mismatch<Set<int>, SetIterator<int>>(s1, s4) << '\n';
        std::cout << "s1 == s5 is " << mismatch<Set<int>, SetIterator<int>>(s1, s5) << '\n';

        Set s6 = s2 / s1;
        std::cout << "s6: " << s6;

        s4 |= s3;
        std::cout << "s4: " << s4;

        std::cout << (s6 &= s4);
        s5 &= s4;
        std::cout << s5;




        std::cout << "\n\n\n\n\n";
        Set<myType> t1;
        for (size_t i = 1; i < 5; ++i) {
            std::string s(i, 's');
            myType my(s, i + 160 * 2);
            t1 >> my;
        }

        Set<myType> t2, t3(t1), t4(t1), t5(t1);
        t2 >> myType("artem", 100);
        t3 >> myType("sava", 201);
        t4 >> myType("fedya", 1234930);

        std::cout << "t1: " << t1 << "\nt2: " << t2 << "\nt3: " << t3 << "\nt4: " << t4 << "\nt5: " << t5 << "\n";

        std::cout << "t1 == t2 is " << mismatch<Set<myType>, SetIterator<myType>>(t1, t2) << '\n';
        std::cout << "t1 == t3 is " << mismatch<Set<myType>, SetIterator<myType>>(t1, t3) << '\n';
        std::cout << "t1 == t4 is " << mismatch<Set<myType>, SetIterator<myType>>(t1, t4) << '\n';
        std::cout << "t1 == t5 is " << mismatch<Set<myType>, SetIterator<myType>>(t1, t5) << '\n';

        Set t6 = t2 / t1;
        std::cout << "t6: " << t6;

        t4 |= t3;
        std::cout << "t4: " << t4;

        std::cout << (t6 &= t4);
        t5 &= t4;
        std::cout << t5;

    }catch (const char* ex){
        std::cout << ex;
    }

    return 0;
}
