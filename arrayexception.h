#ifndef ARREXCEPTION_H
#define ARREXCEPTION_H
#include <iostream>
#include <string>
#include <exception> // ��� std::exception

class ArrayException: public std::exception // ��� ����� �� std::runtime_error �������������. ����� what ����� �� ��������������
{
private:
    std::string m_error;

public:
    ArrayException(const std::string& error);

    // ���������� std::string � �������� ����������� ������ C-style
//	const char* what() const { return m_error.c_str(); } // �� C++11
    const char* what() const noexcept; // C++11 � ����
};


// ������ ���� ����� �������� ����� ����� ���
class BadRange: public ArrayException {
public:
  explicit BadRange (const std::string& error) : ArrayException(error) {};
}; // �����-������� 1

class BadIndex: public ArrayException {
public:
    explicit BadIndex (const std::string& error) : ArrayException(error) {};
};  // �����-������� 2

class BadSize : public ArrayException {
public:
  explicit BadSize (const std::string& error) : ArrayException(error) {};
};// �����-������� 2


#endif // ARREXCEPTION_H
