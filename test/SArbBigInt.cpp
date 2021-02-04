#include "../include/catch2/catch.hpp"
#include "../src/math/SArbBigInt.hpp"

#define LONG_TESTS 0

using ppvr::math::UArbBigInt;
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


TEST_CASE( "signed infinit big integer to std:string hex", "[SABigint]" ) {
	// --- single byte big int creation ---

	REQUIRE( SArbBigInt(0, false).toStringHex() == std::string("0") );
	REQUIRE( SArbBigInt(0, true).toStringHex() == std::string("0") );
	REQUIRE( SArbBigInt(1, false).toStringHex() == std::string("1") );
	REQUIRE( SArbBigInt(1, true).toStringHex() == std::string("-1") );

	REQUIRE( SArbBigInt(UArbBigInt::fromString("1e02bc1e8aa1d63b5b9ccf516f9d67d27b3c80b500001cbe991a08", 16), false).toStringHex()     == std::string( "1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1e02bc1e8aa1d63b5b9ccf516f9d67d27b3c80b500001cbe991a08", 16), true).toStringHex()      == std::string("-1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") );

}

TEST_CASE( "signed infinit big integer to std:string dec", "[SABigint]" ) {
	// --- single byte big int creation ---

	REQUIRE( SArbBigInt(0, false).toStringDec() == std::string("0") );
	REQUIRE( SArbBigInt(0, true).toStringDec() == std::string("0") );
	REQUIRE( SArbBigInt(1, false).toStringDec() == std::string("1") );
	REQUIRE( SArbBigInt(1, true).toStringDec() == std::string("-1") );

	REQUIRE( SArbBigInt(UArbBigInt::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10), false).toStringDec() == std::string("12345678900000000000000000000000000000000000000000000123456789000") );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10), true).toStringDec() == std::string("-12345678900000000000000000000000000000000000000000000123456789000") );

}

TEST_CASE( "signed infinit big integer from int64", "[SABigint]" ) {
	REQUIRE( SArbBigInt::fromInt64(0).toInt64() 	==   0 );
	REQUIRE( SArbBigInt::fromInt64(-0).toInt64() 	==   0 );
	REQUIRE( SArbBigInt::fromInt64(1).toInt64() 	==   1 );
	REQUIRE( SArbBigInt::fromInt64(-1).toInt64() 	==   -1 );

	REQUIRE( SArbBigInt::fromInt64(-2147483647).toInt64() 	==   -2147483647 ); // 32 bit signed min + 1
	REQUIRE( SArbBigInt::fromInt64(-2147483648).toInt64() 	==   -2147483648 ); // 32 bit signed min
	REQUIRE( SArbBigInt::fromInt64(-2147483649).toInt64() 	==   -2147483649 ); // 32 bit signed min - 1

	REQUIRE( SArbBigInt::fromInt64(2147483646).toInt64() 	==   2147483646 ); // 32 bit signed max - 1
	REQUIRE( SArbBigInt::fromInt64(2147483647).toInt64() 	==   2147483647 ); // 32 bit signed max
	REQUIRE( SArbBigInt::fromInt64(2147483648).toInt64() 	==   2147483648 ); // 32 bit signed max + 1

	REQUIRE( SArbBigInt::fromInt64(4294967294).toInt64() 	==   4294967294 ); // 32 bit unsigned max - 1
	REQUIRE( SArbBigInt::fromInt64(4294967295).toInt64() 	==   4294967295 ); // 32 bit unsigned max
	REQUIRE( SArbBigInt::fromInt64(4294967296).toInt64() 	==   4294967296 ); // 32 bit unsigned max + 1

	REQUIRE( SArbBigInt::fromInt64(-9223372036854775807ll).toStringDec() 	==   "-9223372036854775807" ); // 64 bit signed min + 1
	REQUIRE( SArbBigInt::fromInt64(-9223372036854775808ll).toStringDec() 	==   "-9223372036854775808" ); // 64 bit signed min
	//REQUIRE( SArbBigInt::fromInt64(-9223372036854775809).toStringDec() 	==   "-9223372036854775809" ); // 64 bit signed min - 1 // darf nicht funktionieren

	REQUIRE( SArbBigInt::fromInt64(9223372036854775806).toStringDec() 	==   "9223372036854775806" ); // 64 bit signed max - 1
	REQUIRE( SArbBigInt::fromInt64(9223372036854775807).toStringDec() 	==   "9223372036854775807" ); // 64 bit signed max
	//REQUIRE( SArbBigInt::fromInt64(9223372036854775808).toStringDec() 	==   "9223372036854775808" ); // 64 bit signed max + 1 // darf nicht funktionieren
	REQUIRE( SArbBigInt::fromInt64(9223372036854775808).toStringDec() 	==   "-9223372036854775808" ); // 64 bit signed max + 1 // ATTENTION unsigned interpreted as signed!

	//REQUIRE( SArbBigInt::fromInt64(18446744073709551614).toStringDec() 	==   "18446744073709551614" ); // 64 bit unsigned max - 1
	//REQUIRE( SArbBigInt::fromInt64(18446744073709551615).toStringDec() 	==   "18446744073709551615" ); // 64 bit unsigned max
	//REQUIRE( SArbBigInt::fromInt64(18446744073709551616).toStringDec() 	==   18446744073709551616 ); // 32 bit unsigned max + 1 // darf nicht funktionieren

	// ATTENTION unsigned interpreted as signed!
	REQUIRE( SArbBigInt::fromInt64(18446744073709551614).toStringDec() 	==   "-2" ); // 64 bit unsigned max - 1
	REQUIRE( SArbBigInt::fromInt64(18446744073709551615).toStringDec() 	==   "-1" ); // 64 bit unsigned max
}

TEST_CASE( "signed infinit big integer from std:string", "[SABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( SArbBigInt::fromString( "", 10).toInt64() 	==   0 );
	REQUIRE( SArbBigInt::fromString( "+", 10).toInt64() 	==   0 );
	REQUIRE( SArbBigInt::fromString( "-", 10).toInt64() 	==   0 );
	REQUIRE( SArbBigInt::fromString( "  ", 10).toInt64() 	==   0 );
	REQUIRE( SArbBigInt::fromString( "  +", 10).toInt64() 	==   0 );
	REQUIRE( SArbBigInt::fromString( "  -", 10).toInt64() 	==   0 );

	REQUIRE( SArbBigInt::fromString( "  0", 10).toInt64() 	==   0 );
	REQUIRE( SArbBigInt::fromString( " 1", 10).toInt64() 	==   1 );
	REQUIRE( SArbBigInt::fromString( "  -1", 10).toInt64() 	==  -1 );
	REQUIRE( SArbBigInt::fromString( "   1", 10).toInt64() 	==   1 );
	REQUIRE( SArbBigInt::fromString( "  -123", 10).toInt64() 	==   -123 );
	REQUIRE( SArbBigInt::fromString( "  -80", 16).toInt64() 	==   -128 );
	REQUIRE( SArbBigInt::fromString( " -81", 16).toInt64() 	==   -129 );

	REQUIRE( SArbBigInt::fromString( "+2", 10).toInt64() 	==   2 );
	REQUIRE( SArbBigInt::fromString( " +3", 10).toInt64() 	==   3 );
	REQUIRE( SArbBigInt::fromString( " -4", 10).toInt64() 	==   -4 );
	REQUIRE( SArbBigInt::fromString( "  5", 10).toInt64() 	==   5 );
	REQUIRE( SArbBigInt::fromString( "-6", 10).toInt64() 	==   -6 );
	REQUIRE( SArbBigInt::fromString( "+7", 10).toInt64() 	==   7 );
	REQUIRE( SArbBigInt::fromString( " -8", 10).toInt64() 	==   -8 );
	REQUIRE( SArbBigInt::fromString( " 9", 10).toInt64() 	==   9 );
	REQUIRE( SArbBigInt::fromString("+10", 10).toInt64() 	==  10 );
	REQUIRE( SArbBigInt::fromString("-77", 10).toInt64() 	==  -77 );
	REQUIRE( SArbBigInt::fromString(" -127", 10).toInt64() 	== -127 );
	REQUIRE( SArbBigInt::fromString(" 128", 10).toInt64() 	== 128 );
	REQUIRE( SArbBigInt::fromString("-255", 10).toInt64() 	== -255 );


	REQUIRE( SArbBigInt::fromString("-0", 16).toInt64() 	==  -0 );
	REQUIRE( SArbBigInt::fromString("-1", 16).toInt64() 	==  -1 );
	REQUIRE( SArbBigInt::fromString("-2", 16).toInt64() 	==  -2 );
	REQUIRE( SArbBigInt::fromString("-3", 16).toInt64() 	==  -3 );
	REQUIRE( SArbBigInt::fromString("-4", 16).toInt64() 	==  -4 );
	REQUIRE( SArbBigInt::fromString("-5", 16).toInt64() 	==  -5 );
	REQUIRE( SArbBigInt::fromString("-6", 16).toInt64() 	==  -6 );
	REQUIRE( SArbBigInt::fromString("-7", 16).toInt64() 	==  -7 );
	REQUIRE( SArbBigInt::fromString("-8", 16).toInt64() 	==  -8 );
	REQUIRE( SArbBigInt::fromString("-9", 16).toInt64() 	==  -9 );

	REQUIRE( SArbBigInt::fromString("-a", 16).toInt64() 	== -10 );
	REQUIRE( SArbBigInt::fromString("-b", 16).toInt64() 	== -11 );
	REQUIRE( SArbBigInt::fromString("-c", 16).toInt64() 	== -12 );
	REQUIRE( SArbBigInt::fromString("-d", 16).toInt64() 	== -13 );
	REQUIRE( SArbBigInt::fromString("-e", 16).toInt64() 	== -14 );
	REQUIRE( SArbBigInt::fromString("-f", 16).toInt64() 	== -15 );

	REQUIRE( SArbBigInt::fromString("+A", 16).toInt64() 	== 10 );
	REQUIRE( SArbBigInt::fromString("+B", 16).toInt64() 	== 11 );
	REQUIRE( SArbBigInt::fromString("+C", 16).toInt64() 	== 12 );
	REQUIRE( SArbBigInt::fromString("+D", 16).toInt64() 	== 13 );
	REQUIRE( SArbBigInt::fromString("+E", 16).toInt64() 	== 14 );
	REQUIRE( SArbBigInt::fromString("+F", 16).toInt64() 	== 15 );

	REQUIRE( SArbBigInt::fromString("+7F", 16).toInt64()	== 127 );
	REQUIRE( SArbBigInt::fromString("-80", 16).toInt64()	== -128 );
	REQUIRE( SArbBigInt::fromString("-FF", 16).toInt64()	== -255 );

	// leading zeros
	REQUIRE( SArbBigInt::fromString(  " -01", 10).toInt64() 	==   -1 );
	REQUIRE( SArbBigInt::fromString( " -001", 10).toInt64() 	==   -1 );
	REQUIRE( SArbBigInt::fromString("  +0256", 10).toInt64() 	==   256 );

	REQUIRE( SArbBigInt::fromString(  " -00", 16).toInt64() 	==   0 );
	REQUIRE( SArbBigInt::fromString(  "-01", 16).toInt64() 	==   -1 );
	REQUIRE( SArbBigInt::fromString(  " -0f", 16).toInt64() 	==   -15 );
	REQUIRE( SArbBigInt::fromString("+000A", 16).toInt64() 	==   10 );
	REQUIRE( SArbBigInt::fromString("-00ff", 16).toInt64() 	==   -255 );

	// 2 Bytes (16 bit)
	REQUIRE( SArbBigInt::fromString("-256", 10).toInt64() == -256 ); // 2^16
	REQUIRE( SArbBigInt::fromString("+0100", 16).toInt64() == 256 );

	// 4 Bytes (32 bit)
	REQUIRE( SArbBigInt::fromString("+FFFFFFFF", 16).toInt64() == +0xFFFFFFFF );
	REQUIRE( SArbBigInt::fromString("-FFFFFFFF", 16).toInt64() == -0xFFFFFFFFll );
	REQUIRE( SArbBigInt::fromString("-4294967295", 10).toInt64() == -0xFFFFFFFFll ); // 2^32 - 1
	REQUIRE( SArbBigInt::fromString("-01234567", 16).toInt64() == -0x01234567ll );

	// 8 Bytes (64 bit)
	REQUIRE( SArbBigInt::fromString("+4294967296", 10).toInt64() == 0x0100000000 ); // 2^32
	REQUIRE( SArbBigInt::fromString("+0100000000", 16).toInt64() == 0x0100000000 );
	REQUIRE( SArbBigInt::fromString("-4294967297", 10).toInt64() == -0x0100000001 ); // 2^32 + 1
	REQUIRE( SArbBigInt::fromString("-0100000001", 16).toInt64() == -0x0100000001 );
	REQUIRE( SArbBigInt::fromString("-0123456789ABCDEF", 16).toInt64() == -0x0123456789ABCDEF );
	REQUIRE( SArbBigInt::fromString("-fedcba9876543210", 16).toInt64() == -0xFEDCBA9876543210 );


	REQUIRE( SArbBigInt::fromString("+18446744073709551615", 10).toInt64() 	== 0xFFFFFFFFFFFFFFFFull ); // 2^64 - 1
	REQUIRE( SArbBigInt::fromString("+FFFFFFFFFFFFFFFF", 16).toInt64() 		== 0xFFFFFFFFFFFFFFFFull );

	// --- use 65 bit conversion for big int reference creation ---
	// this uses also the BIG int == operator, therefore a failed test could als be a problem of the == operator implementation
	REQUIRE( SArbBigInt::fromString("-18446744073709551616", 10) == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1)) ); // 2^64
	REQUIRE( SArbBigInt::fromString("-010000000000000000", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1)) ); // 2^64
	REQUIRE( SArbBigInt::fromString("-010000000000000001", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x01)) );
	REQUIRE( SArbBigInt::fromString("-010000000000000002", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x02)) );
	REQUIRE( SArbBigInt::fromString("-010000000000000003", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x03)) );
	REQUIRE( SArbBigInt::fromString("-010000000000000004", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x04)) );
	REQUIRE( SArbBigInt::fromString("-010000000000000005", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x05)) );
	REQUIRE( SArbBigInt::fromString("-010000000000000006", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x06)) );
	REQUIRE( SArbBigInt::fromString("-010000000000000007", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x07)) );
	REQUIRE( SArbBigInt::fromString("-010000000000000008", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x08)) );
	REQUIRE( SArbBigInt::fromString("-010000000000000009", 16)   == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x09)) );
	REQUIRE( SArbBigInt::fromString("-01000000000000000A", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x0A)) );
	REQUIRE( SArbBigInt::fromString("-01000000000000000B", 16)   == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x0B)) );
	REQUIRE( SArbBigInt::fromString("-01000000000000000C", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x0C)) );
	REQUIRE( SArbBigInt::fromString("-01000000000000000D", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x0D)) );
	REQUIRE( SArbBigInt::fromString("-01000000000000000E", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x0E)) );
	REQUIRE( SArbBigInt::fromString("-01000000000000000F", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0x0F)) );
	REQUIRE( SArbBigInt::fromString("-0100000000000000Fe", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0xFE)) );
	REQUIRE( SArbBigInt::fromString("-0100000000000000Ff", 16) 	 == (SArbBigInt(UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull), true) - SArbBigInt(1) - UArbBigInt(0xFF)) );


	// ---- ignore blank
	REQUIRE( SArbBigInt::fromString(" - 01 F3 86 9C 69 BB 1C 01", 16) 	== SArbBigInt::fromInt64(-0x01F3869C69BB1C01) );
	REQUIRE( SArbBigInt::fromString(" + 140 604 019 725 507 585", 10) 	== SArbBigInt::fromInt64(0x01F3869C69BB1C01) );
	REQUIRE( SArbBigInt::fromString(" - 123 456 789 000 000 321", 10) 	== SArbBigInt::fromInt64(-123456789000000321) );
}



TEST_CASE( "signed infinit big integer comparisons", "[SABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( SArbBigInt(1) != SArbBigInt(UArbBigInt::ZERO) );
	REQUIRE( SArbBigInt(0) != SArbBigInt(UArbBigInt::ONE) );

	REQUIRE( SArbBigInt(0) == SArbBigInt(UArbBigInt::ZERO) );
	REQUIRE( SArbBigInt(0) <= SArbBigInt(UArbBigInt::ZERO) );
	REQUIRE( SArbBigInt(0) >= SArbBigInt(UArbBigInt::ZERO) );

	REQUIRE( SArbBigInt(0) < SArbBigInt(UArbBigInt::ONE) );
	REQUIRE( SArbBigInt(1) > SArbBigInt(UArbBigInt::ZERO) );

	REQUIRE( SArbBigInt(UArbBigInt::ZERO, false) == SArbBigInt(UArbBigInt::ZERO, true) );
	REQUIRE( SArbBigInt(UArbBigInt::ONE, false) != SArbBigInt(UArbBigInt::ONE, true) );

	REQUIRE( SArbBigInt(1, false) >  SArbBigInt(1, true ) );
	REQUIRE( SArbBigInt(1, false) >= SArbBigInt(1, true ) );
	REQUIRE( SArbBigInt(1, true ) <  SArbBigInt(1, false) );
	REQUIRE( SArbBigInt(1, true ) <= SArbBigInt(1, false) );

	REQUIRE( SArbBigInt(1, true) >  SArbBigInt(2, true) ); // -1 >  -2
	REQUIRE( SArbBigInt(1, true) >= SArbBigInt(2, true) ); // -1 >= -2
	REQUIRE( SArbBigInt(2, true) >= SArbBigInt(2, true) ); // -2 >= -2
	REQUIRE( SArbBigInt(2, true) <  SArbBigInt(1, true) ); // -2 <  -1
	REQUIRE( SArbBigInt(2, true) <= SArbBigInt(1, true) ); // -2 <= -1
	REQUIRE( SArbBigInt(2, true) <= SArbBigInt(2, true) ); // -2 <= -2

	REQUIRE( SArbBigInt(1, false) > SArbBigInt(UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), true) );
	REQUIRE( SArbBigInt(1, false) >= SArbBigInt(UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), true) );
	REQUIRE( SArbBigInt(1, true) < SArbBigInt(UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), false) );
	REQUIRE( SArbBigInt(1, true) <= SArbBigInt(UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), false) );

	REQUIRE( SArbBigInt(UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), false) > SArbBigInt(1, true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), false) >= SArbBigInt(1, true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), true) < SArbBigInt(1, false) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16), true) <= SArbBigInt(1, false) );
}

TEST_CASE( "signed infinit big integer shift left", "[SABigint]" ) {

	// 1 Byte (8bit)
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) <<  0 == SArbBigInt(UArbBigInt::fromString("1", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) <<  1 == SArbBigInt(UArbBigInt::fromString("10", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) <<  2 == SArbBigInt(UArbBigInt::fromString("100", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) <<  3 == SArbBigInt(UArbBigInt::fromString("1000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) <<  4 == SArbBigInt(UArbBigInt::fromString("10000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) <<  5 == SArbBigInt(UArbBigInt::fromString("100000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) <<  6 == SArbBigInt(UArbBigInt::fromString("1000000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) <<  7 == SArbBigInt(UArbBigInt::fromString("10000000", 2), true) );


	// 9 Byte (72bit)
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) << 64 == SArbBigInt(UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) << 65 == SArbBigInt(UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) << 66 == SArbBigInt(UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) << 67 == SArbBigInt(UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) << 68 == SArbBigInt(UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) << 69 == SArbBigInt(UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 000000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) << 70 == SArbBigInt(UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("1", 2), true) << 71 == SArbBigInt(UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2), true) );

	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) <<  0 == SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) <<  1 == SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) <<  2 == SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) <<  3 == SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) <<  4 == SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) <<  5 == SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) <<  6 == SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 000000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) <<  7 == SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0000000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), true) <<  8 == SArbBigInt(UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000000", 2), true) );



}

TEST_CASE( "signed infinit big integer shift right", "[SABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  0 == SArbBigInt(UArbBigInt::fromString("10000000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  1 == SArbBigInt(UArbBigInt::fromString( "1000000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  2 == SArbBigInt(UArbBigInt::fromString(  "100000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  3 == SArbBigInt(UArbBigInt::fromString(   "10000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  4 == SArbBigInt(UArbBigInt::fromString(    "1000", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  5 == SArbBigInt(UArbBigInt::fromString(     "100", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  6 == SArbBigInt(UArbBigInt::fromString(      "10", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  7 == SArbBigInt(UArbBigInt::fromString(       "1", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  8 == SArbBigInt(UArbBigInt::fromString(       "0", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >>  9 == SArbBigInt(UArbBigInt::fromString(       "0", 2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10000000", 2), true) >> 16 == SArbBigInt(UArbBigInt::fromString(       "0", 2), true) );



	// 9 Byte (72bit)
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   0 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                      1), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   1 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                      2), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   2 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                      4), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   3 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                      8), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   4 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                     16), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   5 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                     32), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   6 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                     64), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   7 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                    128), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   8 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                    256), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>   9 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                    512), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  10 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                   1024), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  11 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                   2048), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  12 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                   4096), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  13 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                   8192), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  14 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                  16384), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  15 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                  32768), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  16 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                  65536), true) );

	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  63 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(    9223372036854775808ull), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  64 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString(  "18446744073709551616", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  65 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString(  "36893488147419103232", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  66 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString(  "73786976294838206464", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  67 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString( "147573952589676412928", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  68 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString( "295147905179352825856", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  69 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString( "590295810358705651712", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  70 == SArbBigInt(UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString("1180591620717411303424", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  71 == SArbBigInt(UArbBigInt::fromString("1", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  72 == SArbBigInt(UArbBigInt::fromString("0", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >>  73 == SArbBigInt(UArbBigInt::fromString("0", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >> 127 == SArbBigInt(UArbBigInt::fromString("0", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >> 128 == SArbBigInt(UArbBigInt::fromString("0", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), true) >> 129 == SArbBigInt(UArbBigInt::fromString("0", 10), true) );
}

TEST_CASE( "signed infinit big integer addition", "[SABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (SArbBigInt(  0, true)  + SArbBigInt(  0, false)).toInt64()	==   0 );
	REQUIRE( (SArbBigInt(  1, false) + SArbBigInt(  0, true)).toInt64()	    ==   1 );
	REQUIRE( (SArbBigInt(  1, true) + SArbBigInt(  0, true)).toInt64()	    ==  -1 );
	REQUIRE( (SArbBigInt(  0, true)  + SArbBigInt(  1, false)).toInt64()	==   1 );
	REQUIRE( (SArbBigInt(  0, true)  + SArbBigInt(  1, true)).toInt64()		==  -1 );
	REQUIRE( (SArbBigInt(  1, false) + SArbBigInt(  1, false)).toInt64()	==   2 );
	REQUIRE( (SArbBigInt(  1, false) + SArbBigInt(  1, true)).toInt64()		==   0 );
	REQUIRE( (SArbBigInt(  1, true) + SArbBigInt(  1, false)).toInt64()		==   0 );
	REQUIRE( (SArbBigInt(  1, true) + SArbBigInt(  1, true)).toInt64()		==  -2 );

	REQUIRE( (SArbBigInt(  2, false) + SArbBigInt(  1, false)).toInt64()	==   3 );
	REQUIRE( (SArbBigInt(  2, false) + SArbBigInt(  1, true)).toInt64()		==   1 );
	REQUIRE( (SArbBigInt(  2, true) + SArbBigInt(  1, false)).toInt64()		==  -1 );
	REQUIRE( (SArbBigInt(  2, true) + SArbBigInt(  1, true)).toInt64()		==  -3 );
}

TEST_CASE( "signed infinit big integer subtraction", "[SABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (SArbBigInt(  0, false) - SArbBigInt(  0, false)).toInt64() ==  0 ); //  0 -  0 =  0
	REQUIRE( (SArbBigInt(  0, true ) - SArbBigInt(  0, true )).toInt64() ==  0 ); //  0 -  0 =  0
	REQUIRE( (SArbBigInt(  0, true ) - SArbBigInt(  0, false)).toInt64() ==  0 ); //  0 -  0 =  0
	REQUIRE( (SArbBigInt(  0, false) - SArbBigInt(  0, true )).toInt64() ==  0 ); //  0 -  0 =  0

	REQUIRE( (SArbBigInt(  1, false) - SArbBigInt(  0, false)).toInt64() ==  1 ); // +1 -  0 = +1
	REQUIRE( (SArbBigInt(  1, true ) - SArbBigInt(  0, false)).toInt64() ==  -1 ); // -1 -  0 = -1
	REQUIRE( (SArbBigInt(  1, false) - SArbBigInt(  1, false)).toInt64() ==  0 ); // +1 - +1 =  0
	REQUIRE( (SArbBigInt(  0, false) - SArbBigInt(  1, false)).toInt64() == -1 ); //  0 - +1 = -1
	REQUIRE( (SArbBigInt(  0, false) - SArbBigInt(  1, true )).toInt64() ==  1 ); //  0 - -1 = +1

	REQUIRE( (SArbBigInt(  1, false) - SArbBigInt(  1, false)).toInt64() ==  0 ); // +1 - +1 =  0
	REQUIRE( (SArbBigInt(  1, true ) - SArbBigInt(  1, true )).toInt64() ==  0 ); // -1 - -1 =  0
	REQUIRE( (SArbBigInt(  1, false) - SArbBigInt(  1, true )).toInt64() ==  2 ); // +1 - -1 = +2
	REQUIRE( (SArbBigInt(  1, true ) - SArbBigInt(  1, false)).toInt64() == -2 ); // -1 - +1 = -2

	REQUIRE( (SArbBigInt(  2, false) - SArbBigInt(  1, false)).toInt64() ==  1 ); // +2 - +1 = +1
	REQUIRE( (SArbBigInt(  2, true ) - SArbBigInt(  1, true )).toInt64() == -1 ); // -2 - -1 = -1
	REQUIRE( (SArbBigInt(  2, false) - SArbBigInt(  1, true )).toInt64() ==  3 ); // +2 - -1 = +3
	REQUIRE( (SArbBigInt(  2, true ) - SArbBigInt(  1, false)).toInt64() == -3 ); // -2 - +1 = -3

	REQUIRE( (SArbBigInt(  1, false) - SArbBigInt(  2, false)).toInt64() == -1 ); // +1 - +2 = -1
	REQUIRE( (SArbBigInt(  1, true ) - SArbBigInt(  2, true )).toInt64() ==  1 ); // -1 - -2 = +1
	REQUIRE( (SArbBigInt(  1, false) - SArbBigInt(  2, true )).toInt64() ==  3 ); // +1 - -2 = +3
	REQUIRE( (SArbBigInt(  1, true ) - SArbBigInt(  2, false)).toInt64() == -3 ); // -1 - +2 = -3

}

TEST_CASE( "signed infinit big integer multiplication", "[SABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (SArbBigInt(  0, false) * SArbBigInt(0, false)).toInt64() ==    0 );
	REQUIRE( (SArbBigInt(  0, true ) * SArbBigInt(0, false)).toInt64() ==    0 );
	REQUIRE( (SArbBigInt(  0, false) * SArbBigInt(0, true )).toInt64() ==    0 );
	REQUIRE( (SArbBigInt(  0, true ) * SArbBigInt(0, true )).toInt64() ==    0 );
	REQUIRE( (SArbBigInt(  1, true ) * SArbBigInt(0, true )).toInt64() ==    0 );
	REQUIRE( (SArbBigInt(  1, false) * SArbBigInt(0, true )).toInt64() ==    0 );
	REQUIRE( (SArbBigInt(  0, true ) * SArbBigInt(0, false)).toInt64() ==    0 );
	REQUIRE( (SArbBigInt(  0, false) * SArbBigInt(0, true )).toInt64() ==    0 );

	REQUIRE( (SArbBigInt(  1, false) * SArbBigInt(1, false)).toInt64() ==    1 );
	REQUIRE( (SArbBigInt(  1, false) * SArbBigInt(1, true )).toInt64() ==   -1 );
	REQUIRE( (SArbBigInt(  1, true ) * SArbBigInt(1, false)).toInt64() ==   -1 );
	REQUIRE( (SArbBigInt(  1, true ) * SArbBigInt(1, true )).toInt64() ==    1 );

	REQUIRE( (SArbBigInt(  2, true ) * SArbBigInt(1, false)).toInt64() ==   -2 );
	REQUIRE( (SArbBigInt(  1, false) * SArbBigInt(2, true )).toInt64() ==   -2 );
	REQUIRE( (SArbBigInt( 10, true ) * SArbBigInt(0, true )).toInt64() ==    0 );
	REQUIRE( (SArbBigInt( 11, true ) * SArbBigInt(2, true )).toInt64() ==   22 );
	REQUIRE( (SArbBigInt(127, false) * SArbBigInt(2, true )).toInt64() == -254 );


	// -------
	REQUIRE( SArbBigInt(UArbBigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16), true) *  SArbBigInt(UArbBigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16), false) == SArbBigInt(UArbBigInt::fromString("121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16), true) *  SArbBigInt(UArbBigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16), true) == SArbBigInt(UArbBigInt::fromString("121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16), false) );

	REQUIRE( SArbBigInt(UArbBigInt::fromString("123456789000000000000000000000000000001234567890", 10), false) *  SArbBigInt(UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10), true) == SArbBigInt(UArbBigInt::fromString("121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10), true) );
	REQUIRE( SArbBigInt(UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10), false) *  SArbBigInt(UArbBigInt::fromString("123456789000000000000000000000000000001234567890", 10), false) == SArbBigInt(UArbBigInt::fromString("121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10), false) );
}


TEST_CASE( "signed infinit big integer division", "[SABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (SArbBigInt(  0, false) / SArbBigInt(  1, false)).toInt64() ==   0 );
	REQUIRE( (SArbBigInt(  0, true ) / SArbBigInt(  1, true )).toInt64() ==   0 );
	REQUIRE( (SArbBigInt(  1, false) / SArbBigInt(  1, false)).toInt64() ==   1 );
	REQUIRE( (SArbBigInt(  1, true ) / SArbBigInt(  1, true )).toInt64() ==   1 );
	REQUIRE( (SArbBigInt(  1, false) / SArbBigInt(  1, true )).toInt64() ==  -1 );
	REQUIRE( (SArbBigInt(  1, true ) / SArbBigInt(  1, false)).toInt64() ==  -1 );


	// ------
	REQUIRE( SArbBigInt(UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10), true) / SArbBigInt(UArbBigInt::fromString("1", 10), false) == SArbBigInt(UArbBigInt::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10), true) );

	REQUIRE( SArbBigInt(UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10), false) / SArbBigInt(UArbBigInt::fromString("2", 10), true) == SArbBigInt(UArbBigInt::fromString("3282327327325825708273258273273258263263232825825739394992080780749242493932813447459093582582732732572788", 10), true) );

	REQUIRE( SArbBigInt(UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10), true) / SArbBigInt(UArbBigInt::fromString("5555555555555544455555555555555555444441122235654445554547555", 10), true) == SArbBigInt(UArbBigInt::fromString("1181637837837299615890772977303005548172635842", 10), false));


	REQUIRE( SArbBigInt(UArbBigInt::fromString( "121212121121212454564757645640000000000000000000546424465744466464313145643", 10), false) / SArbBigInt(UArbBigInt::fromString("46464644515442612", 10), false) == SArbBigInt(UArbBigInt::fromString("2608695759652855584042902602291341403871593244214364153233", 10), false) );

}

TEST_CASE( "signed infinit big integer modulor", "[SABigint]" ) {
	// 1 Byte (8bit)

	REQUIRE( (SArbBigInt(  0, false) % SArbBigInt(  1, false)).toInt64() ==   0 );
	REQUIRE( (SArbBigInt(  1, false) % SArbBigInt(  1, true )).toInt64() ==   0 );

	REQUIRE( (SArbBigInt(  1, false) % SArbBigInt(  3, false)).toInt64() ==   1 ); // +1 mod +3 = +1
	REQUIRE( (SArbBigInt(  1, true ) % SArbBigInt(  3, true )).toInt64() ==  -1 ); // -1 mod -3 = -1
	REQUIRE( (SArbBigInt(  1, true ) % SArbBigInt(  3, false)).toInt64() ==   2 ); // -1 mod +3 = +2
	REQUIRE( (SArbBigInt(  1, false) % SArbBigInt(  3, true )).toInt64() ==  -2 ); // +1 mod -3 = -2

	REQUIRE( (SArbBigInt(  1, false) % SArbBigInt(  5, false)).toInt64() ==   1 ); // +1 mod +5 = +1
	REQUIRE( (SArbBigInt(  1, true ) % SArbBigInt(  5, true )).toInt64() ==  -1 ); // -1 mod -5 = -1
	REQUIRE( (SArbBigInt(  1, true ) % SArbBigInt(  5, false)).toInt64() ==   4 ); // -1 mod +5 = +4
	REQUIRE( (SArbBigInt(  1, false) % SArbBigInt(  5, true )).toInt64() ==  -4 ); // +1 mod -5 = -4

	REQUIRE( (SArbBigInt(  4, false) % SArbBigInt(  5, false)).toInt64() ==   4 ); // +4 mod +5 = +4
	REQUIRE( (SArbBigInt(  4, true ) % SArbBigInt(  5, true )).toInt64() ==  -4 ); // -4 mod -5 = -4
	REQUIRE( (SArbBigInt(  4, true ) % SArbBigInt(  5, false)).toInt64() ==   1 ); // -4 mod +5 = +1
	REQUIRE( (SArbBigInt(  4, false) % SArbBigInt(  5, true )).toInt64() ==  -1 ); // +4 mod -5 = -1

	REQUIRE( (SArbBigInt(UArbBigInt::fromUint64(1050505100004), false) % SArbBigInt(  5, false)).toInt64() ==   4 ); // +4 mod +5 = +4
	REQUIRE( (SArbBigInt(UArbBigInt::fromUint64(1050505100004), true ) % SArbBigInt(  5, true )).toInt64() ==  -4 ); // -4 mod -5 = -4
	REQUIRE( (SArbBigInt(UArbBigInt::fromUint64(1050505100004), true ) % SArbBigInt(  5, false)).toInt64() ==   1 ); // -4 mod +5 = +1
	REQUIRE( (SArbBigInt(UArbBigInt::fromUint64(1050505100004), false) % SArbBigInt(  5, true )).toInt64() ==  -1 ); // +4 mod -5 = -1
}

TEST_CASE( "signed infinit big integer pow", "[SABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( SArbBigInt(  1, false).pow(SArbBigInt(  1, false)).toInt64() ==   1 ); // 1^1 = 1
	REQUIRE( SArbBigInt(  1, true ).pow(SArbBigInt(  1, false)).toInt64() ==  -1 ); // -1^1 = -1
	REQUIRE( SArbBigInt(  1, true ).pow(SArbBigInt(  0, false)).toInt64() ==   1 ); // -1^0 = 1
	REQUIRE( SArbBigInt(  1, true ).pow(SArbBigInt(  2, false)).toInt64() ==   1 ); // -1^2 = 1
	REQUIRE( SArbBigInt(  1, true ).pow(SArbBigInt(  3, false)).toInt64() ==  -1 ); // -1^3 = -1
	REQUIRE( SArbBigInt(  0, false).pow(SArbBigInt(  3, false)).toInt64() ==   0 ); // 0^3 = 0
	REQUIRE( SArbBigInt(  3, true ).pow(SArbBigInt(  0, false)).toInt64() ==   1 ); // -3^0 = 1
	REQUIRE( SArbBigInt(255, true ).pow(SArbBigInt(  0, false)).toInt64() ==   1 ); // -255^0 = 1
	REQUIRE( SArbBigInt(255, true ).pow(SArbBigInt(  1, false)).toInt64() ==  -255 ); // -255^1 = 1


	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(0)).toInt64() ==   1 );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(1)) == SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(2)) == SArbBigInt::fromString("+1524048626526185117008148645329708998795770321794318911442256140455458946053172210513801777413097237329246447244122385285308414454789711324787960475901495579519924778756", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(3)) == SArbBigInt::fromString("-1881474063392538580104293111393515179649632793959103295994811562361294554161939745982608133564565542204073242684988356858761198894560865302229744629701298307382732414852446913292026698808738732944827521756186090834642278871507135064538602803625789936904", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(4)) == SArbBigInt::fromString("+2322724216016351285472707124797887713981534093719739103213407334702107425041932730777326153711532379822978430798408976244316601438139655559996863723159199445623538286148496267102069962655433997187047023578211999563638238190873223997008007371192667094663558359643750680318859643251894423390770637182150347047660358392496015012475548907536", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(5)) == SArbBigInt::fromString("-2867457962158038971853938647659375320115494383219896161741583092210829444699615500326588552418737089216037940156999920949940166545191462082581253155295134695870831145921714817833094876533390847748267009204859527832933060930612590727989929106335206340916340073313189287861119834506233261329926851146364423475764872904013979979647627788807185431063573845274690387283341162568066853325074114840393511798145094976543399611424", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(6)) == SArbBigInt::fromString("+3539944651218830283540237184943231733526400651356915543005999830870728064470946236962840236630958805963468880528581970518426253453126552935135702339291798727869826342947189921425668475204474360928826722707549964601043918911967378559821737176530807786999546527891889398340508787606662886034686369292655165825645593194777876820396404402099390250401340029154647740647755879072938227342165972233945850036459828750018220652089900824625252564384949798192695376327532441052506514246293241314988128954312301105216", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(7)) == SArbBigInt::fromString("-4370145368848532993242523075480569474139689185243537323461489922215230490555285155220171557274942547946391227642834796084203294700211008420494777946537074472184785618953558877240196071108329207824554743163383909448668325710116607092261566917692365671156479943140409928293640801157769626295637371165926498441822931984045867370978011530469809936350130402824887833172879161880272854103993910122813147049672068271585034130216078042298280565291016527870287491535160333187558206060681978142740974783641780486905910766479698398585528176367347217326798941738259976825918154594987947097719570108544", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(8)) == SArbBigInt::fromString("+5395047783668773709460639056224185760889235717278209951617981537996864826581460683682501318938815681656151958366140465272884649876381694772498596841934270041178306976885452204765063226273182513141163415617476121267278772677860029973492021040065556863907996371801937962087527374769987283177425267845426325078540447496795491526579513442194482548092077099751401641305494953304352311309669493975681079008283809834498665401746908842008129396834776449030813934294217884594751428876570388384142266037241163723638366407733503102721783079433521192695271104586599752841392843737198696981062031279116702499649000416708580359920953881420098099346685016780778222606258624322683077591296", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(9)) == SArbBigInt::fromString("-6660314047113375362717118830937150418894822047689175393373261671094594020566478309787317394536511654440334145396014118250585775607229382517821857691572311721610361814315339092248604034789677002480899646574438926664785599408420949268895302251058514364940634764862382757544044760638210705868384389235211642594541458339214544495817772551070071638986276284136919611246439790071468861836483776797120826186998385040118047655817351174172012988433608066340201003365144512395679567507777521535751903610199604821667817269481414854081548331738516698573839760290854730756066914126892758698199224637074055449072973410012335191441628122431795002240207292069084514744712983684809263796595352722062614488551975275543914901720954495344443353023118414301445927792170105291264", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(10)) == SArbBigInt::fromString("+8222315164743533660322716869205426863298595939614360305442998688209230822741081065880621484469343806415355099455827992366204650030477782349786805802611371198385552114729607612922493857084859636592884607302472143286667576151286304509748792169775990414683086310499759210086314636846142836598831338179359936823353371796102561138300730509971405941785043312353445877831136983874954344159228211618775469143483738566408548893667340467692018161874545230032443789619494305274302301113989109668836113826465977227815031287792805790862002225986391995444892842504718408666055595037262539997469969697387246472169537858751674998655549656461006006174519707063523399279679397216139896950840488719823220059762423870515397663615757747330968399275746884748859378061652915318561679597724441030415446783066798052540826374335278428786048844155232349343754191307776", 10) );

	REQUIRE( SArbBigInt::fromString("-1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(127)) == SArbBigInt::fromString("-417277835567150141191109395931676669187596598594742769231298337489746577103940594588352572819875934610526087127658594429760591231603023165051763326238472146198980522690073560006071408899372813173449415394677024908310339914206830566820031822815124820686693258703460257053244419949289360746368526154134448101668461547772048449299120018317194753884121404398161188985217076863186914235426474539187446142336386468315114037214801138088855013799049008692643528381930269961079215631734139042611824145905382240310073973983746820887774595753225789255022583623162441701935732603711545026850197372302346606879848800177504385828135364061678557349387488138918799117824516874669204542202901527680118580550969167637842098859754043320213594232734001632531319572757386071000052950546265173009335276197520016604657601476229286434993501237620365479171667863321139635277429695266722311393010611957573361279901289818416661244581797657682292845737905630278426423202455921969854049211651821695606246661023362704358230735341708228264366729249169629910766808077041314223516757988463342443687693413231416424808769327751525874623157435845329380530288320983746909904173441404714849158297418216032876913173859078445999830039314003930254745526729141954782794743513011321848306159109988703088679370241825935853689955810342947822290578755684619545570153606580829765982307625611688943340451956795638277822881777861057244991073084190216934533065780101820546633052394827139327410843036782416179279638927478241842774591016364203372412918124278561377856629474996672629949350106305048024930696486441731965475642356502651101076986950356437233749650759466214388370820889872652107919375892308853070128821878672910156126496617183716059808432047003806625996571266499060792862574247722303472260310839753308041439373475352888596392778389288484650154437440542569183176515081591034896765441696795354790628886184669972971835646732985444582066853748377153325955782345712146077886438746357634366225834742144105922751245438211152572778897173976180512146099034187488738454574152676518764070733023948611028006369688677472966973318429365961721754274161853649952430142465390483145746711165695335996070657097083073218167728874229672173711005980071950486217087677293646824454017597593425796694991084402981903334914397529070851794903061661033496963208276735066887865892889097829500177924939839852787038603269817450527233053402338677436141517302897480874179039475916747356814327531858051368858225008127571754260734040215584634901659191052978352277098848768713959010342724790150588333408521267646707331014317004506024731906889387828176715367698314885846744321747608495962065083561868837372150971105918957696356041654809086753936158957260152667612158649353051473515225688067801184926374666063627900787504356089883282207738585833469163156160762059179067068920198373741654277443861486824578063189339207222648527716484114861992810688756711994604166704650234165238876378047055820615347228179052403676809812033836132252548943960319194809289334401089339262853158447723627007332264683028823494101985993106640572711963402994489913861438140485716117378873333940586987171954529368689111100697342087233641653793028912107250061640845562425050733583752905750219974478955230184131045399922136262521411230619969831329035765864786684488386974975653623844664017741980781265311928393180196371696939538444105208466859570023970138572124446745811557319707171888015882252804477838860202217293144134361851368922712664549445534382005591992873547660244288487454948255212880744061237528549522414831037097857662162912272463993932257076428335162986631591776121069444259346979192441863438520789075094752598011302119769223877507035606135386127303475943851897872203440772697916188433585022801850971620477807686646091059987468287863559804023967769493850749915230275551969947260415081733248651727769968024888011726663764885227220023181910208084949165889227905437069677943829350162352606590388363684458557202532297814054152869512470428709528487961704231797578066749363572254340581062829356649074003667034366807720961796014805775883509412046585166371298370808687468619421738988358569408337124360463646761561195862695914068110450432650854655545225751148056069986748600967634632907302905566873500127570946429759631200089692653221281806907648892496190923105578585222605259468065234664658581125937056333426711552287358750171590862998020893390909379866646311065617444377881996963747668440270405673968740647191571230463137171083462070227738521526426354279635233939189082027518271273601587549475510971050435909738930314655938616730567882060722248350486984236994478294613285717471697904955130991005111482197450678273996024645237646782314802273748046837125914695079780298903191609123337480910823418897178726443669854130280335963283585713140022944625201291906839679477308536089414231983969177906313393124740143896583710562046640134184287695675822622730889929110812874561417090230457863804108388711965333582842408373424575610315904447120826288098548933414806132273100069525122893921091824843107451025110596471135646826657916345300577233165130194444049863693946029305758298902585792574341730054343568122779225956907751934864052437190818673123041650363282633011530407411057296414728491695756521985483511010243327181905240771213765368692656340176761711010839172087882066532121755754213764820555156656666839601047232072469120100583928426345764673634552296051401936251897143751670081916891785026800630730607721578778942351632316110800357925457891179181491903523711834958945091559047146056263242215299410930482709179179931728246319335395872361648709503472793672822445333121406180825851160606745816372327262339810753734381854790335239896077167009351750423888113937652296150740528923137239370956702281054491932633303587289318554588930634475928758595458531331660436196074187581967859910607392936572123387273380719469894545425375502817736371875270891399569530316157875220353604980526617509049072798283257554301225112959647728693671839547857110374769987091743484709191343897149755061913588907710823397882306198066142660145328982007478441822848523654583266917111146437079671338480666940165722091120945352315509496229352761678445150283169381179570999987991746795629714673158863871206425365759831898771740129681610057945264153479006472598081407783087132760318359864487031157975104608111778367890361710457231241831999846232952487736787035250203288217485604776336810011419997031495780637454183396805870775610813964917116341138794600696151282552497959367026824594806576578644984738562350329920898708954416375110571898561757905963819851107301020134058148807561800680414587007255364735911780427540643576612792055267234456917539471194821090827127118642486323120101019864587389233257557223684602134690894074668025646573007189310030101077223330888138737880189931876192876960443638933109944223095185105859967349762741690903135292121794301815662528263494280307282399736707142923807633854456718345931179289564555070051945006012528012626066892315193773224284773135906837010477314965037634592951368920033673228283597326971902949991162818135314019347199088225299951678530082350231775668442104591008448498438499352503053787556975144080751552681186441917422242000792600537284341975461535733922856677620428801401222757127279097255139472973493706813189713270356512035705536849597282567969728521699914284416337704221894724249488165135923499310463291964286442668397187893829150171866864625711513597326607106613707535659436717436517557068492549810119715216443113441481670436510062409318112364989154172658485257192210170219771674376612743151993655077846908146282364083295273041649523599742404038503988732731773192835172154375583016278143694133672254584349109121116617052128750057334193012337639398652795888992787804314307899586947485073963164938120003418885225351892552806285865832346824671479941163365895729999464882733938645776847846699316746439572406956331609192776170132179768462405715823669823786205685907877153224154920247264875862260228557185017943585447984755716552669486483834741763186435791198464080373100155220381034705182202505679472182509619655245873601178775467090559895167751889548734259267905589166060552044288438788241000401970009693733081572536061513742012487291606550434288071555100171109101896738751286222902951353279163688579760905687117860851335909110205725185275279798312348633965169773838547750743928786845984334189620508161943707661820919468028846370657982521929344770694275234499358955572713293150774986334986472600808787020913036817406073774961958607887507261453830046387641256558134836398505717187039067115892353362641733283316033309993399155198602301567146255339598628314452859903174983546925142887576725241103262689974794122822977898130345481971316967454410782835259182281511481502948859158030021053916856397026463114456538766098663001207141460578238569661583891590228243438810916707535545025260379408033005564558717739034101697043366067352840574362832443043606605900525922300562434061926334152502597886892440399451195298851618027288897586582951839166193144411555212587940196275808060553248213999870744849770958017005538690386016359702688131466561710093339469339137832648986803648788524233449705612741164130080481813622115067493893737001315611168328755629815151332165384422422314276256826835280343066002773675656653354929362703826363076654296222380129180285809320088328161546598069443389803959754118113914293763498254116281464179901530203146703395824885665346107736911743669323991130701270287215484567435138220267331024966575243378761793939809176516094231793643839018632142197154629798663921140333950884913186047396659666153463921419918641277582508532842180695467316290425125829831947705098305929736666071543418647510201477763834524945364753947200866684857391438487689235146855497715263799232266230974923610682698013178966722769425931342669905221895945606291968588879824675821110894679454203004151400994585556208760120091813545930832176300287702268654356598564146262745419956445256642247365376210391523353854029543933772073156546727797254013917885970942185558001928269211304053670224275191036931163385779974792858865530144244932676496868140493357768671189432400623586821802421767056676639928357617034267843659209954162375614084833029579548372577531813186281727667224378916660791614302698071252063181175765365639962872422299308867377646477535427988183701185984316993396520279736987061839131776333115019948956975228152965514517938817218714364896404323124677848936031034963531477221158176833491080254184204201092578106804419690412761126731879037153928103751398883897317338145827124656958585880821956545002573264386022206020246786677755818450928912081006850713187609503663165518916599019849328973155510112022579091833292278798515480624669951820706547959817585853851375289196055965398139088607903744", 10) );


	//REQUIRE( UArbBigInt::fromString("321", 10).pow(UArbBigInt::fromString("721", 10)) == UArbBigInt::fromString("", 10)
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433567268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(  0)) == SArbBigInt::fromString("1", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433567268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(  1)) == SArbBigInt::fromString("-1234523643567098765433567268387411043985640123642389767832457568567546743234", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433567268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(  2)) == SArbBigInt::fromString("1524048626526185117009300887066646984801000635652102594542843496634376890037090347989840702629834785285308414454789711324787960475901495579519924778756", 10) );
	REQUIRE( SArbBigInt::fromString("-1234523643567098765433567268387411043985640123642389767832457568567546743234", 10).pow(SArbBigInt(  3)) == SArbBigInt::fromString("-1881474063392538580106426815894547327171770148415566976156576321426526570237551650380671167672400988508650560208292536988242351239777537818079498416359650350849044405399679921756186090834642278871507135064538602803625789936904", 10) );
	
	REQUIRE( SArbBigInt(  0).pow(SArbBigInt::fromString("1234523643567098765433567268387411043985640123642389767832457568567546743234", 10)).toInt64() ==   0 );
 
}

TEST_CASE( "signed infinit big integer sqrt", "[SABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( SArbBigInt(  0, false).sqrt().toInt64() ==   0 );
	REQUIRE( SArbBigInt(  0, true ).sqrt().toInt64() ==   0 );
	REQUIRE( SArbBigInt(  1, false).sqrt().toInt64() ==   1 );
	REQUIRE_THROWS( SArbBigInt(  1, true ).sqrt().toInt64() ==   1 ); // sqr(-1) => exception
	REQUIRE( SArbBigInt(  2, false).sqrt().toInt64() ==   1 );
	REQUIRE( SArbBigInt(  3, false).sqrt().toInt64() ==   1 );
	REQUIRE( SArbBigInt( 19, false).sqrt().toInt64() ==   4 );
	REQUIRE( SArbBigInt( 20, false).sqrt().toInt64() ==   4 );

	REQUIRE( SArbBigInt( 25, false).sqrt().toInt64() ==   5 );
	REQUIRE( SArbBigInt( 79, false).sqrt().toInt64() ==   8);
	REQUIRE( SArbBigInt(127, false).sqrt().toInt64() ==   11);
	REQUIRE( SArbBigInt(143, false).sqrt().toInt64() ==   11);
	REQUIRE( SArbBigInt(144, false).sqrt().toInt64() ==   12);
	REQUIRE( SArbBigInt(145, false).sqrt().toInt64() ==   12);
	REQUIRE( SArbBigInt(255, false).sqrt().toInt64() ==   15);

	// 2 Byte (16bit)
	REQUIRE( SArbBigInt::fromInt64(  256).sqrt().toInt64() ==   16);
	REQUIRE( SArbBigInt::fromInt64(16128).sqrt().toInt64() ==   126);
	REQUIRE( SArbBigInt::fromInt64(16129).sqrt().toInt64() ==   127);
	REQUIRE( SArbBigInt::fromInt64(16130).sqrt().toInt64() ==   127);

	// 4 Byte (32bit)
	REQUIRE( SArbBigInt::fromString("10 00 00 00", 16).sqrt() == SArbBigInt::fromString("40 00", 16) );
	REQUIRE( SArbBigInt::fromString("01 23 cd ef", 16).sqrt() == SArbBigInt::fromString("11 15", 16) );
	REQUIRE( SArbBigInt::fromString("ff ff ff ff", 16).sqrt() == SArbBigInt::fromString("ff ff", 16) );

	// 8 Byte (64bit)
	REQUIRE( SArbBigInt::fromString("10 00 00 00 00 00 00 00", 16).sqrt() == SArbBigInt::fromString("40 00 00 00", 16) );
	REQUIRE( SArbBigInt::fromString("01 23 45 67 89 ab cd ef", 16).sqrt() == SArbBigInt::fromString("11 11 11 11", 16) );
	REQUIRE( SArbBigInt::fromString("ff ff ff ff ff ff ff ff", 16).sqrt() == SArbBigInt::fromString("ff ff ff ff", 16) );

	// 16 Byte (128bit)
	REQUIRE( SArbBigInt::fromString("0d f8 45 84 5b 4a 35 e4 89 0d e0 00 9f", 16).sqrt() == SArbBigInt::fromString("03 bc d4 ba db 37 87", 16) );
	REQUIRE( SArbBigInt::fromString("c7 d8 56 0d f8 45 84 5b 4a 35 e4 89 0d e0 00 9f", 16).sqrt() == SArbBigInt::fromString("e2 2f be f3 b5 70 46 1d", 16) );

	// ------
	REQUIRE( SArbBigInt::fromString("1524048626526185117008148645329708998795770321794318911442256140455458946053172210513801777413097237329246447244122385285308414454789711324787960475901495579519924778756", 10).sqrt() == UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10) );
	
	REQUIRE_THROWS( SArbBigInt::fromString("-1524048626526185117008148645329708998795770321794318911442256140455458946053172210513801777413097237329246447244122385285308414454789711324787960475901495579519924778756", 10).sqrt() ); //can not claculate sqrt from negative number (no imaginary suport)!
}

TEST_CASE( "signed infinit big integer bitLength", "[SABigint]" ) {
	REQUIRE( SArbBigInt::fromString(" - 00000000", 2).bitLength() == 0 );
	REQUIRE( SArbBigInt::fromString(" + 00000001", 2).bitLength() == 1 );
	REQUIRE( SArbBigInt::fromString("   00000011", 2).bitLength() == 2 );
	REQUIRE( SArbBigInt::fromString(" - 00000111", 2).bitLength() == 3 );
	REQUIRE( SArbBigInt::fromString(" + 00001111", 2).bitLength() == 4 );
	REQUIRE( SArbBigInt::fromString("   00011111", 2).bitLength() == 5 );
	REQUIRE( SArbBigInt::fromString(" - 00111111", 2).bitLength() == 6 );
	REQUIRE( SArbBigInt::fromString(" + 01111111", 2).bitLength() == 7 );
	REQUIRE( SArbBigInt::fromString("   11111111", 2).bitLength() == 8 );

	REQUIRE( SArbBigInt::fromString(" - 00000000", 2).bitLength() == 0 );
	REQUIRE( SArbBigInt::fromString(" + 00000001", 2).bitLength() == 1 );
	REQUIRE( SArbBigInt::fromString("   00000010", 2).bitLength() == 2 );
	REQUIRE( SArbBigInt::fromString(" - 00000100", 2).bitLength() == 3 );
	REQUIRE( SArbBigInt::fromString(" + 00001000", 2).bitLength() == 4 );
	REQUIRE( SArbBigInt::fromString("   00010000", 2).bitLength() == 5 );
	REQUIRE( SArbBigInt::fromString(" - 00100000", 2).bitLength() == 6 );
	REQUIRE( SArbBigInt::fromString(" + 01000000", 2).bitLength() == 7 );
	REQUIRE( SArbBigInt::fromString("   10000000", 2).bitLength() == 8 );

	REQUIRE( SArbBigInt::fromString(" - 00000000 00000000", 2).bitLength() ==  0 );
	REQUIRE( SArbBigInt::fromString(" + 00000001 00000000", 2).bitLength() ==  9 );
	REQUIRE( SArbBigInt::fromString("   00000010 00000000", 2).bitLength() == 10 );
	REQUIRE( SArbBigInt::fromString(" - 00000100 00000000", 2).bitLength() == 11 );
	REQUIRE( SArbBigInt::fromString(" + 00001000 00000000", 2).bitLength() == 12 );
	REQUIRE( SArbBigInt::fromString("   00010000 00000000", 2).bitLength() == 13 );
	REQUIRE( SArbBigInt::fromString(" - 00100000 00000000", 2).bitLength() == 14 );
	REQUIRE( SArbBigInt::fromString(" + 01000000 00000000", 2).bitLength() == 15 );
	REQUIRE( SArbBigInt::fromString("   10000000 00000000", 2).bitLength() == 16 );

	REQUIRE( SArbBigInt::fromString(" - 00000000 00000000 00000000", 2).bitLength() ==  0 );
	REQUIRE( SArbBigInt::fromString(" + 00000001 00000000 00000000", 2).bitLength() == 17 );
	REQUIRE( SArbBigInt::fromString("   00000010 00000000 00000000", 2).bitLength() == 18 );
	REQUIRE( SArbBigInt::fromString(" - 00000100 00000000 00000000", 2).bitLength() == 19 );
	REQUIRE( SArbBigInt::fromString(" + 00001000 00000000 00000000", 2).bitLength() == 20 );
	REQUIRE( SArbBigInt::fromString("   00010000 00000000 00000000", 2).bitLength() == 21 );
	REQUIRE( SArbBigInt::fromString(" - 00100000 00000000 00000000", 2).bitLength() == 22 );
	REQUIRE( SArbBigInt::fromString(" + 01000000 00000000 00000000", 2).bitLength() == 23 );
	REQUIRE( SArbBigInt::fromString("   10000000 00000000 00000000", 2).bitLength() == 24 );

	// 9 byte
	REQUIRE( SArbBigInt::fromString(" - 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() ==  0 );
	REQUIRE( SArbBigInt::fromString(" + 00000000 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 64 );
	REQUIRE( SArbBigInt::fromString("   00000001 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 65 );
	REQUIRE( SArbBigInt::fromString(" - 00000010 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 66 );
	REQUIRE( SArbBigInt::fromString(" + 00000100 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 67 );
	REQUIRE( SArbBigInt::fromString("   00001000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 68 );
	REQUIRE( SArbBigInt::fromString(" - 00010000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 69 );
	REQUIRE( SArbBigInt::fromString(" + 00100000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 70 );
	REQUIRE( SArbBigInt::fromString("   01000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 71 );
	REQUIRE( SArbBigInt::fromString(" - 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 72 );

	REQUIRE( SArbBigInt::fromString(" + 00000000 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 57 );
	REQUIRE( SArbBigInt::fromString("   00000000 10000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 64 );
	REQUIRE( SArbBigInt::fromString(" - 00000001 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 65 );
	REQUIRE( SArbBigInt::fromString(" + 00000011 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 66 );
	REQUIRE( SArbBigInt::fromString("   00000111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 67 );
	REQUIRE( SArbBigInt::fromString(" - 00001111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 68 );
	REQUIRE( SArbBigInt::fromString(" + 00011111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 69 );
	REQUIRE( SArbBigInt::fromString("   00111111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 70 );
	REQUIRE( SArbBigInt::fromString(" - 01111111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 71 );
	REQUIRE( SArbBigInt::fromString("   11111111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 72 );

}

TEST_CASE( "signed infinit big integer modInverse", "[SABigint]" ) {
	// wolfram alpha: PowerMod[this, -1, param]
	REQUIRE_THROWS_AS( SArbBigInt( 1).modInverse(0), std::invalid_argument );
	REQUIRE( SArbBigInt( 1).modInverse(3) == 1 );
	REQUIRE( SArbBigInt(13).modInverse(3) == 1 );
	REQUIRE( SArbBigInt( 2).modInverse(13) == 7 ); // wolfram alpha: PowerMod[2, -1, 13] => 7
	REQUIRE( SArbBigInt( 7).modInverse(13) == 2 );
	REQUIRE( SArbBigInt( 5).modInverse(13) == 8 );

	REQUIRE( SArbBigInt::fromInt64( 1).modInverse(SArbBigInt::fromInt64( 5)).toInt64() ==  1 );
	REQUIRE( SArbBigInt::fromInt64(-1).modInverse(SArbBigInt::fromInt64(-5)).toInt64() == -1 );
	REQUIRE( SArbBigInt::fromInt64(-1).modInverse(SArbBigInt::fromInt64( 5)).toInt64() ==  4 );
	REQUIRE( SArbBigInt::fromInt64( 1).modInverse(SArbBigInt::fromInt64(-5)).toInt64() == -4 );

	REQUIRE( SArbBigInt::fromInt64( 62369045776285).modInverse(SArbBigInt::fromInt64( 43567898765432)).toInt64() ==  38649570326437 );

	REQUIRE( SArbBigInt::fromInt64( 38649570326437).modInverse(SArbBigInt::fromInt64( 43567898765432)).toInt64() ==  18801147010853 );
	REQUIRE( SArbBigInt::fromInt64(-38649570326437).modInverse(SArbBigInt::fromInt64(-43567898765432)).toInt64() == -18801147010853 );
	REQUIRE( SArbBigInt::fromInt64(-38649570326437).modInverse(SArbBigInt::fromInt64( 43567898765432)).toInt64() ==  24766751754579 );
	REQUIRE( SArbBigInt::fromInt64( 38649570326437).modInverse(SArbBigInt::fromInt64(-43567898765432)).toInt64() == -24766751754579 );

	REQUIRE( SArbBigInt::fromString("16017867594215767234084978576693245168373889033733221066690514240642714658687", 10).modInverse(UArbBigInt::fromString("64071470376863068936339914306772980674254926422336709160732384697932204415401", 10)) == UArbBigInt::fromString("84374476378202765996703081706816197849", 10) );

	REQUIRE( SArbBigInt::fromString(" 84374476378202765996703081706816197849", 10).modInverse(SArbBigInt::fromString(" 64071470376863068936339914306772980674254926422336709160732384697932204415401", 10)) == SArbBigInt::fromString(" 16017867594215767234084978576693245168373889033733221066690514240642714658687", 10) );
	REQUIRE( SArbBigInt::fromString("-84374476378202765996703081706816197849", 10).modInverse(SArbBigInt::fromString("-64071470376863068936339914306772980674254926422336709160732384697932204415401", 10)) == SArbBigInt::fromString("-16017867594215767234084978576693245168373889033733221066690514240642714658687", 10) );
	REQUIRE( SArbBigInt::fromString("-84374476378202765996703081706816197849", 10).modInverse(SArbBigInt::fromString(" 64071470376863068936339914306772980674254926422336709160732384697932204415401", 10)) == SArbBigInt::fromString(" 48053602782647301702254935730079735505881037388603488094041870457289489756714", 10) );
	REQUIRE( SArbBigInt::fromString(" 84374476378202765996703081706816197849", 10).modInverse(SArbBigInt::fromString("-64071470376863068936339914306772980674254926422336709160732384697932204415401", 10)) == SArbBigInt::fromString("-48053602782647301702254935730079735505881037388603488094041870457289489756714", 10) );


	SArbBigInt one = SArbBigInt(1);
	SArbBigInt minusOne = SArbBigInt(1, true);
	SArbBigInt v = SArbBigInt::fromString(" 12345672345890887765433", 10);
	SArbBigInt m = SArbBigInt::fromString(" 204690484325368677690653462884286106163", 10);

	// m > 0 & v > 0
	REQUIRE( (v * v.modInverse(m) ) % m == SArbBigInt(1) % m);

	// m < 0 & v > 0
	m = m*minusOne;
	REQUIRE( (v * v.modInverse(m) ) % m == SArbBigInt(1) % m);

	// m < 0 & v < 0
	v = v*minusOne;
	REQUIRE( (v * v.modInverse(m) ) % m == SArbBigInt(1) % m);

	// m > 0 & v < 0
	m = m*minusOne;
	REQUIRE( (v * v.modInverse(m) ) % m == SArbBigInt(1) % m);
	
	REQUIRE_THROWS_AS( SArbBigInt(255).modInverse( 48), ppvr::math::NoMultiplicativeInverse );	// not relatively prime
}

TEST_CASE( "signed infinit big integer modPow", "[SABigint]" ) {
	// wolfram alpha: PowerMod[this, -1, param]

	// Trivial cases: exponent = 0
	REQUIRE( SArbBigInt(  0      ).modPow(SArbBigInt(  0       ), SArbBigInt(  3)) == SArbBigInt(1) ); // PowerMod[   0,    0,  3]
	REQUIRE( SArbBigInt(  0      ).modPow(SArbBigInt(  0       ), SArbBigInt(  1)) == SArbBigInt(0) ); // PowerMod[   0,    0,  1]
	REQUIRE( SArbBigInt(111      ).modPow(SArbBigInt(  0       ), SArbBigInt(  3)) == SArbBigInt(1) ); // PowerMod[ 111,    0,  3]
	REQUIRE( SArbBigInt(111      ).modPow(SArbBigInt(  0       ), SArbBigInt(  1)) == SArbBigInt(0) ); // PowerMod[ 111,    0,  1]
	REQUIRE( SArbBigInt(111, true).modPow(SArbBigInt(  0       ), SArbBigInt( 33)) == SArbBigInt(1) ); // PowerMod[-111,    0, 33]
	REQUIRE( SArbBigInt(111, true).modPow(SArbBigInt(  0       ), SArbBigInt( 21)) == SArbBigInt(1) ); // PowerMod[-111,    0, 21]
	REQUIRE( SArbBigInt(111, true).modPow(SArbBigInt(  0       ), SArbBigInt(  1)) == SArbBigInt(0) ); // PowerMod[-111,    0,  1]

	// Trivial cases: base = 1
	REQUIRE( SArbBigInt(  1      ).modPow(SArbBigInt(123       ), SArbBigInt(  1)) == SArbBigInt(0) ); // PowerMod[   1,  123,  1]
	REQUIRE( SArbBigInt(  1      ).modPow(SArbBigInt(123, true ), SArbBigInt(  1)) == SArbBigInt(0) ); // PowerMod[   1, -123,  1]
	REQUIRE( SArbBigInt(  1      ).modPow(SArbBigInt(123       ), SArbBigInt( 55)) == SArbBigInt(1) ); // PowerMod[   1,  123, 55]
	REQUIRE( SArbBigInt(  1      ).modPow(SArbBigInt(123, true ), SArbBigInt( 55)) == SArbBigInt(1) ); // PowerMod[   1, -123, 55]

	// Trivial cases: base = 0
	REQUIRE( SArbBigInt(  0      ).modPow(SArbBigInt(  7       ), SArbBigInt( 11)) == SArbBigInt(0) ); // PowerMod[   0,  7,   11]
	REQUIRE( SArbBigInt(  0      ).modPow(SArbBigInt(123       ), SArbBigInt( 55)) == SArbBigInt(0) ); // PowerMod[   0, 123,  55]
	REQUIRE( SArbBigInt(  0      ).modPow(SArbBigInt( 33       ), SArbBigInt(123)) == SArbBigInt(0) ); // PowerMod[   0,  33, 123]

	// Trivial cases: base = -1 && (exponent % 2 = 0)
	REQUIRE( SArbBigInt(  1, true).modPow(SArbBigInt(  0       ), SArbBigInt(  1)) == SArbBigInt(0) ); // PowerMod[  -1,   0,   1]
	REQUIRE( SArbBigInt(  1, true).modPow(SArbBigInt(  2       ), SArbBigInt(  1)) == SArbBigInt(0) ); // PowerMod[  -1,   2,   1]
	REQUIRE( SArbBigInt(  1, true).modPow(SArbBigInt(126       ), SArbBigInt(  1)) == SArbBigInt(0) ); // PowerMod[  -1, 126,   1]
	REQUIRE( SArbBigInt(  1, true).modPow(SArbBigInt(  0       ), SArbBigInt(  2)) == SArbBigInt(1) ); // PowerMod[  -1,   0,   2]
	REQUIRE( SArbBigInt(  1, true).modPow(SArbBigInt(  2       ), SArbBigInt(  3)) == SArbBigInt(1) ); // PowerMod[  -1,   2,   3]
	REQUIRE( SArbBigInt(  1, true).modPow(SArbBigInt(126       ), SArbBigInt(  4)) == SArbBigInt(1) ); // PowerMod[  -1, 126,   4]


	// -----
	REQUIRE( SArbBigInt::fromString("321", 10).modPow(SArbBigInt::fromString("170316580215634215412390428579751188659", 10), SArbBigInt::fromString("29007737496348564246541369697392157257353622947791601355298952855523410218281", 10)) == SArbBigInt::fromString("17721908342651498136687561664913427653804630235400928582777881790054443435532", 10) ); // PowerMod[321, 170316580215634215412390428579751188659, 29007737496348564246541369697392157257353622947791601355298952855523410218281]

	REQUIRE( SArbBigInt::fromString("3214568", 10).modPow(SArbBigInt::fromString("170316580215634215412390428579751188659", 10), SArbBigInt::fromString("29007737496348564246541369697392157257353622947791601355298952855523410218281", 10)) == SArbBigInt::fromString("1127560914217561411705062573176555105071973410478365642298306671851679283604", 10) ); // PowerMod[3214568, 170316580215634215412390428579751188659, 29007737496348564246541369697392157257353622947791601355298952855523410218281]
	REQUIRE( SArbBigInt::fromString("-3214568", 10).modPow(SArbBigInt::fromString("170316580215634215412390428579751188659", 10), SArbBigInt::fromString("29007737496348564246541369697392157257353622947791601355298952855523410218281", 10)) == SArbBigInt::fromString("27880176582131002834836307124215602152281649537313235713000646183671730934677", 10) ); // PowerMod[-3214568, 170316580215634215412390428579751188659, 29007737496348564246541369697392157257353622947791601355298952855523410218281]
	REQUIRE( SArbBigInt::fromString("3214568", 10).modPow(SArbBigInt::fromString("-170316580215634215412390428579751188659", 10), SArbBigInt::fromString("29007737496348564246541369697392157257353622947791601355298952855523410218281", 10)) == SArbBigInt::fromString("20116263141030960959212699376225349893755047493557022531820342521941680877605", 10) ); // PowerMod[3214568, -170316580215634215412390428579751188659, 29007737496348564246541369697392157257353622947791601355298952855523410218281]
	REQUIRE( SArbBigInt::fromString("-3214568", 10).modPow(SArbBigInt::fromString("-170316580215634215412390428579751188659", 10), SArbBigInt::fromString("29007737496348564246541369697392157257353622947791601355298952855523410218281", 10)) == SArbBigInt::fromString("8891474355317603287328670321166807363598575454234578823478610333581729340676", 10) ); // PowerMod[-3214568, -170316580215634215412390428579751188659, 29007737496348564246541369697392157257353622947791601355298952855523410218281]

	REQUIRE_THROWS( SArbBigInt::fromString("-4", 10).modPow(SArbBigInt::fromString("1", 10), SArbBigInt::fromString("-5", 10)) == SArbBigInt::fromString("-4", 10) ); // PowerMod[-4, 1, -5]
	
	REQUIRE(
			SArbBigInt::fromString(                                      "147058127173847711901598181942028410410", 10).modPow(
												  SArbBigInt::fromString("212590621487307383100037676105693032843", 10),
			SArbBigInt::fromString("45194772344359599619712314997219172273874874118738306499181802927551476662649", 10)
			).toStringDec() == "14880112179674072450044864404658332961525453634042072109707074639304131011910"
			); // PowerMod[147058127173847711901598181942028410410, 212590621487307383100037676105693032843, 45194772344359599619712314997219172273874874118738306499181802927551476662649]

	// b > m
	REQUIRE(
			SArbBigInt::fromString("34546737496348564246541369697392157357343622947391601355298952857523410218281", 10).modPow(
			                                      SArbBigInt::fromString("170316580215634215412390428579751188659", 10),
			SArbBigInt::fromString("29007737496348564246541369697392157257353622947791601355298952855523410218281", 10)
			).toStringDec() == "27437935934933632837176167850088741034260151597862879929180562960786562419072"
		); // PowerMod[34546737496348564246541369697392157357343622947391601355298952857523410218281, 170316580215634215412390428579751188659, 29007737496348564246541369697392157257353622947791601355298952855523410218281]
	
	REQUIRE(
			SArbBigInt::fromString("DDD283D73A398FE7A86987D9E0A37063", 16).modPow( SArbBigInt::fromString("DC9481390F23502D4F3C8D54BB194AA6", 16), SArbBigInt::fromString("EA3D7298B90FCFAE01364041BCB288C", 16)
			).toStringDec() == "12944751882554430796756496548659233721"
		); // PowerMod[294852443456491459562487243528900669539, 293201239959273747082550393509009509030, 19459900338543143665460291529662474380]
}

TEST_CASE( "signed infinit big integer fromSFixBigInt", "[SABigint]" ) {
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0, false)) == SArbBigInt(0, false) );
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, false)) == SArbBigInt(1, false) );
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1, true)) == SArbBigInt(1, true) );
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127, false)) == SArbBigInt(127, false) );
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127, true)) == SArbBigInt(127, true) );
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(128, false)) == SArbBigInt(128, false) );
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(128, true)) == SArbBigInt(128, true) );
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255, false)) == SArbBigInt(255, false) );
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255, true)) == SArbBigInt(255, true) );
	
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(560)>::fromString("+ 1 524 048 626 526 185 117 008 148 645 329 708 998 795 770 321 794 318 911 442 256 140 455 458 946 053 172 210 513 801 777 413  097 237 329 246 447 244 122 385 285 308 414 454 789 711 324 787 960 475 901 495 579 519 924 778 756", 10)) == SArbBigInt::fromString("+1524048626526185117008148645329708998795770321794318911442256140455458946053172210513801777413097237329246447244122385285308414454789711324787960475901495579519924778756", 10) );
	REQUIRE( SArbBigInt::fromSFixBigInt(SFixBigInt<BIG_INT_BIT_TO_SIZE(560)>::fromString("- 1 524 048 626 526 185 117 008 148 645 329 708 998 795 770 321 794 318 911 442 256 140 455 458 946 053 172 210 513 801 777 413  097 237 329 246 447 244 122 385 285 308 414 454 789 711 324 787 960 475 901 495 579 519 924 778 756", 10)) == SArbBigInt::fromString("-1524048626526185117008148645329708998795770321794318911442256140455458946053172210513801777413097237329246447244122385285308414454789711324787960475901495579519924778756", 10) );
	
	REQUIRE( SArbBigInt::fromSFixBigInt( SFixBigInt<BIG_INT_BIT_TO_SIZE(1024)>::fromString("+ 1 FF", 16)) == SArbBigInt::fromString("+ 1 FF", 16) );
	REQUIRE( SArbBigInt::fromSFixBigInt( SFixBigInt<BIG_INT_BIT_TO_SIZE(1024)>::fromString("- 1 FF", 16)) == SArbBigInt::fromString("- 1 FF", 16) );

	//REQUIRE_THROWS( UArbBigInt::fromUFixBigInt(UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("1  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00", 16)) );
}
