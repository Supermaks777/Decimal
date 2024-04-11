#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (s21_checking(value) || !result) {
    return 1;
  }
  int s_ost = 0;
  super_decimal itog;
  s21_bleach(&itog);
  s21_conversion(value, &itog);
  while (s21_get_scale(itog)) {
    s_ost += s21_scale_down(&itog);
  }
  if (s21_get_znak(itog) && s_ost) {
    itog.bits[0] += 1;
  }
  s21_conversion_decimal(itog, result);
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (s21_checking(value) || !result) {
    return 1;
  }
  int ost = 0;
  super_decimal itog;
  s21_bleach(&itog);
  s21_conversion(value, &itog);
  while (s21_get_scale(itog)) {
    ost = s21_scale_down(&itog);
  }
  if (ost >= 5) {
    itog.bits[0] += 1;
  }
  s21_conversion_decimal(itog, result);
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (s21_checking(value) || !result) {
    return 1;
  }
  s21_clear(result);
  *result = value;
  super_decimal itog;
  s21_bleach(&itog);
  s21_conversion(value, &itog);
  for (; s21_get_scale(itog) > 0;) {
    s21_scale_down(&itog);
  }
  s21_conversion_decimal(itog, result);
  return 0;
}

//умножение на -1
int s21_negate(s21_decimal value, s21_decimal *result) {
  int exit = 0;
  if (s21_checking(value)) {
    exit = 1;
  } else {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
    result->bits[3] += 1 << 31;
  }
  return exit;
}