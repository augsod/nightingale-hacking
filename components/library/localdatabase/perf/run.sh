#!/bin/sh
#
# Note: this file is for personal testing only, and is not used 
# in the automated perf testing environment
#
LIBRARY_DIR=/builds/songbird/libraries/
RESULTS_FILE=/builds/songbird/dbperf_results.txt

LIBRARY_FILES="test_5000.db test_10000.db test_25000.db test_50000.db test_100000.db"
PERF_TESTS="guidarray guidarray_multisort guidarray_distinct guidarray_default_view guidarray_library_enumerate guidarray_search guidarray_search_distinct guidarray_filtering propertycache"

# Stupid mac compatibility
alias seq=gseq

for library_file in $LIBRARY_FILES; do
  for perf_test in $PERF_TESTS; do
    for i in `seq 1 3`; do
      echo $LIBRARY_DIR$library_file
      export SB_PERF_LIBRARY=$LIBRARY_DIR$library_file
      export SB_PERF_RESULTS=$RESULTS_FILE
      ./songbird -test localdatabaselibraryperf:$perf_test
    done;
  done;
done
