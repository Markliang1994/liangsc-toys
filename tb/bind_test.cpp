#include <iostream>
#include "bind.h"

class Foo{
public:
    int bar(int val){
        std::cout << "Call the fucking Foo::bar." << std::endl;
    }
};
void bar(int val) {
    std::cout << "fuck this bar" << std::endl;
}

int main(void){
    auto c1 = liangsc_toys::bind(bar, 42);
    c1();
    Foo foo;
    auto c2 = liangsc_toys::bind(&Foo::bar, &foo, 43);
    c2(43);
    return 0;
}