#include "test.h"

FLO_TEST_FUNCTION(test4, {
    FLO_TEST_FAILURE {
        // kdfjfkdj
        FLO_ERROR("chaos and destruction\n");
        FLO_ERROR("chaos and destruction\n");
        FLO_ERROR("chaos and destruction\n");
}
});

void test1() {
    flo_printTestStart(FLO_STRING("Test 1"));

    flo_testSuccess();
}

void test2() {
    flo_printTestStart(FLO_STRING("Test 2"));

    FLO_TEST_FAILURE {
        // Inside this scoped block you can do your additional logging.
        FLO_ERROR("chaos and destruction\n");
    }
}

void test3() {
    flo_printTestStart(FLO_STRING("Test 3"));

    flo_testSuccess();
}

int main() {
    flo_testSuiteStart();

    FLO_TEST_TOPIC(FLO_STRING("First topic")) {
        test1();
        test1();
        test1();
        FLO_TEST_TOPIC(FLO_STRING("Inside first topic")) {
            test2();
            test2();
            test2();
        }

        test3();
        test1();
    }

    for (ptrdiff_t i = 0; i < 10; i++) {
        FLO_TEST(FLO_STRING("aaaa")) {
            if (i % 2 == 0) {
                flo_testSuccess();
            } else {
                FLO_TEST_FAILURE {
                    FLO_ERROR(_i_MACRO_VAR__LINE__);
                    // Inside this scoped block you can do your additional
                    // logging.
                    FLO_ERROR("big chaos\n");
                }
            }
        }
    }

    test1();
    test1();
    test4();

    return flo_testSuiteFinish();
}
