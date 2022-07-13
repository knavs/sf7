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
    // ����������� ����������� (+1)
    IntArray(const IntArray&);


    ~IntArray();

    void erase();

    int& operator[](int index);
    //int operator[](int index) const;

    int index(int value);

    // reallocate - ������ ������ �������.  ��� ������������ �������� ����� ����������.  ������� �������.
    void reallocate(int newLength);

    // resize - ������ ������ �������.  ��� ������������ �������� ����� ���������.  ��������� �������.
    void resize(int newLength);

    void insertBefore(int value, int index);

    void remove(int index);

    // ���� ��������������� ������� ��� ��������
    void insertAtBeginning(int value);
    void insertAtEnd(int value);

    int getLength() const;

    // ���������� ��������� ������ (+2)
    friend std::ostream& operator<<(std::ostream& ostr, const IntArray rhs);

};



#endif
