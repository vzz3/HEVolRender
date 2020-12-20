#include "../include/catch2/catch.hpp"
#include "../src/math/UFixBigInt.hpp"
#include "../src/math/SFixBigInt.hpp"

#include "../src/math/SArbBigInt.hpp"


#define LONG_TESTS 0

using ppvr::math::UFixBigInt;
using ppvr::math::SFixBigInt;

using ppvr::math::SArbBigInt;

/*
TEST_CASE( "signed infinit big integer to int 64 (UArbBigInt from Word constructor)", "[SArbBigInt]" ) {
	REQUIRE( UArbBigInt::ZERO.toUint64() == 0ull );
	REQUIRE( UArbBigInt(0).toUint64() == 0ull );

	REQUIRE( UArbBigInt::ONE.toUint64() == 1ull );
	REQUIRE( UArbBigInt(1).toUint64() == 1ull );

	REQUIRE( UArbBigInt::TWO.toUint64() == 2ull );
	REQUIRE( UArbBigInt(2).toUint64() == 2ull );

	REQUIRE( UArbBigInt::TEN.toUint64() == 10ull );
	REQUIRE( UArbBigInt(10).toUint64() == 10ull );

	REQUIRE( UArbBigInt(5).toUint64() == 5ull );
	REQUIRE( UArbBigInt(55).toUint64() == 55ull );
	REQUIRE( UArbBigInt(127).toUint64() == 127ull );
	REQUIRE( UArbBigInt(255).toUint64() == 255ull );
}
*/


TEST_CASE( "signed fixed big integer to std:string hex", "[SFBigint]" ) {
	// --- single byte big int creation ---

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0, false).toStringHex() == std::string("0") );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0, true).toStringHex() == std::string("0") );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, false).toStringHex() == std::string("1") );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true).toStringHex() == std::string("-1") );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(216)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(216)>::fromString("1e02bc1e8aa1d63b5b9ccf516f9d67d2 7b3c80b500001cbe991a08", 16), false).toStringHex()     == std::string( "1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(216)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(216)>::fromString("1e02bc1e8aa1d63b5b9ccf516f9d67d27b3c80b500001cbe991a08", 16), true).toStringHex()      == std::string("-1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") );

}

TEST_CASE( "signed fixed big integer to std:string dec", "[SFBigint]" ) {
	// --- single byte big int creation ---

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0, false).toStringDec() == std::string("0") );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0, true).toStringDec() == std::string("0") );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, false).toStringDec() == std::string("1") );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true).toStringDec() == std::string("-1") );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(216)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(216)>::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10), false).toStringDec() == std::string("12345678900000000000000000000000000000000000000000000123456789000") );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(216)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(216)>::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10), true).toStringDec() == std::string("-12345678900000000000000000000000000000000000000000000123456789000") );

}

TEST_CASE( "signed fixed big integer from int64", "[SFBigint]" ) {
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromInt64(0).toInt64() 	==   0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromInt64(-0).toInt64() 	==   0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromInt64(1).toInt64() 	==   1 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromInt64(-1).toInt64() 	==   -1 );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromInt64(-2147483647).toInt64() 	==   -2147483647 ); // 32 bit signed min + 1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromInt64(-2147483648).toInt64() 	==   -2147483648 ); // 32 bit signed min
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromInt64(-2147483649).toInt64() 	==   -2147483649 ); // 32 bit signed min - 1

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromInt64(2147483646).toInt64() 	==   2147483646 ); // 32 bit signed max - 1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromInt64(2147483647).toInt64() 	==   2147483647 ); // 32 bit signed max
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromInt64(2147483648).toInt64() 	==   2147483648 ); // 32 bit signed max + 1

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromInt64(4294967294).toInt64() 	==   4294967294 ); // 32 bit unsigned max - 1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromInt64(4294967295).toInt64() 	==   4294967295 ); // 32 bit unsigned max
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(33)>::fromInt64(4294967296).toInt64() 	==   4294967296 ); // 32 bit unsigned max + 1

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(-9223372036854775807ll).toStringDec() 	==   "-9223372036854775807" ); // 64 bit signed min + 1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(-9223372036854775808ll).toStringDec() 	==   "-9223372036854775808" ); // 64 bit signed min
	//REQUIRE( SArbBigInt::fromInt64(-9223372036854775809).toStringDec() 	==   "-9223372036854775809" ); // 64 bit signed min - 1 // darf nicht funktionieren

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(9223372036854775806).toStringDec() 	==   "9223372036854775806" ); // 64 bit signed max - 1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(9223372036854775807).toStringDec() 	==   "9223372036854775807" ); // 64 bit signed max
	//REQUIRE( SArbBigInt::fromInt64(9223372036854775808).toStringDec() 	==   "9223372036854775808" ); // 64 bit signed max + 1 // darf nicht funktionieren
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(9223372036854775808).toStringDec() 	==   "-9223372036854775808" ); // 64 bit signed max + 1 // ATTENTION unsigned interpreted as signed!

	//REQUIRE( SArbBigInt::fromInt64(18446744073709551614).toStringDec() 	==   "18446744073709551614" ); // 64 bit unsigned max - 1
	//REQUIRE( SArbBigInt::fromInt64(18446744073709551615).toStringDec() 	==   "18446744073709551615" ); // 64 bit unsigned max
	//REQUIRE( SArbBigInt::fromInt64(18446744073709551616).toStringDec() 	==   18446744073709551616 ); // 32 bit unsigned max + 1 // darf nicht funktionieren

	// ATTENTION unsigned interpreted as signed!
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(18446744073709551614).toStringDec() 	==   "-2" ); // 64 bit unsigned max - 1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(18446744073709551615).toStringDec() 	==   "-1" ); // 64 bit unsigned max
}

TEST_CASE( "signed fixed big integer from std:string", "[SFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "", 10).toInt64() 	==   0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "+", 10).toInt64() 	==   0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "-", 10).toInt64() 	==   0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "  ", 10).toInt64() 	==   0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "  +", 10).toInt64() 	==   0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "  -", 10).toInt64() 	==   0 );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "  0", 10).toInt64() 	==   0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( " 1", 10).toInt64() 	==   1 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "  -1", 10).toInt64() 	==  -1 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "   1", 10).toInt64() 	==   1 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "  -123", 10).toInt64() 	==   -123 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "  -80", 16).toInt64() 	==   -128 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( " -81", 16).toInt64() 	==   -129 );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "+2", 10).toInt64() 	==   2 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( " +3", 10).toInt64() 	==   3 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( " -4", 10).toInt64() 	==   -4 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "  5", 10).toInt64() 	==   5 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "-6", 10).toInt64() 	==   -6 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "+7", 10).toInt64() 	==   7 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( " -8", 10).toInt64() 	==   -8 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( " 9", 10).toInt64() 	==   9 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("+10", 10).toInt64() 	==  10 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-77", 10).toInt64() 	==  -77 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(" -127", 10).toInt64() 	== -127 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(" 128", 10).toInt64() 	== 128 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-255", 10).toInt64() 	== -255 );


	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-0", 16).toInt64() 	==  -0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-1", 16).toInt64() 	==  -1 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-2", 16).toInt64() 	==  -2 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-3", 16).toInt64() 	==  -3 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-4", 16).toInt64() 	==  -4 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-5", 16).toInt64() 	==  -5 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-6", 16).toInt64() 	==  -6 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-7", 16).toInt64() 	==  -7 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-8", 16).toInt64() 	==  -8 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-9", 16).toInt64() 	==  -9 );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-a", 16).toInt64() 	== -10 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-b", 16).toInt64() 	== -11 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-c", 16).toInt64() 	== -12 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-d", 16).toInt64() 	== -13 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-e", 16).toInt64() 	== -14 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-f", 16).toInt64() 	== -15 );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("+A", 16).toInt64() 	== 10 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("+B", 16).toInt64() 	== 11 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("+C", 16).toInt64() 	== 12 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("+D", 16).toInt64() 	== 13 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("+E", 16).toInt64() 	== 14 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("+F", 16).toInt64() 	== 15 );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("+7F", 16).toInt64()	== 127 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-80", 16).toInt64()	== -128 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-FF", 16).toInt64()	== -255 );

	// leading zeros
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(  " -01", 10).toInt64() 	==   -1 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( " -001", 10).toInt64() 	==   -1 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("  +0255", 10).toInt64() 	==   255 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(9)>::fromString("  +0256", 10).toInt64() 	==   256 );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(  " -00", 16).toInt64() 	==   0 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(  "-01", 16).toInt64() 	==   -1 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(  " -0f", 16).toInt64() 	==   -15 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("+000A", 16).toInt64() 	==   10 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("-00ff", 16).toInt64() 	==   -255 );

	// 2 Bytes (16 bit)
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("-256", 10).toInt64() == -256 ); // 2^16
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("+0100", 16).toInt64() == 256 );

	// 4 Bytes (32 bit)
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("+FFFFFFFF", 16).toInt64() == +0xFFFFFFFF );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("-FFFFFFFF", 16).toInt64() == -0xFFFFFFFFll );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("-4294967295", 10).toInt64() == -0xFFFFFFFFll ); // 2^32 - 1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("-01234567", 16).toInt64() == -0x01234567ll );

	// 8 Bytes (64 bit)
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("+4294967296", 10).toInt64() == 0x0100000000 ); // 2^32
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("+0100000000", 16).toInt64() == 0x0100000000 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("-4294967297", 10).toInt64() == -0x0100000001 ); // 2^32 + 1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("-0100000001", 16).toInt64() == -0x0100000001 );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("-0123456789ABCDEF", 16).toInt64() == -0x0123456789ABCDEF );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("-fedcba9876543210", 16).toInt64() == -0xFEDCBA9876543210 );


	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("+18446744073709551615", 10).toInt64() 	== 0xFFFFFFFFFFFFFFFFull ); // 2^64 - 1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("+FFFFFFFFFFFFFFFF", 16).toInt64() 		== 0xFFFFFFFFFFFFFFFFull );

	// --- use 65 bit conversion for big int reference creation ---
	// this uses also the BIG int == operator, therefore a failed test could als be a problem of the == operator implementation
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-18446744073709551616", 10)    == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1)) ); // 2^64
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000000", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1)) ); // 2^64
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000001", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x01)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000002", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x02)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000003", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x03)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000004", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x04)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000005", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x05)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000006", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x06)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000007", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x07)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000008", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x08)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-010000000000000009", 16)   	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x09)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-01000000000000000A", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0A)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-01000000000000000B", 16)      == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0B)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-01000000000000000C", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0C)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-01000000000000000D", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0D)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-01000000000000000E", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0E)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-01000000000000000F", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0F)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-0100000000000000Fe", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0xFE)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("-0100000000000000Ff", 16) 	 == (SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0xFF)) );


	// ---- ignore blank
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString(" - 01 F3 86 9C 69 BB 1C 01", 16) 	== SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(-0x01F3869C69BB1C01) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString(" + 140 604 019 725 507 585", 10) 	== SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(0x01F3869C69BB1C01) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString(" - 123 456 789 000 000 321", 10) 	== SFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromInt64(-123456789000000321) );
}

TEST_CASE( "signed fixed big integer comparisons", "[SFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) != SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) != SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1)) );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) == SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) <= SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) >= SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0)) );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) < SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1)) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) > SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0)) );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0), false) == SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0), true) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1), false) != SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1), true) );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, false) >  SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true ) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, false) >= SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true ) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true ) <  SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, false) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true ) <= SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, false) );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true) >  SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2, true) ); // -1 >  -2
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true) >= SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2, true) ); // -1 >= -2
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2, true) >= SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2, true) ); // -2 >= -2
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2, true) <  SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true) ); // -2 <  -1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2, true) <= SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true) ); // -2 <= -1
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2, true) <= SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2, true) ); // -2 <= -2

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1, false) > SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), true) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1, false) >= SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), true) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1, true) < SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), false) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1, true) <= SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), false) );

	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), false) > SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1, true) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), false) >= SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1, true) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), true) < SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1, false) );
	REQUIRE( SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), true) <= SFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1, false) );
}
