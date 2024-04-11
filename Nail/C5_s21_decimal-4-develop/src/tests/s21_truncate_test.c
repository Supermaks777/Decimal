#include "s21_test.h"

// ORDINARY TESTS
START_TEST(truncate_test_1) {
  s21_decimal values[] = {
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  //                  0
      {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  //                  1
      {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //                 -1
      {{0xCF5C048C, 0x004D2BEF, 0x00000000, 0x00070000}},  // 2172188218.2812812
      {{0xFEADBDA2, 0x000001FB, 0x00000000, 0x80060000}},  //    -2181821.218210
      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},
      //                                           79228162514264337593543950335
      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
      //                                          -79228162514264337593543950335
      {{0x00000000, 0x00000000, 0x00000000, 0x00020000}},  //               0.00
      {{0x00000000, 0x00000000, 0x00000000, 0x80020000}},  //               0.00
      {{0x000F4240, 0x00000000, 0x00000000, 0x00020000}},  //           10000.00
      {{0x000F4240, 0x00000000, 0x00000000, 0x80020000}},  //          -10000.00
      {{0x00000467, 0x0000007A, 0x00000000, 0x00040000}},  //      52398601.1239
      {{0x00000467, 0x0000007A, 0x00000000, 0x80000000}},  //      -523986011239
      {{0x00000467, 0x0000007A, 0x00003215, 0x00010000}},
      //                                               23650570576955414727997.5
      {{0x00000467, 0x0000007A, 0x00205FF0, 0x80020000}},
      //                                            -391386782621189641642978.31
      {{0x000F4240, 0x00002710, 0x00002710, 0x80050000}},
      //                                              -1844674407800451901.20000
      {{0x0000000E, 0x00000000, 0x00000000, 0x00000000}},  //                 14
      {{0x0000000F, 0x00000000, 0x00000000, 0x80000000}},  //                -15
      {{0x000186A0, 0x00000000, 0x00000000, 0x00000000}},  //             100000
      {{0x0000000B, 0x00000000, 0x00000000, 0x00010000}},  //                1.1
      {{0x0000000B, 0x00000000, 0x00000000, 0x80010000}},  //               -1.1
      {{0x0000000F, 0x00000000, 0x00000000, 0x80010000}},  //               -1.5
      {{0x0000000F, 0x00000000, 0x00000000, 0x00010000}},  //                1.5
      {{0x00000086, 0x00000000, 0x00000000, 0x80020000}},  //              -1.34
      {{0x00000086, 0x00000000, 0x00000000, 0x00020000}},  //               1.34
      {{0x000006E5, 0x00000000, 0x00000000, 0x00030000}},  //              1.765
      {{0x000006E5, 0x00000000, 0x00000000, 0x80030000}},  //             -1.765
      {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  //                2.5
      {{0x00000019, 0x00000000, 0x00000000, 0x80010000}},  //               -2.5
      {{0x1FC40A5F, 0xA98FD4BE, 0x00000000, 0x00020000}},
      //                                                   122182182271212611.51
      {{0x1FC40A5D, 0xA98FD4BE, 0x00000000, 0x00020000}},
      //                                                   122182182271212611.49
      {{0x1FC40A5F, 0xA98FD4BE, 0x00000000, 0x80020000}},
      //                                                  -122182182271212611.51
      {{0x1FC40A5D, 0xA98FD4BE, 0x00000000, 0x80020000}},
      //                                                  -122182182271212611.49
      {{0x075BCD15, 0x00000000, 0x00000000, 0x00030000}},  //         123456.789
      {{0x075BCD15, 0x00000000, 0x00000000, 0x00090000}},  //        0.123456789
      {{0x075BCD15, 0x00000000, 0x00000000, 0x00120000}},
      //                                                    0.000000000123456789
      {{0x075BCD15, 0x00000000, 0x00000000, 0x001B0000}},
      //                                           0.000000000000000000123456789
      {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00060000}},  //        4294.967295
      {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00050000}},
      //                                                   184467440737095.51615
      {{0x075BCD15, 0x00000000, 0x00000000, 0x801B0000}},
      //                                          -0.000000000000000000123456789
      {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x80060000}},  //       -4294.967295
      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}},
      //                                          7.9228162514264337593543950335
      {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x80050000}},
      //                                                  -184467440737095.51615
      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}}
      //                                         -7.9228162514264337593543950335
  };

  s21_decimal results[] = {
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  //                  0
      {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  //                  1
      {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //                 -1
      {{0x8178F63A, 0x00000000, 0x00000000, 0x00000000}},  //         2172188218
      {{0x00214ABD, 0x00000000, 0x00000000, 0x80000000}},  //           -2181821
      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},
      //                                           79228162514264337593543950335
      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
      //                                          -79228162514264337593543950335
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  //                  0
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  //                  0
      {{0x00002710, 0x00000000, 0x00000000, 0x00000000}},  //              10000
      {{0x00002710, 0x00000000, 0x00000000, 0x80000000}},  //             -10000
      {{0x031F8A09, 0x00000000, 0x00000000, 0x00000000}},  //           52398601
      {{0x00000467, 0x0000007A, 0x00000000, 0x80000000}},  //      -523986011239
      {{0xCCCCCD3D, 0x199999A5, 0x00000502, 0x00000000}},
      //                                                 23650570576955414727997
      {{0xBD70A3E2, 0x1EB851EC, 0x000052E1, 0x80000000}},
      //                                               -391386782621189641642978
      {{0xB333333D, 0x19999999, 0x00000000, 0x80000000}},
      //                                                    -1844674407800451901
      {{0x0000000E, 0x00000000, 0x00000000, 0x00000000}},  //                 14
      {{0x0000000F, 0x00000000, 0x00000000, 0x80000000}},  //                -15
      {{0x000186A0, 0x00000000, 0x00000000, 0x00000000}},  //             100000
      {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  //                  1
      {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //                 -1
      {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //                 -1
      {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  //                  1
      {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //                 -1
      {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  //                  1
      {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  //                  1
      {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //                 -1
      {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  //                  2
      {{0x00000002, 0x00000000, 0x00000000, 0x80000000}},  //                 -2
      {{0x24285C43, 0x01B2140C, 0x00000000, 0x00000000}},  // 122182182271212611
      {{0x24285C43, 0x01B2140C, 0x00000000, 0x00000000}},  // 122182182271212611
      {{0x24285C43, 0x01B2140C, 0x00000000, 0x80000000}},  //-122182182271212611
      {{0x24285C43, 0x01B2140C, 0x00000000, 0x80000000}},  //-122182182271212611
      {{0x0001E240, 0x00000000, 0x00000000, 0x00000000}},  //             123456
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  //                  0
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  //                  0
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  //                  0
      {{0x000010C6, 0x00000000, 0x00000000, 0x00000000}},  //               4294
      {{0xAC471B47, 0x0000A7C5, 0x00000000, 0x00000000}},  //    184467440737095
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  //                  0
      {{0x000010C6, 0x00000000, 0x00000000, 0x80000000}},  //              -4294
      {{0x00000007, 0x00000000, 0x00000000, 0x00000000}},  //                  7
      {{0xAC471B47, 0x0000A7C5, 0x00000000, 0x80000000}},  //   -184467440737095
      {{0x00000007, 0x00000000, 0x00000000, 0x80000000}},  //                 -7
  };

  for (size_t i = 0; i < sizeof(values) / sizeof(s21_decimal); i++) {
    s21_decimal res;
    int ret = s21_truncate(values[i], &res);
    ck_assert_int_eq(res.bits[0], results[i].bits[0]);
    ck_assert_int_eq(res.bits[1], results[i].bits[1]);
    ck_assert_int_eq(res.bits[2], results[i].bits[2]);
    ck_assert_int_eq(res.bits[3], results[i].bits[3]);
    ck_assert_int_eq(ret, FALSE);
  }
}
END_TEST

// ERROR TEST
START_TEST(truncate_test_2) {
  s21_decimal error_value_1 = {
      {0x0000000A, 0x0000000D, 0x0000033B, 0x001E0000}};
  s21_decimal error_value_2;
  int ret = s21_truncate(error_value_1, &error_value_2);
  ck_assert_int_eq(ret, TRUE);
}
END_TEST

Suite* s21_truncate_suite(void) {
  Suite* s;
  s = suite_create("\033[33ms21_truncate\033[0m");

  TCase* tc_core;
  tc_core = tcase_create("s21_truncate_core");
  tcase_add_test(tc_core, truncate_test_1);
  tcase_add_test(tc_core, truncate_test_2);
  suite_add_tcase(s, tc_core);

  return s;
}