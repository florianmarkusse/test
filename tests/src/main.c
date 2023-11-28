#include <sys/mman.h>

#include "hash/hashes.h"
#include "memory/arena.h"
#include "test.h"
#include "unit-test.h"

#define CAP 1 << 21

static flo_String testNames[] = {
    FLO_STRING("aaaaaaaaa"),   FLO_STRING("bbbbbbbbb"),
    FLO_STRING("cccccccccc"),  FLO_STRING("dddddddddd"),
    FLO_STRING("eeeeeeeeee"),  FLO_STRING("fffffffff"),
    FLO_STRING("ggggggggggg"), FLO_STRING("hhhhhhhhh"),
    FLO_STRING("iiiiiiiiii"),  FLO_STRING("ffffffffffff"),
};

static ptrdiff_t numTestNames = FLO_COUNTOF(testNames);

FLO_TEST_FUNCTION(test4, {
    FLO_TEST_FAILURE {
        // kdfjfkdj
        FLO_ERROR("chaos and destruction\n");
        FLO_ERROR("chaos and destruction\n");
        FLO_ERROR("chaos and destruction\n");
}
});

void test1() {
    flo_unitTestStart(FLO_STRING("Test 1"), test1);

    flo_testSuccess();
}

void test2() {
    flo_unitTestStart(FLO_STRING("Test 2"), test2);

    flo_testSuccess();
}

FLO_COMPOUND_TEST_FUNCTION(multipleTests, {
    for (ptrdiff_t i = 0; i < numTestNames; i++) {
        FLO_PARAMETERIZED_TEST(testNames[i]) {
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
});

void test3() {
    flo_unitTestStart(FLO_STRING("Test 3"), test3);

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

    FLO_TEST_TOPIC(FLO_STRING("My first topic")) { test1(); }

    FLO_TEST_TOPIC(FLO_STRING("My second topic")) {
        test2();
        FLO_TEST_TOPIC(FLO_STRING("inside topic")) { multipleTests(); }
        test3();
        test4();
    }

    return flo_testSuiteFinish();
}
