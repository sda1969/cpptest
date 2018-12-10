/*
 * templatetest.cpp
 *
 *  Created on: 17 окт. 2018 г.
 *      Author: user
 */
#include <iostream>
#include "templatetest.h"

namespace templatetest {

void templatetest_run(){
	integral_constant<bool, true> myTrue;
	if (myTrue){  //работает operator T()
		printf("yes\n");
	}
	integral_constant<int, 1> my_1;
	printf("%d\n", (decltype(my_1)::value_type) my_1);

	int x = my_1;
	printf("%d\n",  x);
}

}


