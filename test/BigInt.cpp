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

TEST_CASE( "big integer to std:string hex", "[bigint]" ) {
	// --- single byte big int creation ---
	
	REQUIRE( BigInt(0).toStringHex() == std::string("0") );
	REQUIRE( BigInt(1).toStringHex() == std::string("1") );
	REQUIRE( BigInt(2).toStringHex() == std::string("2") );
	REQUIRE( BigInt(3).toStringHex() == std::string("3") );
	REQUIRE( BigInt(4).toStringHex() == std::string("4") );
	REQUIRE( BigInt(5).toStringHex() == std::string("5") );
	REQUIRE( BigInt(6).toStringHex() == std::string("6") );
	REQUIRE( BigInt(7).toStringHex() == std::string("7") );
	REQUIRE( BigInt(8).toStringHex() == std::string("8") );
	REQUIRE( BigInt(9).toStringHex() == std::string("9") );
	REQUIRE( BigInt(10).toStringHex() == std::string("A") );
	REQUIRE( BigInt(11).toStringHex() == std::string("B") );
	REQUIRE( BigInt(12).toStringHex() == std::string("C") );
	REQUIRE( BigInt(13).toStringHex() == std::string("D") );
	REQUIRE( BigInt(14).toStringHex() == std::string("E") );
	REQUIRE( BigInt(15).toStringHex() == std::string("F") );
	REQUIRE( BigInt(16).toStringHex() == std::string("10") );
	
	REQUIRE( BigInt(66).toStringHex() == std::string("42") );
	REQUIRE( BigInt(127).toStringHex() == std::string("7F") );
	REQUIRE( BigInt(128).toStringHex() == std::string("80") );
	REQUIRE( BigInt(255).toStringHex() == std::string("FF") );
	
	// --- use 64 bit conversion for big int creation ---
	
	REQUIRE( BigInt::fromUint64(256).toStringHex() == std::string("100") );
	
	REQUIRE( BigInt::fromUint64(0xFFFFFFFF).toStringHex() == std::string("FFFFFFFF") ); // 2^32 - 1
	REQUIRE( BigInt::fromUint64(0x0100000000).toStringHex() == std::string("100000000") ); // 2^32
	REQUIRE( BigInt::fromUint64(0x0100000001).toStringHex() == std::string("100000001") ); // 2^32 + 1
	
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF).toStringHex() == std::string("FFFFFFFFFFFFFFFF") ); // 2^64 - 1
	REQUIRE( BigInt::fromUint64(0xFEDCBA9876543210).toStringHex() == std::string("FEDCBA9876543210") );
	REQUIRE( BigInt::fromUint64( 0xFEDCBA987654321).toStringHex() == std::string( "FEDCBA987654321") );
	REQUIRE( BigInt::fromUint64(  0xFEDCBA98765432).toStringHex() == std::string(  "FEDCBA98765432") );
	REQUIRE( BigInt::fromUint64(   0xFEDCBA9876543).toStringHex() == std::string(   "FEDCBA9876543") );
	REQUIRE( BigInt::fromUint64(    0xFEDCBA987654).toStringHex() == std::string(    "FEDCBA987654") );
	REQUIRE( BigInt::fromUint64(     0xFEDCBA98765).toStringHex() == std::string(     "FEDCBA98765") );
	REQUIRE( BigInt::fromUint64(      0xFEDCBA9876).toStringHex() == std::string(      "FEDCBA9876") );
	REQUIRE( BigInt::fromUint64(       0xFEDCBA987).toStringHex() == std::string(       "FEDCBA987") );
	REQUIRE( BigInt::fromUint64(        0xFEDCBA98).toStringHex() == std::string(        "FEDCBA98") );
	REQUIRE( BigInt::fromUint64(         0xFEDCBA9).toStringHex() == std::string(         "FEDCBA9") );
	REQUIRE( BigInt::fromUint64(          0xFEDCBA).toStringHex() == std::string(          "FEDCBA") );
	REQUIRE( BigInt::fromUint64(           0xFEDCB).toStringHex() == std::string(           "FEDCB") );
	REQUIRE( BigInt::fromUint64(            0xFEDC).toStringHex() == std::string(            "FEDC") );
	REQUIRE( BigInt::fromUint64(             0xFED).toStringHex() == std::string(             "FED") );
	REQUIRE( BigInt::fromUint64(              0xFE).toStringHex() == std::string(              "FE") );
	REQUIRE( BigInt::fromUint64(               0xF).toStringHex() == std::string(               "F") );
	REQUIRE( BigInt::fromUint64(               0x0).toStringHex() == std::string(               "0") );
	
	// 128 bit test!
	REQUIRE( BigInt::fromUint64(                    18446744073709551615ull).toStringHex()   == std::string(                 "FFFFFFFFFFFFFFFF") ); // 2^64 - 1
	REQUIRE((BigInt::fromUint64(                    18446744073709551615ull) + BigInt::ONE).toStringHex() == std::string(   "10000000000000000") ); // 2^64
	REQUIRE( BigInt::fromString(                   "18446744073709551615", 10).toStringHex() == std::string(                 "FFFFFFFFFFFFFFFF") ); // 2^64 - 1
	REQUIRE( BigInt::fromString(                   "18446744073709551616", 10).toStringHex() == std::string(                "10000000000000000") ); // 2^64
	REQUIRE( BigInt::fromString(                 "4722366482869645213696", 10).toStringHex() == std::string(              "1000000000000000000") ); // 2^72
	REQUIRE( BigInt::fromString(              "1208925819614629174706176", 10).toStringHex() == std::string(            "100000000000000000000") ); // 2^80
	REQUIRE( BigInt::fromString(            "309485009821345068724781056", 10).toStringHex() == std::string(          "10000000000000000000000") ); // 2^88
	REQUIRE( BigInt::fromString(          "79228162514264337593543950336", 10).toStringHex() == std::string(        "1000000000000000000000000") ); // 2^96
	REQUIRE( BigInt::fromString(       "20282409603651670423947251286016", 10).toStringHex() == std::string(      "100000000000000000000000000") ); // 2^104
	REQUIRE( BigInt::fromString(     "5192296858534827628530496329220096", 10).toStringHex() == std::string(    "10000000000000000000000000000") ); // 2^112
	REQUIRE( BigInt::fromString(  "1329227995784915872903807060280344576", 10).toStringHex() == std::string(  "1000000000000000000000000000000") ); // 2^120
	REQUIRE( BigInt::fromString(  "1329227995784915872903807060280344577", 10).toStringHex() == std::string(  "1000000000000000000000000000001") ); // 2^120 + 1
	REQUIRE( BigInt::fromString(  "1329227995784915872903807060280344591", 10).toStringHex() == std::string(  "100000000000000000000000000000F") ); // 2^120 + 15
	REQUIRE( BigInt::fromString("340282366920938463463374607431768211456", 10).toStringHex() == std::string("100000000000000000000000000000000") ); // 2^128
	REQUIRE( BigInt::fromString("340282366920938463463374607431768211457", 10).toStringHex() == std::string("100000000000000000000000000000001") ); // 2^128 + 1
	REQUIRE( BigInt::fromString("340282366920938463463374607431768211471", 10).toStringHex() == std::string("10000000000000000000000000000000F") ); // 2^128 + 15
	
	
	REQUIRE( BigInt::fromUint64(0x121fa00ad77d7422ull).toStringHex() 					== std::string( "121FA00AD77D7422") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422", 16).toStringHex() 					== std::string( "121FA00AD77D7422") );
	REQUIRE( BigInt::fromString( "121fa00ad77d74222", 16).toStringHex() 				== std::string( "121FA00AD77D74222") );
	REQUIRE( BigInt::fromString( "121fa00ad77d742223", 16).toStringHex() 				== std::string( "121FA00AD77D742223") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236", 16).toStringHex() 				== std::string( "121FA00AD77D7422236") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d", 16).toStringHex() 				== std::string( "121FA00AD77D7422236D") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d8", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D8") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88f", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88F") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe", 16).toStringHex() 			== std::string( "121FA00AD77D7422236D88FE") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE5") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe56", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE56") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe561", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE561") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618", 16).toStringHex() 		== std::string( "121FA00AD77D7422236D88FE5618") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618c", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618C") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618cf", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618CF") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618cf0", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618CF0") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618cf00", 16).toStringHex() 	== std::string( "121FA00AD77D7422236D88FE5618CF00") );
	
	REQUIRE( BigInt::fromUint64(                     1305938385386173474ull).toStringHex()   == std::string( "121FA00AD77D7422") );
	REQUIRE( BigInt::fromString(                    "1305938385386173474", 10).toStringHex() == std::string( "121FA00AD77D7422") );
	REQUIRE( BigInt::fromString(                   "20895014166178775586", 10).toStringHex() == std::string( "121FA00AD77D74222") );
	REQUIRE( BigInt::fromString(                  "334320226658860409379", 10).toStringHex() == std::string( "121FA00AD77D742223") );
	REQUIRE( BigInt::fromString(                 "5349123626541766550070", 10).toStringHex() == std::string( "121FA00AD77D7422236") );
	REQUIRE( BigInt::fromString(                "85585978024668264801133", 10).toStringHex() == std::string( "121FA00AD77D7422236D") );
	REQUIRE( BigInt::fromString(              "1369375648394692236818136", 10).toStringHex() == std::string( "121FA00AD77D7422236D8") );
	REQUIRE( BigInt::fromString(             "21910010374315075789090184", 10).toStringHex() == std::string( "121FA00AD77D7422236D88") );
	REQUIRE( BigInt::fromString(            "350560165989041212625442959", 10).toStringHex() == std::string( "121FA00AD77D7422236D88F") );
	REQUIRE( BigInt::fromString(           "5608962655824659402007087358", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE") );
	REQUIRE( BigInt::fromString(          "89743402493194550432113397733", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5") );
	REQUIRE( BigInt::fromString(        "1435894439891112806913814363734", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE56") );
	REQUIRE( BigInt::fromString(       "22974311038257804910621029819745", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE561") );
	REQUIRE( BigInt::fromString(      "367588976612124878569936477115928", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618") );
	REQUIRE( BigInt::fromString(     "5881423625793998057118983633854860", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618C") );
	REQUIRE( BigInt::fromString(    "94102778012703968913903738141677775", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618CF") );
	REQUIRE( BigInt::fromString(  "1505644448203263502622459810266844400", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618CF0") );
	REQUIRE( BigInt::fromString( "24090311171252216041959356964269510400", 10).toStringHex() == std::string( "121FA00AD77D7422236D88FE5618CF00") );
	
	// --------
	REQUIRE( BigInt::fromString("1e02bc1e8aa1d63b5b9ccf516f9d67d27b3c80b500001cbe991a08", 16).toStringHex()            == std::string("1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") );
	REQUIRE( BigInt::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10).toStringHex() == std::string("1E02BC1E8AA1D63B5B9CCF516F9D67D27B3C80B500001CBE991A08") );
	
	REQUIRE( BigInt::fromString("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000", 16).toStringHex()                == std::string("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000") ); // 39 Bytes => 312 bit
	REQUIRE( BigInt::fromString("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040", 10).toStringHex() == std::string("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000") );
}

TEST_CASE( "big integer to std:string dec", "[bigint]" ) {
	// --- single byte big int creation ---

	REQUIRE( BigInt(0).toStringDec() == std::string("0") );
	REQUIRE( BigInt(1).toStringDec() == std::string("1") );
	REQUIRE( BigInt(2).toStringDec() == std::string("2") );
	REQUIRE( BigInt(3).toStringDec() == std::string("3") );
	REQUIRE( BigInt(4).toStringDec() == std::string("4") );
	REQUIRE( BigInt(5).toStringDec() == std::string("5") );
	REQUIRE( BigInt(6).toStringDec() == std::string("6") );
	REQUIRE( BigInt(7).toStringDec() == std::string("7") );
	REQUIRE( BigInt(8).toStringDec() == std::string("8") );
	REQUIRE( BigInt(9).toStringDec() == std::string("9") );
	REQUIRE( BigInt(10).toStringDec() == std::string("10") );

	REQUIRE( BigInt(0x42).toStringDec() == std::string("66") );
	REQUIRE( BigInt(0x7F).toStringDec() == std::string("127") );
	REQUIRE( BigInt(0x80).toStringDec() == std::string("128") );
	REQUIRE( BigInt(0xFF).toStringDec() == std::string("255") );
	
	// --- use 64 bit conversion for big int creation ---
	
	REQUIRE( BigInt::fromUint64(256).toStringDec() == std::string("256") );
	
	REQUIRE( BigInt::fromUint64(0xFFFFFFFF).toStringDec() == std::string("4294967295") ); // 2^32 - 1
	REQUIRE( BigInt::fromUint64(0x0100000000).toStringDec() == std::string("4294967296") ); // 2^32
	REQUIRE( BigInt::fromUint64(0x0100000001).toStringDec() == std::string("4294967297") ); // 2^32 + 1
	
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF).toStringDec() == std::string("18446744073709551615") ); // 2^64 - 1
	
	// 128 bit test!
	REQUIRE( BigInt::fromUint64(                0xFFFFFFFFFFFFFFFF).toStringDec()      == std::string(                   "18446744073709551615") ); // 2^64 - 1
	REQUIRE( (BigInt::fromUint64(               0xFFFFFFFFFFFFFFFF) + BigInt::ONE).toStringDec() == std::string(         "18446744073709551616") ); // 2^64
	REQUIRE( BigInt::fromString(                 "FFFFFFFFFFFFFFFF", 16).toStringDec() == std::string(                   "18446744073709551615") ); // 2^64 - 1
	REQUIRE( BigInt::fromString(                "10000000000000000", 16).toStringDec() == std::string(                   "18446744073709551616") ); // 2^64
	REQUIRE( BigInt::fromString(              "1000000000000000000", 16).toStringDec() == std::string(                 "4722366482869645213696") ); // 2^72
	REQUIRE( BigInt::fromString(            "100000000000000000000", 16).toStringDec() == std::string(              "1208925819614629174706176") ); // 2^80
	REQUIRE( BigInt::fromString(          "10000000000000000000000", 16).toStringDec() == std::string(            "309485009821345068724781056") ); // 2^88
	REQUIRE( BigInt::fromString(        "1000000000000000000000000", 16).toStringDec() == std::string(          "79228162514264337593543950336") ); // 2^96
	REQUIRE( BigInt::fromString(      "100000000000000000000000000", 16).toStringDec() == std::string(       "20282409603651670423947251286016") ); // 2^104
	REQUIRE( BigInt::fromString(    "10000000000000000000000000000", 16).toStringDec() == std::string(     "5192296858534827628530496329220096") ); // 2^112
	REQUIRE( BigInt::fromString(  "1000000000000000000000000000000", 16).toStringDec() == std::string(  "1329227995784915872903807060280344576") ); // 2^120
	REQUIRE( BigInt::fromString(  "1000000000000000000000000000001", 16).toStringDec() == std::string(  "1329227995784915872903807060280344577") ); // 2^120 + 1
	REQUIRE( BigInt::fromString(  "100000000000000000000000000000F", 16).toStringDec() == std::string(  "1329227995784915872903807060280344591") ); // 2^120 + 15
	REQUIRE( BigInt::fromString("100000000000000000000000000000000", 16).toStringDec() == std::string("340282366920938463463374607431768211456") ); // 2^128
	REQUIRE( BigInt::fromString("100000000000000000000000000000001", 16).toStringDec() == std::string("340282366920938463463374607431768211457") ); // 2^128 + 1
	REQUIRE( BigInt::fromString("10000000000000000000000000000000F", 16).toStringDec() == std::string("340282366920938463463374607431768211471") ); // 2^128 + 15
	
	//REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618cf", 16).toStringDec() == std::string( "94102778012703968913903738141677775") );
	//REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618cf00", 16).toStringDec() == std::string( "24090311171252216041959356964269510400") );

	//REQUIRE( BigInt::fromString( "94102778012703968913903738141677775", 10).toStringDec() == std::string( "94102778012703968913903738141677775") );
	//REQUIRE( BigInt::fromString( "24090311171252216041959356964269510400", 10).toStringDec() == std::string( "24090311171252216041959356964269510400") );
	
	// --------
	REQUIRE( BigInt::fromUint64(0x121fa00ad77d7422ull).toStringDec()                         == std::string(                    "1305938385386173474") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422", 16).toStringDec()                       == std::string(                    "1305938385386173474") );
	REQUIRE( BigInt::fromString( "121fa00ad77d74222", 16).toStringDec()                      == std::string(                   "20895014166178775586") );
	REQUIRE( BigInt::fromString( "121fa00ad77d742223", 16).toStringDec()                     == std::string(                  "334320226658860409379") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236", 16).toStringDec()                    == std::string(                 "5349123626541766550070") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d", 16).toStringDec()                   == std::string(                "85585978024668264801133") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d8", 16).toStringDec()                  == std::string(              "1369375648394692236818136") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88", 16).toStringDec()                 == std::string(             "21910010374315075789090184") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88f", 16).toStringDec()                == std::string(            "350560165989041212625442959") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe", 16).toStringDec()               == std::string(           "5608962655824659402007087358") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5", 16).toStringDec()              == std::string(          "89743402493194550432113397733") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe56", 16).toStringDec()             == std::string(        "1435894439891112806913814363734") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe561", 16).toStringDec()            == std::string(       "22974311038257804910621029819745") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618", 16).toStringDec()           == std::string(      "367588976612124878569936477115928") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618c", 16).toStringDec()          == std::string(     "5881423625793998057118983633854860") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618cf", 16).toStringDec()         == std::string(    "94102778012703968913903738141677775") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618cf0", 16).toStringDec()        == std::string(  "1505644448203263502622459810266844400") );
	REQUIRE( BigInt::fromString( "121fa00ad77d7422236d88fe5618cf00", 16).toStringDec()       == std::string( "24090311171252216041959356964269510400") );
	
	REQUIRE( BigInt::fromUint64(                     1305938385386173474ull  ).toStringDec() == std::string(                    "1305938385386173474") );
	REQUIRE( BigInt::fromString(                    "1305938385386173474", 10).toStringDec() == std::string(                    "1305938385386173474") );
	REQUIRE( BigInt::fromString(                   "20895014166178775586", 10).toStringDec() == std::string(                   "20895014166178775586") );
	REQUIRE( BigInt::fromString(                  "334320226658860409379", 10).toStringDec() == std::string(                  "334320226658860409379") );
	REQUIRE( BigInt::fromString(                 "5349123626541766550070", 10).toStringDec() == std::string(                 "5349123626541766550070") );
	REQUIRE( BigInt::fromString(                "85585978024668264801133", 10).toStringDec() == std::string(                "85585978024668264801133") );
	REQUIRE( BigInt::fromString(              "1369375648394692236818136", 10).toStringDec() == std::string(              "1369375648394692236818136") );
	REQUIRE( BigInt::fromString(             "21910010374315075789090184", 10).toStringDec() == std::string(             "21910010374315075789090184") );
	REQUIRE( BigInt::fromString(            "350560165989041212625442959", 10).toStringDec() == std::string(            "350560165989041212625442959") );
	REQUIRE( BigInt::fromString(           "5608962655824659402007087358", 10).toStringDec() == std::string(           "5608962655824659402007087358") );
	REQUIRE( BigInt::fromString(          "89743402493194550432113397733", 10).toStringDec() == std::string(          "89743402493194550432113397733") );
	REQUIRE( BigInt::fromString(        "1435894439891112806913814363734", 10).toStringDec() == std::string(        "1435894439891112806913814363734") );
	REQUIRE( BigInt::fromString(       "22974311038257804910621029819745", 10).toStringDec() == std::string(       "22974311038257804910621029819745") );
	REQUIRE( BigInt::fromString(      "367588976612124878569936477115928", 10).toStringDec() == std::string(      "367588976612124878569936477115928") );
	REQUIRE( BigInt::fromString(     "5881423625793998057118983633854860", 10).toStringDec() == std::string(     "5881423625793998057118983633854860") );
	REQUIRE( BigInt::fromString(    "94102778012703968913903738141677775", 10).toStringDec() == std::string(    "94102778012703968913903738141677775") );
	REQUIRE( BigInt::fromString(  "1505644448203263502622459810266844400", 10).toStringDec() == std::string(  "1505644448203263502622459810266844400") );
	REQUIRE( BigInt::fromString( "24090311171252216041959356964269510400", 10).toStringDec() == std::string( "24090311171252216041959356964269510400") );
	
	// --------
	REQUIRE( BigInt::fromString("1e02bc1e8aa1d63b5b9ccf516f9d67d27b3c80b500001cbe991a08", 16).toStringDec()            == std::string("12345678900000000000000000000000000000000000000000000123456789000") );
	REQUIRE( BigInt::fromString("12345678900000000000000000000000000000000000000000000123456789000", 10).toStringDec() == std::string("12345678900000000000000000000000000000000000000000000123456789000") );
	
	REQUIRE( BigInt::fromString("123456789ABCDEF00000000000000000000000000000000000000000000123456789ABCDEF000", 16).toStringDec()                == std::string("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040") ); // 39 Bytes => 312 bit
	REQUIRE( BigInt::fromString("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040", 10).toStringDec() == std::string("37083108262515799557102920138478281554203075264980329467169710128521593951634998575520215040") );
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
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(1)) 		>=  BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) );
	
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::TEN) 	!= (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::TEN) 	== (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(10)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::TEN)		<  (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::TEN)		<= (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) 		>  (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(10)) );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) 		>= (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(10)) );
	
	//REQUIRE( (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) 		!=  (BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt(11)) );
}

TEST_CASE( "big integer addition", "[bigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (BigInt(  0) + BigInt(  0)).toUint64()	==   0 );
	REQUIRE( (BigInt(  1) + BigInt(  0)).toUint64()	==   1 );
	REQUIRE( (BigInt(  0) + BigInt(  1)).toUint64()	==   1 );
	REQUIRE( (BigInt(  1) + BigInt(  1)).toUint64()	==   2 );
	REQUIRE( (BigInt(  2) + BigInt(  1)).toUint64()	==   3 );
	REQUIRE( (BigInt(  1) + BigInt(  2)).toUint64()	==   3 );
	REQUIRE( (BigInt( 10) + BigInt(  1)).toUint64()	==  11 );
	REQUIRE( (BigInt(128) + BigInt(127)).toUint64()	== 255 );
	
	// 2 Bytes (16 bit)
	REQUIRE( (BigInt(128) + BigInt(128).toUint64()).toUint64()	== 0x0100ull );
	REQUIRE( (BigInt(255) + BigInt(  1).toUint64()).toUint64()	== 0x0100ull );
	REQUIRE( (BigInt(  1) + BigInt(255).toUint64()).toUint64()	== 0x0100ull );
	REQUIRE( (BigInt(255) + BigInt(255).toUint64()).toUint64()	== 0x01FEull );
	
	REQUIRE( (BigInt::fromUint64(0x7FFF) + BigInt::fromUint64(0x7FFF) 				).toUint64() == 0xFFFEull );
	REQUIRE( (BigInt::fromUint64(0x7FFF) + BigInt::fromUint64(0x7FFF) + BigInt(0)	).toUint64() == 0xFFFEull );
	REQUIRE( (BigInt::fromUint64(0x7FFF) + BigInt::fromUint64(0x7FFF) + BigInt(1) 	).toUint64() == 0xFFFFull );
	REQUIRE( (BigInt(1) + BigInt::fromUint64(0x7FFF) + BigInt::fromUint64(0x7FFF) 	).toUint64() == 0xFFFFull );
	
	// 4 Bytes (32bit)
	REQUIRE( (BigInt::fromUint64(0x8000) + BigInt::fromUint64(0x8000)).toUint64() 	== 0x010000ull );
	REQUIRE( (BigInt::fromUint64(0xFFFF) + BigInt::fromUint64(  0x01)).toUint64() 	== 0x010000ull );
	REQUIRE( (BigInt::fromUint64(  0x01) + BigInt::fromUint64(0xFFFF)).toUint64() 	== 0x010000ull );
	REQUIRE( (BigInt::fromUint64(0xFFFF) + BigInt::fromUint64(0xFFFF)).toUint64() 	== 0x01FFFEull );
	
	REQUIRE( (BigInt::fromUint64(0x7FFFFFFF) + BigInt::fromUint64(0x7FFFFFFF) 				).toUint64() == 0xFFFFFFFEull );
	REQUIRE( (BigInt::fromUint64(0x7FFFFFFF) + BigInt::fromUint64(0x7FFFFFFF) + BigInt(0) 	).toUint64() == 0xFFFFFFFEull );
	REQUIRE( (BigInt::fromUint64(0x7FFFFFFF) + BigInt::fromUint64(0x7FFFFFFF) + BigInt(1) 	).toUint64() == 0xFFFFFFFFull );
	REQUIRE( (BigInt(1) + BigInt::fromUint64(0x7FFFFFFF) + BigInt::fromUint64(0x7FFFFFFF) 	).toUint64() == 0xFFFFFFFFull );
	
	// 8 Bytes (64bit)
	REQUIRE( (BigInt::fromUint64(0x80000000) + BigInt::fromUint64(0x80000000)).toUint64() 	== 0x0100000000ull );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFF) + BigInt::fromUint64(      0x01)).toUint64() 	== 0x0100000000ull );
	REQUIRE( (BigInt::fromUint64(      0x01) + BigInt::fromUint64(0xFFFFFFFF)).toUint64() 	== 0x0100000000ull );
	REQUIRE( (BigInt::fromUint64(0xFFFFFFFF) + BigInt::fromUint64(0xFFFFFFFF)).toUint64() 	== 0x01FFFFFFFEull );
	
	REQUIRE( (BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) 				).toUint64() == 0xFFFFFFFFFFFFFFFEull );
	REQUIRE( (BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt(0)	).toUint64() == 0xFFFFFFFFFFFFFFFEull );
	REQUIRE( (BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt(1)	).toUint64() == 0xFFFFFFFFFFFFFFFFull );
	REQUIRE( (BigInt(1) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF) + BigInt::fromUint64(0x7FFFFFFFFFFFFFFF)	).toUint64() == 0xFFFFFFFFFFFFFFFFull );
	
	// 16 Bytes (128bit)
	REQUIRE( BigInt::fromString("18446744073709551616", 10) == (BigInt::fromUint64(0xFFFFFFFFFFFFFFFFull) + BigInt::ONE) ); // 2^64
	
	REQUIRE( BigInt::fromUint64(0x8000000000000000) + BigInt::fromUint64(0x8000000000000000) 	== BigInt::fromString("18446744073709551616", 10) ); // 2^64
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::fromUint64(              0x01) 	== BigInt::fromString("010000000000000000", 16) ); // 2^64
	REQUIRE( BigInt::fromUint64(              0x01) + BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 	== BigInt::fromString("010000000000000000", 16) ); // 2^64
	REQUIRE( BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) + BigInt::fromUint64(0xFFFFFFFFFFFFFFFF) 	== BigInt::fromString("01FFFFFFFFFFFFFFFE", 16) );
	
	REQUIRE( BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) 				== BigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE", 16) );
	REQUIRE( BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt(0)	== BigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE", 16) );
	REQUIRE( BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt(1)	== BigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) );
	REQUIRE( BigInt(1) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) + BigInt::fromString("7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16)	== BigInt::fromString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) );
	
	
	REQUIRE( BigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) + BigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) == BigInt::fromString("ffffffffffffffff0000000000000011111111111111100", 16) );
	REQUIRE( BigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) + BigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) == BigInt::fromString("FFFFFFFFFFFFFFFF0000000000000011111111111111100", 16) );
	
	REQUIRE( BigInt::fromString("123456789000000000000000000000000000001234567890", 10) + BigInt::fromString("987654321000000000000000000000000000009876543210", 10) == BigInt::fromString("1111111110000000000000000000000000000011111111100", 10) );
	REQUIRE( BigInt::fromString("987654321000000000000000000000000000009876543210", 10) + BigInt::fromString("123456789000000000000000000000000000001234567890", 10) == BigInt::fromString("1111111110000000000000000000000000000011111111100", 10) );
}

TEST_CASE( "big integer subtraction", "[bigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (BigInt(  0) - BigInt(  0)).toUint64() ==   0 );
	REQUIRE( (BigInt(  1) - BigInt(  0)).toUint64() ==   1 );
	REQUIRE( (BigInt(  1) - BigInt(  1)).toUint64() ==   0 );
	
	REQUIRE( (BigInt(  9) - BigInt(  1)).toUint64() ==   8 );
	REQUIRE( (BigInt(  9) - BigInt(  9)).toUint64() ==   0 );
	REQUIRE( (BigInt( 10) - BigInt(  9)).toUint64() ==   1 );
	REQUIRE( (BigInt(255) - BigInt(  0)).toUint64() == 255 );
	REQUIRE( (BigInt(255) - BigInt(255)).toUint64() ==   0 );
	REQUIRE( (BigInt(255) - BigInt( 1)).toUint64() 	== 254 );
	
	// 2 Bytes (16 bit)
	REQUIRE( (BigInt::fromUint64(0x0100ull) - BigInt::fromUint64(0x0100ull)).toUint64() ==   0x00ull ); // 256 - 256 = 0
	REQUIRE( (BigInt::fromUint64(0x0101ull) - BigInt::fromUint64(0x0100ull)).toUint64() ==   0x01ull ); // 257 - 256 = 1
	REQUIRE( (BigInt::fromUint64(0x0101ull) - BigInt::fromUint64(  0x01ull)).toUint64() == 0x0100ull ); // 257 - 1 = 256
	REQUIRE( (BigInt::fromUint64(0x0101ull) - BigInt::fromUint64(  0x02ull)).toUint64() ==   0xFFull ); // 257 - 2 = 255
	
	// 4 Bytes (32bit)
	REQUIRE( (BigInt::fromUint64(0x010000ull) - BigInt::fromUint64(0x010000ull)).toUint64() ==     0x00ull ); // 2^16 - 2^16 = 0
	REQUIRE( (BigInt::fromUint64(0x010001ull) - BigInt::fromUint64(0x010000ull)).toUint64() ==     0x01ull ); // (2^16 + 1) - 2^16 = 1
	REQUIRE( (BigInt::fromUint64(0x010001ull) - BigInt::fromUint64(    0x01ull)).toUint64() == 0x010000ull ); // (2^16 + 1) - 1 = 2^16
	REQUIRE( (BigInt::fromUint64(0x010001ull) - BigInt::fromUint64(    0x02ull)).toUint64() == 0x00FFFFull ); // (2^16 + 1) - 2 = 2^16 - 1
	
	// 8 Bytes (64bit)
	REQUIRE( (BigInt::fromUint64(0x0100000000ull) - BigInt::fromUint64(0x0100000000ull)).toUint64() 	==         0x00ull ); // 2^32 - 2^32 = 0
	REQUIRE( (BigInt::fromUint64(0x0100000001ull) - BigInt::fromUint64(0x0100000000ull)).toUint64() 	==         0x01ull ); // (2^32 + 1) - 2^32 = 1
	REQUIRE( (BigInt::fromUint64(0x0100000001ull) - BigInt::fromUint64(        0x01ull)).toUint64() 	== 0x0100000000ull ); // (2^32 + 1) - 1 = 2^32
	REQUIRE( (BigInt::fromUint64(0x0100000001ull) - BigInt::fromUint64(        0x02ull)).toUint64() 	== 0x00FFFFFFFFull ); // (2^32 + 1) - 2 = 2^32 - 1
	
	// 16 Bytes (128bit)
	REQUIRE( BigInt::fromString("010000000000000000", 16) - BigInt::fromString("010000000000000000", 16) 	== 							  BigInt(0x00)      ); // 2^64 - 2^64 = 0
	REQUIRE( BigInt::fromString("010000000000000001", 16) - BigInt::fromString("010000000000000000", 16) 	==                            BigInt(0x01)      ); // (2^64 + 1) - 2^64 = 1
	REQUIRE( BigInt::fromString("010000000000000001", 16) - BigInt::fromUint64(               0x01ull)	 	== BigInt::fromString("010000000000000000", 16) ); // (2^64 + 1) - 1 = 2^64
	REQUIRE( BigInt::fromString("010000000000000001", 16) - BigInt::fromUint64(               0x02ull)		== BigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull)   ); // (2^64 + 1) - 2 = 2^64 - 1
	
	REQUIRE( BigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) - BigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) == BigInt::fromString("fdb97530eca86421000000000000000eca8641fdb975320", 16) );
	REQUIRE( BigInt::fromString("987654321000000000000000000000000000009876543210", 10) - BigInt::fromString("123456789000000000000000000000000000001234567890", 10) == BigInt::fromString("864197532000000000000000000000000000008641975320", 10) );
}

TEST_CASE( "big integer multiplication", "[bigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (BigInt(  0) * BigInt(0)).toUint64() ==   0 );
	REQUIRE( (BigInt(  1) * BigInt(0)).toUint64() ==   0 );
	REQUIRE( (BigInt(  1) * BigInt(1)).toUint64() ==   1 );
	REQUIRE( (BigInt(  2) * BigInt(1)).toUint64() ==   2 );
	REQUIRE( (BigInt(  1) * BigInt(2)).toUint64() ==   2 );
	REQUIRE( (BigInt( 10) * BigInt(0)).toUint64() ==   0 );
	REQUIRE( (BigInt( 11) * BigInt(2)).toUint64() ==  22 );
	REQUIRE( (BigInt(127) * BigInt(2)).toUint64() == 254 );
	
	// 2 Bytes (16 bit)
	REQUIRE( (BigInt(128) * BigInt(              2)).toUint64() == 0x0100ull );
	REQUIRE( (BigInt(128) * BigInt(              4)).toUint64() == 0x0200ull );
	REQUIRE( (BigInt(123) * BigInt::fromUint64(532)).toUint64() == 0xFF9Cull );
	REQUIRE( (BigInt( 98) * BigInt::fromUint64(571)).toUint64() == 0xDA96ull );
	
	REQUIRE( (BigInt::fromUint64(0x0100ull) * BigInt::fromUint64(0x0FFull)).toUint64() == 0xFF00ull );
	REQUIRE( (BigInt::fromUint64(0x0011ull) * BigInt::fromUint64(0x0FFull)).toUint64() == 0x10EFull );
	
	// 4 Bytes (32bit)
	REQUIRE( (BigInt::fromUint64(    0xFFFFull) * BigInt::fromUint64( 0xFFFFull)).toUint64() == 0xFFFE0001ull );
	
	REQUIRE( (BigInt::fromUint64(    0x0100ull) * BigInt::fromUint64( 0x0100ull)).toUint64() ==   0x010000ull );
	REQUIRE( (BigInt::fromUint64(    0x0100ull) * BigInt::fromUint64( 0x0F00ull)).toUint64() ==   0x0F0000ull );
	
	REQUIRE( (BigInt::fromUint64(0x55555555ull) * BigInt::fromUint64(  0x003ull)).toUint64() == 0xFFFFFFFFull );
	REQUIRE( (BigInt::fromUint64(    0xEFEFull) * BigInt::fromUint64(   0xEFull)).toUint64() ==   0xE00021ull );
	REQUIRE( (BigInt::fromUint64(    0xEFEFull) * BigInt::fromUint64( 0xEFEFull)).toUint64() == 0xE0E02121ull );
	
	REQUIRE( (BigInt::fromUint64(0xff9Cull) * BigInt::fromUint64(  0x7Bull)).toUint64() == 0x7ACFF4ull ); // 65436 * 123 = 8048628
	
	// 8 Bytes (64bit)
	REQUIRE( (BigInt::fromUint64(    0xFFFFFFFFull) * BigInt::fromUint64( 0xFFFFFFFFull)).toUint64() == 0xFFFFFFFE00000001ull );
	REQUIRE( (BigInt::fromUint64(    0xFFFFFFFFull) * BigInt::fromUint64(       0x02ull)).toUint64() ==        0x1FFFFFFFEull );
	REQUIRE( (BigInt::fromUint64(    0xFEDCBA98ull) * BigInt::fromUint64( 0x12345678ull)).toUint64() == 0x121FA00A35068740ull );
	REQUIRE( (BigInt::fromUint64(    0xFEDCBA98ull) * BigInt::fromUint64( 0x12345678ull)).toUint64() == 0xFEDCBA98ull * 0x12345678ull);
	
	// 16 Bytes (128bit)
	REQUIRE( BigInt::fromUint64(    0xFFFFFFFFFFFFFFFFull) * BigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull) == BigInt::fromString("FFFFFFFFFFFFFFFE0000000000000001", 16) );
	REQUIRE( BigInt::fromUint64(    0xFFFFFFFFFFFFFFFFull) * BigInt::fromUint64(               0x02ull) == BigInt::fromString(               "1FFFFFFFFFFFFFFFE", 16) );
	REQUIRE( BigInt::fromUint64(    0xFEDCBA9876543210ull) * BigInt::fromUint64( 0x123456789ABCDEF0ull) == BigInt::fromString("24090311171252216041959356964269510400", 10) ); // 18364758544493064720 * 1311768467463790320 = 24090311171252216041959356964269510400
	REQUIRE( BigInt::fromUint64(    0xFEDCBA9876543210ull) * BigInt::fromUint64( 0x123456789ABCDEF0ull) == BigInt::fromString("121fa00ad77d7422236d88fe5618cf00", 16) ); // 18364758544493064720 * 1311768467463790320 = 24090311171252216041959356964269510400
	REQUIRE( (BigInt::fromUint64(    0xFEDCBA9876543210ull) * BigInt::fromUint64( 0x123456789ABCDEF0ull)).toStringDec() == std::string("24090311171252216041959356964269510400") ); // 18364758544493064720 * 1311768467463790320 = 24090311171252216041959356964269510400
	
	// -------
	REQUIRE( BigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) *  BigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) == BigInt::fromString("121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16) );
	REQUIRE( BigInt::fromString("fedcba9876543210000000000000000fedcba9876543210", 16) *  BigInt::fromString("123456789abcdef000000000000000123456789abcdef0", 16) == BigInt::fromString("121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16) );
	
	REQUIRE( BigInt::fromString("123456789000000000000000000000000000001234567890", 10) *  BigInt::fromString("987654321000000000000000000000000000009876543210", 10) == BigInt::fromString("121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) );
	REQUIRE( BigInt::fromString("987654321000000000000000000000000000009876543210", 10) *  BigInt::fromString("123456789000000000000000000000000000001234567890", 10) == BigInt::fromString("121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) );
}

TEST_CASE( "big integer division", "[bigint]" ) {
	// 1 Byte (8bit)
	REQUIRE( (BigInt(  0) / BigInt(  1)).toUint64() ==   0 );
	REQUIRE( (BigInt(  0) % BigInt(  1)).toUint64() ==   0 );
	REQUIRE( (BigInt(  1) / BigInt(  1)).toUint64() ==   1 );
	REQUIRE( (BigInt(  1) % BigInt(  1)).toUint64() ==   0 );
	REQUIRE( (BigInt(  1) / BigInt(  2)).toUint64() ==   0 );
	REQUIRE( (BigInt(  1) % BigInt(  2)).toUint64() ==   1 );
	REQUIRE( (BigInt(  2) / BigInt(  1)).toUint64() ==   2 );
	REQUIRE( (BigInt(  2) % BigInt(  1)).toUint64() ==   0 );
	REQUIRE( (BigInt(  2) / BigInt(  2)).toUint64() ==   1 );
	REQUIRE( (BigInt(  2) % BigInt(  2)).toUint64() ==   0 );
	REQUIRE( (BigInt(  4) / BigInt(  2)).toUint64() ==   2 );
	REQUIRE( (BigInt(  4) % BigInt(  2)).toUint64() ==   0 );
	REQUIRE( (BigInt( 10) / BigInt(  1)).toUint64() ==  10 );
	REQUIRE( (BigInt( 10) % BigInt(  1)).toUint64() ==   0 );
	REQUIRE( (BigInt( 10) / BigInt(  2)).toUint64() ==   5 );
	REQUIRE( (BigInt( 10) % BigInt(  2)).toUint64() ==   0 );
	REQUIRE( (BigInt( 10) / BigInt(  3)).toUint64() ==   3 );
	REQUIRE( (BigInt( 10) % BigInt(  3)).toUint64() ==   1 );
	REQUIRE( (BigInt( 10) / BigInt(  5)).toUint64() ==   2 );
	REQUIRE( (BigInt( 10) % BigInt(  5)).toUint64() ==   0 );
	REQUIRE( (BigInt( 11) / BigInt(  2)).toUint64() ==   5 );
	REQUIRE( (BigInt( 11) % BigInt(  2)).toUint64() ==   1 );
	REQUIRE( (BigInt( 12) / BigInt(  2)).toUint64() ==   6 );
	REQUIRE( (BigInt( 12) % BigInt(  2)).toUint64() ==   0 );
	REQUIRE( (BigInt(252) / BigInt(  2)).toUint64() == 126 );
	REQUIRE( (BigInt(252) % BigInt(  2)).toUint64() ==   0 );
	REQUIRE( (BigInt(253) / BigInt(  2)).toUint64() == 126 );
	REQUIRE( (BigInt(253) % BigInt(  2)).toUint64() ==   1 );
	REQUIRE( (BigInt(254) / BigInt(  2)).toUint64() == 127 );
	REQUIRE( (BigInt(254) % BigInt(  2)).toUint64() ==   0 );
	REQUIRE( (BigInt(255) / BigInt(  2)).toUint64() == 127 );
	REQUIRE( (BigInt(255) % BigInt(  2)).toUint64() ==   1 );
	REQUIRE( (BigInt(255) / BigInt(255)).toUint64() ==   1 );
	REQUIRE( (BigInt(255) % BigInt(255)).toUint64() ==   0 );
	REQUIRE( (BigInt(254) / BigInt(127)).toUint64() ==   2 );
	REQUIRE( (BigInt(254) % BigInt(127)).toUint64() ==   0 );
	REQUIRE( (BigInt(255) / BigInt(127)).toUint64() ==   2 );
	REQUIRE( (BigInt(255) % BigInt(127)).toUint64() ==   1 );
	
	
	// 2 Bytes (16 bit)
	REQUIRE( (BigInt::fromUint64(0x0100ull) / BigInt(                2)).toUint64() ==   128);
	REQUIRE( (BigInt::fromUint64(0x0100ull) % BigInt(                2)).toUint64() ==     0);
	REQUIRE( (BigInt::fromUint64(0x0200ull) / BigInt(                4)).toUint64() ==   128);
	REQUIRE( (BigInt::fromUint64(0x0200ull) % BigInt(                4)).toUint64() ==     0);
	REQUIRE( (BigInt::fromUint64(0x0100ull) / BigInt::fromUint64(0x100)).toUint64() ==     1);
	REQUIRE( (BigInt::fromUint64(0x0100ull) % BigInt::fromUint64(0x100)).toUint64() ==     0);
	REQUIRE( (BigInt::fromUint64(0x0200ull) / BigInt::fromUint64(0x100)).toUint64() ==     2);
	REQUIRE( (BigInt::fromUint64(0x0200ull) % BigInt::fromUint64(0x100)).toUint64() ==     0);
	REQUIRE( (BigInt::fromUint64(0x0200ull) / BigInt::fromUint64(0x200)).toUint64() ==     1);
	REQUIRE( (BigInt::fromUint64(0x0200ull) % BigInt::fromUint64(0x200)).toUint64() ==     0);
	REQUIRE( (BigInt::fromUint64(0x0300ull) / BigInt::fromUint64(0x200)).toUint64() ==     1);
	REQUIRE( (BigInt::fromUint64(0x0300ull) % BigInt::fromUint64(0x200)).toUint64() == 0x100);
	REQUIRE( (BigInt::fromUint64(0x0400ull) / BigInt::fromUint64(0x200)).toUint64() ==     2);
	REQUIRE( (BigInt::fromUint64(0x0400ull) % BigInt::fromUint64(0x200)).toUint64() ==     0);
	REQUIRE( (BigInt::fromUint64(0xFF9Cull) / BigInt::fromUint64(0x100)).toUint64() ==  0xff);
	REQUIRE( (BigInt::fromUint64(0xFF9Cull) % BigInt::fromUint64(0x100)).toUint64() ==  0x9C);
	REQUIRE( (BigInt::fromUint64(0xFF9Cull) / BigInt::fromUint64(  532)).toUint64() ==   123);
	REQUIRE( (BigInt::fromUint64(0xFF9Cull) % BigInt::fromUint64(  532)).toUint64() ==     0);
	REQUIRE( (BigInt::fromUint64(0xDA96ull) / BigInt::fromUint64(  571)).toUint64() ==    98);
	REQUIRE( (BigInt::fromUint64(0xDA96ull) % BigInt::fromUint64(  571)).toUint64() ==     0);
	
	REQUIRE( (BigInt::fromUint64(0xFF00ull) / BigInt::fromUint64(0x0FFull)).toUint64() == 0x0100ull );
	REQUIRE( (BigInt::fromUint64(0xFF00ull) % BigInt::fromUint64(0x0FFull)).toUint64() ==      0ull );
	REQUIRE( (BigInt::fromUint64(0x10EFull) / BigInt::fromUint64(0x0FFull)).toUint64() == 0x0011ull );
	REQUIRE( (BigInt::fromUint64(0x10EFull) % BigInt::fromUint64(0x0FFull)).toUint64() ==      0ull );
	
	// 4 Bytes (32bit)
	REQUIRE( (BigInt::fromUint64( 0xFFFE0001ull) / BigInt::fromUint64( 0xFFFFull)).toUint64() ==     0xFFFFull ); // first test of D5. [Test Remainder] and D6. [add back] (at 8bit words)
	REQUIRE( (BigInt::fromUint64( 0xFFFE0001ull) % BigInt::fromUint64( 0xFFFFull)).toUint64() ==          0ull );
	
	REQUIRE( (BigInt::fromUint64(   0x010000ull) / BigInt::fromUint64( 0x0100ull)).toUint64() ==     0x0100ull );
	REQUIRE( (BigInt::fromUint64(   0x010000ull) % BigInt::fromUint64( 0x0100ull)).toUint64() ==          0ull );
	REQUIRE( (BigInt::fromUint64(   0x0F0000ull) / BigInt::fromUint64( 0x0F00ull)).toUint64() ==     0x0100ull );
	REQUIRE( (BigInt::fromUint64(   0x0F0000ull) % BigInt::fromUint64( 0x0F00ull)).toUint64() ==          0ull );
	
	REQUIRE( (BigInt::fromUint64( 0xFFFFFFFFull) / BigInt::fromUint64(  0x003ull)).toUint64() == 0x55555555ull );
	REQUIRE( (BigInt::fromUint64( 0xFFFFFFFFull) % BigInt::fromUint64(  0x003ull)).toUint64() ==          0ull );
	REQUIRE( (BigInt::fromUint64(   0xE00021ull) / BigInt::fromUint64(   0xEFull)).toUint64() ==     0xEFEFull );
	REQUIRE( (BigInt::fromUint64(   0xE00021ull) % BigInt::fromUint64(   0xEFull)).toUint64() ==          0ull );
	REQUIRE( (BigInt::fromUint64( 0xE0E02121ull) / BigInt::fromUint64( 0xEFEFull)).toUint64() ==     0xEFEFull );
	REQUIRE( (BigInt::fromUint64( 0xE0E02121ull) % BigInt::fromUint64( 0xEFEFull)).toUint64() ==          0ull );
	
	// 8 Bytes (64bit)
	REQUIRE( (BigInt::fromUint64(          0xFFFFFFFE00000001ull) / BigInt::fromUint64( 0xFFFFFFFFull)).toUint64() == 0xFFFFFFFFull ); // test of D5. [Test Remainder] and D6. [add back] (at 8bit words)
	REQUIRE( (BigInt::fromUint64(          0xFFFFFFFE00000001ull) % BigInt::fromUint64( 0xFFFFFFFFull)).toUint64() ==          0ull );
	
	REQUIRE( (BigInt::fromUint64(                 0x1FFFFFFFEull) / BigInt::fromUint64(       0x02ull)).toUint64() == 0xFFFFFFFFull );
	REQUIRE( (BigInt::fromUint64(                 0x1FFFFFFFEull) % BigInt::fromUint64(       0x02ull)).toUint64() ==          0ull );
	REQUIRE( (BigInt::fromUint64(          0x121FA00A35068740ull) / BigInt::fromUint64( 0x12345678ull)).toUint64() == 0xFEDCBA98ull );
	REQUIRE( (BigInt::fromUint64(          0x121FA00A35068740ull) % BigInt::fromUint64( 0x12345678ull)).toUint64() ==          0ull );
	REQUIRE( (BigInt::fromUint64(  0xFEDCBA98ull * 0x12345678ull) / BigInt::fromUint64( 0x12345678ull)).toUint64() == 0xFEDCBA98ull );
	REQUIRE( (BigInt::fromUint64(  0xFEDCBA98ull * 0x12345678ull) % BigInt::fromUint64( 0x12345678ull)).toUint64() ==          0ull );
	
	// 16 Bytes (128bit)
	REQUIRE( BigInt::fromString(       "FFFFFFFFFFFFFFFE0000000000000001", 16) / BigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull) == BigInt::fromUint64(    0xFFFFFFFFFFFFFFFFull)); // test of D5. [Test Remainder] and D6. [add back] (at 8bit words)
	REQUIRE( BigInt::fromString(       "FFFFFFFFFFFFFFFE0000000000000001", 16) % BigInt::fromUint64( 0xFFFFFFFFFFFFFFFFull) == BigInt::fromUint64(                     0ull));
	
	REQUIRE( BigInt::fromString(                      "1FFFFFFFFFFFFFFFE", 16) / BigInt::fromUint64(               0x02ull) == BigInt::fromUint64(    0xFFFFFFFFFFFFFFFFull));
	REQUIRE( BigInt::fromString(                      "1FFFFFFFFFFFFFFFE", 16) % BigInt::fromUint64(               0x02ull) == BigInt::fromUint64(                     0ull));
	REQUIRE( BigInt::fromString( "24090311171252216041959356964269510400", 10) / BigInt::fromUint64( 0x123456789ABCDEF0ull) == BigInt::fromUint64(    0xFEDCBA9876543210ull)); // 24090311171252216041959356964269510400 / 1311768467463790320 = 18364758544493064720
	REQUIRE( BigInt::fromString( "24090311171252216041959356964269510400", 10) % BigInt::fromUint64( 0x123456789ABCDEF0ull) == BigInt::fromUint64(                     0ull));
	REQUIRE( BigInt::fromString(       "121fa00ad77d7422236d88fe5618cf00", 16) / BigInt::fromUint64( 0x123456789ABCDEF0ull) == BigInt::fromUint64(    0xFEDCBA9876543210ull)); // 24090311171252216041959356964269510400 / 1311768467463790320 = 18364758544493064720
	REQUIRE( BigInt::fromString(       "121fa00ad77d7422236d88fe5618cf00", 16) % BigInt::fromUint64( 0x123456789ABCDEF0ull) == BigInt::fromUint64(                     0ull));
	
	// -------
	REQUIRE( BigInt::fromString(    "121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16) / BigInt::fromString( "fedcba9876543210000000000000000fedcba9876543210", 16) == BigInt::fromString(  "123456789abcdef000000000000000123456789abcdef0", 16));
	REQUIRE( BigInt::fromString(    "121fa00ad77d7422236d88fe5618cf13419a0b84f54b6445a4618e3b7a5bf121fa00ad77d7422236d88fe5618cf00", 16) % BigInt::fromString( "fedcba9876543210000000000000000fedcba9876543210", 16) == BigInt::fromString(                                               "0", 16));
	REQUIRE( BigInt::fromString( "121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) / BigInt::fromString("987654321000000000000000000000000000009876543210", 10) == BigInt::fromString("123456789000000000000000000000000000001234567890", 10));
	REQUIRE( BigInt::fromString( "121932631112635269000000000000000000002438652622252705380000000000000000000012193263111263526900", 10) % BigInt::fromString("987654321000000000000000000000000000009876543210", 10) == BigInt::fromString(                                               "0", 10));
	
	// ------
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / BigInt::fromString("1", 10) == BigInt::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10));
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % BigInt::fromString("1", 10) == BigInt::fromString(                                                                                                         "0", 10));
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / BigInt::fromString("2", 10) == BigInt::fromString("3282327327325825708273258273273258263263232825825739394992080780749242493932813447459093582582732732572788", 10));
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % BigInt::fromString("2", 10) == BigInt::fromString(                                                                                                         "1", 10));
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / BigInt::fromString("147", 10) == BigInt::fromString("44657514657494227323445690792833445758683439807152916938667765724479489713371611530055695001125615409153", 10));
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % BigInt::fromString("147", 10) == BigInt::fromString(                                                                                                      "86", 10));
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / BigInt::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) == BigInt::fromString("1", 10));
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % BigInt::fromString("6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) == BigInt::fromString("0", 10));
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) / BigInt::fromString("5555555555555544455555555555555555444441122235654445554547555", 10) == BigInt::fromString("1181637837837299615890772977303005548172635842", 10));
	REQUIRE( BigInt::fromString( "6564654654651651416546516546546516526526465651651478789984161561498484987865626894918187165165465465145577", 10) % BigInt::fromString("5555555555555544455555555555555555444441122235654445554547555", 10) == BigInt::fromString("102256964850719633725637788587322669027978740977851378679267", 10));
	
	REQUIRE( BigInt::fromString( "121212121121212454564757645640000000000000000000546424465744466464313145643", 10) / BigInt::fromString("46464644515442612", 10) == BigInt::fromString("2608695759652855584042902602291341403871593244214364153233", 10));
	REQUIRE( BigInt::fromString( "121212121121212454564757645640000000000000000000546424465744466464313145643", 10) % BigInt::fromString("46464644515442612", 10) == BigInt::fromString("5925350727381047", 10));
	REQUIRE( BigInt::fromString( "AEDBBBBBDDDFFFFFFFFFFF65156895651516500000000000000000F", 16) / BigInt::fromString("FFFFFFFFFF56556165465466546546546546122222222F", 16) == BigInt::fromString("aedbbbbbd", 16));
	REQUIRE( BigInt::fromString( "AEDBBBBBDDDFFFFFFFFFFF65156895651516500000000000000000F", 16) % BigInt::fromString("FFFFFFFFFF56556165465466546546546546122222222F", 16) == BigInt::fromString("e53e3992ef3e65ed83201fbc921bdf68de2743627f6e5c", 16));
	
	REQUIRE( BigInt::fromString( "15485863", 10) / BigInt::fromString("17", 10) == BigInt::fromString("910933", 10));
	REQUIRE( BigInt::fromString( "15485863", 10) % BigInt::fromString("17", 10) == BigInt::fromString("2", 10));
	
}
