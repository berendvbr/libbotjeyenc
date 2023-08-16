#include "test_botje_yenc__decode.h"

void test_botje_yenc__decode_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t ret_val;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);
    unsigned char *str_src = malloc(buf_size);

    // test 1
    // decimal 107 (char 'k') is NOT a special char so only -42 -> decimal 65 (char 'A')
    str_src_len = 1;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    str_src[0] = 'k';
    ret_val = botje_yenc__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 1);
    assert_int_equal(str_dst[0], 'A');

    // test 2
    // decimal 108 (char 'l') is NOT a special char so only -42 -> decimal 66 (char 'B')
    str_src_len = 1;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    str_src[0] = 'l';
    ret_val = botje_yenc__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 1);
    assert_int_equal(str_dst[0], 'B');

    // test 3
    str_src_len = 2;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    str_src[0] = 61;
    str_src[1] = 64;
    ret_val = botje_yenc__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 1);
    assert_int_equal(str_dst[0], 214);

    // test 4
    str_src_len = 2;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    str_src[0] = 61;
    str_src[1] = 74;
    ret_val = botje_yenc__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 1);
    assert_int_equal(str_dst[0], 224);

    // test 5
    str_src_len = 2;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    str_src[0] = 61;
    str_src[1] = 125;
    ret_val = botje_yenc__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 1);
    assert_int_equal(str_dst[0], 19);

    // test 6
    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    str_src[0] = 'k';  // decimal 107
    str_src[1] = 'l';
    str_src[2] = 'm';
    str_src[3] = 'n';
    ret_val = botje_yenc__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 4);
    assert_int_equal(str_dst[0], 'A');  // decimal 65
    assert_int_equal(str_dst[1], 'B');
    assert_int_equal(str_dst[2], 'C');
    assert_int_equal(str_dst[3], 'D');

    // test 7
    str_src_len = 9;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    str_src[0] = '=';  // decimal 61
    str_src[1] = '@';
    str_src[2] = 'k';
    str_src[3] = '=';
    str_src[4] = 'J';
    str_src[5] = 'l';
    str_src[6] = '=';
    str_src[7] = '}';
    str_src[8] = 'm';
    ret_val = botje_yenc__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 6);
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
