#include "test_botje_yenc__encode.h"

void test_botje_yenc__encode_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t num_chars;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);

    // test 1
    // first step:      tmp_char = input_char + 42
    // second step:     if tmp_char is one of these special chars: 0 (NUL), 10 (LF), 13 (CR) or 61 ('=')
    //                  then an escape char with value 61 ('=') should be added to the output buffer
    //                  and tmp_char += 64
    // third step:      tmp_char should be added to the output buffer
    for(int64_t i = 0; i < 256; i++) {

        str_src_len = 1;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { i };
        num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);

        unsigned char test_char = (i + 42) % 256;
        if(test_char == 0 || test_char == 10 || test_char == 13 || test_char == 61) {
            assert_int_equal(num_chars, 2);
            unsigned char str_dst_cmp[] = { 61, (test_char + 64) % 256 };
            assert_memory_equal(str_dst, str_dst_cmp, num_chars);
        } else {
            assert_int_equal(num_chars, 1);
            unsigned char str_dst_cmp[] = { test_char };
            assert_memory_equal(str_dst, str_dst_cmp, num_chars);
        }
    }

    // test 2
    // no specials chars
    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 'A', 'B', 'C', 'D' };  // 'A' is decimal 65
        num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        unsigned char str_dst_cmp[] = { 'k', 'l', 'm', 'n' };  // 'k' is decimal 107
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    // test 3
    // only special chars
    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 19, 214, 224, 227 };  // after +42 special char '=', NUL, LF, CR
        num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        unsigned char str_dst_cmp[] = { '=', '}', '=', '@', '=', 'J', '=', 'M' };
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    // test 4
    // mix of normal and special chars, test 2 + test 3 combined
    {
        str_src_len = 8;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 'A', 'B', 'C', 'D', 19, 214, 224, 227 };
        num_chars = botje_yenc__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 12);
        unsigned char str_dst_cmp[] = { 'k', 'l', 'm', 'n', '=', '}', '=', '@', '=', 'J', '=', 'M' };
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    // clean up
    free(str_dst);
}
