#include <iostream>

class Foo
{
public:
    explicit Foo(int foo) : m_foo(foo) {}

    int foo() const { return m_foo; }

private:
    int m_foo;
};

void doBar(Foo foo)
{
    int i = foo.foo();
}

int main(int argc, char* argv[]) 
{
    doBar(42);
    return 0;
}
