#include "mystring.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

MyString::MyString()
{}

MyString::MyString(const char *str)
{
    *this = str;
}

MyString::MyString(const char *str, double num)
{
    _str = new char[strlen(str) + sizeof (num) * 8 + 1];
    sprintf(_str, str, num);
}

MyString::MyString(long num)
{
    _str = new char[sizeof (num) * 8 + 1];
    sprintf(_str, "%li", num);
}

MyString::MyString(const MyString &str)
{
    *this = str;
}

MyString::MyString(MyString &&str)
{
    _str = str._str;
    str._str = nullptr;
}


const char *MyString::c_str() const
{
    return _str;
}

size_t MyString::length() const
{
    return strlen(_str);
}

MyString MyString::removeBeginTo(const MyString &str , const MyString &defStr) const
{
    const char *begin = strstr(_str, str.c_str());

    if ( begin == nullptr ) return defStr;

    begin += strlen(str.c_str());

    return MyString(begin);
}

MyString MyString::findNum(const MyString &str, const MyString &defStr) const
{
    char *begin = strstr(_str, str.c_str());

    if ( begin == nullptr ) return defStr;

    begin += strlen(str.c_str());
    auto end = begin + 1;

    while ( isdigit(*end) )
    {
        ++end;
    }
    char temp = *end;
    *end = '\0'; //CRUNCH!!!!!!!!!!!!
    MyString result(begin);
    *end = temp;

    return result;
}

long MyString::toLong() const
{
    return atol(_str);
}

MyString MyString::operator +(const MyString &anotherStr) const
{
    auto length = strlen(anotherStr._str) + strlen(this->_str) + 1;
    auto res = new char[length];
    res[0] = '\0';
    strcat(res, _str);
    strcat(res, anotherStr._str);
    MyString result;
    result._str = res;
    return result;
}

void MyString::operator =(const char *anotherStr)
{
    auto length = strlen( anotherStr ) + 1;
    clear();
    _str = new char[length+1];
    strcpy( _str, anotherStr );
}

void MyString::operator =(const MyString &anotherStr)
{
    *this = anotherStr._str;
}

void MyString::clear()
{
    if ( _str != nullptr )
    {
        delete[] _str;
        _str = nullptr;
    }
}

MyString::~MyString()
{
    clear();
}

MyString operator +(const char *oneStr, const MyString &anotherStr)
{
    return MyString(oneStr) + anotherStr;
}

MyString MyString::toUrl() const
{
    MyString result;

    auto len = length();
    char *const tempStr = new char[len*3+1];
    const char *hex = "0123456789abcdef";

    int pos = 0;
    for (auto i = 0; i < len; i++)
    {
        if ( _str[i] == ' '
          || _str[i] == '{'
          || _str[i] == '}'
          || _str[i] == '\\'
          || _str[i] == '"')
        {
            tempStr[pos++] = '%';
            tempStr[pos++] = hex[_str[i] >> 4];
            tempStr[pos++] = hex[_str[i] & 15];
        } else {
            tempStr[pos++] = _str[i];
        }
    }
    tempStr[pos] = '\0';

    result = tempStr;
    delete [] tempStr;
    return result;
}
