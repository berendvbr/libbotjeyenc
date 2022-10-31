#include "test_botje_yenc__encode.h"

void test_botje_yenc__encode_test(void **state) {

  unsigned char *str_dst = calloc(1, 16);
  unsigned char *str_src = calloc(1, 16);
  int64_t num_chars;
  int64_t str_src_len;

  // test 1
  // decimal 65 (char 'A') is NOT a special char so only +42 -> decimal 107 (char 'k')
  str_src_len = 1;
  str_src[0] = 'A';
  num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 1);
  assert_int_equal(str_dst[0], 'k');

  // test 2
  // decimal 66 (char 'B') is NOT a special char so only +42 -> decimal 108 (char 'l')
  str_src_len = 1;
  str_src[0] = 'B';
  num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 1);
  assert_int_equal(str_dst[0], 'l');

  // test 3
  // decimal 214 + 42 % 256 -> 0, decimal 0 is special char (NUL) -> +64
  str_src_len = 1;
  str_src[0] = 214;
  num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 2);
  assert_int_equal(str_dst[0], 61);
  assert_int_equal(str_dst[1], 64);

  // test 4
  // decimal 224 + 42 % 256 -> 10, decimal 10 is special char ('\n') -> +64
  str_src_len = 1;
  str_src[0] = 224;
  num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 2);
  assert_int_equal(str_dst[0], 61);
  assert_int_equal(str_dst[1], 74);

  // test 5
  // decimal 19 + 42 % 256 -> 61, decimal 61 is special char (=) -> +64
  str_src_len = 1;
  str_src[0] = 19;
  num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 2);
  assert_int_equal(str_dst[0], 61);
  assert_int_equal(str_dst[1], 125);

  // test 6
  str_src_len = 4;
  str_src[0] = 'A';  // decimal 65
  str_src[1] = 'B';
  str_src[2] = 'C';
  str_src[3] = 'D';
  num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 4);
  assert_int_equal(str_dst[0], 'k');  // decimal 107
  assert_int_equal(str_dst[1], 'l');
  assert_int_equal(str_dst[2], 'm');
  assert_int_equal(str_dst[3], 'n');

  // test 7
  str_src_len = 6;
  str_src[0] = 214;
  str_src[1] = 65;
  str_src[2] = 224;
  str_src[3] = 66;
  str_src[4] = 19;
  str_src[5] = 67;
  num_chars = botje_yenc__encode((unsigned char *)str_dst, (unsigned char *)str_src, str_src_len);
  assert_int_equal(num_chars, 9);
  assert_int_equal(str_dst[0], '=');
  assert_int_equal(str_dst[1], '@');
  assert_int_equal(str_dst[2], 'k');
  assert_int_equal(str_dst[3], '=');
  assert_int_equal(str_dst[4], 'J');
  assert_int_equal(str_dst[5], 'l');
  assert_int_equal(str_dst[6], '=');
  assert_int_equal(str_dst[7], '}');
  assert_int_equal(str_dst[8], 'm');

  // clean up
  free(str_dst);
  free(str_src);
}
