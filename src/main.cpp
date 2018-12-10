/*
 * main.cpp
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
#include "condvartest.h"
#include "semtest.h"
#include "threadtest.h"
#include "chronotest.h"
#include "containerstest.h"
#include "newt_test.h"
#include "destructorstest.h"
#include "streamtest.h"
#include "regextest.h"
#include "ctortest.h"
#include "cfilereadtest.h"
#include "templatetest.h"

int main() {

    //ctest::cpptest_run();
    //cvtest::condvartest_run();
    //semtest::semtest_run();
    //threadtest::threadtest_run();
    //chronotest::chronotest_run();
    //containerstest::containerstest_run();
    //newt_test::newt_test_run();
    //destructors::destructorstest_run();
    //streams::streamstest_run();
    //rgx::regextest_run();
	//ctortest::ctortest_run();
	//freadtest::freadtest_run();
	templatetest::templatetest_run();

    return 0;
}
