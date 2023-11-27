#include <sys/mman.h>

#include "hash/hashes.h"
#include "memory/arena.h"
#include "test.h"
#include "unit-test.h"

#define CAP 1 << 21

FLO_TEST_FUNCTION(test4, {
    FLO_TEST_FAILURE {
        // kdfjfkdj
        FLO_ERROR("chaos and destruction\n");
        FLO_ERROR("chaos and destruction\n");
        FLO_ERROR("chaos and destruction\n");
}
});

void test1() {
    flo_testStart(FLO_STRING("Test 1"), test1);

    flo_testSuccess();
}

void test2() {
    flo_testStart(FLO_STRING("Test 2"), test2);

    FLO_TEST_FAILURE {
        // Inside this scoped block you can do your additional logging.
        FLO_ERROR("chaos and destruction\n");
    }
}

FLO_COMPOUND_TEST_FUNCTION(test5, {
    for (ptrdiff_t i = 0; i < 10; i++) {
        FLO_REPREATED_TEST(FLO_STRING("aaaa")) {
            if (i % 2 == 0) {
                flo_testSuccess();
            } else {
                FLO_TEST_FAILURE {
                    // Inside this scoped block you can do your
                    // additional logging.
                    FLO_ERROR("big chaos\n");
                }
            }
        }
    }
})

void test3() {
    flo_testStart(FLO_STRING("Test 3"), test3);

    flo_testSuccess();
}

int main() {
    char *begin = mmap(NULL, CAP, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (begin == MAP_FAILED) {
        FLO_ERROR("Failed to allocate memory!\n", FLO_FLUSH);
        return -1;
    }

    flo_Arena arena =
        (flo_Arena){.beg = begin, .cap = CAP, .end = begin + (ptrdiff_t)(CAP)};

    void *jmp_buf[5];
    if (__builtin_setjmp(jmp_buf)) {
        if (munmap(arena.beg, arena.cap) == -1) {
            FLO_FLUSH_AFTER(FLO_STDERR) {
                FLO_ERROR((FLO_STRING("Failed to unmap memory from arena!\n"
                                      "Arena Details:\n"
                                      "  beg: ")));
                FLO_ERROR(arena.beg);
                FLO_ERROR((FLO_STRING("\n end: ")));
                FLO_ERROR(arena.end);
                FLO_ERROR((FLO_STRING("\n cap: ")));
                FLO_ERROR(arena.cap);
                FLO_ERROR((FLO_STRING("\nZeroing Arena regardless.\n")));
            }
        }
        arena.beg = NULL;
        arena.end = NULL;
        arena.cap = 0;
        arena.jmp_buf = NULL;
        FLO_ERROR((FLO_STRING("OOM/overflow in arena!\n")), FLO_FLUSH);
        return -1;
    }
    arena.jmp_buf = jmp_buf;

    flo_msi_UnitTest failedTests =
        FLO_NEW_MSI_SET(flo_msi_UnitTest, 10, &arena);
    flo_msi_setUnitTestsVariable(&failedTests);

    flo_testSuiteStart();

    FLO_TEST_TOPIC(FLO_STRING("First topic")) {
        test2();
        FLO_TEST_TOPIC(FLO_STRING("Inside first topic")) {
            // run test 5.
            test1();
            test5();
            test1();
        }
    }
    test2();

    test3();

    flo_UnitTest element;
    FLO_FOR_EACH_MSI_UNIT_TEST(element, &failedTests) {
        // klfgsdl
        FLO_INFO(element.key, FLO_FLUSH | FLO_NEWLINE);
    }

    return flo_testSuiteFinish();
}
