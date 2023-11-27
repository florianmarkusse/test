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
             (flo_testFailure(), flo_appendTestDemarcation(), 0);              \
         FLO_MACRO_VAR(i) < 1;                                                 \
         FLO_MACRO_VAR(i) =                                                    \
             (flo_appendTestDemarcation(), FLO_FLUSH_TO(FLO_STDERR), 1))

#define FLO_TEST_FUNCTION(testName, ...)                                       \
    void testName() {                                                          \
        flo_printTestStart(FLO_STRING((#testName)));                           \
        do {                                                                   \
            __VA_ARGS__                                                        \
        } while (0);                                                           \
    }

#define FLO_TEST(testString)                                                   \
    for (ptrdiff_t FLO_MACRO_VAR(i) = (flo_printTestStart(testString), 0);     \
         FLO_MACRO_VAR(i) < 1; FLO_MACRO_VAR(i) = 1)

#define FLO_TEST_TOPIC(testTopicString)                                        \
    for (ptrdiff_t FLO_MACRO_VAR(i) =                                          \
             (flo_testTopicStart(testTopicString), 0);                         \
         FLO_MACRO_VAR(i) < 1; FLO_MACRO_VAR(i) = (flo_testTopicFinish(), 1))

void flo_testSuiteStart();
int flo_testSuiteFinish();

void flo_testTopicStart(flo_String testTopic);
void flo_testTopicFinish();

void flo_printTestStart(flo_String testName);

void flo_testSuccess();

void flo_testFailure();
void flo_appendTestDemarcation();

#ifdef __cplusplus
}
#endif

#endif
