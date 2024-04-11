#include "s21_decimal.h"

int s21_comparison(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  super_decimal num_1, num_2, summ;
  s21_bleach(&num_2);
  s21_bleach(&num_1);
  s21_bleach(&summ);
  s21_conversion(value_1, &num_1);
  s21_conversion(value_2, &num_2);
  s21_coice(&num_1, &num_2);
  s21_coice(&num_1, &num_2);
  if (s21_is_null(value_1) && s21_is_null(value_2)) {
    flag = 0;
  } else if (s21_get_znak(num_1) && !s21_get_znak(num_2)) {
    flag = 2;
  } else if (!s21_get_znak(num_1) && s21_get_znak(num_2)) {
    flag = 1;
  } else {
    for (int i = 2; i >= 0; i--) {
      if (num_1.bits[i] < num_2.bits[i]) {
        flag = 2;
        break;
      } else if (num_1.bits[i] > num_2.bits[i]) {
        flag = 1;
        break;
      }
    }
  }
  if (s21_get_znak(num_1) && s21_get_znak(num_2) && flag) {
    if (flag == 1) {
      flag = 2;
    } else {
      flag = 1;
    }
  }
  return flag;
}

// ==
int s21_is_equal(s21_decimal num_1, s21_decimal num_2) {
  int res = s21_comparison(num_1, num_2);
  if (res > 0) {
    res = 0;
  } else {
    res = 1;
  }
  return res;
}

// !=
int s21_is_not_equal(s21_decimal num_1, s21_decimal num_2) {
  return s21_is_equal(num_1, num_2) ? 0 : 1;
}

//<
int s21_is_less(s21_decimal num_1, s21_decimal num_2) {
  return s21_is_greater(num_2, num_1);
}

//>
int s21_is_greater(s21_decimal num_1, s21_decimal num_2) {
  int res = s21_comparison(num_1, num_2);
  if (res == 2) {
    res = 0;
  }
  return res;
}

// >=
int s21_is_greater_or_equal(s21_decimal num_1, s21_decimal num_2) {
  int res = s21_comparison(num_1, num_2);
  if (res == 0 || res == 1) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

// <=
int s21_is_less_or_equal(s21_decimal num_1, s21_decimal num_2) {
  int res = s21_comparison(num_1, num_2);
  if (res == 0 || res == 2) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}