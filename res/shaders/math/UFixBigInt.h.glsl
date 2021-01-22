
#define S PAILLIER_INT_WORD_SIZE



/* ---------- comparisons ---------- */

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
