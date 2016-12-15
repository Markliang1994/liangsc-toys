//
// Created by mark on 16-12-13.
//
#ifndef LIANGSC_TOYS_BIND_H
#define LIANGSC_TOYS_BIND_H

namespace liangsc_toys{
    template <typename R, typename T, typename Arg>
    class bind_t;

    template <typename R, typename T, typename Arg>
    class bind_t{
    private:
        typedef R(T::*F)(Arg);
        F f_;
        Arg a_;
        T *t_;

    public:
        bind_t(F f, T *t, Arg a)
                : f_(f), a_(a), t_(t)
        { }

        R operator() (Arg a){
            (t_->*f_)(a);
        }
    };

    template <typename R, typename Arg>
    class bind_t<R, Arg, void>{
    private:
        typedef R(*F)(Arg);
        F f_;
        Arg a_;
    public:
        bind_t(F f, Arg a)
                : f_(f), a_(a)
        { }

        R operator()(){
            f_(a_);
        }
    };

    template <typename R, typename Arg>
    bind_t<R, Arg, void> bind(R(*f)(Arg), Arg a){
        return bind_t<R, Arg, void>(f, a);
    };

    template <typename R, typename T, typename Arg>
    bind_t<R, T, Arg> bind(R(T::*f)(Arg), T *t, Arg a){
        return bind_t<R, T, Arg>(f, t, a);
    };

};

#endif