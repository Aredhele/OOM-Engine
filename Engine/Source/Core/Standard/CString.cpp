/// \file       CString.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    CString
/// \author     Vincent STEHLY--CALISTO

#include <cstdlib>
#include <cstring>
#include "Core/Standard/CString.hpp"
#include <locale>

namespace Oom
{

/* explicit */ CString::CString(uint32_t char_count, char character)
{
    uint32_t pow2 = GetNextPow2(char_count + 1);

    mp_data = static_cast<char*>(malloc(pow2));
    memset(mp_data, character, char_count);

    mp_data[char_count] = '\0';
    m_size              = char_count;
    m_capacity          = pow2;
}

CString::CString(const char* c_string)
{
    auto char_count = static_cast<uint32_t>(strlen(c_string));
    uint32_t pow2   = GetNextPow2(char_count + 1);

    mp_data         = static_cast<char*>(malloc(pow2));
    memcpy(mp_data, c_string, char_count);

    mp_data[char_count] = '\0';
    m_size              = char_count;
    m_capacity          = pow2;
}

CString::CString(const CString& string)
{
    uint32_t pow2   = GetNextPow2(string.Size() + 1);

    mp_data = static_cast<char*>(malloc(pow2));
    memcpy(mp_data, string.mp_data, string.m_size);

    mp_data[string.Size()] = '\0';
    m_size                 = string.m_size;
    m_capacity             = pow2;
}

CString::CString(CString&& string) noexcept
{
    mp_data    = string.mp_data;
    m_size     = string.m_size;
    m_capacity = string.m_capacity;

    string.mp_data    = nullptr;
    string.m_size     = 0;
    string.m_capacity = 0;
}

CString::~CString()
{
    free(mp_data);
}

CString& CString::operator=(const CString& string)
{
    if(m_capacity < string.m_size + 1)
    {
        free(mp_data);
        uint32_t pow2 = GetNextPow2(string.Size() + 1);

        mp_data       = static_cast<char*>(malloc(pow2));
        m_capacity    = pow2;
    }

    memcpy(mp_data, string.mp_data, string.m_size);

    mp_data[string.m_size] = '\0';
    m_size                 = string.m_size;

    return *this;
}

CString &CString::operator=(const char* c_string)
{
    auto char_count = static_cast<uint32_t>(strlen(c_string));

    if(m_capacity < char_count + 1)
    {
        free(mp_data);
        uint32_t pow2 = GetNextPow2(char_count + 1);

        mp_data       = static_cast<char*>(malloc(pow2));
        m_capacity    = pow2;
    }

    memcpy(mp_data, c_string, char_count);

    mp_data[char_count] = '\0';
    m_size              = char_count;

    return *this;
}

CString& CString::operator=(char character)
{
    if(m_capacity < 2)
    {
        free(mp_data);
        uint32_t pow2 = GetNextPow2(2);

        mp_data       = static_cast<char*>(malloc(pow2));
        m_capacity    = pow2;
    }

    mp_data[0] = character;
    mp_data[1] = '\0';
    m_size     = 1;

    return *this;
}

CString& CString::operator=(CString&& string) noexcept
{
    free(mp_data);

    mp_data    = string.mp_data;
    m_size     = string.m_size;
    m_capacity = string.m_capacity;

    string.mp_data    = nullptr;
    string.m_size     = 0;
    string.m_capacity = 0;

    return *this;
}

char* CString::begin()
{
    return mp_data;
}

char* CString::end()
{
    return mp_data + m_size;
}

const char* CString::cbegin() const
{
    return mp_data;
}

const char* CString::cend() const
{
    return mp_data + m_size;
}

uint32_t CString::Size() const
{
    return m_size;
}

uint32_t CString::Capacity() const
{
    return m_capacity;
}

char* CString::Data() noexcept
{
    return mp_data;
}

const char* CString::Data() const noexcept
{
    return mp_data;
}

void CString::Clear()
{
    if(m_size != 0)
    {
        mp_data[0] = '\0';
        m_size = 0;
    }
}

bool CString::Empty()
{
    return m_size == 0;
}

char& CString::operator[](uint32_t position)
{
    return mp_data[position];
}

const char& CString::operator[](uint32_t position) const
{
    return mp_data[position];
}

char& CString::At(uint32_t position)
{
    return mp_data[position];
}

const char& CString::At(uint32_t position) const
{
    return mp_data[position];
}

char& CString::Back()
{
    return mp_data[m_size - 1];
}

const char& CString::Back() const
{
    return mp_data[m_size - 1];
}

char& CString::Front()
{
    return mp_data[0];
}

const char& CString::Front() const
{
    return mp_data[0];
}

CString& CString::operator+=(const CString& string)
{
    return (*this += string.Data());
}

CString& CString::operator+=(const char* c_string)
{
    auto size           =  static_cast<uint32_t>(strlen(c_string));
    uint32_t total_size = m_size + size;

    if(total_size + 1> m_capacity)
    {
        char* p_buffer = mp_data;
        uint32_t pow2 = GetNextPow2(total_size + 1);

        mp_data       = static_cast<char*>(malloc(pow2));
        m_capacity    = pow2;

        memcpy(mp_data, p_buffer, m_size);
        memcpy(&mp_data[m_size], c_string, size);

        free(p_buffer);
    }
    else
    {
        memcpy(&mp_data[m_size], c_string, size);
    }

    m_size         += size;
    mp_data[m_size] = '\0';

    return *this;
}

CString& CString::operator+=(char character)
{
    PushBack(character);
    return *this;
}

void CString::PushBack(char character)
{
    if(m_size + 2 > m_capacity)
    {
        char* p_buffer = mp_data;
        uint32_t pow2 = GetNextPow2(m_size + 2);

        mp_data       = static_cast<char*>(malloc(pow2));
        m_capacity    = pow2;

        memcpy(mp_data, p_buffer, m_size);
        free(p_buffer);
    }

    mp_data[m_size]     = character;
    mp_data[m_size + 1] = '\0';
    m_size              = m_size + 1;
}

void CString::PopBack()
{
    if(m_size >= 1)
    {
        m_size         -= 1;
        mp_data[m_size] = '\0';
    }
}

uint32_t CString::Find(char character, uint32_t pos) const noexcept
{
    for(uint32_t i = pos; i < m_size; ++i)
    {
        if(mp_data[i] == character)
            return i;
    }

    return s_npos;
}

void CString::toUpper()
{
	char *s = Data();
	while (*s) {
		*s = toupper((unsigned char)*s);
		s++;
	}
}

void CString::toLower()
{
	char *s = Data();
	while (*s) {
		*s = tolower((unsigned char)*s);
		s++;
	}
}

	uint32_t CString::GetNextPow2(uint32_t size) const
{
    uint32_t pow2 = 2;
    while(pow2 < size) { pow2 *= 2; }

    return pow2;
}

CString operator+ (const CString& lhs, const CString& rhs)
{
    CString result(lhs);
    result += rhs;

    return result;
}

CString operator+ (CString&& lhs, CString&& rhs)
{
    CString result(static_cast<CString&&>(lhs));
    result += rhs;

    return result;
}

CString operator+ (CString&& lhs, const CString& rhs)
{
    CString result(static_cast<CString&&>(lhs));
    result += rhs;

    return result;
}

CString operator+ (const CString& lhs, const char* rhs)
{
    CString result(lhs);
    result += rhs;

    return result;
}

CString operator+ (CString&& lhs, const char* rhs)
{
    CString result(static_cast<CString&&>(lhs));
    result += rhs;

    return result;
}

CString operator+ (const char* lhs, const CString& rhs)
{
    CString result(lhs);
    result += rhs;

    return result;
}

CString operator+ (const CString& lhs, char rhs)
{
    CString result(lhs);
    result += rhs;

    return result;
}

CString operator+ (CString&& lhs, char rhs)
{
    CString result(static_cast<CString&&>(lhs));
    result += rhs;

    return result;
}

CString operator+ (char lhs, const CString& rhs)
{
    CString result(1 + rhs.Size(), lhs);
    result += rhs;

    return result;
}

bool operator== (const CString& lhs, const CString& rhs)
{
    return (lhs.Size() == rhs.Size()) ? (memcmp(lhs.Data(), rhs.Data(), lhs.Size()) == 0) : false;
}

bool operator== (const char* lhs, const CString& rhs)
{
    return (strlen(lhs) == rhs.Size()) ? (memcmp(lhs, rhs.Data(), rhs.Size())  == 0) : false;
}

bool operator== (const CString& lhs, const char* rhs)
{
    return (lhs.Size() == strlen(rhs)) ? (memcmp(lhs.Data(), rhs, lhs.Size()) == 0) : false;
}

bool operator!= (const CString& lhs, const CString& rhs)
{
    return !(lhs == rhs);
}

bool operator!= (const char* lhs, const CString& rhs)
{
    return !(lhs == rhs);
}

bool operator!= (const CString& lhs, const char* rhs)
{
    return !(lhs == rhs);
}

}

