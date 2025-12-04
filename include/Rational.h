
class Rational {
public:
	Rational(int nummerator = 0, int denominator = 1);
	int numerator() const;
	int denominator() const;
	Rational absValue() const;
	Rational squareValue() const;
	bool dividedBy(const Rational& divisor) const;

	Rational operator+=(const Rational& other);

	Rational operator-=(const Rational& other);

	Rational operator*=(const Rational& other);

	Rational operator/=(const Rational& other);

private:
	int m_numerator;
	int m_denominator;
	void reduceFraction();
	void properSign();
	void makeValid();
	int gcd() const;
};

Rational operator+(const Rational& a, const Rational& b);

Rational operator-(const Rational& a, const Rational& b);

Rational operator*(const Rational& a, const Rational& b);

Rational operator/(const Rational& a, const Rational& b);
