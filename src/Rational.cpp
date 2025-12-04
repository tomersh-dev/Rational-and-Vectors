#include "Rational.h"
#include <cmath>

Rational::Rational(int numerator, int denominator) {
	m_numerator = numerator;
	m_denominator = (denominator == 0) ? 1 : denominator ;
	makeValid();
}

int Rational::numerator() const { return m_numerator }

int Rational::denominator() const { return m_denominator }

Rational Rational::absValue() const { return Rational(std::abs(m_numerator), m_denominator) }

Rational Rational::squareValue() const { return Rational(m_numerator * m_numerator, m_denominator * m_denominator) }

bool Rational::dividedBy(const Rational& divisor) {
	temp Rational(m_numerator * divisor.m_denominator, m_denominator * divisor.m_numerator);
	return (temp.m_denominator == 1);
}

int Rational::gcd() const {

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
    int gcd = gcd();
    m_numerator /= gcd;
    m_denominator /= gcd;
}

void Rational::properSign() {
    if (m_denominator < 0) {
        m_numerator = -m_numerator;
        m_denominator = -m_denominator;
    }
}

