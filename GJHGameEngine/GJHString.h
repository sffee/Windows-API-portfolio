#pragma once
#include <iostream>
#include <string>
#include <atlstr.h>

class GJHString
{
public:
    static size_t FINDERROR;

public:
    std::string Str;

public:
    size_t Size() const
    {
        return Str.size();
    }

public:
    std::wstring ConvertWString() const
    {
        return CA2W(Str.c_str()).m_psz;
    }

public:
    GJHString()
    {
        
    }

    GJHString(const std::string& _Text) : Str(_Text)
    {

    }

    GJHString(const char* _Ptr) : Str(_Ptr)
    {
        
    }

    GJHString(const wchar_t* _Ptr) : Str(CW2A(_Ptr).m_psz)
    {

    }

public:
    operator const char* () const
    {
        return Str.c_str();
    }

    bool operator<(const GJHString& _Other) const
    {
        return Str < _Other.Str;
    }

    bool operator>(const GJHString& _Other) const
    {
        return Str > _Other.Str;
    }

    bool operator==(const GJHString& _Other) const
    {
        return Str == _Other.Str;
    }

    bool operator==(const char* _Other) const
    {
        return Str == _Other;
    }

    bool operator!=(const GJHString& _Other) const
    {
        return Str != _Other.Str;
    }

    bool operator!=(const char* _Other) const
    {
        return Str != _Other;
    }

    GJHString operator+(const char* _Text) const
    {
        return Str + _Text;
    }

    GJHString& operator+=(const char* _Text)
    {
        Str += _Text;
        return *this;
    }

    char& operator[](size_t _Index)
    {
        return Str[_Index];
    }

    size_t FirstFind(char _FindChar, size_t _Offset = 0) const
    {
        return Str.find_first_of(_FindChar, _Offset);
    }

    size_t LastFind(char _FindChar, size_t _Offset = FINDERROR) const
    {
        return Str.find_last_of(_FindChar, _Offset);
    }

    GJHString Cut(size_t _Start, size_t _Len) const
    {
        std::string ReturnStr = Str.substr(_Start, _Len);
        return ReturnStr;
    }

    GJHString Upper() const
    {
        std::string Text = Str;

        for (size_t i = 0; i < Text.size(); i++)
        {
            Text[i] = toupper(Text[i]);
        }

        return Text;
    }

    GJHString Lower() const
    {
        std::string Text = Str;

        for (size_t i = 0; i < Text.size(); i++)
        {
            Text[i] = tolower(Text[i]);
        }

        return Text;
    }
};