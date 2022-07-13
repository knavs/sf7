#include "intarray.h"
#include <ostream>
IntArray::IntArray(int length):
    m_length{ length }
{
    //assert(length >= 0);
    if (length <= 0) throw BadSize("Array Length must be positive");//;std::runtime_error("Array Length must be positive");

    if (length > 0)
        m_data = new int[length]{};
}

IntArray::IntArray(const IntArray &other)
{
    int length = other.getLength();

    if (length <= 0) {
        throw  BadSize("Wrong other Length");
    } else {
        //��������� ������ �� 10 ���������
        m_data = new int[length]{};
        m_length = length;
        // ��������� ��� ����������
        for (int i = 0; i < m_length; i++) {
            m_data[i] = other.m_data[i];
        }
    }

}

IntArray::~IntArray()
{
    delete[] m_data;
    // �� ���� ����������� m_data = null ��� m_length = 0, �.�. � ����� ������ ������ ����� ��������� ��������� ����� ����� ����� �����������
}

void IntArray::erase()
{
    delete[] m_data;
    // �� ������ ���� �������, ��� m_data = nullptr,
    // ����� m_data ����� ��������� �� ��������� ������� ������!
    m_data = nullptr;
    m_length = 0;
}

int &IntArray::operator[](int index)
{
    //assert(index >= 0 && index < m_length);
    if  (index < 0 or index >= m_length) throw BadRange("Access index out of range");

    return m_data[index];
}

int IntArray::index(int value)
{
    for (int i = 0; i < m_length; i++) {
        if (m_data[i] == value) return i;
    }

    throw ArrayException("No such value in array");
}

//int IntArray::operator[](int index) const
//{
//    //assert(index >= 0 && index < m_length);
//    if  (index < 0 or index >= m_length) throw BadRange("Access index out of range");

//    return m_data[index];
//}

void IntArray::reallocate(int newLength)
{
    // 1. ������� ��� ������������ �������� �������
    erase();

    // 2. ���� ����� ������ ������, ����� ����� ���������� ������ ������
    if (newLength <= 0)
        return;

    // 3. ���� ����� ������ ��������. ���������, �������������� � �������� ������ ��� ����� ������
    m_data = new int[newLength];
    m_length = newLength;
}

void IntArray::resize(int newLength)
{
    if (newLength < 0) throw BadSize("Array length can't be negative.");
    // ���� ��������� ������ ������� ����� �������� ������� �������. ������ �� ������
    if (newLength == m_length)
        return;

    // ���� ����� ������ ����� 0. ������� ������ � ���������� ������
    if (newLength == 0)
    {
        erase();
        return;
    }

    // �����������, ��� ����� ����� newLength ��� ������� 1.
    // �������� �����: �������� ������ ��� ����� ������.  �����
    // �������� � ����� ������ �������� �� ������� �������.
    // ����� ���������� �����������, ������� ������ �����,
    // � ������������� ��������� make m_data �� ����� ������.

    // �������� ������ ��� ����� ������
    int* data{ new int[newLength] };

    // ���� ������ ������� ��������� ���������� �� ������� ������� � �����
    // �������� �� ������� ������� ���������, ������� ���������� � ���������� �� ���� ��������.
    if (m_length > 0)
    {
        int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

                            // �������� �� ������ ��� �������� �� ������� ������� � �����
                            for (int index{ 0 }; index < elementsToCopy; ++index)
                                data[index] = m_data[index];
    }

    // ������� ������ ������. �� ��� ������ �� �����
    delete[] m_data;

    // And use the new array instead!  Note that this simply makes m_data point
    // to the same address as the new array we dynamically allocated.  Because
    // data was dynamically allocated, it won't be destroyed when it goes out of scope.
    m_data = data;
    m_length = newLength;
}

void IntArray::insertBefore(int value, int index)
{
    // �������� ������������ ����������� �������
    //assert(index >= 0 && index <= m_length);
    if (index < 0 || index > m_length) throw BadIndex("Sanity check our index value");//throw std::runtime_error("Sanity check our index value");

    // ������� ����� ������ � ������ �� 1 ������� ������ �������
    int* data{ new int[m_length+1] };

    // �������� ��� �������� �� 0 �� index-1
    for (int before{ 0 }; before < index; ++before)
        data[before] = m_data[before];

    // ��������� ����� ������� value � ������ �� ������� index
    data[index] = value;

    // �������� ��� ��������, ������ ����� ������������ ��������
    for (int after{ index }; after < m_length; ++after)
        data[after+1] = m_data[after];

    // �������, ������� ������ ������ � ������ ���� ����� �����
    delete[] m_data;
    m_data = data;
    ++m_length;
}

void IntArray::remove(int index)
{
    // �������� ������������ ����������� �������
    //assert(index >= 0 && index < m_length);
    if (index < 0 || index >= m_length) throw BadIndex("Sanity check our index value"); //ArrayOutOfRange("Sanity check our index value");

    // ���� � �� ������� ������������ ������� � �������. �� ����� ������ �������� ������ � ������� ������
    if (m_length == 1)
    {
        erase();
        return;
    }

    // ������� ����� ������ � ������ �� 1 ������� ������ �������
    int* data{ new int[m_length-1] };

    // �������� ��� �������� �� 0 �� index-1
    for (int before{ 0 }; before  < index; ++before)
        data[before] = m_data[before];

    // �������� ��� ��������, ������ ����� ����������
    for (int after{ index+1 }; after < m_length; ++after)
        data[after-1] = m_data[after];

    // �������, ������� ������ ������ � ������ ���� ����� �����
    delete[] m_data;
    m_data = data;
    --m_length;
}

void IntArray::insertAtBeginning(int value)
{
    insertBefore(value, 0);
}

void IntArray::insertAtEnd(int value)
{
    insertBefore(value, m_length);
}

int IntArray::getLength() const
{
    return m_length;
}

std::ostream& operator<<(std::ostream& ostr, IntArray rhs)
{
    ostr << "[";
    for (int i = 0; i < rhs.getLength(); i++) {
        ostr << (i == 0 or rhs.getLength() == 1 ? "" : ", ");
        ostr << rhs[i];
    }
    ostr << "]";

    return ostr;
}
