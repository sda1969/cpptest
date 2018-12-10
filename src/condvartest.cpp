/*
 * condvartest.cpp
 *
 *  Created on: 16 февр. 2017 г.
 *      Author: dmitry
 */

// condition_variable example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <unistd.h>
#include "condvartest.h"

namespace cvtest{

const int numThreads = 5;

static std::mutex mtx;
static std::condition_variable request, confirm;
static bool ready = false;
static uint32_t data;

// универсальный работник
static void worker (int id) {
    uint32_t localData;

  while(1){
      // блок выполняющийся с  обязательно закрытом мютексом
      {
          // ждем заявку мютекс закрыт
          std::unique_lock<std::mutex> lck(mtx);
          while (!ready){
              request.wait(lck);
          }
          // mutex по прежнему закрыт здесь
          ready = false; // обработал заявку
          localData = data;
          std::cout << "thread id=" << id << " local data=" << localData << '\n';
          confirm.notify_one(); //заявка принята в работу
      } //  <--мютекс открывается здесь

      // имитация длительной самостоятельной работы над локальным комплектом данных
      // мютекс открыт что-бы не мешать другим в это время принимать и выполнять заявки
      sleep(1);
  }

}


void condvartest_run(){

      std::thread threads[10];
      // numThreads одинаковых исполнителей работы, мне все равно кто ее сделает
      for (int i = 0; i < numThreads; ++i){
        threads[i] = std::thread(worker, i);
      }

      std::cout << numThreads << " workers ready to serve my requests...\n";

      while(1){
          //lock нужен что-бы работники не могли отменить задание до его запуска
          std::unique_lock<std::mutex> lck(mtx);
          //std::cout << "go!" <<  '\n';
          data++; // новые данные для очередного работника
          ready = true;
          request.notify_one(); //заявка работнику
          //не будем посылать заявки до тех пор, пока последняя не будет принята в работу
          while (ready){
              confirm.wait(lck);
          }
      }

      for (auto& th : threads) th.join();
}

}
