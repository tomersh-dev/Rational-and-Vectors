#include "Rational.h"
#include <cmath>

Rational::Rational(int numerator, int denominator) {
	m_numerator = numerator;
	m_denominator = (denominator == 0) ? 1 : denominator ;
	makeValid();
}

int Rational::numerator() const { return m_numerator; }

int Rational::denominator() const { return m_denominator; }

Rational Rational::absValue() const { return Rational(std::abs(m_numerator), m_denominator); }

Rational Rational::squareValue() const { return Rational(m_numerator * m_numerator, m_denominator * m_denominator); }

bool Rational::dividedBy(const Rational& divisor) const {
	Rational temp(m_numerator * divisor.m_denominator, m_denominator * divisor.m_numerator);
	return (temp.m_denominator == 1);
}

int Rational::findGCD() const {

    int a = std::abs(m_numerator);
    int b = m_denominator;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

void Rational::reduceFraction() {
    int gcd = findGCD();
    m_numerator /= gcd;
    m_denominator /= gcd;
}

void Rational::properSign() {
    if (m_denominator < 0) {
        m_numerator = -m_numerator;
        m_denominator = -m_denominator;
    }
}

void Rational::makeValid() {
    properSign();
    reduceFraction();
}

Rational& operator+=(Rational& left, const Rational& right)
{
    left = (left + right);
    return left;
}

Rational& operator-=(Rational& left, const Rational& right)
{
    left = (left - right);
    return left;
}

Rational& operator*=(Rational& left, const Rational& right)
{
    left = (left * right);
    return left;
}

Rational& operator/=(Rational& left, const Rational& right)
{
    left = (left / right);
    return left;
}

Rational operator+(const Rational& a, const Rational& b)
{
    return Rational(
        a.numerator()*b.denominator() + b.numerator()*b.denominator(), 
        a.denominator()*b.denominator()
    );
}

Rational operator-(const Rational& a, const Rational& b) { return a + (-b); }

Rational operator*(const Rational& a, const Rational& b) { return Rational(a.numerator() * b.numerator(), a.denominator() * b.denominator()); }

Rational operator/(const Rational& a, const Rational& b) { return a * Rational(b.denominator(), b.numerator()); }

Rational operator+(const Rational& a) { return a; }

Rational operator-(const Rational& a) { return Rational(-a.numerator(), a.denominator()); }

bool operator==(const Rational& left, const Rational& right)
{
    return left.numerator() == right.numerator() && left.denominator() == right.numerator();
}

bool operator!=(const Rational& left, const Rational& right)
{
    return !(left == right);
}