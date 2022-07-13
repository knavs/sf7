#include "arrayexception.h"

ArrayException::ArrayException(const std::string& error)
    : m_error(error)
{
}

const char *ArrayException::what() const noexcept
{
    return m_error.c_str();
}

