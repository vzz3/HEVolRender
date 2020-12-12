#include "../include/catch2/catch.hpp"
#include "../src/math/UArbBigInt.hpp"
#include "../src/math/UFixBigInt.hpp"

#include <iostream>

#define LONG_TESTS 0

using ppvr::math::UArbBigInt;
using ppvr::math::UFixBigInt;

TEST_CASE( "Test macro tat calculates the minumum word count for a given bit size", "[UFBigint]" ) {
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
// TODO
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("1", 2) << 7);
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
// TODO
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("1", 2) << 15);
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
// TODO
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("1", 2) << 31);
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
// TODO
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("1", 2) << 63);
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

	/*
	// 16 Bytes (128bit)
	REQUIRE( UArbBigInt::fromString("18446744073709551616", 10) == (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE) ); // 2^64

	REQUIRE( UArbBigInt::fromUint64(0x8000000000000000) + UArbBigInt::fromUint64(0x8000000000000000) 	== UArbBigInt::fromString("18446744073709551616", 10) ); // 2^64
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt::fromUint64(              0x01) 	== UArbBigInt::fromString("010000000000000000", 16) ); // 2^64
	REQUIRE( UArbBigInt::fromUint64(              0x01) + UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 	== UArbBigInt::fromString("010000000000000000", 16) ); // 2^64
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 	== UArbBigInt::fromString("01FFFFFFFFFFFFFFFE", 16) );

	REQUIRE( UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) 				== UArbBigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE", 16) );
	REQUIRE( UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + UArbBigInt(0)	== UArbBigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE", 16) );
	REQUIRE( UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + UArbBigInt(1)	== UArbBigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) );
	REQUIRE( UArbBigInt(1) + UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + UArbBigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16)	== UArbBigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) );


	REQUIRE( UArbBigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) + UArbBigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) == UArbBigInt::fromString("ffffffffffffffff0000000000000011111111111111100", 16) );
	REQUIRE( UArbBigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) + UArbBigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) == UArbBigInt::fromString("FFFFFFFFFFFFFFFF0000000000000011111111111111100", 16) );

	REQUIRE( UArbBigInt::fromString("123456789000000000000000000000000000001234567890", 10) + UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10) == UArbBigInt::fromString("1111111110000000000000000000000000000011111111100", 10) );
	REQUIRE( UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10) + UArbBigInt::fromString("123456789000000000000000000000000000001234567890", 10) == UArbBigInt::fromString("1111111110000000000000000000000000000011111111100", 10) );
	 */
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
/*
	// 16 Bytes (128bit)
	REQUIRE( UArbBigInt::fromString("010000000000000000", 16) - UArbBigInt::fromString("010000000000000000", 16) 	== 							  UArbBigInt(0x00)      ); // 2^64 - 2^64 = 0
	REQUIRE( UArbBigInt::fromString("010000000000000001", 16) - UArbBigInt::fromString("010000000000000000", 16) 	==                            UArbBigInt(0x01)      ); // (2^64 + 1) - 2^64 = 1
	REQUIRE( UArbBigInt::fromString("010000000000000001", 16) - UArbBigInt::fromUint64(               0x01ull)	 	== UArbBigInt::fromString("010000000000000000", 16) ); // (2^64 + 1) - 1 = 2^64
	REQUIRE( UArbBigInt::fromString("010000000000000001", 16) - UArbBigInt::fromUint64(               0x02ull)		== UArbBigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull)   ); // (2^64 + 1) - 2 = 2^64 - 1

	REQUIRE( UArbBigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) - UArbBigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) == UArbBigInt::fromString("fdb97530eca86421000000000000000eca8641fdb975320", 16) );
	REQUIRE( UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10) - UArbBigInt::fromString("123456789000000000000000000000000000001234567890", 10) == UArbBigInt::fromString("864197532000000000000000000000000000008641975320", 10) );
*/
}
