#ifndef INTARRAY_H
#define INTARRAY_H
#include <stdexcept>
#include <iostream>
#include <ostream>
#include "arrayexception.h"
#include <string>
#include <cassert> // for assert()

class IntArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int length);
    // Конструктор копирования (+1)
    IntArray(const IntArray&);


    ~IntArray();

    void erase();

    int& operator[](int index);
    //int operator[](int index) const;

    int index(int value);

    // reallocate - меняет размер массива.  Все существующие элементы будут уничтожены.  Быстрая функция.
    void reallocate(int newLength);

    // resize - меняет размер массива.  Все существующие элементы будут сохранены.  Медленная функция.
    void resize(int newLength);

    void insertBefore(int value, int index);

    void remove(int index);

    // Пара вспомогательных функций для удобства
    void insertAtBeginning(int value);
    void insertAtEnd(int value);

    int getLength() const;

    // Перегрузка оператора вывода (+2)
    friend std::ostream& operator<<(std::ostream& ostr, const IntArray rhs);

};



#endif
