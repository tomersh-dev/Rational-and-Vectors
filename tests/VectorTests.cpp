#include "catch2/catch.hpp"

#include <sstream>

#include "Vector.h"
#include "Rational.h"

TEST_CASE("Vector constructors & basic properties", "[Vector]")
{

    SECTION("Constructor with size & init value")
    {
        Vector v(3, Rational(2, 3));
        REQUIRE(v.dimension() == 3);
        REQUIRE(v[0] == Rational(2, 3));
        REQUIRE(v[1] == Rational(2, 3));
        REQUIRE(v[2] == Rational(2, 3));
    }

    SECTION("Constructor with array")
    {
        Rational arr[] = { Rational(1,2), Rational(2,3), Rational(3,4) };
        Vector v(arr, 3);

        REQUIRE(v.dimension() == 3);
        REQUIRE(v[0] == Rational(1, 2));
        REQUIRE(v[1] == Rational(2, 3));
        REQUIRE(v[2] == Rational(3, 4));
    }
}

TEST_CASE("Deep copy semantics", "[Vector]")
{
    Rational arr[] = { Rational(1,2), Rational(3,4) };
    Vector v1(arr, 2);
    Vector v2 = v1;  // copy constructor

    REQUIRE(v1 == v2);

    // Modify v1 – ensure v2 does not change
    v1[0] = Rational(5, 1);

    REQUIRE(v1[0] == Rational(5, 1));
    REQUIRE(v2[0] == Rational(1, 2));

    // Assignment operator
    Vector v3;
    v3 = v1;
    REQUIRE(v3 == v1);

    v1[1] = Rational(7, 8);
    REQUIRE(v3[1] == Rational(3, 4));
}

TEST_CASE("Unary operators", "[Vector]")
{
    Rational arr[] = { Rational(1,2), Rational(-2,3) };
    Vector v(arr, 2);

    SECTION("Unary + returns identical vector")
    {
        Vector p = +v;
        REQUIRE(p == v);
    }

    SECTION("Unary - negates each element")
    {
        Vector m = -v;
        REQUIRE(m[0] == Rational(-1, 2));
        REQUIRE(m[1] == Rational(2, 3));
    }
}

TEST_CASE("Vector +, -, * (Hadamard), with size mismatch", "[Vector]")
{
    Rational a1[] = { Rational(1,2), Rational(2,3) };
    Rational a2[] = { Rational(3,4) };  // smaller vector

    Vector v1(a1, 2);
    Vector v2(a2, 1);

    SECTION("Addition uses larger dimension, missing entries = 0")
    {
        Vector v = v1 + v2;
        REQUIRE(v.dimension() == 2);
        REQUIRE(v[0] == Rational(1, 2) + Rational(3, 4));
        REQUIRE(v[1] == Rational(2, 3));  // +0
    }

    SECTION("Subtraction")
    {
        Vector v = v1 - v2;
        REQUIRE(v.dimension() == 2);
        REQUIRE(v[0] == Rational(1, 2) - Rational(3, 4));
        REQUIRE(v[1] == Rational(2, 3)); // -0
    }

    SECTION("Hadamard product")
    {
        Vector v = v1 * v2;
        REQUIRE(v.dimension() == 2);
        REQUIRE(v[0] == Rational(1, 2) * Rational(3, 4));
        REQUIRE(v[1] == Rational(0));  // missing term
    }
}

TEST_CASE("Scalar multiplication", "[Vector]")
{
    Rational a[] = { Rational(1,2), Rational(-2,3) };
    Vector v(a, 2);

    Rational s(3, 4);

    SECTION("v * scalar")
    {
        Vector r = v * s;
        REQUIRE(r[0] == Rational(1, 2) * s);
        REQUIRE(r[1] == Rational(-2, 3) * s);
    }

    SECTION("scalar * v")
    {
        Vector r = s * v;
        REQUIRE(r[0] == s * Rational(1, 2));
        REQUIRE(r[1] == s * Rational(-2, 3));
    }

    SECTION("scalar assignment versions")
    {
        Vector v2 = v;
        v2 *= s;

        REQUIRE(v2[0] == Rational(1, 2) * s);
        REQUIRE(v2[1] == Rational(-2, 3) * s);
    }
}

TEST_CASE("Assignment versions +=, -=, *= (Hadamard)", "[Vector]")
{
    Rational a1[] = { Rational(1,2), Rational(2,3) };
    Rational a2[] = { Rational(3,4) };

    Vector v1(a1, 2);
    Vector v2(a2, 1);

    SECTION("Addition with assignment")
    {
        v1 += v2;
        REQUIRE(v1.dimension() == 2);
        REQUIRE(v1[0] == Rational(1, 2) + Rational(3, 4));
        REQUIRE(v1[1] == Rational(2, 3));
    }

    SECTION("Subtraction with assignment")
    {
        v1 -= v2;
        REQUIRE(v1[0] == Rational(1, 2) - Rational(3, 4));
        REQUIRE(v1[1] == Rational(2, 3));
    }

    SECTION("Hadamard with assignment")
    {
        v1 *= v2;
        REQUIRE(v1[0] == Rational(1, 2) * Rational(3, 4));
        REQUIRE(v1[1] == Rational(0));
    }
}

TEST_CASE("Equality and inequality", "[Vector]")
{
    Rational a1[] = { Rational(1,2), Rational(2,3) };
    Rational a2[] = { Rational(1,2), Rational(2,3) };
    Rational a3[] = { Rational(1,2) };

    Vector v1(a1, 2);
    Vector v2(a2, 2);
    Vector v3(a3, 1);

    REQUIRE(v1 == v2);
    REQUIRE(v1 != v3);
}

TEST_CASE("operator[] const and non-const", "[Vector]")
{
    Rational a[] = {
        Rational(1,2),
        Rational(3,4)
    };

    Vector v(a, 2);
    const Vector& cv = v;

    SECTION("non-const index")
    {
        v[0] = Rational(7, 8);
        REQUIRE(v[0] == Rational(7, 8));
    }

    SECTION("const index")
    {
        REQUIRE(cv[1] == Rational(3, 4));
    }
}

TEST_CASE("dot() scalar product", "[Vector]")
{
    Rational a1[] = { Rational(1,2), Rational(2,3) };
    Rational a2[] = { Rational(3,4), Rational(5,6) };

    Vector v1(a1, 2);
    Vector v2(a2, 2);

    SECTION("Normal dot product")
    {
        Rational r = v1.dot(v2);
        REQUIRE(r == Rational(1, 2) * Rational(3, 4) +
            Rational(2, 3) * Rational(5, 6));
    }

    SECTION("Mismatched dimensions")
    {
        Rational a3[] = { Rational(7,8) };
        Vector v3(a3, 1);

        Rational r = v1.dot(v3);
        REQUIRE(r == Rational(1, 2) * Rational(7, 8) + Rational(0)); // second term is 0
    }
}

TEST_CASE("Printing operator <<", "[Vector]")
{
    Rational arr[] = {
        Rational(1,2),
        Rational(-3,4),
        Rational(5,6)
    };

    Vector v(arr, 3);

    std::ostringstream oss;
    oss << v;

    REQUIRE(oss.str() == "1/2 -3/4 5/6");
}
