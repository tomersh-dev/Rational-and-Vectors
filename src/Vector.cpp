#include "Vector.h"
#include <cmath>
#include <ostream>
#include <algorithm>

Vector::Vector(int size, const Rational& defaultValue)
	: m_data(size, defaultValue) { }

Vector::Vector(Rational values[], int size)
	: m_data(values, size) { }

int Vector::dimension() const { return m_data.size() }

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

Rational& Vector::operator[](int index) { return m_data[index] };

bool Vector::operator==(const Vector& other) { return m_data == other.m_data; }

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
	auto res = Vector(maxSize);
	for	(int i = 0; i < maxSize;i++)
	{
		res[i] = (i > left.dimension() ? Rational() : left[i]) + (i > right.dimension() ? Rational() : right[i]);
	}
	return res;
}

Vector operator-(const Vector& left, const Vector& right)
{
	return left + (-right);
}

Vector operator*(const Vector& left, const Vector& right)
{
	int maxSize = std::max(left.dimension(), right.dimension());
	auto res = Vector(maxSize);
	for (int i = 0; i < maxSize; i++)
	{
		res[i] = (i > left.dimension() ? Rational() : left[i]) * (i > right.dimension() ? Rational() : right[i]);
	}
	return res;
}

Vector operator*(double scalar, const Vector& vect)
{
	return vect * scalar;
}

Vector operator*(const Vector& vect, double scalar)
{
	auto res = Vector(vect);
	for (int i = 0; i < maxSize; i++)
		res[i] *= scalar;
	return res;
}

bool operator!=(const Vector& left, const Vector& right);
{
	return !(vect == vect);
}

Vector operator-(const Vector& a)
{
	return a * -1;
}

Vector operator+(const Vector& a)
{
	return Vector(a);
}