#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0xFFFFFFFF
#define S_MAX 0xFFFFFFFFFFFFFFFF

#define BUF 64
#define S21_MAX_FLOAT 79228162514264337593543950335.0F
#define S21_MIN_FLOAT 1E-28
#define S21_MAX_INT 2147483647

#define SENIOR_BIT_0 31
#define SENIOR_BIT_1 63
#define JUNIOR_BIT_1 32
#define JUNIOR_BIT_2 64
#define GLOBAL_SENIOR_BIT 95

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  uint64_t bits[6];
  uint32_t scale;
} super_decimal;

void s21_bit_print_decimal(s21_decimal num);
void s21_bit_print(super_decimal num);
uint64_t s21_get_bit(super_decimal sis, int index);
int s21_get_bit_decimal(s21_decimal num, int index);
int s21_get_znak(super_decimal num);
int s21_get_znak_decimal(s21_decimal num);
int s21_get_scale(super_decimal num);
int s21_get_scale_decimal(s21_decimal num);
void s21_addition(super_decimal *num, int index, int znach);
void s21_set_bit(super_decimal *num, int index, int znach);
void s21_set_bit_decimal(s21_decimal *num, int index, int znach);
void s21_set_scale(super_decimal *num, int scale);
void s21_set_znak(super_decimal *num, int znak);
void s21_set_znak_decimal(s21_decimal *num, int znak);
void s21_bleach(super_decimal *num);
void s21_clear(s21_decimal *num);
void s21_coice(super_decimal *num_1, super_decimal *num_2);
void s21_normalization(super_decimal *result, int scale);
int s21_is_null(s21_decimal num);
void s21_conversion(s21_decimal num, super_decimal *result);
int s21_get_overflow(super_decimal *num);
void s21_summa(super_decimal num_1, super_decimal num_2, super_decimal *summ);
int s21_comparison(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_step(s21_decimal num_1, int move);
void s21_scale_up(super_decimal *num);
uint64_t s21_scale_down(super_decimal *num);
void s21_mult_bu_10(s21_decimal *num);
void s21_bank(super_decimal *num, int ost, int s_ost);
void s21_preparation(super_decimal *num_1, super_decimal *num_2,
                     super_decimal *itog, s21_decimal value_1,
                     s21_decimal value_2);
void s21_set_scale_decimal(s21_decimal *num, int scale);
void s21_left(super_decimal num, super_decimal *result, int i);
int s21_nan(s21_decimal value);
int s21_infinity(s21_decimal value);
int s21_last_bit(s21_decimal value);
int s21_degree_range(s21_decimal value);
int s21_checking(s21_decimal value);
void s21_conversion_decimal(super_decimal num, s21_decimal *result);
int s21_checking_float(float value);
void s21_conversion_float(float src, unsigned int *mantissa, int *scale);
int s21_scale_checking(s21_decimal *dst, int scale);
void s21_dividend_is_less(s21_decimal *divident, s21_decimal divider,
                          int *exponent);
void s21_generate_exponent(s21_decimal *sub_divident, s21_decimal divider,
                           s21_decimal *divident, int *exponent);
int s21_is_full_matisse(s21_decimal num_1);
void s21_get_sub_divident(int *cursor, s21_decimal divident,
                          s21_decimal *sub_divident, s21_decimal divider);
void s21_array_add(s21_decimal *array, int index, s21_decimal num);
void s21_array_sum(s21_decimal *answer, s21_decimal *array, int exponent);
s21_decimal s21_degree_ten(int degree);
void s21_shift_bit(s21_decimal *num, int step, int direction);
void s21_generation_answer(s21_decimal *sub_result, bool volume);
void s21_down_bit(s21_decimal *sub_divident, s21_decimal divident, int cursor);
void s21_down_zero_bit(s21_decimal *sub_divident);
int s21_generation_scale(int scale_divident, int scale_divider, int *exponent,
                         s21_decimal *num);
void s21_generation_sign(s21_decimal *num, bool sign_divident,
                         bool sign_divider);
void s21_bit_3_nool(s21_decimal *divident, s21_decimal *divider);
void s21_sub_nool(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);
void s21_myn_culc(s21_decimal divident, s21_decimal divider,
                  s21_decimal *all_sub_result, int *exponent,
                  bool div_remainder, int cursor);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_is_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_not_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_less(s21_decimal num_1, s21_decimal num_2);
int s21_is_greater(s21_decimal num_1, s21_decimal num_2);
int s21_is_greater_or_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_less_or_equal(s21_decimal num_1, s21_decimal num_2);

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

#endif