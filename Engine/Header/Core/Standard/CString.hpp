/// \file       CString.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Core/Standard
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_STRING_HPP__
#define OOM_ENGINE_C_STRING_HPP__

#include <cstdint>

namespace Oom
{

class CString
{
public:

	using		 iterator        = char*;
	using  const_iterator        = const char*;
    static const uint32_t s_npos = 0xFFFFFFFF;

public:

    // Constructors
    CString  () = default;
    CString  (uint32_t char_count, char character);             // NOLINT
    CString  (const char* c_string);                            // NOLINT
    CString  (const CString& string);
    CString  (CString&& string) noexcept;
	CString  (iterator begin, iterator end);

    // Destructor
    ~CString ();

    // Assignment operators
    CString& operator= (const CString& string);
    CString& operator= (const char* c_string);
    CString& operator= (char character);
    CString& operator= (CString&& string) noexcept;

    // Iterators
	iterator       begin  ();
	iterator       end    ();
    const_iterator cbegin () const;
	const_iterator cend   () const;

    // Accessors
    uint32_t    Size()      const;
    uint32_t    Capacity () const;
    char*       Data     () noexcept;
    const char* Data     () const noexcept;

    void Clear();
	void Resize(uint32_t size);
    bool Empty();

    // Array operator
    char&       operator[]  (uint32_t position);
    const char& operator[]  (uint32_t position) const;

    // Accessors
    char&       At    (uint32_t position);
    const char& At    (uint32_t position) const;
    char&       Back  ();
    const char& Back  () const;
    char&       Front ();
    const char& Front () const;

    // Concatenates strings
    CString& operator+= (const CString& string);
    CString& operator+= (const char* c_string);
    CString& operator+= (char character);

    // Utils
    void PushBack (char character);
    void PopBack  ();
    uint32_t Find (char character, uint32_t pos = 0) const noexcept;
	void toUpper();
	void toLower();

private:

    uint32_t GetNextPow2(uint32_t size) const;

private:

    char*       mp_data     = nullptr;
    uint32_t    m_size      = 0;
    uint32_t    m_capacity  = 0;
};

CString operator+ (const CString& lhs, const CString& rhs);
CString operator+ (CString&&      lhs, const CString& rhs);
CString operator+ (const CString& lhs, CString&&      rhs);
CString operator+ (const CString& lhs, const char*    rhs);
CString operator+ (CString&&      lhs, const char*    rhs);
CString operator+ (const char*    lhs, const CString& rhs);
CString operator+ (const CString& lhs, char           rhs);
CString operator+ (CString&&      lhs, char           rhs);
CString operator+ (char           lhs, const CString& rhs);

bool operator== (const CString& lhs, const CString& rhs);
bool operator== (const char*    lhs, const CString& rhs);
bool operator== (const CString& lhs, const char*    rhs);
bool operator!= (const CString& lhs, const CString& rhs);
bool operator!= (const char*    lhs, const CString& rhs);
bool operator!= (const CString& lhs, const char*    rhs);

}

#endif // !OOM_ENGINE_C_STRING_HPP__