

// ----- bit utilities -----

/**
 * this method returns the number of the highest set bit in word
 * if the 'word' is zero this method returns '-1'
 */
//static int findHighestSetBitInWord(BIG_INT_WORD_TYPE word);

/**
 * this method returns the number of the lowest set bit in word
 * if the 'word' is zero this method returns '-1'
 */
//static int findLowestSetBitInWord(BIG_INT_WORD_TYPE word);

/**
 * Replace target.low with src.low bits.
 *
 * target:	hhhhllll
 * src:		HHHHLLLL
 * res:		hhhhLLLL
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_setLowFromLowBits(const in BIG_INT_WORD_TYPE target, const in BIG_INT_WORD_TYPE src);

/**
 * Replace target.low with src.high bits.
 *
 * target:	hhhhllll
 * src:		HHHHLLLL
 * res:		hhhhHHHH
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_setLowFromHighBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src);

/**
 * Replace target.high with src.high bits.
 *
 * target:	hhhhllll
 * src:		HHHHLLLL
 * res:		HHHHllll
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_setHighFromHighBits(const in BIG_INT_WORD_TYPE target, const in BIG_INT_WORD_TYPE src);

/**
 * Replace target.high with src.low bits.
 *
 * target:	hhhhllll
 * src:		HHHHLLLL
 * res:		LLLLllll
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_setHighFromLowBits(const in BIG_INT_WORD_TYPE target, const in BIG_INT_WORD_TYPE src);

/**
 * Set low bit to 0 and keep the high bits.
 *
 * src:	HHHHLLLL
 * res:	HHHH0000
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_getHighAsHighBits(const in BIG_INT_WORD_TYPE src);

/**
 * Move the high bits of src to the low bits. The high bits will be 0.
 *
 * src:	HHHHLLLL
 * res:	0000HHHH
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_getHighAsLowBits(const in BIG_INT_WORD_TYPE src);

/**
 * Set high bit to 0 and keep the low bits.
 *
 * src:	HHHHLLLL
 * res:	0000LLLL
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_getLowAsLowBits(const in BIG_INT_WORD_TYPE src);

/**
 * Move the low bits of src to the high bits. The low bits will be 0.
 *
 * src:	HHHHLLLL
 * res:	LLLL0000
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_getLowAsHighBits(const in BIG_INT_WORD_TYPE src);


// ----- addition -----

/**
 * this method adds two words together
 * returns carry
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_addTwoWords(const in BIG_INT_WORD_TYPE a, const in BIG_INT_WORD_TYPE b, in BIG_INT_WORD_TYPE carry, out BIG_INT_WORD_TYPE result);

/**
 * this method adds only two unsigned words to the existing value
 * and these words begin on the 'index' position
 *
 * index should be equal or smaller than value_size-2 (index <= value_size-2)
 * x1 - lower word, x2 - higher word
 *
 * for example if we've got value_size equal 4 and:
 *
 * value[0] = 3
 * value[1] = 4
 * value[2] = 5
 * value[3] = 6
 *
 * then let
 *
 * x1 = 10
 * x2 = 20
 *
 * and
 *
 * index = 1
 *
 * the result of this method will be:
 *
 * value[0] = 3
 * value[1] = 4 + x1 = 14
 * value[2] = 5 + x2 = 25
 * value[3] = 6
 *
 * and no carry at the end of value[3]
 *
 * (of course if there was a carry in value[2](5+20) then
 * this carry would be passed to the value[3] etc.)
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_addTwoInts(const in BIG_INT_WORD_TYPE wordHigh, const in BIG_INT_WORD_TYPE wordLow, const in BIG_INT_WORD_COUNT_TYPE index, inout FIX_BIG_INT_VALUE targetArray, const in BIG_INT_WORD_COUNT_TYPE targetWordCount);


/**
 * this method adds one word (at a specific position)
 * and returns a carry (if it was)
 *
 * if we've got (value_size=3):
 *
 * table[0] = 10;
 * table[1] = 30;
 * table[2] = 5;
 *
 * and we call:
 *
 * AddInt(2,1)
 *
 * then it'll be:
 *
 * table[0] = 10;
 * table[1] = 30 + 2;
 * table[2] = 5;
 *
 * of course if there was a carry from table[2] it would be returned
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_addInt(const in BIG_INT_WORD_TYPE word, const in BIG_INT_WORD_COUNT_TYPE index, inout FIX_BIG_INT_VALUE targetArray, const in BIG_INT_WORD_COUNT_TYPE targetWordCount);


// ----- substraction -----

/**
 * this method subtractes one word from the other and subtracting
 * carry if it has been defined
 * (result = a - b - carry)
 * carry have to be 0 or 1
 *
 * returns carry(borow)
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_subTwoWords(const in BIG_INT_WORD_TYPE a, const in BIG_INT_WORD_TYPE b, in BIG_INT_WORD_TYPE carry, out BIG_INT_WORD_TYPE result);


/**
 * this method subtracts one word (at a specific position)
 * and returns a carry (if it was)
 *
 * if we've got (value_size=3):
 *
 * table[0] = 10;
 * table[1] = 30;
 * table[2] = 5;
 *
 * and we call:
 *
 * SubInt(2,1)
 *
 * then it'll be:
 *
 * table[0] = 10;
 * table[1] = 30 - 2;
 * table[2] = 5;
 *
 * of course if there was a carry from table[2] it would be returned
 *
 * @static
 * @public
 */
BIG_INT_WORD_TYPE BigIntUtil_subInt(const in BIG_INT_WORD_TYPE word, const in BIG_INT_WORD_COUNT_TYPE index, inout FIX_BIG_INT_VALUE targetArray, const in BIG_INT_WORD_COUNT_TYPE targetWordCount);

// ----- multiplication -----

/**
 * @static
 * @public
 */
void BigIntUtil_mulTwoWords(const in BIG_INT_WORD_TYPE a, const in BIG_INT_WORD_TYPE b, out BIG_INT_WORD_TYPE resultHigh, out BIG_INT_WORD_TYPE resultLow);
