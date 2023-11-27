#!/bin/bash
set -e

source ./build.sh

EXECUTABLE="test"
if [ "$RUN_TESTS" = true ]; then
	./run-executable.sh build "$EXECUTABLE"-tests-"$BUILD_MODE"
fi
