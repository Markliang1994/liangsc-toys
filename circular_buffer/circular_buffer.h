//
// Created by mark on 1/6/17.
//

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <cstdint>

namespace liangsc_toys { ;
    template<typename T>
    class circular_buffer {
    private:
        uint32_t head_;
        uint32_t tail_;
        uint32_t size_;
        T *array_;
    public:
        circular_buffer(int size)
                : head_(0), tail_(0), size_(size+1), array_(new T[size_]){

        }
        circular_buffer(int size, const T &val)
                : head_(0), tail_(0), size_(size + 1), array_(new T[size_]) {
        }
        circular_buffer(const circular_buffer<T> &rhs)
                : head_(rhs.head_), tail_(rhs.tail_), size_(rhs.size_){
            for(int i = 0; i < size_; ++i){
                array_[i] = rhs.array_[i];
            }
        }
        circular_buffer& operator =(const circular_buffer<T> &rhs){
            if(this == &rhs){
                return *this;
            }
            delete []array_;
            head_ = rhs.head_;
            tail_ = rhs.tail_;
            size_ = rhs.size_;

            array_ = new T[size_];
            for(int i = 0; i < size_; ++i){
                array_[i] = rhs.array_[i];
            }
            return *this;
        }

        circular_buffer &operator ==(circular_buffer<T> &&rhs){
            head_(rhs.head_);
            tail_ (rhs.tail_);
            size_ (rhs.size_);
            array_(rhs.array_);
            return *this;
        }

        circular_buffer(circular_buffer<T> &&rhs)
            : head_(rhs.head_),
              tail_ (rhs.tail_),
              size_ (rhs.size_),
              array_(rhs.array_){
        }

        ~circular_buffer(){
            delete []array_;
        }

    };
}
#endif //C_CIRCULAR_BUFFER_H
