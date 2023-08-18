#include "test_botje_yenc__decode.h"

void test_botje_yenc__decode_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t num_chars;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);

    // test 1
    for(int64_t i = 0; i < 256; i++) {

        str_src_len = 1;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { i };
        num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);

        if(i == '=') {  // skip the escape char '='
            assert_int_equal(num_chars, 0);
        } else if(i == 0 || i == 10 || i == 13) {  // these chars should not be in the string because they are escaped
            assert_int_equal(num_chars, -1);
        } else {
            assert_int_equal(num_chars, 1);
            unsigned char str_dst_cmp[] = { i - 42 };
            assert_memory_equal(str_dst, str_dst_cmp, num_chars);
        }
    }

    // test 2
    // no specials chars
    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 'k', 'l', 'm', 'n' };
        num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        unsigned char str_dst_cmp[] = { 'A', 'B', 'C', 'D' };  // 'k' (107) - 42 -> 'A' (65)
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    // test 3
    // only special chars
    {
        str_src_len = 8;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { '=', '}', '=', '@', '=', 'J', '=', 'M' };
        num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        unsigned char str_dst_cmp[] = { 19, 214, 224, 227 };  // '}' (125) - 64 - 42 -> 19
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    // test 4
    // mix of normal and special chars, test 2 + test 3 combined
    {
        str_src_len = 12;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 'k', 'l', 'm', 'n', '=', '}', '=', '@', '=', 'J', '=', 'M' };
        num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        unsigned char str_dst_cmp[] = { 'A', 'B', 'C', 'D', 19, 214, 224, 227 };
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    // test 5
    // wrong input
    for(int64_t i = 0; i < 256; i++) {

        str_src_len = 2;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { '=', i };
        num_chars = botje_yenc__decode(str_dst, str_src, str_src_len);

        if(i == 64 || i == 74 || i == 77 || i == 125) {  // these special chars ('@', 'J', 'M', '}') should only be allowed after escape char
            assert_int_equal(num_chars, 1);
            unsigned char str_dst_cmp[] = { i - 64 - 42 };
            assert_memory_equal(str_dst, str_dst_cmp, num_chars);
        } else {
            assert_int_equal(num_chars, -1);
        }
    }

    // clean up
    free(str_dst);
}
