#include "test_botje_yenc__decode.h"

void test_botje_yenc__decode_test(void **state) {

  unsigned char *str_dst = calloc(1, 16);
  unsigned char *str_src = calloc(1, 16);
  int64_t num_chars;
  int64_t str_src_len;

  // test 1
  // decimal 107 (char 'k') is NOT a special char so only -42 -> decimal 65 (char 'A')
  str_src_len = 1;
  str_src[0] = 'k';
  num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 1);
  assert_int_equal(str_dst[0], 'A');

  // test 2
  // decimal 108 (char 'l') is NOT a special char so only -42 -> decimal 66 (char 'B')
  str_src_len = 1;
  str_src[0] = 'l';
  num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 1);
  assert_int_equal(str_dst[0], 'B');

  // test 3
  str_src_len = 2;
  str_src[0] = 61;
  str_src[1] = 64;
  num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 1);
  assert_int_equal(str_dst[0], 214);

  // test 4
  str_src_len = 2;
  str_src[0] = 61;
  str_src[1] = 74;
  num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 1);
  assert_int_equal(str_dst[0], 224);

  // test 5
  str_src_len = 2;
  str_src[0] = 61;
  str_src[1] = 125;
  num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 1);
  assert_int_equal(str_dst[0], 19);

  // test 6
  str_src_len = 4;
  str_src[0] = 'k';  // decimal 107
  str_src[1] = 'l';
  str_src[2] = 'm';
  str_src[3] = 'n';
  num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 4);
  assert_int_equal(str_dst[0], 'A');  // decimal 65
  assert_int_equal(str_dst[1], 'B');
  assert_int_equal(str_dst[2], 'C');
  assert_int_equal(str_dst[3], 'D');

  // test 7
  str_src_len = 9;
  str_src[0] = '=';  // decimal 61
  str_src[1] = '@';
  str_src[2] = 'k';
  str_src[3] = '=';
  str_src[4] = 'J';
  str_src[5] = 'l';
  str_src[6] = '=';
  str_src[7] = '}';
  str_src[8] = 'm';
  num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
  assert_int_equal(num_chars, 6);
  assert_int_equal(str_dst[0], 214);
  assert_int_equal(str_dst[1], 65);
  assert_int_equal(str_dst[2], 224);
  assert_int_equal(str_dst[3], 66);
  assert_int_equal(str_dst[4], 19);
  assert_int_equal(str_dst[5], 67);

  // clean up
  free(str_dst);
  free(str_src);
}
