/****************************************************************
 *                                                              *
 *          __ ____  _________                                  *
 *         /_ \\\  \/   /|    \______                           *
 *        //   \\\     /|| D  /_    /.                          *
 *       //     \\\_  /.||    \ ___/.                           *
 *      /___/\___\\__/. |__|\__\__.___  ___                     *
 *       ....  .......   ...||  _/_\  \////.                    *
 *                          || |.| |\  ///.                     *
 *                          |__|.|_|///  \                      *
 *                           .... ./__/\__\                     *
 *                                  ........                    *
 * Fixed Point Library                                          *
 * according to                                                 *
 * ISO/IEC DTR 18037                                            *
 *                                                              *
 * Version 1.0.1                                                *
 * Maximilan Rosenblattl, Andreas Wolf 2007-02-07               *
 ****************************************************************/

#ifndef _AVRFIX_H
#define _AVRFIX_H


#ifndef TEST_ON_PC
#include <avr/io.h>
#include <avr/interrupt.h>
/*#include <avr/signal.h>*/
#include <avr/pgmspace.h>
// #include "avrfix_config.h"
#endif

/* Only two datatypes are used from the ISO/IEC standard:
 * short fix_t with s7.8 bit format
 *       fix_t with s15.16 bit format
 * long  fix_t with  s7.24 bit format
 */

typedef signed short sfix_t;
typedef signed long  fix_t;
typedef signed long  lfix_t;

/* Pragmas for defining overflow behaviour */

#define DEFAULT    0
#define SAT        1

#ifndef FX_ACCUM_OVERFLOW
#define FX_ACCUM_OVERFLOW DEFAULT
#endif

/* Pragmas for internal use */

#define SACCUM_IBIT 7
#define SACCUM_FBIT 8
#define ACCUM_IBIT 15
#define ACCUM_FBIT 16
#define LACCUM_IBIT 7
#define LACCUM_FBIT 24

#define SACCUM_MIN -32767
#define SACCUM_MAX  32767
#define ACCUM_MIN -2147483647L
#define ACCUM_MAX  2147483647L
#define LACCUM_MIN -2147483647L
#define LACCUM_MAX  2147483647L

#define SACCUM_FACTOR ((short)1 << SACCUM_FBIT)
#define ACCUM_FACTOR ((long)1 << ACCUM_FBIT)
#define LACCUM_FACTOR ((long)1 << LACCUM_FBIT)

/* Mathematical constants */

#define PIsk 804
#define PIk 205887
#define PIlk 52707179

#define LOG2k  45426
#define LOG2lk 11629080

#define LOG10k 150902
#define LOG10lk 38630967

#ifndef NULL
#define NULL ((void*)0)
#endif

/* conversion Functions */

#define itosk(i) ((sfix_t)(i) << SACCUM_FBIT)
#define itok(i)  ((fix_t)(i)  << ACCUM_FBIT)
#define itolk(i) ((lfix_t)(i) << LACCUM_FBIT)

#define sktoi(k) ((int8_t)((k) >> SACCUM_FBIT))
#define ktoi(k)  ((signed short)((k) >> ACCUM_FBIT))
#define lktoi(k) ((int8_t)((k) >> LACCUM_FBIT))

#define sktok(sk)  ( (fix_t)(sk) << (ACCUM_FBIT-SACCUM_FBIT))
#define ktosk(k)   ((sfix_t)((k) >> (ACCUM_FBIT-SACCUM_FBIT)))

#define sktolk(sk) ((lfix_t)(sk) << (LACCUM_FBIT-SACCUM_FBIT))
#define lktosk(lk) ((sfix_t)((lk) >> (LACCUM_FBIT-SACCUM_FBIT)))

#define ktolk(k)   ((fix_t)(k) << (LACCUM_FBIT-ACCUM_FBIT))
#define lktok(lk)  ((lfix_t)(lk) >> (LACCUM_FBIT-ACCUM_FBIT))

#define ftosk(f)  ((sfix_t)((f)  * (1 << SACCUM_FBIT)))
#define ftok(f)   ((fix_t)((f)  * (1L << ACCUM_FBIT)))
#define ftolk(f)  ((lfix_t)((f) * (1L << LACCUM_FBIT)))

#define sktof(sk) ((float)((sfix_t)(sk) / ((float)(1 << SACCUM_FBIT))))
#define ktod(k)   ((double)((fix_t)(k) / ((double)(1L << ACCUM_FBIT))))
#define lktod(lk) ((double)((lfix_t)(lk) / ((double)(1L << LACCUM_FBIT))))

/* Main Functions */

sfix_t smulskD(sfix_t, sfix_t);
fix_t mulkD(fix_t, fix_t);
lfix_t lmullkD(lfix_t, lfix_t);


sfix_t sdivskD(sfix_t, sfix_t);
fix_t divkD(fix_t, fix_t);
lfix_t ldivlkD(lfix_t, lfix_t);

sfix_t smulskS(sfix_t, sfix_t);
fix_t mulkS(fix_t, fix_t);
lfix_t lmullkS(lfix_t, lfix_t);

sfix_t sdivskS(sfix_t, sfix_t);
fix_t divkS(fix_t, fix_t);
lfix_t ldivlkS(lfix_t, lfix_t);

#if FX_ACCUM_OVERFLOW == DEFAULT
  #define smulsk(a,b) smulskD((a),(b))
  #define mulk(a,b) mulkD((a),(b))
  #define lmullk(a,b) lmullkD((a), (b))
  #define sdivsk(a,b) sdivskD((a), (b))
  #define divk(a,b) divkD((a), (b))
  #define ldivlk(a,b) ldivlkD((a), (b))
#elif FX_ACCUM_OVERFLOW == SAT
  #define smulsk(a,b) smulskS((a),(b))
  #define mulk(a,b) mulkS((a),(b))
  #define lmullk(a,b) lmullkS((a), (b))
  #define sdivsk(a,b) sdivskS((a), (b))
  #define divk(a,b) divkS((a), (b))
  #define ldivlk(a,b) ldivlkS((a), (b))
#endif

/* Support Functions */
/*
#define mulikD(i,k) ktoi((i) * (k))
#define mulilkD(i,lk) lktoi((i) * (lk))

#define divikD(i,k) ktoi(divkD(itok(i),(k)))
#define divilkD(i,lk) lktoi(ldivlkD(itolk(i),(lk)))

#define kdiviD(a,b) divkD(itok(a),itok(b))
#define lkdiviD(a,b) ldivlkD(itolk(a),itolk(b))

#define idivkD(a,b) ktoi(divkD((a),(b)))
#define idivlkD(a,b) lktoi(ldivlkD((a),(b)))

#define mulikS(i,k) ktoi(mulkS(itok(i),(k)))
#define mulilkS(i,lk) lktoi(lmullkS(itolk(i),(lk)))

#define divikS(i,k) ktoi(divkS(itok(i),(k)))
#define divilkS(i,lk) lktoi(ldivlkS(itolk(i),(lk)))

#define kdiviS(a,b) divkS(itok(a),itok(b))
#define lkdiviS(a,b) ldivlkS(itolk(a),itolk(b))

#define idivkS(a,b) ktoi(divkS((a),(b)))
#define idivlkS(a,b) lktoi(ldivlkS((a),(b)))

#if FX_ACCUM_OVERFLOW == DEFAULT
  #define mulik(a,b) mulikD((a),(b))
  #define mulilk(a,b) mulilkD((a),(b))
  #define divik(a,b) divikD((a),(b))
  #define divilk(a,b) divilkD((a),(b))
  #define kdivi(a,b) kdiviD((a),(b))
  #define lkdivi(a,b) lkdiviD((a),(b))
  #define idivk(a,b) idivkD((a),(b))
  #define idivlk(a,b) idivlkD((a),(b))
#elif FX_ACCUM_OVERFLOW == SAT
  #define mulik(a,b) mulikS((a),(b))
  #define mulilk(a,b) mulilkS((a),(b))
  #define divik(a,b) divikS((a),(b))
  #define divilk(a,b) divilkS((a),(b))
  #define kdivi(a,b) kdiviS((a),(b))
  #define lkdivi(a,b) lkdiviS((a),(b))
  #define idivk(a,b) idivkS((a),(b))
  #define idivlk(a,b) idivlkS((a),(b))
#endif
*/
/* Abs Functions */

#define sabssk(f)  ((f) < 0 ? (-(f)) : (f))
#define absk(f)  ((f) < 0 ? (-(f)) : (f))
#define labslk(f) ((f) < 0 ? (-(f)) : (f))

/* Rounding Functions */
/*
extern sfix_t roundskD(sfix_t f, uint8_t n);
extern fix_t roundkD(fix_t f, uint8_t n);
extern lfix_t roundlkD(lfix_t f, uint8_t n);

extern sfix_t roundskS(sfix_t f, uint8_t n);
extern fix_t roundkS(fix_t f, uint8_t n);
extern lfix_t roundlkS(lfix_t f, uint8_t n);

#if FX_ACCUM_OVERFLOW == DEFAULT
  #define roundsk(f, n) roundskD((f), (n))
  #define roundk(f, n) roundkD((f), (n))
  #define roundlk(f, n) roundlkD((f), (n))
#elif FX_ACCUM_OVERFLOW == SAT
  #define roundsk(f, n) roundskS((f), (n))
  #define roundk(f, n) roundkS((f), (n))
  #define roundlk(f, n) roundlkS((f), (n))
#endif
*/
/* countls Functions */
/*
extern uint8_t countlssk(sfix_t f);
extern uint8_t countlsk(fix_t f);
#define countlslk(f) countlsk((f))
*/
/* Special Functions */

#define CORDICC_GAIN 10188012
#define CORDICH_GAIN 20258445
/*
extern fix_t sqrtk_uncorrected(fix_t,int8_t,uint8_t);

#define sqrtkD(a)   mulkD(sqrtk_uncorrected(a, -8, 17), CORDICH_GAIN/256)
#define lsqrtlkD(a) lmullkD(sqrtk_uncorrected(a, 0, 24), CORDICH_GAIN)

#define sqrtkS(a)   mulkS(sqrtk_uncorrected(a, -8, 17), CORDICH_GAIN/256)
#define lsqrtlkS(a) lmullkS(sqrtk_uncorrected(a, 0, 24), CORDICH_GAIN)

#if FX_ACCUM_OVERFLOW == DEFAULT
  #define sqrtk(a) sqrtkD(a)
  #define lsqrtlk(a) lsqrtlkD(a)
#else
  #define sqrtk(a) sqrtkS(a)
  #define lsqrtlk(a) lsqrtlkS(a)
#endif

extern fix_t sincosk(fix_t, fix_t*);
extern lfix_t lsincoslk(lfix_t, lfix_t*);
extern lfix_t lsincosk(fix_t, lfix_t*);
extern sfix_t ssincossk(sfix_t, sfix_t*);

#define sink(a)   sincosk((a), NULL)
#define lsinlk(a) lsincoslk((a), NULL)
#define lsink(a)  lsincosk((a), NULL)
#define ssinsk(a) ssincossk((a), NULL)

#define cosk(a)   sink((a) + PIk/2 + 1)
#define lcoslk(a) lsinlk((a) + PIlk/2)
#define lcosk(a)  lsink((a) + PIk/2 + 1)
#define scossk(a) ssinsk((a) + PIsk/2)

extern fix_t tankD(fix_t);
extern lfix_t ltanlkD(lfix_t);
extern lfix_t ltankD(fix_t);

extern fix_t tankS(fix_t);
extern lfix_t ltanlkS(lfix_t);
extern lfix_t ltankS(fix_t);

#if FX_ACCUM_OVERFLOW == DEFAULT
  #define tank(a) tankD((a))
  #define ltanlk(a) ltanlkD((a))
  #define ltank(a) ltankD((a))
#elif FX_ACCUM_OVERFLOW == SAT
  #define tank(a) tankS((a))
  #define ltanlk(a) ltanlkS((a))
  #define ltank(a) ltankS((a))
#endif

extern fix_t atan2k(fix_t, fix_t);
extern lfix_t latan2lk(lfix_t, lfix_t);

#define atank(a) atan2k(itok(1), (a))
#define latanlk(a) latan2lk(itolk(1), (a))

extern fix_t logk(fix_t);
extern lfix_t lloglk(lfix_t);

#define log2k(x) (divk(logk((x)), LOG2k))
#define log10k(x) (divk(logk((x)), LOG10k))
#define logak(a, x) (divk(logk((x)), logk((a))))

#define llog2lk(x) (ldivlk(lloglk((x)), LOG2lk))
#define llog10lk(x) (ldivlk(lloglk((x)), LOG10lk))
#define llogalk(a, x) (ldivlk(lloglk((x)), lloglk((a))))
*/

#endif /* _AVRFIX_H */

