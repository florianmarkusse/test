#include "test.h"
#include "log.h"
#include "unit-test.h"

typedef struct {
    uint64_t successes;
    uint64_t failures;
    flo_String topic;
} flo_TestTopic;

#define MAX_TEST_TOPICS 1 << 6

static flo_UnitTest currentTest = {0};

static flo_TestTopic testTopics[MAX_TEST_TOPICS];
static ptrdiff_t nextTestTopic = 0;

void addTopic(flo_String topic) {
    FLO_ASSERT(nextTestTopic < MAX_TEST_TOPICS);
    testTopics[nextTestTopic++] =
        (flo_TestTopic){.failures = 0, .successes = 0, .topic = topic};
}

void appendSpaces() {
    for (ptrdiff_t i = 0; i < nextTestTopic - 1; i++) {
        FLO_INFO("  ");
    }
}

void flo_printTestScore(uint64_t successes, uint64_t failures) {
    FLO_FLUSH_AFTER(FLO_STDOUT) {
        appendSpaces();

        FLO_INFO((FLO_STRING("[ ")));
        FLO_INFO(successes);
        FLO_INFO((FLO_STRING(" / ")));
        FLO_INFO(failures + successes);
        FLO_INFO((FLO_STRING(" ]\n")));
    }
}

void flo_testSuiteStart() {
    FLO_INFO((FLO_STRING("Starting test suite...\n\n")), FLO_FLUSH);

    addTopic(FLO_STRING("Root topic"));
}

int flo_testSuiteFinish() {
    uint64_t globalSuccesses = testTopics[0].successes;
    uint64_t globalFailures = testTopics[0].failures;

    flo_printTestScore(globalSuccesses, globalFailures);
    if (globalFailures > 0) {
        FLO_FLUSH_AFTER(FLO_STDERR) {
            FLO_ERROR((FLO_STRING("\nTest suite ")));
            flo_appendColor(FLO_COLOR_RED, FLO_STDERR);
            FLO_ERROR((FLO_STRING("failed")));
            flo_appendColorReset(FLO_STDERR);
            FLO_ERROR((FLO_STRING(".\n")));
        }
    } else {
        FLO_FLUSH_AFTER(FLO_STDOUT) {
            FLO_INFO((FLO_STRING("\nTest suite ")));
            flo_appendColor(FLO_COLOR_GREEN, FLO_STDOUT);
            FLO_INFO((FLO_STRING("successful")));
            flo_appendColorReset(FLO_STDOUT);
            FLO_INFO((FLO_STRING(".\n")));
        }
    }

    return globalFailures > 0;
}

void flo_testTopicStart(flo_String testTopic) {
    addTopic(testTopic);

    FLO_FLUSH_AFTER(FLO_STDOUT) {
        appendSpaces();
        FLO_INFO((FLO_STRING("Testing ")));
        FLO_INFO(testTopic);
        FLO_INFO((FLO_STRING("...\n")));
    }
}

void flo_testTopicFinish() {
    flo_printTestScore(testTopics[nextTestTopic - 1].successes,
                       testTopics[nextTestTopic - 1].failures);

    nextTestTopic--;
}

void flo_setCurrentUnitTest(flo_String testName, void (*testFunction)()) {
    if (testFunction != NULL) {
        currentTest = (flo_UnitTest){.key = testName, .value = testFunction};
    }
}

void flo_testStart(flo_String testName, void (*testFunction)()) {
    flo_setCurrentUnitTest(testName, testFunction);

    FLO_FLUSH_AFTER(FLO_STDOUT) {
        appendSpaces();
        FLO_INFO("- ");
        flo_appendToBufferMinSize(testName, 50, flo_getWriteBuffer(FLO_STDOUT),
                                  0);
    }
}

void flo_testSuccess() {
    for (ptrdiff_t i = 0; i < nextTestTopic; i++) {
        testTopics[i].successes++;
    }

    FLO_FLUSH_AFTER(FLO_STDOUT) {
        flo_appendColor(FLO_COLOR_GREEN, FLO_STDOUT);
        flo_appendToBufferMinSize(FLO_STRING("Success"), 20,
                                  flo_getWriteBuffer(FLO_STDOUT), 0);
        flo_appendColorReset(FLO_STDOUT);
        FLO_INFO((FLO_STRING("\n")));
    }
}

void flo_testFailure() {
    for (ptrdiff_t i = 0; i < nextTestTopic; i++) {
        testTopics[i].failures++;
    }

    if (currentTest.key.len != 0) {
        flo_msi_insertFailedUnitTest(currentTest);
        currentTest.key.len = 0;
    }

    FLO_FLUSH_AFTER(FLO_STDERR) {
        flo_appendColor(FLO_COLOR_RED, FLO_STDERR);
        flo_appendToBufferMinSize(FLO_STRING("Failure"), 20,
                                  flo_getWriteBuffer(FLO_STDERR), 0);
        flo_appendColorReset(FLO_STDERR);
        FLO_ERROR((FLO_STRING("\n")));
    }
}

void flo_appendTestFailureStart() {
    FLO_ERROR((FLO_STRING("----------------------------------------------------"
                          "----------------------------\n")));
    FLO_ERROR((FLO_STRING("|                                    REASON         "
                          "                           |\n")));
}

void flo_appendTestFailureFinish() {
    FLO_ERROR((FLO_STRING("|                                                   "
                          "                           |\n")));
    FLO_ERROR((FLO_STRING("----------------------------------------------------"
                          "----------------------------\n")));
}
