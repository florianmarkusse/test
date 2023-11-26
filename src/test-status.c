#include "test-status.h"

static flo_String testStatusStrings[TEST_NUM_STATUS] = {
    FLO_STRING("Success"), FLO_STRING("Initialization Error"),
    FLO_STRING("Failure")};

flo_String testStatusToString(TestStatus status) {
    if (status >= 0 && status < TEST_NUM_STATUS) {
        return testStatusStrings[status];
    }
    return FLO_STRING("Unknown test status code!");
}
