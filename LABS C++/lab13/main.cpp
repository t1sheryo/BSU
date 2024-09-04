
//    Theory

//    1)Класс pair используется для инициализации элементов контейнеров map и set, передается методу insert как параметр


//2) Пары можно создавать:
/*std::pair<int, int> p1;
auto p2 = std::make_pair(1, 2);*/

/* //3) Дайте характеристику параметрам контейнера map:
 1-ый параметр - это тип ключа;
 2-ой параметр - это неключевого значения;
 3-ий параметр сортировка ключей(по возрастанию, по убыванию);*/

/*//4)Доступ к элементам map:
1) С помощью ключа;
2) С помощью итератора*/

//5) Какие итераторы можно использовать с map?
//    можно использовать итераторы для ассоциативных контейнеров
/*map_type map1;
it_type map1_iterator1;*/

//6) Методы поиска в map:
/*map_type map1;
pair_it_type i1, i4;
map1.insert({1, 10});
map1.insert({2, 5});
map1.insert({3, 30});
std::cout << "map.find: " <<(map1.find(2))->second << "\n";
i1 = map1.equal_range(2);
std::cout << "map.equal_range: " <<i1.first->first << " " << i1.first->second << "   " << i1.second->first << " " << i1.second->second<< "\n";
it_type i2, i3;
i2 = map1.upper_bound(1);
std::cout << "map.upper_bound: " << i2->first << " " << i2->second << "\n";
i3 = map1.lower_bound(3);
std::cout << "map.lower_bound: " <<  i3->first << " " << i3->second << "\n";
std::cout << "map.count: " << map1.count(1);*/

//7)  Что произойдет, если добавляется в map элемент с существующим ключом?
//    Если ключ key уже существует в контейнере, то data[key] = value и функция insert_or_assign его перезапишут, а insert — нет
/*map_type map1;
pair_it_type i1, i4;
map1.insert({1, 10});
map1.insert({2, 5});
map1.insert({3, 30});
map1.insert_or_assign(1, 14);
std::cout << map1[1];*/

//8) Вставка элементов в map.
/*map_type map2;
map2.insert({10, 20});
map2.emplace(12, 1490);*/

//   9)Удаление элементов из map
/*map_type map2;
map2.insert({10, 20});
map2.emplace(12, 1490);
map2.erase(12);
map2.clear();
for(auto a : map2){
    std::cout << a.second << " ";
}*/

/*//10)Использование методов lower_bound и upper_bound
смотреть пункт 6*/

/*//11) Использование метода equal_range
смотреть пункт 6*/

/*  //12)Дайте характеристику параметрам контейнера multimap:
  допускает хранение нескольких элементов с одинаковыми
  ключами, поэтому в этом классе операция доступа по индексу запрещена, и
  вместо нее надо пользоваться итераторами.*/


//13)Методы поиска в multimap
//    multimap_type mp1;
//    multi_it iter1;
//    mp1.insert({10, 0});
//    mp1.emplace(12, -1);
//    mp1.insert({10, 20});
//    mp1.emplace(12, 1220);
//    for(auto a : mp1){
//        std::cout << a.second << " ";
//    }
//    iter1 = mp1.find(12);
//    std::cout << "\n" << iter1->second;

//    14) Такой же как 7-ой вопрос

//15)Вставка элементов в multimap(ключи совпадают \ не совпадают):
//    Если ключи одинаковы, то вставляется в зависимости от значения.
//    Если ключи разные, то вставка после элемента с таким же значением ключа.

//    mp1.insert({10, 191});
//    mp1.emplace(12, 120);
//    for(auto a : mp1){
//        std::cout << a.second << " ";
//    }

//16)Удаление элементов из multimap(ключи совпадают \ не совпадают):
//    multimap_type map;
//    map.emplace(12, 1220);
//    map.emplace(12, 120);
//    map.emplace(12, 199);
//    map.emplace(10, 1000);
//    for(auto a : map){
//        std::cout << a.second << " ";
//    }
//    map.erase(12);            //удаляет все элементы с таким значением ключа
//    std::cout << "\n";
//    for(auto a : map){
//        std::cout << a.second << " ";
//    }
//    map.clear();                    //очищает полностью контейнер
//    std::cout << "\nПусто!";


//    17) Использование методов lower_bound и upper_bound
//        lower_bound - Возвращает итератор на элемент, ключ которого не меньше заданного, или end()
//        upper_bound - Возвращает итератор на элемент, ключ которого больше заданного, или end()
//    18)Использование метода equal_range
//        equal_range - Возвращает пару (lower_bound, upper_bound) для заданного ключа (т. е. интервал, включающий все элементы с заданным ключом)

//    multimap_type map1;
//    multi_pair_it_type i1, i4;
//    map1.insert({1, 10});
//    map1.insert({2, 5});
//    map1.insert({3, 1});
//    map1.insert({3, -2390});
//    map1.insert({10, 12});
//    for(auto a : map1){
//        std::cout << a.second << " ";
//    }
//    std::cout << "\n";
//    std::cout << "map.find: " <<(map1.find(2))->second << "\n";
//    i1 = map1.equal_range(3);
//    std::cout << "map.equal_range: " <<i1.first->first << " " << i1.first->second << "   " << i1.second->first << " " << i1.second->second<< "\n";
//    it_type i2, i3;
//    i2 = map1.upper_bound(1);
//    std::cout << "map.upper_bound: " << i2->first << " " << i2->second << "\n";
//    i3 = map1.lower_bound(3);
//    std::cout << "map.lower_bound: " <<  i3->first << " " << i3->second << "\n";
//    std::cout << "map.count: " << map1.count(3);