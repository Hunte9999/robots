#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <stdexcept>

namespace robots {

template<typename T>
class Vector
{
public:
    T* beginning;
    int currsize, maxsize;
    static const int SZ = 5;
public:

    class const_It
    {
    private:
        const T* st;
        int pointer_;
        const_It(const T* ss,int size = 0) : st(ss), pointer_(size) {}
    public:
        friend class Vector;
        const_It(): st(nullptr), pointer_(0) {}
        const_It(const const_It &other): st(other.st), pointer_(other.pointer_) {}

        bool operator!=(const const_It& other) const
        {
            return !(*this == other);
        }

        bool operator==(const const_It& other) const
        {
            return pointer_ == other.pointer_;
        }

        const_It& operator++()
        {
            ++pointer_;
            return *this;
        }

        const_It& operator--()
        {
            --pointer_;
            return *this;
        }

        const T &operator*() const
        {
            return *(st+pointer_);
        }

        const T *operator ->()
        {
            return st+pointer_;
        }
    };


    class It
    {
    private:
        T* st;
        int pointer_;
        It(T* ss, int size = 0) : st(ss), pointer_(size) {}
    public:
        friend class Vector;

        bool operator!=(const It& other) const
        {
            return !(*this == other);
        }

        bool operator==(const It& other) const
        {
            return pointer_ == other.pointer_;
        }

        It& operator++()
        {
            ++pointer_;
            return *this;
        }

        const_It& operator--()
        {
            --pointer_;
            return *this;
        }

        T &operator*() const
        {
            return *(st+pointer_);
        }

        T *operator ->()
        {
            return st+pointer_;
        }
    };

    Vector() : currsize(0), maxsize(SZ) { beginning = new T[SZ]; }
    Vector(const Vector& other)
    {
        currsize = other.currsize;
        maxsize = other.maxsize;
        beginning = new T[maxsize];
        for (int i = 0; i < currsize; ++i){
            beginning[i] = other[i];
        }
    }
    ~Vector(){ delete[] beginning; }

    void push_back(const T& item)
    {
        if(currsize == maxsize){
            T* nbeg = new T[maxsize+SZ];
            maxsize += SZ;
            for(int i = 0; i < currsize; ++i){
                nbeg[i] = beginning[i];
            }
            delete[] beginning;
            beginning = nbeg;
        }

        beginning[currsize] = item;
        ++currsize;

    }

    It begin()
    {
        return It(beginning);
    }

    It end()
    {
        if(currsize == 0){
            return It(beginning);
        }
        else{
            return It(beginning, currsize);
        }
    }

    const_It begin() const
    {
        return const_It(beginning);
    }

    const_It end() const
    {
        if(currsize == 0){
            return const_It(beginning);
        }
        else{
            return const_It(beginning, currsize);
        }
    }

    void clear()
    {
        currsize = 0;
        delete[] beginning;
        beginning = new T[maxsize];
    }

    int size() const
    {
        return currsize;
    }

    int capacity() const
    {
        return maxsize;
    }

    bool empty() const
    {
        return currsize == 0;
    }

    const T &operator[](int n) const
    {
        return beginning[n];
    }

    T &operator[](int n)
    {
        return beginning[n];
    }

    T& front()
    {
        return beginning[0];
    }

    const T& front() const
    {
        return beginning[0];
    }

    T& back()//вызов back() для пустого контейнера не определен!
    {
        return beginning[currsize - 1];
    }

    const T& back() const
    {
        return beginning[currsize - 1];
    }

    T& at(int n)
    {
        if(n >= currsize){
            throw std::out_of_range();
        }
        return beginning[n];
    }

    const T& at(int n) const
    {
        if(!(n < currsize)){
            throw std::out_of_range();
        }
        return beginning[n];
    }

    /*It erase(It pos)
    {
        for (int i = pos.pointer_; i < currsize - 1; ++i){
            beginning[i] = beginning[i + 1];
        }
        --currsize;
        return pos;
    }

    It erase(const_It pos)
    {
        for (int i = pos.pointer_ ; i < currsize - 1; ++i){
            beginning[i] = beginning[i + 1];
        }
        --currsize;
        return pos;
    }

    It erase(It first, It last)
    {
        int n = first.pointer_;
        for (int i = last.pointer_ + 1; i < currsize; ++i){
            beginning[n++] = beginning[i];
        }
        currsize -= (last.pointer_ - first.pointer_);
        return first;
    }

    It erase( const_It first, const_It last )
    {
        int n = first.pointer_;
        for (int i = last.pointer_ + 1; i < currsize; ++i){
            beginning[n++] = beginning[i];
        }
        currsize -= (last.pointer_ - first.pointer_);
        return first;
    }*/

};

}

#endif // MYVECTOR_H
