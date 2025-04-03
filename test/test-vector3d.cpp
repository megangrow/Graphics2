#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "vector3d.h"
#include <sstream>

TEST_CASE( "constructors for Vector3D" ) {
    SUBCASE( "default constructor" ) {
	Vector3D a;
	CHECK( a.x == 0.0 );
	CHECK( a.y == 0.0 );
	CHECK( a.z == 0.0 );
    }
    SUBCASE( "constructor with values" ) {
	Vector3D a{1, 2, 3};
	CHECK( a.x == 1.0 );
	CHECK( a.y == 2.0 );
	CHECK( a.z == 3.0 );
    }
}

TEST_CASE( "member operator overloading" ) {
    SUBCASE( "+=" ) {
	Vector3D a{1, 2, 3}, b{-2, 3, 4};
	CHECK( (a += b) == Vector3D{-1, 5, 7} );
    }
    SUBCASE( "-=" ) {
	Vector3D a{1, 2, 3}, b{-2, 3, 4};
	CHECK( (a -= b) == Vector3D{3, -1, -1} );
    }
    SUBCASE( "*=" ) {
	Vector3D a{1, 2, 3}, b{-2, 3, 4};
	CHECK( (a *= b) == Vector3D{-2, 6, 12} );
	CHECK( (b *= 3) == Vector3D{-6, 9, 12} );
    }
    SUBCASE( "/=" ) {
	Vector3D a{1, 2, 3};
	CHECK( (a /= 2) == Vector3D{0.5, 1, 1.5} );
	CHECK_THROWS_AS( (a /= 0), std::overflow_error );
    }
}

TEST_CASE( "equality" ) {
    Vector3D a{1, 2, 3}, b{2, 3, 4};
    SUBCASE( "==" ) {
	CHECK( a == a);
	CHECK_FALSE( a == b);
    }
    SUBCASE( "!=" ) {
	CHECK_FALSE( a != a);
	CHECK( a != b);
    }
}

TEST_CASE( "operator overloading" ) {
    Vector3D a{1, 2, 3}, b{2, 3, 4};
    SUBCASE( "+" ) {
	CHECK( a + b == Vector3D{3, 5, 7} );
    }
    SUBCASE( "-" ) {
	CHECK( a + b == Vector3D{3, 5, 7} );
	CHECK( -a == Vector3D{-1, -2, -3} );
    }
    SUBCASE( "*" ) {
	CHECK( a * b == Vector3D{2, 6, 12} );
	CHECK( a * 3 == Vector3D{3, 6, 9} );
	CHECK( 4 * a == Vector3D{4, 8, 12} );
    }
    SUBCASE( "/" ) {
	CHECK( b / 2 == Vector3D{1, 1.5, 2} );
    }
}

TEST_CASE( "functions" ) {
    SUBCASE( "pow" ) {
	Vector3D a{2, 3, 4};
	CHECK( pow(a, 3) == Vector3D{8, 27, 64} );
	CHECK( pow(a, -1) == Vector3D{1.0/2, 1.0/3, 1.0/4} );
    }
    SUBCASE( "dot" ) {
	Vector3D a{1, 2, 3}, b{2, 3, 4};
	CHECK( dot(a, b) == 20 );
    }
    SUBCASE( "cross" ) {
	// assuming a right-handed coordinate system
	CHECK( cross({1, 0, 0}, {0, 1, 0}) == Vector3D{0, 0, 1} );
    }
    SUBCASE( "length" ) {
	Vector3D a{3, 4, 12};
	CHECK( length(a) == 13 );
    }
    SUBCASE( "unit" ) {
	Vector3D a{1, 1, 1};
	double b{1/std::sqrt(3)};
	CHECK( unit(a) == Vector3D{b, b, b} );
	CHECK_THROWS_AS(unit({0, 0, 0}), std::overflow_error);
    }
}

TEST_CASE( "I/O" ) {
    SUBCASE( "output" ) {
	Vector3D a{1, 2, 3};
	std::stringstream ss;
	ss << a;
	CHECK( ss.str() == "(1 2 3)" );
    }
    SUBCASE( "input" ) {
	Vector3D a;
	std::stringstream ss;
	ss << "(1 2 3)";
	ss >> a;
	CHECK( a == Vector3D{1, 2, 3} );
    }
}
