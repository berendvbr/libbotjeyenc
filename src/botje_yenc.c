#include "botje_yenc.h"

int64_t botje_yenc__decode(unsigned char *str_dst, unsigned char *str_src, int64_t str_src_len) {

    bool special_char = false;
    int64_t str_dst_len = 0;
    unsigned char *str_dst_ptr = str_dst;

    for(int64_t l = 0; l < str_src_len; l++) {
        
        unsigned char tmp_char = str_src[l];
        
        // these chars should not be in the string because they are escaped
        if(tmp_char == 0 || tmp_char == 10 || tmp_char == 13) {
            return -1;
        }

        if(!special_char && tmp_char == '=') {  // '=' is decimal 61
            special_char = true;
            continue;
        }

        if(special_char) {
            
            // these special chars ('@', 'J', 'M', '}') should only be allowed after escape char
            if(tmp_char != 64 && tmp_char != 74 && tmp_char != 77 && tmp_char != 125) return -1;

            tmp_char = (tmp_char - 64) % 256;
            special_char = false;
        }

        *(str_dst_ptr++) = (tmp_char - 42) % 256;
        str_dst_len++;
    }

    return str_dst_len;
}


int64_t botje_yenc__encode(unsigned char *str_dst, unsigned char *str_src, int64_t str_src_len) {

    int64_t str_dst_len = 0;
    unsigned char *str_dst_ptr = str_dst;

    for(int64_t l = 0; l < str_src_len; l++) {
      
        unsigned char tmp_char = (str_src[l] + 42) % 256;
        if(tmp_char == 0 || tmp_char == 10 || tmp_char == 13 || tmp_char == 61) {  // NULL, LF, CR, '='
            *(str_dst_ptr++) = '=';
            str_dst_len++;
            tmp_char = (tmp_char + 64) % 256;
        }
        *(str_dst_ptr++) = tmp_char;
        str_dst_len++;
    }

    return str_dst_len;
}
