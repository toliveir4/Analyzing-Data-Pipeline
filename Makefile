CPPFILE = pipeline.cpp
EXE = e.out
DIFF = testCases/diff.txt
TIMEFILE = testCases/timefile

main: ${CPPFILE} ${TESTCASE} ${TESTOUTPUT}
	g++ -std=c++17 -Wall -Wextra -O2 -o ${EXE} ${CPPFILE} -lm
	# diff -c ${OUTPUT} ${TESTOUTPUT} > ${DIFF}
	