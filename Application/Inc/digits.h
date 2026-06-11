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

/* Centered vertical cols 12-19 (8 dark) — digit 1 */
#define R1C _W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_D,_D,_D,_D,_D,_D,_D,_D,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W

/* Diagonal-mid cols 14-21 (8 dark) — digit 7 diagonal step */
#define RBM _W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W,_D,_D,_D,_D,_D,_D,_D,_D,_W,_W,_W,_W,_W,_W,_W,_W,_W,_W

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
 * Digit 1: thin centered vertical stroke (cols 12-19).
 *          Centered to match MNIST "1" position.
 * ========================================================= */
static const uint8_t digit_1[32*32*3] = {
    RW,  /* row  0 */
    RW,  /* row  1 */
    RW,  /* row  2 */
    R1C, /* row  3 */
    R1C, /* row  4 */
    R1C, /* row  5 */
    R1C, /* row  6 */
    R1C, /* row  7 */
    R1C, /* row  8 */
    R1C, /* row  9 */
    R1C, /* row 10 */
    R1C, /* row 11 */
    R1C, /* row 12 */
    R1C, /* row 13 */
    R1C, /* row 14 */
    R1C, /* row 15 */
    R1C, /* row 16 */
    R1C, /* row 17 */
    R1C, /* row 18 */
    R1C, /* row 19 */
    R1C, /* row 20 */
    R1C, /* row 21 */
    R1C, /* row 22 */
    R1C, /* row 23 */
    R1C, /* row 24 */
    R1C, /* row 25 */
    RW,  /* row 26 */
    RW,  /* row 27 */
    RW,  /* row 28 */
    RW,  /* row 29 */
    RW,  /* row 30 */
    RW,  /* row 31 */
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
 * Digit 4: right vertical from top, left arm joins midway,
 *          crossbar, right stem continues.
 *          Top has only the right stroke (unlike 8 which has
 *          symmetric both-side strokes from the top).
 * ========================================================= */
static const uint8_t digit_4[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RB, /* row  3  right stroke from top */
    RB, /* row  4 */
    RB, /* row  5 */
    RB, /* row  6 */
    RB, /* row  7 */
    RB, /* row  8 */
    RD, /* row  9  left arm joins (both sides) */
    RD, /* row 10 */
    RD, /* row 11 */
    RA, /* row 12  crossbar */
    RA, /* row 13  crossbar */
    RB, /* row 14  right stem only */
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
 * Digit 7: top bar + diagonal stroke.
 *          The stroke shifts LEFT as it goes DOWN:
 *            right (RB, cols 17-24) → center-right (RBM, cols 14-21)
 *            → center (R1C, cols 12-19).
 *          This diagonal distinguishes "7" from "2" (which
 *          has a horizontal bar, a right stroke, then a LEFT
 *          stroke — the opposite direction).
 * ========================================================= */
static const uint8_t digit_7[32*32*3] = {
    RW,  /* row  0 */
    RW,  /* row  1 */
    RW,  /* row  2 */
    RA,  /* row  3  top bar */
    RA,  /* row  4  top bar */
    RA,  /* row  5  top bar */
    RB,  /* row  6  right side (top of diagonal) */
    RB,  /* row  7 */
    RB,  /* row  8 */
    RB,  /* row  9 */
    RB,  /* row 10 */
    RB,  /* row 11 */
    RBM, /* row 12  center-right (mid diagonal) */
    RBM, /* row 13 */
    RBM, /* row 14 */
    RBM, /* row 15 */
    RBM, /* row 16 */
    RBM, /* row 17 */
    R1C, /* row 18  center (bottom of diagonal) */
    R1C, /* row 19 */
    R1C, /* row 20 */
    R1C, /* row 21 */
    R1C, /* row 22 */
    R1C, /* row 23 */
    R1C, /* row 24 */
    R1C, /* row 25 */
    RW,  /* row 26 */
    RW,  /* row 27 */
    RW,  /* row 28 */
    RW,  /* row 29 */
    RW,  /* row 30 */
    RW,  /* row 31 */
};

/* =========================================================
 * Digit 8: top bar + short upper loops + WIDE middle bar
 *          (6 rows) + short lower loops + bottom bar.
 *          The prominent middle bar clearly distinguishes "8"
 *          from "0" (which has no middle bar at all).
 * ========================================================= */
static const uint8_t digit_8[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RA, /* row  3  top bar */
    RA, /* row  4  top bar */
    RD, /* row  5  upper both sides */
    RD, /* row  6 */
    RD, /* row  7 */
    RD, /* row  8 */
    RD, /* row  9 */
    RA, /* row 10  middle bar (wide — 6 rows) */
    RA, /* row 11 */
    RA, /* row 12 */
    RA, /* row 13 */
    RA, /* row 14 */
    RA, /* row 15 */
    RD, /* row 16  lower both sides */
    RD, /* row 17 */
    RD, /* row 18 */
    RD, /* row 19 */
    RD, /* row 20 */
    RA, /* row 21  bottom bar */
    RA, /* row 22 */
    RA, /* row 23 */
    RA, /* row 24 */
    RA, /* row 25 */
    RW, /* row 26 */
    RW, /* row 27 */
    RW, /* row 28 */
    RW, /* row 29 */
    RW, /* row 30 */
    RW, /* row 31 */
};

/* =========================================================
 * Digit 9: compact top circle (top bar + both sides + bottom
 *          bar) followed by a long right-only tail.
 *          No bottom bar at the end of the tail — this
 *          distinguishes "9" from "3" (which has bottom bar).
 * ========================================================= */
static const uint8_t digit_9[32*32*3] = {
    RW, /* row  0 */
    RW, /* row  1 */
    RW, /* row  2 */
    RW, /* row  3 */
    RA, /* row  4  top of circle */
    RA, /* row  5 */
    RD, /* row  6  circle sides */
    RD, /* row  7 */
    RD, /* row  8 */
    RD, /* row  9 */
    RA, /* row 10  bottom of circle */
    RA, /* row 11 */
    RB, /* row 12  right tail starts */
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
#undef R1C
#undef RBM

#endif /* DIGITS_H */
