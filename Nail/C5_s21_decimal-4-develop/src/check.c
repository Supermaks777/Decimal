#include "s21_decimal.h"

// проверка nan
int s21_nan(s21_decimal value) {
  int flag = 1;
  for (int i = 111; i <= 118; i++) {
    if (s21_get_bit_decimal(value, i) == 0) flag = 0;
  }
  return flag;
}

// бесконечность (infinity)
int s21_infinity(s21_decimal value) {
  int flag = 1;
  for (int i = 111; i <= 118; i++) {
    if (s21_get_bit_decimal(value, i) == 0) flag = 0;
  }
  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit_decimal(value, i) == 1) flag = 0;
  }
  return flag;
}

// проверка последнего бита
int s21_last_bit(s21_decimal value) {
  int flag = 0;
  for (int i = 127; i >= 96; i--) {
    if (s21_get_bit_decimal(value, i)) {
      if (i != 127 && (i < 112 || i > 119)) {
        flag = 1;
      }
    }
  }
  return flag;
}

// диапазон  степени
int s21_degree_range(s21_decimal value) {
  return s21_get_scale_decimal(value) < 0 || s21_get_scale_decimal(value) > 28;
}

// проверка краевых, для округления
int s21_checking(s21_decimal value) {
  return s21_nan(value) || s21_degree_range(value) || s21_infinity(value) ||
         s21_last_bit(value);
}
