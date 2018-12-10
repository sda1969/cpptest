/*
 * containerstest.cpp
 *
 *  Created on: 31 марта 2017 г.
 *      Author: dmitry
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <array>
#include <map>
#include <set>
#include <tuple>

#include <iterator>
#include <functional>
#include <string.h>

//vector degueue list
namespace containerstest {

template <class C> void print_all(const C& container){
    std::for_each(container.begin(), container.end(), [](const typename C::value_type& x){std::cout << x << ' ';} );
    std::cout << '\n';
}

static void vectors(){

    //empty container constructor (default constructor)
    std::vector<int> first;                                // empty vector of ints
    //fill constructor
    std::vector<int> second (4,100);                       // four ints with value 100
    //range constructor
    std::vector<int> third (second.begin(),second.end());  // iterating through second
    //copy constructor
    std::vector<int> fourth (third);                       // a copy of third

    // the iterator constructor (range constructor) can also be used to construct from arrays:
    typedef std::vector<int>::iterator VI;
    int myints[] = {16,2,77,29};
    VI begin = static_cast<VI> (myints);
    VI end = static_cast<VI> (&myints[3] + 1);
    //std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
    std::vector<int> fifth (begin, end);
    print_all<std::vector<int>> (fifth);

    //initializer list constructor
    std::vector<int> sixth({1,2,3,4});

    std::cout << "size :" << sixth.size() << std::endl;
    std::cout << "capacity :" << sixth.capacity() << std::endl;
    std::cout << "max_size :" << sixth.max_size() << std::endl;
    sixth.reserve(20);
    std::cout << "capacity after reserve:" << sixth.capacity() << std::endl;
    std::cout << "size after reserve::" << sixth.size() << std::endl;
    sixth.resize(30, 5);
    std::cout << "capacity after resize:" << sixth.capacity() << std::endl;
    std::cout << "size after resize::" << sixth.size() << std::endl;
    print_all<std::vector<int>> (sixth);

    sixth.assign(fifth.begin()+1, fifth.begin()+3);
    sixth.push_back(86);
    sixth.push_back(12);
    sixth.push_back(27);
    sixth.erase(sixth.begin() + 3);
    sixth.pop_back();
    //insert
    sixth.insert(sixth.end(),24);
    sixth.insert(sixth.end(),3, 45);
    VI pos(&sixth[3]); //конструкторы итератора
    sixth.insert(pos, fifth.begin(), fifth.begin() + 2);

    pos =sixth.begin() + 7;
    pos = static_cast<VI>(&sixth[7]);

    sixth.insert(pos, {1,2,3,4,5});
    print_all<std::vector<int>> (sixth);
}

static void dequeues(){
    //конструкторы такие же как и в векторе
    std::deque<int> dq1 = {1,2,3,4,5} ;
    print_all<std::deque<int>> (dq1);

    //нет capacity и reserve, а size resize assign insert erase , такие же как и в vector

    dq1.push_back(6);
    dq1.push_front(0);
    print_all<std::deque<int>> (dq1);

    for(std::deque<int>::size_type i = 0; i < dq1.size(); ++i){
        dq1.push_back(dq1.front());
        dq1.pop_front();
    }
    print_all<std::deque<int>> (dq1);
}

static void lists(){
//конструкторы такие же как и для vector deque

    std::list<int> ls1({42,13,15,18,21,24,23,62});
    //нет capacity и reserve, а size resize assign insert erase , такие же как и в vector

    //уникально для листа
    ls1.remove(18);
    ls1.remove_if([](const int& x){return x > 40;});
    std::cout << "size :" << ls1.size() << std::endl;
    print_all<std::list<int>> (ls1);
    ls1.reverse();
    print_all<std::list<int>> (ls1);
    ls1.sort(); //используя оператор <
    print_all<std::list<int>> (ls1);
    ls1.sort([](const int& x, const int& y){return x > y;});
    print_all<std::list<int>> (ls1);

    //unique
    ls1.insert(ls1.end(), 3, 50);
    ls1.unique([](const int& x, const int& y){return x == y;}); //то же самое что и  ls1.unique([]
    print_all<std::list<int>> (ls1);

    //splice
    std::list<int> ls2 {1,2,3,4,5};
    std::cout << std::endl;
    ls1.splice(++ls1.begin(), ls2); //весь список
    auto it = ls1.begin();
    std::advance(it, 3);
    ls2.splice(ls2.begin(), ls1, it); //конкретный один элемент
    ls2.splice(ls2.end(), ls1, ++ls1.begin(), --ls1.end()); //диапазон

    print_all<std::list<int>> (ls1);
    print_all<std::list<int>> (ls2);
    //swap обмен содержимым двух листов
}

static void forward_lists(){
    std::forward_list<int> fls1 {1,2,3,4,5};
    std::forward_list<int> fls2 {6,7,8,9,10};

    //xxx_after
    fls1.insert_after(fls1.before_begin(), {-1,0});
    fls1.erase_after(fls1.begin());
    fls1.erase_after(fls1.begin(),fls1.end());

    fls1.splice_after(fls1.before_begin(), fls2);

    print_all<std::forward_list<int>> (fls1);
    print_all<std::forward_list<int>> (fls2);
}

//adaptor
static void stacks(){
     std::deque<int> mydeque (3,100);          // deque with 3 elements
     std::vector<int> myvector (2,200);        // vector with 2 elements

     std::stack<int> first;                    // empty stack
     std::stack<int> second (mydeque);         // stack initialized to copy of deque

     std::stack<int,std::vector<int> > third;  // empty stack using vector
     std::stack<int,std::vector<int> > fourth (std::move(myvector));

     std::cout << "size of first: " << first.size() << '\n';
     std::cout << "size of second: " << second.size() << '\n';
     std::cout << "size of third: " << third.size() << '\n';
     std::cout << "size of fourth: " << fourth.size() << '\n';

     second.push(34);
     second.push(43);

     while (!second.empty())
     {
        std::cout << ' ' << second.top();
        second.pop();
     }
     std::cout << '\n';
}

//adaptor
static void queues(){
    std::deque<int> mydeque {1,2,3,4,5};
    std::list<int> mylist {6,7,8,9,10};

    std::queue<int> myqd {mydeque};
    std::queue<int, std::list<int> > myql{std::move(mylist)};

    while (!myqd.empty())
    {
       std::cout << ' ' << myqd.front();
       myqd.pop();
    }
    std::cout << '\n';


    while (!myql.empty())
    {
       std::cout << ' ' << myql.front();
       myql.pop();
    }
    std::cout << '\n';


}

static void arrays(){
// default initialization (local = automatic storage):
 std::array<int,3> first;              // uninitialized:    {?,?,?}
 int myints[3] = {1,2,3};
 //std::array<int,3> first {myints[3]}; //нельзя- нет конструктора
 memcpy(first.data(), myints, sizeof(first));

 // initializer-list initializations:
 std::array<int,3> second;
 std::array<int,3> third = {1,2,3}; // нет инициализации списком проблемы с gcc 4.7.2 ?? 4.9 ok
 second.fill(4);
 print_all<std::array<int,3> >(second);
 //std::array<int,3> third;
 second = third;
 // copy initialization:
 std::array<int,3> fourth = third;     // copy:

 print_all<std::array<int,3> >(fourth);
 print_all<std::array<int,3> >(first);

}

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

static void maps(){
    std::map<char,int> first;
    typedef std::pair<std::map<char,int>::iterator,bool> ret_t;

    first['a']=10;
    first['b']=30;
    first['c']=50;
    first['d']=70;
    first['e']=90;

    std::map<char,int> second (first.begin(),first.end());

    std::map<char,int> third (second);

    std::map<char,int,classcomp> fourth {{'c',1},{'d',2},{'e',3}};                 // class as Compare


    std::function<bool(char,char)> fn_pt = fncomp;
    std::map<char,int, std::function<bool(char,char)>> fifth (fn_pt);
    for(auto x : first){std::cout << x.first << " " << x.second << std::endl;}
//    for (std::map<char,int>::iterator it=first.begin(); it!=first.end(); ++it)
//      std::cout << it->first << " => " << it->second << '\n';
    std::cout << third.size() << std::endl;
    std::cout << third.count('b') << std::endl;
    std::cout << third.count('f') << std::endl;
    third.erase(third.find('b')); //iterator
    third.erase('a');   //value
    third.erase(third.find('d'),  ++third.find('e') ); //range
    for(auto x : third){std::cout << x.first << " " << x.second << std::endl;}

    first.clear();
    first.insert({{'g',34},{'k',35}, {'l',36}});
    first['m'] = 37;
    first['g'] = 37;
    ret_t ret = first.insert({'g',31});
    if (!ret.second){
        std::cout << "element already exist!\n";
    }
    //hints
    first.insert(first.begin(),{'a',30}); //effective
    first.insert(first.begin(),{'b',31}); //ineffective
    first.insert(fourth.find('c'), ++fourth.find('d'));
    std::cout << first['z']; //чтение приводит к появлению пары!!
    first.at('m') = 78;
    for(auto x : first){std::cout << x.first << " " << x.second << std::endl;}

    std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> bounds;
    bounds = first.equal_range('k');  //по отдельности есть  lower_bound() upper_bound()
    std::cout << "lower bound points to: ";
    std::cout << bounds.first->first << " => " << bounds.first->second << '\n';
    std::cout << "upper bound points to: ";
    std::cout << bounds.second->first << " => " << bounds.second->second << '\n';

    std::cout << "\n\n Multimap\n"; //нет at, []
    std::multimap<char,int> mm1 (first.begin(), first.end());
    mm1.insert({'k',20});
    for(auto x : mm1){std::cout << x.first << " " << x.second << std::endl;}
    bounds = mm1.equal_range('k');  //по отдельности есть  lower_bound() upper_bound()
    std::cout << "lower bound points to: ";
    std::cout << bounds.first->first << " => " << bounds.first->second << '\n';
    std::cout << "upper bound points to: ";
    std::cout << bounds.second->first << " => " << bounds.second->second << '\n';

    for( auto it = bounds.first; it!= bounds.second; ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }
}

static void sets(){

    std::set<char> sc1 {'a','b','c'};
    std::multiset<char> sc2 {'a','a','c','c'};
    std::cout << sc1.count('a') << ' ' << sc2.count('a') << "\n";
    sc2.erase(sc2.find('c'));
    sc2.erase('c');
    sc2.insert(sc1.find('b'), sc1.end());
    sc2.insert({'d','e'});
    print_all<std::set<char> > (sc1);
    print_all<std::multiset<char> > (sc2);

}

static void tuples(){

  std::pair<int,char> mypr1 {12,'f'};
  std::tuple<int,char> mytpl1 (mypr1);

  std::tuple<int,char> foo (10,'x');
  auto bar = std::make_tuple ("test", 3.1, 14, 'y');

  std::get<2>(bar) = 100;                                    // access element

  int myint; char mychar;

  std::tie (myint, mychar) = foo;                            // unpack elements
  std::tie (std::ignore, std::ignore, myint, mychar) = bar;  // unpack (with ignore)

  mychar = std::get<3>(bar);

  std::get<0>(foo) = std::get<2>(bar);
  std::get<1>(foo) = mychar;

  std::cout << "foo contains: ";
  std::cout << std::get<0>(foo) << ' ';
  std::cout << std::get<1>(foo) << '\n';

//  Forward as tuple
//  Constructs a tuple object with rvalue references to the elements in args
//  suitable to be forwarded as argument to a function.

    std::tuple<float,std::string> mytuple (3.14,"pi");
    std::pair<int,char> mypair (10,'a');

    auto myauto = std::tuple_cat ( mytuple, std::tuple<int,char>(mypair) );

    std::cout << "myauto contains: " << '\n';
    std::cout << std::get<0>(myauto) << '\n';
    std::cout << std::get<1>(myauto) << '\n';
    std::cout << std::get<2>(myauto) << '\n';
    std::cout << std::get<3>(myauto) << '\n';
}

void containerstest_run(){
    //vectors();
    //dequeues();
    //lists();
    //forward_lists();
    //stacks();
    //queues();
    arrays();
    //maps();
    //sets();
   // tuples();
}

}
