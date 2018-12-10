/*
 * destructorstest.cpp
 *
 *  Created on: 21 апр. 2017 г.
 *      Author: dmitry
 */
#include <iostream>
#include <memory>

namespace destructors {


static void destr01(){
    std::cout << "destr01()\n";

    struct point{

        virtual ~point(){std::cout << "destructor point \n"; }

    };

    struct a_point : public point{

        int z {3};
        ~a_point(){std::cout << "destructor a_point \n"; }
    };

    struct b_point : public a_point{

        int w {4};
        ~b_point(){std::cout << "destructor b_point \n"; }
    };

    {
        point * ptr = new  b_point; //деструктор HE будет вызван для объекта на который указ ptr

        std::unique_ptr<b_point> smartptr(new b_point); //деструктор будет вызван для объекта на который указ smartptr
        //указатель на базовый класс point деструктор должн быть virtual

        std::cout << smartptr->w << "\n";

    }

}
static void autoptr(){
    std::auto_ptr<int> x_ptr(new int(42));
    std::auto_ptr<int> y_ptr;

    // вот это нехороший и неявный момент
    // права владения ресурсов уходят в y_ptr и x_ptr начинает
    // указывать на null pointer
    y_ptr = x_ptr;

    // segmentation fault
    std::cout << *x_ptr << std::endl;
}

static void uniqueptr(){
    std::unique_ptr<int> x_ptr(new int(42));
    std::unique_ptr<int> z_ptr(new int(43));
    int * foo = nullptr;
    {
        std::unique_ptr<int> y_ptr;

        // ошибка при компиляции
        //y_ptr = x_ptr;

        // ошибка при компиляции
        //std::unique_ptr<int> z_ptr(x_ptr);

        y_ptr = std::move(x_ptr);

        // получаем классический указатель
        foo = y_ptr.get();
        std::cout << *foo << std::endl;
        // delete object и назначить новый
        //y_ptr.reset(new int (44));
        y_ptr.release();//объект не удаляется
    }

    std::cout << *foo << std::endl;

}
static void sharedptr(){
    std::shared_ptr<int> x_ptr(new int(42));
    std::shared_ptr<int> y_ptr(new int(13));

    // после выполнения данной строчки, ресурс
    // на который указывал ранее y_ptr (istd::endl;nt(13)) освободится,
    // а на int(42) будут ссылаться оба указателя
    y_ptr = x_ptr;
    std::shared_ptr<int> z_ptr(y_ptr);
    std::cout << *x_ptr << "\t" << *y_ptr << std::endl;
    std::cout << y_ptr.use_count() << std::endl;
    x_ptr.reset(new int(15));
    std::cout << y_ptr.use_count() << std::endl;

}

//what a weak pointer does -- it allows you to locate an object if it's still around,
//but doesn't keep it around if nothing else needs it.
static void weakptr(){
    std::shared_ptr<int> x_ptr(new int(42));
    std::weak_ptr<int> w_ptr = x_ptr;
    std::cout << *x_ptr << std::endl;

    if(std::shared_ptr<int>  ptr = w_ptr.lock()){
        std::cout << *ptr << std::endl;
        std::cout << x_ptr.use_count() << std::endl;
    }
    else {
        std::cout << "expired\n";
    }
    std::cout << x_ptr.use_count() << std::endl;
    x_ptr.reset(new int(42));
    std::cout << x_ptr.use_count() << std::endl;
    //можно проеверить w_ptr.expired()
    if (w_ptr.expired()){
        std::cout << "expired\n";
    }
}

void destructorstest_run(){
    //destr01();
    //autoptr();
    //uniqueptr();
    //sharedptr();
    weakptr();
}

}
