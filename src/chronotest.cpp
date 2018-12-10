/*
 * chronotest.cpp
 *
 *  Created on: 24 марта 2017 г.
 *      Author: dmitry
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <ratio>
#include <ctime>

#include "chronotest.h"

namespace chronotest {

//duration test
void test01(){
    std::chrono::duration<int, std::ratio<60,1>> dminutes {1};
    std::chrono::duration<int, std::ratio<1,1>> dseconds {1};
    std::chrono::duration<int, std::ratio<1,1000>> dmiliseconds {500};
    typedef std::chrono::duration<uint64_t, std::ratio<1,1000000>> microsec_t;

    while(1){
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //std::this_thread::sleep_for(std::chrono::hours(1));
        //std::this_thread::sleep_for(dseconds);
        //std::this_thread::sleep_for(dmiliseconds);


        //auto dur = std::chrono::microseconds {500000};
        //dmiliseconds = 100; нельзя
        //dseconds = std::chrono::duration<int, std::ratio<1,1>> {2};
        //auto dur = dseconds;
        //auto dur = std::chrono::duration<double, std::ratio<1,1000>> {507.8};
        //std::chrono::duration<double, std::ratio<1,1000>> dur {509.8};
        //std::chrono::milliseconds dur {607};
        microsec_t dur {807};
        std::this_thread::sleep_for(dur);
        std::cout << dur.count() << " period passed\n";
    }
}

//time_point and clock test
void test02(){
    std::chrono::system_clock::time_point tp_epoch;  // epoch value

    std::chrono::time_point <std::chrono::system_clock, std::chrono::duration<int>> tp_seconds (std::chrono::duration<int>(1));

    std::chrono::system_clock::time_point tp {tp_seconds};

      std::cout << "1 second since system_clock epoch = ";
      std::cout << tp.time_since_epoch().count();
      std::cout << " system_clock periods." << std::endl;

      // display time_point:
      std::time_t tt = std::chrono::system_clock::to_time_t(tp);
      std::cout << "time_point tp is: " << ctime(&tt);

      std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
// с компилятором 4.7 строки ниже работали с 4.9 нет
//      std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int, std::ratio<1,1000000 >>> t11 = std::chrono::steady_clock::now();
//      std::time_t tt1 = std::chrono::steady_clock::to_time_t(t11);
//      std::cout << "time_point tp is: " << ctime(&tt1);

      std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
      //auto dur = std::chrono::duration<int, std::ratio<1,1000000>>(t2-t1);
      std::chrono::duration<int, std::ratio<1,1000000 > > dur = std::chrono::duration_cast < std::chrono::duration < int, std::ratio<1,1000000 > > >(t2 - t1);
      //std::chrono::microseconds dur = std::chrono::duration_cast< std::chrono::microseconds> (t2 - t1);
      std::cout << dur.count() << " us time interval\n";

      typedef std::chrono::duration<int,std::ratio<60*60*24*7>> weeks_type;
      std::chrono::time_point<std::chrono::system_clock,weeks_type> today =std::chrono::time_point_cast<weeks_type>(std::chrono::system_clock::now());

      std::cout << today.time_since_epoch().count() << " weeks since epoch" << std::endl;
}

void chronotest_run(){
//    test01();
    test02();
}

}
