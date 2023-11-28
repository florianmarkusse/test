#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "hash/hashes.h"
#include "log.h"
#include "unit-test.h"

static flo_msi_UnitTest *failedUnitTests = NULL;
static bool printedWarning = false;

void flo_msi_setUnitTestsVariable(flo_msi_UnitTest *failedTests) {
    failedUnitTests = failedTests;
}

bool internalInsert(flo_UnitTest failedTest, size_t hash) {
    for (int32_t i = (int32_t)hash;;) {
        i = flo_indexLookup(hash, failedUnitTests->exp, i);
        if (failedUnitTests->buf[i].key.len == 0) {
            failedUnitTests->len++;
            failedUnitTests->buf[i] = failedTest;
            return true;
        } else if (flo_stringEquals(failedUnitTests->buf[i].key,
                                    failedTest.key)) {
            return false;
        }
    }
}

bool flo_msi_insertUnitTest(flo_UnitTest failedUnitTest) {
    if (failedUnitTests == NULL) {
        if (!printedWarning) {
            FLO_FLUSH_AFTER(FLO_STDOUT) {
                flo_appendColor(FLO_COLOR_MAGENTA, FLO_STDOUT);
                FLO_INFO(
                    "failedTests variable is not set, please set this variable "
                    "if you wish to record failures.\n");
                flo_appendColorReset(FLO_STDOUT);
            }
            printedWarning = true;
        }
        return true;
    }

    if ((uint32_t)failedUnitTests->len >=
        ((uint32_t)1 << failedUnitTests->exp) / 2) {
        FLO_ASSERT(false);
        FLO_ERROR("Too many elements in MSI set, should rehash or init "
                  "with larger exponent\n",
                  FLO_FLUSH);
    }
    return internalInsert(failedUnitTest,
                          flo_hashStringDjb2(failedUnitTest.key));
}
