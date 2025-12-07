#pragma once
#include <ostream>
class Rational {
public:
	Rational(int nummerator = 0, int denominator = 1);
	int numerator() const;
	int denominator() const;
	Rational absValue() const;
	Rational squareValue() const;
	bool dividedBy(const Rational& divisor) const;



private:
	int m_numerator;
	int m_denominator;
	void reduceFraction();
	void properSign();
	void makeValid();
	int findGCD() const;
};

std::ostream& operator<<(std::ostream& streem, const Rational& out);

Rational& operator+=(Rational& left, const Rational& right);

Rational& operator-=(Rational& left, const Rational& right);

Rational& operator*=(Rational& left, const Rational& right);

Rational& operator/=(Rational& left, const Rational& right);

Rational operator+(const Rational& left, const Rational& right);

Rational operator+(const Rational& a);

Rational operator-(const Rational& left, const Rational& right);

Rational operator-(const Rational& a);

Rational operator*(const Rational& left, const Rational& right);

Rational operator/(const Rational& left, const Rational& right);

bool operator==(const Rational& left, const Rational& right);

bool operator!=(const Rational& left, const Rational& right);

bool operator>(const Rational& left, const Rational& right);

bool operator<(const Rational& left, const Rational& right);

bool operator>=(const Rational& left, const Rational& right);

bool operator<=(const Rational& left, const Rational& right);