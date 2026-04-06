#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <cstddef>

template <typename T>
class Sequence {
public:
    // взятие итератора
    // Get[index] иеренести на arraysequence
    virtual const T& Get(size_t index) const = 0;
    virtual const T& GetFirst() const = 0;
    virtual const T& GetLast() const = 0;
    virtual size_t GetLength() const = 0;

    virtual Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) const = 0;
    virtual Sequence<T>* Concat(const Sequence<T> &other) const = 0;

    virtual Sequence<T> *Clone() const = 0;

    virtual ~Sequence() {}
};

#endif /* SEQUENCE_HPP */
