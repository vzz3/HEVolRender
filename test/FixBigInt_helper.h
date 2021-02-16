
#pragma once
#include <iostream>

#ifdef FIX_BIG_INT_AUTO_SIZE_TEMP_VARS
	#define logFixBigIntAutoSizeInfo()  \
		std::cout << ("INFO: Fix width big integer autosizing of temporary variable is enabled => use original bit length for testing") << std::endl

	#define   _8_p1 	   8
	#define  _16_p1 	  16
	#define  _46_p1 	  46
	#define  _72_p1 	  72
	#define _256_p1		 256

	#define   _8_x2 	   8
	#define  _46_x2 	  46
	#define _128_x2 	 128
	#define _256_x2 	 256
#else
	#define logFixBigIntAutoSizeInfo()  \
		std::cout << ("INFO: Fix width big integer autosizing of temporary variable is disabled => increase the bit length for testing") << std::endl


	// divKnuth_multiplySubtract() not poible without FIX_BIG_INT_AUTO_SIZE_TEMP_VARS
	#define   _8_p1 	(  8 + BIG_INT_BITS_PER_WORD)
	#define  _16_p1 	( 16 + BIG_INT_BITS_PER_WORD)
	#define  _46_p1 	( 47 + BIG_INT_BITS_PER_WORD)
	#define  _72_p1 	( 72 + BIG_INT_BITS_PER_WORD)
	#define _256_p1		(256 + BIG_INT_BITS_PER_WORD)


	// mulSchool() not poible without FIX_BIG_INT_AUTO_SIZE_TEMP_VARS
	#define   _8_x2 	(  8 * 2)
	#define  _46_x2 	( 46 * 2)
	#define _128_x2		(128 * 2)
	#define _256_x2		(256 * 2)
#endif
