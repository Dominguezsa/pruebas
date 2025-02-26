// condition_variable::notify_all
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable


class Base{
public:
  static void f1(void) {
    std::cout << "B.f1" << std::endl;
  }

  void f2(void) {
    std::cout << "B.f2" << std::endl; f3(); f1();
  }

  virtual void f3(void) {
    std::cout << "B.f3" << std::endl; f1();
  }
};

class Derived : public Base {
public:
  static void f1(void) {
    std::cout << "D.f1" << std::endl;
  }

  void f2(void) {
    std::cout << "D.f2" << std::endl; f3(); f1();
  }
  
  virtual void f3(void) {
    std::cout << "D.f3" << std::endl; f1();
  }
};

int main() {
  Derived* pD = new Derived();
  Base *pB = pD;
  pB->f1();
  std::cout << "----" << std::endl;
  pB->f2();
  std::cout << "----" << std::endl;
  pD->f1();
  std::cout << "----" << std::endl;
  pD->f3();
}