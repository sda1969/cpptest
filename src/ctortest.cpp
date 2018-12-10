/*
 * ctortest.cpp
 *
 *  Created on: 31 окт. 2017 г.
 *      Author: user
 */

#include <iostream>
using namespace std;
namespace ctortest {
/*
Конструктор выполняет свою работу в следующем порядке.
    Вызывает конструкторы базовых классов и членов в порядке объявления.
    Если класс является производным от виртуальных базовых классов, конструктор инициализирует указатели виртуальных базовых классов объекта.
    Если класс имеет или наследует виртуальные функции, конструктор инициализирует указатели виртуальных функций объекта. Указатели виртуальных функций указывают на таблицу виртуальных функций класса, чтобы обеспечить правильную привязку вызовов виртуальных функций к коду.
    Выполняет весь код в теле функции.
*/
class BaseClass{
public:
    BaseClass(){
        print_it();
    }
    virtual ~BaseClass(){}

    virtual void print_it() {
        cout << "BaseClass print_it" << endl;
    }
};

class DerivedClass : public BaseClass {
public:
    DerivedClass() {
        print_it();
    }
    virtual void print_it(){
        cout << "Derived Class print_it" << endl;
    }
};

void ctortest_run() {

    DerivedClass dc;

}


}

