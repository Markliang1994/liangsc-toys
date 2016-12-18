//
// Created by mark on 16-12-8.
//
// printf implement with variadic template
#include <iostream>
#include <set>

#include <string.h>

namespace liangsc_toys {
    using std::cout;
    const std::set<char> tag = {'d', 'c', 'f', 'u', 'p'};

    void my_printf(const char *fmt) {
        int len = strlen(fmt);
        for(int i = 0; i < len; ++i){
            if(fmt[i] == '%') {
                if (i + 1 < len && fmt[i + 1] == '%')
                    ++i;
                else
                    throw std::runtime_error("Invalid format string: missing format arguments");
            }
            cout << fmt[i];
        }
    }

    template<typename T, typename ...Args>
    void my_printf(const char *fmt, const T value, Args ...args) {
        int len = strlen(fmt);
        for(int i = 0; i < len; ++i){
            if(fmt[i] == '%'){
                if(!(i+1 < len))
                    return ;
                else{
                    if(fmt[i+1] == '%') {
                        ++i;
                    }
                    else if(tag.find(fmt[i+1]) != tag.end()){
                        cout << value;
                        my_printf(fmt+2, args...);
                        return;
                    }
                }
            }
            cout << fmt[i];
        }
    }
}
using namespace liangsc_toys;
int main(void){
    my_printf("%c\n", 'f');
    return 0;
}