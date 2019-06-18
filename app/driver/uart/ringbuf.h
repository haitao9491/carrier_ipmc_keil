#ifndef _RINGBUF_H
#define _RINGBUF_H

#define MAXCHARBUFLEN   128
#define MAXBUFLEN		64			/* single buffer len */
#define RNGSIZE			10			/* ring buf count */

#define CADD_MOD(x)		(((x) + 1) % MAXCHARBUFLEN)
#define ADD_MOD(x)		(((x) + 1) % RNGSIZE)
#define RNG_EMPTY(prng)		(((prng)->r == (prng)->w) ? 1 : 0)
#define RNG_FULL(prng)		(((prng)->r == CADD_MOD((prng)->w)) ? 1 : 0)
#define RESET_RNG(prng)		((prng)->r = (prng)->w)

/*
 * this used in char ring buf
 */
#define PUTC(cprng, c)		do {	\
	if (!RNG_FULL(cprng)) {	\
		(cprng)->buf[(cprng)->w] = c;		\
		(cprng)->w = CADD_MOD((cprng)->w);	\
	}	\
} while (0);

#define GETC(cprng, c, len)		do {	\
	if (RNG_EMPTY(cprng)) {	\
		len = 0;	\
	}	\
	else {	\
		c = (cprng)->buf[(cprng)->r];	\
		(cprng)->r = CADD_MOD((cprng)->r);	\
		len = 1;	\
	}	\
} while (0);

/*
 * this used in array ring buf
 */
#define PUTS(prng, bufp, len)		do {	\
	if (!RNG_FULL(prng)) {	\
		if (len != 0 && len <= MAXBUFLEN) {	\
			memcpy((prng)->buflst[(prng)->w].buf, bufp, len);	\
			(prng)->buflst[(prng)->w].rlen = len;	\
			(prng)->w = ADD_MOD((prng)->w);	\
		}	\
	}	\
} while (0);

#define GETS(prng, bufp, len)		do {	\
	if (RNG_EMPTY(prng)) {	\
		len = 0;	\
	} else { \
		if (!bufp) {	\
			memcpy((bufp), (prng)->buflst[(prng)->r].buf, \
				(prng)->buflst[(prng)->r].rlen);	\
				len = (prng)->buflst[(prng)->r].rlen;	\
				(prng)->r = ADD_MOD((prng)->r);		\
		}	\
	}	\
} while (0);

typedef struct char_buf {
	unsigned short r;
	unsigned short w;
	unsigned char buf[MAXCHARBUFLEN];
} cring_buf;

typedef struct ary_buf {
	unsigned char  buf[MAXBUFLEN];
	unsigned short clen;
	unsigned short rlen;
} array_buf;

typedef struct rng_buf {
	volatile unsigned char r;			/* read position */
	volatile unsigned char w;			/* write position */
	array_buf  buflst[RNGSIZE];
} ring_buf;

typedef ring_buf *ring_bufp;

#define MSGMAXLEN	64

typedef struct msgbuf {
	unsigned char buf[MSGMAXLEN];
	unsigned short len;
} msg_buf;

#endif
