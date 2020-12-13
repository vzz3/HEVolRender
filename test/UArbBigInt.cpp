#include "../include/catch2/catch.hpp"
#include "../src/math/UArbBigInt.hpp"

#define LONG_TESTS 0

using ppvr::math::UArbBigInt;

TEST_CASE( "unsigned infinit big integer to unsigned int 64 (UArbBigInt from Word constructor)", "[UABigint]" ) {
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

TEST_CASE( "unsigned infinit big integer to unsigned int 64 (UArbBigInt fromUint64())", "[UABigint]" ) {
	//uint64_t int_2e63_test = 0x8000000000000000; // 2^63 => bin: 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
	//uint64_t test_128 = int_2e63_test >> (8 * 7);
	//uint64_t test_0 = int_2e63_test >> (8 * 8);

	REQUIRE( UArbBigInt::fromUint64(0xFF).toUint64() == 255ull );
	REQUIRE( UArbBigInt::fromUint64(0x0100).toUint64() == 256ull );
	REQUIRE( UArbBigInt::fromUint64(1234).toUint64() == 1234ull );

	uint64_t int_2e16_m1 = std::pow(2ull, 16) - 1ull;
	REQUIRE( UArbBigInt::fromUint64(0xFFFF).toUint64() == int_2e16_m1 );

	uint64_t int_2e16 = std::pow(2ull, 16);
	REQUIRE( UArbBigInt::fromUint64(0x010000).toUint64() == int_2e16 );

	uint64_t int_2e23 = std::pow(2ull, 23);
	REQUIRE( UArbBigInt::fromUint64(0x800000).toUint64() == int_2e23 );

	uint64_t int_2e24_m1 = std::pow(2ull, 24) - 1ull;
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFF).toUint64() == int_2e24_m1 );

	uint64_t int_2e24 = std::pow(2ull, 24);
	REQUIRE( UArbBigInt::fromUint64(0x01000000).toUint64() == int_2e24 );

	uint64_t int_2e24_p1 = std::pow(2ull, 24) + 1ull;
	REQUIRE( UArbBigInt::fromUint64(0x01000001).toUint64() == int_2e24_p1 );

	uint64_t int_2e32_m1 = std::pow(2ull, 32) - 1ull;
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFF).toUint64() == int_2e32_m1 );

	uint64_t int_2e32 = std::pow(2ull, 32);
	REQUIRE( UArbBigInt::fromUint64(0x0100000000).toUint64() == int_2e32 );

	uint64_t int_2e32_p1 = std::pow(2ull, 32) + 1ull;
	REQUIRE( UArbBigInt::fromUint64(0x0100000001).toUint64() == int_2e32_p1 );

	uint64_t int_2e63_m1 = 0x7FFFFFFFFFFFFFFF; // 2^63 - 1
	REQUIRE( UArbBigInt::fromUint64(0x7FFFFFFFFFFFFFFF).toUint64() == int_2e63_m1 );

	uint64_t int_2e63 = 0x8000000000000000; // 2^63
	REQUIRE( UArbBigInt::fromUint64(0x8000000000000000).toUint64() == int_2e63 );

	uint64_t int_2e63_m1_mul2 = 0xFFFFFFFFFFFFFFFE; // (2^63 - 1) * 2
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFE).toUint64() == int_2e63_m1_mul2 );

	uint64_t int_2e63_m1_mul2_p1 = 0xFFFFFFFFFFFFFFFF; // (2^63 - 1) * 2 + 1
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF).toUint64() == int_2e63_m1_mul2_p1 );
}

TEST_CASE( "unsigned infinit big integer check word definitions for 64bit", "[UABigint]" ) {
	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
		REQUIRE( sizeof(BIG_INT_WORD_TYPE) == 1 );

		REQUIRE( BIG_INT_WORD_LOW_BIT_MASK == 0x0Full );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_LOW_BIT_MASK) == UArbBigInt::fromString("0F", 16) );

		REQUIRE( BIG_INT_WORD_HIGH_BIT_MASK == 0xF0ull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGH_BIT_MASK) == UArbBigInt::fromString("F0", 16) );

		REQUIRE( BIG_INT_WORD_MAX_VALUE == 0xFFull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_MAX_VALUE) == UArbBigInt::fromString("FF", 16) );

		REQUIRE( BIG_INT_BITS_PER_WORD == sizeof(BIG_INT_WORD_TYPE) * 8 );
		REQUIRE( BIG_INT_BITS_PER_WORD == 8 );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_BITS_PER_WORD) == UArbBigInt::fromString("8", 10) );

		REQUIRE( BIG_INT_WORD_HIGHEST_BIT == 0x80ull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("10000000", 2) );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("1", 2) << 7);
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
		REQUIRE( sizeof(BIG_INT_WORD_TYPE) == 2 );

		REQUIRE( BIG_INT_WORD_LOW_BIT_MASK == 0x00FFull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_LOW_BIT_MASK) == UArbBigInt::fromString("00 FF", 16) );

		REQUIRE( BIG_INT_WORD_HIGH_BIT_MASK == 0xFF00ull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGH_BIT_MASK) == UArbBigInt::fromString("FF 00", 16) );

		REQUIRE( BIG_INT_WORD_MAX_VALUE == 0xFFFFull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_MAX_VALUE) == UArbBigInt::fromString("FF FF", 16) );

		REQUIRE( BIG_INT_BITS_PER_WORD == sizeof(BIG_INT_WORD_TYPE) * 8 );
		REQUIRE( BIG_INT_BITS_PER_WORD == 16 );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_BITS_PER_WORD) == UArbBigInt::fromString("16", 10) );

		REQUIRE( BIG_INT_WORD_HIGHEST_BIT == 0x8000ull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("10000000 00000000", 2) );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("1", 2) << 15);
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
		REQUIRE( sizeof(BIG_INT_WORD_TYPE) == 4 );

		REQUIRE( BIG_INT_WORD_LOW_BIT_MASK == 0x0000FFFFull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_LOW_BIT_MASK) == UArbBigInt::fromString("00 00 FF FF", 16) );

		REQUIRE( BIG_INT_WORD_HIGH_BIT_MASK == 0xFFFF0000ull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGH_BIT_MASK) == UArbBigInt::fromString("FF FF 00 00", 16) );

		REQUIRE( BIG_INT_WORD_MAX_VALUE == 0xFFFFFFFF );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_MAX_VALUE) == UArbBigInt::fromString("FF FF FF FF", 16) );

		REQUIRE( BIG_INT_BITS_PER_WORD == sizeof(BIG_INT_WORD_TYPE) * 8 );
		REQUIRE( BIG_INT_BITS_PER_WORD == 32 );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_BITS_PER_WORD) == UArbBigInt::fromString("32", 10) );

		REQUIRE( BIG_INT_WORD_HIGHEST_BIT == 0x80000000 );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("10000000 00000000 00000000 00000000", 2) );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("1", 2) << 31);
	} else if (typeid(BIG_INT_WORD_TYPE) == typeid(uint64_t)) {
		REQUIRE( sizeof(BIG_INT_WORD_TYPE) == 8 );

		REQUIRE( BIG_INT_WORD_LOW_BIT_MASK == 0x00000000FFFFFFFFull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_LOW_BIT_MASK) == UArbBigInt::fromString("FF FF FF FF", 16) );

		REQUIRE( BIG_INT_WORD_HIGH_BIT_MASK == 0xFFFFFFFF00000000ull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGH_BIT_MASK) == UArbBigInt::fromString("FF FF FF FF 00 00 00 00", 16) );

		REQUIRE( BIG_INT_WORD_MAX_VALUE == 0xFFFFFFFFFFFFFFFFull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_MAX_VALUE) == UArbBigInt::fromString("FF FF FF FF FF FF FF FF", 16) );

		REQUIRE( BIG_INT_BITS_PER_WORD == sizeof(BIG_INT_WORD_TYPE) * 8 );
		REQUIRE( BIG_INT_BITS_PER_WORD == 64 );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_BITS_PER_WORD) == UArbBigInt::fromString("64", 10) );

		REQUIRE( BIG_INT_WORD_HIGHEST_BIT == 0x8000000000000000ull );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("10000000 00000000 00000000 00000000  00000000 00000000 00000000 00000000", 2) );
		REQUIRE( UArbBigInt::fromUint64(BIG_INT_WORD_HIGHEST_BIT) == UArbBigInt::fromString("1", 2) << 63);
	} else {
		REQUIRE( "" == "unkunknowen type big int word type  BIG_INT_WORD_TYPE");
	}
}

TEST_CASE( "unsigned infinit big integer to std:string hex", "[UABigint]" ) {
	// --- single byte big int creation ---

	REQUIRE( UArbBigInt(0).toStringHex() == std::string("0") );
	REQUIRE( UArbBigInt(1).toStringHex() == std::string("1") );
	REQUIRE( UArbBigInt(2).toStringHex() == std::string("2") );
	REQUIRE( UArbBigInt(3).toStringHex() == std::string("3") );
	REQUIRE( UArbBigInt(4).toStringHex() == std::string("4") );
	REQUIRE( UArbBigInt(5).toStringHex() == std::string("5") );
	REQUIRE( UArbBigInt(6).toStringHex() == std::string("6") );
	REQUIRE( UArbBigInt(7).toStringHex() == std::string("7") );
	REQUIRE( UArbBigInt(8).toStringHex() == std::string("8") );
	REQUIRE( UArbBigInt(9).toStringHex() == std::string("9") );
	REQUIRE( UArbBigInt(10).toStringHex() == std::string("A") );
	REQUIRE( UArbBigInt(11).toStringHex() == std::string("B") );
	REQUIRE( UArbBigInt(12).toStringHex() == std::string("C") );
	REQUIRE( UArbBigInt(13).toStringHex() == std::string("D") );
	REQUIRE( UArbBigInt(14).toStringHex() == std::string("E") );
	REQUIRE( UArbBigInt(15).toStringHex() == std::string("F") );
	REQUIRE( UArbBigInt(16).toStringHex() == std::string("10") );

	REQUIRE( UArbBigInt(66).toStringHex() == std::string("42") );
	REQUIRE( UArbBigInt(127).toStringHex() == std::string("7F") );
	REQUIRE( UArbBigInt(128).toStringHex() == std::string("80") );
	REQUIRE( UArbBigInt(255).toStringHex() == std::string("FF") );

	// --- use 64 bit conversion for big int creation ---

	REQUIRE( UArbBigInt::fromUint64(256).toStringHex() == std::string("100") );

	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFF).toStringHex() == std::string("FFFFFFFF") ); // 2^32 - 1
	REQUIRE( UArbBigInt::fromUint64(0x0100000000).toStringHex() == std::string("100000000") ); // 2^32
	REQUIRE( UArbBigInt::fromUint64(0x0100000001).toStringHex() == std::string("100000001") ); // 2^32 + 1

	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF).toStringHex() == std::string("FFFFFFFFFFFFFFFF") ); // 2^64 - 1
	REQUIRE( UArbBigInt::fromUint64(0xFEDCBA9876543210).toStringHex() == std::string("FEDCBA9876543210") );
	REQUIRE( UArbBigInt::fromUint64( 0xFEDCBA987654321).toStringHex() == std::string( "FEDCBA987654321") );
	REQUIRE( UArbBigInt::fromUint64(  0xFEDCBA98765432).toStringHex() == std::string(  "FEDCBA98765432") );
	REQUIRE( UArbBigInt::fromUint64(   0xFEDCBA9876543).toStringHex() == std::string(   "FEDCBA9876543") );
	REQUIRE( UArbBigInt::fromUint64(    0xFEDCBA987654).toStringHex() == std::string(    "FEDCBA987654") );
	REQUIRE( UArbBigInt::fromUint64(     0xFEDCBA98765).toStringHex() == std::string(     "FEDCBA98765") );
	REQUIRE( UArbBigInt::fromUint64(      0xFEDCBA9876).toStringHex() == std::string(      "FEDCBA9876") );
	REQUIRE( UArbBigInt::fromUint64(       0xFEDCBA987).toStringHex() == std::string(       "FEDCBA987") );
	REQUIRE( UArbBigInt::fromUint64(        0xFEDCBA98).toStringHex() == std::string(        "FEDCBA98") );
	REQUIRE( UArbBigInt::fromUint64(         0xFEDCBA9).toStringHex() == std::string(         "FEDCBA9") );
	REQUIRE( UArbBigInt::fromUint64(          0xFEDCBA).toStringHex() == std::string(          "FEDCBA") );
	REQUIRE( UArbBigInt::fromUint64(           0xFEDCB).toStringHex() == std::string(           "FEDCB") );
	REQUIRE( UArbBigInt::fromUint64(            0xFEDC).toStringHex() == std::string(            "FEDC") );
	REQUIRE( UArbBigInt::fromUint64(             0xFED).toStringHex() == std::string(             "FED") );
	REQUIRE( UArbBigInt::fromUint64(              0xFE).toStringHex() == std::string(              "FE") );
	REQUIRE( UArbBigInt::fromUint64(               0xF).toStringHex() == std::string(               "F") );
	REQUIRE( UArbBigInt::fromUint64(               0x0).toStringHex() == std::string(               "0") );

	// 128 bit test!
	REQUIRE( UArbBigInt::fromUint64(                    18446744073709551615ull).toStringHex()   == std::string(                 "FFFFFFFFFFFFFFFF") ); // 2^64 - 1
	REQUIRE((UArbBigInt::fromUint64(                    18446744073709551615ull) + UArbBigInt::ONE).toStringHex() == std::string(   "10000000000000000") ); // 2^64
	REQUIRE( UArbBigInt::fromString(                   "18446744073709551615", 10).toStringHex() == std::string(                 "FFFFFFFFFFFFFFFF") ); // 2^64 - 1
	REQUIRE( UArbBigInt::fromString(                   "18446744073709551616", 10).toStringHex() == std::string(                "10000000000000000") ); // 2^64
	REQUIRE( UArbBigInt::fromString(                 "4722366482869645213696", 10).toStringHex() == std::string(              "1000000000000000000") ); // 2^72
	REQUIRE( UArbBigInt::fromString(              "1208925819614629174706176", 10).toStringHex() == std::string(            "100000000000000000000") ); // 2^80
	REQUIRE( UArbBigInt::fromString(            "309485009821345068724781056", 10).toStringHex() == std::string(          "10000000000000000000000") ); // 2^88
	REQUIRE( UArbBigInt::fromString(          "79228162514264337593543950336", 10).toStringHex() == std::string(        "1000000000000000000000000") ); // 2^96
	REQUIRE( UArbBigInt::fromString(       "20282409603651670423947251286016", 10).toStringHex() == std::string(      "100000000000000000000000000") ); // 2^104
	REQUIRE( UArbBigInt::fromString(     "5192296858534827628530496329220096", 10).toStringHex() == std::string(    "10000000000000000000000000000") ); // 2^112
	REQUIRE( UArbBigInt::fromString(  "1329227995784915872903807060280344576", 10).toStringHex() == std::string(  "1000000000000000000000000000000") ); // 2^120
	REQUIRE( UArbBigInt::fromString(  "1329227995784915872903807060280344577", 10).toStringHex() == std::string(  "1000000000000000000000000000001") ); // 2^120 + 1
	REQUIRE( UArbBigInt::fromString(  "1329227995784915872903807060280344591", 10).toStringHex() == std::string(  "100000000000000000000000000000F") ); // 2^120 + 15
	REQUIRE( UArbBigInt::fromString("340282366920938463463374607431768211456", 10).toStringHex() == std::string("100000000000000000000000000000000") ); // 2^128
	REQUIRE( UArbBigInt::fromString("340282366920938463463374607431768211457", 10).toStringHex() == std::string("100000000000000000000000000000001") ); // 2^128 + 1
	REQUIRE( UArbBigInt::fromString("340282366920938463463374607431768211471", 10).toStringHex() == std::string("10000000000000000000000000000000F") ); // 2^128 + 15


	REQUIRE( UArbBigInt::fromUint64(0x121fa00ad77d7422ull).toStringHex() 					== std::string( "121FA00AD77D7422") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422", 16).toStringHex() 					== std::string( "121FA00AD77D7422") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d74222", 16).toStringHex() 				== std::string( "121FA00AD77D74222") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d742223", 16).toStringHex() 				== std::string( "121FA00AD77D742223") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236", 16).toStringHex() 				== std::string( "121FA00AD77D7422236") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d", 16).toStringHex() 				== std::string( "121FA00AD77D7422236D") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d8", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D8") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88f", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88F") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88FE") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE5") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe56", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE56") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe561", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE561") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE5618") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618c", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618C") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618CF") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf0", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618CF0") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf00", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618CF00") );

	REQUIRE( UArbBigInt::fromUint64(                     1305938385386173474ull).toStringHex()   == std::string( "121FA00AD77D7422") );
	REQUIRE( UArbBigInt::fromString(                    "1305938385386173474", 10).toStringHex() == std::string( "121FA00AD77D7422") );
	REQUIRE( UArbBigInt::fromString(                   "20895014166178775586", 10).toStringHex() == std::string( "121FA00AD77D74222") );
	REQUIRE( UArbBigInt::fromString(                  "334320226658860409379", 10).toStringHex() == std::string( "121FA00AD77D742223") );
	REQUIRE( UArbBigInt::fromString(                 "5349123626541766550070", 10).toStringHex() == std::string( "121FA00AD77D7422236") );
	REQUIRE( UArbBigInt::fromString(                "85585978024668264801133", 10).toStringHex() == std::string( "121FA00AD77D7422236D") );
	REQUIRE( UArbBigInt::fromString(              "1369375648394692236818136", 10).toStringHex() == std::string( "121FA00AD77D7422236D8") );
	REQUIRE( UArbBigInt::fromString(             "21910010374315075789090184", 10).toStringHex() == std::string( "121FA00AD77D7422236D88") );
	REQUIRE( UArbBigInt::fromString(            "350560165989041212625442959", 10).toStringHex() == std::string( "121FA00AD77D7422236D88F") );
	REQUIRE( UArbBigInt::fromString(           "5608962655824659402007087358", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE") );
	REQUIRE( UArbBigInt::fromString(          "89743402493194550432113397733", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5") );
	REQUIRE( UArbBigInt::fromString(        "1435894439891112806913814363734", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE56") );
	REQUIRE( UArbBigInt::fromString(       "22974311038257804910621029819745", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE561") );
	REQUIRE( UArbBigInt::fromString(      "367588976612124878569936477115928", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618") );
	REQUIRE( UArbBigInt::fromString(     "5881423625793998057118983633854860", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618C") );
	REQUIRE( UArbBigInt::fromString(    "94102778012703968913903738141677775", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618CF") );
	REQUIRE( UArbBigInt::fromString(  "1505644448203263502622459810266844400", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618CF0") );
	REQUIRE( UArbBigInt::fromString( "24090311171252216041959356964269510400", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618CF00") );

	// --------
	REQUIRE( UArbBigInt::fromString("1e02bc1e8aa1d63b5b9ccf516f9d67d27b3c80b500001cbe991a08", 16).toStringHex()            == std::string("1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") );
	REQUIRE( UArbBigInt::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10).toStringHex() == std::string("1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") );

	REQUIRE( UArbBigInt::fromString("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000", 16).toStringHex()                == std::string("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000") ); // 39 Bytes => 312 bit
	REQUIRE( UArbBigInt::fromString("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040", 10).toStringHex() == std::string("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000") );
}

TEST_CASE( "unsigned infinit big integer to std:string dec", "[UABigint]" ) {
	// --- single byte big int creation ---

	REQUIRE( UArbBigInt(0).toStringDec() == std::string("0") );
	REQUIRE( UArbBigInt(1).toStringDec() == std::string("1") );
	REQUIRE( UArbBigInt(2).toStringDec() == std::string("2") );
	REQUIRE( UArbBigInt(3).toStringDec() == std::string("3") );
	REQUIRE( UArbBigInt(4).toStringDec() == std::string("4") );
	REQUIRE( UArbBigInt(5).toStringDec() == std::string("5") );
	REQUIRE( UArbBigInt(6).toStringDec() == std::string("6") );
	REQUIRE( UArbBigInt(7).toStringDec() == std::string("7") );
	REQUIRE( UArbBigInt(8).toStringDec() == std::string("8") );
	REQUIRE( UArbBigInt(9).toStringDec() == std::string("9") );
	REQUIRE( UArbBigInt(10).toStringDec() == std::string("10") );

	REQUIRE( UArbBigInt(0x42).toStringDec() == std::string("66") );
	REQUIRE( UArbBigInt(0x7F).toStringDec() == std::string("127") );
	REQUIRE( UArbBigInt(0x80).toStringDec() == std::string("128") );
	REQUIRE( UArbBigInt(0xFF).toStringDec() == std::string("255") );

	// --- use 64 bit conversion for big int creation ---

	REQUIRE( UArbBigInt::fromUint64(256).toStringDec() == std::string("256") );

	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFF).toStringDec() == std::string("4294967295") ); // 2^32 - 1
	REQUIRE( UArbBigInt::fromUint64(0x0100000000).toStringDec() == std::string("4294967296") ); // 2^32
	REQUIRE( UArbBigInt::fromUint64(0x0100000001).toStringDec() == std::string("4294967297") ); // 2^32 + 1

	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF).toStringDec() == std::string("18446744073709551615") ); // 2^64 - 1

	// 128 bit test!
	REQUIRE( UArbBigInt::fromUint64(                0xFFFFFFFFFFFFFFFF).toStringDec()      == std::string(                   "18446744073709551615") ); // 2^64 - 1
	REQUIRE( (UArbBigInt::fromUint64(               0xFFFFFFFFFFFFFFFF) + UArbBigInt::ONE).toStringDec() == std::string(         "18446744073709551616") ); // 2^64
	REQUIRE( UArbBigInt::fromString(                 "FFFFFFFFFFFFFFFF", 16).toStringDec() == std::string(                   "18446744073709551615") ); // 2^64 - 1
	REQUIRE( UArbBigInt::fromString(                "10000000000000000", 16).toStringDec() == std::string(                   "18446744073709551616") ); // 2^64
	REQUIRE( UArbBigInt::fromString(              "1000000000000000000", 16).toStringDec() == std::string(                 "4722366482869645213696") ); // 2^72
	REQUIRE( UArbBigInt::fromString(            "100000000000000000000", 16).toStringDec() == std::string(              "1208925819614629174706176") ); // 2^80
	REQUIRE( UArbBigInt::fromString(          "10000000000000000000000", 16).toStringDec() == std::string(            "309485009821345068724781056") ); // 2^88
	REQUIRE( UArbBigInt::fromString(        "1000000000000000000000000", 16).toStringDec() == std::string(          "79228162514264337593543950336") ); // 2^96
	REQUIRE( UArbBigInt::fromString(      "100000000000000000000000000", 16).toStringDec() == std::string(       "20282409603651670423947251286016") ); // 2^104
	REQUIRE( UArbBigInt::fromString(    "10000000000000000000000000000", 16).toStringDec() == std::string(     "5192296858534827628530496329220096") ); // 2^112
	REQUIRE( UArbBigInt::fromString(  "1000000000000000000000000000000", 16).toStringDec() == std::string(  "1329227995784915872903807060280344576") ); // 2^120
	REQUIRE( UArbBigInt::fromString(  "1000000000000000000000000000001", 16).toStringDec() == std::string(  "1329227995784915872903807060280344577") ); // 2^120 + 1
	REQUIRE( UArbBigInt::fromString(  "100000000000000000000000000000F", 16).toStringDec() == std::string(  "1329227995784915872903807060280344591") ); // 2^120 + 15
	REQUIRE( UArbBigInt::fromString("100000000000000000000000000000000", 16).toStringDec() == std::string("340282366920938463463374607431768211456") ); // 2^128
	REQUIRE( UArbBigInt::fromString("100000000000000000000000000000001", 16).toStringDec() == std::string("340282366920938463463374607431768211457") ); // 2^128 + 1
	REQUIRE( UArbBigInt::fromString("10000000000000000000000000000000F", 16).toStringDec() == std::string("340282366920938463463374607431768211471") ); // 2^128 + 15

	//REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf", 16).toStringDec() == std::string( "94102778012703968913903738141677775") );
	//REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf00", 16).toStringDec() == std::string( "24090311171252216041959356964269510400") );

	//REQUIRE( UArbBigInt::fromString( "94102778012703968913903738141677775", 10).toStringDec() == std::string( "94102778012703968913903738141677775") );
	//REQUIRE( UArbBigInt::fromString( "24090311171252216041959356964269510400", 10).toStringDec() == std::string( "24090311171252216041959356964269510400") );

	// --------
	REQUIRE( UArbBigInt::fromUint64(0x121fa00ad77d7422ull).toStringDec()                         == std::string(                    "1305938385386173474") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422", 16).toStringDec()                       == std::string(                    "1305938385386173474") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d74222", 16).toStringDec()                      == std::string(                   "20895014166178775586") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d742223", 16).toStringDec()                     == std::string(                  "334320226658860409379") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236", 16).toStringDec()                    == std::string(                 "5349123626541766550070") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d", 16).toStringDec()                   == std::string(                "85585978024668264801133") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d8", 16).toStringDec()                  == std::string(              "1369375648394692236818136") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88", 16).toStringDec()                 == std::string(             "21910010374315075789090184") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88f", 16).toStringDec()                == std::string(            "350560165989041212625442959") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe", 16).toStringDec()               == std::string(           "5608962655824659402007087358") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5", 16).toStringDec()              == std::string(          "89743402493194550432113397733") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe56", 16).toStringDec()             == std::string(        "1435894439891112806913814363734") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe561", 16).toStringDec()            == std::string(       "22974311038257804910621029819745") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618", 16).toStringDec()           == std::string(      "367588976612124878569936477115928") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618c", 16).toStringDec()          == std::string(     "5881423625793998057118983633854860") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf", 16).toStringDec()         == std::string(    "94102778012703968913903738141677775") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf0", 16).toStringDec()        == std::string(  "1505644448203263502622459810266844400") );
	REQUIRE( UArbBigInt::fromString( "121fa00ad77d7422236d88fe5618cf00", 16).toStringDec()       == std::string( "24090311171252216041959356964269510400") );

	REQUIRE( UArbBigInt::fromUint64(                     1305938385386173474ull  ).toStringDec() == std::string(                    "1305938385386173474") );
	REQUIRE( UArbBigInt::fromString(                    "1305938385386173474", 10).toStringDec() == std::string(                    "1305938385386173474") );
	REQUIRE( UArbBigInt::fromString(                   "20895014166178775586", 10).toStringDec() == std::string(                   "20895014166178775586") );
	REQUIRE( UArbBigInt::fromString(                  "334320226658860409379", 10).toStringDec() == std::string(                  "334320226658860409379") );
	REQUIRE( UArbBigInt::fromString(                 "5349123626541766550070", 10).toStringDec() == std::string(                 "5349123626541766550070") );
	REQUIRE( UArbBigInt::fromString(                "85585978024668264801133", 10).toStringDec() == std::string(                "85585978024668264801133") );
	REQUIRE( UArbBigInt::fromString(              "1369375648394692236818136", 10).toStringDec() == std::string(              "1369375648394692236818136") );
	REQUIRE( UArbBigInt::fromString(             "21910010374315075789090184", 10).toStringDec() == std::string(             "21910010374315075789090184") );
	REQUIRE( UArbBigInt::fromString(            "350560165989041212625442959", 10).toStringDec() == std::string(            "350560165989041212625442959") );
	REQUIRE( UArbBigInt::fromString(           "5608962655824659402007087358", 10).toStringDec() == std::string(           "5608962655824659402007087358") );
	REQUIRE( UArbBigInt::fromString(          "89743402493194550432113397733", 10).toStringDec() == std::string(          "89743402493194550432113397733") );
	REQUIRE( UArbBigInt::fromString(        "1435894439891112806913814363734", 10).toStringDec() == std::string(        "1435894439891112806913814363734") );
	REQUIRE( UArbBigInt::fromString(       "22974311038257804910621029819745", 10).toStringDec() == std::string(       "22974311038257804910621029819745") );
	REQUIRE( UArbBigInt::fromString(      "367588976612124878569936477115928", 10).toStringDec() == std::string(      "367588976612124878569936477115928") );
	REQUIRE( UArbBigInt::fromString(     "5881423625793998057118983633854860", 10).toStringDec() == std::string(     "5881423625793998057118983633854860") );
	REQUIRE( UArbBigInt::fromString(    "94102778012703968913903738141677775", 10).toStringDec() == std::string(    "94102778012703968913903738141677775") );
	REQUIRE( UArbBigInt::fromString(  "1505644448203263502622459810266844400", 10).toStringDec() == std::string(  "1505644448203263502622459810266844400") );
	REQUIRE( UArbBigInt::fromString( "24090311171252216041959356964269510400", 10).toStringDec() == std::string( "24090311171252216041959356964269510400") );

	// --------
	REQUIRE( UArbBigInt::fromString("1e02bc1e8aa1d63b5b9ccf516f9d67d27b3c80b500001cbe991a08", 16).toStringDec()            == std::string("12345678900000000000000000000000000000000000000000000123456789000") );
	REQUIRE( UArbBigInt::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10).toStringDec() == std::string("12345678900000000000000000000000000000000000000000000123456789000") );

	REQUIRE( UArbBigInt::fromString("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000", 16).toStringDec()                == std::string("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040") ); // 39 Bytes => 312 bit
	REQUIRE( UArbBigInt::fromString("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040", 10).toStringDec() == std::string("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040") );
}

TEST_CASE( "unsigned infinit big integer from std:string", "[UABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UArbBigInt::fromString( "0", 10).toUint64() 	==   0 );
	REQUIRE( UArbBigInt::fromString( "1", 10).toUint64() 	==   1 );
	REQUIRE( UArbBigInt::fromString( "2", 10).toUint64() 	==   2 );
	REQUIRE( UArbBigInt::fromString( "3", 10).toUint64() 	==   3 );
	REQUIRE( UArbBigInt::fromString( "4", 10).toUint64() 	==   4 );
	REQUIRE( UArbBigInt::fromString( "5", 10).toUint64() 	==   5 );
	REQUIRE( UArbBigInt::fromString( "6", 10).toUint64() 	==   6 );
	REQUIRE( UArbBigInt::fromString( "7", 10).toUint64() 	==   7 );
	REQUIRE( UArbBigInt::fromString( "8", 10).toUint64() 	==   8 );
	REQUIRE( UArbBigInt::fromString( "9", 10).toUint64() 	==   9 );
	REQUIRE( UArbBigInt::fromString("10", 10).toUint64() 	==  10 );
	REQUIRE( UArbBigInt::fromString("77", 10).toUint64() 	==  77 );
	REQUIRE( UArbBigInt::fromString("127", 10).toUint64() 	== 127 );
	REQUIRE( UArbBigInt::fromString("128", 10).toUint64() 	== 128 );
	REQUIRE( UArbBigInt::fromString("255", 10).toUint64() 	== 255 );


	REQUIRE( UArbBigInt::fromString("0", 16).toUint64() 	==  0 );
	REQUIRE( UArbBigInt::fromString("1", 16).toUint64() 	==  1 );
	REQUIRE( UArbBigInt::fromString("2", 16).toUint64() 	==  2 );
	REQUIRE( UArbBigInt::fromString("3", 16).toUint64() 	==  3 );
	REQUIRE( UArbBigInt::fromString("4", 16).toUint64() 	==  4 );
	REQUIRE( UArbBigInt::fromString("5", 16).toUint64() 	==  5 );
	REQUIRE( UArbBigInt::fromString("6", 16).toUint64() 	==  6 );
	REQUIRE( UArbBigInt::fromString("7", 16).toUint64() 	==  7 );
	REQUIRE( UArbBigInt::fromString("8", 16).toUint64() 	==  8 );
	REQUIRE( UArbBigInt::fromString("9", 16).toUint64() 	==  9 );

	REQUIRE( UArbBigInt::fromString("a", 16).toUint64() 	== 10 );
	REQUIRE( UArbBigInt::fromString("b", 16).toUint64() 	== 11 );
	REQUIRE( UArbBigInt::fromString("c", 16).toUint64() 	== 12 );
	REQUIRE( UArbBigInt::fromString("d", 16).toUint64() 	== 13 );
	REQUIRE( UArbBigInt::fromString("e", 16).toUint64() 	== 14 );
	REQUIRE( UArbBigInt::fromString("f", 16).toUint64() 	== 15 );

	REQUIRE( UArbBigInt::fromString("A", 16).toUint64() 	== 10 );
	REQUIRE( UArbBigInt::fromString("B", 16).toUint64() 	== 11 );
	REQUIRE( UArbBigInt::fromString("C", 16).toUint64() 	== 12 );
	REQUIRE( UArbBigInt::fromString("D", 16).toUint64() 	== 13 );
	REQUIRE( UArbBigInt::fromString("E", 16).toUint64() 	== 14 );
	REQUIRE( UArbBigInt::fromString("F", 16).toUint64() 	== 15 );

	REQUIRE( UArbBigInt::fromString("7F", 16).toUint64()	== 127 );
	REQUIRE( UArbBigInt::fromString("80", 16).toUint64()	== 128 );
	REQUIRE( UArbBigInt::fromString("FF", 16).toUint64()	== 255 );

	// leading zeros
	REQUIRE( UArbBigInt::fromString(  "01", 10).toUint64() 	==   1 );
	REQUIRE( UArbBigInt::fromString( "001", 10).toUint64() 	==   1 );
	REQUIRE( UArbBigInt::fromString("0256", 10).toUint64() 	==   256 );

	REQUIRE( UArbBigInt::fromString(  "00", 16).toUint64() 	==   0 );
	REQUIRE( UArbBigInt::fromString(  "01", 16).toUint64() 	==   1 );
	REQUIRE( UArbBigInt::fromString(  "0f", 16).toUint64() 	==   15 );
	REQUIRE( UArbBigInt::fromString("000A", 16).toUint64() 	==   10 );
	REQUIRE( UArbBigInt::fromString("00ff", 16).toUint64() 	==   255 );
	
	REQUIRE( UArbBigInt::fromString("00 00 00 00   00 00 00 00   00 00 00 00   00 00 00 00   00 00 00 09", 16).toUint64() 	==   9 ); // 160 bits ful of zeros:  that is is even for 64 bit words an interesting leading zero test

	// 2 Bytes (16 bit)
	REQUIRE( UArbBigInt::fromString("256", 10).toUint64() == 256 ); // 2^16
	REQUIRE( UArbBigInt::fromString("0100", 16).toUint64() == 256 );

	// 4 Bytes (32 bit)
	REQUIRE( UArbBigInt::fromString("4294967295", 10).toUint64() == 0xFFFFFFFFull ); // 2^32 - 1
	REQUIRE( UArbBigInt::fromString("FFFFFFFF", 16).toUint64() == 0xFFFFFFFFull );
	REQUIRE( UArbBigInt::fromString("01234567", 16).toUint64() == 0x01234567ull );

	// 8 Bytes (64 bit)
	REQUIRE( UArbBigInt::fromString("4294967296", 10).toUint64() == 0x0100000000ull ); // 2^32
	REQUIRE( UArbBigInt::fromString("0100000000", 16).toUint64() == 0x0100000000ull );
	REQUIRE( UArbBigInt::fromString("4294967297", 10).toUint64() == 0x0100000001ull ); // 2^32 + 1
	REQUIRE( UArbBigInt::fromString("0100000001", 16).toUint64() == 0x0100000001ull );
	REQUIRE( UArbBigInt::fromString("0123456789ABCDEF", 16).toUint64() == 0x0123456789ABCDEFull );
	REQUIRE( UArbBigInt::fromString("fedcba9876543210", 16).toUint64() == 0xFEDCBA9876543210ull );


	REQUIRE( UArbBigInt::fromString("18446744073709551615", 10).toUint64() 	== 0xFFFFFFFFFFFFFFFFull ); // 2^64 - 1
	REQUIRE( UArbBigInt::fromString("FFFFFFFFFFFFFFFF", 16).toUint64() 		== 0xFFFFFFFFFFFFFFFFull );

	// --- use 65 bit conversion for big int reference creation ---
	// this uses also the BIG int == operator, therefore a failed test could als be a problem of the == operator implementation
	REQUIRE( UArbBigInt::fromString("18446744073709551616", 10) == (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE) ); // 2^64
	REQUIRE( UArbBigInt::fromString("010000000000000000", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE) ); // 2^64
	REQUIRE( UArbBigInt::fromString("010000000000000001", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x01)) );
	REQUIRE( UArbBigInt::fromString("010000000000000002", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x02)) );
	REQUIRE( UArbBigInt::fromString("010000000000000003", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x03)) );
	REQUIRE( UArbBigInt::fromString("010000000000000004", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x04)) );
	REQUIRE( UArbBigInt::fromString("010000000000000005", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x05)) );
	REQUIRE( UArbBigInt::fromString("010000000000000006", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x06)) );
	REQUIRE( UArbBigInt::fromString("010000000000000007", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x07)) );
	REQUIRE( UArbBigInt::fromString("010000000000000008", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x08)) );
	REQUIRE( UArbBigInt::fromString("010000000000000009", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x09)) );
	REQUIRE( UArbBigInt::fromString("01000000000000000A", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x0A)) );
	REQUIRE( UArbBigInt::fromString("01000000000000000B", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x0B)) );
	REQUIRE( UArbBigInt::fromString("01000000000000000C", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x0C)) );
	REQUIRE( UArbBigInt::fromString("01000000000000000D", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x0D)) );
	REQUIRE( UArbBigInt::fromString("01000000000000000E", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x0E)) );
	REQUIRE( UArbBigInt::fromString("01000000000000000F", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0x0F)) );
	REQUIRE( UArbBigInt::fromString("0100000000000000Fe", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0xFE)) );
	REQUIRE( UArbBigInt::fromString("0100000000000000Ff", 16) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + UArbBigInt::ONE + UArbBigInt(0xFF)) );


	// ---- ignore blank
	REQUIRE( UArbBigInt::fromString(" 1 ", 10) 	== UArbBigInt::fromUint64(1ull) );
	REQUIRE( UArbBigInt::fromString(" 1 1 ", 10) 	== UArbBigInt::fromUint64(11ull) );
	REQUIRE( UArbBigInt::fromString(" 222 111 000 ", 10) 	== UArbBigInt::fromUint64(222111000ull) );
	REQUIRE( UArbBigInt::fromString(" 000 111 222  ", 10) 	== UArbBigInt::fromUint64(111222ull) );
	REQUIRE( UArbBigInt::fromString("        1 2 3 4 5 6 7 8 9 0      ", 10) 	== UArbBigInt::fromUint64(1234567890ull) );
	
	REQUIRE( UArbBigInt::fromString("01 F3 86 9C 69 BB 1C 01", 16) 	== UArbBigInt::fromUint64(0x01F3869C69BB1C01ull) );
	REQUIRE( UArbBigInt::fromString("140 604 019 725 507 585", 10) 	== UArbBigInt::fromUint64(0x01F3869C69BB1C01ull) );
	REQUIRE( UArbBigInt::fromString("123 456 789 000 000 321", 10) 	== UArbBigInt::fromUint64(123456789000000321ull) );
}

TEST_CASE( "unsigned infinit big integer comparisons", "[UABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UArbBigInt(1) != UArbBigInt::ZERO );
	REQUIRE( UArbBigInt(0) != UArbBigInt::ONE );

	REQUIRE( UArbBigInt(0) == UArbBigInt::ZERO );
	REQUIRE( UArbBigInt(0) <= UArbBigInt::ZERO );
	REQUIRE( UArbBigInt(0) >= UArbBigInt::ZERO );

	REQUIRE( UArbBigInt(0) < UArbBigInt::ONE );
	REQUIRE( UArbBigInt(1) > UArbBigInt::ZERO );

	REQUIRE( UArbBigInt(10) >  UArbBigInt(9) );
	REQUIRE( UArbBigInt(10) >= UArbBigInt(9) );
	REQUIRE( UArbBigInt(9) 	<  UArbBigInt::TEN );
	REQUIRE( UArbBigInt(9) 	<= UArbBigInt::TEN );
	REQUIRE( UArbBigInt(10) <= UArbBigInt::TEN );
	REQUIRE( UArbBigInt(10) >= UArbBigInt::TEN );

	REQUIRE( UArbBigInt(255) == UArbBigInt::fromUint64(0xFF) );
	REQUIRE( UArbBigInt(255) <= UArbBigInt::fromUint64(0xFF) );
	REQUIRE( UArbBigInt(255) >= UArbBigInt::fromUint64(0xFF) );

	REQUIRE( UArbBigInt(0) 		<  UArbBigInt(255) );
	REQUIRE( UArbBigInt(0) 		<= UArbBigInt(255) );
	REQUIRE( UArbBigInt(255) 	>  UArbBigInt(0) );
	REQUIRE( UArbBigInt(255) 	>= UArbBigInt(0) );

	REQUIRE( UArbBigInt(1) 		<  UArbBigInt(255) );
	REQUIRE( UArbBigInt(1) 		<= UArbBigInt(255) );
	REQUIRE( UArbBigInt(255) 	>  UArbBigInt(1) );
	REQUIRE( UArbBigInt(255) 	>= UArbBigInt(1) );

	REQUIRE( UArbBigInt(245) 	<  UArbBigInt(255) );
	REQUIRE( UArbBigInt(245) 	<= UArbBigInt(255) );
	REQUIRE( UArbBigInt(255) 	>  UArbBigInt(245) );
	REQUIRE( UArbBigInt(255) 	>= UArbBigInt(245) );

	// 2 Bytes (16 bit)
	REQUIRE( UArbBigInt(255) 				<  UArbBigInt::fromUint64(0x0100) );
	REQUIRE( UArbBigInt(255) 				<= UArbBigInt::fromUint64(0x0100) );
	REQUIRE( UArbBigInt::fromUint64(0x0100) >  UArbBigInt(255) );
	REQUIRE( UArbBigInt::fromUint64(0x0100) >= UArbBigInt(255) );

	REQUIRE( UArbBigInt::fromUint64(0x0100) == UArbBigInt::fromUint64(0x0100) );
	REQUIRE( UArbBigInt::fromUint64(0x0100) <= UArbBigInt::fromUint64(0x0100) );
	REQUIRE( UArbBigInt::fromUint64(0x0100) >= UArbBigInt::fromUint64(0x0100) );

	REQUIRE( UArbBigInt::fromUint64(0x0101) >  UArbBigInt::fromUint64(0x0100) );
	REQUIRE( UArbBigInt::fromUint64(0x0101) >= UArbBigInt::fromUint64(0x0100) );
	REQUIRE( UArbBigInt::fromUint64(0x0101) <  UArbBigInt::fromUint64(0x0102) );
	REQUIRE( UArbBigInt::fromUint64(0x0101) <= UArbBigInt::fromUint64(0x0102) );

	// 8 Bytes (64bit)
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFE) != UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UArbBigInt::fromUint64(0xEFFFFFFFFFFFFFFF) != UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) == UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) <= UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) >= UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFE) <  UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) >  UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFE) );

	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF00) >  UArbBigInt(1) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF00) >= UArbBigInt::ONE );
	REQUIRE( UArbBigInt::ONE 							<  UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF00) );
	REQUIRE( UArbBigInt(1) 								<= UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF00) );

	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) != UArbBigInt::fromUint64(0x01) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) >  UArbBigInt::fromUint64(0x01) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) >= UArbBigInt::fromUint64(0x01) );
	REQUIRE( UArbBigInt::fromUint64(0x01) 				<  UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) );
	REQUIRE( UArbBigInt::fromUint64(0x01) 				<= UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) );

	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) != UArbBigInt::fromUint64(0xFF01) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) >  UArbBigInt::fromUint64(0xFF01) );
	REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) >= UArbBigInt::fromUint64(0xFF01) );
	REQUIRE( UArbBigInt::fromUint64(0xFF01) 			<  UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) );
	REQUIRE( UArbBigInt::fromUint64(0xFF01) 			<= UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) );

	//REQUIRE( UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) != UArbBigInt::fromUint64(0xFFFFFFFFFFFFFF01) );

	// 9 Bytes (65bit)
	REQUIRE(  UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 						!= (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(1)) );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt::ONE) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(1)) );
	REQUIRE(  UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 						<  (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(1)) );
	REQUIRE(  UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 						<= (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(1)) );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(1)) 		>   UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(1)) 		>=  UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );

	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt::TEN) 	!= (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(11)) );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt::TEN) 	== (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(10)) );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt::TEN)		<  (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(11)) );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt::TEN)		<= (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(11)) );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(11)) 		>  (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(10)) );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(11)) 		>= (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(10)) );

	//REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(11)) 	!=  (UArbBigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + UArbBigInt(11)) );
}

TEST_CASE( "unsigned infinit big integer shift left", "[UABigint]" ) {

	// 1 Byte (8bit)
	REQUIRE( UArbBigInt::fromString("1", 2) <<  0 == UArbBigInt::fromString("1", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) <<  1 == UArbBigInt::fromString("10", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) <<  2 == UArbBigInt::fromString("100", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) <<  3 == UArbBigInt::fromString("1000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) <<  4 == UArbBigInt::fromString("10000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) <<  5 == UArbBigInt::fromString("100000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) <<  6 == UArbBigInt::fromString("1000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) <<  7 == UArbBigInt::fromString("10000000", 2) );

	// 2 Byte (16bit)
	REQUIRE( UArbBigInt::fromString("1", 2) <<  8 == UArbBigInt::fromString("10000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) <<  9 == UArbBigInt::fromString("10000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 10 == UArbBigInt::fromString("10000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 11 == UArbBigInt::fromString("10000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 12 == UArbBigInt::fromString("10000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 13 == UArbBigInt::fromString("10000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 14 == UArbBigInt::fromString("10000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 15 == UArbBigInt::fromString("10000000 00000000", 2) );

	REQUIRE( UArbBigInt::fromString("10000000", 2) <<  0 == UArbBigInt::fromString("10000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) <<  1 == UArbBigInt::fromString("10000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) <<  2 == UArbBigInt::fromString("10000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) <<  3 == UArbBigInt::fromString("10000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) <<  4 == UArbBigInt::fromString("10000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) <<  5 == UArbBigInt::fromString("10000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) <<  6 == UArbBigInt::fromString("10000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) <<  7 == UArbBigInt::fromString("10000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) <<  8 == UArbBigInt::fromString("10000000 00000000", 2) );

	// 3 Byte (24bit)
	REQUIRE( UArbBigInt::fromString("1", 2) << 16 == UArbBigInt::fromString("10000000 00000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 17 == UArbBigInt::fromString("10000000 00000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 18 == UArbBigInt::fromString("10000000 00000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 19 == UArbBigInt::fromString("10000000 00000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 20 == UArbBigInt::fromString("10000000 00000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 21 == UArbBigInt::fromString("10000000 00000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 22 == UArbBigInt::fromString("10000000 00000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 23 == UArbBigInt::fromString("10000000 00000000 00000000", 2) );

	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2) <<  0 == UArbBigInt::fromString("10000000 00000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2) <<  1 == UArbBigInt::fromString("10000000 00000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2) <<  2 == UArbBigInt::fromString("10000000 00000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2) <<  3 == UArbBigInt::fromString("10000000 00000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2) <<  4 == UArbBigInt::fromString("10000000 00000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2) <<  5 == UArbBigInt::fromString("10000000 00000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2) <<  6 == UArbBigInt::fromString("10000000 00000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2) <<  7 == UArbBigInt::fromString("10000000 00000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2) <<  8 == UArbBigInt::fromString("10000000 00000000 00000000", 2) );

	// 4 Byte (32bit)
	REQUIRE( UArbBigInt::fromString("1", 2) << 24 == UArbBigInt::fromString("10000000 00000000 00000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 25 == UArbBigInt::fromString("10000000 00000000 00000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 26 == UArbBigInt::fromString("10000000 00000000 00000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 27 == UArbBigInt::fromString("10000000 00000000 00000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 28 == UArbBigInt::fromString("10000000 00000000 00000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 29 == UArbBigInt::fromString("10000000 00000000 00000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 30 == UArbBigInt::fromString("10000000 00000000 00000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 31 == UArbBigInt::fromString("10000000 00000000 00000000 00000000", 2) );

	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2) <<  0 == UArbBigInt::fromString("10000000 00000000 00000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2) <<  1 == UArbBigInt::fromString("10000000 00000000 00000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2) <<  2 == UArbBigInt::fromString("10000000 00000000 00000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2) <<  3 == UArbBigInt::fromString("10000000 00000000 00000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2) <<  4 == UArbBigInt::fromString("10000000 00000000 00000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2) <<  5 == UArbBigInt::fromString("10000000 00000000 00000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2) <<  6 == UArbBigInt::fromString("10000000 00000000 00000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2) <<  7 == UArbBigInt::fromString("10000000 00000000 00000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2) <<  8 == UArbBigInt::fromString("10000000 00000000 00000000 00000000", 2) );

	// 5 Byte (40bit)
	REQUIRE( UArbBigInt::fromString("1", 2) << 32 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 33 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 34 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 35 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 36 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 37 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 38 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 39 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000", 2) );

	REQUIRE( UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) <<  0 == UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) <<  1 == UArbBigInt::fromString("10000000 00000000 10110111 00000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) <<  2 == UArbBigInt::fromString("10000000 00000000 10110111 00000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) <<  3 == UArbBigInt::fromString("10000000 00000000 10110111 00000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) <<  4 == UArbBigInt::fromString("10000000 00000000 10110111 00000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) <<  5 == UArbBigInt::fromString("10000000 00000000 10110111 00000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) <<  6 == UArbBigInt::fromString("10000000 00000000 10110111 00000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) <<  7 == UArbBigInt::fromString("10000000 00000000 10110111 00000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 10110111 00000000", 2) <<  8 == UArbBigInt::fromString("10000000 00000000 10110111 00000000 00000000", 2) );

	// 8 Byte (64bit)
	REQUIRE( UArbBigInt::fromString("1", 2) << 56 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 57 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 58 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 59 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 60 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 61 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 62 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 63 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2) );

	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  0 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  1 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  2 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  3 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  4 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  5 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  6 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  7 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) <<  8 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 00000000", 2) );

	// 9 Byte (72bit)
	REQUIRE( UArbBigInt::fromString("1", 2) << 64 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 65 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 66 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 67 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 68 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 69 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 70 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("1", 2) << 71 == UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2) );

	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  0 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  1 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  2 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  3 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  4 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  5 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  6 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  7 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) <<  8 == UArbBigInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000000", 2) );


	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   0 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                       1) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   1 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                       2) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   2 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                       4) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   3 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                       8) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   4 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                      16) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   5 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                      32) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   6 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                      64) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   7 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                     128) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   8 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                     256) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<   9 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                     512) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  10 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                    1024) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  11 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                    2048) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  12 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                    4096) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  13 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                    8192) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  14 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                   16384) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  15 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                   32768) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  16 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                   65536) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  17 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                                  131072) );

	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  63 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromUint64(                     9223372036854775808ull) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  64 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                   "18446744073709551616", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  65 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                   "36893488147419103232", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  66 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                   "73786976294838206464", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  67 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                  "147573952589676412928", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  68 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                  "295147905179352825856", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  69 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                  "590295810358705651712", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  70 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                 "1180591620717411303424", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  71 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                 "2361183241434822606848", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  72 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                 "4722366482869645213696", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) <<  73 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString(                 "9444732965739290427392", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) << 127 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString("170141183460469231731687303715884105728", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) << 128 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString("340282366920938463463374607431768211456", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) << 129 == UArbBigInt::fromString("3529260907631713815077", 10) * UArbBigInt::fromString("680564733841876926926749214863536422912", 10) );
}

TEST_CASE( "unsigned infinit big integer shift right", "[UABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  0 == UArbBigInt::fromString("10000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  1 == UArbBigInt::fromString( "1000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  2 == UArbBigInt::fromString(  "100000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  3 == UArbBigInt::fromString(   "10000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  4 == UArbBigInt::fromString(    "1000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  5 == UArbBigInt::fromString(     "100", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  6 == UArbBigInt::fromString(      "10", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  7 == UArbBigInt::fromString(       "1", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  8 == UArbBigInt::fromString(       "0", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >>  9 == UArbBigInt::fromString(       "0", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2) >> 16 == UArbBigInt::fromString(       "0", 2) );

	// 2 Byte (16bit)
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  0 == UArbBigInt::fromString("1000001100101101", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  1 == UArbBigInt::fromString("0100000110010110", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  2 == UArbBigInt::fromString("0010000011001011", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  3 == UArbBigInt::fromString("0001000001100101", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  4 == UArbBigInt::fromString("0000100000110010", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  5 == UArbBigInt::fromString("0000010000011001", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  6 == UArbBigInt::fromString("0000001000001100", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  7 == UArbBigInt::fromString("0000000100000110", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  8 == UArbBigInt::fromString("0000000010000011", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >>  9 == UArbBigInt::fromString("0000000001000001", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >> 10 == UArbBigInt::fromString("0000000000100000", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >> 11 == UArbBigInt::fromString("0000000000010000", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >> 12 == UArbBigInt::fromString("0000000000001000", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >> 13 == UArbBigInt::fromString("0000000000000100", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >> 14 == UArbBigInt::fromString("0000000000000010", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >> 15 == UArbBigInt::fromString("0000000000000001", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >> 16 == UArbBigInt::fromString("0000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >> 17 == UArbBigInt::fromString("0000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000011 00101101", 2) >> 32 == UArbBigInt::fromString("0000000000000000", 2) );

	// 8 Byte (64bit)
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   0 == UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   1 == UArbBigInt::fromString("0000000010000110110000000101010100101010100011000100100111000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   2 == UArbBigInt::fromString("0000000001000011011000000010101010010101010001100010010011100000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   3 == UArbBigInt::fromString("0000000000100001101100000001010101001010101000110001001001110000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   4 == UArbBigInt::fromString("0000000000010000110110000000101010100101010100011000100100111000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   5 == UArbBigInt::fromString("0000000000001000011011000000010101010010101010001100010010011100", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   6 == UArbBigInt::fromString("0000000000000100001101100000001010101001010101000110001001001110", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   7 == UArbBigInt::fromString("0000000000000010000110110000000101010100101010100011000100100111", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   8 == UArbBigInt::fromString("0000000000000001000011011000000010101010010101010001100010010011", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>   9 == UArbBigInt::fromString("0000000000000000100001101100000001010101001010101000110001001001", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  10 == UArbBigInt::fromString("0000000000000000010000110110000000101010100101010100011000100100", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  11 == UArbBigInt::fromString("0000000000000000001000011011000000010101010010101010001100010010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  12 == UArbBigInt::fromString("0000000000000000000100001101100000001010101001010101000110001001", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  13 == UArbBigInt::fromString("0000000000000000000010000110110000000101010100101010100011000100", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  14 == UArbBigInt::fromString("0000000000000000000001000011011000000010101010010101010001100010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  15 == UArbBigInt::fromString("0000000000000000000000100001101100000001010101001010101000110001", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  16 == UArbBigInt::fromString("0000000000000000000000010000110110000000101010100101010100011000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  17 == UArbBigInt::fromString("0000000000000000000000001000011011000000010101010010101010001100", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  18 == UArbBigInt::fromString("0000000000000000000000000100001101100000001010101001010101000110", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  19 == UArbBigInt::fromString("0000000000000000000000000010000110110000000101010100101010100011", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  20 == UArbBigInt::fromString("0000000000000000000000000001000011011000000010101010010101010001", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  21 == UArbBigInt::fromString("0000000000000000000000000000100001101100000001010101001010101000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  22 == UArbBigInt::fromString("0000000000000000000000000000010000110110000000101010100101010100", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  23 == UArbBigInt::fromString("0000000000000000000000000000001000011011000000010101010010101010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  24 == UArbBigInt::fromString("0000000000000000000000000000000100001101100000001010101001010101", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  25 == UArbBigInt::fromString("0000000000000000000000000000000010000110110000000101010100101010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  26 == UArbBigInt::fromString("0000000000000000000000000000000001000011011000000010101010010101", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  27 == UArbBigInt::fromString("0000000000000000000000000000000000100001101100000001010101001010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  28 == UArbBigInt::fromString("0000000000000000000000000000000000010000110110000000101010100101", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  29 == UArbBigInt::fromString("0000000000000000000000000000000000001000011011000000010101010010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  30 == UArbBigInt::fromString("0000000000000000000000000000000000000100001101100000001010101001", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  31 == UArbBigInt::fromString("0000000000000000000000000000000000000010000110110000000101010100", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  32 == UArbBigInt::fromString("0000000000000000000000000000000000000001000011011000000010101010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  33 == UArbBigInt::fromString("0000000000000000000000000000000000000000100001101100000001010101", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  34 == UArbBigInt::fromString("0000000000000000000000000000000000000000010000110110000000101010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  35 == UArbBigInt::fromString("0000000000000000000000000000000000000000001000011011000000010101", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  36 == UArbBigInt::fromString("0000000000000000000000000000000000000000000100001101100000001010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  37 == UArbBigInt::fromString("0000000000000000000000000000000000000000000010000110110000000101", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  38 == UArbBigInt::fromString("0000000000000000000000000000000000000000000001000011011000000010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  39 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000100001101100000001", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  40 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000010000110110000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  41 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000001000011011000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  42 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000100001101100000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  43 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000010000110110000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  44 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000001000011011000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  45 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000100001101100", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  46 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000010000110110", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  47 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000001000011011", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  48 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000100001101", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  49 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000010000110", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  50 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000001000011", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  51 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000100001", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  52 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000010000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  53 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000001000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  54 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000100", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  55 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000010", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  56 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000001", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  57 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  58 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  59 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  60 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  61 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  62 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  63 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  64 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  65 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  66 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >>  67 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) >> 127 == UArbBigInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );


	// 9 Byte (72bit)
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   0 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                      1) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   1 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                      2) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   2 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                      4) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   3 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                      8) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   4 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                     16) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   5 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                     32) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   6 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                     64) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   7 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                    128) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   8 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                    256) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>   9 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                    512) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  10 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                   1024) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  11 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                   2048) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  12 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                   4096) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  13 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                   8192) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  14 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                  16384) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  15 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                  32768) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  16 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(                  65536) );

	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  63 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromUint64(    9223372036854775808ull) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  64 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString(  "18446744073709551616", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  65 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString(  "36893488147419103232", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  66 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString(  "73786976294838206464", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  67 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString( "147573952589676412928", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  68 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString( "295147905179352825856", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  69 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString( "590295810358705651712", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  70 == UArbBigInt::fromString("3529260907631713815077", 10) / UArbBigInt::fromString("1180591620717411303424", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  71 == UArbBigInt::fromString("1", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  72 == UArbBigInt::fromString("0", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >>  73 == UArbBigInt::fromString("0", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >> 127 == UArbBigInt::fromString("0", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >> 128 == UArbBigInt::fromString("0", 10) );
	REQUIRE( UArbBigInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2) >> 129 == UArbBigInt::fromString("0", 10) );
}

TEST_CASE( "unsigned infinit big integer addition", "[UABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (UArbBigInt(  0) + UArbBigInt(  0)).toUint64()	==   0 );
	REQUIRE( (UArbBigInt(  1) + UArbBigInt(  0)).toUint64()	==   1 );
	REQUIRE( (UArbBigInt(  0) + UArbBigInt(  1)).toUint64()	==   1 );
	REQUIRE( (UArbBigInt(  1) + UArbBigInt(  1)).toUint64()	==   2 );
	REQUIRE( (UArbBigInt(  2) + UArbBigInt(  1)).toUint64()	==   3 );
	REQUIRE( (UArbBigInt(  1) + UArbBigInt(  2)).toUint64()	==   3 );
	REQUIRE( (UArbBigInt( 10) + UArbBigInt(  1)).toUint64()	==  11 );
	REQUIRE( (UArbBigInt(128) + UArbBigInt(127)).toUint64()	== 255 );

	// 2 Bytes (16 bit)
	REQUIRE( (UArbBigInt(128) + UArbBigInt(128)).toUint64()	== 0x0100ull );
	REQUIRE( (UArbBigInt(255) + UArbBigInt(  1)).toUint64()	== 0x0100ull );
	REQUIRE( (UArbBigInt(  1) + UArbBigInt(255)).toUint64()	== 0x0100ull );
	REQUIRE( (UArbBigInt(255) + UArbBigInt(255)).toUint64()	== 0x01FEull );

	REQUIRE( (UArbBigInt::fromUint64(0x7FFF) + UArbBigInt::fromUint64(0x7FFF) 				).toUint64() == 0xFFFEull );
	REQUIRE( (UArbBigInt::fromUint64(0x7FFF) + UArbBigInt::fromUint64(0x7FFF) + UArbBigInt(0)	).toUint64() == 0xFFFEull );
	REQUIRE( (UArbBigInt::fromUint64(0x7FFF) + UArbBigInt::fromUint64(0x7FFF) + UArbBigInt(1) 	).toUint64() == 0xFFFFull );
	REQUIRE( (UArbBigInt(1) + UArbBigInt::fromUint64(0x7FFF) + UArbBigInt::fromUint64(0x7FFF) 	).toUint64() == 0xFFFFull );

	// 4 Bytes (32bit)
	REQUIRE( (UArbBigInt::fromUint64(0x8000) + UArbBigInt::fromUint64(0x8000)).toUint64() 	== 0x010000ull );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFF) + UArbBigInt::fromUint64(  0x01)).toUint64() 	== 0x010000ull );
	REQUIRE( (UArbBigInt::fromUint64(  0x01) + UArbBigInt::fromUint64(0xFFFF)).toUint64() 	== 0x010000ull );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFF) + UArbBigInt::fromUint64(0xFFFF)).toUint64() 	== 0x01FFFEull );

	REQUIRE( (UArbBigInt::fromUint64(0x7FFFFFFF) + UArbBigInt::fromUint64(0x7FFFFFFF) 				).toUint64() == 0xFFFFFFFEull );
	REQUIRE( (UArbBigInt::fromUint64(0x7FFFFFFF) + UArbBigInt::fromUint64(0x7FFFFFFF) + UArbBigInt(0) 	).toUint64() == 0xFFFFFFFEull );
	REQUIRE( (UArbBigInt::fromUint64(0x7FFFFFFF) + UArbBigInt::fromUint64(0x7FFFFFFF) + UArbBigInt(1) 	).toUint64() == 0xFFFFFFFFull );
	REQUIRE( (UArbBigInt(1) + UArbBigInt::fromUint64(0x7FFFFFFF) + UArbBigInt::fromUint64(0x7FFFFFFF) 	).toUint64() == 0xFFFFFFFFull );

	// 8 Bytes (64bit)
	REQUIRE( (UArbBigInt::fromUint64(0x80000000) + UArbBigInt::fromUint64(0x80000000)).toUint64() 	== 0x0100000000ull );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFF) + UArbBigInt::fromUint64(      0x01)).toUint64() 	== 0x0100000000ull );
	REQUIRE( (UArbBigInt::fromUint64(      0x01) + UArbBigInt::fromUint64(0xFFFFFFFF)).toUint64() 	== 0x0100000000ull );
	REQUIRE( (UArbBigInt::fromUint64(0xFFFFFFFF) + UArbBigInt::fromUint64(0xFFFFFFFF)).toUint64() 	== 0x01FFFFFFFEull );

	REQUIRE( (UArbBigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + UArbBigInt::fromUint64(0x7FFFFFFFFFFFFFFF) 				).toUint64() == 0xFFFFFFFFFFFFFFFEull );
	REQUIRE( (UArbBigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + UArbBigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + UArbBigInt(0)	).toUint64() == 0xFFFFFFFFFFFFFFFEull );
	REQUIRE( (UArbBigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + UArbBigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + UArbBigInt(1)	).toUint64() == 0xFFFFFFFFFFFFFFFFull );
	REQUIRE( (UArbBigInt(1) + UArbBigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + UArbBigInt::fromUint64(0x7FFFFFFFFFFFFFFF)	).toUint64() == 0xFFFFFFFFFFFFFFFFull );

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
}

TEST_CASE( "unsigned infinit big integer subtraction", "[UABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (UArbBigInt(  0) - UArbBigInt(  0)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(  1) - UArbBigInt(  0)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt(  1) - UArbBigInt(  1)).toUint64() ==   0 );

	REQUIRE( (UArbBigInt(  9) - UArbBigInt(  1)).toUint64() ==   8 );
	REQUIRE( (UArbBigInt(  9) - UArbBigInt(  9)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt( 10) - UArbBigInt(  9)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt(255) - UArbBigInt(  0)).toUint64() == 255 );
	REQUIRE( (UArbBigInt(255) - UArbBigInt(255)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(255) - UArbBigInt( 1)).toUint64() 	== 254 );

	// 2 Bytes (16 bit)
	REQUIRE( (UArbBigInt::fromUint64(0x0100ull) - UArbBigInt::fromUint64(0x0100ull)).toUint64() ==   0x00ull ); // 256 - 256 = 0
	REQUIRE( (UArbBigInt::fromUint64(0x0101ull) - UArbBigInt::fromUint64(0x0100ull)).toUint64() ==   0x01ull ); // 257 - 256 = 1
	REQUIRE( (UArbBigInt::fromUint64(0x0101ull) - UArbBigInt::fromUint64(  0x01ull)).toUint64() == 0x0100ull ); // 257 - 1 = 256
	REQUIRE( (UArbBigInt::fromUint64(0x0101ull) - UArbBigInt::fromUint64(  0x02ull)).toUint64() ==   0xFFull ); // 257 - 2 = 255

	// 4 Bytes (32bit)
	REQUIRE( (UArbBigInt::fromUint64(0x010000ull) - UArbBigInt::fromUint64(0x010000ull)).toUint64() ==     0x00ull ); // 2^16 - 2^16 = 0
	REQUIRE( (UArbBigInt::fromUint64(0x010001ull) - UArbBigInt::fromUint64(0x010000ull)).toUint64() ==     0x01ull ); // (2^16 + 1) - 2^16 = 1
	REQUIRE( (UArbBigInt::fromUint64(0x010001ull) - UArbBigInt::fromUint64(    0x01ull)).toUint64() == 0x010000ull ); // (2^16 + 1) - 1 = 2^16
	REQUIRE( (UArbBigInt::fromUint64(0x010001ull) - UArbBigInt::fromUint64(    0x02ull)).toUint64() == 0x00FFFFull ); // (2^16 + 1) - 2 = 2^16 - 1

	// 8 Bytes (64bit)
	REQUIRE( (UArbBigInt::fromUint64(0x0100000000ull) - UArbBigInt::fromUint64(0x0100000000ull)).toUint64() 	==         0x00ull ); // 2^32 - 2^32 = 0
	REQUIRE( (UArbBigInt::fromUint64(0x0100000001ull) - UArbBigInt::fromUint64(0x0100000000ull)).toUint64() 	==         0x01ull ); // (2^32 + 1) - 2^32 = 1
	REQUIRE( (UArbBigInt::fromUint64(0x0100000001ull) - UArbBigInt::fromUint64(        0x01ull)).toUint64() 	== 0x0100000000ull ); // (2^32 + 1) - 1 = 2^32
	REQUIRE( (UArbBigInt::fromUint64(0x0100000001ull) - UArbBigInt::fromUint64(        0x02ull)).toUint64() 	== 0x00FFFFFFFFull ); // (2^32 + 1) - 2 = 2^32 - 1

	// 16 Bytes (128bit)
	REQUIRE( UArbBigInt::fromString("010000000000000000", 16) - UArbBigInt::fromString("010000000000000000", 16) 	== 							  UArbBigInt(0x00)      ); // 2^64 - 2^64 = 0
	REQUIRE( UArbBigInt::fromString("010000000000000001", 16) - UArbBigInt::fromString("010000000000000000", 16) 	==                            UArbBigInt(0x01)      ); // (2^64 + 1) - 2^64 = 1
	REQUIRE( UArbBigInt::fromString("010000000000000001", 16) - UArbBigInt::fromUint64(               0x01ull)	 	== UArbBigInt::fromString("010000000000000000", 16) ); // (2^64 + 1) - 1 = 2^64
	REQUIRE( UArbBigInt::fromString("010000000000000001", 16) - UArbBigInt::fromUint64(               0x02ull)		== UArbBigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull)   ); // (2^64 + 1) - 2 = 2^64 - 1

	REQUIRE( UArbBigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) - UArbBigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) == UArbBigInt::fromString("fdb97530eca86421000000000000000eca8641fdb975320", 16) );
	REQUIRE( UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10) - UArbBigInt::fromString("123456789000000000000000000000000000001234567890", 10) == UArbBigInt::fromString("864197532000000000000000000000000000008641975320", 10) );
}

TEST_CASE( "unsigned infinit big integer multiplication", "[UABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (UArbBigInt(  0) * UArbBigInt(0)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(  1) * UArbBigInt(0)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(  1) * UArbBigInt(1)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt(  2) * UArbBigInt(1)).toUint64() ==   2 );
	REQUIRE( (UArbBigInt(  1) * UArbBigInt(2)).toUint64() ==   2 );
	REQUIRE( (UArbBigInt( 10) * UArbBigInt(0)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt( 11) * UArbBigInt(2)).toUint64() ==  22 );
	REQUIRE( (UArbBigInt(127) * UArbBigInt(2)).toUint64() == 254 );

	// 2 Bytes (16 bit)
	REQUIRE( (UArbBigInt(128) * UArbBigInt(              2)).toUint64() == 0x0100ull );
	REQUIRE( (UArbBigInt(128) * UArbBigInt(              4)).toUint64() == 0x0200ull );
	REQUIRE( (UArbBigInt(123) * UArbBigInt::fromUint64(532)).toUint64() == 0xFF9Cull );
	REQUIRE( (UArbBigInt( 98) * UArbBigInt::fromUint64(571)).toUint64() == 0xDA96ull );

	REQUIRE( (UArbBigInt::fromUint64(0x0100ull) * UArbBigInt::fromUint64(0x0FFull)).toUint64() == 0xFF00ull );
	REQUIRE( (UArbBigInt::fromUint64(0x0011ull) * UArbBigInt::fromUint64(0x0FFull)).toUint64() == 0x10EFull );

	// 4 Bytes (32bit)
	REQUIRE( (UArbBigInt::fromUint64(    0xFFFFull) * UArbBigInt::fromUint64( 0xFFFFull)).toUint64() == 0xFFFE0001ull );

	REQUIRE( (UArbBigInt::fromUint64(    0x0100ull) * UArbBigInt::fromUint64( 0x0100ull)).toUint64() ==   0x010000ull );
	REQUIRE( (UArbBigInt::fromUint64(    0x0100ull) * UArbBigInt::fromUint64( 0x0F00ull)).toUint64() ==   0x0F0000ull );

	REQUIRE( (UArbBigInt::fromUint64(0x55555555ull) * UArbBigInt::fromUint64(  0x003ull)).toUint64() == 0xFFFFFFFFull );
	REQUIRE( (UArbBigInt::fromUint64(    0xEFEFull) * UArbBigInt::fromUint64(   0xEFull)).toUint64() ==   0xE00021ull );
	REQUIRE( (UArbBigInt::fromUint64(    0xEFEFull) * UArbBigInt::fromUint64( 0xEFEFull)).toUint64() == 0xE0E02121ull );

	REQUIRE( (UArbBigInt::fromUint64(0xff9Cull) * UArbBigInt::fromUint64(  0x7Bull)).toUint64() == 0x7ACFF4ull ); // 65436 * 123 = 8048628

	// 8 Bytes (64bit)
	REQUIRE( (UArbBigInt::fromUint64(    0xFFFFFFFFull) * UArbBigInt::fromUint64( 0xFFFFFFFFull)).toUint64() == 0xFFFFFFFE00000001ull );
	REQUIRE( (UArbBigInt::fromUint64(    0xFFFFFFFFull) * UArbBigInt::fromUint64(       0x02ull)).toUint64() ==        0x1FFFFFFFEull );
	REQUIRE( (UArbBigInt::fromUint64(    0xFEDCBA98ull) * UArbBigInt::fromUint64( 0x12345678ull)).toUint64() == 0x121FA00A35068740ull );
	REQUIRE( (UArbBigInt::fromUint64(    0xFEDCBA98ull) * UArbBigInt::fromUint64( 0x12345678ull)).toUint64() == 0xFEDCBA98ull * 0x12345678ull);

	// 16 Bytes (128bit)
	REQUIRE( UArbBigInt::fromUint64(    0xFFFFFFFFFFFFFFFFull) * UArbBigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull) == UArbBigInt::fromString("FFFFFFFFFFFFFFFE0000000000000001", 16) );
	REQUIRE( UArbBigInt::fromUint64(    0xFFFFFFFFFFFFFFFFull) * UArbBigInt::fromUint64(               0x02ull) == UArbBigInt::fromString(               "1FFFFFFFFFFFFFFFE", 16) );
	REQUIRE( UArbBigInt::fromUint64(    0xFEDCBA9876543210ull) * UArbBigInt::fromUint64( 0x123456789ABCDEF0ull) == UArbBigInt::fromString("24090311171252216041959356964269510400", 10) ); // 18364758544493064720 * 1311768467463790320 = 24090311171252216041959356964269510400
	REQUIRE( UArbBigInt::fromUint64(    0xFEDCBA9876543210ull) * UArbBigInt::fromUint64( 0x123456789ABCDEF0ull) == UArbBigInt::fromString("121fa00ad77d7422236d88fe5618cf00", 16) ); // 18364758544493064720 * 1311768467463790320 = 24090311171252216041959356964269510400
	REQUIRE( (UArbBigInt::fromUint64(    0xFEDCBA9876543210ull) * UArbBigInt::fromUint64( 0x123456789ABCDEF0ull)).toStringDec() == std::string("24090311171252216041959356964269510400") ); // 18364758544493064720 * 1311768467463790320 = 24090311171252216041959356964269510400

	// -------
	REQUIRE( UArbBigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) *  UArbBigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) == UArbBigInt::fromString("121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16) );
	REQUIRE( UArbBigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) *  UArbBigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) == UArbBigInt::fromString("121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16) );

	REQUIRE( UArbBigInt::fromString("123456789000000000000000000000000000001234567890", 10) *  UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10) == UArbBigInt::fromString("121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) );
	REQUIRE( UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10) *  UArbBigInt::fromString("123456789000000000000000000000000000001234567890", 10) == UArbBigInt::fromString("121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) );
}

TEST_CASE( "unsigned infinit big integer division", "[UABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (UArbBigInt(  0) / UArbBigInt(  1)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(  0) % UArbBigInt(  1)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(  1) / UArbBigInt(  1)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt(  1) % UArbBigInt(  1)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(  1) / UArbBigInt(  2)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(  1) % UArbBigInt(  2)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt(  2) / UArbBigInt(  1)).toUint64() ==   2 );
	REQUIRE( (UArbBigInt(  2) % UArbBigInt(  1)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(  2) / UArbBigInt(  2)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt(  2) % UArbBigInt(  2)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(  4) / UArbBigInt(  2)).toUint64() ==   2 );
	REQUIRE( (UArbBigInt(  4) % UArbBigInt(  2)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt( 10) / UArbBigInt(  1)).toUint64() ==  10 );
	REQUIRE( (UArbBigInt( 10) % UArbBigInt(  1)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt( 10) / UArbBigInt(  2)).toUint64() ==   5 );
	REQUIRE( (UArbBigInt( 10) % UArbBigInt(  2)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt( 10) / UArbBigInt(  3)).toUint64() ==   3 );
	REQUIRE( (UArbBigInt( 10) % UArbBigInt(  3)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt( 10) / UArbBigInt(  5)).toUint64() ==   2 );
	REQUIRE( (UArbBigInt( 10) % UArbBigInt(  5)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt( 11) / UArbBigInt(  2)).toUint64() ==   5 );
	REQUIRE( (UArbBigInt( 11) % UArbBigInt(  2)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt( 12) / UArbBigInt(  2)).toUint64() ==   6 );
	REQUIRE( (UArbBigInt( 12) % UArbBigInt(  2)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(252) / UArbBigInt(  2)).toUint64() == 126 );
	REQUIRE( (UArbBigInt(252) % UArbBigInt(  2)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(253) / UArbBigInt(  2)).toUint64() == 126 );
	REQUIRE( (UArbBigInt(253) % UArbBigInt(  2)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt(254) / UArbBigInt(  2)).toUint64() == 127 );
	REQUIRE( (UArbBigInt(254) % UArbBigInt(  2)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(255) / UArbBigInt(  2)).toUint64() == 127 );
	REQUIRE( (UArbBigInt(255) % UArbBigInt(  2)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt(255) / UArbBigInt(255)).toUint64() ==   1 );
	REQUIRE( (UArbBigInt(255) % UArbBigInt(255)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(254) / UArbBigInt(127)).toUint64() ==   2 );
	REQUIRE( (UArbBigInt(254) % UArbBigInt(127)).toUint64() ==   0 );
	REQUIRE( (UArbBigInt(255) / UArbBigInt(127)).toUint64() ==   2 );
	REQUIRE( (UArbBigInt(255) % UArbBigInt(127)).toUint64() ==   1 );


	// 2 Bytes (16 bit)
	REQUIRE( (UArbBigInt::fromUint64(0x0100ull) / UArbBigInt(                2)).toUint64() ==   128);
	REQUIRE( (UArbBigInt::fromUint64(0x0100ull) % UArbBigInt(                2)).toUint64() ==     0);
	REQUIRE( (UArbBigInt::fromUint64(0x0200ull) / UArbBigInt(                4)).toUint64() ==   128);
	REQUIRE( (UArbBigInt::fromUint64(0x0200ull) % UArbBigInt(                4)).toUint64() ==     0);
	REQUIRE( (UArbBigInt::fromUint64(0x0100ull) / UArbBigInt::fromUint64(0x100)).toUint64() ==     1);
	REQUIRE( (UArbBigInt::fromUint64(0x0100ull) % UArbBigInt::fromUint64(0x100)).toUint64() ==     0);
	REQUIRE( (UArbBigInt::fromUint64(0x0200ull) / UArbBigInt::fromUint64(0x100)).toUint64() ==     2);
	REQUIRE( (UArbBigInt::fromUint64(0x0200ull) % UArbBigInt::fromUint64(0x100)).toUint64() ==     0);
	REQUIRE( (UArbBigInt::fromUint64(0x0200ull) / UArbBigInt::fromUint64(0x200)).toUint64() ==     1);
	REQUIRE( (UArbBigInt::fromUint64(0x0200ull) % UArbBigInt::fromUint64(0x200)).toUint64() ==     0);
	REQUIRE( (UArbBigInt::fromUint64(0x0300ull) / UArbBigInt::fromUint64(0x200)).toUint64() ==     1);
	REQUIRE( (UArbBigInt::fromUint64(0x0300ull) % UArbBigInt::fromUint64(0x200)).toUint64() == 0x100);
	REQUIRE( (UArbBigInt::fromUint64(0x0400ull) / UArbBigInt::fromUint64(0x200)).toUint64() ==     2);
	REQUIRE( (UArbBigInt::fromUint64(0x0400ull) % UArbBigInt::fromUint64(0x200)).toUint64() ==     0);
	REQUIRE( (UArbBigInt::fromUint64(0xFF9Cull) / UArbBigInt::fromUint64(0x100)).toUint64() ==  0xff);
	REQUIRE( (UArbBigInt::fromUint64(0xFF9Cull) % UArbBigInt::fromUint64(0x100)).toUint64() ==  0x9C);
	REQUIRE( (UArbBigInt::fromUint64(0xFF9Cull) / UArbBigInt::fromUint64(  532)).toUint64() ==   123);
	REQUIRE( (UArbBigInt::fromUint64(0xFF9Cull) % UArbBigInt::fromUint64(  532)).toUint64() ==     0);
	REQUIRE( (UArbBigInt::fromUint64(0xDA96ull) / UArbBigInt::fromUint64(  571)).toUint64() ==    98);
	REQUIRE( (UArbBigInt::fromUint64(0xDA96ull) % UArbBigInt::fromUint64(  571)).toUint64() ==     0);

	REQUIRE( (UArbBigInt::fromUint64(0xFF00ull) / UArbBigInt::fromUint64(0x0FFull)).toUint64() == 0x0100ull );
	REQUIRE( (UArbBigInt::fromUint64(0xFF00ull) % UArbBigInt::fromUint64(0x0FFull)).toUint64() ==      0ull );
	REQUIRE( (UArbBigInt::fromUint64(0x10EFull) / UArbBigInt::fromUint64(0x0FFull)).toUint64() == 0x0011ull );
	REQUIRE( (UArbBigInt::fromUint64(0x10EFull) % UArbBigInt::fromUint64(0x0FFull)).toUint64() ==      0ull );

	// 4 Bytes (32bit)
	REQUIRE( (UArbBigInt::fromUint64( 0xFFFE0001ull) / UArbBigInt::fromUint64( 0xFFFFull)).toUint64() ==     0xFFFFull ); // first test of D5. [Test Remainder] and D6. [add back] (at 8bit words)
	REQUIRE( (UArbBigInt::fromUint64( 0xFFFE0001ull) % UArbBigInt::fromUint64( 0xFFFFull)).toUint64() ==          0ull );

	REQUIRE( (UArbBigInt::fromUint64(   0x010000ull) / UArbBigInt::fromUint64( 0x0100ull)).toUint64() ==     0x0100ull );
	REQUIRE( (UArbBigInt::fromUint64(   0x010000ull) % UArbBigInt::fromUint64( 0x0100ull)).toUint64() ==          0ull );
	REQUIRE( (UArbBigInt::fromUint64(   0x0F0000ull) / UArbBigInt::fromUint64( 0x0F00ull)).toUint64() ==     0x0100ull );
	REQUIRE( (UArbBigInt::fromUint64(   0x0F0000ull) % UArbBigInt::fromUint64( 0x0F00ull)).toUint64() ==          0ull );

	REQUIRE( (UArbBigInt::fromUint64( 0xFFFFFFFFull) / UArbBigInt::fromUint64(  0x003ull)).toUint64() == 0x55555555ull );
	REQUIRE( (UArbBigInt::fromUint64( 0xFFFFFFFFull) % UArbBigInt::fromUint64(  0x003ull)).toUint64() ==          0ull );
	REQUIRE( (UArbBigInt::fromUint64(   0xE00021ull) / UArbBigInt::fromUint64(   0xEFull)).toUint64() ==     0xEFEFull );
	REQUIRE( (UArbBigInt::fromUint64(   0xE00021ull) % UArbBigInt::fromUint64(   0xEFull)).toUint64() ==          0ull );
	REQUIRE( (UArbBigInt::fromUint64( 0xE0E02121ull) / UArbBigInt::fromUint64( 0xEFEFull)).toUint64() ==     0xEFEFull );
	REQUIRE( (UArbBigInt::fromUint64( 0xE0E02121ull) % UArbBigInt::fromUint64( 0xEFEFull)).toUint64() ==          0ull );

	// 8 Bytes (64bit)
	REQUIRE( (UArbBigInt::fromUint64(          0xFFFFFFFE00000001ull) / UArbBigInt::fromUint64( 0xFFFFFFFFull)).toUint64() == 0xFFFFFFFFull ); // test of D5. [Test Remainder] and D6. [add back] (at 8bit words)
	REQUIRE( (UArbBigInt::fromUint64(          0xFFFFFFFE00000001ull) % UArbBigInt::fromUint64( 0xFFFFFFFFull)).toUint64() ==          0ull );

	REQUIRE( (UArbBigInt::fromUint64(                 0x1FFFFFFFEull) / UArbBigInt::fromUint64(       0x02ull)).toUint64() == 0xFFFFFFFFull );
	REQUIRE( (UArbBigInt::fromUint64(                 0x1FFFFFFFEull) % UArbBigInt::fromUint64(       0x02ull)).toUint64() ==          0ull );
	REQUIRE( (UArbBigInt::fromUint64(          0x121FA00A35068740ull) / UArbBigInt::fromUint64( 0x12345678ull)).toUint64() == 0xFEDCBA98ull );
	REQUIRE( (UArbBigInt::fromUint64(          0x121FA00A35068740ull) % UArbBigInt::fromUint64( 0x12345678ull)).toUint64() ==          0ull );
	REQUIRE( (UArbBigInt::fromUint64(  0xFEDCBA98ull * 0x12345678ull) / UArbBigInt::fromUint64( 0x12345678ull)).toUint64() == 0xFEDCBA98ull );
	REQUIRE( (UArbBigInt::fromUint64(  0xFEDCBA98ull * 0x12345678ull) % UArbBigInt::fromUint64( 0x12345678ull)).toUint64() ==          0ull );

	// 16 Bytes (128bit)
	REQUIRE( UArbBigInt::fromString(       "FFFFFFFFFFFFFFFE0000000000000001", 16) / UArbBigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull) == UArbBigInt::fromUint64(    0xFFFFFFFFFFFFFFFFull)); // test of D5. [Test Remainder] and D6. [add back] (at 8bit words)
	REQUIRE( UArbBigInt::fromString(       "FFFFFFFFFFFFFFFE0000000000000001", 16) % UArbBigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull) == UArbBigInt::fromUint64(                     0ull));

	REQUIRE( UArbBigInt::fromString(                      "1FFFFFFFFFFFFFFFE", 16) / UArbBigInt::fromUint64(               0x02ull) == UArbBigInt::fromUint64(    0xFFFFFFFFFFFFFFFFull));
	REQUIRE( UArbBigInt::fromString(                      "1FFFFFFFFFFFFFFFE", 16) % UArbBigInt::fromUint64(               0x02ull) == UArbBigInt::fromUint64(                     0ull));
	REQUIRE( UArbBigInt::fromString( "24090311171252216041959356964269510400", 10) / UArbBigInt::fromUint64( 0x123456789ABCDEF0ull) == UArbBigInt::fromUint64(    0xFEDCBA9876543210ull)); // 24090311171252216041959356964269510400 / 1311768467463790320 = 18364758544493064720
	REQUIRE( UArbBigInt::fromString( "24090311171252216041959356964269510400", 10) % UArbBigInt::fromUint64( 0x123456789ABCDEF0ull) == UArbBigInt::fromUint64(                     0ull));
	REQUIRE( UArbBigInt::fromString(       "121fa00ad77d7422236d88fe5618cf00", 16) / UArbBigInt::fromUint64( 0x123456789ABCDEF0ull) == UArbBigInt::fromUint64(    0xFEDCBA9876543210ull)); // 24090311171252216041959356964269510400 / 1311768467463790320 = 18364758544493064720
	REQUIRE( UArbBigInt::fromString(       "121fa00ad77d7422236d88fe5618cf00", 16) % UArbBigInt::fromUint64( 0x123456789ABCDEF0ull) == UArbBigInt::fromUint64(                     0ull));

	// -------
	REQUIRE( UArbBigInt::fromString(    "121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16) / UArbBigInt::fromString( "fedcba9876543210000000000000000fedcba9876543210", 16) == UArbBigInt::fromString(  "123456789abcdef000000000000000123456789abcdef0", 16));
	REQUIRE( UArbBigInt::fromString(    "121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16) % UArbBigInt::fromString( "fedcba9876543210000000000000000fedcba9876543210", 16) == UArbBigInt::fromString(                                               "0", 16));
	REQUIRE( UArbBigInt::fromString( "121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) / UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10) == UArbBigInt::fromString("123456789000000000000000000000000000001234567890", 10));
	REQUIRE( UArbBigInt::fromString( "121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) % UArbBigInt::fromString("987654321000000000000000000000000000009876543210", 10) == UArbBigInt::fromString(                                               "0", 10));

	// ------
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UArbBigInt::fromString("1", 10) == UArbBigInt::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10));
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UArbBigInt::fromString("1", 10) == UArbBigInt::fromString(                                                                                                         "0", 10));
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UArbBigInt::fromString("2", 10) == UArbBigInt::fromString("3282327327325825708273258273273258263263232825825739394992080780749242493932813447459093582582732732572788", 10));
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UArbBigInt::fromString("2", 10) == UArbBigInt::fromString(                                                                                                         "1", 10));
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UArbBigInt::fromString("147", 10) == UArbBigInt::fromString("44657514657494227323445690792833445758683439807152916938667765724479489713371611530055695001125615409153", 10));
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UArbBigInt::fromString("147", 10) == UArbBigInt::fromString(                                                                                                      "86", 10));
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UArbBigInt::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) == UArbBigInt::fromString("1", 10));
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UArbBigInt::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) == UArbBigInt::fromString("0", 10));
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / UArbBigInt::fromString("5555555555555544455555555555555555444441122235654445554547555", 10) == UArbBigInt::fromString("1181637837837299615890772977303005548172635842", 10));
	REQUIRE( UArbBigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % UArbBigInt::fromString("5555555555555544455555555555555555444441122235654445554547555", 10) == UArbBigInt::fromString("102256964850719633725637788587322669027978740977851378679267", 10));

	REQUIRE( UArbBigInt::fromString( "121212121121212454564757645640000000000000000000546424465744466464313145643", 10) / UArbBigInt::fromString("46464644515442612", 10) == UArbBigInt::fromString("2608695759652855584042902602291341403871593244214364153233", 10));
	REQUIRE( UArbBigInt::fromString( "121212121121212454564757645640000000000000000000546424465744466464313145643", 10) % UArbBigInt::fromString("46464644515442612", 10) == UArbBigInt::fromString("5925350727381047", 10));
	REQUIRE( UArbBigInt::fromString( "AEDBBBBBDDDFFFFFFFFFFF65156895651516500000000000000000F", 16) / UArbBigInt::fromString("FFFFFFFFFF56556165465466546546546546122222222F", 16) == UArbBigInt::fromString("aedbbbbbd", 16));
	REQUIRE( UArbBigInt::fromString( "AEDBBBBBDDDFFFFFFFFFFF65156895651516500000000000000000F", 16) % UArbBigInt::fromString("FFFFFFFFFF56556165465466546546546546122222222F", 16) == UArbBigInt::fromString("e53e3992ef3e65ed83201fbc921bdf68de2743627f6e5c", 16));

	REQUIRE( UArbBigInt::fromString( "15485863", 10) / UArbBigInt::fromString("17", 10) == UArbBigInt::fromString("910933", 10));
	REQUIRE( UArbBigInt::fromString( "15485863", 10) % UArbBigInt::fromString("17", 10) == UArbBigInt::fromString("2", 10));

}

TEST_CASE( "unsigned infinit big integer pow", "[UABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UArbBigInt(  1).pow(UArbBigInt(  1)).toUint64() ==   1 );
	REQUIRE( UArbBigInt(  0).pow(UArbBigInt(  1)).toUint64() ==   0 );
	REQUIRE( UArbBigInt(  0).pow(UArbBigInt(  2)).toUint64() ==   0 );
	REQUIRE( UArbBigInt(  0).pow(UArbBigInt(  3)).toUint64() ==   0 );
	REQUIRE( UArbBigInt(  0).pow(UArbBigInt(255)).toUint64() ==   0 );
	REQUIRE( UArbBigInt(  1).pow(UArbBigInt(  0)).toUint64() ==   1 );
	REQUIRE( UArbBigInt(  2).pow(UArbBigInt(  0)).toUint64() ==   1 );
	REQUIRE( UArbBigInt(  3).pow(UArbBigInt(  0)).toUint64() ==   1 );
	REQUIRE( UArbBigInt(255).pow(UArbBigInt(  0)).toUint64() ==   1 );


	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(0)).toUint64() ==   1 );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(1)) == UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(2)) ==   UArbBigInt::fromString("1524048626526185117008148645329708998795770321794318911442256140455458946053172210513801777413097237329246447244122385285308414454789711324787960475901495579519924778756", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(3)) == UArbBigInt::fromString("1881474063392538580104293111393515179649632793959103295994811562361294554161939745982608133564565542204073242684988356858761198894560865302229744629701298307382732414852446913292026698808738732944827521756186090834642278871507135064538602803625789936904", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(4)) == UArbBigInt::fromString("2322724216016351285472707124797887713981534093719739103213407334702107425041932730777326153711532379822978430798408976244316601438139655559996863723159199445623538286148496267102069962655433997187047023578211999563638238190873223997008007371192667094663558359643750680318859643251894423390770637182150347047660358392496015012475548907536", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(5)) == UArbBigInt::fromString("2867457962158038971853938647659375320115494383219896161741583092210829444699615500326588552418737089216037940156999920949940166545191462082581253155295134695870831145921714817833094876533390847748267009204859527832933060930612590727989929106335206340916340073313189287861119834506233261329926851146364423475764872904013979979647627788807185431063573845274690387283341162568066853325074114840393511798145094976543399611424", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(6)) == UArbBigInt::fromString("3539944651218830283540237184943231733526400651356915543005999830870728064470946236962840236630958805963468880528581970518426253453126552935135702339291798727869826342947189921425668475204474360928826722707549964601043918911967378559821737176530807786999546527891889398340508787606662886034686369292655165825645593194777876820396404402099390250401340029154647740647755879072938227342165972233945850036459828750018220652089900824625252564384949798192695376327532441052506514246293241314988128954312301105216", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(7)) == UArbBigInt::fromString("4370145368848532993242523075480569474139689185243537323461489922215230490555285155220171557274942547946391227642834796084203294700211008420494777946537074472184785618953558877240196071108329207824554743163383909448668325710116607092261566917692365671156479943140409928293640801157769626295637371165926498441822931984045867370978011530469809936350130402824887833172879161880272854103993910122813147049672068271585034130216078042298280565291016527870287491535160333187558206060681978142740974783641780486905910766479698398585528176367347217326798941738259976825918154594987947097719570108544", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(8)) == UArbBigInt::fromString("5395047783668773709460639056224185760889235717278209951617981537996864826581460683682501318938815681656151958366140465272884649876381694772498596841934270041178306976885452204765063226273182513141163415617476121267278772677860029973492021040065556863907996371801937962087527374769987283177425267845426325078540447496795491526579513442194482548092077099751401641305494953304352311309669493975681079008283809834498665401746908842008129396834776449030813934294217884594751428876570388384142266037241163723638366407733503102721783079433521192695271104586599752841392843737198696981062031279116702499649000416708580359920953881420098099346685016780778222606258624322683077591296", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(9)) == UArbBigInt::fromString("6660314047113375362717118830937150418894822047689175393373261671094594020566478309787317394536511654440334145396014118250585775607229382517821857691572311721610361814315339092248604034789677002480899646574438926664785599408420949268895302251058514364940634764862382757544044760638210705868384389235211642594541458339214544495817772551070071638986276284136919611246439790071468861836483776797120826186998385040118047655817351174172012988433608066340201003365144512395679567507777521535751903610199604821667817269481414854081548331738516698573839760290854730756066914126892758698199224637074055449072973410012335191441628122431795002240207292069084514744712983684809263796595352722062614488551975275543914901720954495344443353023118414301445927792170105291264", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(10)) == UArbBigInt::fromString("8222315164743533660322716869205426863298595939614360305442998688209230822741081065880621484469343806415355099455827992366204650030477782349786805802611371198385552114729607612922493857084859636592884607302472143286667576151286304509748792169775990414683086310499759210086314636846142836598831338179359936823353371796102561138300730509971405941785043312353445877831136983874954344159228211618775469143483738566408548893667340467692018161874545230032443789619494305274302301113989109668836113826465977227815031287792805790862002225986391995444892842504718408666055595037262539997469969697387246472169537858751674998655549656461006006174519707063523399279679397216139896950840488719823220059762423870515397663615757747330968399275746884748859378061652915318561679597724441030415446783066798052540826374335278428786048844155232349343754191307776", 10) );

	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(127)) == UArbBigInt::fromString("417277835567150141191109395931676669187596598594742769231298337489746577103940594588352572819875934610526087127658594429760591231603023165051763326238472146198980522690073560006071408899372813173449415394677024908310339914206830566820031822815124820686693258703460257053244419949289360746368526154134448101668461547772048449299120018317194753884121404398161188985217076863186914235426474539187446142336386468315114037214801138088855013799049008692643528381930269961079215631734139042611824145905382240310073973983746820887774595753225789255022583623162441701935732603711545026850197372302346606879848800177504385828135364061678557349387488138918799117824516874669204542202901527680118580550969167637842098859754043320213594232734001632531319572757386071000052950546265173009335276197520016604657601476229286434993501237620365479171667863321139635277429695266722311393010611957573361279901289818416661244581797657682292845737905630278426423202455921969854049211651821695606246661023362704358230735341708228264366729249169629910766808077041314223516757988463342443687693413231416424808769327751525874623157435845329380530288320983746909904173441404714849158297418216032876913173859078445999830039314003930254745526729141954782794743513011321848306159109988703088679370241825935853689955810342947822290578755684619545570153606580829765982307625611688943340451956795638277822881777861057244991073084190216934533065780101820546633052394827139327410843036782416179279638927478241842774591016364203372412918124278561377856629474996672629949350106305048024930696486441731965475642356502651101076986950356437233749650759466214388370820889872652107919375892308853070128821878672910156126496617183716059808432047003806625996571266499060792862574247722303472260310839753308041439373475352888596392778389288484650154437440542569183176515081591034896765441696795354790628886184669972971835646732985444582066853748377153325955782345712146077886438746357634366225834742144105922751245438211152572778897173976180512146099034187488738454574152676518764070733023948611028006369688677472966973318429365961721754274161853649952430142465390483145746711165695335996070657097083073218167728874229672173711005980071950486217087677293646824454017597593425796694991084402981903334914397529070851794903061661033496963208276735066887865892889097829500177924939839852787038603269817450527233053402338677436141517302897480874179039475916747356814327531858051368858225008127571754260734040215584634901659191052978352277098848768713959010342724790150588333408521267646707331014317004506024731906889387828176715367698314885846744321747608495962065083561868837372150971105918957696356041654809086753936158957260152667612158649353051473515225688067801184926374666063627900787504356089883282207738585833469163156160762059179067068920198373741654277443861486824578063189339207222648527716484114861992810688756711994604166704650234165238876378047055820615347228179052403676809812033836132252548943960319194809289334401089339262853158447723627007332264683028823494101985993106640572711963402994489913861438140485716117378873333940586987171954529368689111100697342087233641653793028912107250061640845562425050733583752905750219974478955230184131045399922136262521411230619969831329035765864786684488386974975653623844664017741980781265311928393180196371696939538444105208466859570023970138572124446745811557319707171888015882252804477838860202217293144134361851368922712664549445534382005591992873547660244288487454948255212880744061237528549522414831037097857662162912272463993932257076428335162986631591776121069444259346979192441863438520789075094752598011302119769223877507035606135386127303475943851897872203440772697916188433585022801850971620477807686646091059987468287863559804023967769493850749915230275551969947260415081733248651727769968024888011726663764885227220023181910208084949165889227905437069677943829350162352606590388363684458557202532297814054152869512470428709528487961704231797578066749363572254340581062829356649074003667034366807720961796014805775883509412046585166371298370808687468619421738988358569408337124360463646761561195862695914068110450432650854655545225751148056069986748600967634632907302905566873500127570946429759631200089692653221281806907648892496190923105578585222605259468065234664658581125937056333426711552287358750171590862998020893390909379866646311065617444377881996963747668440270405673968740647191571230463137171083462070227738521526426354279635233939189082027518271273601587549475510971050435909738930314655938616730567882060722248350486984236994478294613285717471697904955130991005111482197450678273996024645237646782314802273748046837125914695079780298903191609123337480910823418897178726443669854130280335963283585713140022944625201291906839679477308536089414231983969177906313393124740143896583710562046640134184287695675822622730889929110812874561417090230457863804108388711965333582842408373424575610315904447120826288098548933414806132273100069525122893921091824843107451025110596471135646826657916345300577233165130194444049863693946029305758298902585792574341730054343568122779225956907751934864052437190818673123041650363282633011530407411057296414728491695756521985483511010243327181905240771213765368692656340176761711010839172087882066532121755754213764820555156656666839601047232072469120100583928426345764673634552296051401936251897143751670081916891785026800630730607721578778942351632316110800357925457891179181491903523711834958945091559047146056263242215299410930482709179179931728246319335395872361648709503472793672822445333121406180825851160606745816372327262339810753734381854790335239896077167009351750423888113937652296150740528923137239370956702281054491932633303587289318554588930634475928758595458531331660436196074187581967859910607392936572123387273380719469894545425375502817736371875270891399569530316157875220353604980526617509049072798283257554301225112959647728693671839547857110374769987091743484709191343897149755061913588907710823397882306198066142660145328982007478441822848523654583266917111146437079671338480666940165722091120945352315509496229352761678445150283169381179570999987991746795629714673158863871206425365759831898771740129681610057945264153479006472598081407783087132760318359864487031157975104608111778367890361710457231241831999846232952487736787035250203288217485604776336810011419997031495780637454183396805870775610813964917116341138794600696151282552497959367026824594806576578644984738562350329920898708954416375110571898561757905963819851107301020134058148807561800680414587007255364735911780427540643576612792055267234456917539471194821090827127118642486323120101019864587389233257557223684602134690894074668025646573007189310030101077223330888138737880189931876192876960443638933109944223095185105859967349762741690903135292121794301815662528263494280307282399736707142923807633854456718345931179289564555070051945006012528012626066892315193773224284773135906837010477314965037634592951368920033673228283597326971902949991162818135314019347199088225299951678530082350231775668442104591008448498438499352503053787556975144080751552681186441917422242000792600537284341975461535733922856677620428801401222757127279097255139472973493706813189713270356512035705536849597282567969728521699914284416337704221894724249488165135923499310463291964286442668397187893829150171866864625711513597326607106613707535659436717436517557068492549810119715216443113441481670436510062409318112364989154172658485257192210170219771674376612743151993655077846908146282364083295273041649523599742404038503988732731773192835172154375583016278143694133672254584349109121116617052128750057334193012337639398652795888992787804314307899586947485073963164938120003418885225351892552806285865832346824671479941163365895729999464882733938645776847846699316746439572406956331609192776170132179768462405715823669823786205685907877153224154920247264875862260228557185017943585447984755716552669486483834741763186435791198464080373100155220381034705182202505679472182509619655245873601178775467090559895167751889548734259267905589166060552044288438788241000401970009693733081572536061513742012487291606550434288071555100171109101896738751286222902951353279163688579760905687117860851335909110205725185275279798312348633965169773838547750743928786845984334189620508161943707661820919468028846370657982521929344770694275234499358955572713293150774986334986472600808787020913036817406073774961958607887507261453830046387641256558134836398505717187039067115892353362641733283316033309993399155198602301567146255339598628314452859903174983546925142887576725241103262689974794122822977898130345481971316967454410782835259182281511481502948859158030021053916856397026463114456538766098663001207141460578238569661583891590228243438810916707535545025260379408033005564558717739034101697043366067352840574362832443043606605900525922300562434061926334152502597886892440399451195298851618027288897586582951839166193144411555212587940196275808060553248213999870744849770958017005538690386016359702688131466561710093339469339137832648986803648788524233449705612741164130080481813622115067493893737001315611168328755629815151332165384422422314276256826835280343066002773675656653354929362703826363076654296222380129180285809320088328161546598069443389803959754118113914293763498254116281464179901530203146703395824885665346107736911743669323991130701270287215484567435138220267331024966575243378761793939809176516094231793643839018632142197154629798663921140333950884913186047396659666153463921419918641277582508532842180695467316290425125829831947705098305929736666071543418647510201477763834524945364753947200866684857391438487689235146855497715263799232266230974923610682698013178966722769425931342669905221895945606291968588879824675821110894679454203004151400994585556208760120091813545930832176300287702268654356598564146262745419956445256642247365376210391523353854029543933772073156546727797254013917885970942185558001928269211304053670224275191036931163385779974792858865530144244932676496868140493357768671189432400623586821802421767056676639928357617034267843659209954162375614084833029579548372577531813186281727667224378916660791614302698071252063181175765365639962872422299308867377646477535427988183701185984316993396520279736987061839131776333115019948956975228152965514517938817218714364896404323124677848936031034963531477221158176833491080254184204201092578106804419690412761126731879037153928103751398883897317338145827124656958585880821956545002573264386022206020246786677755818450928912081006850713187609503663165518916599019849328973155510112022579091833292278798515480624669951820706547959817585853851375289196055965398139088607903744", 10) );
#if LONG_TESTS
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(128)) == UArbBigInt::fromString("515139353944150908823939928660784858818076281944241321546618689404744263123230852252861682868822283013192285705847233416622657680250229305310921405481485272890960426205194001170511937880502897471825355080420369641575195295761876592209664705782459359916732056595025778259774980425006328882709734530180371920257925325382807152255886901648280906999845841112311058258511477990380171004712662549056707939811330753664300923440720769302683375542702957238396326475232131687415741314305691740345114616306632387096266401151683150397958979834773298945352942267166265954858381971441435944671142230176114897849319055231700096237059282189532537253919605224323687194424279922494412141871488957649275932147941547931474981995205272885011743001099122098820175523401191198797687346393343461313713162184619180931475754045912294252253906102034267610364922332074110628840424237071747217877137970973075954118730086155447494172831699228447928482650914033838248788942160022623763883162318197734153520796248376552817829237644848935811541829657461894740452343026566094348570041978021905936359515304096729463675057441123751839038106159445807113588002117972925838828673478720638924812125693560693573972847478445290750235185664693460767645505634233157695756619717954823520573314737923191623897144083290975972971705454288647202556433828081973814572152279416196813871861867530615949842588878715234924863004896394842054492284548956839022263753758675732989373703076307062741993461754885643808113691670047558355860078656879948792787840624512545287603836152267298890059101023634934397940449262972951803816407298483323608596681377972500449802552416682985618058196526236652674245360843823750726261364117944563398717264200540244028364179144684149112305155409037292303697917405706267995811620295643325376902500322895447874880833686387934843772025039333187223458989981672850741983834201345895305871327015041556485030404845309858367650934006082643866189770234387837251705543894367890736243439017347415475689530861377086520966627284528521087231388816824941192740031795742032275930233504802726946905844520955719645702603475070911700478544458913142756770641378715088611142946266872892729943999731719237775990705160569304567006779998080370839844073897294310518225629502362678704903764440516335113712551113344922746449443017786146614754603327674087445948033059271634622946847296098536371697262290121622681284940197715792304931449413285282895619516295812962563128913018972880781238414494543525690546952525660458125665762981309788919023150738025784210977410710611016299017557075069778783486514672384447488400387836155200500343532002754920581176612141097906195454740580600297990018570107688666501218510346229060151270641714708721737699616209162894908016314178846709778583515349741689507079956773882528053640072131048438814839468162677831938299350942229918142957442427844057541329422729492053062301494254611661009760833553456992986171962099149384598602847570591931580955529599354113092691446681779292480760992583264826912292742058567927864528506305653398790955801953520066287455848039906876788396478325470067006241598098821044582444997176886707178330701549024800018726551535044937127101147474007783865006406015550767476032765464659782113477509086480424457617403734879353251400737758865745508005089640076666089528481946445790529292328286551242407249041974937236503674701942487054887468197502905067724861364938691227480122972818697762465359471540832687774242122939787535475669008648199701141639113918654402826680667026758445643856118206672145124029063073858317226802717040605375139843165606368474968982910969637469900783220895689257631639048019830447787492587870966661429393107737012063934204952954849842042338461253866445132857650301070765627199461914200329993850529302762863082014824752814555391375578905461823191383144440157419814314761302239860397527222263785529130234342744482931217330886473258960561581764218193847463120559997931123751683447671229846152022460149376697014871192156878347296354877653415300100938793024914837039437466126798734665071414063826296225869183434695250276309764293900010236540919118006478859333808605235848280444486493425581621940076122430359452074842639534013832184070276956477067674940525539416000932395734928523336576130541504660940226665437758226330853863284150071050425594002359430757020719077378985227000631849127138391963937406669032853391575044135818892085920694208345512990049062747263199107636470036471743307092011816641063860247376769511184071501414884105977505552974207156553481295628797895857583176916136531762602663425948466732755469570475532644609693228624032236926568941913270720917289944240614186715102348230652286470019921502026099870773213485130484783413362751312516215896390348808935486082618731032017139635852249549643055935445040403113042670420032806327590272694398479161880908556919110314551189333316998205204763300108461485494007498409989381246502077918119773444064177157957808888576637656151883613049437819661266097316511255445992247755947414467397007718922561930372026863583832675586821488786463586101773779195614811628811427285962762626065615100589705047014094440725421785746487871423033571872972665207569450417317225331686479318290815375710436223067427270090059497086953994665907957094529311880048111897230812818519669799342695223438107868136382045440309840353149866539362282652976415668795716555215845041027173707001249460206727967706301031218260603110748842737070246750893809579748665143359510153740117113394879576376308418220130918402563648658395305415304428414826788848357587091468037614959363217125977938350949698753776247197883358645563326773587747473682992770621129546503278330724447920728178046013828531697402008365098651893036914826508889637763344753081664779483921617275439780763629290016176950460656066383289290830094314378924495934710814174772982738746595327493536919040570909927198977126034131075455677228874679968811073498990528910279765956554850139701996325114210324278077059689397993494001107283721749582275978516786583077497599550930372336895327822069670043252127576807110016517403626676511384090917023376558308638993761032976146714920214440783121796518441632733722058289472705102942624264524058107419808784715394981214691634576101793361407196012706491622504995689302841456197503725648275376917677359203919914940074700613426035386473166513082482215246706985401365869603230890391802223108704577963188769350592211279571994423663632930067526928726338812562742289245962056846245897133033307426611739863198716828174160462279000227179532343116141272447174706484463876472153709754360754471041173084060824308077624359458131554679654635960906561839503133732085568837986194151510064160333201030284203871509458457647300581828998684413938941071933449062532613350488007087274047552715142149526471420693769124187768191261566443724134729138488746270755188948431925664060836387440680569163531787862811765324412236231494288663955249610466730799765526727212525543750253647730997473678168438848094591492970695353125875943738730773315803917005391045547132886035488239908670545978434014514366512981546241959985942508069583937549229839666750208650079394997725388734090935065122461984896885335887453702062411901034021148901451961382482273987321094457134654263886897100055183665082564655641338924218152161985644546806601618825160410120588008049438140357767272031215271182668797216712293401547706566911184640685590948097763570195835295693577122776805859718592459234949228630841261774294919919173634465879091629854593300396589231630952849627695530476478427698270705029765071873032053015045087214655305915666030736040431846101237680403432569093339326524071160146595454608786633734780788959371493997186044432124880236356372761307444786960208401090309724961656085365936221164554107784355167410201422396414322786060152229716935289445878787275712624123502828438331820234424557954656305749285876724526112848788813376507142588325818551311809061692425595544812336233084205792373681447566705578667009362819994688122973767078877133905976954550317936113450951318986691299468865918091090104240886757655451584497187559891112207877896400675440034994980999829216508850072138307817474530742092589409610475547459753841263683214995621958594061845332489939417548747437865461617371916342642570721681295015163608334442842564308986226776877243410352006296044189698552893476373213190954859287371817705375078300631322116214869546743162989973614738224710919789322960543107375489379793229901523455245992227002886824470638479658053053637910612881569566438462256197864098162383683781318057987739328083006554018187973381675770005951648954863592539161988515770367807593153103169966523616342264324721071390039447169712506150626606806565891624048929837620878760216470159276183095125355061194085594673275629110344419675196779004547377986196509754907463510105249876111992632208774380742629576959661675238328998296894187663870026578369662829655968695405919612160348386507888607385859145940582485665209018419349696653404976814732295817013129094874407446857517532480199156441014352021957685535473260454608420281169848680492868319052600423593674463439727385484918844781914639117221918046830074101473126206612971244832158559100717347806744076931289386823150194588987176335375320944686005293796963321869395664253143381817725348310783890494440071365526211649243811517297001773322197398782465643081153564322215267712466669137415275026728510142285995772688367224125129707176863392670037679629007453677486605320686677166490842230998471858438011559019690344863221888760682763420237682446409843806951497256275327391572383631904565834000079022538260827557622363328084329603454096934279228748075895976472287917975050066245492034686327783644787343947595672267409738104154976602230922112903517639259401247822907424334774379699979183085875035839617153604098569578533680235272009449624937121483489287459205455098615312589974398688036655395376269831003568217573312890004852157603471052784031882161905228778973356129897390119825368632238578341859644396874939693261487168065712699843209356299688488329170745882129474778187009214736699587441909415522530314714226632888627976084906661537344632766141146277090838157622141898761321595201642807200096773304853154872550931307032782345996335962993054242932896025777908582076915677538065539662098798376918317242372098123554537404019218296259050883487998043169547823122933682188428165308336193439487287888695792598972232622652028544486084271300082874380272217501140121563566565959856201249253156638220584618140450936105410346983878660775987759496520672316307672747602128270956237669782061699262548958273286046901904891290317629641530713956452423798148143372761153257405369671510325432105827844414163207184982520255897319829686790930978501515253102252098197660605732923188094895437945124544232450993090920507642544322910120067218043618477300333775097639174171338211903312698955268096", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(129)) == UArbBigInt::fromString("635951712175934490150824185770557571956499124391435903351306520129803432749415071858173572993650192976662381152139491894432464992251550065778065117926925251140745624653033747620604220757386635973678790697830172250260651277822446387405132890741967630868081316436300958804643740280381343702180343974253918391076599558967264377567863857311718687400923821351777816477169330708322161422651998554455592281117126528634282378534690182390861967810886181638335341644287803090852177417605421750676639136865563407771155228723755682630688502102467134250931914716022518260776672607703037785368410772833566466846316065214506835455679539063828486284987896130379491345966426524883740761398674607420520820646669075369987705527054267508352954457406780704139497338248950986845700309575504962816789898521135301309936399476215708706034653471270145203039499555576208520826218073583506408119264754409275723726577554009156622915409249481688243394633337532773541766566887917306636476949689041314586977752725937260913640034815374618019765584285784532150076939515891950449628097656653075571125268794687890556997557466623671610485224442791285032609811640438111224243112764277819454459182821995289749841846730323153017902147340664105140041900801028671898497076000708236319177721563683174195270629146698944309404414311213604656428156581182689209432599491156588244416660037280747822809116639374879327718182034341735620637572243497308573780121307330095472348929235634181329614638132359217803803848350657842932059073886311079942767785370421543330369082544859351821652970340679994899440319433835222988165851239629639553002566053552470286535458081651254403348758313989685183386068053522342307614568985478973097870104343316751303448799072671231774598225898884967610119068263080908317230991550158645642696810239411442955140186814247189342818906108317412010831280768219501170837342661787523986757583124296033271678619682334493887929791678767831717937663494396008963148937149280339926671033391987621746551576671550177191311380827239582001556636832834074652790513515794301794698992614172314698759222504813478618498080892483042125001150345393637686359016042881242153727341290768735215258057939558067152572788454927254170106310640824288346513298187823618307804258425480024177810845670774570745075471921434316904997881806806888308518636211066594513666359665008069645425389163580657309975307854447318135362118256854511652266043704728441838575035656677146523059177012355755631162020983478145560120535274688384006958206591142653126630274115356867472753367807234984669196068271000332921679684488955084747052156750595307664100713138437121855779785320718814449868963850876046531664715500634182390568024826291164783827389243386118987740334459322546588605492380207219016249711270945509613826970882797187276445764255249579552031214736256156584871766681688564699077908212257726277023233964220159589447916390156598544121787620014108657095806051144539616841448842484647273184030561756930525426215966000744481955367834573629060712153967706329591815408837801890701219702074316047057742000858117590615667425941864207300556622439801737494718239345703927984834742847877250712098193830423795875100455947421619745421792454347806281481726323238743497990455933700933472007015837308149398778641844884465461518258546868255439230529782047923419617082396484454930812936708876572625121322322188682005474076617057817136688448217320340998022364898646394068580057389889390594151488555429590081042977724834263376520723237138842228044548442750953168146168836578422637883664459230638194469270897961718938705845647707143945162691270737346955580660480968046777133638393782455601119764019014021420622439326184804990806633824866883796513677804606300627503370270001723899423935227984966927064438839393165165117959412139886938592617180706512993556378392469155005267182057188514143571803616277973583775282808131423817488483937019494597993456425818281092669117672184916823564623256863896646277099926298104283538320862952703310567675325639134115735105462985066734641093533920112483443082698128446794279306069318502498757011158444731279765691354570252482079566702314917350380206843067817007784250079858012290128511548958598036273929149298060277859532453436976920937283980764274449715611324461452341046616471544348095076856937820646686993681680927854598508022734647863861036253557147418040424556619906141267226144669813292978528221761953316246254451897938574166464145334513113651580219760450378182868141322110945172832535878961706667912317265455276965215042472613480332742020067674337989327268087713647623162565748592424171180811243625917426130068076335549428916619431220672623521714677093130998789380437619730438474048216241438231375206931807976075866786197079241948092745221692609268965691393672645412491078439792722937907821035544661472570501223509134545927738053339080406547908910681678480574104615562300831289921982447509521718971349310889082145753739206168451726991900401063694240037794250823006040182252295025462672368402564778917576618192756024789347586886388574413238742065954767593771087757225101201068865151334133728092348843800766914897769688979852954391523404942797889635585934278855098986377771673443767953150896576947638051054131373034198888315613582572229064994615151020543592774158472746238922697170381210033555792388485616777464151377399699219298821742362714730864187537158144916321086445926054386999891934874002535950930713155005200158708486633318905379964939470239321288390262771680664066877080085238002502428536266551512424962213778558381526714995127644996733955502085329995496754955499615105570763938636812464381117250282665468408761785726961291745514467106054703031880476639466311538429393382057719334302693818187072464198917394064836258870194670378233382514839598372867031936585183746601070502773730660318369119191471638522814106793754989882864416198497537644564906596058983789905004818258654236903251608205496084143460065731562950073681865320504961732145755726972465494897734191226293129920888520484128714993539765132646362624601616043867869397610739751891391542509129750370945609146372001804470029886388563122305622062207670375533506854596264037610790299134714685981136363298091722177790189738325658601246596418703762731869536800196954503090841082602460558339279970235975488688328830173821172546877347827471137858042545849909991370879014187061780027951031120438063704385492953660759466098775379543444371407446514056262563278922264362733619845291263744930876311726831657610001357483964292307379998961411608837902184371710167211996436790099976143208481679248704921448544759530640701869589445971140170762334271452506537431976367821445323563717283464443723596403579179252718992216575999220572423262862258890052287842899898783805694045374039459470662175588258525976657348253891985269388180758322731757777603489923402389539364326658723840742828697879979067799569623716039457094187557403203251050110441685558286141821748449922848848021777529596178644672157566315179732473256280380775989917991395409303489824836628488735451297528048925462196445393772471281368387709756429696310182673849411835564178464614552045212043997097228358858490533311683725873768165532243875909382786821067213310753917478070064840974243157482235456895748490031518728722503320786407370980168873412720646608186267677113762362989874552483020897572924899331788894489640349862178724771906903595189830000985176080518999902998025929428024075713902954898368574212544587323889832178427369792360312419190346607716995350901794851566055634157025674075251351135494729163873711195548630205767236309675334448461940815640654738310349008662396718625688974642997976139520647347402837216604930182365204168969254195211870321567688947881160073767221370674446839640345800743055702246011573369654597534691637419996903826925046213156431046401285016363695312318754008921083345672806189558819438562913745747826280612755338651649661087775354217420452527916084613823412855236791585422937183132505779178540139167148222149292744956550996506653547852946423076005364990212696344180860190123619035561136312092637962731609708385745162617544072583186134057504560182252614082187429818175295073690581122414987895218132880557755377126988313090698016459977021816215671798781336849154797762195752079849025720700514602602883224747998658984310899081087704210372671105077455767378319084937324942477470706452467629274257801213856159641753071475783454072894282393908489198001215103685894695343973460256894657581581543104345259839254401888078098387418530405971435275616135817492134407506213706718325250896182587835927430745784652918212292667847734576184535693891175406268698493746892989761424896126199663696232948821464368110151971053271970705743018135635422553080816491872659964509648007440462675358199613156485724726626369684981743152158340904359816952483978122628556479001318397376647044610891372486071094210712092160821091931139625429307421882104667106792028879397850437227775568393499653053684543458993936933931936145540695887047982038868261337378321792191047646356766599200861497831218257995694076732717090742166183693981003378048329198317047581616186710275954254078537187506920956649723272024390621939368409639325793792302681271105808931176145118370639969229882407643218515626298526622707532954362513622692844474330068059737920950348944978648708363138104922790895455092759701490742248795330491459863297813416821190942796427605591055361267481802903449616038383400686139558767638838201658345499365557314419652063391541202823795480251027897966561100985259696106642720997811016595467714785558492756381911405225030326045749277363179249770252690734501140721756729146227779785313653610909180133018353321211830759978729811475553653972690727727405418122259020240296853922684939323453883349128410377904191152191923638646358244097311310569048859899894064711086545832295262949695845351578826089632406433686249959550149246033556388820789421507831685678901124342711487483621862443388822576834907705363309096851141214462886310760536389724105878221023509838789605682252432542416463179047207154138913300903230360631351344374604886249354822435557266850551808072764698742844644782443898398692455490255193019488951027064140297215725266084853696729774963954319247565241792491914821282255869273578010722427642689928288989613282764070628833888877973925512008230015088584593400726060002348340372937650106023881121160722846956724410611565369451515549352243172799370617821725177682855466766560014846451607544237893131780843737547250277897954139617426153935834497307097496642230164748551241229078540206541048578326671223876269709870806543261690293608670950928963109734732647103741541592391850833068183576911094927257130958888384393683551406975071847841111218765978202965774831693222219990101788297502227365400235670060486983310751954520897343304027294143488536490701143472240328174366190808409900360185255254001770878964152130519545893328713500311675174190536976174520563698932257001054346772127610132144062464", 10) );

	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt::fromUint64(255)) == UArbBigInt::fromString("214956234629275359469858114419303291428061846295212479209350330017780956257616622194987644832845617277418815093584190980303674834651770616566603884423631601877854582947721319528131012247424715710042206482981218808826396131615002227835603306889174006752380387018236384155350465853462305846399430389965079962928204394520264971719521451863812793820752969630914075631351605476174140797723155819123204182092746873452000727899227902792037055650598489787964189917404186372170072814833796767786105203596816812374944666170004158731035947629612389072846096793908546537390946213429294741739980081799198606047321708659527526240067417685856731692125461464141627155469846145901534658443581342359922631013859838661320524561089696616791526973177497694871314078078792006691557022626199720153819321059884068830278315754524385316556940619511137625174169350866953258279328029061202396801138999943936057490150745578458274114692422425808780147647010052133731031586487601802656724918789950192014250136207449259287891385338722617577216291486438103565493255128328738181082710310835013068986918310869348854838380163763919992255051353894610720183255453368070375307491017734091736510386445564157408323487240168073814021063399725894668636356537496696166315079816781954346915784389327694871597744250802800244727386630823136763739962667371155384246534925112791828365339110610328960059735027716129725075948767520543690003858063046994171041198938802557533937607305393322638168824086869224831795196175469433482145846530132077293471712106427852830085186750352758261410836692731485549224334965966410555874211932496024101642311575794514971383840109952439197050537207172326904708592769868930455974128722661634932370686330128991774427341432626671839648500131321254752713067841735393495852926971615360319869594374710134793760025027307372095925865793914659706881664461219918593199709986361853298416164584892899766369217535713924203877910020466972554389562949849112429855177457958319918070966935645542665150240889185960800568068886958526683212123162282871041901504168477459938880776794264131925957907599358214740744333932833117519597387724945268364300756692027975319179301171483764078305219709093254378639483954637883680861983296741418966437885163930575932853852477690783219341735936312631771084364411607181687846143544209531056515341238659385518085256856266842559467285747639636205663344113674482312227763656004238313278387357056992223757058042585463892265534001492889140492160148807823058404934014945735335225402904740109991360774890936750237817968545869466499357949015724281592848140793342636296060838631575497397465865467722204833596437429314813237255285856442085325255392452247569414139338062153301933599554623777425780326451360666533237077382195982686980292194155366481051548819802811840133411256357285986194429360673027933702921461016989914919719831995989045455586735341988475028350972690950275096782101595182848713492069640650816678226193200200237039677788768366976001630385968152532929611093313340253175416292894070199100095731879849000912550108930180826914100735457807040406322498739763729602463626040152555099853228553193797319627360458073110077935137714941283534898890890914943261682764758491933615397135592076505610901260524069227277874407846525626209769531618513439712679441591081761254173267681822372817952493743871037800785405729396669864274222505001989323201715725663798591983372039813046240909189650244718240969465760388851400099582445628090414029023139283474550380476029055787200218429401662366746448830306620058679575271514492756421205862791326432859729224277466081781015082213607548734562283790330032433391561345546735555761765889316414642319889313123717803001490314319028041184411068551566326773932829001630058814156891019699309319933785863224981019392850707760949868670893178387523916845862418329015962313298582655823654199164758194491210182295055761873901774659301288500108591911212555106546590311888536085905191654540432338579911696394595173335450266627750419990979285234745504499834285237653389185787464461511809197517809694440031833179522133432060223235185203507398435972545789322153069839158752972338451142798604264946800817526187452551853690027509893633034147095976248390278084442019702639892056703811808094219555561175474652826375922034561040452821169632441871002390887410957670046181882236117029689168411960371157704605048349168287137889106420081710339449819893984305593729403577699204881381681726180662420924495972673336976537161533019065896107665907883041263514152551582491959869842841531237452281566810466428896423948073511204182750301603425381576026343022138505764102994781344988202128618131455733025628316128764313132289709772482642998011863742319103716818822174278080357120365953434415636560546311752130398639748199164019314713933631459980467432975496675792478032606335113580057556161234141697690754135688936535644296427158463156879854549312050883966166013724044996574297824649233898050366235507173693397461996456276333471108432503029054421310236957197141966345446159416292739065866688438240925324400867540808324464998213236946452195791494231354692646121796454479750857976375916267099387506606909264584748325934627047123226598147350224695765669170197315865048594579101846125237373970239971682508000192281192410353327475697267143606500982948587659796424484052565940764545756649562131228051451289983224953873462390307419133147974109244071752040683564751586679456158902891841772082071049523370808248137924977432943982523075044789701058972164218505287494175190058808745871206239766032597232695861308510941896396244989239379898984652637385567697996955853660929696954222858861943999148145304416983076414758686027002109750066346074251963697444279981185480843694670295656365285191601043929738131986562081608501663768372847296256031027819419858355784210548364929771986036784817012993468670925326489408831674030908892666678674323798065685645517955503714555183489121981881252144855396928111370822345045809723963259957069707557046538363373199969068399717667706406951710359902895814814276118640679604292230189170063963621506632352351865813177222469261964347063327527616527271926993924170837129961340455767405802350204307858599405119595055004803993597504971202241956243179469716789622874059272402779474199465005790636724517841506191425663230536703334758332767244660268355177345006842624045135899355798510468874333797457875509353069881428526364743319637608056307486506631910503359789585521360864833428219486492027373763764869694462139649172718274843941447589766426924250757784838914778177839094969030468185715892381125789504452607258532993255387446662834670942277986317664408936765815162507525608978124654992029754413199067034335274951591899189889914834524959120931046736839034833829532734150940647116599755477302332116709513267721864895181194666850164059832118985505685629995206099053616336871973868367754836695686293554113013039223949484700451431806182980383629116020180316852210920257345173253882307773479074145776784152217254854142384238802340096569824256949356782094271112842674957897577978204506691827107327891994327486006878201185494372310834258595799586441759232199186736744884237255745176625126888750351340347228311163492502434561808959749366304222869412649090783088833849761979319411746651592351904906995533663834556994409322417822502868537624054897225554769620970451746268805641264342744765929934075544988102992778108321926832374064694614538886480635790298662720849435871792784149178807651207876785158447536668576586644975778173980355715455866677863024256592836524322614865126918345917915371843634274774862926988728435865174334594764725885732517955608920958815369161784062692164864416613596760374140446279122660734819213283507980248056012858040472930241419999211285050352290922210836774022194742188202957335613420996139744602562922370825711165348616203253347329772344726185788508807742852141068512093041831772895638802701707666038123405910766638688552150852193188689165798694878727885084654545690982352772796736087448948855958231341998925297335248865223732153625761515402093497897001834822101336219945485865219073745561400173286109808705247035328065149841610899221577371439753111174580650998877071693509084714602069239977526662329052697957640501764103144283591320068460708408972296351899832202711890222716085944720450210394914331687497868714414121305446209364846900409824441347186125840115083078464707876599516309365326880759773288163877583788844669885425231421384674227180941874521504690828973314367120412528814515440290245070475491185794043666220567466676028749460092107909605746360799560452538903998688850561256026720836716365900285236513986631793526411351584704625375141675741397676799745605037481935253375037376421841605588801021285974435261808503743274203883885676785101011773838368241206081625503000133285595872965446502028073621895599631634915511959999272149841563872241042483601367025041294068204599970338774358426278995263464436595662255738347847942561585133860677463583071414059332491682663873809408757605882702685330759250891543806208878264628591329793561721304562310995202297244673555135081853850428158921893465913503204233740057012922087629577888342045981102135621406375364647641683066593068404613415173632334424588035777352681142716876343162635528255908039643650358984961643923838248029390354041061712151657022977073683499173425663605937265477261594742112889032545935314053130915322649921337903249686104617515792696129632935953684178985544116723796003687103372278174406702949709761539025965519701128533691348806405492373284402008292617569767984067821117752712318479346478578369308534479040817891001564809416096193844811389468138895971510853821833374553861929868857564930818908088899761247423374895722735281860496308277212760021642756697232685481442971816284087792112352450010895520248342460077703215537820455549105585541707130420720571281271174024680603382666612289304253518630542881803247528361700762797962176758729580493549761237732643543395816000782677695216471059092789762502836594209114138284647188944448661612701300624208034316812011511533453458479032210710213776690661761372330264616385364461997141335736548917564751259352286483357045809398673863239092200003674857299516031091522259150985898744810346035933394902716335719029343089866838434482519738824679327950842957669417801814455150314440720228495381890678545426342157702624704377549139074444435996120115292608897063035729351226839236652879229634040282994119303222569877426751766844620104351282055030551354781516277075291179622363814594004417937101494058478498915679272369946944203140004145215781460085375331179264728344096689836148426498391799227413562489368858598776053659333187486047267365757474002689276772352977627501753551995708890160554340967316260066642609593589763142113529580543980247913894600626543696458695292526294105153045050303623105804481431297731628282176282237049458149411839289429452012838277323602420646664372080379376868288906132118099169486994195117552229375567882233547619629075585647810749601206770056311754354457729536887488088770193691839705094779086783417983307093422576421194114566467525661823904942325710117201532950711966538233749782622144403701692671417152651477074264611490960121638237575327558425384543467100439804658796839929405389509990777103131797177232599008105418206890716722765676481722002837522419068669861057850108528995825357059535790284042455485473694103373872069914148375901125314562464066506933727338200789540743847735604554986534740574462161173031426590068620311925180775231973137170304552675541226547786215924646160764610687158949665716838644847361315843828753715459348191259134144123735060681687746387367041199400232449081631966393849007020080324897376704126399137891753454032349732424173276495555505007369396060013717556653361984925456276503614697259726116543478786586622668149685869571638491679063776793037708030859190242146049839431386270041419619775809040306943945414793591257572546476400966543840312943441043132075220852418102922090079019732433805703874300496662840995435299660672669488917983449589236308854021924598671276547316309346617828589733713357717500863634223068824599587343677003904826480210494020155005824840507490269927630684631492301293646662024770568275658118227558246754634746306386804303061939485160219784011099845851925236849247527281487254588880897872288004409686772846358335964399706625488686369989294384428426040056488869575719255412775146777435879056993425608119726077223336004905315019794770082214608126389611084074183787304643421429169801299213446631044991514870192400675718055088947143224877443107621849921449012862789349978466432608027584450845499684021327639080984023076840295580448061871235393251230976236892232258316712076003765266682225471670909453486820370110386992014135190700977361412386081479951643032162074787316692708060669344433810234238258638265838397982377951661159578311040215795516441562476412094127637256741154234311103153224377643328207957665382071811738454199286183550747270084192645691333386016352574289170286389065973092858142274365418951321025470011737541357600378729747617947739461882036384228203742836330933355924358153091217042232936518882748070217195125758312237012270964136802350013028726188611902502434240294229586522860863206336296335968870889386816331389464692026544471381507780099839865126047542857177018847571687924644640174269325929177206839133843170903017363038755911623166238569360053129093735698573212984264454452143134030159622511940510152309757463787441829040755051220675079732718771695098185233300724675184311069673321234887256745018942930207532919547850672601605563018100789274398197363997729969788070291134880352042549540294040961437867783868001005075764926775434989542695264005161901363525350878234749274717745665527654293163621787045842831063459569829695818711611709266373870569062993057059850729406865024162287132503988584686803776397249774852550221238155071653602285309103854520921926385805814952827886966839378230014588226670040497107958928965347514569286530135067054659002222583425476016869665426585897188990682760779979838277436735607034618924947378906447370746482189924114367613938877274173622780210789825260237961440993329486868300567160446473289207944050633564426190131244913238613496742746908995096330408525048466909673338233203715805433104461789043458226535225557917561898684364394327192773546328664670118529139885453190690229575266496189120716720590514904486404856405415895099547749326859871885293080873795668043450804398465392354708073567620291208828800277773623264530171899375076116139916407758213583572777463621352051403873677517614411518702757693723433591507880799556459854306740466201947790017791898649115320881559349050411123639544504654010340395134888583367467015158768310249934335824381083458142463689669026983695856567359190056980550699745002039061678068517038816189562617030804990831254368567588228175913277423494602628535920271499889913641740658868959529064882449849441309210410213474638428325890304970527014113743075315049621126687082889036115426869790726465245973859989749803707740883323488330561329163839640163401367120831382632398135883171681937870146808403444768198361875503586640827442800378525757109940092054327896171637109600492841706046717451110873951823187176546222136995942044542841904626034565532377801140326549007495163794445290634753570751010429817302850078122198939474535948146396247741278955277238129344214712831660379232871921818843095519783911749306811818042181704603183626741459524065766424610192470072797082675039263497928592788666000197732202002320706594432577696587844008288243367607731695606134430391755240050798595897252103795736615456566445038145956119217296526226023258466409818028398755113215961216559513099327755841766945720003321580773546630758888086439598981402612244732669103137890616351332321120438289216007952610581493446341979222282413343437554284422922504428043093012392391694967002518169522741874508323248403343206947426819501947953038289928709829304040966452248907228794721624995547018274189492524002191660351158129493697848050426915914287604288489747330765509255700870280014546236965663815450940485619969579058451409981174963586593519771748545904927318571788082781674041869233315881505124994557172343082216047127241542494048041531831484091643871656648432119538710285316156340987667705850074896714839722179673164380024017683521645464833352282636924760250537412219008012489286794538349212942571369660980859241718493260276919554830027763008144927367747355254417584288959878482927900591977132325169489308812878213629590392115177383749502543690685625857821579747696827645487382445164589210762229815873708432410525294436666231293354396868567405388567176390939619784286060823832925294818871532063529299095200481501944527837420378473678195729259322106338799366531094099342190813671080332380248141097378462752339514289316196127067474123250941321068991756664810002500164606089772264854561054702724018592572530404155891145122132630529305309612542131677383362536856799694527951246533649719940156381744334420483575405775728358028336345991888120321932207089294808528629694411673575162770394155842234057214730201223775215149396086175973780343239097948696915425026340653113423749760314276726964855972300427117923621715882925965334862609801505375488405828570350280970056733553602936874739478856863284426704578035959808962855471555561253329268621649599076297857683127760897090187686275964001685831480715215329464972680942180859566972330395523756815158180812430141393406911126758434198245179751953409316691324622032121775335598007142913716948741177606585061513337818757269052577888606259413506528628968041543094266782523751055704010990018703624125769900923613489983518015841925063788149804547410808213174852831128932649288796365907412849856569180689513126891008996663087298206507975460848564432645934229941913585494062757999751892402786908258840502542736916595491082113105439471125474176819540651690455741701255074650604089768296251501651913877171876530210499189835311495831341035676173347732558087299626730782313042015263983950519834930453184935691586006707302661191560424368249439428788656855606356285642625998464712626190009118327753507486521002446267241829732216170705264855617729054724054940626773264992804618832223479637991836412145234328031452804441152277934683115126242380707061585843781514186407157474140099267258432440463267705264327789728776695512138563664474014473657779243671710170039936938965062587359320115738424439376962977044117608809534042912624511956212095244972768294930777328808780376230057510308055242778082674461581736199509643321794913377885426735077545735632393076653720449508481540484622977553571423720459984672209481441005014844780847333832504975585241379573687581809855892612677611065532498080650031898415911248518087319267744848882979386006007314575994527518608510549188970716029141592432680426484375244831599128280363452441854906619901560881750983198308734318555109259593286947521669182092786759107710683396432617687298505676555943803968805924393167762990936024886894550523661009399983435530701526071347914939367785135788311970132829151276059858027298928058534962764656084239843610328291197437249155698693476593133853420666400560391783922102612003012658153665152165585873847518278187069980331715948607614877640602845217663793611486267791973840356231140698172743688777677588218198584159329604528036612934691891227116260703541091313500442356672971350223341301685275874662349656048918747751690624694338196819191999364051067812746990819788007641069902236329731579438142418093206435754429057601888243357822934427648991542712890149272337835809399673278297375918426642108576359105018580111368342577909866523305342094154323748393080345144560464484578609105002693120399948492053938526242861648325821311881396260382010147156625339271581107236079481497738908417474505745616471719960575472933706299104919143064057919384859557964551311082092079035548651504838642253193338397862725330289015272392029233631893705355169353634165646343101346622185976939970481378187003148054468958789237643305454002524825279829790175322671950395967869247717550647913644982497306527396492301185912280334670270942205315270922110792050656532766869597677937841200723291964522872919064951047427733248935873036626979819253269864467410079100450094943668362311978277966259154578838647435839994896479012789822840330949317990924465385543491811874529264459146078474925325815268928067453946901458793983937389925673898620545897070373600596647593613791521423733368163632697671068603487288492546143987962758944217184877194227308749202161291372602739274877179763581737208271264463541712355144011358800516338571551563463034992684118572888968201419476122450545967868714483069439921032209930168633454963882825202623125463433524956821228583788003426773683322485379531765501203795115194787901771619702449602692875448807326694927828077590555342860979682035027323162505864626450078546528565758201607957964028106073189699067507981265043159756717957091876352284860983706962784749698189951215051479360566341878294181141406049439865687911692743434043734238382238507423074220530112378090993183544358810698940973756385607908539995155562550653704420023880653118544934216658094074145726355355620096410885097596248622554906397360174134744154210320027007631284446557719250717929992670966267219518602222749252198335668131671922592985500119067382449720650634487607868497971928768587283832998678047346208805703850877090626011714835968411962280733740785765785301224242002060730222692181119492086487142158547958588802657736555462283735055048286380723915442143079070643161863192443730238129254358920798614134189005102807494290161469581042150788234588812082151424", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt::fromUint64(256)) == UArbBigInt::fromString("265368553981997186503273750155437465531427824103820412169367623544572622778171789484276232954992492801170720905641559966127766846804045259686102963942389012434065464124313583917131886217542583635505270382162990568870063572808229584549947354836407516214703840777499237046584233562662703565109993954847866695718090274383616026514860976289258390846183001661356392081428312402302504644425489012545188764331347283780600737252383248780109160927863590789325077874142900551727105052959129489353313179788020585287050387427564367002633365040068000561435549700661602606985280615550777292545469473439183611548085218784772335195699710834419636173775754696307095892009440406275721017395396274623492851685400484458197106790682133029933611120831942064625757848764856669941760235662133914944688599128453017617699732402947987260444551971843529845306905107934348764686190349672735455779336062067225792677173453087153504880778779866313388264640327154821529715898512544899156525835467099734037962868163478617356967595372126026133732952974532734644848369892451294991718595830241056094222624934589166525839483191272001642423565631599839367407391798821104636491617485776434696092663339501272188484542155207832307392042145580094408250366112847908511972758029581947666104740070225819269053875826718807076866190260248019125425370235759292773870853512674679036055641353328535538247061148711686387882117110660881707622046096919145445274305794715273809733408620853815725079912952729372985843365728110831257842089420903100376544989995681091362191337085068378112117486231724445082971131915866743540780613386178320503371978242570623199194329940907080081680315768093032762142754991343912836588176898053095825330406715777385403937325517169338199926103367683795748137257743056975846249896143317454098593758395595714449837311563753550707205780397603959538611478329040089784658111830604481073335658950218515566444438584898555741974702094162694371687751380955647781509514992616606861296934237628275676790567344138590432159055538625730843526560436757377170341308302012058633093652493501984253329796197801953097978366268434605280775284851269150374035500668694757163766084552160722093048150019689140267802856775028133707315735750372273307933048057826219691986533332716286206983737434967669985356586299215107546357864187205688439775458133642157802253931187354078240152057512677220361384163785072617302245428829545583461937809848200746333538595035354351077744490458722564188097470594664208400743337829708777456351971003595085404950317690710431986990967946502132336167730158117720448270360025452270792035176950844088438054832910761280461164570305864504365938101673706811782847625802942630958488735883435452665237855844360155360197627386934416202592341329434305566570339698795620591332409175307625433748490999093210294236853373420107179531950786665044487257760767392278012246105371628125209216779259130920670333100846533475376690957436814231661492605900989082167898057978344025206053678561813156196234844869484321547301492594819307774878326066005222314524745960090511250197124173125766822193207610419724957347861182344526339071430326241266316689990851724676099345138254632333752973796575375392996650022502226449181548762382451354295874149161512289242904161218836527621510339485197058619818779794909555249412931265566884739065544626374012847640980504034125714378516478087701677191621705667918118561417202254573467039101811443231804309582717490406201129533519460270129797871222558845129997533489114821909269528841124381961816948624077847590156483782125540817791695256310908073122048419748556195900951597217138348002626009481704353416396401944258953100412289587312868876374055994484696488575479835774312899429269017524679249384621609710455567769696336489068626297193380418682189286310282812099921011443963533661257434685482400022421222773542724731965879401783741935246925157801247165622241746510315329637090153907143771877504290777318466574591995711081465124372137312702760254855471544229738047951262229107109879268532805127285614231667008523813077912374236533791471639286268628539131608114482333726474047060934290613294033688657497364030663244934641618398182868907636032955366708356611810664914053598720894170505466453423461569662712288097404939499575344411370631696263102943958911976767447664561602219710067584120637841215844905034013718805989922731870907208961017928547386562829311856481493457384889896639068950885729384594094605507571056562258717548298469470805776418268661733621882976017024955739888756909967517592569235501117219857800861280266682384977527628890539766401910805589791719612387510601306251039264448408871756323294348434663609107878148077162440087568040892427231495501887340399432343237110122185423698592057618210558981393912276053968891445608207642904613863931107111960451909088076228489930422053282230124133850765596157885725837509475441851064238740493031387184278736630984124701065286153815969652170167121633929451176376439410575841631142007176797603862647904668193101426666157134275629089674777171343317170496214049795733918715837190909548563590363714082643127986613064146706379146083984514253669786410872800828689586345280549426454028557875653511201666322453340805129829085001832580326165342159816463893888899515460714642454397533796133141853090766434463095031601816400644378797041272825135485466792859634361634476260292054508564879872116944417961043116340499237145137014521961740020149838116753538490504699152190752110163474105593340999351618762022075666852679003529014015280272547015179389230232656818462393198154811063247384784638193362922451377055188655125823185996719534391090110768236136625039579052250048967207944792520128122631916068205178221411973189522604666562122679829392202460061598687467138554451292409310906678258515836617768065639117397152098014149624164091410706816409473235914483119484814444136215034104703130956779422314930681440610254479723368249957601438481919111444974326456562059730909025889662513589541384405289677863796680621041935225142941612950834031222724983065651319429430201453796580392930570786535880772823210952242239408201269644423859580145114074213103923004688372937745109913874267917802180815076673354325330397694493241459512726228486560192345362832648984320603752593728901144327718186438724461606636845701486535628385406150232122296551650061453319896431955843119953030512529207389445688259512238490046232918645767202755670842939813491435196898842194286320938301887882381597645124951986353581123338864625181896533484186428516726824723326352907782818527951924625936023505569084226866800794721058778029503166333499193389121579924343083348470952122391696895221681567504761192183587279254816804093589082073909683496234933147551019264239096436438312181424738932686093445121965937519478178303704259493665857423767383414282918555829971144806273632733082387406327926595109830156248222410687943949358097857781353114125891981581829715914797805092240148480744875944934257316583440516161056656185088156446166792655784026431136774302778011131551738704366091987591033466112091733115517302021781698513742305063242370994031984139100409317445790305743754374358303307469951196566599560331494813452014214855700288134086462746727578755158138555954730593025867420620596055710643584974614252982477123819374145488037046422334524323940860590591871160275204162203231757340588696948704008996584626263717266272014711265938853076046013225240863228557063282488027961950847248693224516721373303056169624105707025585283478494174242875045587590947315795470060315662028932410104520075915885082326675139577938158044549484373924428535267636234622851599238710166923062591434007083915251020589810681482093219755082724718003255444753922934997545204988036088317229636814913982319442652391299429696217376945209668302338873149576789649284676079611250398735314195110471059750775313696408840274752496069788838095613137940023920298804351024221912280962791014583343572585765781809420575083591571742173550398722117474727893780833016563466766656368148372569866455803716142922411948749365223637189798079634647563195727497016984919852977428799381177416065415100643752563235956748857476262830848826600404627569699861850190066153336976391151281238519277157770592089271607129110280226312084603459521448716005069792758161664039017693259340469998541505225372830122351181691319480775019280274599269616542023962222210692234934765710205387062824467673837698319072908737076682835918814627743927160038350471806068129853733851319286633869861413869211385503686695701071592452766508896182853775150749878791633359563445265762587351354580950818136844702719433855498080289526755077359818182458282555763303426691439169289697867433149078032841042157771610982301102195135435685456332403871964868154397544216859774427050342225407655290117301633794800024418753496805398994144227641290055648971941868918087407828535762049562937165072434416952843924410669840382567528833972783462187594312508510239388929314182577525939443708182302577389756421623769765411627015511170954689667180860348400263815920236279097031281880425081647440524198954134368317452706880483626711816425410252501616157276610302221370092109367804754480657028193919003043497607087963245342537397737782241220256123729667721370405084266004933948162417461748852381027470211364931748376500567103823627921489793885601409081213840806017382772675063150977028461258319365427474319747722866680477405669719681900807465423393387112300848457705788319850287608018580648683336714051616379612168642363717802341110696341420881625260664002931380756341367629387875319474067674362243036716974291195923839942287182690733729913468550548276797695577134565597206481892895471365835509390275564965555109175237414910890045213864368028330002664201158121881539854612633762352366958375541003766268235010402438611992457586737842551452656921394814540351866192144158557542227307763409969205822553049445625917332977805470038339082061784296892237610531142359566491486751479096206152262252133748336836126630123130705702961055783551726304411929848389456230059330909941709579093995534510886469017469585079631498965381986537369630493515624763082208233906722334668911270945692105434519881995361409519430238141716607383748572385467635784227012368708905559221661030588665800532112570836661596028968569176574276402490328744217598261388903436169411198556688613909154457920671611690474683245419507789207941280179469030529092152054637779043376777985113488138620518936447179248560151965250755827283085648549827206428877626782704320769699189628316964860507410608845589697787961931279022232437527676173735698945580778488457225039328418754558971463711411241964072502254434801750594742204007944147333412844094987979011418818288885947743546584715714408801656862222943611193525526816974964984819314531000804771766102758088712128168253821203590126981053723627122982940143523962385736067178069118864136295813595167868924216982331483233933607368128963157903794618662786002157545530897741132083037490380285079121368704009541493318832354662807446062657089842224414219851674601270427510845247761020214633076176593095650698367338310662559259855149282485018409078305238468807335088820755390463323998228311635714064994924411492820533140089503956857397521128036705074221653274853288484228440635009188230039553857624292901775610974219614761953532071757836213246078189275582289714279025317334739593127248151170219352356568555858075457552487927006608049113604855729925904523843350558749172392514659291820445375272431844243847429206256587256813097941929144996892548461695725305600186342557829859656387917654239516741857035157244854859688972213564271466804414502170478722631860093504310484753774407490144451829026016173947215626413374703664042910179759814104800866416219492926670785181387582582660906588673029577965321158888364587371786085465711379334316846267432660382219342627336417325883503627139506769053502464115198869240715386022001793697556974413388309257727624838386246261956017964647889787844926427586246641319927299020913550189602858701745987381821740134774602516215898853812330125717897910124626248504366597171548923845093230690066022087816877223171629873694054152399670274878747947421262076134222972198465873806693267050881406034700404140362365518920605730517401083452951089984979267154427642692282104239095327251886082494486068237845728125993166978853325559065166438220598327661547091838279396398526637723899687062462314042865503950951101862454602051331716307299867011608934399246868593682714886984972285074071308407331357159784283132893306886851259844666209241253152796816454204770014441475779023086426924269522419644709530258690621253026791448658906852876250245014743211259382382314533421221662749189693226062892590523718755051918840534102002845228912014525787763348151565261361150249946408723885471199889921837317892601445509344707084513935626711287706374969887024330235259698440627209650549919915035026971754837099109722450504484450300195802185191139008532739106139430038083861382020229639345182755838305809855443688022867586272686582089618940431140812078081853860786642343227539918103552783314902487321084314297586519692493427047824105805319284819165264494332225528759627586489569301597720852595082158457784457358361973035503350247407796242145146653791357300566675097439735085525111477298128596908004945120626933789841956192716628615090043752949775857529100779605280458770452436778903592575743924814987647957665138476571811662114968956340515718741078543292225710029587006319580797671959514088709724961083441566991102489552119146979830928646804951111937739010630082859011652418120333542703000526519052936733819373218454815148626594694099321310084238737833738419067779688652283538895989992575834699210062531970644832609871684516861143387920936815689668617916836521482054794993176226501715724200919510806732931746882580161812036931887402648182800485334921791433477716169598961474493590420675563094312938717813231680612370953227970156436870268885815731687471805218092023096901736776845448848525047808619861136495449072531669736742574108031376313734335909919199691807923159715470261990977395166302812313435462988632718484023866884031831406283592029434461390322565260504675238614512221502081069502044660126376810867186702628020172535348683431344641743460580367658106261908182962630377659882298424540094260139199647106241164938938955462864124789575144174948776834900586138789932597292222885670920264346849129602220016823304791657213128859753251396889170741208015963301026631326115174865949925730163097362814460224527706413353239387985524201888426718558918062970156176993433607064126874759799526189107115073053741161226374332100378045632598742509831941382910309364062664663075254485462399293498482949024825777998379412660861571114871232314093232855563220038245307067874666773722192447679242609142978812687025927714313244195195036337842103434649273824463696482954454823098199579707862221960541283769310124158573463104486151556071823282120458022048292731205057067345485769085935007196229477932077289119638301352272404485115717088432366680407536436305059949533170281542100914422925914023270055341532179347550573891879022275520207208100238645433092692944473338233782346807653523380826861097003732357925980920590779153257117225915774750032846961973275321318298702127648905844709445455271404759474782194457918666357553782992348183582249149858568597508335853383757573191331011024535059158975601661788083958376587574024243747944589270909274904055134239310757870938244413920164525135463028215965088972110772105982791713305953156349774947579780251090524975511955848120940891602776916160276814417960414829302435028359457316392182217046839362912176155360516234465079497985966628049305703852178782162178706553145967353130737216110298234692934993157638179900022017263378729834771787772861844710806644267959319044705148387704236116819735740525737988295910487595203300816914014961824989372675884253405520561204025895356612914776376549961293644958888768715403120953912958627853394740522888731378627653475046414483484029036974361017895073984047670677600862928890807454305335303471556020775116493559937066006590871743201228032163567523119653753188237672522423054814479497329656610303916045469576582470483901661482628290295659293763860065550520185606808645198565485134067119399006488130952257937707325540797203266259296090087320720900085950751803815064417544773904010896974279695376395819703844930384290836504502462853421484790374314162560203683283110904117287935604885237330573131335484647600512315213802372337175217846017174083346183058221725972506757174624147246989630664174539482228236425620837022921034881886963001039658992314354242321762168087031384277538439169217059793858482898525855874481582534707911214928328807021465584421626940131154881206066603846362738421515859527119892904290659097522097773475118720594516737916852121780448464640979099640243832773343687495617557300275618620205257839005154030604398059169867513778973594688799117308550018873333386478126222357289800162319630154250342029149385511261331150629824835362166892771866657157792163536179789706239629166345364093974992244640454776222215950662569759364010947770908088213284562026167048538342788455871032647176812705582831028578101768721377443286587582265674182395214969571270986777459086575165382045873091874778706592422405949298144872567745772685622878375190688881103412879974101386799228140980807057879133249245128530350807294512080792073586087933525051471632449307171251320622974275348453778965070497557611888356854903982942200742085349714065192439425495074507238381269816806530223080079162916399914968384414496798662968938244166113287206026757847708918287894318778370818614478194983601390924361325931087146339714667771092071550875974101890363304390848079999448713947665851518188267818602991062371831313375576567833037742638670370741360717696623180431529430069304393559593082807641516828755759826786474243970132325405403517414900082900804310768645611672006322975005962905911972147004076381026387803917366161628425459857868321515350749227420294441574773528606974364269151290781533289623693791163589451315146561363790093824798871730092481400069370442781775905376050620003448530418930032785444337397284962576207601449611845645642475726598782216395468868472612149679393357784513641317869756291478498481899765638429976345108932839755117740271751823602699822821082478448799047360235906220280421907944240246001273992058992780735931911767397360065570249591546691932955565659858441802696246332450014835814079097903852942966108153899480312726611319280870905640495910625481285184749978945485644332304691825322697809125086175883317642602107634883560603540464863646181367360461483839545196295116958708635853154301353999973961897260293872729894992155373551526189277634765203582110845829184027398807541980328546740128614325620959255032843479389946182949762067958600050857669985670999406606448325655865803797221834519663964636030883733825740343278857598167366314696034208082887766470371078828763457488421374617531683854678398930375286965227674167461969734841223703453600532461101122492640228449211152775046857705717420013282137866810251231712581030278518972528027594652170482721097549218476626744384016968177748072058989174987457050383416981997117965623907607298554154159178543356433023087086527670407390715173497867504271798341184897577142612154854112037901691504473527394047315765552997020355451531934723707289025056261304701424101495472275957972561376323959274775079849377035284705519666385514613546416502204043741863168659163769339173780209700475524715246719874137000834467369040489932565136283686092953319936199770050512220532181076168027864855030653859025164481628855404936321486901268091861526535884360546625501869440454268905793404621664153559557535651670274350345664604565746229259084511921233756522640123660816047166225534601501040775036560742439948301230840891259062614866088634533386923781299662707679287806546181090623999202471502827809680381856923791351965169622468961647637914438539462513671909251391745828743183763876890520302308966496279175322606334647064013866885766327974415589769837451578949270598913402457502038107225978459343598431871464830791761353630574880110340568384273135005847345179213544106800018565865164062562824328247862379095093423427107446551769406368362052700360280866990784820785404422072165245684682759477237450205312217487859466715043646293480788870090320265516317333115055610376022943214701582621237124645905087128384489577889608405034190540975667944651284891224793907146782530377811590760712650591125729810259164257461506255650333754603040680260544301571387593413965790617277289602985486970450697447917389085497095951481092773319280754706033063508408050106083195137058869424759964860279734071098082786350004472378171554361087736590862092911219169194734306912637949713709845984120122128394063824029870319841251704896663459013398755754728664700689671861599929739951473884847425772355825093489758467100516093176525080441278910976880379512850989888227922990582954705825361980920242261119025053577176460209506577393309365467807414914721481592182380329404968600391017044584986418799507600069996217461352950944168314753764169532770747780939315108868825547200662153775456452705517674104803946856807405183067033286214846290766257833629612161284989500545583412201033091565472377724227167478096505852256973124231852255879552087320415096476821028356527790660122836983578321021301890589552681552456621081064918451835925855514475874242570116026981090622180925978653680233478453475762630987448098429596804407115148326145805507166110578965515527189846566195772125294168842055305765666186689840050908243059149657948828800812350927682823847830414983053438325768126335021712877653255115365125113649281883319134703151235465216", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt::fromUint64(257)) == UArbBigInt::fromString("327603754149987502445729656460957995503430058362104173870854579310346540098632556694658102559555786294165687972432229560620151035211230557105704871089230037158981665946769597998787708943167200257614007891118037557334363773206035148960965081281955365011535418426116223005701108071236634890758743909109674445624644034681720656793988569975810991547178290600261164455776689054514141794424543749681793733626486200905275949142511593307531050771476323974804486857973504539392385261322932063152758103259807092150605130988356290032220174947023724826431432386105069174859793613415452162319096262734922423459405488621770108076063209799570248979696342910814428084400935608673767622203212480381608467250121351295919533809320816192175368091440236302858449397060846166412944260247590626699073924289842412292508340891588130895690752746818600333584153380739493184341354150232912168499246675254229779265372313604579058324171083470806054805158941275060062410978821281233927009903100588666560343587814811669502138212975499141970033124500608645533835975494025624975108436254216413265726399567876721640715867488899578831444205142757400746608787258570391446808826413224733246880449152993823916232214282464771972942086195296664622806964272575402708454996353917419736639557020769315596386443711054214863078708288025854598155330526951972925150727107518826497338230589700573829120826146066910183737500473598710192468247946074441453281514239386565651609674116649681100218031898656519037933432903097389691335659792811362818953108153163200991763464006419193981248040278703841441226702877559900479161849181007172013607521240632567136200941691224454057963899186047244993265574713020036043202969513047900429002925756804515106076356723433598554906011892397831083358598278159756361023250984666364062213303134885750826428813525206849022570523518787648139377730326651110384826684149374921565107914068678776267927576126817275078347939209399269067218260956322811021560805683780853945636283074127815194000156626742929519797087178731705261497207058004392560046140851227916702002347912248429622910566403514503706966850581460971998794304719296008109378774510969532527760425849955697854107413354792913282841962933360553444043894858061237224297756442195585257997307095573292554816279297981941214501348698183600043073633220174247595140550560072419989840815288522791033312516427619331082391933952003229180274614997469375065750156016326069632701314518892613895228803998571741379485220072388427014542829693570732779920124846244855106778802962051582698917658751433285015996895871751546750346883165843491181638375442761713362378953497037876437184199276899338566721314370379661097527840291262711521260676844579598141533047789453446154571545866249175362219880014176772657012925208340463688246396712592739132417561179054587074667648204620076931314621080407401036668374110116193975658245920546172704724692700446748306461415572355915393081701024601921300336872695438305318679655915224744834104714810522467578867150754022476409942622077667737040297216529158901525441442723183776617833180950105689223580893073645186723505086045011984322242353511189419555087126329123783833670797972924880925110402005165378655189634693802633813810834605824312731926860307752826052274033893361466345324824829477357821524495164689387291663688005144927664511452382107490965473968571232503740173846391369996802954566279919980479013475027971473418212454550072298482877892431903175248919050318667570036118883525853886706067751230944605387186830864868266766868425777095533002959774605839861025566559244343609365201458316694446139611975344921822545345733984723522500715346066617040594298812905225296308640420506538334907847520848089515678053931946404413347127514028814459485886822958444047309539725489905481458741590499451870329562385174543225163219565178581665264679322775243912474976402194747393607417024001547347680501545919260164085213154207087894002500969529189081265876287470007333652123617959468509481538464138172008382138477677279650187328205595587713555039177812399789615766684433662482787017207315985381513876944634602719473180600186624758680118635456528584437625223566474375906212137753278371655038206830683423960292121340484576899246011248388898774580073245517676942793509035370536325659162104167069468380939359500102459352614785007407361846123367236716909451837169331940485977586414328875330415366617994982962545552223732171804754004647717392478145821888288205680428985515784802234333445773304305849838718462511275914850704413090325772004936695069355283372379736886371738081603686240581136561452000865854965099145865681577495294243084025638870267886153804409160873995638198002861665815600097758805565126195377086839403889487949567120316002528682311535854329486763041728378231557408284348529297826951511198996335129251797094618706767903287348687728209373766773404053072035911398780590607910265188058438068574731632702280539359395872267157336525753030533653189085730675127799091483479232414120819958071725071039815320452994578801168845736361151821996391252424861404998258234232476709815817855478989922661338338639458557919112670497070716708150882992416945047215459748416679010083867925915040006288901311399984597092352349730250371199355946479577793992660346870535266560592035018209683638713032064394113474700924064892352816723167101471505047249819157805778646104716460639974835038835843838524600963101172847589450609151067587802322768788704011841521221020191432600482966066125020647469114573081259770503234412477982054941293555941534744433486120896461149257163787067461576317852857436035056393032127693973138322276698520556727281772208324501212954214640280972185996183575040579001084107648427710584124349037686239217472899714938387636782265869904636121181335033484894717513011632553784859765036990670421919579437069341168090451397750896545778998976220205513243307452824880268883739566935499315843325629059977905197650716704292403281047307923250095808091426432550091782480353120052033983348505306647129893307398532082762790329093016431482685381067050329414758479829489039508578950087494016061610688038763883713060968463862987840194661023325143867543170253192552780847245398598388720457792454977432819927240646542555071090290673045073409295484281943112203480422862790356847757345245704048934375511585903412508771475750548861126587736801206879859745665662166506799555982606908009232611231623940518464857261819072968528623192221539851635945217042212149937630533628938957382034031806455301218080635623072419792688110477450318620845836482272740941757610365895053384625930150168736072943181409666188386980843739238841606215832243878364641050178179000931829321848879788416221687382711178079839132196503935559182746817882072561759819572369400958598327186824802094144489070158533077080380121591166846614120429835245269954724352319362806527742503579055788804746077484814862651082784767166783738250807981669124325789212055575426747944751487994195134174181341586942700937147042933939900061090679712443292785894253751321670084760236561339699323290996489856528946306585657785479417005563204024253781977702925755200308360699539326019523169389554205898098363793850389861633196846112582726938050640628331931161279112885633650769198586053919795002027455242580646621433887259608545193425017165852402426446011260068732652350849292037939612066153837034358128202090273705322992204873754403043824448081855406011809308104186643826697933668244670288218440340167649415512875845262449644811056859865207656617524426637476593870247890073497308125419697161845262421895663914267473900718617920877673032915588965474792104772779082773435083717054966824232372782997174901361568164529251596316855265131057635513839716499529198302797605531429801575226702494945978952593701415755809464009472200766975533721074492958485301672909088958948368052221092024957021525761743687540529829305792362448933301427827167990864820676194880271821768584320287386164460081096132038447145426529678187732071232291758120071834597495203207555257346390635619141359854038788702950074658590030739052068196709898187700064109421202270471774555734932434942482563833034867566610830533264512633187593991901531978067798299503777628270582795980790552150745613125209695790720122337487562703670223267553481287058385328666325664768047586329896245583719791948075589986426078924762055375577644808022937960455075954923470947751739849996855338046374674636503478092465387844887655098611526715407686013904432202262088143034932381720495885788044517162036384161148257466873563361724741256809983254235270252300985104643878330991256138465958697383468682255825242809338905724127229548841406631835066045774902899638315652535631036883107635528472111175908341656429333224398239736976236611325567608100754867709925452970127463346114530206826441593767144313448702755633439454612970952083986711758085779423667403016740948478307929876500311771241434615212280905143053045053174838451099903930989186103762508126337404686841204815531119994211800066577710891066142689557414880298035454193651090164093803347157429643427265767405937374774951537494611595990211064146563270667119807547765679975250809520062124943103539264238697604806298470375007254220019001081239550671791273550538354474114877470069434458154489574962287535638975355375438153363861576808706373808923450927334989998803990652827163677966968419578370099157565467142512943535785961740576634556132914809958556748538740912444455832817452726197066183106716708986724317588783730434385505545208159550646599704692317366901593203994735782529204487734108090587712128070733081691106922013504701528821160953097655415706288384922676620498563205034114904799921096538444936749575532041966791241329704003245198697711504086093134460245377654049333656708421953686273647016558349230294366265750578210484227595774951491581815542064785952388226709923444552773716386118897230984589559185262985725566287537075506922576246831113407846793711621284482551531994653299575672081586172874101342001107608757602080907973590559124448139754255135946837920725666978669468995649576294991897991747341800887070270047962896752356866518475374368433893130335308424556266620117878764927086601236775806759706735683526812814962126414898964624518088216500835838584083789822092235597616786451649229313753483373845363484739357260997359416585167017356818202205796579169290964454249854672952352450647303402125729408378728954286023045527585830836177212398487756810013465144122411883488980748569154469170237759025881158531315132204822006944682606343454323367347456926803124978292918834741843216682402278094888419233165613470711768181217882377510239185554992429184455980601774253971865859634807406708548263455592394373753544775982628571802894558376038379801568402678570982513132616058723336362724639635033107569061914526621965122867506779258122173640012698819532610072034910060421709515148072393625842096455408502300695882002535690682657647273545607064638286671825414998646183756662681125761101164694749488999649011568112719916153475406585547493271686835508326290320350063148658155337294872596709459922094642847179729590906009839197974683778964282026799209505012671307082900386643947945089639314803113141855472624204790982536419448836402040527343182978274992190774295486767309915882423038847530366691574304898686954061276024106974153243370026845514238815745338331728198212444020830975540818215658245128979075869516867211106014410880959127184460584246761703618285740569331947994745670282248777241571077722050698875317938480850850348677769445647881441902065745558328488220975542576444821379301211264533961129852331730936516220942696876036177936239233735330433123152857652194484228791999870706619889462153267604201923835717370761644000935660290933064971573173335648339656389165857679365558309298277977329766779341187374898362604090162833644195979239024021887419503582168484328052097985734089616326522390256410586124625111401097174561460999320684238835965916125168372879766572586483916378319174985980825465132496554568944690181220089087762338424004882196421182010208957732359669662875051712849454301146328513231651202660633774488855796780566269953158642095634807181716033131960542223561728645425103255850423735052574146552915830108305374231843341130658505502726414748623017608522686282745485695410042969354054746223438359101580689119742268436429903529929173387523059729861401237037783632845542050215519013641494643622882872516442834180881003304946232336851644093481279191527691484044168418194725026930490991215367672183432550209167110955219230370762326334774772086025875012256733949733087721368295687550469977789641827884342017855466781795319627377608976993930344819541859880338509806275252927177224359771554225917303556278186243114709116981348410936372233579065564182221894167106398211844972702126119357381880786472539371337787583306562900346941647535823861426937651390335529649840784232369378694733005995555289763891294910286235981593607153724153728385391235894609033911207351290560886267733334162756233458074461864219876871581104173027561495543882459172045755595058190649918243604931473931494311921678279470942896079930787021103861790241603128332939667153836568780877673253283230257731072995871720344950329714826191794779869022099769319621874198658607648555416376098015904253397266391153401138282572364238118582769448148352061368497598644501267984638597469100182671653006571295294280220776390932110622862460074378004995597559609859821722809644876500106252625994505414557044404677046329172786530163519061979458505456701739418356318768117260557059874748394047516704472584691418349978337247013904395868497744349805593610680991591841010532273042534353247458940497890704796491544657934005735572961875595144773026844205686617746738275675331291102703323612131442476554455875371907109465533748563018725971006724714798602382768383319412656971949611895305898884431118757686059484039223147810412689878782961054866682583662075816933740625606439034854338940047379156718982802447033545099615249274987681158493787490877799276836698971264511068895836386121449283576905886433812500746965030684120919016787663805160709984908308032404775444661868722198386838628212544317551378272451280174650250177086490989384729302136533031240419743411513934482687841757592838536825614249325154608369097489002421136689242127838836911111547904383398676595258005538721127714721712649642943317521842739329600751420143497097756935617048318144720607389465896689667300222119749800320198719725453228829638787621255471772563520896492833606655153573402434695451335755700619575565933523735770068815952936504260745996786731264726192657388157434509830243949442704172992165639656375568054118301346175662159185271566457899840503981246678702545484193023758777261495769432443230343614560943677837341559120425189787245019655938299941850652639650072491198430663923862934620992455578440771317132141109248532068734915687540275727864828658314681749183050235649996606648856772562794083976039877659349737837762019095279252344080071413761016329870706117681857166910046142142485640004789806083735097170038353867277945384657530919503231291613878803095389241430738667589855481254468406738228063695176032426306880966756346558132206527828405122142449741182196919396075312953176107186944933776810158319786021099786327916816065256562477102533474818372753211291876891564836136450914563981995636484221454752738935865161532051371764999806424284199678833285563094644979891356201676569254483712509356102247138571505431769567037227137034087674630212740213030141191694497761657087964929445462778865871549640551765628654190710973424107337385673844300122006605193766311954211831286104289260627212016062995285388273989203012235910952746388172138951141689869822878032264247074108054613087137152716379849156571312256040845909799676303540438445648710783377378792270641372197144923357566202702880652477782061895103133895761891700188962631016376416116264966831867612609193931469452606282175827141880414985175786828906319130392237464621007504411128408453085159663139532507543192618924634868683839593248480791340465338387806695484301585819004854345604562432652429090733369467614363658129742656533869179399148259464110223985207339364687810960852179313380637424086074899556497833665926354297413338691571199532071600343631001467432051429282713604154715414402294510869092995597300311879454154038650267338793301827440702656144046594061783584424555453286422897483315551345993613803275818976649306233026807584328144556338984327935570078865728887974067970225594633622744002632532967395604094507561306991854841073707800930037320543517625857629910637230562960863727834695629320693445447469312908210580695447857315711285245968277948664252196850133383043050654465549847176201704731183042882159706337521177153550287462554290056067271324294874373314897396469413703629777938682593219416516077087608696144796146574077160908012362332645261441212440672311810128244309601100794555296545525474572868268852713877884170580579976428010202688079292950969275024339581696653048046969319850653168490510083590031649029787856777093528579815427260329645317436137406078813342690134318769133795860313048059956289117972666272196619167013908449124558237999379409877502302934361160966779860357464469567824093063600381042266791253793140769933368277922540833223829158238177301762075516680692893385074498517242064838270816941262188939860568008522464642900470755801889957927192109245290124462699377855390168627227922494767810583290046076106170342168883603920329339898005025376949361961099479102994881710757484471011246434961858951745839354624926366070530443735000887103484907283518978425644215936027397047323785615232033654252367525224457573337445975856300927916971644751664192933692574818253077849636646956596119614389056771021403157628858613051218278712882752242208643320669040660291974284596036979306587207000408709215382356085521929296352124989328818011126254113961385803750397416778188839418230022597256603036807979639609059618780889921772235499457686889821882204716013869838338086258948660747333424896899296295463517855132925868856347976310362540604936653497086600462010539885917925223204130511031706810326811408605222433260197188590678927969275172036886784743420697995665606296169102176653256697648338151524153710434350762857211963320116289568619285830641310461857492188126180896394102504993187121301444822671065839542963658971905225459530157747988678592113708454364466570557152519049534115164841432421305716168292822400650034234722487361835439502990699278480574942811150562741561570964004853452304877853047065553166712346401611305364658252547435344656796959321927355793136481458023918239152680145847543615859220853101016986893389256139062348407270477379922311300341160887063954548349693800323554212183107685329265194094696402197619301446670610111362898314966793019109933904142729636653427511119896896746327315152014190489952855357123776232237325341331731159250863296416379304174290853792479908738386222012569261963572902504558163070120745178968990871244705812618568641880820358809967346508193785046682366666306143385386951273606426067741506630575658419960905679984455754078511258458478244441856460141587207054876762214979014854192085400845086086389821225266286916468025344910527147617495838837920570310319543220989788617208387334003757231233730093577644878058380024932415631188574922048355281655720862460021772328368690725430507273848577250983950061145457574279479418902707709795872189357623194696136491616932349903531118485993485709541482330863796024305662106673603357397752894838886841920072428346984202681114494457833071974960854763404429012267185523225399893697500783253444553057266877531269624332556279061890630533136708787650070732074947333160649659636688114842428020545987285562435155024852803517055456374654028472316374046891574387448487169039406427637243822935909816982801364535019480057768682305435294914337405978192697520107472012360788422688598291443558061170327949088789582434768785967015979251280428140022034811579496005353673466768679408040874609732108185750303441355695485357306249895694475038144814772175847655886295699000726538798345154350775753915476736657050213141881296784742499152258037505419811472932999059908304403066946403598050521478057573625834304502179846485268010741976057370361847729501791332492456588203762363733176653654246116543445050274690766815791420372207125169599175997678727851271455958080307767226028993058870537623474812989009245050608947972798175256383358331936814166791828178674055635511186991786766809668780288167199750289313029756757226435198063003003883952879928045356097938641878668124458821016076965519312619592824895102067317274931169244096359337759248798704612615540023963736849212782078053374429360304354887142489880490314218855113971871629269882849389885635771000289093397874077538371934469041252822101825808527003625863305582711838980459506381661058934296245277143103690605716992289162624737607025836322938548764047719439425935256995041301392167692984392128408307701204716970853008700121515741461152271725841356308945635751865962939328050755054709447178514300674212103037878917162573715091618065652540695905747242802965538327469880592998849172794446205159490018651016586764369387865791409396129375015301363952767159187060605550387280372251573359215704870666238411509086600963568956958947846767198468653456143668874040191115915780241149280836853057306837787681689448472204958103873928524747030222139664706648510230134132863033645779457401111258094326626172493372716916953288693618174555420435871454874193408745200797547537638739320119778716002853101682892089885769149125933723916116687093881869779479539044009341936358709641568110611184041069302773684176721370311102925127738292528616709231180976636907727074936983904871151206356884076250770650979217575381995235194581683203972494605875584805632993297474440535147289492999934819690348544", 10) );
	REQUIRE( UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt::fromString("321", 10)) == UArbBigInt::fromString("235131727369793598590237927764327204907148418164945334929209808908609764248872000066242323468863555199676594920212602965453323155296135730823798195269211664656099299342438661381834514623279041772166444954511708391015722895874195656374613822945545696494212556595774802101190576031720894607150635820520441402088848948291688752806902757547248673629269017502396086768556246929722149748128651974902900938948631946706677657087442335326305793283786426587137880294841762641262458951011187343624314169099408722061144065682400560742207893177229024368858782308151526955442479388997380747719815030513808467089362737612016474932458928560286135649656702635257518527949842171790395430352547097705094761396425013402456710753306722925975887903774200064103107061402842408845112258286395675238500043419535336328644685762659179188142594033233156760569619145444465447119442688589567820637051214115321669253706115446541877223495734908272788181245756766495605512497239521194937129256710525896692858013722560872034974732710298814928778564509164468751299785340791354413530822178307488910138304885796089942578324626341955013078468012460114858057616657944434333386298801618014952688549274444450810384598514318629481339200379589959042143710511819559346097571837578418992641528678028803511447779225621244515282709627042397241577409787670473279562947082775848563907727814574077009850724835573310617540815143410753661112735043763870375303636993551026559182999191036332848109084080430165453534585373784117420799991830889543349711955956511387781767167166558251200214303288610875881328672237926542407866799220327717600541521483167657381853198494047913317596950171449779368491036552615604095603909926737193304440270251797886513083560076145186057646246750775966029859016224453850881200415764417624796017170145559969226939914712837705215211114208809592042864252752640508755097674077983549961394964778246870917849626235687780256258054588240610995575856784322305771312238407910690916012250979209774124529439990662675073688522067061674380007088044331379846406692559602362083496956283454433672958960737513637429981090113699848642370960987654051063877822437864450347391956595331894276287417347769356273160822645733236415330368918822403282708741717202440995430205250513050504295670702141723083635172068134075917891066238170095449883778971795843637916631459957353184455966473607818636174808325159356110640929994928825770439680638900428958097816165209311084010101686090756926710075449289286207428643356148197622537962729318254120464476353572656839008390430652006387671125636879985744941882842779910558804132922234038850919197621848124525208062078273571816565333815097314993616362734097194249480359242239397825780911267546180569994257932232202271461300345307317936111504463199865920790727756586682812729702793661755600209930787118342298868172652142002637209509078286736394494347346290762876900539130716361413953818834955789474666983527429947056916317790694436312091308015495445099963986259228979221228764704289050409272057235454644247446695849989070955969232556131053321635636028873677452434730203701902154863053692232773031141376117441957681274913925529133143241731791342228850618659184766182619280375921753504754286917298136903375724012093755484378577197380053186169130561118645633062090298103084160893725886070653916245881559546369767203341749468730373276804944526622731466162623926549663275477114180116381878721708638034362613218264636884178855020977780033452309013338338116866502189353635217369544490459289786477984127554671061454436975190573363075993401195349111426632164645313893619920424065492912100165527764934954237003248305721997238554131583372353703655794355302397290516465877933055077658045057560335352127561770461827924106182125292721991482626877503036893503148652437332534425160992353895748580149847973237161904318875434198084422432988782697569411945521132233626266207207325171070629399224815817118722076998850034507615226857402452330641138741159202708648823865307480109747243923528988679124314806545132863082244074420311922923650460395577274537129971908526099346206861941864951662813406750780044715000769492819948479148638778930817476597531160475805551565577054869253717516609228100401479965445551554301320968264018215358889179384480210935889662957745938765579694931865914781505472477288406192206518964526074775890704026178328167052222857914996999779020426571879601905890284802264746623834227209831942601903379468339309623507706613113295393156296613248226611679289175281777154746535195232001135902202461281276826273565581440628505334333853478501098064087122527902740195505207970415320682292812689389691295022917075199395381363548789616686357494232028276587646355923419037622530303282118724719870762362437476567935558443332980036918516697001712716333608185129700588362255711570595021405471331878061346988931715519710770372594524210095327034922678364167020080882895082315073055160283845175193717226198291512002872623593093417180386859868752333731841363785254383602622409683137512107248639162294934435402101273907941443828010725985684404258694327165343259094837588664250451872665448071837189735666559102572420426040952101626854482347358141921781416549632550202350751698922136806830592376099788557081841661640637790123488919674676523529487034661870510635466975092584587976022332542662116032413123371722313846241219453559872474199429343427451246513516870518927235871740752893659307659266815227731652755694628594224915766290147551567965928247812004310817173443972325959496945195439393512382028328526351136319587630773111489980584812436156888017756305520001229737203415218465707772221159530942060703396301006455581777062910246325145817793314366922546886953791049498123699442109431670476520383386929165159425161760231111220776472636937012609900160024190417120981673868749914924825233519671802606078433638782921787270841713641832319402799546989564976975436545017658500565470342497257963436077847402657400509902991010584087902234306632259818606677882302317837916061067593530730297323898218182142629739503472415805441787381366541179954030135861290561200735222823289927862514609159832554516045268126522359344866480932632090180439158728653760291053169256956763465864989010464217615925236175550791689473148829016141106331870185919410551442771906094610995312770461972268642330441413338175913211834676909385335323383387678370845296128845203167315552901919597802327750697034630474963769391057059111351606032679515404452107187673487961525614716362698673555449415255311586782600390974347889512434586216438570456127511475977426688379718598481495821475546566771024695420191616824818777628193460997159677710247115603938755118004316060858872839651908015075372275475102756283920431551783913144356712015767698356337679487943657192284254598838308831047533957057313593354099313663297790803287370990347859075450515438372129211648406251352185122677743030805791941565940220508891195603879705144778562234105805997228789200762557717640194781572344555261524944796235859277873654613181443042053643116988913652891169294736600373143073440549346054673324178527660357158463727180516311016224808906386702873748502846185503258467818695704690307389326365353409161210672135177984403874844673041935174164363057696892926231273698290368099843099770735891861323222394865761454283252219407555271831912222149644623002345418832352723877264119479125636442106965258394120258356171994757071625254928181117564071551565072413983427678066302973800501234084337419947680059093167344072661617808178348635901476543378834233192245905860300628403547052039132947915833579792137016644056578455804798271983792538825620155478289388646959577296350015602938609778302582048339131865331801384396531882520553786404737587101700780199820814484586571989181941033411435795632278117666698821409471316940052055753111026411032154985014903037435619759672050067221628089300013832862226397515444440594127840907744334825730493081295414822720030727458461657781930273763340879165157298352939594013063703886256174451347114439292678955787011602073598524382968813039537611686030602254037135409562747709791440666086882645295277603505649417488294937055584421977494562454499193608592372225860884836289945961308651320126998406278833034830510214995171382964992406106094415135068938139266359688688193215099398333597625087928882257649392444104511867944687867784975759352336717597403490031773448628647396070240256041363130117495488958354675370230619493781867565808074030912282446247871538986085144797438869995690996458355678694700388594570791212356689163761772711053303630417310000462636603694761287247843958035420380909909709998309489601821279610391337645117776196170498083870242598177149120198945985961887718760061358007940161865655000918634871627779015097123224479681615319480987751327419883528981000187650321034115904138411374134807315364004701273365175486423486601490351055977553931449342783183598219931664778332456139402190675165225780258995657860356526821984945762644975027288177622471188984287286569576281002519745044866772569744472160399392199251879491026094573842969998648534841021798994595691439751278598712868117700282114705747352076694575970108199590129168528792978656241293315348774232445223431350140491658746167380148287025077914377965121565338642708739499091876104010843925439957311626302787480971835021690038994978768443916415116318408938473141820325118420942415263113711529959779218250707018842010821159987726569562710723706152534784051515027149237439327747494564380263421932628374007771939247859855661221209093926540750699751890165833199147016190781230022918939552396828884348717483767891060638823183679223001606177169700170849406077332326245761413530614449100547995755482566211564715864428419617583478827799035147340093916276320404663630723320197095450542058761774781873276018366582029234940369910061644929886830776426210802791915140250984282690448609966398921070658726416660745914561167231377562017066582747016666476047219099160668822190371009273632102734264240170863201854790221031286622177398534831901307522797026611376407225079002215773201948544872906174985013010529882515319025353837392574960505916767771531959579873531370906737752931233157737181761633751031553857529289928819488425702466226633259691727081394795284219117296688528300582247722834406955903563537033908076459759583480662044008261840754731475468509807104411032914439135278402552227858785823206623166357959547302448923687756075724887610045766146566994402164819212857643226951834183509586250378607526456967418488270428192765963716860258046173708267754976678902514682608964398353026663364871271334502804010123271186108735400292520005589092057751460440529767435133642926799901491747874406618050460590471282887050867957927392928166673160750149266278097870029346450227909035081311417332900385586664215533688578575023461958122086100168406359925341637943391094521992887497835126812867160092838692561811863683145806457919902096987308538920021109382459437399553886773570375719728160436165049527136131486918579384599210210960893176821684472303938151472429664239842570154160958415314446489106820897983733387712242368810902724914532619550148957455531679313611739075156392879212806685092394612180495865744390971825215707808122744384170684527328523620725223388751446259341474290638199708574757029558606873610144696493130728167520895022181113492604415287226815978641055486653509337312844992231880917337503470595903107556830664378337387835226745623696943362527728272480683852317713504994502477406806712300916252484244641098402727737493408177230359405321656289293710563766526866420059956811702129018726049132104133091834698984984739606228612321777202942751479270662482558114021223481431431072139166016334921640815454157318059144145679474862724375713966801818900132293310509808718144265858878546818663406500491614278322398093358593894890659807928207132752586733660882940209665639225388905130496238142229825541862035206127801473863192714429428944517911451792996591592537346826502929136655783140561665260934654827897939746442990362338855012246699045039566163507657167167934533069365316604373451195486488887289485303355403745220508186323108710400063916923564226634187717143125508910341654595985756837094122646690316877697368501233819325911869971520945990208918258379183769634696721861948570102865706443749816812696333481493369944686820956371350038307978515072643148480080208903386565114535729052641730568652904695146196130621251545640665855637075057794087325457440667196432773702702070039558923026383352166871584893275636323188185980273215370103788924139371105483641560399158493130350713214447196727771580688853162469414572156687879320454623294493030412689757052890265830924418229418397389902710405405543519240459762455722733895038826259833595802013039282073883216668776647814050703999198932243199629314956261041100765513202067741186511606364013205876005301968360020797722496936119458024397394218163779322579925621101352910651933684826245190921430593150452488948049706175323344565093177146694802407595128203084217524289197684095787657295050941524973083194701806682757964238027089302235672204421963358069289932460205739304335176101364203312631297477727697952251091573611514423116966893421668189650270200771589153792501677758454236090790232300524198619528267340217972593073806308044251667314687223099491372766391803099688589900005174209003566644123617673958250233675467270989355075854464516555980735954167478418379041069058678452632138556269784196986097422548215997592177754692811076363454438380633008206440573054003152606605109408200352193304335857838128932010196735017411994465180542750533025041591879579449904990675996955440343656002965053745978338715328910178798943271394211786168904887974652539097434567775113859446561094776504066184504291398317567150191140577107728271567171432197188335213209129926707415352162543057529539385830245522734659654799981031643176782003387655121329298096085235276820546113288719260332963340430295940646372885123213044328960834400099356504711158310625981915880619554576064328070569045479090458705923173172054858775749238618839447943088452088690685762574929501416820768591165137835776010088147092375288206422990475656322825704647064080170113438565358104744621346550356857975674978089680023894144579111378004007978127423329841141794436786998476095700398884215744019867898249695623687946439420237727403335886715655780069878643259403546612086187093251217508648295018052219485874321964393775406438386964551978139658704614138195581642305164051912783658277767991884944107479763810648376727788807244362433964211774848250194993286737662129286212739983588659635556843292182729092485947894919264985869800551328479277164845149047249681294444684870883789467798132704821321213212568553038985406405286377958168158993935578110934317718770526773001743625590630244661463774170852423744935339827273116729868808392806089609230475030262669535637953331111117024766025102239538171650651256252492597441202594968827395315432284893641604334362991641810422246382972292018693644167521248112552129642255902609979813337197012389236090264376177519634017744248991870258986339993078504748490791688054076821192225573131067030005346437738550314002046474740186425717730190702877641772567301598534523237689021473787832014704324931454624365709624541868982452288181921251455354923248722214589993883769247750088484321183754030868868136394035871103245291695694091678972243310899856636575359498750305726553177782265893365511610522404619221117715910206234770004649000158288753606003783278712957971390063672685377612374846072589112660624102538421423942953379790412091870502254281665825228323272817085856453425310340562602610817504185190066656400120118342192104042377354105820861729542726857243890204628140196010684896364633751787152822890588862961805080953260777304558547878600015182065451661619128702160350636204034040451673120580443624692706662966297238332805983788645124545331489261473636230943446019090993121103219764654147446068503351061948200532174477970453618307043246707814359558704864097836878669771321645695901219995518264710949918350048864010872904042700494813508188952554104545520381750137714804442922498309335173459937235379478192738565842296572774696203057991719503497561972893260429638433347713826345220812836213999041476551890341165655508882409476507874447865471196569034890150056758979868454031697589848958831614593022402758561522206027362299900951312859399938216277420852515787559239698471768055218072916186760584787307356188279706960468022655832106168041090525950858600096000963799056765317438597543301170210930782139852610655318746592547009620093212081547161494259405995543467865768792676252801907116899641580888179721105563023711652646193045849011148466651728265800429762096999069606826596876631206685145298894757495143186168090942242394169253922597929436995189573156795380662969605566891639447305828700914742566365548068603890985317847778234048909380718524464281907493046621496295004211969182269103264886360162829568008776013182671987420731859640033591353005096073147828623133684747051527544965208017518040351197900521173471794528754695668369586640699357788548864485226792025710523296502052254304936870636372444170166126328185769364601488847271361788658245938342656747812150605770739222554045566999670422961415701392330044351421466973793274538288007937803252828719517505564614223377265169586427736526883064040657965053098592652651266035649533644838251697479030491804460922419147566816623308692960203894565670069401410691344479111684008105567240210273981369642601651608514020677619707504563656220934220962152682895429197367129945727561821499740925088159520622206543789031058995540854254446361050229003293958943073796302070538180624561928355995566181178497410757517433038222792159764992957400225845617774670376915312845638218532429175409906049924643616986154754554779101577918283899919347502311180697693323762222392685498256733515819298261352295767759721383793903960574870029761986240029489978773653269273385189371707270546542588006618959974931294348785881178733588297672836261301402096770892358589264262250838006108114448003292976173685858501814631309976173579886623099064815648913061181925644157776999069726502975892132857391170215023610174403655565615137238637135319935122566369942697863454090417018554445147292737923908260529363323635476486378277807692938241388583929851174290724374857461421278572832153559668723901842265467565860273532421888957546928891918038991550487984262383877765483680342988769245239677066615672436692122267623118106074622291078337740429994908609618870633223075811831439138494070182381889705877426823774114688871028926224049201442878376147339958918356952327863135517148055790535408820862452459802370789442926695182830544034190214487140671809524178991840024650002497636900630928805395879666149852689508266808330228741711342096849197284569096716800954670753754999238946992858452551049647274500862238658980721516199655673254563224684053464834903088462778566888068495618490636724383785527882938573486017379734081149155681393187191071861076488526677326486064717806682353577151499244692325356411633762757487460034108923641524869423105593254278604634497937688192971499637957056082035394865398722451453775461022178038868050654078426058043860250228775227730715781442871271565848406283233070981064793977810892624324238081311963260958766726794869666388440707661175132179964386830465631441998550073857304277593713931999324367940869560342712543070153249444855948792447605379484828506247570490046098191848844205599509422835433157118878943733216471834207629792928018236352613944948523089021743090825289477119521269208970227627186905910474201867027760320177100521125557220212830436151331883602020402363007701423825057272628319601708679093703600875782794137718453122872630901374778783753860790844541753547547479135500945982266818535359438269570414482856035649957981226396134516887267352371441996470443033621416080449844789299028720233744985159721741857583541214116347309860429255749090976975792107406933932430886798869630138778678830246871782205041076497048052502094275427573913857957047447615309791380629894787399872300641889522633521065317039435709316852537166016997768360319046027385462334903041129329946489316779006519950820822213578319577064411393697057441970241918355236609923324843207341113633024644829250822653688959839296615354426781509152566941944578332686900669298378609148352499594716306071473928517633120561149138120517283455239263777149161609836471210755806333047528836891032254896286380858475160047846758203553968523407112969665193148671078439617477173044252087307009135295325144827340080377788638481780915409602527742381574960982368764096836962550429551369078657366081683802708236786934375455851631746810733547772987923951856110801260384429761300964340447769629444332774966764878608501171813320645929380172024167239716820831079290125095379068439212748888117598941524136428159633675673981802978616600058167488937798380562157936902535788948513585151443009840170928664272669260565240279454871002029679021205074963629312821345244354310398913369718417670069378310689331141751130563839827125249504141124441851986383309099116639214477185701721432659123877972108155353747784873478698271659076269274157240344214695800204641058004942336734432057915774280073752348884298588198768477662726079574069574300127580133343836267315013351708387336108584129310669414748891721830040384145161726381949607384497475034581738955923257790467042600877491010875913461635706268825461741390802838301176526819147725797065517868344374822800174457366802069330914971090184845806085318607407543370109303131624320585331974815215506047010426991397696780885107448229107941162095759193717582007508049355481765309711512161875251755377816885263111664846964598475707958583397242912080069040723098238257275487695166939698916614082288718065176213787627959454742115963778572748738250397244030147372278678804058805929285889959209092591634706150438694126788805402911035479946022204422095698659915862374847292998066319647438948703485962838299490573750526000948266427616538918292705083156374295078319145969882436043804278219720089503341672644073646894915522466723173953730083171454586076813218917121031541889333563756543337241739262896542165170186649998733278356461344911954949707029189690403864280376290088765513685401043299418399233736697020569161161595958467796826337137172207641109760413622233774665673592178721531827876969936808307506598760925806379481937038351635940098690447443047445116550534756472944859087663076178027660975469503347763188607356876501744335643137204661437705458440756764102085096436796510140575416840828946600937932691922924000074421606951954686271821918873475896018965620867402564955882022940515767460446802475962310952021492642657825362945216961698594964540325493722303632323324727142105910366329998066094019774280028136544435951946162160926030932768887183488587607768345809700344217134673534001068442660778586809345677994651227908197297255962460979732470571683696572467910316954834303887922407676945840699350328304767960647137799236048446843407136046839779150388360940992037454707363659187570723325496218599187091722214562891590340678512533564787590478930420812033157446803317857021341409337353636607951160690933939240832141930224103346607698439411225240894433232737899273191797512804090194406357447285022201905091588628503513027800769475791859679647558094428029829798087141717730343724795341733808138318993663738262134730698650467564084164953886021341225151313544087269654987589181396797546531884682922017415902487308416037379812855536237007501652895566172245279116385273838376843446226842214643234813768246562898361181239824736179438457671542182161997138581145830006868392592868143371165851136299232540895011198190059981490016920245295133401990629681579686590882813725932574776065634350729957798230015816457111413016823606953931370019345103618959244803972904117626232863514479418098217799630536310812050616384850498976697781834285790935670303956643013432370904615237617039009509679587650436730290984741208885631064466051822665868982791295202611783582527537730376825173279204105672113743427708480293357579574239587639959842663472824397656166965336197899533519561802626082604495978887362170358638988918398194785141249432545258445463010122130357439558972426920921300734915256921448702492501742143316035460921053088591793717396708301265402222008571545784305137560456465090301530303411332401743810680964585086720384201905880660891557177506736044144549020567405235962340066288409758057098737633474379384213912978204038940587199561454966676419302616925127381379448800699627787976606862355069625844388034636193740869272123177936070856572539635570600113871655644079960447636989082696321308211804408215881380854507846020285220422117131135853021598378541138356279306602848382986777366582863294263482978061629306204254192969193391253971814437547693672055773396560331883107557310202674855803143692429450863943345531189008151133773805565202873518467959787701098743980841526560812655812577524477683421472631177833541190404241930478808898915362142239170114200148120845700068227302163092424509850547093951449670685649292184408755914783167981665213703207976314544626768519665547620055993587962747554343581734236384397067372888556867185224416696196988631436238610758987706278940642363289762297194358393485543415935596044715584236192203588892066073254601528117515078870869458158769158849485412975018300834757852308243689379051007389184247434766900033129421827876396445579986505158711233001693454874616004153061635188173279702689109182507193710207997781486925386704688323952841189504448903816125581222310779409366767269341195986318574815389048757675708096754568807019739380865924457276847562075410365340882195463125220395332363641275606688401590603603835545648104202228402074831352023667781887081427613471668894536611237205415997110740912984612409150745035127181514423147104849040912286047824237661884276273754384991090547853067884214721248806473174189331959443748639751628385666515075764786137067151058596590248542133882547771501935899274667322122667741096528282284040134100252901712267880638249749806114481379947916919445696418179658228821543819503299350444633684477211358736100428437622441829313228466800148060208737306434740551496340207540633285248481230280548904124902521605914801954359293566750777477286028453171874244276113306534738423042978719649047777829031852707036430788632782649842736577376962163243149697391280870516723475002436466592860167875756512565409745707848661754519159120845435998008629587385341081327446004137144457628225873949353571962194319006222218022338707640621468706038868373346053359320153827239658910825825900837488001661343766657569472328306888807121394393399628779669860008642699443375763692601332284889079718744889948687766283692431974903604820697116581959348271753353202309017803468965723118910078597595564330800724764254646090886298053075305865680910775518849352456060094134434188969789237991325061545356874953690096202642270307285057377684547851559481726395555324353267780748320233980354295418030390529197606534435936119645744869184709048440512341851963476498609519947802545990636817055776914198920871578340182672435678274685226500313051840310129923314490466821274413367389872874088146454759017631343000991387119851545821184", 10) );
#endif

	//REQUIRE( UArbBigInt::fromString("321", 10).pow(UArbBigInt::fromString("721", 10)) == UArbBigInt::fromString("", 10)

	REQUIRE( UArbBigInt::fromString("1234523643567098765433567268387411043985640123642389767832457568567546743234", 10).pow(UArbBigInt(  0)).toUint64() ==   1 );
	REQUIRE( UArbBigInt(  0).pow(UArbBigInt::fromString("1234523643567098765433567268387411043985640123642389767832457568567546743234", 10)).toUint64() ==   0 );
}

TEST_CASE( "unsigned infinit big integer sqrt", "[UABigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( UArbBigInt(  0).sqrt().toUint64() ==   0 );
	REQUIRE( UArbBigInt(  1).sqrt().toUint64() ==   1 );
	REQUIRE( UArbBigInt(  2).sqrt().toUint64() ==   1 );
	REQUIRE( UArbBigInt(  3).sqrt().toUint64() ==   1 );
	REQUIRE( UArbBigInt(  4).sqrt().toUint64() ==   2 );
	REQUIRE( UArbBigInt(  5).sqrt().toUint64() ==   2 );
	REQUIRE( UArbBigInt(  6).sqrt().toUint64() ==   2 );
	REQUIRE( UArbBigInt(  7).sqrt().toUint64() ==   2 );
	REQUIRE( UArbBigInt(  8).sqrt().toUint64() ==   2 );
	REQUIRE( UArbBigInt(  9).sqrt().toUint64() ==   3 );
	REQUIRE( UArbBigInt( 10).sqrt().toUint64() ==   3 );
	REQUIRE( UArbBigInt( 11).sqrt().toUint64() ==   3 );
	REQUIRE( UArbBigInt( 12).sqrt().toUint64() ==   3 );
	REQUIRE( UArbBigInt( 13).sqrt().toUint64() ==   3 );
	REQUIRE( UArbBigInt( 14).sqrt().toUint64() ==   3 );
	REQUIRE( UArbBigInt( 15).sqrt().toUint64() ==   3 );
	REQUIRE( UArbBigInt( 16).sqrt().toUint64() ==   4 );
	REQUIRE( UArbBigInt( 18).sqrt().toUint64() ==   4 );
	REQUIRE( UArbBigInt( 19).sqrt().toUint64() ==   4 );
	REQUIRE( UArbBigInt( 20).sqrt().toUint64() ==   4 );

	REQUIRE( UArbBigInt( 25).sqrt().toUint64() ==   5 );
	REQUIRE( UArbBigInt( 79).sqrt().toUint64() ==   8);
	REQUIRE( UArbBigInt(127).sqrt().toUint64() ==   11);
	REQUIRE( UArbBigInt(143).sqrt().toUint64() ==   11);
	REQUIRE( UArbBigInt(144).sqrt().toUint64() ==   12);
	REQUIRE( UArbBigInt(145).sqrt().toUint64() ==   12);
	REQUIRE( UArbBigInt(255).sqrt().toUint64() ==   15);

	// 2 Byte (16bit)
	REQUIRE( UArbBigInt::fromUint64(  256).sqrt().toUint64() ==   16);
	REQUIRE( UArbBigInt::fromUint64(16128).sqrt().toUint64() ==   126);
	REQUIRE( UArbBigInt::fromUint64(16129).sqrt().toUint64() ==   127);
	REQUIRE( UArbBigInt::fromUint64(16130).sqrt().toUint64() ==   127);

	// 4 Byte (32bit)
	REQUIRE( UArbBigInt::fromString("10 00 00 00", 16).sqrt() == UArbBigInt::fromString("40 00", 16) );
	REQUIRE( UArbBigInt::fromString("01 23 cd ef", 16).sqrt() == UArbBigInt::fromString("11 15", 16) );
	REQUIRE( UArbBigInt::fromString("ff ff ff ff", 16).sqrt() == UArbBigInt::fromString("ff ff", 16) );

	// 8 Byte (64bit)
	REQUIRE( UArbBigInt::fromString("10 00 00 00 00 00 00 00", 16).sqrt() == UArbBigInt::fromString("40 00 00 00", 16) );
	REQUIRE( UArbBigInt::fromString("01 23 45 67 89 ab cd ef", 16).sqrt() == UArbBigInt::fromString("11 11 11 11", 16) );
	REQUIRE( UArbBigInt::fromString("ff ff ff ff ff ff ff ff", 16).sqrt() == UArbBigInt::fromString("ff ff ff ff", 16) );

	// 16 Byte (128bit)
	REQUIRE( UArbBigInt::fromString("0d f8 45 84 5b 4a 35 e4 89 0d e0 00 9f", 16).sqrt() == UArbBigInt::fromString("03 bc d4 ba db 37 87", 16) );
	REQUIRE( UArbBigInt::fromString("c7 d8 56 0d f8 45 84 5b 4a 35 e4 89 0d e0 00 9f", 16).sqrt() == UArbBigInt::fromString("e2 2f be f3 b5 70 46 1d", 16) );

	// ------
	REQUIRE( UArbBigInt::fromString("1524048626526185117008148645329708998795770321794318911442256140455458946053172210513801777413097237329246447244122385285308414454789711324787960475901495579519924778756", 10).sqrt() == UArbBigInt::fromString("1234523643567098765433100593754267268387411043985640123642389767832457568567546743234", 10) );
}

TEST_CASE( "unsigned infinit big integer bitLength", "[UABigint]" ) {
	REQUIRE( UArbBigInt::fromString("00000000", 2).bitLength() == 0 );
	REQUIRE( UArbBigInt::fromString("00000001", 2).bitLength() == 1 );
	REQUIRE( UArbBigInt::fromString("00000011", 2).bitLength() == 2 );
	REQUIRE( UArbBigInt::fromString("00000111", 2).bitLength() == 3 );
	REQUIRE( UArbBigInt::fromString("00001111", 2).bitLength() == 4 );
	REQUIRE( UArbBigInt::fromString("00011111", 2).bitLength() == 5 );
	REQUIRE( UArbBigInt::fromString("00111111", 2).bitLength() == 6 );
	REQUIRE( UArbBigInt::fromString("01111111", 2).bitLength() == 7 );
	REQUIRE( UArbBigInt::fromString("11111111", 2).bitLength() == 8 );

	REQUIRE( UArbBigInt::fromString("00000000", 2).bitLength() == 0 );
	REQUIRE( UArbBigInt::fromString("00000001", 2).bitLength() == 1 );
	REQUIRE( UArbBigInt::fromString("00000010", 2).bitLength() == 2 );
	REQUIRE( UArbBigInt::fromString("00000100", 2).bitLength() == 3 );
	REQUIRE( UArbBigInt::fromString("00001000", 2).bitLength() == 4 );
	REQUIRE( UArbBigInt::fromString("00010000", 2).bitLength() == 5 );
	REQUIRE( UArbBigInt::fromString("00100000", 2).bitLength() == 6 );
	REQUIRE( UArbBigInt::fromString("01000000", 2).bitLength() == 7 );
	REQUIRE( UArbBigInt::fromString("10000000", 2).bitLength() == 8 );

	REQUIRE( UArbBigInt::fromString("00000000 00000000", 2).bitLength() ==  0 );
	REQUIRE( UArbBigInt::fromString("00000001 00000000", 2).bitLength() ==  9 );
	REQUIRE( UArbBigInt::fromString("00000010 00000000", 2).bitLength() == 10 );
	REQUIRE( UArbBigInt::fromString("00000100 00000000", 2).bitLength() == 11 );
	REQUIRE( UArbBigInt::fromString("00001000 00000000", 2).bitLength() == 12 );
	REQUIRE( UArbBigInt::fromString("00010000 00000000", 2).bitLength() == 13 );
	REQUIRE( UArbBigInt::fromString("00100000 00000000", 2).bitLength() == 14 );
	REQUIRE( UArbBigInt::fromString("01000000 00000000", 2).bitLength() == 15 );
	REQUIRE( UArbBigInt::fromString("10000000 00000000", 2).bitLength() == 16 );

	REQUIRE( UArbBigInt::fromString("00000000 00000000 00000000", 2).bitLength() ==  0 );
	REQUIRE( UArbBigInt::fromString("00000001 00000000 00000000", 2).bitLength() == 17 );
	REQUIRE( UArbBigInt::fromString("00000010 00000000 00000000", 2).bitLength() == 18 );
	REQUIRE( UArbBigInt::fromString("00000100 00000000 00000000", 2).bitLength() == 19 );
	REQUIRE( UArbBigInt::fromString("00001000 00000000 00000000", 2).bitLength() == 20 );
	REQUIRE( UArbBigInt::fromString("00010000 00000000 00000000", 2).bitLength() == 21 );
	REQUIRE( UArbBigInt::fromString("00100000 00000000 00000000", 2).bitLength() == 22 );
	REQUIRE( UArbBigInt::fromString("01000000 00000000 00000000", 2).bitLength() == 23 );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000", 2).bitLength() == 24 );

	// 9 byte
	REQUIRE( UArbBigInt::fromString("00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() ==  0 );
	REQUIRE( UArbBigInt::fromString("00000000 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 64 );
	REQUIRE( UArbBigInt::fromString("00000001 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 65 );
	REQUIRE( UArbBigInt::fromString("00000010 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 66 );
	REQUIRE( UArbBigInt::fromString("00000100 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 67 );
	REQUIRE( UArbBigInt::fromString("00001000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 68 );
	REQUIRE( UArbBigInt::fromString("00010000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 69 );
	REQUIRE( UArbBigInt::fromString("00100000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 70 );
	REQUIRE( UArbBigInt::fromString("01000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 71 );
	REQUIRE( UArbBigInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2).bitLength() == 72 );

	REQUIRE( UArbBigInt::fromString("00000000 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 57 );
	REQUIRE( UArbBigInt::fromString("00000000 10000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 64 );
	REQUIRE( UArbBigInt::fromString("00000001 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 65 );
	REQUIRE( UArbBigInt::fromString("00000011 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 66 );
	REQUIRE( UArbBigInt::fromString("00000111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 67 );
	REQUIRE( UArbBigInt::fromString("00001111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 68 );
	REQUIRE( UArbBigInt::fromString("00011111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 69 );
	REQUIRE( UArbBigInt::fromString("00111111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 70 );
	REQUIRE( UArbBigInt::fromString("01111111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 71 );
	REQUIRE( UArbBigInt::fromString("11111111 00000001 10000000 00011000 00000000 10000001 10000000 00000000 00000001", 2).bitLength() == 72 );

}

TEST_CASE( "unsigned infinit big integer randomNumber", "[UABigint]" ) {
	ppvr::math::Random rnd{};

	REQUIRE_THROWS (UArbBigInt::randomNumber(0, rnd));

	// randomNumber must return 1 or more
	REQUIRE( UArbBigInt::randomNumber(  1, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  2, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  3, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  3, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  2, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  1, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  1, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  2, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  3, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  3, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  2, rnd) >= UArbBigInt(1) );
	REQUIRE( UArbBigInt::randomNumber(  1, rnd) >= UArbBigInt(1) );

	// check max bit length
	// 1 Byte
	REQUIRE( UArbBigInt::randomNumber(  1, rnd).bitLength() <=   1 );
	REQUIRE( UArbBigInt::randomNumber(  2, rnd).bitLength() <=   2 );
	REQUIRE( UArbBigInt::randomNumber(  3, rnd).bitLength() <=   3 );
	REQUIRE( UArbBigInt::randomNumber(  4, rnd).bitLength() <=   4 );
	REQUIRE( UArbBigInt::randomNumber(  5, rnd).bitLength() <=   5 );
	REQUIRE( UArbBigInt::randomNumber(  6, rnd).bitLength() <=   6 );
	REQUIRE( UArbBigInt::randomNumber(  7, rnd).bitLength() <=   7 );
	REQUIRE( UArbBigInt::randomNumber(  8, rnd).bitLength() <=   8 );

	// 2 Byte
	REQUIRE( UArbBigInt::randomNumber(  9, rnd).bitLength() <=   9 );
	REQUIRE( UArbBigInt::randomNumber( 10, rnd).bitLength() <=  10 );
	REQUIRE( UArbBigInt::randomNumber( 11, rnd).bitLength() <=  11 );
	REQUIRE( UArbBigInt::randomNumber( 12, rnd).bitLength() <=  12 );
	REQUIRE( UArbBigInt::randomNumber( 13, rnd).bitLength() <=  13 );
	REQUIRE( UArbBigInt::randomNumber( 14, rnd).bitLength() <=  14 );
	REQUIRE( UArbBigInt::randomNumber( 15, rnd).bitLength() <=  15 );
	REQUIRE( UArbBigInt::randomNumber( 16, rnd).bitLength() <=  16 );

	// 3 Byte
	REQUIRE( UArbBigInt::randomNumber( 17, rnd).bitLength() <=  17 );
	REQUIRE( UArbBigInt::randomNumber( 18, rnd).bitLength() <=  18 );
	REQUIRE( UArbBigInt::randomNumber( 19, rnd).bitLength() <=  19 );
	REQUIRE( UArbBigInt::randomNumber( 20, rnd).bitLength() <=  20 );
	REQUIRE( UArbBigInt::randomNumber( 21, rnd).bitLength() <=  21 );
	REQUIRE( UArbBigInt::randomNumber( 22, rnd).bitLength() <=  22 );
	REQUIRE( UArbBigInt::randomNumber( 23, rnd).bitLength() <=  23 );
	REQUIRE( UArbBigInt::randomNumber( 24, rnd).bitLength() <=  24 );

	// 4 Byte
	REQUIRE( UArbBigInt::randomNumber( 25, rnd).bitLength() <=  25 );
	REQUIRE( UArbBigInt::randomNumber( 26, rnd).bitLength() <=  26 );
	REQUIRE( UArbBigInt::randomNumber( 27, rnd).bitLength() <=  27 );
	REQUIRE( UArbBigInt::randomNumber( 28, rnd).bitLength() <=  28 );
	REQUIRE( UArbBigInt::randomNumber( 29, rnd).bitLength() <=  29 );
	REQUIRE( UArbBigInt::randomNumber( 30, rnd).bitLength() <=  30 );
	REQUIRE( UArbBigInt::randomNumber( 31, rnd).bitLength() <=  31 );
	REQUIRE( UArbBigInt::randomNumber( 32, rnd).bitLength() <=  32 );

	// 8 Bytes
	REQUIRE( UArbBigInt::randomNumber( 60, rnd).bitLength() <=  60 );
	REQUIRE( UArbBigInt::randomNumber( 61, rnd).bitLength() <=  61 );
	REQUIRE( UArbBigInt::randomNumber( 62, rnd).bitLength() <=  62 );
	REQUIRE( UArbBigInt::randomNumber( 63, rnd).bitLength() <=  63 );
	REQUIRE( UArbBigInt::randomNumber( 64, rnd).bitLength() <=  64 );

	// 9 Byte
	REQUIRE( UArbBigInt::randomNumber( 65, rnd).bitLength() <=  65 );
	REQUIRE( UArbBigInt::randomNumber( 66, rnd).bitLength() <=  66 );
	REQUIRE( UArbBigInt::randomNumber( 67, rnd).bitLength() <=  67 );

	// 16 Byte
	REQUIRE( UArbBigInt::randomNumber(126, rnd).bitLength() <= 126 );
	REQUIRE( UArbBigInt::randomNumber(127, rnd).bitLength() <= 127 );
	REQUIRE( UArbBigInt::randomNumber(128, rnd).bitLength() <= 128 );

	// 17 Byte
	REQUIRE( UArbBigInt::randomNumber(129, rnd).bitLength() <= 129 );
	REQUIRE( UArbBigInt::randomNumber(130, rnd).bitLength() <= 130 );
	REQUIRE( UArbBigInt::randomNumber(131, rnd).bitLength() <= 131 );
	REQUIRE( UArbBigInt::randomNumber(132, rnd).bitLength() <= 132 );
	REQUIRE( UArbBigInt::randomNumber(133, rnd).bitLength() <= 133 );
	REQUIRE( UArbBigInt::randomNumber(134, rnd).bitLength() <= 134 );
	REQUIRE( UArbBigInt::randomNumber(135, rnd).bitLength() <= 135 );
	REQUIRE( UArbBigInt::randomNumber(136, rnd).bitLength() <= 136 );


	REQUIRE( UArbBigInt::randomNumber(1023, rnd).bitLength() <= 1023 );
	REQUIRE( UArbBigInt::randomNumber(1024, rnd).bitLength() <= 1024 );
	REQUIRE( UArbBigInt::randomNumber(1025, rnd).bitLength() <= 1025 );

	REQUIRE( UArbBigInt::randomNumber(2047, rnd).bitLength() <= 2047 );
	REQUIRE( UArbBigInt::randomNumber(2048, rnd).bitLength() <= 2048 );
	REQUIRE( UArbBigInt::randomNumber(2049, rnd).bitLength() <= 2049 );
}

TEST_CASE( "unsigned infinit big integer setBit", "[UABigint]" ) {
	REQUIRE( UArbBigInt::fromString("00000000", 2).withBit(0) == UArbBigInt::fromString("00000001", 2) );
	REQUIRE( UArbBigInt::fromString("00000000", 2).withBit(1) == UArbBigInt::fromString("00000010", 2) );
	REQUIRE( UArbBigInt::fromString("00000000", 2).withBit(2) == UArbBigInt::fromString("00000100", 2) );
	REQUIRE( UArbBigInt::fromString("00000000", 2).withBit(3) == UArbBigInt::fromString("00001000", 2) );
	REQUIRE( UArbBigInt::fromString("00000000", 2).withBit(4) == UArbBigInt::fromString("00010000", 2) );
	REQUIRE( UArbBigInt::fromString("00000000", 2).withBit(5) == UArbBigInt::fromString("00100000", 2) );
	REQUIRE( UArbBigInt::fromString("00000000", 2).withBit(6) == UArbBigInt::fromString("01000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000000", 2).withBit(7) == UArbBigInt::fromString("10000000", 2) );

	REQUIRE( UArbBigInt::fromString("10101010", 2).withBit(0) == UArbBigInt::fromString("10101011", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withBit(1) == UArbBigInt::fromString("10101010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withBit(2) == UArbBigInt::fromString("10101110", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withBit(3) == UArbBigInt::fromString("10101010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withBit(4) == UArbBigInt::fromString("10111010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withBit(5) == UArbBigInt::fromString("10101010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withBit(6) == UArbBigInt::fromString("11101010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withBit(7) == UArbBigInt::fromString("10101010", 2) );

	REQUIRE( UArbBigInt::fromString("    77 66 55 44 33 22 11 00", 16).withBit( 64) == UArbBigInt::fromString("                         01  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(  7) == UArbBigInt::fromString("                         88  77 66 55 44 33 22 11 80", 16) );
	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(127) == UArbBigInt::fromString("00  80 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(128) == UArbBigInt::fromString("01  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(129) == UArbBigInt::fromString("02  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(130) == UArbBigInt::fromString("04  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(131) == UArbBigInt::fromString("08  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(132) == UArbBigInt::fromString("10  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );

	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(191) == UArbBigInt::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(192) == UArbBigInt::fromString("01  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16).withBit(193) == UArbBigInt::fromString("02  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
}

TEST_CASE( "unsigned infinit big integer clearBit", "[UABigint]" ) {
	REQUIRE( UArbBigInt::fromString("00000001", 2).withoutBit(0) == UArbBigInt::fromString("00000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000010", 2).withoutBit(1) == UArbBigInt::fromString("00000000", 2) );
	REQUIRE( UArbBigInt::fromString("00000100", 2).withoutBit(2) == UArbBigInt::fromString("00000000", 2) );
	REQUIRE( UArbBigInt::fromString("00001000", 2).withoutBit(3) == UArbBigInt::fromString("00000000", 2) );
	REQUIRE( UArbBigInt::fromString("00010000", 2).withoutBit(4) == UArbBigInt::fromString("00000000", 2) );
	REQUIRE( UArbBigInt::fromString("00100000", 2).withoutBit(5) == UArbBigInt::fromString("00000000", 2) );
	REQUIRE( UArbBigInt::fromString("01000000", 2).withoutBit(6) == UArbBigInt::fromString("00000000", 2) );
	REQUIRE( UArbBigInt::fromString("10000000", 2).withoutBit(7) == UArbBigInt::fromString("00000000", 2) );

	REQUIRE( UArbBigInt::fromString("10101010", 2).withoutBit(0) == UArbBigInt::fromString("10101010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withoutBit(1) == UArbBigInt::fromString("10101000", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withoutBit(2) == UArbBigInt::fromString("10101010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withoutBit(3) == UArbBigInt::fromString("10100010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withoutBit(4) == UArbBigInt::fromString("10101010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withoutBit(5) == UArbBigInt::fromString("10001010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withoutBit(6) == UArbBigInt::fromString("10101010", 2) );
	REQUIRE( UArbBigInt::fromString("10101010", 2).withoutBit(7) == UArbBigInt::fromString("00101010", 2) );

	REQUIRE( UArbBigInt::fromString("                         01  77 66 55 44 33 22 11 00", 16).withoutBit( 64) == UArbBigInt::fromString("    77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("                         88  77 66 55 44 33 22 11 80", 16).withoutBit(  7) == UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("00  80 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(127) == UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("01  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(128) == UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("02  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(129) == UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("04  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(130) == UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("08  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(131) == UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("10  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(132) == UArbBigInt::fromString("88  77 66 55 44 33 22 11 00", 16) );

	REQUIRE( UArbBigInt::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(191) == UArbBigInt::fromString("                                                  88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("01  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(192) == UArbBigInt::fromString("                                                  88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("02  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(193) == UArbBigInt::fromString("                                                  88  77 66 55 44 33 22 11 00", 16) );
	REQUIRE( UArbBigInt::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).withoutBit(192) == UArbBigInt::fromString("02  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16) );
}

TEST_CASE( "unsigned infinit big integer isEven", "[UABigint]" ) {
	REQUIRE( UArbBigInt::fromString("10101010", 2).isEven() == true );
	REQUIRE( UArbBigInt::fromString("10101011", 2).isEven() == false );
	
	REQUIRE( UArbBigInt::fromString("254", 2).isEven() == true );
	REQUIRE( UArbBigInt::fromString("255", 2).isEven() == false );
	
	REQUIRE( UArbBigInt::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).isEven() == true );
	REQUIRE( UArbBigInt::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 01", 16).isEven() == false );
	REQUIRE( UArbBigInt::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 0a", 16).isEven() == true );
	REQUIRE( UArbBigInt::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 0d", 16).isEven() == false );
}

TEST_CASE( "unsigned infinit big integer isOdd", "[UABigint]" ) {
	REQUIRE( UArbBigInt::fromString("10101010", 2).isOdd() == false );
	REQUIRE( UArbBigInt::fromString("10101011", 2).isOdd() == true );
	
	REQUIRE( UArbBigInt::fromString("254", 2).isOdd() == false );
	REQUIRE( UArbBigInt::fromString("255", 2).isOdd() == true );
	
	REQUIRE( UArbBigInt::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 00", 16).isOdd() == false );
	REQUIRE( UArbBigInt::fromString("    80 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 01", 16).isOdd() == true );
	REQUIRE( UArbBigInt::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 0a", 16).isOdd() == false );
	REQUIRE( UArbBigInt::fromString("03  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 88  77 66 55 44 33 22 11 0d", 16).isOdd() == true );
}
