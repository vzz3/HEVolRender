
#define S PAILLIER_INT_WORD_SIZE

//#define FIX_BIG_INT_AUTO_SIZE_TEMP_VARS

#ifdef FIX_BIG_INT_AUTO_SIZE_TEMP_VARS
	// missing methods: divInt(), subInt(), mulInt(), sub(), ad(d)
	#define FBI_WC_Sp1 (S+1)
	#define FBI_WC_Sm2 (S*2)
#else
	#define FBI_WC_Sp1 (S)
	#define FBI_WC_Sm2 (S)
#endif




// ----- division -----

/**
 * division by one unsigned word
 * restul = this / divisor
 *
 * returns the remainder
 *
 * @const
 * @protected
 */
BIG_INT_WORD_TYPE UFixBigInt_divInt(const in FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE divisor, out FIX_BIG_INT_VALUE result);


/**
 * division by one unsigned word
 * this = this / divisor
 *
 * returns the remainder
 *
 * @protected
 */
BIG_INT_WORD_TYPE UFixBigInt_divInt(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE divisor);


// -- divKnuth

/*
 * @const
 * @private
 */
void UFixBigInt_divKnuth_division(const in FIX_BIG_INT_VALUE me, in FIX_BIG_INT_VALUE divisor, out FIX_BIG_INT_VALUE result, out FIX_BIG_INT_VALUE remainder, const in uint m, const in uint n);

/*
 * @const
 * @private
 */
void UFixBigInt_divKnuth_makeNewU(const in FIX_BIG_INT_VALUE me, inout BIG_INT_WORD_TYPE[FBI_WC_Sp1] uu, in BIG_INT_WORD_COUNT_TYPE j, const in BIG_INT_WORD_COUNT_TYPE n, const in BIG_INT_WORD_TYPE u_max);

/*
 * @private
 */
void UFixBigInt_divKnuth_copyNewU(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE[FBI_WC_Sp1] uu, const in BIG_INT_WORD_COUNT_TYPE j, const in BIG_INT_WORD_COUNT_TYPE n);

/**
 * D1. [Normaliez]
 *
 * we're moving all bits from 'divisor' into the left side of the n-1 word
 * (the highest bit at divisor.value[n-1] will be equal one,
 * the bits from 'dividend' we're moving the same times as 'divisor')
 *
 * return values:
 * -  d - how many times we've moved
 * -  return - the next-left value from 'this' (that after value[value_size-1])
 *
 * @private
 */
BIG_INT_WORD_TYPE UFixBigInt_divKnuth_normalize(inout FIX_BIG_INT_VALUE me, inout FIX_BIG_INT_VALUE divisor, const in uint n, out uint d);

/*
 * @private
 */
void UFixBigInt_divKnuth_unnormalize(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_COUNT_TYPE d);

/*
 * @const
 * @private
 */
BIG_INT_WORD_TYPE UFixBigInt_divKnuth_calculate(const in BIG_INT_WORD_TYPE u2, const in BIG_INT_WORD_TYPE u1, const in BIG_INT_WORD_TYPE u0, const in BIG_INT_WORD_TYPE v1, const in BIG_INT_WORD_TYPE v0);

/**
 * D4. [Multiply and subtract]
 *		includes also: D5. [Test Remainder] and D6. [add back]
 *
 * @const
 * @private
 */
void UFixBigInt_divKnuth_multiplySubtract(inout BIG_INT_WORD_TYPE[FBI_WC_Sp1] uu, const in BIG_INT_WORD_TYPE[FBI_WC_Sp1] vv, inout BIG_INT_WORD_TYPE qp);

/**
 * the third division algorithm
 *
 * this algorithm is described in the following book:
 * "The art of computer programming 2" (4.3.1 page 257)
 * Donald E. Knuth
 * !! give the description here (from the book)
 *
 * @const
 * @private
 */
void UFixBigInt_divKnuth(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE divisor, out FIX_BIG_INT_VALUE result, out FIX_BIG_INT_VALUE remainder);








// ----- comparisons -----

/*
 * operator<
 *
 * @const
 * @public
 */
bool UFixBigInt_lessThan(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other);

/*
 * operator<=
 *
 * @const
 * @public
 */
bool UFixBigInt_lessThanOrEqualTo(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other);

/*
 * operator>
 *
 * @const
 * @public
 */
bool UFixBigInt_greaterThan(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other);

/*
 * operator>=
 *
 * @const
 * @public
 */
bool UFixBigInt_greaterThanOrEqualTo(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other);

/*
 * operator==
 *
 * @const
 * @public
 */
bool UFixBigInt_equalTo(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other);

/*
 * operator!=
 *
 * @const
 * @public
 */
bool UFixBigInt_notEqualTo(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other);
