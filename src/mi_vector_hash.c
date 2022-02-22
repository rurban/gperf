/*
 * See http://burtleburtle.net/bob/hash/doobs.html for the full description
 * and the original version of the code.  This version differs by exposing
 * the full internal state and avoiding byte operations in the inner loop
 * if the key is aligned correctly.
 */
/* __RCSID("$NetBSD: mi_vector_hash.c,v 1.1 2013/12/11 01:24:08 joerg Exp $"); */

#ifdef HAVE_ENDIAN_H
#include <endian.h>
#endif
#include <stdint.h>
#include <stdlib.h>

#ifndef le32toh
#define le32toh(x) x
#endif

#ifdef __GNUC__
__inline
#elif defined __cplusplus
inline
#endif
static uint32_t
le32dec(const void *buf)
{
        return *(uint32_t*)buf;
}

#define mix(a, b, c) do {		\
	a -= b; a -= c; a ^= (c >> 13);	\
	b -= c; b -= a; b ^= (a << 8);	\
	c -= a; c -= b; c ^= (b >> 13);	\
	a -= b; a -= c; a ^= (c >> 12);	\
	b -= c; b -= a; b ^= (a << 16);	\
	c -= a; c -= b; c ^= (b >> 5);	\
	a -= b; a -= c; a ^= (c >> 3);	\
	b -= c; b -= a; b ^= (a << 10);	\
	c -= a; c -= b; c ^= (b >> 15);	\
} while (/* CONSTCOND */0)

#define FIXED_SEED	0x9e3779b9	/* Golden ratio, arbitrary constant */

void
mi_vector_hash(const void * __restrict key, size_t len, uint32_t seed,
               uint32_t hashes[3])
{
	static const uint32_t mask[4] = {
		0x000000ff, 0x0000ffff, 0x00ffffff, 0xffffffff
	};
	uint32_t orig_len, a, b, c;
	const uint8_t *k;

	orig_len = (uint32_t)len;

	a = b = FIXED_SEED;
	c = seed;

	if ((uintptr_t)key & 3) {
		k = (const uint8_t *)key;
		while (len >= 12) {
			a += le32dec(k);
			b += le32dec(k + 4);
			c += le32dec(k + 8);
			mix(a, b, c);
			k += 12;
			len -= 12;
		}
		c += orig_len;

		if (len > 8) {
			switch (len) {
			case 11:
				c += (uint32_t)k[10] << 24;
				/* FALLTHROUGH */
			case 10:
				c += (uint32_t)k[9] << 16;
				/* FALLTHROUGH */
			case 9:
				c += (uint32_t)k[8] << 8;
				/* FALLTHROUGH */
			}
			b += le32dec(k + 4);
			a += le32dec(k);
		} else if (len > 4) {
			switch (len) {
			case 8:
				b += (uint32_t)k[7] << 24;
				/* FALLTHROUGH */
			case 7:
				b += (uint32_t)k[6] << 16;
				/* FALLTHROUGH */
			case 6:
				b += (uint32_t)k[5] << 8;
				/* FALLTHROUGH */
			case 5:
				b += k[4];
				/* FALLTHROUGH */
			}
			a += le32dec(k);
		} else if (len) {
			switch (len) {
			case 4:
				a += (uint32_t)k[3] << 24;
				/* FALLTHROUGH */
			case 3:
				a += (uint32_t)k[2] << 16;
				/* FALLTHROUGH */
			case 2:
				a += (uint32_t)k[1] << 8;
				/* FALLTHROUGH */
			case 1:
				a += k[0];
				/* FALLTHROUGH */
			}
		}
	} else {
		const uint32_t *key32 = (const uint32_t *)key;
		while (len >= 12) {
			a += le32toh(key32[0]);
			b += le32toh(key32[1]);
			c += le32toh(key32[2]);
			mix(a, b, c);
			key32 += 3;
			len -= 12;
		}
		c += orig_len;

		if (len > 8) {
			c += (le32toh(key32[2]) & mask[len - 9]) << 8;
			b += le32toh(key32[1]);
			a += le32toh(key32[0]);
		} else if (len > 4) {
			b += le32toh(key32[1]) & mask[len - 5];
			a += le32toh(key32[0]);
		} else if (len)
			a += le32toh(key32[0]) & mask[len - 1];
	}
	mix(a, b, c);
	hashes[0] = a;
	hashes[1] = b;
	hashes[2] = c;
}
