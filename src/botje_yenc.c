#include "botje_yenc.h"

int64_t botje_yenc__decode(unsigned char *str_dst, unsigned char *str_src, int64_t str_src_len) {

    bool special_char = false;

    unsigned char *str_dst_ptr = str_dst;
    int64_t str_dst_len = 0;

    for(int64_t l = 0; l < str_src_len; l++) {
        
        unsigned char tmp_char = str_src[l];
        if(!special_char && tmp_char == '=') {
            special_char = true;
            continue;
        }

        if(special_char) {
            tmp_char = (tmp_char - 64) % 256;
            special_char = false;
        }

        *(str_dst_ptr++) = (tmp_char - 42) % 256;
        str_dst_len++;
    }

    return str_dst_len;
}


int64_t botje_yenc__encode(unsigned char *str_dst, unsigned char *str_src, int64_t str_src_len) {

    unsigned char *str_dst_ptr = str_dst;
    int64_t str_dst_len = 0;

    for(int64_t l = 0; l < str_src_len; l++) {
      
        unsigned char tmp_char = (str_src[l] + 42) % 256;
        if(tmp_char == 0 || tmp_char == 10 || tmp_char == 13 || tmp_char == 61) {  // NULL, LF, CR, =
            *(str_dst_ptr++) = '=';
            str_dst_len++;
            tmp_char = (tmp_char + 64) % 256;
        }
        *(str_dst_ptr++) = tmp_char;
        str_dst_len++;
    }

    return str_dst_len;
}
