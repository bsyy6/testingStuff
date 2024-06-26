#ifndef FFIFO_H
#define FFIFO_H

#include <vector>
#include <cstddef>
/*
FFIFO: [F]ixed_size [F]irst [I]n [F]irst [O]ut 
template class that inherits from std::vector
and maintains a fixed size FIFO. 
When the maximum size is reached, it removes
the oldest element before adding a new one.
warning:
filling starts from end:
FFIFO<int,4> fifo; // [Nan,Nan,Nan,Nan]
fifo.push_back(1); // [1,Nan,Nan,Nan]
fifo.push_back(99); // [0,0,1,99]
*/

template <typename T, size_t MaxLen>
class FFIFO : public std::vector<T> {
    public:
        FFIFO() : std::vector<T>() {
            // block memory
            this->reserve(MaxLen);
        }
    
        void push_back(const T& value){
            if (this->size() == MaxLen) {
                this->erase(this->begin());
            }
            // the normal function for vector 
            std::vector<T>::push_back(value); // Add the new element
        }
};

#endif // FFIFO_H
