set -e

GEN_NAME=gen.cpp
SOL_NAME=../submissions/accepted/7wonders_js.cpp

g++ -std=gnu++11 -Wconversion -fsanitize=address -g3 $GEN_NAME -o gen
g++ -std=gnu++11 -Wconversion -fsanitize=address -g3 $SOL_NAME -o sol

CURCASE=-1

# Arguments: testcasename
testcase () {
  CURCASE=$((CURCASE + 1))
  NAME=`printf "%02d" $CURCASE`$1
  echo "Case $NAME"
  ./gen ${*:2} > secret/$NAME.in
  ./sol < secret/$NAME.in > secret/$NAME.ans
}

testcase random-small-1 random 3211 0 10
testcase random-small-2 random 3212 1 10
testcase random-small-3 random 3213 2 10
testcase random-small-4 random 3214 3 10
testcase random-small-5 random 3215 4 10
testcase random-small-6 random 3216 5 10
testcase random-small-7 random 3217 6 10
testcase random-small-8 random 3218 7 10
testcase random-small-9 random 3218 10 15
testcase random-small-10 random 3218 30 20
testcase random-small-11 random 3218 50 30

testcase random-medium-1 random 3219 0 1000000
testcase random-medium-2 random 32110 100 1000000
testcase random-medium-3 random 32111 10000 1000000
testcase random-medium-4 random 32112 1000000 1000000
testcase random-medium-5 random 32113 100000000 1000000

testcase random-large-1 random 32114 0 100000000
testcase random-large-2 random 32115 100 100000000
testcase random-large-3 random 32116 10000 100000000
testcase random-large-4 random 32117 1000000 100000000
testcase random-large-5 random 32118 100000000 100000000
