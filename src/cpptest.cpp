/*
 * cpptest.cpp
 *
 *  Created on: 16 февр. 2017 г.
 *      Author: dmitry
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <strings.h>

#include "cpptest.h"

namespace ctest {

void cpptest_run(){

    ctest::CTest tst;

    tst[3] = 4;
    tst[1] = 2;
    auto a = tst[3];
    printf("---- is not read yet \n");
    printf("a=%d\n", static_cast<int>(a));

    printf("-----------\n");
    tst[1] = tst[2];
    printf("-----------\n");
    tst[1] = tst[2] = tst[3];
    printf("-----------\n");
    tst[1] = tst[2] = 3;
    printf("-----------\n");

    int x  = 1;
    int y  = 2;
    int z  = 3;

    x = y = z;

    printf("x=%d\n", x);

//    printf("-----------\n");
//    ctest::CTest3 tst3;
//    tst3[5] = 6;
//    printf("-----------\n");
//    volatile int a3 = tst3[5];
//    printf("-----------\n");
//    printf("%d\n", tst3[5]);

}

}
