#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cmocka.h>

#include "test_botje_yenc__decode.h"
#include "test_botje_yenc__encode.h"

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_botje_yenc__decode_test),
        cmocka_unit_test(test_botje_yenc__encode_test)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
