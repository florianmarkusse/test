#ifndef EXPECTATIONS_H
#define EXPECTATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "text/string.h"

void flo_appendExpectCodeWithString(ptrdiff_t expected,
                                    flo_String expectedString, ptrdiff_t actual,
                                    flo_String actualString);
void flo_appendExpectString(flo_String expectedString, flo_String actualString);
void flo_appendExpectBool(bool expectedBool, bool actualBool);
void flo_appendExpectPtrDiff(ptrdiff_t expectedNumber, ptrdiff_t actualNumber);
void flo_appendExpectUint(uint64_t expectedNumber, uint64_t actualNumber);

#ifdef __cplusplus
}
#endif

#endif
