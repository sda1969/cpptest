/*
 * threadtest.cpp
 *
 *  Created on: 15 марта 2017 г.
 *      Author: dmitry
 */

#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include <functional>     // std::ref
#include <future>         // std::promise, std::future
#include <exception>
#include <chrono>

#include <pthread.h>

namespace threadtest{


//статические переменные для данного потока thread_local
static /*thread_local компилятор 4.72 не поддерживает*/ int rage =   1 ;
static std::mutex cout_mutex;

static void increase_rage(const std::string& thread_name)
{
    ++rage; // modifying outside a lock is okay; this is a thread-local variable
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Rage counter for " << thread_name << ": " << rage << '\n';
}

// тест на локальные статические объекты потока
static void threadtest_01 ()
{
    std::thread a(increase_rage, "a"), b(increase_rage, "b");

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Rage counter for main: " << rage << '\n';
    }

    a.join();
    b.join();
}

//future promise
// promise example

// два promise на один future в цикле не работает
// один promise на два future одновременно работает - но разрешено ли так ? нет нужно shared
// Once the shared state is ready, the function unblocks and returns (or throws) releasing its shared state.
// This makes the future object no longer valid:
//this member function shall be called once at most for every future shared state.

std::mutex lck;
void print_int (std::shared_future<int>& fut) {
  try {
    int x = fut.get();
    std::lock_guard<std::mutex> lock(lck);
    std::cout << "print_int value: " << x << '\n';
  }
  catch (std::exception& e) {
    std::lock_guard<std::mutex> lock(lck);
    std::cout << "[exception caught: " << e.what() << "]\n";
  }
}

void print_int2(std::shared_future<int>& fut){
    try {
        int x = fut.get();
        std::lock_guard<std::mutex> lock(lck);
        std::cout << "print_int2 value: " << x << '\n';
    }
    catch (std::exception& e) {
        std::lock_guard<std::mutex> lock(lck);
        std::cout << "[exception caught2: " << e.what() << "]\n";
    }
}

void get_int (std::promise<int>& prom) {
  int x;
  std::cout << "Please, enter an integer value: ";
  std::cin.exceptions (std::ios::failbit);   // throw on failbit
  try {
    std::cin >> x;                           // sets failbit if input is not int
    prom.set_value(x);
  }
  catch (std::exception&) {
    prom.set_exception(std::current_exception());
  }
}

int get_int_async(int arg){
    int x;
    std::cout << "\nYour arg = " << arg << " Please, enter an integer value: ";
    std::cin >> x;
    return x;
}

//  тест на promise ,future, shared_future
void threadtest_02 ()
{
  std::promise<int> prom;                      // create promise
  std::future<int> fut = prom.get_future();    // engagement with future
  std::shared_future<int> shfut(std::move(fut)); // перемещающий конструктор из просто future или можно = fut.share();
  std::thread th1 (print_int, std::ref(shfut));  // send future to new thread
  std::thread th2 (get_int, std::ref(prom));  // send promise to new thread
  std::thread th3 (print_int2, std::ref(shfut));  // send future to new thread
                                               // (synchronizes with getting the future)
  th1.join();
  th2.join();
  th3.join();

}

//  тест на std::async
void threadtest_03 ()
{
     std::cout << "Async test \n";
     // std::launch::async - запускается сразу же
     //std::launch::deferred .- запускается после futas.get()
     //after call надпись будет в разных местах
     std::future<int> futas = std::async(std::launch::async, get_int_async, 12);

     std::this_thread::sleep_for(std::chrono::seconds(1));
     std::cout << "\n1 sec after call passed\n";
     int res = futas.get();  //ждем здесь пока функция не закончится
     std::cout << res;
}

//тест на std::packaged_task

// count down taking a second for each value:
int countdown (int from, int to) {
  for (int i=from; i!=to; --i) {
    std::cout << i << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Lift off!\n";
  return from-to;
}

void threadtest_04 ()
{
    std::packaged_task<int(int,int)> tsk (countdown);   // set up packaged_task
    std::future<int> ret = tsk.get_future();            // get future

    std::thread th (std::move(tsk),10,0);   // spawn thread to count down from 10 to 0

    int value = ret.get();                  // wait for the task to finish and get result

    std::cout << "The countdown lasted for " << value << " seconds.\n";

    th.join();
}

void threadtest_run(){
//    threadtest_01 ();
//    threadtest_02 ();
//    threadtest_03 ();
    threadtest_04 ();

}

}
