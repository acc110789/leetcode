#include <iostream>

struct A
{
  A(int x) : x(x) {};
  int call_me() { return x; }
  int x;
};

struct B
{
  B(A* a) : i(the_a->call_me()), the_a(a) {}
  int i;
  A* the_a;
};

int
main()
{
  A a(20);
  B b(&a);
  std::cout << b.i << std::endl;
}
