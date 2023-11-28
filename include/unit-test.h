#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hash/msi/common.h"
#include "macros.h"
#include "text/string.h"

typedef struct {
    flo_String key;
    void (*value)();
    bool wasSuccess;
} flo_UnitTest;

typedef FLO_MSI_SET(flo_UnitTest) flo_msi_UnitTest;

void flo_msi_setUnitTestsVariable(flo_msi_UnitTest *failedTests);
bool flo_msi_insertUnitTest(flo_UnitTest failedUnitTest);

#define FLO_FOR_EACH_MSI_UNIT_TEST(element, msiSet)                            \
    for (ptrdiff_t FLO_MACRO_VAR(i) = 0;                                       \
         FLO_MACRO_VAR(i) < (1 << (msiSet)->exp); ++FLO_MACRO_VAR(i))          \
        if (((element) = (msiSet)->buf[FLO_MACRO_VAR(i)]).key.len != 0)

#define FLO_FOR_EACH_MSI_FAILED_UNIT_TEST(element, msiSet)                     \
    for (ptrdiff_t FLO_MACRO_VAR(i) = 0;                                       \
         FLO_MACRO_VAR(i) < (1 << (msiSet)->exp); ++FLO_MACRO_VAR(i))          \
        if (((element) = (msiSet)->buf[FLO_MACRO_VAR(i)]).key.len != 0 &&      \
            !(element).wasSuccess)

#define FLO_FOR_EACH_MSI_SUCCESSFUL_UNIT_TEST(element, msiSet)                 \
    for (ptrdiff_t FLO_MACRO_VAR(i) = 0;                                       \
         FLO_MACRO_VAR(i) < (1 << (msiSet)->exp); ++FLO_MACRO_VAR(i))          \
        if (((element) = (msiSet)->buf[FLO_MACRO_VAR(i)]).key.len != 0 &&      \
            (element).wasSuccess)

#ifdef __cplusplus
}
#endif

#endif
