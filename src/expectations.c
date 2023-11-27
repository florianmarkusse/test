#include "expectations.h"
#include "log.h"

void flo_appendExpectCodeWithString(ptrdiff_t expected,
                                    flo_String expectedString, ptrdiff_t actual,
                                    flo_String actualString) {
    flo_appendToBufferMinSize(FLO_STRING("Expected"), 10,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    flo_appendPtrDiffToBufferMinSize(expected, 4,
                                     flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(" - ")));
    FLO_ERROR(expectedString, FLO_NEWLINE);

    flo_appendToBufferMinSize(FLO_STRING("Actual"), 10,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    flo_appendPtrDiffToBufferMinSize(actual, 4, flo_getWriteBuffer(FLO_STDERR),
                                     0);
    FLO_ERROR((FLO_STRING(" - ")));
    FLO_ERROR(actualString, FLO_NEWLINE);
}

void flo_appendExpectString(flo_String expectedString,
                            flo_String actualString) {
    flo_appendToBufferMinSize(FLO_STRING("Expected string"), 20,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    FLO_ERROR(expectedString, FLO_NEWLINE);

    flo_appendToBufferMinSize(FLO_STRING("Actual string"), 20,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    FLO_ERROR(actualString, FLO_NEWLINE);
}

void flo_appendExpectBool(bool expectedBool, bool actualBool) {
    flo_appendToBufferMinSize(FLO_STRING("Expected bool"), 20,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    FLO_ERROR(expectedBool, FLO_NEWLINE);

    flo_appendToBufferMinSize(FLO_STRING("Actual bool"), 20,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    FLO_ERROR(actualBool, FLO_NEWLINE);
}

void flo_appendExpectPtrDiff(ptrdiff_t expectedNumber, ptrdiff_t actualNumber) {
    flo_appendToBufferMinSize(FLO_STRING("Expected number"), 20,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    FLO_ERROR(expectedNumber, FLO_NEWLINE);

    flo_appendToBufferMinSize(FLO_STRING("Actual number"), 20,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    FLO_ERROR(actualNumber, FLO_NEWLINE);
}
void flo_appendExpectUint(uint64_t expectedNumber, uint64_t actualNumber) {
    flo_appendToBufferMinSize(FLO_STRING("Expected number"), 20,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    FLO_ERROR(expectedNumber, FLO_NEWLINE);

    flo_appendToBufferMinSize(FLO_STRING("Actual number"), 20,
                              flo_getWriteBuffer(FLO_STDERR), 0);
    FLO_ERROR((FLO_STRING(": ")));
    FLO_ERROR(actualNumber, FLO_NEWLINE);
}
