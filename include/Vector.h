#pragma once
#include "RationalArray.h"
#include "Rational.h"


class Vector
{
public:
	explicit Vector(int size = 0, const Rational& defaultValue = Rational());
	explicit Vector(Rational values[], int size = 0);

	int dimension() const;
	Rational dot(const Vector& other) const;
	double norm() const;

	const Rational operator[](int index) const;
	Rational& operator[](int index);
	bool operator==(const Vector& other);
private:
	RationalArray m_data;
}



std::ostream& operator<<(std::ostream& streem, const Vector& out);

Vector& operator+=(Vector& left, const Vector& right);

Vector& operator-=(Vector& left, const Vector& right);

Vector& operator*=(Vector& left, const Vector& right);

Vector operator+(const Vector& left, const Vector& right);

Vector operator-(const Vector& left, const Vector& right);

Vector operator*(const Vector& left, const Vector& right);

Vector operator*(double scalar, const Vector& vect);

Vector operator*(const Vector& vect, double scalar);

bool operator!=(const Vector& left, const Vector& right);

Vector operator-(const Vector& a);

Vector operator+(const Vector& a);