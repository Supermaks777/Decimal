#include "s21_decimal.h"

// функйия сложения
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit = 0;
  int ost = 0;
  int s_ost = 0;
  s21_clear(result);
  if (s21_is_null(value_1) == 1 || s21_is_null(value_2) == 1) {
    if (s21_is_null(value_1) == 1 && s21_is_null(value_2) == 1) {
      s21_clear(result);
    } else if (s21_is_null(value_1) == 1 && s21_is_null(value_2) == 0) {
      *result = value_2;
    } else if (s21_is_null(value_1) == 0 && s21_is_null(value_2) == 1) {
      *result = value_1;
    }
  } else {
    if (s21_get_znak_decimal(value_1) == 0 &&
        s21_get_znak_decimal(value_2) == 1) {
      s21_set_znak_decimal(&value_2, 0);
      exit = s21_sub(value_1, value_2, result);
    } else if (s21_get_znak_decimal(value_1) == 1 &&
               s21_get_znak_decimal(value_2) == 0) {
      s21_set_znak_decimal(&value_1, 0);
      exit = s21_sub(value_2, value_1, result);
    } else if (s21_get_znak_decimal(value_1) == s21_get_znak_decimal(value_2)) {
      super_decimal num_1, num_2, itog;
      s21_preparation(&num_1, &num_2, &itog, value_1, value_2);
      s21_coice(&num_1, &num_2);
      for (int i = 0; i < 6; i++) {
        itog.bits[i] = num_1.bits[i] + num_2.bits[i];
      }
      s21_set_scale(&itog, s21_get_scale(num_2));
      s21_set_znak(&itog, s21_get_znak(num_2));
      while (s21_get_overflow(&itog) && s21_get_scale(itog)) {
        s_ost += ost;
        ost = s21_scale_down(&itog);
      }
      s21_bank(&itog, ost, s_ost);
      if (s21_get_overflow(&itog) == 0) {
        s21_conversion_decimal(itog, result);
      } else if (!s21_get_znak(itog)) {
        exit = 1;
      } else if (s21_get_znak(itog)) {
        exit = 2;
      }
    }
  }
  return exit;
}

// функция вычитания
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit = 0, ost = 0, s_ost = 0;
  s21_clear(result);
  if (s21_is_null(value_1) == 1 || s21_is_null(value_2) == 1)
    s21_sub_nool(value_1, value_2, result);
  else {
    if (s21_get_znak_decimal(value_1) == 0 &&
        s21_get_znak_decimal(value_2) == 1) {
      s21_set_znak_decimal(&value_2, 0);
      exit = s21_add(value_1, value_2, result);
    } else if (s21_get_znak_decimal(value_1) == 1 &&
               s21_get_znak_decimal(value_2) == 0) {
      s21_set_znak_decimal(&value_1, 0);
      exit = s21_add(value_1, value_2, result) ? 2 : 0;
      s21_set_znak_decimal(result, exit ? 0 : 1);
    } else if (s21_get_znak_decimal(value_1) == s21_get_znak_decimal(value_2)) {
      int znak = 0;
      if (s21_is_less(value_1, value_2)) {
        znak = 1;
      }
      if ((s21_get_znak_decimal(value_1) == 1 &&
           s21_is_less(value_2, value_1)) ||
          (s21_is_less(value_1, value_2) &&
           s21_get_znak_decimal(value_1) == 0)) {
        s21_decimal swap = value_1;
        value_1 = value_2;
        value_2 = swap;
      }
      super_decimal num_1, num_2, itog;
      s21_preparation(&num_1, &num_2, &itog, value_1, value_2);
      s21_coice(&num_1, &num_2);
      for (int i = 0; i < 6; i++) {
        if (num_1.bits[i] < num_2.bits[i]) {
          num_1.bits[i] |= (uint64_t)1 << 32;
          num_1.bits[i + 1] -= 1;
        }
        itog.bits[i] = num_1.bits[i] - num_2.bits[i];
      }
      s21_set_scale(&itog, s21_get_scale(num_2));
      while (s21_get_overflow(&itog) && s21_get_scale(itog)) {
        s_ost += ost;
        ost = s21_scale_down(&itog);
      }
      s21_bank(&itog, ost, s_ost);
      if (s21_get_overflow(&itog) == 0) {
        s21_conversion_decimal(itog, result);
        s21_set_znak_decimal(result, znak);
      } else if (!s21_get_znak(itog))
        exit = 1;
      else if (s21_get_znak(itog))
        exit = 2;
    }
  }
  return exit;
}

// функция умножения
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit = 0;
  int ost = 0;
  int s_ost = 0;
  int znak = 0;
  s21_clear(result);
  if (s21_is_null(value_1) == 1 || s21_is_null(value_2) == 1) {
    s21_clear(result);
  } else {
    if ((s21_get_znak_decimal(value_1) || s21_get_znak_decimal(value_2)) &&
        !((s21_get_znak_decimal(value_1) && s21_get_znak_decimal(value_2)))) {
      znak = 1;
    }
    int scale = s21_get_scale_decimal(value_1) + s21_get_scale_decimal(value_2);
    super_decimal buff, num_1, num_2, itog;
    s21_preparation(&num_1, &num_2, &itog, value_1, value_2);
    for (int i = 0; i < 384; i++) {
      s21_bleach(&buff);
      if (s21_get_bit(num_2, i)) {
        s21_left(num_1, &buff, i);
        s21_summa(itog, buff, &itog);
        s21_get_overflow(&itog);
      }
    }
    s21_set_scale(&itog, scale);
    s21_set_znak(&itog, znak);
    while ((s21_get_overflow(&itog) && s21_get_scale(itog)) ||
           s21_get_scale(itog) > 28) {
      s_ost += ost;
      ost = s21_scale_down(&itog);
    }
    s21_bank(&itog, ost, s_ost);
    if (s21_get_overflow(&itog) == 0) {
      s21_conversion_decimal(itog, result);
    } else if (!s21_get_znak(itog)) {
      exit = 1;
    } else if (s21_get_znak(itog)) {
      exit = 2;
    }
  }
  return exit;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit = 0;
  bool continue_calc = true;
  s21_decimal divident = value_1, divider = value_2;
  int cursor = 0, exponent = 0;
  bool div_remainder = true;
  s21_decimal all_sub_result[50] = {{{0, 0, 0, 0}}}, zero = {0};
  s21_clear(result);
  int scale_divident = s21_get_scale_decimal(divident),
      scale_divider = s21_get_scale_decimal(divider);
  bool sign_divident = s21_get_znak_decimal(divident),
       sign_divider = s21_get_znak_decimal(divider);
  s21_bit_3_nool(&divident, &divider);
  if (s21_is_equal(divider, zero)) {
    exit = 3;
    continue_calc = false;
  }
  if (s21_is_equal(divident, zero) && continue_calc) {
    s21_clear(result);
    continue_calc = false;
  }
  if (continue_calc) {
    if (s21_is_less(divident, divider))
      s21_dividend_is_less(&divident, divider, &exponent);
    s21_myn_culc(divident, divider, all_sub_result, &exponent, div_remainder,
                 cursor);
    s21_array_sum(result, all_sub_result, exponent);
    exit =
        s21_generation_scale(scale_divident, scale_divider, &exponent, result);
    if (exit == 1) {
      if (sign_divider) {
        exit = 2;
        s21_clear(result);
      }
    }
    if (exit == 0) s21_generation_sign(result, sign_divident, sign_divider);
  }
  return exit;
}