#include "Vector.h"
#include <cmath>
#include <ostream>
#include <algorithm>

Vector::Vector(int size, const Rational& defaultValue)
	: m_data(size, defaultValue) { }

Vector::Vector(Rational values[], int size)
	: m_data(values, size) { }

int Vector::dimension() const { return m_data.size(); }

Rational Vector::dot(const Vector& other) const
{
	auto mul = (*this) * other;
	Rational result;
	for (int i = 0; i < mul.dimension(); i++)
		result += mul[i];
	
	return result;
}

double Vector::norm() const
{
	double sum = 0;
	for (int i = 0; i < m_data.size(); i++)
	{
		Rational sqr = m_data[i].squareValue();
		sum += ((double)sqr.numerator() / sqr.denominator());
	}
	return std::sqrt(sum);
}

const Rational Vector::operator[](int index) const { return m_data[index]; }

Rational& Vector::operator[](int index) { return m_data[index]; };

bool Vector::operator==(const Vector& other) const { return m_data == other.m_data; }

std::ostream& operator<<(std::ostream& streem, const Vector& out)
{
	for (int i = 0; i < out.dimension()-1; i++)
		streem << out[i] << ' ';
	streem << out[out.dimension()-1];
	return streem;
}

Vector& operator+=(Vector& left, const Vector& right)
{
	left = left + right;
	return left;
}

Vector& operator-=(Vector& left, const Vector& right)
{
	left = left - right;
	return left;
}

Vector& operator*=(Vector& left, const Vector& right)
{
	left = left * right;
	return left;
}

Vector operator+(const Vector& left, const Vector& right)
{
	int maxSize = std::max(left.dimension(), right.dimension());
	auto result = Vector(maxSize);
	for	(int i = 0; i < maxSize;i++)
	{
		result[i] = (i > left.dimension() ? Rational() : left[i]) + (i > right.dimension() ? Rational() : right[i]);
	}
	return result;
}

Vector operator-(const Vector& left, const Vector& right)
{
	return left + (-right);
}

Vector operator*(const Vector& left, const Vector& right)
{
	int maxSize = std::max(left.dimension(), right.dimension());
	auto result = Vector(maxSize);
	for (int i = 0; i < maxSize; i++)
	{
		result[i] = (i > left.dimension() ? Rational() : left[i]) * (i > right.dimension() ? Rational() : right[i]);
	}
	return result;
}

Vector operator*(Rational scalar, const Vector& vect)
{
	return vect * scalar;
}

Vector operator*(const Vector& vect, Rational scalar)
{
	auto result = Vector(vect);
	for (int i = 0; i < result.dimension(); i++)
		result[i] *= scalar;
	return result;
}

Vector& operator*=(Vector& vect, Rational scalar)
{
	for (int i = 0; i < vect.dimension(); i++)
		vect[i] *= scalar;
	return vect;
}

bool operator!=(const Vector& left, const Vector& right)
{
	return !(left == right);
}

Vector operator-(const Vector& a)
{
	return a * -1;
}

Vector operator+(const Vector& a)
{
	return Vector(a);
}