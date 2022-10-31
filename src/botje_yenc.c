#include "botje_yenc.h"

int64_t botje_yenc__decode(unsigned char *str_dst, unsigned char *str_src, int64_t num_chars_in_src) {

  bool special_char = false;

  unsigned char *tmp_str_dst = str_dst;
  int64_t num_chars_in_dst = 0;

  for(int64_t l = 0; l < num_chars_in_src; l++) {
    if(!special_char && str_src[l] == '=') {
      special_char = true;
      continue;
    }

    unsigned char tmp_char = str_src[l];
    if(special_char) {
      tmp_char = (tmp_char - 64) % 256;
      special_char = false;
    }

    *(tmp_str_dst++) = (tmp_char - 42) % 256;
    num_chars_in_dst++;
  }

  return num_chars_in_dst;
}


int64_t botje_yenc__encode(unsigned char *str_dst, unsigned char *str_src, int64_t num_chars_in_src) {

  unsigned char *tmp_str_dst = str_dst;
  int64_t num_chars_in_dst = 0;

  for(int64_t l = 0; l < num_chars_in_src; l++) {
    unsigned char tmp_char = (str_src[l] + 42) % 256;
    if(tmp_char == 0 || tmp_char == 10 || tmp_char == 13 || tmp_char == 61) {  // NULL, LF, CR, =
      *(tmp_str_dst++) = '=';
      num_chars_in_dst++;
      tmp_char = (tmp_char + 64) % 256;
    }
    *(tmp_str_dst++) = tmp_char;
    num_chars_in_dst++;
  }

  return num_chars_in_dst;
}
