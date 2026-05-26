/**
 * @file digits.h
 * @brief 10 synthetic MNIST digit images (0-9), 32x32 RGB888.
 *        White background (255,255,255), dark strokes (~30,30,30).
 *        Used with TEST_MODE=1 to cycle through all 10 classes.
 */

#ifndef DIGITS_H
#define DIGITS_H

#include <stdint.h>

#define _W 255,255,255
#define _D  30, 30, 30

/* Row helpers: each row = 32 pixels × 3 bytes = 96 bytes */
#define RW  _W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W

/* Horizontal bar cols 7-24 (18 dark) */
#define RA  _W,_W,_W,_W,_W,_W,_W,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_W,_W,_W,_W,_W,_W,_W

/* Right stroke only cols 17-24 (8 dark) */
#define RB  _W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_D,_D,_D,_D,_D,_D,_D,_D,_W,_W,_W,_W,_W,_W,_W

/* Left stroke only cols 7-14 (8 dark) */
#define RC  _W,_W,_W,_W,_W,_W,_W,_D,_D,_D,_D,_D,_D,_D,_D,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W

/* Both side strokes cols 7-14 and 17-24 */
#define RD  _W,_W,_W,_W,_W,_W,_W,_D,_D,_D,_D,_D,_D,_D,_D,_W,_W,_D,_D,_D,_D,_D,_D,_D,_D,_W,_W,_W,_W,_W,_W,_W

/* =========================================================
 * Digit 0: oval — top/bottom bars + both side strokes
 * ========================================================= */
static const uint8_t digit_0[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RA, /* row  3  top bar */
    RA, /* row  4  top bar */
    RA, /* row  5  top bar */
    RD, /* row  6  both sides */
    RD, /* row  7 */
    RD, /* row  8 */
    RD, /* row  9 */
    RD, /* row 10 */
    RD, /* row 11 */
    RD, /* row 12 */
    RD, /* row 13 */
    RD, /* row 14 */
    RD, /* row 15 */
    RD, /* row 16 */
    RD, /* row 17 */
    RD, /* row 18 */
    RD, /* row 19 */
    RD, /* row 20 */
    RD, /* row 21 */
    RD, /* row 22 */
    RA, /* row 23  bottom bar */
    RA, /* row 24  bottom bar */
    RA, /* row 25  bottom bar */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 1: vertical bar on right side
 * ========================================================= */
static const uint8_t digit_1[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RB, /* row  3 */
    RB, /* row  4 */
    RB, /* row  5 */
    RB, /* row  6 */
    RB, /* row  7 */
    RB, /* row  8 */
    RB, /* row  9 */
    RB, /* row 10 */
    RB, /* row 11 */
    RB, /* row 12 */
    RB, /* row 13 */
    RB, /* row 14 */
    RB, /* row 15 */
    RB, /* row 16 */
    RB, /* row 17 */
    RB, /* row 18 */
    RB, /* row 19 */
    RB, /* row 20 */
    RB, /* row 21 */
    RB, /* row 22 */
    RB, /* row 23 */
    RB, /* row 24 */
    RB, /* row 25 */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 2: top bar + right-top stroke + middle bar +
 *          left-bottom stroke + bottom bar
 * ========================================================= */
static const uint8_t digit_2[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RA, /* row  3  top bar */
    RA, /* row  4  top bar */
    RA, /* row  5  top bar */
    RB, /* row  6  upper-right stroke */
    RB, /* row  7 */
    RB, /* row  8 */
    RB, /* row  9 */
    RB, /* row 10 */
    RB, /* row 11 */
    RA, /* row 12  middle bar */
    RA, /* row 13  middle bar */
    RA, /* row 14  middle bar */
    RC, /* row 15  lower-left stroke */
    RC, /* row 16 */
    RC, /* row 17 */
    RC, /* row 18 */
    RC, /* row 19 */
    RC, /* row 20 */
    RC, /* row 21 */
    RA, /* row 22  bottom bar */
    RA, /* row 23  bottom bar */
    RA, /* row 24  bottom bar */
    RA, /* row 25  bottom bar */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 3: top/middle/bottom bars + right strokes only
 * ========================================================= */
static const uint8_t digit_3[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RW, /* row  3 */
    RA, /* row  4  top bar */
    RA, /* row  5  top bar */
    RA, /* row  6  top bar */
    RB, /* row  7  upper-right stroke */
    RB, /* row  8 */
    RB, /* row  9 */
    RB, /* row 10 */
    RB, /* row 11 */
    RA, /* row 12  middle bar */
    RA, /* row 13  middle bar */
    RA, /* row 14  middle bar */
    RB, /* row 15  lower-right stroke */
    RB, /* row 16 */
    RB, /* row 17 */
    RB, /* row 18 */
    RB, /* row 19 */
    RB, /* row 20 */
    RB, /* row 21 */
    RA, /* row 22  bottom bar */
    RA, /* row 23  bottom bar */
    RA, /* row 24  bottom bar */
    RA, /* row 25  bottom bar */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 4: left-top stroke + middle bar + right full stroke
 * ========================================================= */
static const uint8_t digit_4[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RW, /* row  3 */
    RD, /* row  4  both sides top */
    RD, /* row  5 */
    RD, /* row  6 */
    RD, /* row  7 */
    RD, /* row  8 */
    RD, /* row  9 */
    RD, /* row 10 */
    RD, /* row 11 */
    RA, /* row 12  middle bar (crossing) */
    RA, /* row 13  middle bar */
    RB, /* row 14  right stroke only */
    RB, /* row 15 */
    RB, /* row 16 */
    RB, /* row 17 */
    RB, /* row 18 */
    RB, /* row 19 */
    RB, /* row 20 */
    RB, /* row 21 */
    RB, /* row 22 */
    RB, /* row 23 */
    RB, /* row 24 */
    RB, /* row 25 */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 5: top bar + left-top stroke + middle bar +
 *          right-bottom stroke + bottom bar
 * ========================================================= */
static const uint8_t digit_5[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RA, /* row  3  top bar */
    RA, /* row  4  top bar */
    RA, /* row  5  top bar */
    RC, /* row  6  upper-left stroke */
    RC, /* row  7 */
    RC, /* row  8 */
    RC, /* row  9 */
    RC, /* row 10 */
    RC, /* row 11 */
    RA, /* row 12  middle bar */
    RA, /* row 13  middle bar */
    RA, /* row 14  middle bar */
    RB, /* row 15  lower-right stroke */
    RB, /* row 16 */
    RB, /* row 17 */
    RB, /* row 18 */
    RB, /* row 19 */
    RB, /* row 20 */
    RB, /* row 21 */
    RA, /* row 22  bottom bar */
    RA, /* row 23  bottom bar */
    RA, /* row 24  bottom bar */
    RA, /* row 25  bottom bar */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 6: top bar + left full stroke + middle bar +
 *          both-sides bottom + bottom bar
 * ========================================================= */
static const uint8_t digit_6[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RA, /* row  3  top bar */
    RA, /* row  4  top bar */
    RA, /* row  5  top bar */
    RC, /* row  6  left stroke */
    RC, /* row  7 */
    RC, /* row  8 */
    RC, /* row  9 */
    RC, /* row 10 */
    RC, /* row 11 */
    RA, /* row 12  middle bar */
    RA, /* row 13  middle bar */
    RA, /* row 14  middle bar */
    RD, /* row 15  both sides */
    RD, /* row 16 */
    RD, /* row 17 */
    RD, /* row 18 */
    RD, /* row 19 */
    RD, /* row 20 */
    RD, /* row 21 */
    RA, /* row 22  bottom bar */
    RA, /* row 23  bottom bar */
    RA, /* row 24  bottom bar */
    RA, /* row 25  bottom bar */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 7: top bar + right stroke descending
 * ========================================================= */
static const uint8_t digit_7[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RA, /* row  3  top bar */
    RA, /* row  4  top bar */
    RA, /* row  5  top bar */
    RB, /* row  6  right stroke */
    RB, /* row  7 */
    RB, /* row  8 */
    RB, /* row  9 */
    RB, /* row 10 */
    RB, /* row 11 */
    RB, /* row 12 */
    RB, /* row 13 */
    RB, /* row 14 */
    RB, /* row 15 */
    RB, /* row 16 */
    RB, /* row 17 */
    RB, /* row 18 */
    RB, /* row 19 */
    RB, /* row 20 */
    RB, /* row 21 */
    RB, /* row 22 */
    RB, /* row 23 */
    RB, /* row 24 */
    RB, /* row 25 */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 8: top/middle/bottom bars + both side strokes
 * ========================================================= */
static const uint8_t digit_8[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RA, /* row  3  top bar */
    RA, /* row  4  top bar */
    RA, /* row  5  top bar */
    RD, /* row  6  both sides */
    RD, /* row  7 */
    RD, /* row  8 */
    RD, /* row  9 */
    RD, /* row 10 */
    RD, /* row 11 */
    RA, /* row 12  middle bar */
    RA, /* row 13  middle bar */
    RA, /* row 14  middle bar */
    RD, /* row 15  both sides */
    RD, /* row 16 */
    RD, /* row 17 */
    RD, /* row 18 */
    RD, /* row 19 */
    RD, /* row 20 */
    RD, /* row 21 */
    RA, /* row 22  bottom bar */
    RA, /* row 23  bottom bar */
    RA, /* row 24  bottom bar */
    RA, /* row 25  bottom bar */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 9: top bar + both-sides top + middle bar +
 *          right-bottom stroke + bottom bar
 * ========================================================= */
static const uint8_t digit_9[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RA, /* row  3  top bar */
    RA, /* row  4  top bar */
    RA, /* row  5  top bar */
    RD, /* row  6  both sides */
    RD, /* row  7 */
    RD, /* row  8 */
    RD, /* row  9 */
    RD, /* row 10 */
    RD, /* row 11 */
    RA, /* row 12  middle bar */
    RA, /* row 13  middle bar */
    RA, /* row 14  middle bar */
    RB, /* row 15  right stroke only */
    RB, /* row 16 */
    RB, /* row 17 */
    RB, /* row 18 */
    RB, /* row 19 */
    RB, /* row 20 */
    RB, /* row 21 */
    RA, /* row 22  bottom bar */
    RA, /* row 23  bottom bar */
    RA, /* row 24  bottom bar */
    RA, /* row 25  bottom bar */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* Lookup table: digit index → image pointer */
static const uint8_t * const digits_table[10] = {
    digit_0, digit_1, digit_2, digit_3, digit_4,
    digit_5, digit_6, digit_7, digit_8, digit_9,
};

#undef _W
#undef _D
#undef RW
#undef RA
#undef RB
#undef RC
#undef RD

#endif /* DIGITS_H */
