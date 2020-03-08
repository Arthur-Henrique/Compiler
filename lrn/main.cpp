#include<iostream>
#include <thread>
#include <mutex>
#include <string>
#include <stdlib.h>

using namespace std;

template <typename T>
class Wrap_ptr{
    T* ptr;
    mutex* mtx;

  public:
    Wrap_ptr(T* _ptr, mutex* _mtx) : ptr(_ptr), mtx(_mtx) { }

    struct Proxy {
        T* ptr;
        mutex* pmtx;

      public:
        Proxy(T* _ptr, mutex* _mtx) : ptr(_ptr), pmtx(_mtx) {
/**/      pmtx->lock();
          cout << "Proxie { ";
        }

        T* operator->(){
          chrono::milliseconds timespan(1111);
          this_thread::sleep_for(timespan);
          *ptr << 1;
          return ptr;
        }

        ~Proxy(){
          cout << " }" << endl;
/**/      pmtx->unlock();
        }
    };

    Proxy operator->(){
      return Proxy(ptr, mtx);
    }
};

struct Obj {
    int a = 5;

    void operator<<(int b){
        a += b;
    }
};

Obj obj = Obj();
static std::mutex mtx;

Wrap_ptr<Obj> wptr = Wrap_ptr<Obj>(&obj, &mtx);

void func(string str){
  cout << str << " : ";
  printf("%d", wptr->a);
}

int main(){
  cout << "it will begin" << endl;

  thread t1(func, "First");
  thread t2(func, "Second");
  thread t3(func, "Third");
  thread t4(func, "Fourth");
  thread t5(func, "Fifth");
  thread t6(func, "Sixth");
  t6.join();
  t5.join();
  t4.join();
  t3.join();
  t2.join();
  t1.join();

  cout << "it's done" << endl;
  return 0;
}
