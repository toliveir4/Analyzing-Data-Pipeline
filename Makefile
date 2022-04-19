CPPFILE = pipeline.cpp
EXE = e.out
TESTCASE = testCases/4.txt
TESTOUTPUT = testCases/4out.txt
OUTPUT = output.txt
DIFF = testCases/diff.txt
TIMEFILE = testCases/timefile

exe: ${CPPFILE} ${TESTCASE} ${TESTOUTPUT}
	g++ -std=c++17 -Wall -Wextra -O2 -o ${EXE} ${CPPFILE} -lm
	/usr/bin/time -v -o ${TIMEFILE} ./${EXE} < ${TESTCASE} > ${OUTPUT}
	# diff -c ${OUTPUT} ${TESTOUTPUT} > ${DIFF}

clear: ${TIMEFILE} ${OUTPUT} ${DIFF}
	rm -rf ${DIFF} ${OUTPUT} ${TIMEFILE}