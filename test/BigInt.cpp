#include "../include/catch2/catch.hpp"
#include "../src/math/BigInt.h"

using ppvr::math::BigInt;

TEST_CASE( "big integer to unsigned int 64 (BigInt from Word constructor)", "[bigint]" ) {
	REQUIRE( BigInt::ZERO.toUint64() == 0ull );
	REQUIRE( BigInt(0).toUint64() == 0ull );
	
	REQUIRE( BigInt::ONE.toUint64() == 1ull );
	REQUIRE( BigInt(1).toUint64() == 1ull );
	
	REQUIRE( BigInt::TWO.toUint64() == 2ull );
	REQUIRE( BigInt(2).toUint64() == 2ull );
	
	REQUIRE( BigInt::TEN.toUint64() == 10ull );
	REQUIRE( BigInt(10).toUint64() == 10ull );
	
	REQUIRE( BigInt(5).toUint64() == 5ull );
	REQUIRE( BigInt(55).toUint64() == 55ull );
	REQUIRE( BigInt(127).toUint64() == 127ull );
	REQUIRE( BigInt(255).toUint64() == 255ull );
}

TEST_CASE( "big integer to unsigned int 64 (BigInt fromUint64())", "[bigint]" ) {
	//uint64_t int_2e63_test = 0x8000000000000000; // 2^63 => bin: 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
	//uint64_t test_128 = int_2e63_test >> (8 * 7);
	//uint64_t test_0 = int_2e63_test >> (8 * 8);
	
	REQUIRE( BigInt::fromUint64(0xFF).toUint64() == 255ull );
	REQUIRE( BigInt::fromUint64(0x0100).toUint64() == 256ull );
	REQUIRE( BigInt::fromUint64(1234).toUint64() == 1234ull );
	
	uint64_t int_2e16_m1 = std::pow(2ull, 16) - 1ull;
	REQUIRE( BigInt::fromUint64(0xFFFF).toUint64() == int_2e16_m1 );
	
	uint64_t int_2e16 = std::pow(2ull, 16);
	REQUIRE( BigInt::fromUint64(0x010000).toUint64() == int_2e16 );
	
	uint64_t int_2e23 = std::pow(2ull, 23);
	REQUIRE( BigInt::fromUint64(0x800000).toUint64() == int_2e23 );
	
	uint64_t int_2e24_m1 = std::pow(2ull, 24) - 1ull;
	REQUIRE( BigInt::fromUint64(0xFFFFFF).toUint64() == int_2e24_m1 );
	
	uint64_t int_2e24 = std::pow(2ull, 24);
	REQUIRE( BigInt::fromUint64(0x01000000).toUint64() == int_2e24 );
	
	uint64_t int_2e24_p1 = std::pow(2ull, 24) + 1ull;
	REQUIRE( BigInt::fromUint64(0x01000001).toUint64() == int_2e24_p1 );
	
	uint64_t int_2e32_m1 = std::pow(2ull, 32) - 1ull;
	REQUIRE( BigInt::fromUint64(0xFFFFFFFF).toUint64() == int_2e32_m1 );
	
	uint64_t int_2e32 = std::pow(2ull, 32);
	REQUIRE( BigInt::fromUint64(0x0100000000).toUint64() == int_2e32 );
	
	uint64_t int_2e32_p1 = std::pow(2ull, 32) + 1ull;
	REQUIRE( BigInt::fromUint64(0x0100000001).toUint64() == int_2e32_p1 );
	
	uint64_t int_2e63_m1 = 0x7FFFFFFFFFFFFFFF; // 2^63 - 1
	REQUIRE( BigInt::fromUint64(0x7FFFFFFFFFFFFFFF).toUint64() == int_2e63_m1 );
	
	uint64_t int_2e63 = 0x8000000000000000; // 2^63
	REQUIRE( BigInt::fromUint64(0x8000000000000000).toUint64() == int_2e63 );
	
	uint64_t int_2e63_m1_mul2 = 0xFFFFFFFFFFFFFFFE; // (2^63 - 1) * 2
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFE).toUint64() == int_2e63_m1_mul2 );
	
	uint64_t int_2e63_m1_mul2_p1 = 0xFFFFFFFFFFFFFFFF; // (2^63 - 1) * 2 + 1
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF).toUint64() == int_2e63_m1_mul2_p1 );
}

TEST_CASE( "big integer to std:string", "[bigint]" ) {
	// --- single byte big int creation ---
	
	REQUIRE( BigInt::ZERO.toStringDec() == std::string("0") );
	REQUIRE( BigInt(0).toStringDec() == std::string("0") );
	
	REQUIRE( BigInt::ONE.toStringDec() == std::string("1") );
	REQUIRE( BigInt(1).toStringDec() == std::string("1") );
	
	REQUIRE( BigInt::TWO.toStringDec() == std::string("2") );
	REQUIRE( BigInt(2).toStringDec() == std::string("2") );
	
	REQUIRE( BigInt::TEN.toStringDec() == std::string("10") );
	REQUIRE( BigInt(10).toStringDec() == std::string("10") );

	REQUIRE( BigInt(6).toStringDec() == std::string("6") );
	REQUIRE( BigInt(66).toStringDec() == std::string("66") );
	REQUIRE( BigInt(127).toStringDec() == std::string("127") );
	REQUIRE( BigInt(128).toStringDec() == std::string("128") );
	REQUIRE( BigInt(255).toStringDec() == std::string("255") );
	
	// --- use 64 bit conversion for big int creation ---
	
	REQUIRE( BigInt::fromUint64(256).toStringDec() == std::string("256") );
	
	REQUIRE( BigInt::fromUint64(0xFFFFFFFF).toStringDec() == std::string("4294967295") ); // 2^32 - 1
	REQUIRE( BigInt::fromUint64(0x0100000000).toStringDec() == std::string("4294967296") ); // 2^32
	REQUIRE( BigInt::fromUint64(0x0100000001).toStringDec() == std::string("4294967297") ); // 2^32 + 1
	
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF).toStringDec() == std::string("18446744073709551615") ); // 2^64 - 1
	
	// 65 bit test!
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::ONE).toStringDec() == std::string("18446744073709551616") ); // 2^64
}

TEST_CASE( "big integer from std:string", "[bigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( BigInt::fromString( "0", 10).toUint64() 	==   0 );
	REQUIRE( BigInt::fromString( "1", 10).toUint64() 	==   1 );
	REQUIRE( BigInt::fromString( "2", 10).toUint64() 	==   2 );
	REQUIRE( BigInt::fromString( "3", 10).toUint64() 	==   3 );
	REQUIRE( BigInt::fromString( "4", 10).toUint64() 	==   4 );
	REQUIRE( BigInt::fromString( "5", 10).toUint64() 	==   5 );
	REQUIRE( BigInt::fromString( "6", 10).toUint64() 	==   6 );
	REQUIRE( BigInt::fromString( "7", 10).toUint64() 	==   7 );
	REQUIRE( BigInt::fromString( "8", 10).toUint64() 	==   8 );
	REQUIRE( BigInt::fromString( "9", 10).toUint64() 	==   9 );
	REQUIRE( BigInt::fromString("10", 10).toUint64() 	==  10 );
	REQUIRE( BigInt::fromString("77", 10).toUint64() 	==  77 );
	REQUIRE( BigInt::fromString("127", 10).toUint64() 	== 127 );
	REQUIRE( BigInt::fromString("128", 10).toUint64() 	== 128 );
	REQUIRE( BigInt::fromString("255", 10).toUint64() 	== 255 );
	
	
	REQUIRE( BigInt::fromString("0", 16).toUint64() 	==  0 );
	REQUIRE( BigInt::fromString("1", 16).toUint64() 	==  1 );
	REQUIRE( BigInt::fromString("2", 16).toUint64() 	==  2 );
	REQUIRE( BigInt::fromString("3", 16).toUint64() 	==  3 );
	REQUIRE( BigInt::fromString("4", 16).toUint64() 	==  4 );
	REQUIRE( BigInt::fromString("5", 16).toUint64() 	==  5 );
	REQUIRE( BigInt::fromString("6", 16).toUint64() 	==  6 );
	REQUIRE( BigInt::fromString("7", 16).toUint64() 	==  7 );
	REQUIRE( BigInt::fromString("8", 16).toUint64() 	==  8 );
	REQUIRE( BigInt::fromString("9", 16).toUint64() 	==  9 );
	
	REQUIRE( BigInt::fromString("a", 16).toUint64() 	== 10 );
	REQUIRE( BigInt::fromString("b", 16).toUint64() 	== 11 );
	REQUIRE( BigInt::fromString("c", 16).toUint64() 	== 12 );
	REQUIRE( BigInt::fromString("d", 16).toUint64() 	== 13 );
	REQUIRE( BigInt::fromString("e", 16).toUint64() 	== 14 );
	REQUIRE( BigInt::fromString("f", 16).toUint64() 	== 15 );
	
	REQUIRE( BigInt::fromString("A", 16).toUint64() 	== 10 );
	REQUIRE( BigInt::fromString("B", 16).toUint64() 	== 11 );
	REQUIRE( BigInt::fromString("C", 16).toUint64() 	== 12 );
	REQUIRE( BigInt::fromString("D", 16).toUint64() 	== 13 );
	REQUIRE( BigInt::fromString("E", 16).toUint64() 	== 14 );
	REQUIRE( BigInt::fromString("F", 16).toUint64() 	== 15 );
	
	REQUIRE( BigInt::fromString("7F", 16).toUint64()	== 127 );
	REQUIRE( BigInt::fromString("80", 16).toUint64()	== 128 );
	REQUIRE( BigInt::fromString("FF", 16).toUint64()	== 255 );
	
	// leading zeros
	REQUIRE( BigInt::fromString(  "01", 10).toUint64() 	==   1 );
	REQUIRE( BigInt::fromString( "001", 10).toUint64() 	==   1 );
	REQUIRE( BigInt::fromString("0256", 10).toUint64() 	==   256 );
	
	REQUIRE( BigInt::fromString(  "00", 16).toUint64() 	==   0 );
	REQUIRE( BigInt::fromString(  "01", 16).toUint64() 	==   1 );
	REQUIRE( BigInt::fromString(  "0f", 16).toUint64() 	==   15 );
	REQUIRE( BigInt::fromString("000A", 16).toUint64() 	==   10 );
	REQUIRE( BigInt::fromString("00ff", 16).toUint64() 	==   255 );
	
	// 2 Bytes (16 bit)
	REQUIRE( BigInt::fromString("256", 10).toUint64() == 256 ); // 2^16
	REQUIRE( BigInt::fromString("0100", 16).toUint64() == 256 );
	
	// 4 Bytes (32 bit)
	REQUIRE( BigInt::fromString("4294967295", 10).toUint64() == 0xFFFFFFFFull ); // 2^32 - 1
	REQUIRE( BigInt::fromString("FFFFFFFF", 16).toUint64() == 0xFFFFFFFFull );
	REQUIRE( BigInt::fromString("01234567", 16).toUint64() == 0x01234567ull );
	
	// 8 Bytes (64 bit)
	REQUIRE( BigInt::fromString("4294967296", 10).toUint64() == 0x0100000000ull ); // 2^32
	REQUIRE( BigInt::fromString("0100000000", 16).toUint64() == 0x0100000000ull );
	REQUIRE( BigInt::fromString("4294967297", 10).toUint64() == 0x0100000001ull ); // 2^32 + 1
	REQUIRE( BigInt::fromString("0100000001", 16).toUint64() == 0x0100000001ull );
	REQUIRE( BigInt::fromString("0123456789ABCDEF", 16).toUint64() == 0x0123456789ABCDEFull );
	REQUIRE( BigInt::fromString("fedcba9876543210", 16).toUint64() == 0xFEDCBA9876543210ull );
	
	
	REQUIRE( BigInt::fromString("18446744073709551615", 10).toUint64() 	== 0xFFFFFFFFFFFFFFFFull ); // 2^64 - 1
	REQUIRE( BigInt::fromString("FFFFFFFFFFFFFFFF", 16).toUint64() 		== 0xFFFFFFFFFFFFFFFFull );
	
	// --- use 65 bit conversion for big int reference creation ---
	// this uses also the BIG int == operator, therefore a failed test could als be a problem of the == operator implementation
	REQUIRE( BigInt::fromString("18446744073709551616", 10) == (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE) ); // 2^64
	REQUIRE( BigInt::fromString("010000000000000000", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE) ); // 2^64
	REQUIRE( BigInt::fromString("010000000000000001", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x01)) );
	REQUIRE( BigInt::fromString("010000000000000002", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x02)) );
	REQUIRE( BigInt::fromString("010000000000000003", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x03)) );
	REQUIRE( BigInt::fromString("010000000000000004", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x04)) );
	REQUIRE( BigInt::fromString("010000000000000005", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x05)) );
	REQUIRE( BigInt::fromString("010000000000000006", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x06)) );
	REQUIRE( BigInt::fromString("010000000000000007", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x07)) );
	REQUIRE( BigInt::fromString("010000000000000008", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x08)) );
	REQUIRE( BigInt::fromString("010000000000000009", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x09)) );
	REQUIRE( BigInt::fromString("01000000000000000A", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x0A)) );
	REQUIRE( BigInt::fromString("01000000000000000B", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x0B)) );
	REQUIRE( BigInt::fromString("01000000000000000C", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x0C)) );
	REQUIRE( BigInt::fromString("01000000000000000D", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x0D)) );
	REQUIRE( BigInt::fromString("01000000000000000E", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x0E)) );
	REQUIRE( BigInt::fromString("01000000000000000F", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0x0F)) );
	REQUIRE( BigInt::fromString("0100000000000000Fe", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0xFE)) );
	REQUIRE( BigInt::fromString("0100000000000000Ff", 16) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE + BigInt(0xFF)) );
	
}

TEST_CASE( "big integer comparisons", "[bigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( BigInt(1) != BigInt::ZERO );
	REQUIRE( BigInt(0) != BigInt::ONE );
	
	REQUIRE( BigInt(0) == BigInt::ZERO );
	REQUIRE( BigInt(0) <= BigInt::ZERO );
	REQUIRE( BigInt(0) >= BigInt::ZERO );
	
	REQUIRE( BigInt(0) < BigInt::ONE );
	REQUIRE( BigInt(1) > BigInt::ZERO );
	
	REQUIRE( BigInt(10) >  BigInt(9) );
	REQUIRE( BigInt(10) >= BigInt(9) );
	REQUIRE( BigInt(9) 	<  BigInt::TEN );
	REQUIRE( BigInt(9) 	<= BigInt::TEN );
	REQUIRE( BigInt(10) <= BigInt::TEN );
	REQUIRE( BigInt(10) >= BigInt::TEN );
	
	REQUIRE( BigInt(255) == BigInt::fromUint64(0xFF) );
	REQUIRE( BigInt(255) <= BigInt::fromUint64(0xFF) );
	REQUIRE( BigInt(255) >= BigInt::fromUint64(0xFF) );
	
	REQUIRE( BigInt(0) 		<  BigInt(255) );
	REQUIRE( BigInt(0) 		<= BigInt(255) );
	REQUIRE( BigInt(255) 	>  BigInt(0) );
	REQUIRE( BigInt(255) 	>= BigInt(0) );
	
	REQUIRE( BigInt(1) 		<  BigInt(255) );
	REQUIRE( BigInt(1) 		<= BigInt(255) );
	REQUIRE( BigInt(255) 	>  BigInt(1) );
	REQUIRE( BigInt(255) 	>= BigInt(1) );
	
	REQUIRE( BigInt(245) 	<  BigInt(255) );
	REQUIRE( BigInt(245) 	<= BigInt(255) );
	REQUIRE( BigInt(255) 	>  BigInt(245) );
	REQUIRE( BigInt(255) 	>= BigInt(245) );
	
	// 2 Bytes (16 bit)
	REQUIRE( BigInt(255) 				<  BigInt::fromUint64(0x0100) );
	REQUIRE( BigInt(255) 				<= BigInt::fromUint64(0x0100) );
	REQUIRE( BigInt::fromUint64(0x0100) >  BigInt(255) );
	REQUIRE( BigInt::fromUint64(0x0100) >= BigInt(255) );
	
	REQUIRE( BigInt::fromUint64(0x0100) == BigInt::fromUint64(0x0100) );
	REQUIRE( BigInt::fromUint64(0x0100) <= BigInt::fromUint64(0x0100) );
	REQUIRE( BigInt::fromUint64(0x0100) >= BigInt::fromUint64(0x0100) );
	
	REQUIRE( BigInt::fromUint64(0x0101) >  BigInt::fromUint64(0x0100) );
	REQUIRE( BigInt::fromUint64(0x0101) >= BigInt::fromUint64(0x0100) );
	REQUIRE( BigInt::fromUint64(0x0101) <  BigInt::fromUint64(0x0102) );
	REQUIRE( BigInt::fromUint64(0x0101) <= BigInt::fromUint64(0x0102) );
	
	// 8 Bytes (64bit)
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFE) != BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( BigInt::fromUint64(0xEFFFFFFFFFFFFFFF) != BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) == BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) <= BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) >= BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFE) <  BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) >  BigInt::fromUint64(0xFFFFFFFFFFFFFFFE) );
	
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFF00) >  BigInt(1) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFF00) >= BigInt::ONE );
	REQUIRE( BigInt::ONE 							<  BigInt::fromUint64(0xFFFFFFFFFFFFFF00) );
	REQUIRE( BigInt(1) 								<= BigInt::fromUint64(0xFFFFFFFFFFFFFF00) );
	
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFF01) != BigInt::fromUint64(0x01) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFF01) >  BigInt::fromUint64(0x01) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFF01) >= BigInt::fromUint64(0x01) );
	REQUIRE( BigInt::fromUint64(0x01) 				<  BigInt::fromUint64(0xFFFFFFFFFFFFFF01) );
	REQUIRE( BigInt::fromUint64(0x01) 				<= BigInt::fromUint64(0xFFFFFFFFFFFFFF01) );
	
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFF01) != BigInt::fromUint64(0xFF01) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFF01) >  BigInt::fromUint64(0xFF01) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFF01) >= BigInt::fromUint64(0xFF01) );
	REQUIRE( BigInt::fromUint64(0xFF01) 			<  BigInt::fromUint64(0xFFFFFFFFFFFFFF01) );
	REQUIRE( BigInt::fromUint64(0xFF01) 			<= BigInt::fromUint64(0xFFFFFFFFFFFFFF01) );
	
	//REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFF01) != BigInt::fromUint64(0xFFFFFFFFFFFFFF01) );
	
	// 9 Bytes (65bit)
	REQUIRE(  BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 					!= (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(1)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::ONE) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(1)) );
	REQUIRE(  BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 					<  (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(1)) );
	REQUIRE(  BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 					<= (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(1)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(1)) 		>   BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(1)) 		>   BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::TEN) 	!= (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::TEN) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(10)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::TEN)		<  (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::TEN)		<= (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) 		>  (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(10)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) 		>  (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(10)) );
	
	//REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) 		!=  (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) );
}

TEST_CASE( "big integer addition", "[bigint]" ) {
	// 1 Byte (8bit)
	REQUIRE(   BigInt(0) +   BigInt(0) 	== BigInt::ZERO );
	REQUIRE(   BigInt(1) +   BigInt(0) 	== BigInt::ONE );
	REQUIRE(   BigInt(0) +   BigInt(1) 	== BigInt::ONE );
	REQUIRE(   BigInt(1) +   BigInt(1) 	== BigInt::TWO );
	REQUIRE(   BigInt(2) +   BigInt(1) 	==   BigInt(3) );
	REQUIRE(   BigInt(1) +   BigInt(2) 	==   BigInt(3) );
	REQUIRE(  BigInt(10) +   BigInt(1) 	==  BigInt(11) );
	REQUIRE( BigInt(128) + BigInt(127) 	== BigInt(255) );
	
	// 2 Bytes (16 bit)
	REQUIRE( BigInt(128) + BigInt(128) 	== BigInt::fromUint64(0x0100ull) );
	REQUIRE( BigInt(255) + BigInt(1) 	== BigInt::fromUint64(0x0100ull) );
	REQUIRE( BigInt(1)   + BigInt(255) 	== BigInt::fromUint64(0x0100ull) );
	REQUIRE( BigInt(255) + BigInt(255) 	== BigInt::fromUint64(0x01FEull) );
	
	REQUIRE( BigInt::fromUint64(0x7FFF) + BigInt::fromUint64(0x7FFF) 				== BigInt::fromUint64(0xFFFEull) );
	REQUIRE( BigInt::fromUint64(0x7FFF) + BigInt::fromUint64(0x7FFF) + BigInt(0) 	== BigInt::fromUint64(0xFFFEull) );
	REQUIRE( BigInt::fromUint64(0x7FFF) + BigInt::fromUint64(0x7FFF) + BigInt(1) 	== BigInt::fromUint64(0xFFFFull) );
	REQUIRE( BigInt(1) + BigInt::fromUint64(0x7FFF) + BigInt::fromUint64(0x7FFF) 	== BigInt::fromUint64(0xFFFFull) );
	
	// 4 Bytes (32bit)
	REQUIRE( BigInt::fromUint64(0x8000) + BigInt::fromUint64(0x8000) 	== BigInt::fromUint64(0x010000ull) );
	REQUIRE( BigInt::fromUint64(0xFFFF) + BigInt::fromUint64(0x01) 		== BigInt::fromUint64(0x010000ull) );
	REQUIRE( BigInt::fromUint64(0x01) + BigInt::fromUint64(0xFFFF) 		== BigInt::fromUint64(0x010000ull) );
	REQUIRE( BigInt::fromUint64(0xFFFF) + BigInt::fromUint64(0xFFFF) 	== BigInt::fromUint64(0x01FFFEull) );
	
	REQUIRE( BigInt::fromUint64(0x7FFFFFFF) + BigInt::fromUint64(0x7FFFFFFF) 				== BigInt::fromUint64(0xFFFFFFFEull) );
	REQUIRE( BigInt::fromUint64(0x7FFFFFFF) + BigInt::fromUint64(0x7FFFFFFF) + BigInt(0) 	== BigInt::fromUint64(0xFFFFFFFEull) );
	REQUIRE( BigInt::fromUint64(0x7FFFFFFF) + BigInt::fromUint64(0x7FFFFFFF) + BigInt(1) 	== BigInt::fromUint64(0xFFFFFFFFull) );
	REQUIRE( BigInt(1) + BigInt::fromUint64(0x7FFFFFFF) + BigInt::fromUint64(0x7FFFFFFF) 	== BigInt::fromUint64(0xFFFFFFFFull) );
	
	// 8 Bytes (64bit)
	REQUIRE( BigInt::fromUint64(0x80000000) + BigInt::fromUint64(0x80000000) 	== BigInt::fromUint64(0x0100000000ull) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFF) + BigInt::fromUint64(0x01) 			== BigInt::fromUint64(0x0100000000ull) );
	REQUIRE( BigInt::fromUint64(0x01) + BigInt::fromUint64(0xFFFFFFFF) 			== BigInt::fromUint64(0x0100000000ull) );
	REQUIRE( BigInt::fromUint64(0xFFFFFFFF) + BigInt::fromUint64(0xFFFFFFFF) 	== BigInt::fromUint64(0x01FFFFFFFEull) );
	
	REQUIRE( BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) 				== BigInt::fromUint64(0xFFFFFFFFFFFFFFFEull) );
	REQUIRE( BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt(0) 	== BigInt::fromUint64(0xFFFFFFFFFFFFFFFEull) );
	REQUIRE( BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt(1) 	== BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) );
	REQUIRE( BigInt(1) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) 	== BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) );
	
	// 16 Bytes (128bit)
	REQUIRE( BigInt::fromString("18446744073709551616", 10) == (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE) ); // 2^64
	
	REQUIRE( BigInt::fromUint64(0x8000000000000000) + BigInt::fromUint64(0x8000000000000000) 	== BigInt::fromString("18446744073709551616", 10) ); // 2^64
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::fromUint64(0x01) 					== BigInt::fromString("010000000000000000", 16) ); // 2^64
	REQUIRE( BigInt::fromUint64(0x01) + BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 					== BigInt::fromString("010000000000000000", 16) ); // 2^64
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 	== BigInt::fromString("01FFFFFFFFFFFFFFFE", 16) );
	
	REQUIRE( BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) 				== BigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE", 16) );
	REQUIRE( BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt(0)	== BigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE", 16) );
	REQUIRE( BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt(1)	== BigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) );
	REQUIRE( BigInt(1) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16)	== BigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) );
}

TEST_CASE( "big integer subtraction", "[bigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( BigInt(0) - BigInt(0) 	== BigInt::ZERO );
	REQUIRE( BigInt(1) - BigInt(0) 	== BigInt::ONE );
	REQUIRE( BigInt(1) - BigInt(1) 	== BigInt::ZERO );
	
	REQUIRE(  BigInt(9) - BigInt(1) 	== BigInt(8) );
	REQUIRE(  BigInt(9) - BigInt(9) 	== BigInt(0) );
	REQUIRE( BigInt(10) - BigInt(9) 	== BigInt(1) );
	REQUIRE( BigInt(255) - BigInt(0) 	== BigInt(255) );
	REQUIRE( BigInt(255) - BigInt(255) 	== BigInt(0) );
	REQUIRE( BigInt(255) - BigInt(1) 	== BigInt(254) );
	
	// 2 Bytes (16 bit)
	REQUIRE(  BigInt::fromUint64(0x0100ull) - BigInt::fromUint64(0x0100ull) 	== BigInt(0) ); // 256 - 256 = 0
	REQUIRE(  BigInt::fromUint64(0x0101ull) - BigInt::fromUint64(0x0100ull) 	== BigInt(1) ); // 257 - 256 = 1
	REQUIRE(  BigInt::fromUint64(0x0101ull) - BigInt::fromUint64(0x01ull) 		== BigInt::fromUint64(0x0100ull) ); // 257 - 1 = 256
	REQUIRE(  BigInt::fromUint64(0x0101ull) - BigInt::fromUint64(0x02ull) 		== BigInt(255) ); // 257 - 2 = 255
	
	// 4 Bytes (32bit)
	REQUIRE(  BigInt::fromUint64(0x010000ull) - BigInt::fromUint64(0x010000ull) 	== BigInt(0) ); // 2^16 - 2^16 = 0
	REQUIRE(  BigInt::fromUint64(0x010001ull) - BigInt::fromUint64(0x010000ull) 	== BigInt(1) ); // (2^16 + 1) - 2^16 = 1
	REQUIRE(  BigInt::fromUint64(0x010001ull) - BigInt::fromUint64(0x01ull) 		== BigInt::fromUint64(0x010000ull) ); // (2^16 + 1) - 1 = 2^16
	REQUIRE(  BigInt::fromUint64(0x010001ull) - BigInt::fromUint64(0x02ull) 		== BigInt::fromUint64(0x00FFFFull) ); // (2^16 + 1) - 2 = 2^16 - 1
	
	// 8 Bytes (64bit)
	REQUIRE(  BigInt::fromUint64(0x0100000000ull) - BigInt::fromUint64(0x0100000000ull) 	== BigInt(0) ); // 2^32 - 2^32 = 0
	REQUIRE(  BigInt::fromUint64(0x0100000001ull) - BigInt::fromUint64(0x0100000000ull) 	== BigInt(1) ); // (2^32 + 1) - 2^32 = 1
	REQUIRE(  BigInt::fromUint64(0x0100000001ull) - BigInt::fromUint64(0x01ull) 			== BigInt::fromUint64(0x0100000000ull) ); // (2^32 + 1) - 1 = 2^32
	REQUIRE(  BigInt::fromUint64(0x0100000001ull) - BigInt::fromUint64(0x02ull) 			== BigInt::fromUint64(0x00FFFFFFFFull) ); // (2^32 + 1) - 2 = 2^32 - 1
	
	// 16 Bytes (128bit)
	REQUIRE(  BigInt::fromString("010000000000000000", 16) - BigInt::fromString("010000000000000000", 16) 	== BigInt(0) ); // 2^64 - 2^64 = 0
	REQUIRE(  BigInt::fromString("010000000000000001", 16) - BigInt::fromString("010000000000000000", 16) 	== BigInt(1) ); // (2^64 + 1) - 2^64 = 1
	REQUIRE(  BigInt::fromString("010000000000000001", 16) - BigInt::fromUint64(0x01ull) 			== BigInt::fromString("010000000000000000", 16) ); // (2^64 + 1) - 1 = 2^64
	REQUIRE(  BigInt::fromString("010000000000000001", 16) - BigInt::fromUint64(0x02ull) 			== BigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull) ); // (2^64 + 1) - 2 = 2^64 - 1
}
