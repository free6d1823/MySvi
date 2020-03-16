/*
 * Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 *
 * The Mersenne Twister pseudo-random number generator (PRNG)
 *
 * This is an implementation of fast PRNG called MT19937,
 * meaning it has a period of 2^19937-1, which is a Mersenne
 * prime.
 *
 * This PRNG is fast and suitable for non-cryptographic code.
 * For instance, it would be perfect for Monte Carlo simulations,
 * etc.
 *
 * For all the details on this algorithm, see the original paper:
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/mt.pdf
 *
 * Written by Christian Stigen Larsen
 * http://csl.name
 *
 * Distributed under the modified BSD license.
 *
 * 2015-02-17
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <target/timer.h>


/*
 * We have an array of 624 32-bit values, and there are
 * 31 unused bits, so we have a seed value of
 * 624*32-31 = 19937 bits.
 */
#define MT_SIZE           624
#define MT_PERIOD         397
#define MT_DIFF           (MT_SIZE - MT_PERIOD)

static uint32_t MT[MT_SIZE];
static unsigned index = 0;

#define M32(x) (0x80000000 & x) // 32nd Most Significant Bit
#define L31(x) (0x7FFFFFFF & x) // 31 Least Significant Bits
#define ODD(x) (x & 1) // Check if number is odd

#define UNROLL(expr) \
  y = M32(MT[i]) | L31(MT[i+1]); \
  MT[i] = MT[expr] ^ (y>>1) ^ MATRIX[ODD(y)]; \
  ++i;


static bool is_rand_initialized = false;

uint32_t get_random_sw(uint8_t *out, uint32_t len)
{
  if (!out || len < 4)
    return 0;

  memset(out, 0, len);

  if (!is_rand_initialized)
  {
    srand((uint32_t)time_get_current_time());
    is_rand_initialized = true;
  }

  uint32_t random = rand();
  memcpy(out, &random, sizeof(random));

  return sizeof(random);
}

static inline void generate_numbers()
{
  /*
   * Originally, we had one loop with i going from [0, MT_SIZE) and
   * two modulus operations:
   *
   * for ( register unsigned i=0; i<MT_SIZE; ++i ) {
   *   register uint32_t y = M32(MT[i]) | L31(MT[(i+1) % MT_SIZE]);
   *   MT[i] = MT[(i + MT_PERIOD) % MT_SIZE] ^ (y>>1);
   *   if ( ODD(y) ) MT[i] ^= 0x9908b0df;
   * }
   *
   * For performance reasons, we've unrolled the loop three times, thus
   * mitigating the need for any modulus operations.
   *
   * Anyway, it seems this trick is old hat:
   * http://www.quadibloc.com/crypto/co4814.htm
   *
   */

  static const uint32_t MATRIX[2] = {0, 0x9908b0df};
  register uint32_t y, i=0;

  // i = [0 ... 225]
  while ( i<(MT_DIFF-1) ) {
    /*
     * We're doing 226 = 113*2, an even number of steps, so we can
     * safely unroll one more step here for speed:
     */
    UNROLL(i+MT_PERIOD);
    UNROLL(i+MT_PERIOD);
  }

  // i = 226
  UNROLL((i+MT_PERIOD) % MT_SIZE);

  // i = [227 ... 622]
  while ( i<(MT_SIZE-1) ) {
    /*
     * 623-227 = 396 = 2*2*3*3*11, so we can unroll this loop in any number
     * that evenly divides 396 (2, 4, 6, etc). Here we'll unroll 11 times.
     */
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
    UNROLL(i-MT_DIFF);
  }

  // i = 623
  y = M32(MT[MT_SIZE-1]) | L31(MT[0]); \
  MT[MT_SIZE-1] = MT[MT_PERIOD-1] ^ (y>>1) ^ MATRIX[ODD(y)]; \
}

void seed(uint32_t value)
{
  register unsigned int i;

  /*
   * The equation below is a linear congruential generator (LCG),
   * one of the oldest known pseudo-random number generator
   * algorithms, in the form X_(n+1) = = (a*X_n + c) (mod m).
   *
   * We've implicitly got m=32 (mask + word size of 32 bits), so
   * there is no need to explicitly use modulus.
   *
   * What is interesting is the multiplier a.  The one we have
   * below is 0x6c07865 --- 1812433253 in decimal, and is called
   * the Borosh-Niederreiter multiplier for modulus 2^32.
   *
   * It is mentioned in passing in Knuth's THE ART OF COMPUTER
   * PROGRAMMING, Volume 2, page 106, Table 1, line 13.  LCGs are
   * treated in the same book, pp. 10-26
   *
   * You can read the original paper by Borosh and Niederreiter
   * as well.  It's called OPTIMAL MULTIPLIERS FOR PSEUDO-RANDOM
   * NUMBER GENERATION BY THE LINEAR CONGRUENTIAL METHOD (1983) at
   * http://www.springerlink.com/content/n7765ku70w8857l7/
   *
   * You can read about LCGs at:
   * http://en.wikipedia.org/wiki/Linear_congruential_generator
   *
   * From that page, it says:
   * "A common Mersenne twister implementation, interestingly
   * enough, uses an LCG to generate seed data.",
   *
   * Since we're using 32-bits data types for our MT array, we can skip the
   * masking with 0xFFFFFFFF below.
   */

  MT[0] = value;
  index = 0;

  for ( i=1; i<MT_SIZE; ++i )
    MT[i] = 0x6c078965*(MT[i-1] ^ MT[i-1]>>30) + i;
}

uint32_t rand_u32()
{
  if ( !index )
    generate_numbers();

  register uint32_t y = MT[index];

  // Tempering
  y ^= y>>11;
  y ^= y<< 7 & 0x9d2c5680;
  y ^= y<<15 & 0xefc60000;
  y ^= y>>18;

  if ( ++index == MT_SIZE )
    index = 0;

  return y;
}

int rand()
{
  /*
   * PORTABILITY WARNING:
   *
   * rand_u32() uses all 32-bits for the pseudo-random number,
   * but rand() must return a number from 0 ... RAND_MAX.
   *
   * We'll just assume that rand() only uses 31 bits worth of
   * data, and that we're on a two's complement system.
   *
   * So, to output an integer compatible with rand(), we have
   * two options: Either mask off the highest (32nd) bit, or
   * shift right by one bit.  Masking with 0x7FFFFFFF will be
   * compatible with 64-bit MT[], so we'll just use that here.
   *
   */
  return (int)(0x7FFFFFFF & rand_u32());
}

void srand(unsigned value)
{
  seed((uint32_t)(value));
}
