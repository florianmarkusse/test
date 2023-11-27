#ifndef TEST_H
#define TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "log.h"
#include "macros.h"
#include <stdbool.h>
#include <stddef.h>
#include <text/string.h>

#define FLO_TEST_FAILURE                                                       \
    for (ptrdiff_t FLO_MACRO_VAR(i) =                                          \
             (flo_testFailure(), flo_appendTestFailureStart(), 0);             \
         FLO_MACRO_VAR(i) < 1;                                                 \
         FLO_MACRO_VAR(i) =                                                    \
             (flo_appendTestFailureFinish(), FLO_FLUSH_TO(FLO_STDERR), 1))

#define FLO_TEST_FUNCTION(testName, ...)                                       \
    void testName() {                                                          \
        flo_testStart(FLO_STRING((#testName)), testName);                      \
        do {                                                                   \
            __VA_ARGS__                                                        \
        } while (0);                                                           \
    }

#define FLO_COMPOUND_TEST_FUNCTION(testName, ...)                              \
    void testName() {                                                          \
        flo_setCurrentUnitTest(FLO_STRING((#testName)), testName);             \
        do {                                                                   \
            __VA_ARGS__                                                        \
        } while (0);                                                           \
    }

// Run these only in compound tests to ensure that failures will be picked up by
// the failed tests recorder for replay. Just counting works always.
#define FLO_REPREATED_TEST(testString)                                         \
    for (ptrdiff_t FLO_MACRO_VAR(i) = (flo_testStart(testString, NULL), 0);    \
         FLO_MACRO_VAR(i) < 1; FLO_MACRO_VAR(i) = 1)

#define FLO_TEST_TOPIC(testTopicString)                                        \
    for (ptrdiff_t FLO_MACRO_VAR(i) =                                          \
             (flo_testTopicStart(testTopicString), 0);                         \
         FLO_MACRO_VAR(i) < 1; FLO_MACRO_VAR(i) = (flo_testTopicFinish(), 1))

void flo_testSuiteStart();
int flo_testSuiteFinish();

void flo_testTopicStart(flo_String testTopic);
void flo_testTopicFinish();

void flo_setCurrentUnitTest(flo_String testName, void (*testFunction)());
void flo_testStart(flo_String testName, void (*testFunction)());

void flo_testSuccess();

void flo_testFailure();
void flo_appendTestFailureStart();
void flo_appendTestFailureFinish();

#ifdef __cplusplus
}
#endif

#endif
