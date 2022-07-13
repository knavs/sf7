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
        //Объявляем массив из 10 элементов
        m_data = new int[length]{};
        m_length = length;
        // Заполняем его значениями
        for (int i = 0; i < m_length; i++) {
            m_data[i] = other.m_data[i];
        }
    }

}

IntArray::~IntArray()
{
    delete[] m_data;
    // Не надо присваивать m_data = null или m_length = 0, т.к. в любом случае объект будет уничтожен мгновенно после вызва этого деструктора
}

void IntArray::erase()
{
    delete[] m_data;
    // Мы должны быть уверены, что m_data = nullptr,
    // иначе m_data будет указывать на очищенный участок памяти!
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
    // 1. Удаляем все существующие элементы массива
    erase();

    // 2. Если новый массив пустой, тогда тутже возвращаем пустой массив
    if (newLength <= 0)
        return;

    // 3. Если новый массив непустой. Объявляем, инициализируем и выделяем память под новый массив
    m_data = new int[newLength];
    m_length = newLength;
}

void IntArray::resize(int newLength)
{
    if (newLength < 0) throw BadSize("Array length can't be negative.");
    // если требуемый размер массива равен текущему размеру массива. ничего не делаем
    if (newLength == m_length)
        return;

    // Если новый размер равен 0. Очищаем массив и возварщаем пустой
    if (newLength == 0)
    {
        erase();
        return;
    }

    // Предположим, что новая длина newLength как минимум 1.
    // Алгоритм такой: Выделяем память под новый массив.  Затем
    // копируем в новый массив элементы из старого массива.
    // После завершения копирования, стираем старый масив,
    // и перенправляем указатель make m_data на новый массив.

    // Выделяем память под новый массив
    int* data{ new int[newLength] };

    // Надо понять сколько элементов копировать из старого массива в новый
    // Копируем из старого столько элементов, сколько содержится в наименьшем из двух массивов.
    if (m_length > 0)
    {
        int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

                            // Копируем по одному все элементы из старого массива в новый
                            for (int index{ 0 }; index < elementsToCopy; ++index)
                                data[index] = m_data[index];
    }

    // Удаляем старый массив. Он нам больше не нужен
    delete[] m_data;

    // And use the new array instead!  Note that this simply makes m_data point
    // to the same address as the new array we dynamically allocated.  Because
    // data was dynamically allocated, it won't be destroyed when it goes out of scope.
    m_data = data;
    m_length = newLength;
}

void IntArray::insertBefore(int value, int index)
{
    // Проверка допустимости переданного индекса
    //assert(index >= 0 && index <= m_length);
    if (index < 0 || index > m_length) throw BadIndex("Sanity check our index value");//throw std::runtime_error("Sanity check our index value");

    // Создаем новый массив с длиной на 1 элемент больше старого
    int* data{ new int[m_length+1] };

    // Копируем все элементы от 0 до index-1
    for (int before{ 0 }; before < index; ++before)
        data[before] = m_data[before];

    // Вставляем новый элемент value в массив на позицию index
    data[index] = value;

    // Копируем все элементы, идущие после вставленного элемента
    for (int after{ index }; after < m_length; ++after)
        data[after+1] = m_data[after];

    // Наконец, удаляем старый массив и вместо него берем новый
    delete[] m_data;
    m_data = data;
    ++m_length;
}

void IntArray::remove(int index)
{
    // Проверка допустимости переданного индекса
    //assert(index >= 0 && index < m_length);
    if (index < 0 || index >= m_length) throw BadIndex("Sanity check our index value"); //ArrayOutOfRange("Sanity check our index value");

    // Если в мы удаляем единственный элемент в массиве. То можно просто очистить массив и вернуть пустой
    if (m_length == 1)
    {
        erase();
        return;
    }

    // Создаем новый массив с длиной на 1 элемент меньше старого
    int* data{ new int[m_length-1] };

    // Копируем все элементы от 0 до index-1
    for (int before{ 0 }; before  < index; ++before)
        data[before] = m_data[before];

    // Копируем все элементы, идущие после удаленного
    for (int after{ index+1 }; after < m_length; ++after)
        data[after-1] = m_data[after];

    // Наконец, удаляем старый массив и вместо него берем новый
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
