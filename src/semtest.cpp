/*
 * semtest.cpp
 *
 *  Created on: 20 февр. 2017 г.
 *      Author: dmitry
 */

#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <unistd.h>
#include <cstdio>

/* реализация различных семафоров через условные переменные,
 *  так как семафоры не входят в STL*/

namespace semtest {

constexpr int num_thrds = 5;

class CCountSema {
public:
    CCountSema(uint32_t cnt = 0) : m_cnt(cnt) {};
    ~CCountSema(){};
    void signal();
    void wait();
    int try_wait();


private:
    uint32_t m_cnt;
    std::mutex mtx;
    std::condition_variable m_cv;
};

void CCountSema::signal(){
    std::unique_lock<std::mutex> lck(mtx);
    m_cnt++;
    m_cv.notify_one();

}

void CCountSema::wait(){
    std::unique_lock<std::mutex> lck(mtx);
    while (m_cnt == 0){
        m_cv.wait(lck);
    }
    m_cnt--;
}

int CCountSema::try_wait(){
    std::unique_lock<std::mutex> lck(mtx);
    if (m_cnt == 0){
        return -1;
    }
    m_cnt--;
    return 0;
}
//sema.wait()
static void  semtest01(){
        CCountSema sema(0);

       std::thread trd[num_thrds];

       for (int i = 0; i < num_thrds; ++i){
           trd[i] =  std::thread([&sema](int id){sema.wait(); std::cout << id << std::endl; }, i);
       }

       for(int i = 0; i < 4; i++){
           sema.signal();
       }

       for (auto& th : trd) th.join();
}
//sema.try_wait()
static void  semtest02(){
        CCountSema sema(0);

       std::thread trd[num_thrds];

       for (int i = 0; i < num_thrds; ++i){
           trd[i] =  std::thread([&sema](int id){while (-1==sema.try_wait()){std::cout <<".\n";sleep(1);}; std::cout << id; }, i);
       }

       for(int i = 0; i < 4; i++){
           sema.signal();
       }

       for (auto& th : trd) th.join();
}

void semtest_run(){
 //   semtest01();
    semtest02();

}

}
