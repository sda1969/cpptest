//============================================================================
// Name        : cpptest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

using namespace std;

namespace ctest {

/* Задача: определить в какой части левой или правой оператора= использовался оператор[]
 *
 * Зачем нужно: в зависимости от того в какой части использовался оператор[]
 * реализуются либо функция чтения аппаратных регистров либо их запись
 *
 * Предлагаемое решение: оператор[] сохраняет свой аргумент в стеке глубиной 2
 * оператор= осуществляет запись в регистры
 * оператор приведения к типу int осуществляет чтение
 *
 * Пояснения:
 * для поддержи цепочек присваивания reg[1]=reg[2] добавлен другой прототип оператора=
 * стек аргументов оператора[] глубиной 2 потребовался потому что необходимо сохранять
 * последовательно 2 аргумента перед вызовом оператора=
 * например для цепочки tst[1]=tst[2]=tst[3] будет выполнено по порядку:
 * сохранен на вершине стека аргумент равный 3
 * сохранен на вершине стека аргумент равный 2
 * вершина стека это индекс для записи, следующий элемент в стеке индекс для чтения
 * выполнен оператор= то есть прочитан tst[3] и сохранен в tst[2]
 * сохранен на вершине стека аргумент равный 1
 * выполнен оператор= то есть прочитан tst[2] и сохранен в tst[1]
 *
 * */

constexpr int maz_size = 8;

class CTest {
public:

    CTest() :  maddr(0), maddr2(0) {bzero(rep, maz_size*4);}
    ~CTest() {}

    CTest& operator[] (int index) {printf("operator[]:  maddr=%d\n", index); maddr2 = maddr; maddr = index; return *this;}
    CTest& operator= (int rhv) {setreg(maddr, rhv); return *this;}
    CTest& operator= (CTest& rhv) {printf("maddr=%d rhv.maddr2=%d\n", maddr, rhv.maddr2);setreg(maddr, rhv.getreg(rhv.maddr2)); return *this;}
    operator int() {return getreg(maddr);}

private:
    void setreg(int addr, int val){printf("setreg:  maddr=%d val=%d\n", addr, val); rep[addr]=val;}
    int getreg(int addr){printf("getreg:  maddr=%d val=%d\n", addr, rep[addr]); return rep[addr];}

    int maddr;
    int maddr2;
    int rep[maz_size];
};

void cpptest_run();

/* неудачная попытка использовать два operator[] и operator[] const для определения в какой части выражения используются []
 * в правой или левой */

//class CTest2 {
//public:
//
//    CTest2() :  maddr(0) {bzero(rep, maz_size*4);}
//    ~CTest2() {}
//
//    CTest2& operator[] (int index) {printf("operator1[]:  maddr=%d\n", index);  maddr = index; return *this;}
//    const int operator[] (int const index) const {printf("operator2[]:  maddr=%d\n", index); return getreg(index);}
//    CTest2& operator= (int rhv) {setreg(maddr, rhv); return *this;}
//    operator int() {return getreg(maddr);}
//
//private:
//    void setreg(int addr, int val){printf("setreg:  maddr=%d val=%d\n", addr, val); maddr = addr; rep[addr]=val;}
//    int getreg(int addr)const {printf("getreg:  maddr=%d val=%d\n", addr, rep[addr]); return rep[addr];}
//
//    int maddr;
//    int rep[maz_size];
//};

//class CTest3 {
//public:
//
//    CTest3() :  maddr(0), maddr2(0) {bzero(rep, maz_size*4);}
//    ~CTest3() {}
//
//    CTest3& operator[] (int index) {printf("operator[]:  maddr=%d\n", index); maddr2 = maddr; maddr = index; return *this;}
////    CTest3& operator= (int rhv) {setreg(maddr, rhv); return *this;}
////    CTest3& operator= (CTest& rhv) {printf("maddr=%d rhv.maddr2=%d\n", maddr, rhv.maddr2);setreg(maddr, rhv.getreg(rhv.maddr2)); return *this;}
//    operator int() {printf("operator int():"); return getreg(maddr);}
//    int getAddr(){return maddr;}
//
//    void setreg(int addr, int val){printf("setreg:  maddr=%d val=%d\n", addr, val); rep[addr]=val;}
//    int getreg(int addr){printf("getreg:  maddr=%d val=%d\n", addr, rep[addr]); return rep[addr];}
//
//private:
//
//    int maddr;
//    int maddr2;
//    int rep[maz_size];
//};
//
//int operator= (CTest3& lhv, int rhv){lhv.setreg(lhv.getAddr(), rhv); return rhv;}
//const CTest3 operator= (int& lhv, CTest3& rhv) {lhv = rhv.getreg(rhv.getAddr()); return rhv;}

} //namespace ctest

