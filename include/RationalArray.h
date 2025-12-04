#pragma once
#include "Rational.h"
class RationalArray
{
public:
    explicit RationalArray(int size = 0, const Rational& defaultValue = Rational());
    explicit RationalArray(Rational defaultValue[], int size = 0);
    RationalArray(const RationalArray& other);
    ~RationalArray();

    int size() const;
    bool empty() const;

    RationalArray& operator=(const RationalArray& other);

    const Rational operator[](int index) const;
    Rational& operator[](int index);

private:
    Rational *m_data;
    int m_size;
};

RationalArray operator+(const RationalArray& a, const RationalArray& b);

bool operator==(const RationalArray& a, const RationalArray& b);

bool operator!=(const RationalArray& a, const RationalArray& b);