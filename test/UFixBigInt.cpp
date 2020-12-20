#include "../include/catch2/catch.hpp"
#include "../src/math/UArbBigInt.hpp"
#include "../src/math/UFixBigInt.hpp"

#include <iostream>

#define LONG_TESTS 0

using ppvr::math::UArbBigInt;
using ppvr::math::UFixBigInt;

TEST_CASE( "Test macro that calculates the minumum word count for a given bit size", "[UFBigint]" ) {
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( BIG_INT_BIT_TO_SIZE(1) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(7) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(8) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(9) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(16) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(17) == 3 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(24) == 3 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(25) == 4 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(32) == 4 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(64) == 8 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(65) == 9 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(120) == 15 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(121) == 16 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(128) == 16 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(129) == 17 );
	
		REQUIRE( BIG_INT_BIT_TO_SIZE(2048) == 256 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(2049) == 257 );
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
		REQUIRE( BIG_INT_BIT_TO_SIZE(1) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(7) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(8) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(9) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(16) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(17) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(24) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(25) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(32) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(33) == 3 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(48) == 3 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(49) == 4 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(64) == 4 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(65) == 5 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(120) == 8 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(121) == 8 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(128) == 8 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(129) == 9 );
		
		REQUIRE( BIG_INT_BIT_TO_SIZE(2048) == 128 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(2049) == 129 );
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
		REQUIRE( BIG_INT_BIT_TO_SIZE(1) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(7) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(8) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(9) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(16) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(17) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(32) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(33) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(48) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(49) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(64) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(65) == 3 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(96) == 3 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(97) == 4 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(128) == 4 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(129) == 5 );
		
		REQUIRE( BIG_INT_BIT_TO_SIZE(2048) == 64 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(2049) == 65 );
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint64_t)) {
		REQUIRE( BIG_INT_BIT_TO_SIZE(1) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(7) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(8) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(9) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(16) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(17) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(32) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(33) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(49) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(64) == 1 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(65) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(96) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(97) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(128) == 2 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(129) == 3 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(192) == 3 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(193) == 4 );
		
		REQUIRE( BIG_INT_BIT_TO_SIZE(2048) == 32 );
		REQUIRE( BIG_INT_BIT_TO_SIZE(2049) == 33 );
	} else {
		REQUIRE( "" == "unkunknowen type big int word type  BIG_INT_WORD_TYPE");
	}
}

TEST_CASE( "unsigned fixed big integer to unsigned int 64 (UFixBigInt from Word constructor)", "[UFBigint]" ) {
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0).toUint64() == 0ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1).toUint64() == 1ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2).toUint64() == 2ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10).toUint64() == 10ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(5).toUint64() == 5ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(55).toUint64() == 55ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127).toUint64() == 127ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255).toUint64() == 255ull );
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(0).toUint64() == 0ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(2).toUint64() == 2ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(127).toUint64() == 127ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(255).toUint64() == 255ull );
	
	//if(UFixBigInt<BIG_INT_BIT_TO_SIZE(2048)>(0).toUint64() == 0ull) {
	//	std::cout << "OK" << std::endl;
	//}
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(1024)>(0).toUint64() == 0ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(1024)>(2).toUint64() == 2ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(1024)>(127).toUint64() == 127ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(1024)>(255).toUint64() == 255ull );
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(2048)>(0).toUint64() == 0ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(2048)>(2).toUint64() == 2ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(2048)>(127).toUint64() == 127ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(2048)>(255).toUint64() == 255ull );
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(4096)>(0).toUint64() == 0ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(4096)>(2).toUint64() == 2ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(4096)>(127).toUint64() == 127ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(4096)>(255).toUint64() == 255ull );
}

TEST_CASE( "unsigned fixed big integer to unsigned int 64 (UFixBigInt fromUint64())", "[UFBigint]" ) {
	//uint64_t int_2e63_test = 0x8000000000000000; // 2^63 => bin: 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
	//uint64_t test_128 = int_2e63_test >> (8 * 7);
	//uint64_t test_0 = int_2e63_test >> (8 * 8);

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(0xFF).toUint64() == 255ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(9)>::fromUint64(0x0100).toUint64() == 256ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(11)>::fromUint64(1234).toUint64() == 1234ull );

	uint64_t int_2e16_m1 = std::pow(2ull, 16) - 1ull;
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0xFFFF).toUint64() == int_2e16_m1 );

	uint64_t int_2e16 = std::pow(2ull, 16);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(17)>::fromUint64(0x010000).toUint64() == int_2e16 );

	uint64_t int_2e23 = std::pow(2ull, 23);
	REQUIRE(  UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromUint64(0x800000).toUint64() == int_2e23 );

	uint64_t int_2e24_m1 = std::pow(2ull, 24) - 1ull;
	REQUIRE(  UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromUint64(0xFFFFFF).toUint64() == int_2e24_m1 );

	uint64_t int_2e24 = std::pow(2ull, 24);
	REQUIRE(  UFixBigInt<BIG_INT_BIT_TO_SIZE(25)>::fromUint64(0x01000000).toUint64() == int_2e24 );

	uint64_t int_2e24_p1 = std::pow(2ull, 24) + 1ull;
	REQUIRE(  UFixBigInt<BIG_INT_BIT_TO_SIZE(25)>::fromUint64(0x01000001).toUint64() == int_2e24_p1 );

	uint64_t int_2e32_m1 = std::pow(2ull, 32) - 1ull;
	REQUIRE(  UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0xFFFFFFFF).toUint64() == int_2e32_m1 );

	uint64_t int_2e32 = std::pow(2ull, 32);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(33)>::fromUint64(0x0100000000).toUint64() == int_2e32 );

	uint64_t int_2e32_p1 = std::pow(2ull, 32) + 1ull;
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(33)>::fromUint64(0x0100000001).toUint64() == int_2e32_p1 );

	uint64_t int_2e63_m1 = 0x7FFFFFFFFFFFFFFF; // 2^63 - 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(63)>::fromUint64(0x7FFFFFFFFFFFFFFF).toUint64() == int_2e63_m1 );

	uint64_t int_2e63 = 0x8000000000000000; // 2^63
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x8000000000000000).toUint64() == int_2e63 );

	uint64_t int_2e63_m1_mul2 = 0xFFFFFFFFFFFFFFFE; // (2^63 - 1) * 2
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFE).toUint64() == int_2e63_m1_mul2 );

	uint64_t int_2e63_m1_mul2_p1 = 0xFFFFFFFFFFFFFFFF; // (2^63 - 1) * 2 + 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF).toUint64() == int_2e63_m1_mul2_p1 );
}

TEST_CASE( "unsigned fixed big integer check word definitions for 64bit", "[UFBigint]" ) {
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( sizeof(BIG_INT_WORD_TYPE) == 1 );

		REQUIRE( BIG_INT_WORD_LOW_BIT_MASK == 0x0Full );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(BIG_INT_WORD_LOW_BIT_MASK) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("0F", 16) );

		REQUIRE( BIG_INT_WORD_HIGH_BIT_MASK == 0xF0ull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(BIG_INT_WORD_HIGH_BIT_MASK) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("F0", 16) );

		REQUIRE( BIG_INT_WORD_MAX_VALUE == 0xFFull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(BIG_INT_WORD_MAX_VALUE) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("FF", 16) );

		REQUIRE( BIG_INT_BITS_PER_WORD == sizeof(BIG_INT_WORD_TYPE) * 8 );
		REQUIRE( BIG_INT_BITS_PER_WORD == 8 );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(BIG_INT_BITS_PER_WORD) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("8", 10) );

		REQUIRE( BIG_INT_WORD_HIGHEST_BIT == 0x80ull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) << 7);
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
		REQUIRE( sizeof(BIG_INT_WORD_TYPE) == 2 );

		REQUIRE( BIG_INT_WORD_LOW_BIT_MASK == 0x00FFull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(BIG_INT_WORD_LOW_BIT_MASK) == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("00 FF", 16) );

		REQUIRE( BIG_INT_WORD_HIGH_BIT_MASK == 0xFF00ull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(BIG_INT_WORD_HIGH_BIT_MASK) == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("FF 00", 16) );

		REQUIRE( BIG_INT_WORD_MAX_VALUE == 0xFFFFull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(BIG_INT_WORD_MAX_VALUE) == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("FF FF", 16) );

		REQUIRE( BIG_INT_BITS_PER_WORD == sizeof(BIG_INT_WORD_TYPE) * 8 );
		REQUIRE( BIG_INT_BITS_PER_WORD == 16 );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(BIG_INT_BITS_PER_WORD) == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("16", 10) );

		REQUIRE( BIG_INT_WORD_HIGHEST_BIT == 0x8000ull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00000000", 2) );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) << 15);
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
		REQUIRE( sizeof(BIG_INT_WORD_TYPE) == 4 );

		REQUIRE( BIG_INT_WORD_LOW_BIT_MASK == 0x0000FFFFull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(BIG_INT_WORD_LOW_BIT_MASK) == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("00 00 FF FF", 16) );

		REQUIRE( BIG_INT_WORD_HIGH_BIT_MASK == 0xFFFF0000ull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(BIG_INT_WORD_HIGH_BIT_MASK) == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("FF FF 00 00", 16) );

		REQUIRE( BIG_INT_WORD_MAX_VALUE == 0xFFFFFFFF );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(BIG_INT_WORD_MAX_VALUE) == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("FF FF FF FF", 16) );

		REQUIRE( BIG_INT_BITS_PER_WORD == sizeof(BIG_INT_WORD_TYPE) * 8 );
		REQUIRE( BIG_INT_BITS_PER_WORD == 32 );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(BIG_INT_BITS_PER_WORD) == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("32", 10) );

		REQUIRE( BIG_INT_WORD_HIGHEST_BIT == 0x80000000 );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 00000000", 2) );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 31);
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint64_t)) {
		REQUIRE( sizeof(BIG_INT_WORD_TYPE) == 8 );

		REQUIRE( BIG_INT_WORD_LOW_BIT_MASK == 0x00000000FFFFFFFFull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(BIG_INT_WORD_LOW_BIT_MASK) == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("FF FF FF FF", 16) );

		REQUIRE( BIG_INT_WORD_HIGH_BIT_MASK == 0xFFFFFFFF00000000ull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(BIG_INT_WORD_HIGH_BIT_MASK) == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("FF FF FF FF 00 00 00 00", 16) );

		REQUIRE( BIG_INT_WORD_MAX_VALUE == 0xFFFFFFFFFFFFFFFFull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(BIG_INT_WORD_MAX_VALUE) == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("FF FF FF FF FF FF FF FF", 16) );

		REQUIRE( BIG_INT_BITS_PER_WORD == sizeof(BIG_INT_WORD_TYPE) * 8 );
		REQUIRE( BIG_INT_BITS_PER_WORD == 64 );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(BIG_INT_BITS_PER_WORD) == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("64", 10) );

		REQUIRE( BIG_INT_WORD_HIGHEST_BIT == 0x8000000000000000ull );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 00000000 00000000 00000000  00000000 00000000 00000000 00000000", 2) );
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 63);
	} else {
		REQUIRE( "" == "unkunknowen type big int word type  BIG_INT_WORD_TYPE");
	}
}

TEST_CASE( "unsigned fixed big integer to std:string hex", "[UFBigint]" ) {
	// --- single byte big int creation ---

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0).toStringHex() == std::string("0") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1).toStringHex() == std::string("1") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2).toStringHex() == std::string("2") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(3).toStringHex() == std::string("3") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(4).toStringHex() == std::string("4") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(5).toStringHex() == std::string("5") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(6).toStringHex() == std::string("6") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(7).toStringHex() == std::string("7") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(8).toStringHex() == std::string("8") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(9).toStringHex() == std::string("9") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10).toStringHex() == std::string("A") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(11).toStringHex() == std::string("B") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(12).toStringHex() == std::string("C") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(13).toStringHex() == std::string("D") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(14).toStringHex() == std::string("E") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(15).toStringHex() == std::string("F") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(16).toStringHex() == std::string("10") );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(66).toStringHex() == std::string("42") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127).toStringHex() == std::string("7F") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(128).toStringHex() == std::string("80") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255).toStringHex() == std::string("FF") );

	// --- use 64 bit conversion for big int creation ---

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(256).toStringHex() == std::string("100") );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFF).toStringHex() == std::string("FFFFFFFF") ); // 2^32 - 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000000).toStringHex() == std::string("100000000") ); // 2^32
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000001).toStringHex() == std::string("100000001") ); // 2^32 + 1

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF).toStringHex() == std::string("FFFFFFFFFFFFFFFF") ); // 2^64 - 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFEDCBA9876543210).toStringHex() == std::string("FEDCBA9876543210") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0xFEDCBA987654321).toStringHex() == std::string( "FEDCBA987654321") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(  0xFEDCBA98765432).toStringHex() == std::string(  "FEDCBA98765432") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(   0xFEDCBA9876543).toStringHex() == std::string(   "FEDCBA9876543") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(    0xFEDCBA987654).toStringHex() == std::string(    "FEDCBA987654") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(     0xFEDCBA98765).toStringHex() == std::string(     "FEDCBA98765") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(      0xFEDCBA9876).toStringHex() == std::string(      "FEDCBA9876") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(       0xFEDCBA987).toStringHex() == std::string(       "FEDCBA987") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(        0xFEDCBA98).toStringHex() == std::string(        "FEDCBA98") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(         0xFEDCBA9).toStringHex() == std::string(         "FEDCBA9") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(          0xFEDCBA).toStringHex() == std::string(          "FEDCBA") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(           0xFEDCB).toStringHex() == std::string(           "FEDCB") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(            0xFEDC).toStringHex() == std::string(            "FEDC") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(             0xFED).toStringHex() == std::string(             "FED") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(              0xFE).toStringHex() == std::string(              "FE") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(               0xF).toStringHex() == std::string(               "F") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(               0x0).toStringHex() == std::string(               "0") );

	// 128 bit test!
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(                    18446744073709551615ull).toStringHex()   == std::string(                 "FFFFFFFFFFFFFFFF") ); // 2^64 - 1
	REQUIRE((UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(                    18446744073709551615ull)
			 + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1)).toStringHex()                                                      == std::string(                "10000000000000000") ); // 2^64

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(                   "18446744073709551615", 10).toStringHex() == std::string(                 "FFFFFFFFFFFFFFFF") ); // 2^64 - 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(                   "18446744073709551616", 10).toStringHex() == std::string(                "10000000000000000") ); // 2^64
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(                 "4722366482869645213696", 10).toStringHex() == std::string(              "1000000000000000000") ); // 2^72
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(              "1208925819614629174706176", 10).toStringHex() == std::string(            "100000000000000000000") ); // 2^80
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(            "309485009821345068724781056", 10).toStringHex() == std::string(          "10000000000000000000000") ); // 2^88
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(          "79228162514264337593543950336", 10).toStringHex() == std::string(        "1000000000000000000000000") ); // 2^96
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(       "20282409603651670423947251286016", 10).toStringHex() == std::string(      "100000000000000000000000000") ); // 2^104
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(     "5192296858534827628530496329220096", 10).toStringHex() == std::string(    "10000000000000000000000000000") ); // 2^112
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(  "1329227995784915872903807060280344576", 10).toStringHex() == std::string(  "1000000000000000000000000000000") ); // 2^120
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(  "1329227995784915872903807060280344577", 10).toStringHex() == std::string(  "1000000000000000000000000000001") ); // 2^120 + 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(  "1329227995784915872903807060280344591", 10).toStringHex() == std::string(  "100000000000000000000000000000F") ); // 2^120 + 15
	
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("340282366920938463463374607431768211456", 10).toStringHex() == std::string("100000000000000000000000000000000") ); // 2^128
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("340282366920938463463374607431768211457", 10).toStringHex() == std::string("100000000000000000000000000000001") ); // 2^128 + 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("340282366920938463463374607431768211471", 10).toStringHex() == std::string("10000000000000000000000000000000F") ); // 2^128 + 15
	
	


	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromUint64(0x121fa00ad77d7422ull).toStringHex() 						== std::string( "121FA00AD77D7422") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromString( "121fa00ad77d7422", 16).toStringHex() 					== std::string( "121FA00AD77D7422") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 68)>::fromString( "121fa00ad77d74222", 16).toStringHex() 					== std::string( "121FA00AD77D74222") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 72)>::fromString( "121fa00ad77d742223", 16).toStringHex() 					== std::string( "121FA00AD77D742223") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 76)>::fromString( "121fa00ad77d7422236", 16).toStringHex() 				== std::string( "121FA00AD77D7422236") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 80)>::fromString( "121fa00ad77d7422236d", 16).toStringHex() 				== std::string( "121FA00AD77D7422236D") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 84)>::fromString( "121fa00ad77d7422236d8", 16).toStringHex() 				== std::string( "121FA00AD77D7422236D8") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 88)>::fromString( "121fa00ad77d7422236d88", 16).toStringHex() 				== std::string( "121FA00AD77D7422236D88") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 92)>::fromString( "121fa00ad77d7422236d88f", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88F") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 96)>::fromString( "121fa00ad77d7422236d88fe", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88FE") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(100)>::fromString( "121fa00ad77d7422236d88fe5", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88FE5") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(104)>::fromString( "121fa00ad77d7422236d88fe56", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88FE56") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(108)>::fromString( "121fa00ad77d7422236d88fe561", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE561") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(112)>::fromString( "121fa00ad77d7422236d88fe5618", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE5618") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(116)>::fromString( "121fa00ad77d7422236d88fe5618c", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE5618C") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(120)>::fromString( "121fa00ad77d7422236d88fe5618cf", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE5618CF") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(124)>::fromString( "121fa00ad77d7422236d88fe5618cf0", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618CF0") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString( "121fa00ad77d7422236d88fe5618cf00", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618CF00") );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromUint64(                     1305938385386173474ull).toStringHex()   == std::string( "121FA00AD77D7422") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromString(                    "1305938385386173474", 10).toStringHex() == std::string( "121FA00AD77D7422") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 68)>::fromString(                   "20895014166178775586", 10).toStringHex() == std::string( "121FA00AD77D74222") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 72)>::fromString(                  "334320226658860409379", 10).toStringHex() == std::string( "121FA00AD77D742223") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 76)>::fromString(                 "5349123626541766550070", 10).toStringHex() == std::string( "121FA00AD77D7422236") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 80)>::fromString(                "85585978024668264801133", 10).toStringHex() == std::string( "121FA00AD77D7422236D") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 84)>::fromString(              "1369375648394692236818136", 10).toStringHex() == std::string( "121FA00AD77D7422236D8") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 88)>::fromString(             "21910010374315075789090184", 10).toStringHex() == std::string( "121FA00AD77D7422236D88") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 92)>::fromString(            "350560165989041212625442959", 10).toStringHex() == std::string( "121FA00AD77D7422236D88F") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 96)>::fromString(           "5608962655824659402007087358", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(100)>::fromString(          "89743402493194550432113397733", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(104)>::fromString(        "1435894439891112806913814363734", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE56") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(108)>::fromString(       "22974311038257804910621029819745", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE561") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(112)>::fromString(      "367588976612124878569936477115928", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(116)>::fromString(     "5881423625793998057118983633854860", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618C") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(120)>::fromString(    "94102778012703968913903738141677775", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618CF") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(124)>::fromString(  "1505644448203263502622459810266844400", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618CF0") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString( "24090311171252216041959356964269510400", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618CF00") );

	// --------
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(216)>::fromString("1e 02 bc   1e 8a a1 d6   3b 5b 9c cf   51 6f 9d 67   d2 7b 3c 80   b5 00 00 1c   be 99 1a 08", 16).toStringHex() == std::string("1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") ); //6*32+3*8 = 54 hexDigits * 4bit = 216 bit
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(216)>::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10).toStringHex()                            == std::string("1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(312)>::fromString("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000", 16).toStringHex()                == std::string("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000") ); // 39 Bytes => 312 bit
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(312)>::fromString("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040", 10).toStringHex() == std::string("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000") );

}

TEST_CASE( "unsigned fixed big integer to std:string dec", "[UFBigint]" ) {
	// --- single byte big int creation ---

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0).toStringDec() == std::string("0") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1).toStringDec() == std::string("1") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2).toStringDec() == std::string("2") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(3).toStringDec() == std::string("3") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(4).toStringDec() == std::string("4") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(5).toStringDec() == std::string("5") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(6).toStringDec() == std::string("6") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(7).toStringDec() == std::string("7") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(8).toStringDec() == std::string("8") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(9).toStringDec() == std::string("9") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10).toStringDec() == std::string("10") );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0x42).toStringDec() == std::string("66") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0x7F).toStringDec() == std::string("127") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0x80).toStringDec() == std::string("128") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0xFF).toStringDec() == std::string("255") );

	// --- use 64 bit conversion for big int creation ---

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(256).toStringDec() == std::string("256") );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFF).toStringDec() == std::string("4294967295") ); // 2^32 - 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000000).toStringDec() == std::string("4294967296") ); // 2^32
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000001).toStringDec() == std::string("4294967297") ); // 2^32 + 1

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF).toStringDec() == std::string("18446744073709551615") ); // 2^64 - 1

	// 128 bit test!
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromUint64(                0xFFFFFFFFFFFFFFFF).toStringDec()      == std::string(                   "18446744073709551615") ); // 2^64 - 1
	REQUIRE((UFixBigInt<BIG_INT_BIT_TO_SIZE( 68)>::fromUint64(                0xFFFFFFFFFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(68)>(1)).toStringDec() == std::string(     "18446744073709551616") ); // 2^64
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromString(                 "FFFFFFFFFFFFFFFF", 16).toStringDec() == std::string(                   "18446744073709551615") ); // 2^64 - 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 68)>::fromString(                "10000000000000000", 16).toStringDec() == std::string(                   "18446744073709551616") ); // 2^64
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 76)>::fromString(              "1000000000000000000", 16).toStringDec() == std::string(                 "4722366482869645213696") ); // 2^72
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 84)>::fromString(            "100000000000000000000", 16).toStringDec() == std::string(              "1208925819614629174706176") ); // 2^80
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 92)>::fromString(          "10000000000000000000000", 16).toStringDec() == std::string(            "309485009821345068724781056") ); // 2^88
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(100)>::fromString(        "1000000000000000000000000", 16).toStringDec() == std::string(          "79228162514264337593543950336") ); // 2^96
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(108)>::fromString(      "100000000000000000000000000", 16).toStringDec() == std::string(       "20282409603651670423947251286016") ); // 2^104
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(116)>::fromString(    "10000000000000000000000000000", 16).toStringDec() == std::string(     "5192296858534827628530496329220096") ); // 2^112
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(  "1000000000000000000000000000000", 16).toStringDec() == std::string(  "1329227995784915872903807060280344576") ); // 2^120
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(  "1000000000000000000000000000001", 16).toStringDec() == std::string(  "1329227995784915872903807060280344577") ); // 2^120 + 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(  "100000000000000000000000000000F", 16).toStringDec() == std::string(  "1329227995784915872903807060280344591") ); // 2^120 + 15
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(132)>::fromString("100000000000000000000000000000000", 16).toStringDec() == std::string("340282366920938463463374607431768211456") ); // 2^128
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(132)>::fromString("100000000000000000000000000000001", 16).toStringDec() == std::string("340282366920938463463374607431768211457") ); // 2^128 + 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(132)>::fromString("10000000000000000000000000000000F", 16).toStringDec() == std::string("340282366920938463463374607431768211471") ); // 2^128 + 15

	//REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf", 16).toStringDec() == std::string( "94102778012703968913903738141677775") );
	//REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf00", 16).toStringDec() == std::string( "24090311171252216041959356964269510400") );

	//REQUIRE( UArbBigInt::fromString( "94102778012703968913903738141677775", 10).toStringDec() == std::string( "94102778012703968913903738141677775") );
	//REQUIRE( UArbBigInt::fromString( "24090311171252216041959356964269510400", 10).toStringDec() == std::string( "24090311171252216041959356964269510400") );

	// --------
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromUint64(0x121fa00ad77d7422ull).toStringDec()                         == std::string(                    "1305938385386173474") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromString( "121fa00ad77d7422", 16).toStringDec()                       == std::string(                    "1305938385386173474") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 68)>::fromString( "121fa00ad77d74222", 16).toStringDec()                      == std::string(                   "20895014166178775586") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 72)>::fromString( "121fa00ad77d742223", 16).toStringDec()                     == std::string(                  "334320226658860409379") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 76)>::fromString( "121fa00ad77d7422236", 16).toStringDec()                    == std::string(                 "5349123626541766550070") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 80)>::fromString( "121fa00ad77d7422236d", 16).toStringDec()                   == std::string(                "85585978024668264801133") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 84)>::fromString( "121fa00ad77d7422236d8", 16).toStringDec()                  == std::string(              "1369375648394692236818136") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 88)>::fromString( "121fa00ad77d7422236d88", 16).toStringDec()                 == std::string(             "21910010374315075789090184") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 92)>::fromString( "121fa00ad77d7422236d88f", 16).toStringDec()                == std::string(            "350560165989041212625442959") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 96)>::fromString( "121fa00ad77d7422236d88fe", 16).toStringDec()               == std::string(           "5608962655824659402007087358") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(100)>::fromString( "121fa00ad77d7422236d88fe5", 16).toStringDec()              == std::string(          "89743402493194550432113397733") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(104)>::fromString( "121fa00ad77d7422236d88fe56", 16).toStringDec()             == std::string(        "1435894439891112806913814363734") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(108)>::fromString( "121fa00ad77d7422236d88fe561", 16).toStringDec()            == std::string(       "22974311038257804910621029819745") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(112)>::fromString( "121fa00ad77d7422236d88fe5618", 16).toStringDec()           == std::string(      "367588976612124878569936477115928") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(116)>::fromString( "121fa00ad77d7422236d88fe5618c", 16).toStringDec()          == std::string(     "5881423625793998057118983633854860") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(120)>::fromString( "121fa00ad77d7422236d88fe5618cf", 16).toStringDec()         == std::string(    "94102778012703968913903738141677775") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(124)>::fromString( "121fa00ad77d7422236d88fe5618cf0", 16).toStringDec()        == std::string(  "1505644448203263502622459810266844400") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString( "121fa00ad77d7422236d88fe5618cf00", 16).toStringDec()       == std::string( "24090311171252216041959356964269510400") );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromUint64(                     1305938385386173474ull  ).toStringDec() == std::string(                    "1305938385386173474") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 64)>::fromString(                    "1305938385386173474", 10).toStringDec() == std::string(                    "1305938385386173474") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 68)>::fromString(                   "20895014166178775586", 10).toStringDec() == std::string(                   "20895014166178775586") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 72)>::fromString(                  "334320226658860409379", 10).toStringDec() == std::string(                  "334320226658860409379") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 76)>::fromString(                 "5349123626541766550070", 10).toStringDec() == std::string(                 "5349123626541766550070") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 80)>::fromString(                "85585978024668264801133", 10).toStringDec() == std::string(                "85585978024668264801133") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 84)>::fromString(              "1369375648394692236818136", 10).toStringDec() == std::string(              "1369375648394692236818136") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 88)>::fromString(             "21910010374315075789090184", 10).toStringDec() == std::string(             "21910010374315075789090184") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 92)>::fromString(            "350560165989041212625442959", 10).toStringDec() == std::string(            "350560165989041212625442959") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 96)>::fromString(           "5608962655824659402007087358", 10).toStringDec() == std::string(           "5608962655824659402007087358") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(100)>::fromString(          "89743402493194550432113397733", 10).toStringDec() == std::string(          "89743402493194550432113397733") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(104)>::fromString(        "1435894439891112806913814363734", 10).toStringDec() == std::string(        "1435894439891112806913814363734") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(108)>::fromString(       "22974311038257804910621029819745", 10).toStringDec() == std::string(       "22974311038257804910621029819745") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(112)>::fromString(      "367588976612124878569936477115928", 10).toStringDec() == std::string(      "367588976612124878569936477115928") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(116)>::fromString(     "5881423625793998057118983633854860", 10).toStringDec() == std::string(     "5881423625793998057118983633854860") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(120)>::fromString(    "94102778012703968913903738141677775", 10).toStringDec() == std::string(    "94102778012703968913903738141677775") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(124)>::fromString(  "1505644448203263502622459810266844400", 10).toStringDec() == std::string(  "1505644448203263502622459810266844400") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString( "24090311171252216041959356964269510400", 10).toStringDec() == std::string( "24090311171252216041959356964269510400") );

	// --------
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(216)>::fromString("1e02bc 1e8aa1d6 3b5b9ccf 516f9d67 d27b3c80 b500001c be991a08", 16).toStringDec()            == std::string("12345678900000000000000000000000000000000000000000000123456789000") );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(216)>::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10).toStringDec() == std::string("12345678900000000000000000000000000000000000000000000123456789000") );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(308)>::fromString("12345 6789ABCD EF000000 00000000 00000000 00000000 00000000 00000012 3456789A BCDEF000", 16).toStringDec()                == std::string("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040") ); // 39 Bytes => 312 bit
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(308)>::fromString("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040", 10).toStringDec() == std::string("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040") );
}

TEST_CASE( "unsigned fixed big integer from std:string", "[UFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "0", 10).toUint64() 	==   0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "1", 10).toUint64() 	==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "2", 10).toUint64() 	==   2 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "3", 10).toUint64() 	==   3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "4", 10).toUint64() 	==   4 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "5", 10).toUint64() 	==   5 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "6", 10).toUint64() 	==   6 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "7", 10).toUint64() 	==   7 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "8", 10).toUint64() 	==   8 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "9", 10).toUint64() 	==   9 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10", 10).toUint64() 	==  10 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("77", 10).toUint64() 	==  77 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("127", 10).toUint64() 	== 127 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("128", 10).toUint64() 	== 128 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("255", 10).toUint64() 	== 255 );


	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("0", 16).toUint64() 	==  0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 16).toUint64() 	==  1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("2", 16).toUint64() 	==  2 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("3", 16).toUint64() 	==  3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("4", 16).toUint64() 	==  4 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("5", 16).toUint64() 	==  5 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("6", 16).toUint64() 	==  6 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("7", 16).toUint64() 	==  7 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("8", 16).toUint64() 	==  8 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("9", 16).toUint64() 	==  9 );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("a", 16).toUint64() 	== 10 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("b", 16).toUint64() 	== 11 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("c", 16).toUint64() 	== 12 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("d", 16).toUint64() 	== 13 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("e", 16).toUint64() 	== 14 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("f", 16).toUint64() 	== 15 );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("A", 16).toUint64() 	== 10 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("B", 16).toUint64() 	== 11 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("C", 16).toUint64() 	== 12 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("D", 16).toUint64() 	== 13 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("E", 16).toUint64() 	== 14 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("F", 16).toUint64() 	== 15 );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("7F", 16).toUint64()	== 127 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("80", 16).toUint64()	== 128 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("FF", 16).toUint64()	== 255 );

	// leading zeros
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(  "01", 10).toUint64() 	==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "001", 10).toUint64() 	==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("0255", 10).toUint64() 	==   255 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(9)>::fromString("0256", 10).toUint64() 	==   256 );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(  "00", 16).toUint64() 	==   0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(  "01", 16).toUint64() 	==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(  "0f", 16).toUint64() 	==   15 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("000A", 16).toUint64() 	==   10 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00ff", 16).toUint64() 	==   255 );
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00 00 00 00   00 00 00 00   00 00 00 00   00 00 00 00   00 00 00 09", 16).toUint64() 	==   9 ); // 160 bits ful of zeros:  that is is even for 64 bit words an interesting leading zero test

	// 2 Bytes (16 bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("256", 10).toUint64() == 256 ); // 2^16
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0100", 16).toUint64() == 256 );

	// 4 Bytes (32 bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("4294967295", 10).toUint64() == 0xFFFFFFFFull ); // 2^32 - 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("FFFFFFFF", 16).toUint64() == 0xFFFFFFFFull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("01234567", 16).toUint64() == 0x01234567ull );

	// 8 Bytes (64 bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("4294967296", 10).toUint64() == 0x0100000000ull ); // 2^32
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0100000000", 16).toUint64() == 0x0100000000ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("4294967297", 10).toUint64() == 0x0100000001ull ); // 2^32 + 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0100000001", 16).toUint64() == 0x0100000001ull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0123456789ABCDEF", 16).toUint64() == 0x0123456789ABCDEFull );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("fedcba9876543210", 16).toUint64() == 0xFEDCBA9876543210ull );


	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("18446744073709551615", 10).toUint64() 	== 0xFFFFFFFFFFFFFFFFull ); // 2^64 - 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("FFFFFFFFFFFFFFFF", 16).toUint64() 		== 0xFFFFFFFFFFFFFFFFull );

	// --- use 65 bit conversion for big int reference creation ---
	// this uses also the BIG int == operator, therefore a failed test could als be a problem of the == operator implementation
	UFixBigInt<BIG_INT_BIT_TO_SIZE(65)> one_65bit(1);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("18446744073709551616", 10) == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit) ); // 2^64
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000000", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit) ); // 2^64
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000001", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x01)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000002", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x02)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000003", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x03)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000004", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x04)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000005", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x05)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000006", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x06)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000007", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x07)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000008", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x08)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "010000000000000009", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x09)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "01000000000000000A", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0A)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "01000000000000000B", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0B)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "01000000000000000C", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0C)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "01000000000000000D", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0D)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "01000000000000000E", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0E)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "01000000000000000F", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0x0F)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "0100000000000000Fe", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0xFE)) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString( "0100000000000000Ff", 16)  == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + one_65bit + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(0xFF)) );


	// ---- ignore blank
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(" 1 ", 10) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(1ull) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(" 1 1 ", 10) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(11ull) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString(" 222 111 000 ", 10) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(222111000ull) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString(" 000 111 222  ", 10) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(111222ull) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("        1 2 3 4 5 6 7 8 9 0      ", 10) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(1234567890ull) );
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("01 F3 86 9C 69 BB 1C 01", 16) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x01F3869C69BB1C01ull) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("140 604 019 725 507 585", 10) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x01F3869C69BB1C01ull) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("123 456 789 000 000 321", 10) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(123456789000000321ull) );
	
	
	
	
	// ---- test overflow dedection
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("256", 10) ); // 2^8 => requires 9 bit
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("65536", 10) ); // 2^16 => requires 17 bit
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("4294967296", 10) ); // 2^32 => requires 33 bit
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint64_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("18446744073709551616", 10) ); // 2^64 => requires 65 bit
	}
	REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("340282366920938463463374607431768211456", 10) ); // 2^128 => requires 129 bit
}

TEST_CASE( "unsigned fixed big integer comparisons", "[UFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) != UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) != UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) <= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) < UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) > UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10) >  UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(9) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(9) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(9) 	<  UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(9) 	<= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10) <= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(10) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(0xFF) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) <= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(0xFF) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromUint64(0xFF) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) 		<  UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) 		<= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) 	>  UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) 	>= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) 		<  UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) 		<= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) 	>  UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) 	>= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(245) 	<  UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(245) 	<= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) 	>  UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(245) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) 	>= UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(245) );

	// 2 Bytes (16 bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(255) 				 <  UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(255) 				 <= UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) >  UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(255) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(255) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) <= UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0101) >  UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0101) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0101) <  UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0102) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0101) <= UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0102) );

	// 8 Bytes (64bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFE) != UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xEFFFFFFFFFFFFFFF) != UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) <= UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFE) <  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFF) >  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFFFE) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF00) >  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>(1) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF00) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>(1) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>(1) 							 <  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF00) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>(1) 							 <= UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF00) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) != UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x01) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) >  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x01) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x01) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x01) 				<  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x01) 				<= UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) != UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFF01) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) >  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFF01) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) >= UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFF01) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFF01) 			<  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFF01) 			<= UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFFFFFFFF01) );

	//REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) != UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) );

	// 9 Bytes (65bit)
	UFixBigInt<BIG_INT_BIT_TO_SIZE(65)> one_65bit(1);
	UFixBigInt<BIG_INT_BIT_TO_SIZE(65)> ten_65bit(10);
	UFixBigInt<BIG_INT_BIT_TO_SIZE(65)> eleven_65bit(11);
	
	REQUIRE(  UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) 					!= (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + one_65bit) );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + one_65bit) 		== (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + one_65bit) );
	REQUIRE(  UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) 					<  (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + one_65bit) );
	REQUIRE(  UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) 					<= (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + one_65bit) );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + one_65bit) 		>   UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + one_65bit) 		>=  UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + ten_65bit) 		!= (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + eleven_65bit) );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + ten_65bit) 		== (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + ten_65bit) );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + ten_65bit)		<  (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + eleven_65bit) );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + ten_65bit)		<= (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + eleven_65bit) );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + eleven_65bit) 	>  (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + ten_65bit) );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + eleven_65bit) 	>= (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + ten_65bit) );

	//REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(11)) 	!=  (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(11)) );
}

TEST_CASE( "unsigned fixed big integer shift left", "[UFBigint]" ) {

	// 1 Byte (8bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("100000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(" 0000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("1", 2) <<  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000 0", 2) );
	}
	
	// 2 Byte (16bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) <<  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) << 10 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) << 11 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) << 12 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) << 13 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) << 14 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) << 15 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) << 16 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString(" 0000000 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1", 2) << 16 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00000000 0", 2) );
	}
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString(" 0000000 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00000000 0", 2) );
	}
	
	// 3 Byte (24bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 16 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 17 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 18 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 19 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 20 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 21 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 22 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 23 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 24 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString(" 0000000 00000000 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1", 2) << 24 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 00000000 0", 2) );
	}
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString(" 0000000 00000000 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 00000000 0", 2) );
	}
	
	// 4 Byte (32bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 24 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 25 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 26 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 27 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 28 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 29 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 30 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 31 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 32 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString(" 0000000 00000000 00000000 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1", 2) << 32 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 00000000 0", 2) );
	}
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString(" 0000000 00000000 00000000 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10000000 00000000 00000000 00000000 0", 2) );
	}

	// 5 Byte (40bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 32 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 00000000 00000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 33 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 00000000 00000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 34 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 00000000 00000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 35 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 00000000 00000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 36 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 00000000 00000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 37 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 00000000 00000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 38 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 00000000 00000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 39 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 00000000 00000000 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 40 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString(" 0000000 00000000 00000000 00000000 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("1", 2) << 40 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 00000000 00000000 00000000 0", 2) );
	}

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString(" 0000000 00000000 10110111 00000000 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(40)>::fromString("10000000 00000000 10110111 00000000 00000000 0", 2) );
	}

	// 8 Byte (64bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 56 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 57 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 58 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 59 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 60 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 61 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 62 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 63 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("1", 2) << 64 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString(" 0000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString(" 0000000 01010101 00000000 10110111 00000000 11111101 00000000 00000000 0", 2) );

	// 9 Byte (72bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 64 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 65 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 66 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 67 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 68 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 69 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 70 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 71 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 72 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString(" 0000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 2) << 72 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
	}

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000000", 2) );
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString(" 0000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000000 0", 2) );
	} else {
		REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000000 0", 2) );
	}


	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                       1) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                       2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                       4) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                       8) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                      16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                      32) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                      64) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                     128) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                     256) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                     512) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  10 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                    1024) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  11 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                    2048) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  12 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                    4096) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  13 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                    8192) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  14 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                   16384) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  15 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                   32768) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  16 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                   65536) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  17 == UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(96)>::fromUint64(                                  131072) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  63 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromUint64(                     9223372036854775808ull) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  64 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                   "18446744073709551616", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  65 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                   "36893488147419103232", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  66 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                   "73786976294838206464", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  67 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                  "147573952589676412928", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  68 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                  "295147905179352825856", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  69 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                  "590295810358705651712", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  70 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                 "1180591620717411303424", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  71 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                 "2361183241434822606848", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  72 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                 "4722366482869645213696", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  73 == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(                 "9444732965739290427392", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(204)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) << 127 == UFixBigInt<BIG_INT_BIT_TO_SIZE(204)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(204)>::fromString("170141183460469231731687303715884105728", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(204)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) << 128 == UFixBigInt<BIG_INT_BIT_TO_SIZE(204)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(204)>::fromString("340282366920938463463374607431768211456", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(204)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) << 129 == UFixBigInt<BIG_INT_BIT_TO_SIZE(204)>::fromString("3529260907631713815077", 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(204)>::fromString("680564733841876926926749214863536422912", 10) );
	
}

TEST_CASE( "unsigned fixed big integer shift right", "[UFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString( "1000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(  "100000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(   "10000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(    "1000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(     "100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(      "10", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(       "1", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(       "0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >>  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(       "0", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) >> 16 == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString(       "0", 2) );

	// 2 Byte (16bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("1000001100101101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0100000110010110", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0010000011001011", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0001000001100101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000100000110010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000010000011001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000001000001100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000100000110", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000010000011", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >>  9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000001000001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >> 10 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000000100000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >> 11 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000000010000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >> 12 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000000001000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >> 13 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000000000100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >> 14 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000000000010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >> 15 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000000000001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >> 16 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >> 17 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000011 00101101", 2) >> 32 == UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("0000000000000000", 2) );

	// 8 Byte (64bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000010000110110000000101010100101010100011000100100111000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000001000011011000000010101010010101010001100010010011100000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000100001101100000001010101001010101000110001001001110000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000010000110110000000101010100101010100011000100100111000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000001000011011000000010101010010101010001100010010011100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000100001101100000001010101001010101000110001001001110", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000010000110110000000101010100101010100011000100100111", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000001000011011000000010101010010101010001100010010011", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000100001101100000001010101001010101000110001001001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  10 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000010000110110000000101010100101010100011000100100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  11 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000001000011011000000010101010010101010001100010010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  12 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000100001101100000001010101001010101000110001001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  13 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000010000110110000000101010100101010100011000100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  14 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000001000011011000000010101010010101010001100010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  15 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000100001101100000001010101001010101000110001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  16 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000010000110110000000101010100101010100011000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  17 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000001000011011000000010101010010101010001100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  18 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000100001101100000001010101001010101000110", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  19 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000010000110110000000101010100101010100011", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  20 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000001000011011000000010101010010101010001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  21 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000100001101100000001010101001010101000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  22 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000010000110110000000101010100101010100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  23 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000001000011011000000010101010010101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  24 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000100001101100000001010101001010101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  25 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000010000110110000000101010100101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  26 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000001000011011000000010101010010101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  27 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000100001101100000001010101001010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  28 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000010000110110000000101010100101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  29 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000001000011011000000010101010010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  30 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000100001101100000001010101001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  31 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000010000110110000000101010100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  32 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000001000011011000000010101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  33 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000100001101100000001010101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  34 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000010000110110000000101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  35 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000001000011011000000010101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  36 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000100001101100000001010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  37 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000010000110110000000101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  38 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000001000011011000000010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  39 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000100001101100000001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  40 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000010000110110000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  41 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000001000011011000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  42 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000100001101100000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  43 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000010000110110000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  44 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000001000011011000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  45 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000100001101100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  46 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000010000110110", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  47 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000001000011011", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  48 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000100001101", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  49 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000010000110", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  50 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000001000011", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  51 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000100001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  52 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000010000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  53 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000001000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  54 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  55 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  56 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  57 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  58 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  59 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  60 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  61 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  62 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  63 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  64 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  65 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  66 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  67 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >> 127 == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );


	// 9 Byte (72bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   0 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                      1) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   1 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                      2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   2 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                      4) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   3 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                      8) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   4 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                     16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   5 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                     32) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   6 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                     64) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   7 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                    128) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   8 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                    256) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   9 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                    512) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  10 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                   1024) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  11 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                   2048) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  12 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                   4096) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  13 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                   8192) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  14 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                  16384) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  15 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                  32768) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  16 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(                  65536) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  63 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromUint64(    9223372036854775808ull) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  64 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString(  "18446744073709551616", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  65 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString(  "36893488147419103232", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  66 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString(  "73786976294838206464", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  67 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString( "147573952589676412928", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  68 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString( "295147905179352825856", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  69 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString( "590295810358705651712", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  70 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("3529260907631713815077", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1180591620717411303424", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  71 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("1", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  72 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("0", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  73 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("0", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >> 127 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("0", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >> 128 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("0", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >> 129 == UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("0", 10) );
}

TEST_CASE( "unsigned fixed big integer addition", "[UFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0) + UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0)).toUint64()	==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) + UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0)).toUint64()	==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0) + UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64()	==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) + UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64()	==   2 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2) + UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64()	==   3 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) + UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64()	==   3 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) + UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64()	==  11 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(128) + UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127)).toUint64()	== 255 );

	// 2 Bytes (16 bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(128) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(128)).toUint64()	== 0x0100ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(255) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(  1)).toUint64()	== 0x0100ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(  1) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(255)).toUint64()	== 0x0100ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(255) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(255)).toUint64()	== 0x01FEull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x7FFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x7FFF) 											).toUint64() == 0xFFFEull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x7FFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x7FFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(0)	).toUint64() == 0xFFFEull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x7FFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x7FFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(1) 	).toUint64() == 0xFFFFull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(1) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x7FFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x7FFF) 	).toUint64() == 0xFFFFull );

	// 4 Bytes (32bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x8000) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x8000)).toUint64() 	== 0x010000ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0xFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(  0x01)).toUint64() 	== 0x010000ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(  0x01) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0xFFFF)).toUint64() 	== 0x010000ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0xFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0xFFFF)).toUint64() 	== 0x01FFFEull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x7FFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x7FFFFFFF) 											).toUint64() == 0xFFFFFFFEull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x7FFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x7FFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>(0) 	).toUint64() == 0xFFFFFFFEull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x7FFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x7FFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>(1) 	).toUint64() == 0xFFFFFFFFull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>(1) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x7FFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x7FFFFFFF) 	).toUint64() == 0xFFFFFFFFull );

	// 8 Bytes (64bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x80000000) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x80000000)).toUint64() 	== 0x0100000000ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(      0x01)).toUint64() 	== 0x0100000000ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(      0x01) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFF)).toUint64() 	== 0x0100000000ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0xFFFFFFFF)).toUint64() 	== 0x01FFFFFFFEull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x7FFFFFFFFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x7FFFFFFFFFFFFFFF) 											).toUint64() == 0xFFFFFFFFFFFFFFFEull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x7FFFFFFFFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x7FFFFFFFFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>(0)	).toUint64() == 0xFFFFFFFFFFFFFFFEull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x7FFFFFFFFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x7FFFFFFFFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>(1)	).toUint64() == 0xFFFFFFFFFFFFFFFFull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>(1) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x7FFFFFFFFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x7FFFFFFFFFFFFFFF)	).toUint64() == 0xFFFFFFFFFFFFFFFFull );

	// 16 Bytes (128bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("18446744073709551616", 10) == (UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFFull) + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>(1)) ); // 2^64

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0x8000000000000000) + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0x8000000000000000) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("18446744073709551616", 10) ); // 2^64
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(              0x01) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("010000000000000000", 16) ); // 2^64
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(              0x01) + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("010000000000000000", 16) ); // 2^64
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) + UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromUint64(0xFFFFFFFFFFFFFFFF) 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(65)>::fromString("01FFFFFFFFFFFFFFFE", 16) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) 				                             == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(0)	 == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1)	 == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(1) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) );
	
	// test overflow exception
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("80000000 00000000 00000000 00000000", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("80000000 00000000 00000000 00000000", 16)).toStringHex()                                           == UArbBigInt::fromString("1 00000000 00000000 00000000 00000000", 16).toStringHex() );
	REQUIRE_THROWS( (UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("80000000 00000000 00000000 00000000", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("80000000 00000000 00000000 00000000", 16)).toStringHex()                                           == UArbBigInt::fromString("1 00000000 00000000 00000000 00000000", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>(2) + UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16)).toStringHex() == UArbBigInt::fromString("1 00000000 00000000 00000000 00000000", 16).toStringHex() );
	REQUIRE_THROWS( (UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(2) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16)).toStringHex() == UArbBigInt::fromString("1 00000000 00000000 00000000 00000000", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>(2)).toStringHex() == UArbBigInt::fromString("1 00000000 00000000 00000000 00000000", 16).toStringHex() );
	REQUIRE_THROWS( (UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(2)).toStringHex() == UArbBigInt::fromString("1 00000000 00000000 00000000 00000000", 16).toStringHex() );
	
	

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("123456 789abcde f0000000 00000000 12345678 9abcdef0", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("fedcba9 87654321 00000000 00000000 fedcba98 76543210", 16) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("fffffff ffffffff f0000000 00000001 11111111 11111100", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("fedcba9 87654321 00000000 00000000 fedcba98 76543210", 16) + UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("123456 789abcde f0000000 00000000 12345678 9abcdef0", 16) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("FFFFFFF FFFFFFFF F0000000 00000001 11111111 11111100", 16) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(160)>::fromString("123456789000000000000000000000000000001234567890", 10) + UFixBigInt<BIG_INT_BIT_TO_SIZE(160)>::fromString("987654321000000000000000000000000000009876543210", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(160)>::fromString("1111111110000000000000000000000000000011111111100", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(160)>::fromString("987654321000000000000000000000000000009876543210", 10) + UFixBigInt<BIG_INT_BIT_TO_SIZE(160)>::fromString("123456789000000000000000000000000000001234567890", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(160)>::fromString("1111111110000000000000000000000000000011111111100", 10) );
}

TEST_CASE( "unsigned fixed big integer subtraction", "[UFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0) - UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) - UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   0 );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  9) - UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   8 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  9) - UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  9)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) - UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  9)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) - UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0)).toUint64() == 255 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) - UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) - UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 1)).toUint64() 	== 254 );

	// 2 Bytes (16 bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100ull)).toUint64() ==   0x00ull ); // 256 - 256 = 0
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0101ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100ull)).toUint64() ==   0x01ull ); // 257 - 256 = 1
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0101ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(  0x01ull)).toUint64() == 0x0100ull ); // 257 - 1 = 256
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0101ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(  0x02ull)).toUint64() ==   0xFFull ); // 257 - 2 = 255

	// 4 Bytes (32bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x010000ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x010000ull)).toUint64() ==     0x00ull ); // 2^16 - 2^16 = 0
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x010001ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x010000ull)).toUint64() ==     0x01ull ); // (2^16 + 1) - 2^16 = 1
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x010001ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(    0x01ull)).toUint64() == 0x010000ull ); // (2^16 + 1) - 1 = 2^16
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x010001ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(    0x02ull)).toUint64() == 0x00FFFFull ); // (2^16 + 1) - 2 = 2^16 - 1

	// 8 Bytes (64bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000000ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000000ull)).toUint64() 	==         0x00ull ); // 2^32 - 2^32 = 0
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000001ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000000ull)).toUint64() 	==         0x01ull ); // (2^32 + 1) - 2^32 = 1
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000001ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(        0x01ull)).toUint64() 	== 0x0100000000ull ); // (2^32 + 1) - 1 = 2^32
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(0x0100000001ull) - UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(        0x02ull)).toUint64() 	== 0x00FFFFFFFFull ); // (2^32 + 1) - 2 = 2^32 - 1

	// 16 Bytes (128bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("010000000000000000", 16) - UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("010000000000000000", 16) 	== 							  UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(0x00)      ); // 2^64 - 2^64 = 0
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("010000000000000001", 16) - UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("010000000000000000", 16) 	==                            UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>(0x01)      ); // (2^64 + 1) - 2^64 = 1
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("010000000000000001", 16) - UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(               0x01ull)	 	== UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("010000000000000000", 16) ); // (2^64 + 1) - 1 = 2^64
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("010000000000000001", 16) - UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(               0x02ull)		== UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0xFFFFFFFFFFFFFFFFull)   ); // (2^64 + 1) - 2 = 2^64 - 1

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString(" fedcba9 87654321 00000000 00000000 fedcba98 76543210", 16) - UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("  123456 789abcde f0000000 00000000 12345678 9abcdef0", 16) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("  fdb9753 0eca8642 10000000 00000000 eca8641f db975320", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("987 654 321 000 000 000 000 000 000 000 000 000 009 876 543 210", 10) - UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("123 456 789 000 000 000 000 000 000 000 000 000 001 234 567 890", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("864 197 532 000 000 000 000 000 000 000 000 000 008 641 975 320", 10) );

}

TEST_CASE( "unsigned fixed big integer multiplication", "[UFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0) * UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) * UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) * UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2) * UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(1)).toUint64() ==   2 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) * UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2)).toUint64() ==   2 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) * UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(0)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 11) * UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2)).toUint64() ==  22 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127) * UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(2)).toUint64() == 254 );

	// 2 Bytes (16 bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(128) * UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(              2)).toUint64() == 0x0100ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(128) * UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(              4)).toUint64() == 0x0200ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(123) * UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(532)).toUint64() == 0xFF9Cull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>( 98) * UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(571)).toUint64() == 0xDA96ull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0FFull)).toUint64() == 0xFF00ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0011ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0FFull)).toUint64() == 0x10EFull );

	// 4 Bytes (32bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(    0xFFFFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xFFFFull)).toUint64() == 0xFFFE0001ull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(    0x0100ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0x0100ull)).toUint64() ==   0x010000ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(    0x0100ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0x0F00ull)).toUint64() ==   0x0F0000ull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0x55555555ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(  0x003ull)).toUint64() == 0xFFFFFFFFull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(    0xEFEFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(   0xEFull)).toUint64() ==   0xE00021ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(    0xEFEFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xEFEFull)).toUint64() == 0xE0E02121ull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(0xff9Cull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(  0x7Bull)).toUint64() == 0x7ACFF4ull ); // 65436 * 123 = 8048628

	// 8 Bytes (64bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(    0xFFFFFFFFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0xFFFFFFFFull)).toUint64() == 0xFFFFFFFE00000001ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(    0xFFFFFFFFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(       0x02ull)).toUint64() ==        0x1FFFFFFFEull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(    0xFEDCBA98ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x12345678ull)).toUint64() == 0x121FA00A35068740ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(    0xFEDCBA98ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x12345678ull)).toUint64() == 0xFEDCBA98ull * 0x12345678ull);

	// 16 Bytes (128bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFFFFFFFFFFFFFFFFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0xFFFFFFFFFFFFFFFFull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("FFFFFFFFFFFFFFFE0000000000000001", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFFFFFFFFFFFFFFFFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(               0x02ull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(               "1FFFFFFFFFFFFFFFE", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFEDCBA9876543210ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0x123456789ABCDEF0ull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("24090311171252216041959356964269510400", 10) ); // 18364758544493064720 * 1311768467463790320 = 24090311171252216041959356964269510400
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFEDCBA9876543210ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0x123456789ABCDEF0ull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("121fa00ad77d7422236d88fe5618cf00", 16) ); // 18364758544493064720 * 1311768467463790320 = 24090311171252216041959356964269510400
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFEDCBA9876543210ull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0x123456789ABCDEF0ull)).toStringDec() == std::string("24090311171252216041959356964269510400") ); // 18364758544493064720 * 1311768467463790320 = 24090311171252216041959356964269510400

	// -------
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(376)>::fromString(" 123456 789abcde f0000000 00000000 12345678 9abcdef0", 16) *  UFixBigInt<BIG_INT_BIT_TO_SIZE(376)>::fromString("fedcba9 87654321 00000000 00000000 fedcba98 76543210", 16) == UFixBigInt<BIG_INT_BIT_TO_SIZE(376)>::fromString("121fa 00ad77d7 422236d8 8fe5618c f13419a0 b84f54b6 445a4618 e3b7a5bf 121fa00a d77d7422 236d88fe 5618cf00", 16) ); // 184bit + 188bit = 372bit
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(376)>::fromString("fedcba9 87654321 00000000 00000000 fedcba98 76543210", 16) *  UFixBigInt<BIG_INT_BIT_TO_SIZE(376)>::fromString(" 123456 789abcde f0000000 00000000 12345678 9abcdef0", 16) == UFixBigInt<BIG_INT_BIT_TO_SIZE(376)>::fromString("121fa 00ad77d7 422236d8 8fe5618c f13419a0 b84f54b6 445a4618 e3b7a5bf 121fa00a d77d7422 236d88fe 5618cf00", 16) ); // 188bit + 184bit = 372bit

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(320)>::fromString("123456789000000000000000000000000000001234567890", 10) *  UFixBigInt<BIG_INT_BIT_TO_SIZE(320)>::fromString("987654321000000000000000000000000000009876543210", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(320)>::fromString("121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) ); // 160bit + 160bit = 320bit
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(320)>::fromString("987654321000000000000000000000000000009876543210", 10) *  UFixBigInt<BIG_INT_BIT_TO_SIZE(320)>::fromString("123456789000000000000000000000000000001234567890", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(320)>::fromString("121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) );
	
	// --- overflow test ---
	REQUIRE_THROWS( (UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("1 00000000 00000000 00000000 00000000 00000000 00000000", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("1 00000000 00000000 00000000 00000000 00000000 00000000", 16)).toStringHex() == UArbBigInt::fromString(" 1 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 16).toStringHex() ); // "mulSchool not posible without overflow (aSize + bSize >= S)"
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(    0xFFFFFFFFFFFFFFFFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x0ull).toUint64() ==  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x0ull) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(    0xFFFFFFFFFFFFFFFFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x1ull).toUint64() ==  UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0xFFFFFFFFFFFFFFFFull) );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFFFFFFFFFFFFFFFFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0x2ull)).toStringHex() == "1FFFFFFFFFFFFFFFE" );
	REQUIRE_THROWS( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(    0xFFFFFFFFFFFFFFFFull) * UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x2ull)).toStringHex() == "1FFFFFFFFFFFFFFFE" ); // "mulSchool not posible without overflow (r2)"
	
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("FF FF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1 01", 16)).toStringHex() == UArbBigInt::fromString("1 00 FE FF", 16).toStringHex() );
		REQUIRE_THROWS( (UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("FF FF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1 01", 16)).toStringHex() == UArbBigInt::fromString("1 00 FE FF", 16).toStringHex() ); // "mulSchool not posible without overflow (r1)"
		REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("FF FF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("1 FF", 16)).toStringHex() == UArbBigInt::fromString("1 FE FE 01", 16).toStringHex() );
		REQUIRE_THROWS( (UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("FF FF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("1 FF", 16)).toStringHex() == UArbBigInt::fromString("1 FE FE 01", 16).toStringHex() ); // "mulSchool not posible without overflow (r1)"
	}
	
	//std::cout << (UArbBigInt::fromString("FFFFFFFFF FFFFFFF FFFFFFFF FFFFFFFF", 16) * UArbBigInt::fromString("1 FFFFFFFF FFFFFFFF", 16)).toStringHex() << std::endl;
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("80000000 00000000", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("20000000 00000000", 16)).toStringHex() == UArbBigInt::fromString(" 10000000 00000000 00000000 00000000", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("80000000 00000000 00000000 00000000", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("  20000000 00000000", 16)).toStringHex() == UArbBigInt::fromString("  10000000 00000000 00000000 00000000 00000000 00000000", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("80000000 00000000 80000000 00000000", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("  20000000 00000000", 16)).toStringHex() == UArbBigInt::fromString("  10000000 00000000 10000000 00000000 00000000 00000000", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("80000000 00000000 FFFFFFFF FFFFFFFF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("  20000000 00000000", 16)).toStringHex() == UArbBigInt::fromString("  10000000 00000000 1FFFFFFF FFFFFFFF E0000000 00000000", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("8FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("  20000000 00000000", 16)).toStringHex() == UArbBigInt::fromString("  11FFFFFF FFFFFFFF FFFFFFFF FFFFFFFF E0000000 00000000", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("  20000000 00000000", 16)).toStringHex() == UArbBigInt::fromString("  1FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF E0000000 00000000", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("  FFFFFFFF FFFFFFFF", 16)).toStringHex() == UArbBigInt::fromString("  FFFFFFFF FFFFFFFE FFFFFFFF FFFFFFFF 00000000 00000001", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("1 00000000 00000000", 16)).toStringHex() == UArbBigInt::fromString("  FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF 00000000 00000000", 16).toStringHex() );
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("1 00000000 00000001", 16)).toStringHex() == UArbBigInt::fromString("1 00000000 00000000 FFFFFFFF FFFFFFFE FFFFFFFF FFFFFFFF", 16).toStringHex() );
	REQUIRE_THROWS( (UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("1 00000000 00000001", 16)).toStringHex() == UArbBigInt::fromString("1 00000000 00000000 FFFFFFFF FFFFFFFE FFFFFFFF FFFFFFFF", 16).toStringHex() ); // "mulSchool not posible without overflow (r1)"
	REQUIRE(        (UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("1 FFFFFFFF FFFFFFFF", 16)).toStringHex() == UArbBigInt::fromString("1 FFFFFFFF FFFFFFFE FFFFFFFF FFFFFFFE 00000000 00000001", 16).toStringHex() );
	REQUIRE_THROWS( (UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) * UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("1 FFFFFFFF FFFFFFFF", 16)).toStringHex() == UArbBigInt::fromString("1 FFFFFFFF FFFFFFFE FFFFFFFF FFFFFFFE 00000000 00000001", 16).toStringHex() ); // "mulSchool not posible without overflow (r1)" for 64 bit words "mulSchool not posible without overflow (loop)" for all shorter word types
}

TEST_CASE( "unsigned fixed big integer division", "[UFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   2 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  4) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   2 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  4) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==  10 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   5 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  3)).toUint64() ==   3 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  3)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  5)).toUint64() ==   2 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  5)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 11) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   5 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 11) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 12) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   6 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 12) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(252) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() == 126 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(252) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(253) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() == 126 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(253) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(254) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() == 127 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(254) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() == 127 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255)).toUint64() ==   1 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(254) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127)).toUint64() ==   2 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(254) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127)).toUint64() ==   0 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) / UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127)).toUint64() ==   2 );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255) % UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127)).toUint64() ==   1 );


	// 2 Bytes (16 bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(                2)).toUint64() ==   128);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(                2)).toUint64() ==     0);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0200ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(                4)).toUint64() ==   128);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0200ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>(                4)).toUint64() ==     0);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x100)).toUint64() ==     1);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0100ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x100)).toUint64() ==     0);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0200ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x100)).toUint64() ==     2);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0200ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x100)).toUint64() ==     0);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0200ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x200)).toUint64() ==     1);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0200ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x200)).toUint64() ==     0);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0300ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x200)).toUint64() ==     1);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0300ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x200)).toUint64() == 0x100);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0400ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x200)).toUint64() ==     2);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0400ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x200)).toUint64() ==     0);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0xFF9Cull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x100)).toUint64() ==  0xff);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0xFF9Cull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x100)).toUint64() ==  0x9C);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0xFF9Cull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(  532)).toUint64() ==   123);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0xFF9Cull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(  532)).toUint64() ==     0);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0xDA96ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(  571)).toUint64() ==    98);
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0xDA96ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(  571)).toUint64() ==     0);

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0xFF00ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0FFull)).toUint64() == 0x0100ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0xFF00ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0FFull)).toUint64() ==      0ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x10EFull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0FFull)).toUint64() == 0x0011ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x10EFull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(0x0FFull)).toUint64() ==      0ull );

	// 4 Bytes (32bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xFFFE0001ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xFFFFull)).toUint64() ==     0xFFFFull ); // first test of D5. [Test Remainder] and D6. [add back] (at 8bit words)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xFFFE0001ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xFFFFull)).toUint64() ==          0ull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(   0x010000ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0x0100ull)).toUint64() ==     0x0100ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(   0x010000ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0x0100ull)).toUint64() ==          0ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(   0x0F0000ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0x0F00ull)).toUint64() ==     0x0100ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(   0x0F0000ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0x0F00ull)).toUint64() ==          0ull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xFFFFFFFFull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(  0x003ull)).toUint64() == 0x55555555ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xFFFFFFFFull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(  0x003ull)).toUint64() ==          0ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(   0xE00021ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(   0xEFull)).toUint64() ==     0xEFEFull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(   0xE00021ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64(   0xEFull)).toUint64() ==          0ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xE0E02121ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xEFEFull)).toUint64() ==     0xEFEFull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xE0E02121ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromUint64( 0xEFEFull)).toUint64() ==          0ull );

	// 8 Bytes (64bit)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(          0xFFFFFFFE00000001ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0xFFFFFFFFull)).toUint64() == 0xFFFFFFFFull ); // test of D5. [Test Remainder] and D6. [add back] (at 8bit words)
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(          0xFFFFFFFE00000001ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0xFFFFFFFFull)).toUint64() ==          0ull );

	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(                 0x1FFFFFFFEull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(       0x02ull)).toUint64() == 0xFFFFFFFFull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(                 0x1FFFFFFFEull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(       0x02ull)).toUint64() ==          0ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(          0x121FA00A35068740ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x12345678ull)).toUint64() == 0xFEDCBA98ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(          0x121FA00A35068740ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x12345678ull)).toUint64() ==          0ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(  0xFEDCBA98ull * 0x12345678ull) / UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x12345678ull)).toUint64() == 0xFEDCBA98ull );
	REQUIRE( (UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64(  0xFEDCBA98ull * 0x12345678ull) % UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromUint64( 0x12345678ull)).toUint64() ==          0ull );

	// 16 Bytes (128bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(       "FFFFFFFFFFFFFFFE0000000000000001", 16) / UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0xFFFFFFFFFFFFFFFFull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFFFFFFFFFFFFFFFFull)); // test of D5. [Test Remainder] and D6. [add back] (at 8bit words)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(       "FFFFFFFFFFFFFFFE0000000000000001", 16) % UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0xFFFFFFFFFFFFFFFFull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(                     0ull));

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(                      "1FFFFFFFFFFFFFFFE", 16) / UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(               0x02ull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFFFFFFFFFFFFFFFFull));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(                      "1FFFFFFFFFFFFFFFE", 16) % UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(               0x02ull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(                     0ull));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString( "24090311171252216041959356964269510400", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0x123456789ABCDEF0ull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFEDCBA9876543210ull)); // 24090311171252216041959356964269510400 / 1311768467463790320 = 18364758544493064720
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString( "24090311171252216041959356964269510400", 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0x123456789ABCDEF0ull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(                     0ull));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(       "121fa00ad77d7422236d88fe5618cf00", 16) / UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0x123456789ABCDEF0ull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(    0xFEDCBA9876543210ull)); // 24090311171252216041959356964269510400 / 1311768467463790320 = 18364758544493064720
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString(       "121fa00ad77d7422236d88fe5618cf00", 16) % UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64( 0x123456789ABCDEF0ull) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromUint64(                     0ull));

	// -------
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString(    "121fa 00ad77d7 422236d8 8fe5618c f13419a0 b84f54b6 445a4618 e3b7a5bf 121fa00a d77d7422 236d88fe 5618cf00", 16) / UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString( "fedcba9876543210000000000000000fedcba9876543210", 16) == UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString(  "123456789abcdef000000000000000123456789abcdef0", 16));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString(    "121f a00ad77d7 422236d8 8fe5618c f13419a0 b84f54b6 445a4618 e3b7a5bf 121fa00a d77d7422 236d88fe 5618cf00", 16) % UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString( "fedcba9876543210000000000000000fedcba9876543210", 16) ==  UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString(                                               "0", 16));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString( "121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString("987654321000000000000000000000000000009876543210", 10) ==  UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString("123456789000000000000000000000000000001234567890", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString( "121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString("987654321000000000000000000000000000009876543210", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(372)>::fromString(                                               "0", 10));

	// ------
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("1", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("1", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString(                                                                                                         "0", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("2", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("3282327327325825708273258273273258263263232825825739394992080780749242493932813447459093582582732732572788", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("2", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString(                                                                                                         "1", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("147", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("44657514657494227323445690792833445758683439807152916938667765724479489713371611530055695001125615409153", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("147", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString(                                                                                                      "86", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("1", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("0", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("5555555555555544455555555555555555444441122235654445554547555", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("1181637837837299615890772977303005548172635842", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("5555555555555544455555555555555555444441122235654445554547555", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(352)>::fromString("102256964850719633725637788587322669027978740977851378679267", 10));

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(248)>::fromString( "121212121121212454564757645640000000000000000000546424465744466464313145643", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(248)>::fromString("46464644515442612", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(248)>::fromString("2608695759652855584042902602291341403871593244214364153233", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(248)>::fromString( "121212121121212454564757645640000000000000000000546424465744466464313145643", 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(248)>::fromString("46464644515442612", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(248)>::fromString("5925350727381047", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(224)>::fromString( "AEDBBBBBDDDFFFFFFFFFFF65156895651516500000000000000000F", 16) / UFixBigInt<BIG_INT_BIT_TO_SIZE(224)>::fromString("FFFFFFFFFF56556165465466546546546546122222222F", 16) == UFixBigInt<BIG_INT_BIT_TO_SIZE(224)>::fromString("aedbbbbbd", 16));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(224)>::fromString( "AEDBBBBBDDDFFFFFFFFFFF65156895651516500000000000000000F", 16) % UFixBigInt<BIG_INT_BIT_TO_SIZE(224)>::fromString("FFFFFFFFFF56556165465466546546546546122222222F", 16) == UFixBigInt<BIG_INT_BIT_TO_SIZE(224)>::fromString("e53e3992ef3e65ed83201fbc921bdf68de2743627f6e5c", 16));

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString( "15485863", 10) / UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("17", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("910933", 10));
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString( "15485863", 10) % UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("17", 10) == UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("2", 10));

}

TEST_CASE( "unsigned fixed big integer pow", "[UFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1)).toUint64() ==   0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2)).toUint64() ==   0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  3)).toUint64() ==   0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255)).toUint64() ==   0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0)).toUint64() ==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0)).toUint64() ==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  3).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0)).toUint64() ==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0)).toUint64() ==   1 );

	// 280bit -> XXXX
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(280)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(280)>(0)).toUint64() ==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(280)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(280)>(1)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(280)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(560)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(560)>(2)) ==   UFixBigInt<BIG_INT_BIT_TO_SIZE(560)>::fromString("1524048626526185117008148645329708998795770321794318911442256140455458946053172210513801777413097237329246447244122385285308414454789711324787960475901495579519924778756", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(840)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(840)>(3)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(840)>::fromString("1881474063392538580104293111393515179649632793959103295994811562361294554161939745982608133564565542204073242684988356858761198894560865302229744629701298307382732414852446913292026698808738732944827521756186090834642278871507135064538602803625789936904", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(1120)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(1120)>(4)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(1120)>::fromString("2322724216016351285472707124797887713981534093719739103213407334702107425041932730777326153711532379822978430798408976244316601438139655559996863723159199445623538286148496267102069962655433997187047023578211999563638238190873223997008007371192667094663558359643750680318859643251894423390770637182150347047660358392496015012475548907536", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(1400)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(1400)>(5)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(1400)>::fromString("2867457962158038971853938647659375320115494383219896161741583092210829444699615500326588552418737089216037940156999920949940166545191462082581253155295134695870831145921714817833094876533390847748267009204859527832933060930612590727989929106335206340916340073313189287861119834506233261329926851146364423475764872904013979979647627788807185431063573845274690387283341162568066853325074114840393511798145094976543399611424", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(1680)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(1680)>(6)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(1680)>::fromString("3539944651218830283540237184943231733526400651356915543005999830870728064470946236962840236630958805963468880528581970518426253453126552935135702339291798727869826342947189921425668475204474360928826722707549964601043918911967378559821737176530807786999546527891889398340508787606662886034686369292655165825645593194777876820396404402099390250401340029154647740647755879072938227342165972233945850036459828750018220652089900824625252564384949798192695376327532441052506514246293241314988128954312301105216", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(1960)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(1960)>(7)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(1960)>::fromString("4370145368848532993242523075480569474139689185243537323461489922215230490555285155220171557274942547946391227642834796084203294700211008420494777946537074472184785618953558877240196071108329207824554743163383909448668325710116607092261566917692365671156479943140409928293640801157769626295637371165926498441822931984045867370978011530469809936350130402824887833172879161880272854103993910122813147049672068271585034130216078042298280565291016527870287491535160333187558206060681978142740974783641780486905910766479698398585528176367347217326798941738259976825918154594987947097719570108544", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(2240)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(2240)>(8)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(2240)>::fromString("5395047783668773709460639056224185760889235717278209951617981537996864826581460683682501318938815681656151958366140465272884649876381694772498596841934270041178306976885452204765063226273182513141163415617476121267278772677860029973492021040065556863907996371801937962087527374769987283177425267845426325078540447496795491526579513442194482548092077099751401641305494953304352311309669493975681079008283809834498665401746908842008129396834776449030813934294217884594751428876570388384142266037241163723638366407733503102721783079433521192695271104586599752841392843737198696981062031279116702499649000416708580359920953881420098099346685016780778222606258624322683077591296", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(2520)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(2520)>(9)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(2520)>::fromString("6660314047113375362717118830937150418894822047689175393373261671094594020566478309787317394536511654440334145396014118250585775607229382517821857691572311721610361814315339092248604034789677002480899646574438926664785599408420949268895302251058514364940634764862382757544044760638210705868384389235211642594541458339214544495817772551070071638986276284136919611246439790071468861836483776797120826186998385040118047655817351174172012988433608066340201003365144512395679567507777521535751903610199604821667817269481414854081548331738516698573839760290854730756066914126892758698199224637074055449072973410012335191441628122431795002240207292069084514744712983684809263796595352722062614488551975275543914901720954495344443353023118414301445927792170105291264", 10) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(2800)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(2800)>(10)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(2800)>::fromString("8222315164743533660322716869205426863298595939614360305442998688209230822741081065880621484469343806415355099455827992366204650030477782349786805802611371198385552114729607612922493857084859636592884607302472143286667576151286304509748792169775990414683086310499759210086314636846142836598831338179359936823353371796102561138300730509971405941785043312353445877831136983874954344159228211618775469143483738566408548893667340467692018161874545230032443789619494305274302301113989109668836113826465977227815031287792805790862002225986391995444892842504718408666055595037262539997469969697387246472169537858751674998655549656461006006174519707063523399279679397216139896950840488719823220059762423870515397663615757747330968399275746884748859378061652915318561679597724441030415446783066798052540826374335278428786048844155232349343754191307776", 10) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(35560)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(35560)>(127)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(35560)>::fromString("4172778355671501411911093959316766691875965985947427692312983374897465771039405945883525728198759346105260871276585944297605912316030231650517633262384721461989805226900735600060714088993728131734494153946770249083103399142068305668200318228151248206866932587034602570532444199492893607463685261541344481016684615477720484492991200183171947538841214043981611889852170768631869142354264745391874461423363864683151140372148011380888550137990490086926435283819302699610792156317341390426118241459053822403100739739837468208877745957532257892550225836231624417019357326037115450268501973723023466068798488001775043858281353640616785573493874881389187991178245168746692045422029015276801185805509691676378420988597540433202135942327340016325313195727573860710000529505462651730093352761975200166046576014762292864349935012376203654791716678633211396352774296952667223113930106119575733612799012898184166612445817976576822928457379056302784264232024559219698540492116518216956062466610233627043582307353417082282643667292491696299107668080770413142235167579884633424436876934132314164248087693277515258746231574358453293805302883209837469099041734414047148491582974182160328769131738590784459998300393140039302547455267291419547827947435130113218483061591099887030886793702418259358536899558103429478222905787556846195455701536065808297659823076256116889433404519567956382778228817778610572449910730841902169345330657801018205466330523948271393274108430367824161792796389274782418427745910163642033724129181242785613778566294749966726299493501063050480249306964864417319654756423565026511010769869503564372337496507594662143883708208898726521079193758923088530701288218786729101561264966171837160598084320470038066259965712664990607928625742477223034722603108397533080414393734753528885963927783892884846501544374405425691831765150815910348967654416967953547906288861846699729718356467329854445820668537483771533259557823457121460778864387463576343662258347421441059227512454382111525727788971739761805121460990341874887384545741526765187640707330239486110280063696886774729669733184293659617217542741618536499524301424653904831457467111656953359960706570970830732181677288742296721737110059800719504862170876772936468244540175975934257966949910844029819033349143975290708517949030616610334969632082767350668878658928890978295001779249398398527870386032698174505272330534023386774361415173028974808741790394759167473568143275318580513688582250081275717542607340402155846349016591910529783522770988487687139590103427247901505883334085212676467073310143170045060247319068893878281767153676983148858467443217476084959620650835618688373721509711059189576963560416548090867539361589572601526676121586493530514735152256880678011849263746660636279007875043560898832822077385858334691631561607620591790670689201983737416542774438614868245780631893392072226485277164841148619928106887567119946041667046502341652388763780470558206153472281790524036768098120338361322525489439603191948092893344010893392628531584477236270073322646830288234941019859931066405727119634029944899138614381404857161173788733339405869871719545293686891111006973420872336416537930289121072500616408455624250507335837529057502199744789552301841310453999221362625214112306199698313290357658647866844883869749756536238446640177419807812653119283931801963716969395384441052084668595700239701385721244467458115573197071718880158822528044778388602022172931441343618513689227126645494455343820055919928735476602442884874549482552128807440612375285495224148310370978576621629122724639939322570764283351629866315917761210694442593469791924418634385207890750947525980113021197692238775070356061353861273034759438518978722034407726979161884335850228018509716204778076866460910599874682878635598040239677694938507499152302755519699472604150817332486517277699680248880117266637648852272200231819102080849491658892279054370696779438293501623526065903883636844585572025322978140541528695124704287095284879617042317975780667493635722543405810628293566490740036670343668077209617960148057758835094120465851663712983708086874686194217389883585694083371243604636467615611958626959140681104504326508546555452257511480560699867486009676346329073029055668735001275709464297596312000896926532212818069076488924961909231055785852226052594680652346646585811259370563334267115522873587501715908629980208933909093798666463110656174443778819969637476684402704056739687406471915712304631371710834620702277385215264263542796352339391890820275182712736015875494755109710504359097389303146559386167305678820607222483504869842369944782946132857174716979049551309910051114821974506782739960246452376467823148022737480468371259146950797802989031916091233374809108234188971787264436698541302803359632835857131400229446252012919068396794773085360894142319839691779063133931247401438965837105620466401341842876956758226227308899291108128745614170902304578638041083887119653335828424083734245756103159044471208262880985489334148061322731000695251228939210918248431074510251105964711356468266579163453005772331651301944440498636939460293057582989025857925743417300543435681227792259569077519348640524371908186731230416503632826330115304074110572964147284916957565219854835110102433271819052407712137653686926563401767617110108391720878820665321217557542137648205551566566668396010472320724691201005839284263457646736345522960514019362518971437516700819168917850268006307306077215787789423516323161108003579254578911791814919035237118349589450915590471460562632422152994109304827091791799317282463193353958723616487095034727936728224453331214061808258511606067458163723272623398107537343818547903352398960771670093517504238881139376522961507405289231372393709567022810544919326333035872893185545889306344759287585954585313316604361960741875819678599106073929365721233872733807194698945454253755028177363718752708913995695303161578752203536049805266175090490727982832575543012251129596477286936718395478571103747699870917434847091913438971497550619135889077108233978823061980661426601453289820074784418228485236545832669171111464370796713384806669401657220911209453523155094962293527616784451502831693811795709999879917467956297146731588638712064253657598318987717401296816100579452641534790064725980814077830871327603183598644870311579751046081117783678903617104572312418319998462329524877367870352502032882174856047763368100114199970314957806374541833968058707756108139649171163411387946006961512825524979593670268245948065765786449847385623503299208987089544163751105718985617579059638198511073010201340581488075618006804145870072553647359117804275406435766127920552672344569175394711948210908271271186424863231201010198645873892332575572236846021346908940746680256465730071893100301010772233308881387378801899318761928769604436389331099442230951851058599673497627416909031352921217943018156625282634942803072823997367071429238076338544567183459311792895645550700519450060125280126260668923151937732242847731359068370104773149650376345929513689200336732282835973269719029499911628181353140193471990882252999516785300823502317756684421045910084484984384993525030537875569751440807515526811864419174222420007926005372843419754615357339228566776204288014012227571272790972551394729734937068131897132703565120357055368495972825679697285216999142844163377042218947242494881651359234993104632919642864426683971878938291501718668646257115135973266071066137075356594367174365175570684925498101197152164431134414816704365100624093181123649891541726584852571922101702197716743766127431519936550778469081462823640832952730416495235997424040385039887327317731928351721543755830162781436941336722545843491091211166170521287500573341930123376393986527958889927878043143078995869474850739631649381200034188852253518925528062858658323468246714799411633658957299994648827339386457768478466993167464395724069563316091927761701321797684624057158236698237862056859078771532241549202472648758622602285571850179435854479847557165526694864838347417631864357911984640803731001552203810347051822025056794721825096196552458736011787754670905598951677518895487342592679055891660605520442884387882410004019700096937330815725360615137420124872916065504342880715551001711091018967387512862229029513532791636885797609056871178608513359091102057251852752797983123486339651697738385477507439287868459843341896205081619437076618209194680288463706579825219293447706942752344993589555727132931507749863349864726008087870209130368174060737749619586078875072614538300463876412565581348363985057171870390671158923533626417332833160333099933991551986023015671462553395986283144528599031749835469251428875767252411032626899747941228229778981303454819713169674544107828352591822815114815029488591580300210539168563970264631144565387660986630012071414605782385696615838915902282434388109167075355450252603794080330055645587177390341016970433660673528405743628324430436066059005259223005624340619263341525025978868924403994511952988516180272888975865829518391661931444115552125879401962758080605532482139998707448497709580170055386903860163597026881314665617100933394693391378326489868036487885242334497056127411641300804818136221150674938937370013156111683287556298151513321653844224223142762568268352803430660027736756566533549293627038263630766542962223801291802858093200883281615465980694433898039597541181139142937634982541162814641799015302031467033958248856653461077369117436693239911307012702872154845674351382202673310249665752433787617939398091765160942317936438390186321421971546297986639211403339508849131860473966596661534639214199186412775825085328421806954673162904251258298319477050983059297366660715434186475102014777638345249453647539472008666848573914384876892351468554977152637992322662309749236106826980131789667227694259313426699052218959456062
#if LONG_TESTS
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(35840)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(35840)>(128)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(35840)>::fromString("5151393539441509088239399286607848588180762819442413215466186894047442631232308522528616828688222830131922857058472334166226576802502293053109214054814852728909604262051940011705119378805028974718253550804203696415751952957618765922096647057824593599167320565950257782597749804250063288827097345301803719202579253253828071522558869016482809069998458411123110582585114779903801710047126625490567079398113307536643009234407207693026833755427029572383963264752321316874157413143056917403451146163066323870962664011516831503979589798347732989453529422671662659548583819714414359446711422301761148978493190552317000962370592821895325372539196052243236871944242799224944121418714889576492759321479415479314749819952052728850117430010991220988201755234011911987976873463933434613137131621846191809314757540459122942522539061020342676103649223320741106288404242370717472178771379709730759541187300861554474941728316992284479284826509140338382487889421600226237638831623181977341535207962483765528178292376448489358115418296574618947404523430265660943485700419780219059363595153040967294636750574411237518390381061594458071135880021179729258388286734787206389248121256935606935739728474784452907502351856646934607676455056342331576957566197179548235205733147379231916238971440832909759729717054542886472025564338280819738145721522794161968138718618675306159498425888787152349248630048963948420544922845489568390222637537586757329893737030763070627419934617548856438081136916700475583558600786568799487927878406245125452876038361522672988900591010236349343979404492629729518038164072984833236085966813779725004498025524166829856180581965262366526742453608438237507262613641179445633987172642005402440283641791446841491123051554090372923036979174057062679958116202956433253769025003228954478748808336863879348437720250393331872234589899816728507419838342013458953058713270150415564850304048453098583676509340060826438661897702343878372517055438943678907362434390173474154756895308613770865209666272845285210872313888168249411927400317957420322759302335048027269469058445209557196457026034750709117004785444589131427567706413787150886111429462668728927299439997317192377759907051605693045670067799980803708398440738972943105182256295023626787049037644405163351137125511133449227464494430177861466147546033276740874459480330592716346229468472960985363716972622901216226812849401977157923049314494132852828956195162958129625631289130189728807812384144945435256905469525256604581256657629813097889190231507380257842109774107106110162990175570750697787834865146723844474884003878361552005003435320027549205811766121410979061954547405806002979900185701076886665012185103462290601512706417147087217376996162091628949080163141788467097785835153497416895070799567738825280536400721310484388148394681626778319382993509422299181429574424278440575413294227294920530623014942546116610097608335534569929861719620991493845986028475705919315809555295993541130926914466817792924807609925832648269122927420585679278645285063056533987909558019535200662874558480399068767883964783254700670062415980988210445824449971768867071783307015490248000187265515350449371271011474740077838650064060155507674760327654646597821134775090864804244576174037348793532514007377588657455080050896400766660895284819464457905292923282865512424072490419749372365036747019424870548874681975029050677248613649386912274801229728186977624653594715408326877742421229397875354756690086481997011416391139186544028266806670267584456438561182066721451240290630738583172268027170406053751398431656063684749689829109696374699007832208956892576316390480198304477874925878709666614293931077370120639342049529548498420423384612538664451328576503010707656271994619142003299938505293027628630820148247528145553913755789054618231913831444401574198143147613022398603975272222637855291302343427444829312173308864732589605615817642181938474631205599979311237516834476712298461520224601493766970148711921568783472963548776534153001009387930249148370394374661267987346650714140638262962258691834346952502763097642939000102365409191180064788593338086052358482804444864934255816219400761224303594520748426395340138321840702769564770676749405255394160009323957349285233365761305415046609402266654377582263308538632841500710504255940023594307570207190773789852270006318491271383919639374066690328533915750441358188920859206942083455129900490627472631991076364700364717433070920118166410638602473767695111840715014148841059775055529742071565534812956287978958575831769161365317626026634259484667327554695704755326446096932286240322369265689419132707209172899442406141867151023482306522864700199215020260998707732134851304847834133627513125162158963903488089354860826187310320171396358522495496430559354450404031130426704200328063275902726943984791618809085569191103145511893333169982052047633001084614854940074984099893812465020779181197734440641771579578088885766376561518836130494378196612660973165112554459922477559474144673970077189225619303720268635838326755868214887864635861017737791956148116288114272859627626260656151005897050470140944407254217857464878714230335718729726652075694504173172253316864793182908153757104362230674272700900594970869539946659079570945293118800481118972308128185196697993426952234381078681363820454403098403531498665393622826529764156687957165552158450410271737070012494602067279677063010312182606031107488427370702467508938095797486651433595101537401171133948795763763084182201309184025636486583953054153044284148267888483575870914680376149593632171259779383509496987537762471978833586455633267735877474736829927706211295465032783307244479207281780460138285316974020083650986518930369148265088896377633447530816647794839216172754397807636292900161769504606560663832892908300943143789244959347108141747729827387465953274935369190405709099271989771260341310754556772288746799688110734989905289102797659565548501397019963251142103242780770596893979934940011072837217495822759785167865830774975995509303723368953278220696700432521275768071100165174036266765113840909170233765583086389937610329761467149202144407831217965184416327337220582894727051029426242645240581074198087847153949812146916345761017933614071960127064916225049956893028414561975037256482753769176773592039199149400747006134260353864731665130824822152467069854013658696032308903918022231087045779631887693505922112795719944236636329300675269287263388125627422892459620568462458971330333074266117398631987168281741604622790002271795323431161412724471747064844638764721537097543607544710411730840608243080776243594581315546796546359609065618395031337320855688379861941515100641603332010302842038715094584576473005818289986844139389410719334490625326133504880070872740475527151421495264714206937691241877681912615664437241347291384887462707551889484319256640608363874406805691635317878628117653244122362314942886639552496104667307997655267272125255437502536477309974736781684388480945914929706953531258759437387307733158039170053910455471328860354882399086705459784340145143665129815462419599859425080695839375492298396667502086500793949977253887340909350651224619848968853358874537020624119010340211489014519613824822739873210944571346542638868971000551836650825646556413389242181521619856445468066016188251604101205880080494381403577672720312152711826687972167122934015477065669111846406855909480977635701958352956935771227768058597185924592349492286308412617742949199191736344658790916298545933003965892316309528496276955304764784276982707050297650718730320530150450872146553059156660307360404318461012376804034325690933393265240711601465954546087866337347807889593714939971860444321248802363563727613074447869602084010903097249616560853659362211645541077843551674102014223964143227860601522297169352894458787872757126241235028284383318202344245579546563057492858767245261128487888133765071425883258185513118090616924255955448123362330842057923736814475667055786670093628199946881229737670788771339059769545503179361134509513189866912994688659180910901042408867576554515844971875598911122078778964006754400349949809998292165088500721383078174745307420925894096104755474597538412636832149956219585940618453324899394175487474378654616173719163426425707216812950151636083344428425643089862267768772434103520062960441896985528934763732131909548592873718177053750783006313221162148695467431629899736147382247109197893229605431073754893797932299015234552459922270028868244706384796580530536379106128815695664384622561978640981623836837813180579877393280830065540181879733816757700059516489548635925391619885157703678075931531031699665236163422643247210713900394471697125061506266068065658916240489298376208787602164701592761830951253550611940855946732756291103444196751967790045473779861965097549074635101052498761119926322087743807426295769596616752383289982968941876638700265783696628296559686954059196121603483865078886073858591459405824856652090184193496966534049768147322958170131290948744074468575175324801991564410143520219576855354732604546084202811698486804928683190526004235936744634397273854849188447819146391172219180468300741014731262066129712448321585591007173478067440769312893868231501945889871763353753209446860052937969633218693956642531433818177253483107838904944400713655262116492438115172970017733221973987824656430811535643222152677124666691374152750267285101422859957726883672241251297071768633926700376796290074536774866053206866771664908422309984718584380115590196903448632218887606827634202376824464098438069514972562753273915723836319045658340000790225382608275576223633280843296034540969342792287480758959764722879179750500662454920346863277836447873439475956722674097381041549766022309221129035176392594012478229074243347743796999791830858750358396171536040985695785336802352720094496249371214834892
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(36120)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(36120)>(129)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(36120)>::fromString("6359517121759344901508241857705575719564991243914359033513065201298034327494150718581735729936501929766623811521394918944324649922515500657780651179269252511407456246530337476206042207573866359736787906978301722502606512778224463874051328907419676308680813164363009588046437402803813437021803439742539183910765995589672643775678638573117186874009238213517778164771693307083221614226519985544555922811171265286342823785346901823908619678108861816383353416442878030908521774176054217506766391368655634077711552287237556826306885021024671342509319147160225182607766726077030377853684107728335664668463160652145068354556795390638284862849878961303794913459664265248837407613986746074205208206466690753699877055270542675083529544574067807041394973382489509868457003095755049628167898985211353013099363994762157087060346534712701452030394995555762085208262180735835064081192647544092757237265775540091566229154092494816882433946333375327735417665668879173066364769496890413145869777527259372609136400348153746180197655842857845321500769395158919504496280976566530755711252687946878905569975574666236716104852244427912850326098116404381112242431127642778194544591828219952897498418467303231530179021473406641051400419008010286718984970760007082363191777215636831741952706291466989443094044143112136046564281565811826892094325994911565882444166600372807478228091166393748793277181820343417356206375722434973085737801213073300954723489292356341813296146381323592178038038483506578429320590738863110799427677853704215433303690825448593518216529703406799948994403194338352229881658512396296395530025660535524702865354580816512544033487583139896851833860680535223423076145689854789730978701043433167513034487990726712317745982258988849676101190682630809083172309915501586456426968102394114429551401868142471893428189061083174120108312807682195011708373426617875239867575831242960332716786196823344938879297916787678317179376634943960089631489371492803399266710333919876217465515766715501771913113808272395820015566368328340746527905135157943017946989926141723146987592225048134786184980808924830421250011503453936376863590160428812421537273412907687352152580579395580671525727884549272541701063106408242883465132981878236183078042584254800241778108456707745707450754719214343169049978818068068883085186362110665945136663596650080696454253891635806573099753078544473181353621182568545116522660437047284418385750356566771465230591770123557556311620209834781455601205352746883840069582065911426531266302741153568674727533678072349846691960682710003329216796844889550847470521567505953076641007131384371218557797853207188144498689638508760465316647155006341823905680248262911647838273892433861189877403344593225465886054923802072190162497112709455096138269708827971872764457642552495795520312147362561565848717666816885646990779082122577262770232339642201595894479163901565985441217876200141086570958060511445396168414488424846472731840305617569305254262159660007444819553678345736290607121539677063295918154088378018907012197020743160470577420008581175906156674259418642073005566224398017374947182393457039279848347428478772507120981938304237958751004559474216197454217924543478062814817263232387434979904559337009334720070158373081493987786418448844654615182585468682554392305297820479234196170823964844549308129367088765726251213223221886820054740766170578171366884482173203409980223648986463940685800573898893905941514885554295900810429777248342633765207232371388422280445484427509531681461688365784226378836644592306381944692708979617189387058456477071439451626912707373469555806604809680467771336383937824556011197640190140214206224393261848049908066338248668837965136778046063006275033702700017238994239352279849669270644388393931651651179594121398869385926171807065129935563783924691550052671820571885141435718036162779735837752828081314238174884839370194945979934564258182810926691176721849168235646232568638966462770999262981042835383208629527033105676753256391341157351054629850667346410935339201124834430826981284467942793060693185024987570111584447312797656913545702524820795667023149173503802068430678170077842500798580122901285115489585980362739291492980602778595324534369769209372839807642744497156113244614523410466164715443480950768569378206466869936816809278545985080227346478638610362535571474180404245566199061412672261446698132929785282217619533162462544518979385741664641453345131136515802197604503781828681413221109451728325358789617066679123172654552769652150424726134803327420200676743379893272680877136476231625657485924241711808112436259174261300680763355494289166194312206726235217146770931309987893804376197304384740482162414382313752069318079760758667861970792419480927452216926092689656913936726454124910784397927229379078210355446614725705012235091345459277380533390804065479089106816784805741046155623008312899219824475095217189713493108890821457537392061684517269919004010636942400377942508230060401822522950254626723684025647789175766181927560247893475868863885744132387420659547675937710877572251012010688651513341337280923488438007669148977696889798529543915234049427978896355859342788550989863777716734437679531508965769476380510541313730341988883156135825722290649946151510205435927741584727462389226971703812100335557923884856167774641513773996992192988217423627147308641875371581449163210864459260543869998919348740025359509307131550052001587084866333189053799649394702393212883902627716806640668770800852380025024285362665515124249622137785583815267149951276449967339555020853299954967549554996151055707639386368124643811172502826654684087617857269612917455144671060547030318804766394663115384293933820577193343026938181870724641989173940648362588701946703782333825148395983728670319365851837466010705027737306603183691191914716385228141067937549898828644161984975376445649065960589837899050048182586542369032516082054960841434600657315629500736818653205049617321457557269724654948977341912262931299208885204841287149935397651326463626246016160438678693976107397518913915425091297503709456091463720018044700298863885631223056220622076703755335068545962640376107902991347146859811363632980917221777901897383256586012465964187037627318695368001969545030908410826024605583392799702359754886883288301738211725468773478274711378580425458499099913708790141870617800279510311204380637043854929536607594660987753795434443714074465140562625632789222643627336198452912637449308763117268316576100013574839642923073799989614116088379021843717101672119964367900999761432084816792487049214485447595306407018695894459711401707623342714525065374319763678214453235637172834644437235964035791792527189922165759992205724232628622588900522878428998987838056940453740394594706621755882585259766573482538919852693881807583227317577776034899234023895393643266587238407428286978799790677995696237160394570941875574032032510501104416855582861418217484499228488480217775295961786446721575663151797324732562803807759899179913954093034898248366284887354512975280489254621964453937724712813683877097564296963101826738494118355641784646145520452120439970972283588584905333116837258737681655322438759093827868210672133107539174780700648409742431574822354568957484900315187287225033207864073709801688734127206466081862676771137623629898745524830208975729248993317888944896403498621787247719069035951898300009851760805189999029980259294280240757139029548983685742125445873238898321784273697923603124191903466077169953509017948515660556341570256740752513511354947291638737111955486302057672363096753344484619408156406547383103490086623967186256889746429979761395206473474028372166049301823652041689692541952118703215676889478811600737672213706744468396403458007430557022460115733696545975346916374199969038269250462131564310464012850163636953123187540089210833456728061895588194385629137457478262806127553386516496610877753542174204525279160846138234128552367915854229371831325057791785401391671482221492927449565509965066535478529464230760053649902126963441808601901236190355611363120926379627316097083857451626175440725831861340575045601822526140821874298181752950736905811224149878952181328805577553771269883130906980164599770218162156717987813368491547977621957520798490257207005146026028832247479986589843108990810877042103726711050774557673783190849373249424774707064524676292742578012138561596417530714757834540728942823939084891980012151036858946953439734602568946575815815431043452598392544018880780983874185304059714352756161358174921344075062137067183252508961825878359274307457846529182122926678477345761845356938911754062686984937468929897614248961261996636962329488214643681101519710532719707057430181356354225530808164918726599645096480074404626753581996131564857247266263696849817431521583409043598169524839781226285564790013183973766470446108913724860710942107120921608210919311396254293074218821046671067920288793978504372277755683934996530536845434589939369339319361455406958870479820388682613373783217921910476463567665992008614978312182579956940767327170907421661836939810033780483291983170475816161867102759542540785371875069209566497232720243906219393684096393257937923026812711058089311761451183706399692298824076432185156262985266227075329543625136226928444743300680597379209503489449786487083631381049227908954550927597014907422487953304914598632978134168211909427964276055910553612674818029034496160383834006861395587676388382016583454993655573144196520633915412028237954802510278979665611009852596961066427209978110165954677147855584927563819114052250303260457492773631792497702526907345011407217567291462277797853136536109091801330183533212118307599787298114755536539726907277274054181222590202402968539226849393234538833491284103779041911521919236386463582440973113105690488598998940647110865458322952629496958453515788

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(71400)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(71400)>::fromUint64(255)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(71400)>::fromString("2149562346292753594698581144193032914280618462952124792093503300177809562576166221949876448328456172774188150935841909803036748346517706165666038844236316018778545829477213195281310122474247157100422064829812188088263961316150022278356033068891740067523803870182363841553504658534623058463994303899650799629282043945202649717195214518638127938207529696309140756313516054761741407977231558191232041820927468734520007278992279027920370556505984897879641899174041863721700728148337967677861052035968168123749446661700041587310359476296123890728460967939085465373909462134292947417399800817991986060473217086595275262400674176858567316921254614641416271554698461459015346584435813423599226310138598386613205245610896966167915269731774976948713140780787920066915570226261997201538193210598840688302783157545243853165569406195111376251741693508669532582793280290612023968011389999439360574901507455784582741146924224258087801476470100521337310315864876018026567249187899501920142501362074492592878913853387226175772162914864381035654932551283287381810827103108350130689869183108693488548383801637639199922550513538946107201832554533680703753074910177340917365103864455641574083234872401680738140210633997258946686363565374966961663150798167819543469157843893276948715977442508028002447273866308231367637399626673711553842465349251127918283653391106103289600597350277161297250759487675205436900038580630469941710411989388025575339376073053933226381688240868692248317951961754694334821458465301320772934717121064278528300851867503527582614108366927314855492243349659664105558742119324960241016423115757945149713838401099524391970505372071723269047085927698689304559741287226616349323706863301289917744273414326266718396485001313212547527130678417353934958529269716153603198695943747101347937600250273073720959258657939146597068816644612199185931997099863618532984161645848928997663692175357139242038779100204669725543895629498491124298551774579583199180709669356455426651502408891859608005680688869585266832121231622828710419015041684774599388807767942641319259579075993582147407443339328331175195973877249452683643007566920279753191793011714837640783052197090932543786394839546378836808619832967414189664378851639305759328538524776907832193417359363126317710843644116071816878461435442095310565153412386593855180852568562668425594672857476396362056633441136744823122277636560042383132783873570569922237570580425854638922655340014928891404921601488078230584049340149457353352254029047401099913607748909367502378179685458694664993579490157242815928481407933426362960608386315754973974658654677222048335964374293148132372552858564420853252553924522475694141393380621533019335995546237774257803264513606665332370773821959826869802921941553664810515488198028118401334112563572859861944293606730279337029214610169899149197198319959890454555867353419884750283509726909502750967821015951828487134920696406508166782261932002002370396777887683669760016303859681525329296110933133402531754162928940701991000957318798490009125501089301808269141007354578070404063224987397637296024636260401525550998532285531937973196273604580731100779351377149412835348988908909149432616827647584919336153971355920765056109012605240692272778744078465256262097695316185134397126794415910817612541732676818223728179524937438710378007854057293966698642742225050019893232017157256637985919833720398130462409091896502447182409694657603888514000995824456280904140290231392834745503804760290557872002184294016623667464488303066200586795752715144927564212058627913264328597292242774660817810150822136075487345622837903300324333915613455467355557617658893164146423198893131237178030014903143190280411844110685515663267739328290016300588141568910196993093199337858632249810193928507077609498686708931783875239168458624183290159623132985826558236541991647581944912101822950557618739017746593012885001085919112125551065465903118885360859051916545404323385799116963945951733354502666277504199909792852347455044998342852376533891857874644615118091975178096944400318331795221334320602232351852035073984359725457893221530698391587529723384511427986042649468008175261874525518536900275098936330341470959762483902780844420197026398920567038118080942195555611754746528263759220345610404528211696324418710023908874109576700461818822361170296891684119603711577046050483491682871378891064200817103394498198939843055937294035776992048813816817261806624209244959726733369765371615330190658961076659078830412635141525515824919598698428415312374522815668104664288964239480735112041827503016034253815760263430221385057641029947813449882021286181314557330256283161287643131322897097724826429980118637423191037168188221742780803571203659534344156365605463117521303986397481991640193147139336314599804674329754966757924780326063351135800575561612341416976907541356889365356442964271584631568798545493120508839661660137240449965742978246492338980503662355071736933974619964562763334711084325030290544213102369571971419663454461594162927390658666884382409253244008675408083244649982132369464521957914942313546926461217964544797508579763759162670993875066069092645847483259346270471232265981473502246957656691701973158650485945791018461252373739702399716825080001922811924103533274756972671436065009829485876597964244840525659407645457566495621312280514512899832249538734623903074191331479741092440717520406835647515866794561589028918417720820710495233708082481379249774329439825230750447897010589721642185052874941751900588087458712062397660325972326958613085109418963962449892393798989846526373855676979969558536609296969542228588619439991481453044169830764147586860270021097500663460742519636974442799811854808436946702956563652851916010439297381319865620816085016637683728472962560310278194198583557842105483649297719860367848170129934686709253264894088316740309088926666786743237980656856455179555037145551834891219818812521448553969281113708223450458097239632599570697075570465383633731999690683997176677064069517103599028958148142761186406796042922301891700639636215066323523518658131772224692619643470633275276165272719269939241708371299613404557674058023502043078585994051195950550048039935975049712022419562431794697167896228740592724027794741994650057906367245178415061914256632305367033347583327672446602683551773450068426240451358993557985104688743337974578755093530698814285263647433196376080563074865066319105033597895855213608648334282194864920273737637648696944621396491727182748439414475897664269242507577848389147781778390949690304681857158923811257895044526072585329932553874466628346709422779863176644089367658151625075256089781246549920297544131990670343352749515918991898899148345249591209310467368390348338295327341509406471165997554773023321167095132677218648951811946668501640598321189855056856299952060990536163368719738683677548366956862935541130130392239494847004514318061829803836291160201803168522109202573451732538823077734790741457767841522172548541423842388023400965698242569493567820942711128426749578975779782045066918271073278919943274860068782011854943723108342585957995864417592321991867367448842372557451766251268887503513403472283111634925024345618089597493663042228694126490907830888338497619793194117466515923519049069955336638345569944093224178225028685376240548972255547696209704517462688056412643427447659299340755449881029927781083219268323740646946145388864806357902986627208494358717927841491788076512078767851584475366685765866449757781739803557154558666778630242565928365243226148651269183459179153718436342747748629269887284358651743345947647258857325179556089209588153691617840626921648644166135967603741404462791226607348192132835079802480560128580404729302414199992112850503522909222108367740221947421882029573356134209961397446025629223708257111653486162032533473297723447261857885088077428521410685120930418317728956388027017076660381234059107666386885521508521931886891657986948787278850846545456909823527727967360874489488559582313419989252973352488652237321536257615154020934978970018348221013362199454858652190737455614001732861098087052470353280651498416108992215773714397531111745806509988770716935090847146020692399775266623290526979576405017641031442835913200684607084089722963518998322027118902227160859447204502103949143316874978687144141213054462093648469004098244413471861258401150830784647078765995163093653268807597732881638775837888446698854252314213846742271809418745215046908289733143671204125288145154402902450704754911857940436662205674666760287494600921079096057463607995604525389039986888505612560267208367163659002852365139866317935264113515847046253751416757413976767997456050374819352533750373764218416055888010212859744352618085037432742038838856767851010117738383682412060816255030001332855958729654465020280736218955996316349155119599992721498415638722410424836013670250412940682045999703387743584262789952634644365956622557383478479425615851338606774635830714140593324916826638738094087576058827026853307592508915438062088782646285913297935617213045623109952022972446735551350818538504281589218934659135032042337400570129220876295778883420459811021356214063753646476416830665930684046134151736323344245880357773526811427168763431626355282559080396436503589849616439238382480293903540410617121516570229770736834991734256636059372654772615947421128890325459353140531309153226499213379032496861046175157926961296329359536841789855441167237960036871033722781744067029497097615390259655197011285336913488064054923732844020082926175697679840678211177527123184793464785783693085344790408178910015648094160961938448113894681388959715108538218333745538619298688575649308189080888997612474233748957227352818604963082772127600216427566972326854814429718162840877921123524500108955202483424600777032155378204555491055855417071
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(71680)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(71680)>::fromUint64(256)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(71680)>::fromString("2653685539819971865032737501554374655314278241038204121693676235445726227781717894842762329549924928011707209056415599661277668468040452596861029639423890124340654641243135839171318862175425836355052703821629905688700635728082295845499473548364075162147038407774992370465842335626627035651099939548478666957180902743836160265148609762892583908461830016613563920814283124023025046444254890125451887643313472837806007372523832487801091609278635907893250778741429005517271050529591294893533131797880205852870503874275643670026333650400680005614355497006616026069852806155507772925454694734391836115480852187847723351956997108344196361737757546963070958920094404062757210173953962746234928516854004844581971067906821330299336111208319420646257578487648566699417602356621339149446885991284530176176997324029479872604445519718435298453069051079343487646861903496727354557793360620672257926771734530871535048807787798663133882646403271548215297158985125448991565258354670997340379628681634786173569675953721260261337329529745327346448483698924512949917185958302410560942226249345891665258394831912720016424235656315998393674073917988211046364916174857764346960926633395012721884845421552078323073920421455800944082503661128479085119727580295819476661047400702258192690538758267188070768661902602480191254253702357592927738708535126746790360556413533285355382470611487116863878821171106608817076220460969191454452743057947152738097334086208538157250799129527293729858433657281108312578420894209031003765449899956810913621913370850683781121174862317244450829711319158667435407806133861783205033719782425706231991943299409070800816803157680930327621427549913439128365881768980530958253304067157773854039373255171693381999261033676837957481372577430569758462498961433174540985937583955957144498373115637535507072057803976039595386114783290400897846581118306044810733356589502185155664444385848985557419747020941626943716877513809556477815095149926166068612969342376282756767905673441385904321590555386257308435265604367573771703413083020120586330936524935019842533297961978019530979783662684346052807752848512691503740355006686947571637660845521607220930481500196891402678028567750281337073157357503722733079330480578262196919865333327162862069837374349676699853565862992151075463578641872056884397754581336421578022539311873540782401520575126772203613841637850726173022454288295455834619378098482007463335385950353543510777444904587225641880974705946642084007433378297087774563519710035950854049503176907104319869909679465021323361677301581177204482703600254522707920351769508440884380548329107612804611645703058645043659381016737068117828476258029426309584887358834354526652378558443601553601976273869344162025923413294343055665703396987956205913324091753076254337484909990932102942368533734201071795319507866650444872577607673922780122461053716281252092167792591309206703331008465334753766909574368142316614926059009890821678980579783440252060536785618131561962348448694843215473014925948193077748783260660052223145247459600905112501971241731257668221932076104197249573478611823445263390714303262412663166899908517246760993451382546323337529737965753753929966500225022264491815487623824513542958741491615122892429041612188365276215103394851970586198187797949095552494129312655668847390655446263740128476409805040341257143785164780877016771916217056679181185614172022545734670391018114432318043095827174904062011295335194602701297978712225588451299975334891148219092695288411243819618169486240778475901564837821255408177916952563109080731220484197485561959009515972171383480026260094817043534163964019442589531004122895873128688763740559944846964885754798357743128994292690175246792493846216097104555677696963364890686262971933804186821892863102828120999210114439635336612574346854824000224212227735427247319658794017837419352469251578012471656222417465103153296370901539071437718775042907773184665745919957110814651243721373127027602548554715442297380479512622291071098792685328051272856142316670085238130779123742365337914716392862686285391316081144823337264740470609342906132940336886574973640306632449346416183981828689076360329553667083566118106649140535987208941705054664534234615696627122880974049394995753444113706316962631029439589119767674476645616022197100675841206378412158449050340137188059899227318709072089610179285473865628293118564814934573848898966390689508857293845940946055075710565622587175482984694708057764182686617336218829760170249557398887569099675175925692355011172198578008612802666823849775276288905397664019108055897917196123875106013062510392644484088717563232943484346636091078781480771624400875680408924272314955018873403994323432371101221854236985920576182105589813939122760539688914456082076429046138639311071119604519090880762284899304220532822301241338507655961578857258375094754418510642387404930313871842787366309841247010652861538159696521701671216339294511763764394105758416311420071767976038626479046681931014266661571342756290896747771713433171704962140497957339187158371909095485635903637140826431279866130641467063791460839845142536697864108728008286895863452805494264540285578756535112016663224533408051298290850018325803261653421598164638938888995154607146424543975337961331418530907664344630950316018164006443787970412728251354854667928596343616344762602920545085648798721169444179610431163404992371451370145219617400201498381167535384905046991521907521101634741055933409993516187620220756668526790035290140152802725470151793892302326568184623931981548110632473847846381933629224513770551886551258231859967195343910901107682361366250395790522500489672079447925201281226319160682051782214119731895226046665621226798293922024600615986874671385544512924093109066782585158366177680656391173971520980141496241640914107068164094732359144831194848144441362150341047031309567794223149306814406102544797233682499576014384819191114449743264565620597309090258896625135895413844052896778637966806210419352251429416129508340312227249830656513194294302014537965803929305707865358807728232109522422394082012696444238595801451140742131039230046883729377451099138742679178021808150766733543253303976944932414595127262284865601923453628326489843206037525937289011443277181864387244616066368457014865356283854061502321222965516500614533198964319558431199530305125292073894456882595122384900462329186457672027556708429398134914351968988421942863209383018878823815976451249519863535811233388646251818965334841864285167268247233263529077828185279519246259360235055690842268668007947210587780295031663334991933891215799243430833484709521223916968952216815675047611921835872792548168040935890820739096834962349331475510192642390964364383121814247389326860934451219659375194781783037042594936658574237673834142829185558299711448062736327330823874063279265951098301562482224106879439493580978577813531141258919815818297159147978050922401484807448759449342573165834405161610566561850881564461667926557840264311367743027780111315517387043660919875910334661120917331155173020217816985137423050632423709940319841391004093174457903057437543743583033074699511965665995603314948134520142148557002881340864627467275787551581385559547305930258674206205960557106435849746142529824771238193741454880370464223345243239408605905918711602752041622032317573405886969487040089965846262637172662720147112659388530760460132252408632285570632824880279619508472486932245167213733030561696241057070255852834784941742428750455875909473157954700603156620289324101045200759158850823266751395779381580445494843739244285352676362346228515992387101669230625914340070839152510205898106814820932197550827247180032554447539229349975452049880360883172296368149139823194426523912994296962173769452096683023388731495767896492846760796112503987353141951104710597507753136964088402747524960697888380956131379400239202988043510242219122809627910145833435725857657818094205750835915717421735503987221174747278937808330165634667666563681483725698664558037161429224119487493652236371897980796346475631957274970169849198529774287993811774160654151006437525632359567488574762628308488266004046275696998618501900661533369763911512812385192771577705920892716071291102802263120846034595214487160050697927581616640390176932593404699985415052253728301223511816913194807750192802745992696165420239622222106922349347657102053870628244676738376983190729087370766828359188146277439271600383504718060681298537338513192866338698614138692113855036866957010715924527665088961828537751507498787916333595634452657625873513545809508181368447027194338554980802895267550773598181824582825557633034266914391692896978674331490780328410421577716109823011021951354356854563324038719648681543975442168597744270503422254076552901173016337948000244187534968053989941442276412900556489719418689180874078285357620495629371650724344169528439244106698403825675288339727834621875943125085102393889293141825775259394437081823025773897564216237697654116270155111709546896671808603484002638159202362790970312818804250816474405241989541343683174527068804836267118164254102525016161572766103022213700921093678047544806570281939190030434976070879632453425373977377822412202561237296677213704050842660049339481624174617488523810274702113649317483765005671038236279214897938856014090812138408060173827726750631509770284612583193654274743197477228666804774056697196819008074654233933871123008484577057883198502876080185806486833367140516163796121686423637178023411106963414208816252606640029313807563413676293878753194740676743622430367169742911959238399422871826907337299134685505482767976955771345655972064818928954713658355093902755649655551091752374149108900452138643680283300026642011581218815398546126337623523669583755410037662682350104024386119924575867378425514526569213948145403518661921
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(71960)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(71960)>::fromUint64(257)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(71960)>::fromString("3276037541499875024457296564609579955034300583621041738708545793103465400986325566946581025595557862941656879724322295606201510352112305571057048710892300371589816659467695979987877089431672002576140078911180375573343637732060351489609650812819553650115354184261162230057011080712366348907587439091096744456246440346817206567939885699758109915471782906002611644557766890545141417944245437496817937336264862009052759491425115933075310507714763239748044868579735045393923852613229320631527581032598070921506051309883562900322201749470237248264314323861050691748597936134154521623190962627349224234594054886217701080760632097995702489796963429108144280844009356086737676222032124803816084672501213512959195338093208161921753680914402363028584493970608461664129442602475906266990739242898424122925083408915881308956907527468186003335841533807394931843413541502329121684992466752542297792653723136045790583241710834708060548051589412750600624109788212812339270099031005886665603435878148116695021382129754991419700331245006086455338359754940256249751084362542164132657263995678767216407158674888995788314442051427574007466087872585703914468088264132247332468804491529938239162322142824647719729420861952966646228069642725754027084549963539174197366395570207693155963864437110542148630787082880258545981553305269519729251507271075188264973382305897005738291208261460669101837375004735987101924682479460744414532815142393865656516096741166496811002180318986565190379334329030973896913356597928113628189531081531632009917634640064191939812480402787038414412267028775599004791618491810071720136075212406325671362009416912244540579638991860472449932655747130200360432029695130479004290029257568045151060763567234335985549060118923978310833585982781597563610232509846663640622133031348857508264288135252068490225705235187876481393777303266511103848266841493749215651079140686787762679275761268172750783479392093992690672182609563228110215608056837808539456362830741278151940001566267429295197970871787317052614972070580043925600461408512279167020023479122484296229105664035145037069668505814609719987943047192960081093787745109695325277604258499556978541074133547929132828419629333605534440438948580612372242977564421955852579973070955732925548162792979819412145013486981836000430736332201742475951405505600724199898408152885227910333125164276193310823919339520032291802746149974693750657501560163260696327013145188926138952288039985717413794852200723884270145428296935707327799201248462448551067788029620515826989176587514332850159968958717515467503468831658434911816383754427617133623789534970378764371841992768993385667213143703796610975278402912627115212606768445795981415330477894534461545715458662491753622198800141767726570129252083404636882463967125927391324175611790545870746676482046200769313146210804074010366683741101161939756582459205461727047246927004467483064614155723559153930817010246019213003368726954383053186796559152247448341047148105224675788671507540224764099426220776677370402972165291589015254414427231837766178331809501056892235808930736451867235050860450119843222423535111894195550871263291237838336707979729248809251104020051653786551896346938026338138108346058243127319268603077528260522740338933614663453248248294773578215244951646893872916636880051449276645114523821074909654739685712325037401738463913699968029545662799199804790134750279714734182124545500722984828778924319031752489190503186675700361188835258538867060677512309446053871868308648682667668684257770955330029597746058398610255665592443436093652014583166944461396119753449218225453457339847235225007153460666170405942988129052252963086404205065383349078475208480895156780539319464044133471275140288144594858868229584440473095397254899054814587415904994518703295623851745432251632195651785816652646793227752439124749764021947473936074170240015473476805015459192601640852131542070878940025009695291890812658762874700073336521236179594685094815384641381720083821384776772796501873282055955877135550391778123997896157666844336624827870172073159853815138769446346027194731806001866247586801186354565285844376252235664743759062121377532783716550382068306834239602921213404845768992460112483888987745800732455176769427935090353705363256591621041670694683809393595001024593526147850074073618461233672367169094518371693319404859775864143288753304153666179949829625455522237321718047540046477173924781458218882882056804289855157848022343334457733043058498387184625112759148507044130903257720049366950693552833723797368863717380816036862405811365614520008658549650991458656815774952942430840256388702678861538044091608739956381980028616658156000977588055651261953770868394038894879495671203160025286823115358543294867630417283782315574082843485292978269515111989963351292517970946187067679032873486877282093737667734040530720359113987805906079102651880584380685747316327022805393593958722671573365257530305336531890857306751277990914834792324141208199580717250710398153204529945788011688457363611518219963912524248614049982582342324767098158178554789899226613383386394585579191126704970707167081508829924169450472154597484166790100838679259150400062889013113999845970923523497302503711993559464795777939926603468705352665605920350182096836387130320643941134747009240648923528167231671014715050472498191578057786461047164606399748350388358438385246009631011728475894506091510675878023227687887040118415212210201914326004829660661250206474691145730812597705032344124779820549412935559415347444334861208964611492571637870674615763178528574360350563930321276939731383222766985205567272817722083245012129542146402809721859961835750405790010841076484277105841243490376862392174728997149383876367822658699046361211813350334848947175130116325537848597650369906704219195794370693411680904513977508965457789989762202055132433074528248802688837395669354993158433256290599779051976507167042924032810473079232500958080914264325500917824803531200520339833485053066471298933073985320827627903290930164314826853810670503294147584798294890395085789500874940160616106880387638837130609684638629878401946610233251438675431702531925527808472453985983887204577924549774328199272406465425550710902906730450734092954842819431122034804228627903568477573452457040489343755115859034125087714757505488611265877368012068798597456656621665067995559826069080092326112316239405184648572618190729685286231922215398516359452170422121499376305336289389573820340318064553012180806356230724197926881104774503186208458364822727409417576103658950533846259301501687360729431814096661883869808437392388416062158322438783646410501781790009318293218488797884162216873827111780798391321965039355591827468178820725617598195723694009585983271868248020941444890701585330770803801215911668466141204298352452699547243523193628065277425035790557888047460774848148626510827847671667837382508079816691243257892120555754267479447514879941951341741813415869427009371470429339399000610906797124432927858942537513216700847602365613396993232909964898565289463065856577854794170055632040242537819777029257552003083606995393260195231693895542058980983637938503898616331968461125827269380506406283319311612791128856336507691985860539197950020274552425806466214338872596085451934250171658524024264460112600687326523508492920379396120661538370343581282020902737053229922048737544030438244480818554060118093081041866438266979336682446702882184403401676494155128758452624496448110568598652076566175244266374765938702478900734973081254196971618452624218956639142674739007186179208776730329155889654747921047727790827734350837170549668242323727829971749013615681645292515963168552651310576355138397164995291983027976055314298015752267024949459789525937014157558094640094722007669755337210744929584853016729090889589483680522210920249570215257617436875405298293057923624489333014278271679908648206761948802718217685843202873861644600810961320384471454265296781877320712322917581200718345974952032075552573463906356191413598540387887029500746585900307390520681967098981877000641094212022704717745557349324349424825638330348675666108305332645126331875939919015319780677982995037776282705827959807905521507456131252096957907201223374875627036702232675534812870583853286663256647680475863298962455837197919480755899864260789247620553755776448080229379604550759549234709477517398499968553380463746746365034780924653878448876550986115267154076860139044322022620881430349323817204958857880445171620363841611482574668735633617247412568099832542352702523009851046438783309912561384659586973834686822558252428093389057241272295488414066318350660457749028996383156525356310368831076355284721111759083416564293332243982397369762366113255676081007548677099254529701274633461145302068264415937671443134487027556334394546129709520839867117580857794236674030167409484783079298765003117712414346152122809051430530450531748384510999039309891861037625081263374046868412048155311199942118000665777108910661426895574148802980354541936510901640938033471574296434272657674059373747749515374946115959902110641465632706671198075477656799752508095200621249431035392642386976048062984703750072542200190010812395506717912735505383544741148774700694344581544895749622875356389753553754381533638615768087063738089234509273349899988039906528271636779669684195783700991575654671425129435357859617405766345561329148099585567485387409124444558328174527261970661831067167089867243175887837304343855055452081595506465997046923173669015932039947357825292044877341080905877121280707330816911069220135047015288211609530976554157062883849226766204985632050341149047999210965384449367495755320419667912413297040032451986977115040860931344602453776540493336567084219536862736470165583492302943662657505782104842275957749514915818155420647859523882267099234445527737
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(89880)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(89880)>::fromString("321", 10)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(89880)>::fromString("2351317273697935985902379277643272049071484181649453349292098089086097642488720000662423234688635551996765949202126029654533231552961357308237981952692116646560992993424386613818345146232790417721664449545117083910157228958741956563746138229455456964942125565957748021011905760317208946071506358205204414020888489482916887528069027575472486736292690175023960867685562469297221497481286519749029009389486319467066776570874423353263057932837864265871378802948417626412624589510111873436243141690994087220611440656824005607422078931772290243688587823081515269554424793889973807477198150305138084670893627376120164749324589285602861356496567026352575185279498421717903954303525470977050947613964250134024567107533067229259758879037742000641031070614028424088451122582863956752385000434195353363286446857626591791881425940332331567605696191454444654471194426885895678206370512141153216692537061154465418772234957349082727881812457567664956055124972395211949371292567105258966928580137225608720349747327102988149287785645091644687512997853407913544135308221783074889101383048857960899425783246263419550130784680124601148580576166579444343333862988016180149526885492744444508103845985143186294813392003795899590421437105118195593460975718375784189926415286780288035114477792256212445152827096270423972415774097876704732795629470827758485639077278145740770098507248355733106175408151434107536611127350437638703753036369935510265591829991910363328481090840804301654535345853737841174207999918308895433497119559565113877817671671665582512002143032886108758813286722379265424078667992203277176005415214831676573818531984940479133175969501714497793684910365526156040956039099267371933044402702517978865130835600761451860576462467507759660298590162244538508812004157644176247960171701455599692269399147128377052152111142088095920428642527526405087550976740779835499613949647782468709178496262356877802562580545882406109955758567843223057713122384079106909160122509792097741245294399906626750736885220670616743800070880443313798464066925596023620834969562834544336729589607375136374299810901136998486423709609876540510638778224378644503473919565953318942762874173477693562731608226457332364153303689188224032827087417172024409954302052505130505042956707021417230836351720681340759178910662381700954498837789717958436379166314599573531844559664736078186361748083251593561106409299949288257704396806389004289580978161652093110840101016860907569267100754492892862074286433561481976225379627293182541204644763535726568390083904306520063876711256368799857449418828427799105588041329222340388509191976218481245252080620782735718165653338150973149936163627340971942494803592422393978257809112675461805699942579322322022714613003453073179361115044631998659207907277565866828127297027936617556002099307871183422988681726521420026372095090782867363944943473462907628769005391307163614139538188349557894746669835274299470569163177906944363120913080154954450999639862592289792212287647042890504092720572354546442474466958499890709559692325561310533216356360288736774524347302037019021548630536922327730311413761174419576812749139255291331432417317913422288506186591847661826192803759217535047542869172981369033757240120937554843785771973800531861691305611186456330620902981030841608937258860706539162458815595463697672033417494687303732768049445266227314661626239265496632754771141801163818787217086380343626132182646368841788550209777800334523090133383381168665021893536352173695444904592897864779841275546710614544369751905733630759934011953491114266321646453138936199204240654929121001655277649349542370032483057219972385541315833723537036557943553023972905164658779330550776580450575603353521275617704618279241061821252927219914826268775030368935031486524373325344251609923538957485801498479732371619043188754341980844224329887826975694119455211322336262662072073251710706293992248158171187220769988500345076152268574024523306411387411592027086488238653074801097472439235289886791243148065451328630822440744203119229236504603955772745371299719085260993462068619418649516628134067507800447150007694928199484791486387789308174765975311604758055515655770548692537175166092281004014799654455515543013209682640182153588891793844802109358896629577459387655796949318659147815054724772884061922065189645260747758907040261783281670522228579149969997790204265718796019058902848022647466238342272098319426019033794683393096235077066131132953931562966132482266116792891752817771547465351952320011359022024612812768262735655814406285053343338534785010980640871225279027401955052079704153206822928126893896912950229170751993953813635487896166863574942320282765876463559234190376225303032821187247198707623624374765679355584433329800369185166970017127163336081851297005883622557115705950214054713318780613469889317155197107703725945242100953270349226783641670200808828950823150730551602838451751937172261982915120028726235930934171803868598687523337318413637852543836026224096831375121072486391622949344354021012739079414438280107259856844042586943271653432590948375886642504518726654480718371897356665591025724204260409521016268544823473581419217814165496325502023507516989221368068305923760997885570818416616406377901234889196746765235294870346618705106354669750925845879760223325426621160324131233717223138462412194535598724741994293434274512465135168705189272358717407528936593076592668152277316527556946285942249157662901475515679659282478120043108171734439723259594969451954393935123820283285263511363195876307731114899805848124361568880177563055200012297372034152184657077722211595309420607033963010064555817770629102463251458177933143669225468869537910494981236994421094316704765203833869291651594251617602311112207764726369370126099001600241904171209816738687499149248252335196718026060784336387829217872708417136418323194027995469895649769754365450176585005654703424972579634360778474026574005099029910105840879022343066322598186066778823023178379160610675935307302973238982181821426297395034724158054417873813665411799540301358612905612007352228232899278625146091598325545160452681265223593448664809326320901804391587286537602910531692569567634658649890104642176159252361755507916894731488290161411063318701859194105514427719060946109953127704619722686423304414133381759132118346769093853353233833876783708452961288452031673155529019195978023277506970346304749637693910570591113516060326795154044521071876734879615256147163626986735554494152553115867826003909743478895124345862164385704561275114759774266883797185984814958214755465667710246954201916168248187776281934609971596777102471156039387551180043160608588728396519080150753722754751027562839204315517839131443567120157676983563376794879436571922842545988383088310475339570573135933540993136632977908032873709903478590754505154383721292116484062513521851226777430308057919415659402205088911956038797051447785622341058059972287892007625577176401947815723445552615249447962358592778736546131814430420536431169889136528911692947366003731430734405493460546733241785276603571584637271805163110162248089063867028737485028461855032584678186957046903073893263653534091612106721351779844038748446730419351741643630576968929262312736982903680998430997707358918613232223948657614542832522194075552718319122221496446230023454188323527238772641194791256364421069652583941202583561719947570716252549281811175640715515650724139834276780663029738005012340843374199476800590931673440726616178081783486359014765433788342331922459058603006284035470520391329479158335797921370166440565784558047982719837925388256201554782893886469595772963500156029386097783025820483391318653318013843965318825205537864047375871017007801998208144845865719891819410334114357956322781176666988214094713169400520557531110264110321549850149030374356197596720500672216280893000138328622263975154444405941278409077443348257304930812954148227200307274584616577819302737633408791651572983529395940130637038862561744513471144392926789557870116020735985243829688130395376116860306022540371354095627477097914406660868826452952776035056494174882949370555844219774945624544991936085923722258608848362899459613086513201269984062788330348305102149951713829649924061060944151350689381392663596886881932150993983335976250879288822576493924441045118679446878677849757593523367175974034900317734486286473960702402560413631301174954889583546753702306194937818675658080740309122824462478715389860851447974388699956909964583556786947003885945707912123566891637617727110533036304173100004626366036947612872478439580354203809099097099983094896018212796103913376451177761961704980838702425981771491201989459859618877187600613580079401618656550009186348716277790150971232244796816153194809877513274198835289810001876503210341159041384113741348073153640047012733651754864234866014903510559775539314493427831835982199316647783324561394021906751652257802589956578603565268219849457626449750272881776224711889842872865695762810025197450448667725697444721603993921992518794910260945738429699986485348410217989945956914397512785987128681177002821147057473520766945759701081995901291685287929786562412933153487742324452234313501404916587461673801482870250779143779651215653386427087394990918761040108439254399573116263027874809718350216900389949787684439164151163184089384731418203251184209424152631137115299597792182507070188420108211599877265695627107237061525347840515150271492374393277474945643802634219326283740077719392478598556612212090939265407506997518901658331991470161907812300229189395523968288843487174837678910606388231836792230016061771697001708494060773323262457614135306144491005479957554825662115647158644284196175834788277990351473400939162763204046636307233201970954505420587617747818732760183665820292349403699100616449298868307764262108027919
#endif

	//REQUIRE( UArbBigInt::fromString("321", 10).pow(UArbBigInt::fromString("721", 10)) == UArbBigInt::fromString("", 10)

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(252)>::fromString("1234523643567098765433567268387411043985640123642389767832457568567546743234", 10).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(252)>(  0)).toUint64() ==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(252)>(  0).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(252)>::fromString("1234523643567098765433567268387411043985640123642389767832457568567546743234", 10)).toUint64() ==   0 );
	
	// check for overfows
	// 128 bit -> 32640 bit
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32256)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(32256)>::fromUint64(252)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(32256)>::fromString("ffffffffffffffffffffffffffffff0400000000000000000000000000007b89ffffffffffffffffffffffffffd7c91400000000000000000000000009c75ae2fffffffffffffffffffffffe1af9973800000000000000000000004dfedd2ed3fffffffffffffffffffff54b0359db780000000000000000000147e6b9601ec4ffffffffffffffffffdd463b7ab5a15c0000000000000000034bd55aa6f5955dffffffffffffffffb77baa35a6e529ec0000000000000005b061baf528304b66ffffffffffffff96f8f3bf8d1a0e41300000000000000700f85127a97a0ca727ffffffffffff90df8af8577ef8040a300000000000066e10c5816ff746442918ffffffffffa6bcbcd1afcf88308a01b400000000048d5fed1588b1aa69d9cd51ffffffffc7ef7d8aa5f33e031e423a44000000028d26bca3f2ae3a5bac493f9affffffe3d03bab35e87b32239cd6c76800000127f58d7a49f6f2718a1130d23bfffff4706879391c5a87909b5417c9a800006e4f707b5466cadd26e092f25bdcfffc11f850161cfa5f7b414790a55e0c00224f6a7fdc79274838325df3974ae5fee0cf8e0aa4a19abff0b93971597a1c0903c54a98307fad9e319d4dd5ba219eba5e7606714b988dfc4bce3408ba926205972c4793b478691b883ef4ae0c9dc185624f49bd35a9f685280b9b63a5a6c3fed10c6abd45623178636fd6d7cff85e5d39028dbcdc1c0b8813c11261403249eb4d0623bf854b5b5ecc0dcd606a0af1049547791c95e17dc02d9b673272bcd0cf0a66826906c61f5609890ad705be5cc3def5acbd779711b6b393dc64d4f77e6f26ba6b4947294432ed05861666669bc57a42b9dd8016ffef1feed177ad2ffb046e8fe24482b8b9f375f517ca8d9f472785dfd1eeebaef9d0725ddc5e7c0906b3595885e816d4009990ae8e9037e1e9bdc8aeef0f908386002b8dbe37315fd43a86c11076118f437f311ebb43e72c28f72abc80b67041fb36ef71e76b5da2bb27bfafbccb06d71588ca7fa3bf2d79dce4d885eaa6d1ade2fa266832704180afc3f89965d78b295bf3a6a6902fd5d8aa23b65258013f3ee9ab9346ba711723e97420e4e26156432256c3e033babf271801d8110be7e18caf34e345809e37773c2a1a5ba5abff8c8224cfaa8877ab13d213d67f8529aac24eda7ae4f53e2ad3b8bba26c6f583a20f9db040df0069118a2f61dacd58f2ebc7c849a9678bf68b5f2150e76d9df294d80d3eb866216535b020cedb3ab876002f8a376640210d825074bb4b12da7345ff11a4ce67136cc7261f15fc2177212b32c6674763aa47ecf64c8a593f05110a60fceed04321902eabcaa079fab11a1a15ece4fd0c854419cfe4ae8839a49af1b4a16bade87a9e2e4b5673aa3dd6aebd6412597c447d1141c22cb26d416203f8b8188cddc94e1925e7cac8bc1f724b28b60fd5b69fe7b7e9368ec740519180621811014c9eabd5efc567b0a5530c8c4ee870356dc6598648261b14201a4b09cfbf39bd73cd0e6b6795a7ca550f37e5d3ff7561a5c1cf8b94f1c06f0baffc7ef47bef016050ff1b1602c27e63d7ec231465b4fd8b7bb264f247f7f40c1da3b62849b401e4abcfcb8ad53720faac655016621a1fc18b0be5f0bc16f8dfe95df6501fe83e273fb048777afed00eb76c15675c9f74a5a1efcd94528e222e9173736f7acc4b103759cf3262344427d81ca6fcfbfb2ba7ab8583fd4caaf0eecfa5872f53f060f27ab35581f61137de9162aa1fd7e3a584a2a67cbfdcbc5d9518ce25e7944393e6812b1dfbdcf4297ab5337ccd3afeb2cd496f0ebbd445c279dd8c924c686257bb6ab8eb341a3496b008dd77d06d21ac2d1fd396be55a756ed12c177f16a7c5f7831979dd04b223f1c5f68a3fdbb872f3300442d3acc5285729432c716ad03669ecb9ec3c5408988bb7255c82f2ee136b797a4a693c4e61fa089df74307dbeb51099c38678a54e1081e1d96339b0cc05476bfdf3ac9d6931bf704c03b9402b1d309a6012f864d48e1e8845f70425c5b85fee5c0c106c14074a93e9799a83ee458c6bfcc5b0e850fbb6bb70399e50e36626815cdbe08cbbf42fb3d3ce57957bd33110547483c2538785814eb1a74838d26b3970e4982044ba5dbb3ee7498fa568d3699106675d7bdc31ba1d6062a8d1a8c206b1b43050eedfd0dce4691f2f13787b39530cec9b9e32102ecd4aba0a06d22ef1ee7a80b09da40b759519ddcaa3185f145de546112f1d6552e49bc963e110b9f7a20596945d8bb398deb7b676793edfbf97c1527c0c45f1d5bf8a76a0e7de7885cb44e6128c91f3765070c4cc5b0df879313fd612c3c48e332489dd25b54b66425dd29df5e143f569924d0ca3be2ee71bb4752ddca30eeb3c9ac977f6f85f9f7a861d23b5930153113f76e8af1a2da2843d0ae40115b7c39b01dabb5872de1181a9d3abf8aef78aad021f18cad2a1c231e9f03913540f639f2f655f06f868932703b4b1855be389a706e3b4bba70e9ecdf90bfe1b73ad6439081acb51798b69ccf0bae5332676c4c6382dba3c52728a396836e597bea49585272d1cffbbd871159367d02e8153cc516fb97d64b0cbb8d8f2a69b25603c020c439185594e7b1598e8ce2427084655761f52d93a3b6207916c79b74155dff94572ca1b6a370b3906e32969d64f38ff63d953bf85dc2678fe4b48b0057f648c90aabd9c22f96b839da589f842ae29353b7a9ecd329673e3d918a12ba673e4e6125cea983ae98604d253114a0536a8c8d232d531c75934425b0b9f701df8072f11358db0fc8c39fbf20b5572e6714e4bb2b6963291b9a015f84f4d8bdbc806c8a337d0d2388083c0bce0b7378c76a990ea8dab5c04d54ad9bcf3b6c64ac3e3c57914faa03ad902f94030a0dc7fae2aa1780c210ac1535a6b9c9abb1d72cf62e44fefcd2e9e2bf0740703d191878f3ad2631ce6374e528b4917f9d54dc225de0d4c46080134a4aa920407ef115b0848493e6d4cdb78c7f4fa5f800231a6303a161316cf6b23bc1a6e960d93cbabc155a324e8d53f4627e94f562ded99a90ea2de6c7400dc7f4585c090168ec93826785486fb71a3ec0aaf162afb31b887c3ac007d7ee9c9d764127c81658dfa409be4bf63df8c12321a1eab025769921d240e5b88dc24a11c2f0751a1c4c2e948aef8674d71af0d812067d9a9f1a648c9e5b70ee8f1267f41ce80d449062d8fc4d301e435d3e45f0d1a4efcb6ed266307f30e78db4c010a0718ce7f121794e9fae1444dde9f1bbfb397e6e7f941356c1b13c44b0ccbae566da77514a6a3260b13cc9225820a3267a0a290a7ac36479ca3dc45cd35e4fb97e74d22e80487967b285d8bcdeb2ca0584d2b3b89f14c6a0428ff1d52be8d31c1424c45bf4e8321e195dda4185750006522c5fdd9abc1d1a83fee320768d2071a78c5e11cfc80ac6f2deedfd6bb947900ebb5977a166b460cd0cbdc2dde6d85c551eed624b505798acb84ba603905dd98c80831ef9f345c3c1f238783ecb58646786f3e6bf624fb36ccbbf430affe4aea8db764dfe4bb3c80d8a0fbb6210935d75364ecb2b4ceecec5554074af0cab071b7793b338e3bb29e97a48e1e51629d944f665acb62592952526931bf90296eb466549137af64c180b11e1081cfad486d269c5bc810df66aff8261fa0940d8c020d335a76c400ab4f23d988bb6cbbc50fc1f39db1bd5b7a52805285729739cce746d8fd0c01909e9b5e723f1c5dcd4179dd127f3cead50e7124e756ed1397eb1119bf71c8aa6bfa1eaa0496b0086fb0b0f7fc4a6b8ca3d534b145c279ddc3c0638801d2b6ac3ee801e7c4297ab5184137bcf1b74a968689bfa9fc5d9518db57c97ada9f4e606b67e3726137de915c637a5875ffc1dcd4620a9caaf0eecfa875475ee07f06c283c315eb844427d81b4f48b1e0d791b5e350531bce222e91740dfd4be49e3656a4133c52ced00eb76bd13580380422fe0a24f91916f8dfe95e13d5bd52cccd5676b1981a0720faac65438cd1b64ea9c71e338d2337f40c1da3bb613e6919fc5739aabb9b127e63d7ec20f23715778810a7d547c5c06f0baffc7fcf4855ac1ca16b1c2c4df7ca550f37e57e1005cda52fa3eed4f55b14201a4b09f0d55f99f0cddc92264637b0a5530c8c426c1c94fbaf319a8b4b8ec74051918066b61129b2c46c7f28979ac8bc1f724b2709cbd425f2f3e8fc976cb26d416203f95019c5b612f2c5b6e8a673aa3dd6aebd2f3b370e4f65d544cfe4ae8839a49af1c69e0516e28819ce075aa079fab11a1a0fee671d40b0a5d7248c8a593f05110a62f176503756974c462f15fc2177212b3226a2cbac3539d68974bb4b12da7345ff4389671394db47d530cedb3ab876002f7afa0bbf11699fcf6150e76d9df294d811cbfd25877db6bcbf61dacd58f2ebc7c6f569d53a906a1f8bba26c6f583a20f9e1159a9818fc30fb13d67f8529aac24ed8c9bc0d22fcca002a1a5ba5abff8c822545a1addfd952a901d8110be7e18caf34c3e6e3a4c82df97420e4e26156432256cc04bba544cb2b23b65258013f3ee9ab9136bd117a57d3c3f89965d78b295bf3a729037f013555e4d885eaa6d1ade2fa2648c50dc2abbb27bfafbccb06d71588ca8704f5597111f72abc80b67041fb36ef703731b1f2383a86c11076118f437f311f1b921469dabdc8aeef0f908386002b8da953ba4b16b3595885e816d4009990ae92f8c3bbc82785dfd1eeebaef9d0725ddb76db30ff046e8fe24482b8b9f375f517f8c383b4c57a42b9dd8016ffef1feed16eb85bbe6f26ba6b4947294432ed05861815e075c3def5acbd779711b6b393dc64862d14cf0a66826906c61f5609890ad713b232049547791c95e17dc02d9b67327057d9eb4d0623bf854b5b5ecc0dcd606a70cf5d39028dbcdc1c0b8813c112614021e7fed10c6abd45623178636fd6d7cffaea85624f49bd35a9f685280b9b63a5a66205972c4793b478691b883ef4ae0c9dcfba5e7606714b988dfc4bce3408ba92600903c54a98307fad9e319d4dd5ba219efee0cf8e0aa4a19abff0b93971597a1c00224f6a7fdc79274838325df3974ae5fffc11f850161cfa5f7b414790a55e0c00006e4f707b5466cadd26e092f25bdcfffff4706879391c5a87909b5417c9a800000127f58d7a49f6f2718a1130d23bffffffe3d03bab35e87b32239cd6c768000000028d26bca3f2ae3a5bac493f9affffffffc7ef7d8aa5f33e031e423a4400000000048d5fed1588b1aa69d9cd51ffffffffffa6bcbcd1afcf88308a01b40000000000066e10c5816ff746442918ffffffffffff90df8af8577ef8040a300000000000000700f85127a97a0ca727ffffffffffffff96f8f3bf8d1a0e41300000000000000005b061baf528304b66ffffffffffffffffb77baa35a6e529ec0000000000000000034bd55aa6f5955dffffffffffffffffffdd463b7ab5a15c0000000000000000000147e6b9601ec4fffffffffffffffffffff54b0359db7800000000000000000000004dfedd2ed3fffffffffffffffffffffffe1af9973800000000000000000000000009c75ae2ffffffffffffffffffffffffffd7c91400000000000000000000000000007b89ffffffffffffffffffffffffffffff0400000000000000000000000000000001", 16) );
	
	// 128 bit -> 32640 bit
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32640)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(32640)>::fromUint64(255)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(32640)>::fromString("ffffffffffffffffffffffffffffff0100000000000000000000000000007e80ffffffffffffffffffffffffffd653810000000000000000000000000a417340fffffffffffffffffffffffdfd2a6641000000000000000000000053cb6eb0c0fffffffffffffffffffff45b4de7b9c10000000000000000000168f190f081a0ffffffffffffffffffd94e1a59c5a8a1000000000000000003b7e5115f9b3220ffffffffffffffffad2eb4f168c52f21000000000000000693f4f628adabec60ffffffffffffff850af5b7f3ef374761000000000000084d671f6fabfd8d9be0ffffffffffff7a9bdc7e6434afd88ce1000000000007d0de149820e9b24fbed0ffffffffff921e2829c35e75cbbcfdd10000000005ace30966053b78b3043950ffffffffb93525e914e727a52c0eae51000000034359a70e6fbec5c95e85f710ffffffdb7c088dfcecc18b6f88e7ea1100000184645f31096f984c2f21460090fffff0a16b5d0f3c3c73980c4ac0699100009492477c6cb9b7a297892d66ae30fffaa333428250d117880cedc2e4d531002f6fff7892e6502fd6528da6667ab0fe6da8e80ad638ad3adcbf15b59157b10ccc32e7a7c1e958d78cc773cbce35f09bd3456648cb852e1950ef98e80150f3f2a64a85fdbe8c2d4148f308a3b1d15b9ab4673bbdca8ab789411c0b9df56306c5112d5dcf7634fb3f383baeae4a4af4eb559ee328f87af192d9556b56b49fb94ab2d471038b73d6aa930e7f6073b66a5b88304c5754f15cc3a1455f5d253a7d25f89ff494f8e7aca9d11f2affab76737932926d189f9dd19653bd2416b1e7e98c13c5732f5ed4ef50c149aa3a85fe65f4988dfbd10a9a49246a10c98bf324463d950149ca6058750829a55941e44baafb823ded709ca087908345834f745486849925fd0b5bda41137b856f5cbf74b015dfb4f0df8c5bb7b15aa68fd77035e3f3b2de0310b8d1b97aee234ff07ea962cd972d969ad64ac2204e1061b5045bd3340b0e7cfa5a3b686163f8611198b6521892eb25f2fc5f508564204230eacf2195835a5b8dba62f868a37afcb13c21765e966829a40bf56936480bfd732ca21d700f34213d68549634d7978286b9c4aa4c9fc006f01156a93faad284916995065d3e84d1171e70f1dede33e75c2aff7c26eebad57bfa7fb3b3f1d5a9f710d6defc95efc4f756f2e4851f192914da61b2d49f8a71578113f95e2f70ffee8ad36151c6362210a0b8a9fcad07d2ada1af5bf478e92f3f362ef1da7f865605871d346df94de31f61830d2711b71887d55e601ffc52b7336c4ec22e05688b1c4e8c52cab6ad876915a96546fff0d3bf13aeacd88178f2cd7368c37a994070bfe8d894b5629e5295e97630b21e028a53a7fe8bbbf2641f71b2c26f7d6996d7b72d5a40cc28d3a1aae7b93d8de75a8c17bd1b3635deadb2bb085055bcfe428fa020e7a5e10a97989fc14ba18cd45d661e86416ef02ab7b4ce8aa0a5425ce00bf130e91c58f34f6679ae0980c4b59b61da2753cfed8a467eaecef6307c8470f050646ddb29bc77e295e98d2cbdf5cac623445c85d7c1fdb534de3310e60e801154b077f49fbae969ce3f48cecabbd69e6626113d650f62b4217e63a2e1155a9b497111196f3b0652d05717100e705264994537e675452e2de6c91d981178fd832da75409f7ba77ae3c613628c87d3858f59eb1f6f54e860a89694818c6a40ab9736aba2b9baf4443dd71f73c44a867c40698ce41f0f5b195496195537ba93fdc338ff7e55449dfb7a16190c6e9a885dcc2444dc47c7684f4b8246b1ee86b5332dd585dd8d26ea76f9e37b9c4d55826f469c3457836e1d7704116b50b3297c3acae359a6e6b0cfdb9b4a98213faf55c8d88c75c4843beb6430114e5b14bd96603f2cd0d1ad3634a55fcb214cc14b413fc57ec767515ecbc135e6f2eff030fc03fd45241d1ed6a9900dcce93c9e1593356db0d24be5c6600709981f1730239d9a029038bba7d65ff6086e6e7821f5d48c0c24c8b79d0ac5530ea154f9e9bb93c97227b47083e1ab6a223c8022526eb7040ae6bc35295e732839ae21f63ea1706e1a9c06b33088ccb4f9974808d6b902e1d825e468fe96d0043a79e0f68145bf208d54fd972d04a5975e03bc268b04fe6cdeda49b6ec4f795878f1243d10125865fcda3ed6f5f2cf5efa4c2c9b55e64428801ef9a1006cd50b39493ae79bfa2ff07969e47313d11bc5bd14aa90f76281e3d9e8598141e7a2a1a8c53ef2f8c5ae5700b859d70aed95d222e739a0b883a023dce5e041e356fb8e3c1cd19e7c3ba8198c2c6c4a5145d36cc95cbae92e1e742ef4af84bae554d5b8931f3c2ce27e06a894207b792f66335d56774cf6c798253a6377f020bdfec223010f24b082a7247550f59dee89dbe3650177c98fb65013256a406480649c96b381855c8c4f452148d0953d3983c54dd3202a28d7d030d5bf1d78bd76f54ebb57ef215e00beefde920654263456e43b357d3626aec2dc1a6d01eae8ccad3967747f80b1689af784a626c4c65d8b09d17105231773e29396157d757ecb4a64ea3690109b838a14710233e7d0e5451cf5db9aa089c8fb0e9a778058f62df1b798e131bea9ee1d2eb41562daddaaace91ec07c9da45ca67b803bf69b4c0ddc6d32b66fcca262bf8aaa4465801562063011e99b5c739c9aafcf04fe6b741f8b1324bf57cdd695ceb7bc2600b26e73c7c6946f93971bf107998af426b3e918985decae13f3458636466b21ae82ffd4661129bce134348b66925bd1b6c51cbf01925196392f1724a6bb5f7ec909d4f5b94e32e351821cb73708e460fd1a397d2588a9ec81e21bb19f1d304f092f7c8e7a78eb07d46dcc13f465dd7d3424505246ad20f05cd4d044210d9847a854a468fe753b293e626be6c7ae4c560345a34799e4bf687cae9305e79f4334d1cc086367ae44625ce72b7cefc636988df11504382ba19ab29bdc62dd7fa7348b28bf3874fbb433021a4f27a5a6ab9451e35553f9c08fd9841aa508ffafec6bab851d0823a22f5aa6458f10a6ce60ae7d49ba3d5307edf890a2849f3a2423f0357f2d9a0e568c9d431f611cf5bf53e733ba5e2ebad5fb08ffc2344aecad2c5a89b792a8b5a6dd13e122c3f0c86eb76f01c603ba74ebca4ebecc24200233aff3f3fe692b52cf9260fcfb96eb7d9b694a440c4906a9142c3750fb27e0e040912e2819df240ab791da795968aee0fcbb37eacda4ce7c3591a732185d2414fc2c1e710427679b678105459f3f83cde78c9ebbbc477d7620e7ccfe79d65b0fdcdd3a391e21ab4203b51c3879996b5b17a291f8e0d5bed097eff78a53a49ac3e946fa8cfc5a5d1aac8bc2d096710b840fb441b5575d87aeb92b1cac1118700f6b31dbfe5fa9f01ca9bca74950925c15bc518f961394d0f511e8b35cfad68a2d7d43f378331706be18b6c881331fa769a7f0d5ab93d670ec2ea78ed62facd659b533bb83db09a2ff935367a8b0311c9694d2c6e51553010a0d16215805cb2a6d9391212d0d160113b097b681cb1c2a9369462ae3e6060452fb4f9e290a524b84476749d7ccd212816936b0f46964ee01654f27dba62554cf772f321fe2da95720a68f1579bbab2d6a18f4d5871754b2845bd7e3d70792b7c1e53228e249b2a587d4f9b80eb864462f53b841f61437cf59ffa3d37926efc58299f8f718b9ca7da106df492eaf44c1a39a03d81d95101fbd79304a0cae150e129564a459df1412f06b75a34f64766aea1345321c849951f4d843143304ad652c9cb4fd5e703fb1c75bc4c4e7390c37bc414a16f2e0a1038c9911ac2484ead194f302184270ef321aca08d4957395c7c91e28a6e249be40ea72714f0ad757a72d915884f5f6196b974ffd2e6df9d5bb83897b10d10fd091ca661b6c24ae0c2aabb62045bc21823c6ba74a469c54dbce0f0a4e6bf1c7efa6d94d39fb1097a2546450bbbb91fd0534c312e594419278890ab179f5b7ae46e77c375aa612c0eab608458851a6daece81567467347a73cd98abad1d225b06810690440738ffe366690c4f9ad2a59f33aa48c309debe244429af09d4be0b8f8c9a44cfae0268faaab6045169630d859ddc15eb26206f6bc1a283e024acb7f24739bdcf128a44e48a4d643881d69f1ad3b983fc331c946b0b01275b981513f3e1d46aecf0c97724923a70cb099864c9568e7c0fe566a8fe6d10fd5484b31775e8cd3160d82aedaf9da1ef56867603dfa64038ab2afcbfed449ca21524d44f7f1f6ddce83a3b0227ba333d72c5e55182f9ac374d74571284958440d9be08e4d457c5192ecd771dec1eb4a9d61ad6a168727f701be5bb4ba91d3277e870d328c981b59cd774484dd1e6d3549527896ea56532cfe9519bedffa5fe003ad48cc93b1544d74376dc98d844b9206b21ce09e7cebef62e8e4378dd8240b8716d0c0c9d11039b07db56ee0917eae39c9ddef5f475566ccf1e75b40b12d2b60758ea87eec06ced29ffb18d0e5a1036a103b08a90d1b6e3a9b6955366303d911452a8405804c4f87790d337b6f39a2c17b2ee8e18f0e20333b87302b2d95b3603ff90feea956c093ac1b959861628ff0cbdec297ab69cb186d361fe94809a16997d65bf40a96c9bbf103379ab60e6a7ca5a472459d07975b8c73fbec6cdde76d14da0d03a0af7a9c1abfcf483aaccbf4f18305a5c4979e9bf9f73d39731d3268d2696529b53ddfb1f2b2822025dc0c4d21fcef472e468511dc02f5aa750fea204b0f2073a4484ea559952ac2d8f97b66da02f4a425beec847a88f03ba7d5047dc2128f635f786f7cba7e3f5c2759c26afeb6359fa78af7d65aa66faa1b3a0b6772042ef565b6db95ef36830a709673ec3a8cd0a12b10af3eb655c2b1e80c86cd6d92e760622e69ac42dbe9ce52c2da07600b6b071853562ee0d5003e24d5a477cfb3a8ab0ea33c5ebaa0a2de8fc6b54d2b8efc748c29556cf1809f8baa8b14aa611cd707850e6d26aa94a94b79813aeed2a23089cb04c0c7c45151b5b12c654b98c44235754876bee3f4620a9d8c0d59b57a024173d2beb70cf75c4e2e8f642cba99b7347ad1e6af106717feaf0ef333cd18583e16a72873388c3431ca0f01925717f529c752c52340ea4a6ea84effd09000876d19afd029ad725999854f00055cccbd7daf2ee877f3123d1b2aceffff6b6db8839346485d6876d29951cf00000f5e94a2f0c3c38c67f3b53f966efffffe7b9ba0cef69067b3d0deb9ff6f0000002483f77203133e7490771815eefffffffcbca658f190413a36a17a08ef0000000046cada16eb18d85ad3f151aefffffffffa531cf699fac4874cfbc6af00000000006de1d7d63ca18a3443022efffffffffff82f21eb67df164db0412f000000000000856423819bcb5027731efffffffffffff7b298e090540272641f000000000000007af50a480c10c8b89efffffffffffffff96c0b09d75254139f000000000000000052d14b0e973ad0defffffffffffffffffc481aeea064cddf00000000000000000026b1e5a63a575efffffffffffffffffffe970e6f0f7e5f000000000000000000000ba4b218463effffffffffffffffffffffac34914f3f00000000000000000000000202d599befffffffffffffffffffffffff5be8cbf0000000000000000000000000029ac7effffffffffffffffffffffffffff817f000000000000000000000000000000feffffffffffffffffffffffffffffffff", 16) );
	
	// 128 bit -> 32768 bit
	REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(32640)>::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16).pow(UFixBigInt<BIG_INT_BIT_TO_SIZE(32640)>::fromUint64(256)) == UFixBigInt<BIG_INT_BIT_TO_SIZE(32640)>::fromString("0", 16) ); // not posible without overflow
}

TEST_CASE( "unsigned fixed big integer sqrt", "[UFBigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  0).sqrt().toUint64() ==   0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  1).sqrt().toUint64() ==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  2).sqrt().toUint64() ==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  3).sqrt().toUint64() ==   1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  4).sqrt().toUint64() ==   2 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  5).sqrt().toUint64() ==   2 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  6).sqrt().toUint64() ==   2 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  7).sqrt().toUint64() ==   2 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  8).sqrt().toUint64() ==   2 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(  9).sqrt().toUint64() ==   3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 10).sqrt().toUint64() ==   3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 11).sqrt().toUint64() ==   3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 12).sqrt().toUint64() ==   3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 13).sqrt().toUint64() ==   3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 14).sqrt().toUint64() ==   3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 15).sqrt().toUint64() ==   3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 16).sqrt().toUint64() ==   4 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 18).sqrt().toUint64() ==   4 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 19).sqrt().toUint64() ==   4 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 20).sqrt().toUint64() ==   4 );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 25).sqrt().toUint64() ==   5 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>( 79).sqrt().toUint64() ==   8);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(127).sqrt().toUint64() ==   11);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(143).sqrt().toUint64() ==   11);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(144).sqrt().toUint64() ==   12);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(145).sqrt().toUint64() ==   12);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>(255).sqrt().toUint64() ==   15);

	// 2 Byte (16bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(  256).sqrt().toUint64() ==   16);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(16128).sqrt().toUint64() ==   126);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(16129).sqrt().toUint64() ==   127);
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromUint64(16130).sqrt().toUint64() ==   127);

	// 4 Byte (32bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10 00 00 00", 16).sqrt() == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("40 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("01 23 cd ef", 16).sqrt() == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("11 15", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("ff ff ff ff", 16).sqrt() == UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("ff ff", 16) );

	// 8 Byte (64bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10 00 00 00 00 00 00 00", 16).sqrt() == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("40 00 00 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("01 23 45 67 89 ab cd ef", 16).sqrt() == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("11 11 11 11", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("ff ff ff ff ff ff ff ff", 16).sqrt() == UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("ff ff ff ff", 16) );

	// 16 Byte (128bit)
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("0d f8 45 84 5b 4a 35 e4 89 0d e0 00 9f", 16).sqrt() == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("03 bc d4 ba db 37 87", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("c7 d8 56 0d f8 45 84 5b 4a 35 e4 89 0d e0 00 9f", 16).sqrt() == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("e2 2f be f3 b5 70 46 1d", 16) );

	// ------
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(560)>::fromString("1524048626526185117008148645329708998795770321794318911442256140455458946053172210513801777413097237329246447244122385285308414454789711324787960475901495579519924778756", 10).sqrt() == UFixBigInt<BIG_INT_BIT_TO_SIZE(560)>::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10) );
}

TEST_CASE( "unsigned fixed big integer bitLength", "[UFBigint]" ) {
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).bitLength() == 0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000001", 2).bitLength() == 1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000011", 2).bitLength() == 2 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000111", 2).bitLength() == 3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00001111", 2).bitLength() == 4 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00011111", 2).bitLength() == 5 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00111111", 2).bitLength() == 6 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("01111111", 2).bitLength() == 7 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("11111111", 2).bitLength() == 8 );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).bitLength() == 0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000001", 2).bitLength() == 1 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000010", 2).bitLength() == 2 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000100", 2).bitLength() == 3 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00001000", 2).bitLength() == 4 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00010000", 2).bitLength() == 5 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00100000", 2).bitLength() == 6 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("01000000", 2).bitLength() == 7 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2).bitLength() == 8 );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("00000000 00000000", 2).bitLength() ==  0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("00000001 00000000", 2).bitLength() ==  9 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("00000010 00000000", 2).bitLength() == 10 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("00000100 00000000", 2).bitLength() == 11 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("00001000 00000000", 2).bitLength() == 12 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("00010000 00000000", 2).bitLength() == 13 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("00100000 00000000", 2).bitLength() == 14 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("01000000 00000000", 2).bitLength() == 15 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10000000 00000000", 2).bitLength() == 16 );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("00000000 00000000 00000000", 2).bitLength() ==  0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("00000001 00000000 00000000", 2).bitLength() == 17 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("00000010 00000000 00000000", 2).bitLength() == 18 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("00000100 00000000 00000000", 2).bitLength() == 19 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("00001000 00000000 00000000", 2).bitLength() == 20 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("00010000 00000000 00000000", 2).bitLength() == 21 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("00100000 00000000 00000000", 2).bitLength() == 22 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("01000000 00000000 00000000", 2).bitLength() == 23 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(24)>::fromString("10000000 00000000 00000000", 2).bitLength() == 24 );

	// 9 byte
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() ==  0 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000000 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 64 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000001 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 65 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000010 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 66 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000100 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 67 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00001000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 68 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00010000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 69 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00100000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 70 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("01000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 71 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 72 );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000000 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 57 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000000 10000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 64 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000001 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 65 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000011 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 66 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00000111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 67 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00001111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 68 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00011111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 69 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("00111111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 70 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("01111111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 71 );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(72)>::fromString("11111111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 72 );

}

TEST_CASE( "unsigned fixed big integer setBit", "[UFBigint]" ) {
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).withBit(0) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000001", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).withBit(1) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).withBit(2) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000100", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).withBit(3) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00001000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).withBit(4) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00010000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).withBit(5) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00100000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).withBit(6) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("01000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2).withBit(7) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withBit(0) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101011", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withBit(1) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withBit(2) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101110", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withBit(3) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withBit(4) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10111010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withBit(5) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withBit(6) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("11101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withBit(7) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 65)>::fromString("    77 66 55 44 33 22 11 00", 16).withBit( 64) == UFixBigInt<BIG_INT_BIT_TO_SIZE( 65)>::fromString("                         01  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 72)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(  7) == UFixBigInt<BIG_INT_BIT_TO_SIZE( 72)>::fromString("                         88  77 66 55 44 33 22 11 80", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(127) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("00  80 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(128) == UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("01  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(130)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(129) == UFixBigInt<BIG_INT_BIT_TO_SIZE(130)>::fromString("02  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(130) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("04  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(131) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("08  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(132) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(191) == UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(192) == UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("01  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(193) == UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("02  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withBit(10) );
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10101010", 2).withBit(18) );
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10101010", 2).withBit(34) );
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint64_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10101010", 2).withBit(66) );
	}
	REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("10101010", 2).withBit(129) );
}

TEST_CASE( "unsigned fixed big integer clearBit", "[UFBigint]" ) {
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000001", 2).withoutBit(0) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000010", 2).withoutBit(1) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000100", 2).withoutBit(2) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00001000", 2).withoutBit(3) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00010000", 2).withoutBit(4) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00100000", 2).withoutBit(5) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("01000000", 2).withoutBit(6) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10000000", 2).withoutBit(7) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00000000", 2) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withoutBit(0) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withoutBit(1) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101000", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withoutBit(2) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withoutBit(3) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10100010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withoutBit(4) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withoutBit(5) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10001010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withoutBit(6) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withoutBit(7) == UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("00101010", 2) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 65)>::fromString("                         01  77 66 55 44 33 22 11 00", 16).withoutBit( 64) == UFixBigInt<BIG_INT_BIT_TO_SIZE( 65)>::fromString("    77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE( 72)>::fromString("                         88  77 66 55 44 33 22 11 80", 16).withoutBit(  7) == UFixBigInt<BIG_INT_BIT_TO_SIZE( 72)>::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("00  80 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(127) == UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("01  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(128) == UFixBigInt<BIG_INT_BIT_TO_SIZE(129)>::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(130)>::fromString("02  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(129) == UFixBigInt<BIG_INT_BIT_TO_SIZE(130)>::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("04  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(130) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("08  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(131) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("10  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(132) == UFixBigInt<BIG_INT_BIT_TO_SIZE(192)>::fromString("88  77 66 55 44 33 22 11 00", 16) );

	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(191) == UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("                                                  88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("01  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(192) == UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("                                                  88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("02  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(193) == UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("                                                  88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(192) == UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("02  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).withoutBit(10) );
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(16)>::fromString("10101010", 2).withoutBit(18) );
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(32)>::fromString("10101010", 2).withoutBit(34) );
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint64_t)) {
		REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(64)>::fromString("10101010", 2).withoutBit(66) );
	}
	REQUIRE_THROWS( UFixBigInt<BIG_INT_BIT_TO_SIZE(128)>::fromString("10101010", 2).withoutBit(129) );
}

TEST_CASE( "unsigned fixed big integer isEven", "[UFBigint]" ) {
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).isEven() == true );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101011", 2).isEven() == false );
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("254", 2).isEven() == true );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("255", 2).isEven() == false );
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).isEven() == true );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 01", 16).isEven() == false );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 0a", 16).isEven() == true );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 0d", 16).isEven() == false );
}

TEST_CASE( "unsigned fixed big integer isOdd", "[UFBigint]" ) {
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101010", 2).isOdd() == false );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("10101011", 2).isOdd() == true );
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("254", 2).isOdd() == false );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(8)>::fromString("255", 2).isOdd() == true );
	
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).isOdd() == false );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 01", 16).isOdd() == true );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 0a", 16).isOdd() == false );
	REQUIRE( UFixBigInt<BIG_INT_BIT_TO_SIZE(256)>::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 0d", 16).isOdd() == true );
}
