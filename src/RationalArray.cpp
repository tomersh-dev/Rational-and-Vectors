#include "RationalArray.h"
#include "Rational.h"

RationalArray::RationalArray(int size, const Rational& defaultValue)
    : m_size(size), m_data(nullptr)
{
    if (size <= 0) return;

    m_data = new Rational[size];

    for (int i = 0; i < m_size; i++)
        m_data[i] = defaultValue;
}

RationalArray::RationalArray(Rational values[], int size)
    : m_size(size), m_data(nullptr)
{
    if (size <= 0) return;
    m_data = new Rational[size];

    for (int i = 0; i < m_size; i++)
        m_data[i] = values[i];
}

RationalArray::RationalArray(const RationalArray& other)
    : RationalArray(other.m_data, other.m_size) { }

RationalArray::~RationalArray()
{
    if (m_size > 0)
        delete[] m_data;
}

int RationalArray::size() const
{
    return m_size;
}

bool RationalArray::empty() const
{
    return m_size == 0;
}

RationalArray& RationalArray::operator=(const RationalArray& other)
{
    RationalArray newArray(other);

    delete[] m_data;

    m_data = newArray.m_data;
    m_size = newArray.m_size;

    newArray.m_data = nullptr;
    newArray.m_size = 0;

    return *this;
}

const Rational RationalArray::operator[](int index) const
{
    return m_data[index];
}

Rational& RationalArray::operator[](int index)
{
    return m_data[index];
}

RationalArray operator+(const RationalArray& a, const RationalArray& b)
{
    auto newList = RationalArray(a.size() + b.size());

    int newListIndex = 0;
    for (int i = 0; i < a.size(); i++, newListIndex++)
        newList[newListIndex] = a[i];

    for (int i = 0; i < b.size(); i++, newListIndex++)
        newList[newListIndex] = b[i];

    return newList;
}

bool operator==(const RationalArray& a, const RationalArray& b)
{
    
    if (a.size() != b.size()) return false;

    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i]) 
            return false;
    

    return true;
}

bool operator!=(const RationalArray& a, const RationalArray& b)
{
    return !(a == b);
}