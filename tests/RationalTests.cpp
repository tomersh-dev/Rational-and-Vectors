#include "catch2/catch.hpp"

#include <sstream>
#include "Rational.h"

TEST_CASE("Rational constructor & normalization", "[Rational]")
{
    SECTION("Default is 0/1")
    {
        Rational r;
        REQUIRE(r.numerator() == 0);
        REQUIRE(r.denominator() == 1);
    }
    
    SECTION("Wrong number 1/0 -> 0/1")
    {
        Rational r(1, 0);
        REQUIRE(r.numerator() == 0);
        REQUIRE(r.denominator() == 1);
    }

    SECTION("Basic reduction")
    {
        Rational r(4, 8);
        REQUIRE(r.numerator() == 1);
        REQUIRE(r.denominator() == 2);
    }

    SECTION("Negative sign always on numerator")
    {
        Rational r1(-4, 8);
        REQUIRE(r1.numerator() == -1);
        REQUIRE(r1.denominator() == 2);

        Rational r2(4, -8);
        REQUIRE(r2.numerator() == -1);
        REQUIRE(r2.denominator() == 2);

        Rational r3(-4, -8);
        REQUIRE(r3.numerator() == 1);
        REQUIRE(r3.denominator() == 2);
    }

    SECTION("Zero numerator always becomes 0/1")
    {
        Rational r(0, 5);
        REQUIRE(r.numerator() == 0);
        REQUIRE(r.denominator() == 1);
    }
}

TEST_CASE("Arithmetic operations", "[Rational]")
{
    Rational a(1, 3);
    Rational b(1, 6);

    SECTION("Addition")
    {
        Rational r = a + b;
        REQUIRE(r == Rational(1, 2));

        a += b;
        REQUIRE(a == Rational(1, 2));
    }

    SECTION("Subtraction")
    {
        Rational r = a - b;
        REQUIRE(r == Rational(1, 6));

        a -= b;
        REQUIRE(a == Rational(1, 6));
    }

    SECTION("Multiplication")
    {
        Rational r = a * b;
        REQUIRE(r == Rational(1, 18));

        a *= b;
        REQUIRE(a == Rational(1, 18));
    }

    SECTION("Division")
    {
        Rational r = a / b;
        REQUIRE(r == Rational(2, 1));

        a /= b;
        REQUIRE(a == Rational(2, 1));
    }

    SECTION("Unary operators")
    {
        Rational x(1, 4);
        REQUIRE(+x == Rational(1, 4));
        REQUIRE(-x == Rational(-1, 4));
    }
}

TEST_CASE("Comparisons", "[Rational]")
{
    Rational a(1, 2);
    Rational b(2, 4);
    Rational c(3, 4);

    SECTION("Equality")
    {
        REQUIRE(a == b);
        REQUIRE(a != c);
    }

    SECTION("Ordering")
    {
        REQUIRE(a < c);
        REQUIRE(c > a);
        REQUIRE(a <= b);
        REQUIRE(b >= a);
    }
}

TEST_CASE("absValue() and dividedBy()", "[Rational]")
{
    SECTION("absValue")
    {
        Rational r(-3, 5);
        REQUIRE(r.absValue() == Rational(3, 5));
    }

    SECTION("dividedBy")
    {
        Rational r1(2, 3);
        Rational r2(1, 3);
        Rational r3(2, 5);

        REQUIRE(r1.dividedBy(r2));
        REQUIRE(!r1.dividedBy(r3));
    }
}

TEST_CASE("Streaming operator <<", "[Rational]")
{
    Rational r(3, 4);
    std::ostringstream oss;

    oss << r;
    REQUIRE(oss.str() == "3/4");

    oss.str("");
    oss << Rational(-5, 6);
    REQUIRE(oss.str() == "-5/6");
}

TEST_CASE("Mixed cases and edge cases", "[Rational]")
{
    SECTION("Chained operations")
    {
        Rational r = Rational(1, 2) + Rational(1, 3) - Rational(1, 6);
        REQUIRE(r == Rational(2, 3));
    }

    SECTION("Nested negatives")
    {
        REQUIRE(Rational(-1, -2) == Rational(1, 2));
        REQUIRE(Rational(1, -2) == Rational(-1, 2));
    }

    SECTION("Large reduction")
    {
        Rational r(150, 300);
        REQUIRE(r == Rational(1, 2));
    }

    SECTION("Division by a rational that becomes negative")
    {
        Rational a(1, 2);
        Rational b(-1, 4);
        REQUIRE(a / b == Rational(-2, 1));
    }
}
