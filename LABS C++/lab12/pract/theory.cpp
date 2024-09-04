#include <algorithm>
#include <cstdio>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>


int main() {

    setlocale(LC_ALL, ".1251");

    //    Theory

    //    // 1. Какие виды векторов позволяют создать конструкторы?
    //            std::vector<int> v1;                // пустой вектор
    //            std::vector<int> v2(v1);            // вектор v2 - копия вектора v1
    //            std::vector<int> v3 = v1;           // вектор v3 - копия вектора v1
    //            std::vector<int> v4(5);             // вектор v4 состоит из 5 чисел, каждое число равно 0
    //            std::vector<int> v5{5};             // вектор состоит из одного числа, которое равно 5
    //            std::vector<int> v6(5, 2);          // вектор v6 состоит из 5 чисел, каждое число равно 2
    //            std::vector<int> v7{5, 2};          // вектор состоит из двух чисел 5 и 2
    //            std::vector<int> v8{1, 2, 4, 5};    // вектор v8 состоит из чисел 1, 2, 4, 5
    //            std::vector<int> v9 = {1, 2, 3, 5}; // вектор v9 состоит из чисел 1, 2, 3, 5

    //        // 2. Как задать размер контейнера?   размер задаётся в конструкторе
    //            std::vector<int> v(5);             // вектор v состоит из 5 чисел, каждое число равно 0
    //                                  // capacity (вместимость) >= size(размер)

    //        // 3. Как определить потенциальный размер контейнера?
    //            std::vector<int> v(5);
    //            size_t vector_capacity = v.capacity();
    //        // 4. Как получить доступ к элементу контейнера?
    //            std::vector<int> v(5);
    //            size_t a = v.back();
    //            a = v.front();
    //            a = v.at(2);
    //            a = v[0];
    //        // 5. Как присвоить значение элементу контейнера?
    //            std::vector<int> v(5);
    //            std::vector<int> v2(5, 2);
    //            v.at(2) = 4;
    //            v[0] = 1;
    //            v.assign(v2.begin(), v2.begin() + 2);
    //        // 6. Опишите функциональность методов begin и end
    //            std::vector<int> v(5);
    //            std::vector<int>::iterator it_begin = v.begin();
    //            std::vector<int>::iterator it_end = v.end();
    //            *(v.begin()) = 2;
    //        // 7. Опишите использование метода back и front
    //            std::vector<int> v(5, 2);
    //            int a = v.front();
    //            std::cout << a << "\n";
    //            a = v.back();
    //            std::cout << a;
    //        // 8. Опишите использование метода insert
    //            std::vector<int> v(5);
    //            v.insert(v.begin() + 1, 10);
    //        // 9. Как и куда можно вставить? новые элементы в контейнер
    //            std::vector<int> v(5);
    //            v.insert(v.begin() + 1, 10);
    //            v.push_back(34);
    //        // 10. Опишите функциональность методов capacity и max_size
    //            std::vector<int> v(100);
    //            size_t cap = v.capacity();
    //            size_t max_size = v.max_size();
    //            /*
    // * size: 100
    // * capacity: 128
    // * max_size: 1073741823
    // */
    //        // 11. Зачем нужны методы reserve и resize?
    //            std::vector<int> v(5);
    //            v.resize(10);
    //            /* Если n = 10 меньше текущего размера контейнера,
    // * содержимое уменьшается до первых n элементов,
    // * удаляя все последующие (и уничтожая их).
    //            v.resize(5);
    //            v.resize(8, 100);
    //            for(auto a : v){
    //                std::cout << a << "  ";
    //            }
    //            /* Если n больше текущего размера контейнера,
    // * содержимое расширяется, вставляя в конец столько
    // * элементов, сколько необходимо для достижения размера n
    // */
    //            v.resize(12);
    //            /* Если n также больше, чем текущий объем контейнера,
    // * происходит автоматическое перераспределение выделенного
    // * пространства для хранения.
    // */
    //        // 12. Как вставить / удалить элемент в начало контейнера?
    //            std::vector<int> v(100);
    //            v.insert(v.begin(), 10);
    //            v.erase(v.begin(), v.begin() + 1);
    //        // 13. Как вставить / удалить элемент в конец контейнера.
    //            std::vector<int> v(100);
    //            v.push_back(10);
    //            v.pop_back();

    //        // DEQUE
    //        // 14. Какие виды двусторонних очередей позволяют создать конструкторы?
    //            std::deque<int> first;                                // empty deque of ints
    //            std::deque<int> second(4, 100);                       // four ints with value 100
    //            std::deque<int> third(second.begin(), second.end());  // iterating through second
    //            std::deque<int> fourth(third);                        // a copy of third
    //        // 15. Как получить доступ к элементу контейнера?
    //            std::deque<int> d(4, 100);                       // four ints with value 100
    //            int a = d[0];
    //            a = d.at(1);
    //            a = d.front();
    //            a = d.back();
    //        // 16. Как присвоить значение элементу контейнера?
    //            std::deque<int> d(4, 100);                       // four ints with value 100
    //            d[0] = 1;
    //            d.at(1) = 2;
    //            std::deque<int> d2(5, 100);                       // four ints with value 100
    //            d.assign(d2.begin(), d2.end() - 1);
    //        // 17. Опишите функциональность методов front и back
    //            std::deque<int> v(4, 100);
    //            int a = v.front();
    //            a = v.back();
    //        // 18. Как вставить / удалить элемент в начало контейнера?
    //            std::deque<int> v(4, 100);
    //            v.push_front(10);
    //            v.pop_front();
    //        // 19. Как вставить / удалить элемент в конец контейнера.
    //            std::deque<int> v(4, 100);
    //            v.push_back(10);
    //            v.pop_back();

    //        // LIST
    //        // 20. Опишите использование метода merge.
    //            std::list<int> l1{1, 3, 5};
    //            std::list<int> l2{2, 4, 6};
    //            /* Объединяет иx в список, перенося все его элементы в
    // * соответствующие упорядоченные позиции в контейнер
    // * (оба контейнера должны быть уже упорядочены).
    // * * */
    //            l1.merge(l2);
    //            for(auto a : l1){
    //                std::cout << a << "  ";
    //            }
    //        // 21. Опишите использование метода remove_if.
    //            std::list<int> l1{1, 3, 5};
    //            l1.remove_if([](int a) { return a % 2; });
    //        // 22. Опишите использование метода splice.
    //            std::list<int> list1{1, 2, 3, 4, 5};
    //            std::list<int> list2{10, 20, 30, 40, 50};
    //
    //            auto it = list1.begin();
    //            std::advance(it, 2);
    //
    //            list1.splice(it, list2);
    /* l1 = {1, 2, 10, 20, 30, 40, 50, 3, 4, 5}
// * l2 = {}
// */
    //            list2.splice(list2.begin(), list1, it, list1.end());
    //            /*
    // * list1: 1 2 10 20 30 40 50
    // * list2: 3 4 5
    // */
    //        // 23. Опишите использование метода unique.
    //            struct is_near {
    //                bool operator()(double first, double second) { return (fabs(first - second) < 5.0); }
    //            };
    //
    //            double mydoubles[] = {12.15, 2.72, 73.0, 12.77, 3.14,
    //                                  12.77, 73.35, 72.25, 15.3, 72.25};
    //            std::list<double> mylist(mydoubles, mydoubles + 10);
    //
    //            mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
    //                          // 15.3,  72.25, 72.25, 73.0,  73.35
    //
    //            mylist.unique();           //  2.72,  3.14, 12.15, 12.77
    //                            // 15.3,  72.25, 73.0,  73.35
    //
    //            mylist.unique([](double first, double second) { return (int(first) == int(second)); });  //  2.72,  3.14, 12.15
    //                                                                                                   // 15.3,  72.25, 73.0
    //
    //            mylist.unique(is_near());           //  2.72, 12.15, 72.25

    //        // ОБЩИЕ ВОПРОСЫ
    //        // 24. У каких контейнеров допустим произвольный доступ к элементам?
    //            // array
    //            // vector
    //            // deque
    //            // string
    //        // 25. Для каких контейнеров сохраняются значения указателей, итераторов после вставки/удаления?
    //              vector
    //              list
    //              forward_list
    //        // 26. Какие последовательные контейнеры поддерживают упорядоченность элементов автоматически?
    //              -----
    //        // 27. Какие средства можно использовать для сортировки элементов контейнера?
    //            std::vector<int> v{4, 7, 4, 0};
    //            std::sort(v.begin(), v.end());
    //            std::stable_sort(v.begin(), v.end());    // сохраняет изначальный порядок у эквивалентных элементов
    //        // 28. Когда, в каких случаях нужно отдать предпочтение выбору одного из контейнеров?
    //            // LIFO / FIFO / deque / array
    //        // 29. Какие средства можно использовать и что необходимо реализовать для сравнения элементов контейнеров, если они содержат объекты пользовательских классов?
    //            // operator==
    //            // operator!=

}