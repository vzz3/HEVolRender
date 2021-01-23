
#define S PAILLIER_INT_WORD_SIZE

//#define FIX_BIG_INT_AUTO_SIZE_TEMP_VARS

#ifdef FIX_BIG_INT_AUTO_SIZE_TEMP_VARS
	#define FBI_WC_Sp1 (S+1)
	#define FBI_WC_Sm2 (S*2)
#else
	#define FBI_WC_Sp1 (S)
	#define FBI_WC_Sm2 (S)
#endif






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
