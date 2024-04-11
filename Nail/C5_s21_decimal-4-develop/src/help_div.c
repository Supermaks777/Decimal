#include "s21_decimal.h"

// делимое меньше делителя
// делимое нужно нарастить за счёт экспоненты
void s21_dividend_is_less(s21_decimal *divident, s21_decimal divider,
                          int *exponent) {
  s21_decimal ten = {{10, 0, 0, 0}};
  while (s21_is_less(*divident, divider)) {
    s21_mul(*divident, ten, divident);
    (*exponent)++;
  }
}

void s21_generate_exponent(s21_decimal *sub_divident, s21_decimal divider,
                           s21_decimal *divident, int *exponent) {
  s21_decimal ten = {{10, 0, 0, 0}};

  while (s21_is_greater(divider, *sub_divident)) {
    (*exponent)++;
    s21_mul(*sub_divident, ten, sub_divident);
  }
  *divident = *sub_divident;
}

// вычисляю первичный под_делитель
// изменяет по ссылке sub_divident - подделитель
// делитель и делимое не должны быть равны, нужно делать проверку до.
void s21_get_sub_divident(int *cursor, s21_decimal divident,
                          s21_decimal *sub_divident, s21_decimal divider) {
  bool shift_cursor = true;

  sub_divident->bits[0] = divident.bits[0];
  sub_divident->bits[1] = divident.bits[1];
  sub_divident->bits[2] = divident.bits[2];
  sub_divident->bits[3] = divident.bits[3];

  for (int i = *cursor; shift_cursor; i--) {
    *cursor = i;
    s21_shift_bit(sub_divident, i, 1);
    if (s21_is_greater(divider, *sub_divident)) {
      shift_cursor = true;

      sub_divident->bits[0] = divident.bits[0];
      sub_divident->bits[1] = divident.bits[1];
      sub_divident->bits[2] = divident.bits[2];
      sub_divident->bits[3] = divident.bits[3];

    } else {
      shift_cursor = false;
    }
  }
}

void s21_array_add(s21_decimal *array, int index, s21_decimal num) {
  array[index] = num;
}

// Финальный ответ матиссы
void s21_array_sum(s21_decimal *answer, s21_decimal *array, int exponent) {
  s21_decimal sub_result = {{0, 0, 0, 0}};
  int index = exponent;
  for (int i = 0; i <= exponent; i++) {
    s21_mul(array[i], s21_degree_ten(index), &sub_result);
    s21_add(*answer, sub_result, answer);
    index--;
  }
  answer->bits[3] = exponent << 16;
}

// возводит 10 в степень
s21_decimal s21_degree_ten(int degree) {
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal num = {{0, 0, 0, 0}};
  num = ten;

  if (degree == 0) {
    s21_clear(&num);
    num.bits[0] = 1;
  } else if (degree > 1) {
    for (int i = 1; i < degree; i++) {
      s21_mul(num, ten, &num);
    }
  }

  return num;
}

// Сдвигает decimal побитово.
// direction = 1 вправо, 0 влево.
// [95…64][63…32][31…0]
void s21_shift_bit(s21_decimal *num, int step, int direction) {
  if (direction) {
    for (; step > 0; step--) {
      unsigned int junior_bit_1 = s21_get_bit_decimal(*num, JUNIOR_BIT_1);
      unsigned int junior_bit_2 = s21_get_bit_decimal(*num, JUNIOR_BIT_2);

      num->bits[0] = num->bits[0] >> 1;
      num->bits[1] = num->bits[1] >> 1;
      num->bits[2] = num->bits[2] >> 1;

      s21_set_bit_decimal(num, SENIOR_BIT_0, junior_bit_1);
      s21_set_bit_decimal(num, SENIOR_BIT_1, junior_bit_2);
    }
  } else {
    for (; step > 0; step--) {
      unsigned int senior_bit_0 = s21_get_bit_decimal(*num, SENIOR_BIT_0);
      unsigned int senior_bit_1 = s21_get_bit_decimal(*num, SENIOR_BIT_1);

      num->bits[0] = num->bits[0] << 1;
      num->bits[1] = num->bits[1] << 1;
      num->bits[2] = num->bits[2] << 1;

      s21_set_bit_decimal(num, JUNIOR_BIT_1, senior_bit_0);
      s21_set_bit_decimal(num, JUNIOR_BIT_2, senior_bit_1);
    }
  }
}

// генерирует ответ деления (частное)
void s21_generation_answer(s21_decimal *sub_result, bool volume) {
  s21_shift_bit(sub_result, 1, 0);
  s21_set_bit_decimal(sub_result, 0, volume);
}

// перенос бита из делимого в под_делимое
void s21_down_bit(s21_decimal *sub_divident, s21_decimal divident, int cursor) {
  s21_shift_bit(sub_divident, 1, 0);
  bool bit = s21_get_bit_decimal(divident, cursor);
  s21_set_bit_decimal(sub_divident, 0, bit);
}

// генерирует масштаб для ответа
int s21_generation_scale(int scale_divident, int scale_divider, int *exponent,
                         s21_decimal *num) {
  int mult_result = 0;
  s21_decimal ten = {{10, 0, 0, 0}};

  int tmp = (scale_divident - scale_divider) + (*exponent);

  if (tmp < 0) {
    tmp = tmp * -1;

    for (int i = tmp; i > 0; i--) {
      mult_result = s21_mul(*num, ten, num);

      if (mult_result == 1) {
        i = 0;

      } else if (mult_result == 2) {
        i = 0;
      }
    }

    tmp = 0;
  }

  if (mult_result == 0) {
    *exponent = tmp;
    s21_set_scale_decimal(num, *exponent);
  }
  return mult_result;
}

void s21_generation_sign(s21_decimal *num, bool sign_divident,
                         bool sign_divider) {
  if ((!sign_divident && sign_divider) || (sign_divident && !sign_divider)) {
    s21_set_znak_decimal(num, 1);
  }
}
void s21_bit_3_nool(s21_decimal *divident, s21_decimal *divider) {
  s21_set_scale_decimal(divident, 0);
  s21_set_scale_decimal(divider, 0);
  s21_set_znak_decimal(divident, 0);
  s21_set_znak_decimal(divider, 0);
}

void s21_myn_culc(s21_decimal divident, s21_decimal divider,
                  s21_decimal *all_sub_result, int *exponent,
                  bool div_remainder, int cursor) {
  while (div_remainder && *exponent <= 27) {
    s21_decimal sub_result = {{0, 0, 0, 0}};
    s21_decimal sub_divident = {{0, 0, 0, 0}};
    cursor = GLOBAL_SENIOR_BIT;
    s21_get_sub_divident(&cursor, divident, &sub_divident, divider);
    s21_generation_answer(&sub_result, true);
    s21_sub(sub_divident, divider, &sub_divident);
    cursor--;
    while (cursor > 0 || cursor == 0) {
      s21_down_bit(&sub_divident, divident, cursor);
      if (s21_is_greater(divider, sub_divident)) {
        cursor--;
        s21_generation_answer(&sub_result, false);
        continue;
      }
      s21_generation_answer(&sub_result, true);
      s21_sub(sub_divident, divider, &sub_divident);
      cursor--;
    }
    if (s21_is_null(sub_divident)) {
      s21_array_add(all_sub_result, *exponent, sub_result);
      div_remainder = false;
    } else {
      div_remainder = true;
      s21_array_add(all_sub_result, *exponent, sub_result);
      s21_generate_exponent(&sub_divident, divider, &divident, exponent);
    }
  }
}