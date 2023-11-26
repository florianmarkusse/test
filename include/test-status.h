#ifndef TEST_STATUS_H
#define TEST_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "text/string.h"

typedef enum {
    TEST_SUCCESS,
    TEST_ERROR_INITIALIZATION,
    TEST_FAILURE,
    TEST_NUM_STATUS
} TestStatus;

flo_String testStatusToString(TestStatus status);

#ifdef __cplusplus
}
#endif

#endif
