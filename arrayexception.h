#ifndef ARREXCEPTION_H
#define ARREXCEPTION_H
#include <iostream>
#include <string>
#include <exception> // для std::exception

class ArrayException: public std::exception // еще можно от std::runtime_error наследоваться. тогда what можно не переопределять
{
private:
    std::string m_error;

public:
    ArrayException(const std::string& error);

    // Возвращаем std::string в качестве константной строки C-style
//	const char* what() const { return m_error.c_str(); } // до C++11
    const char* what() const noexcept; // C++11 и выше
};


// Классы очен очень короткие пусть будут тут
class BadRange: public ArrayException {
public:
  explicit BadRange (const std::string& error) : ArrayException(error) {};
}; // класс-потомок 1

class BadIndex: public ArrayException {
public:
    explicit BadIndex (const std::string& error) : ArrayException(error) {};
};  // класс-потомок 2

class BadSize : public ArrayException {
public:
  explicit BadSize (const std::string& error) : ArrayException(error) {};
};// класс-потомок 2


#endif // ARREXCEPTION_H
