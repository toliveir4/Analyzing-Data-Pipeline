CPPFILE = pipeline.cpp
EXE = e.out
TESTCASE = testCases/alex_input2.txt
TESTOUTPUT = testCases/alex_input2out
OUTPUT = output.txt
DIFF = testCases/diff.txt
TIMEFILE = testCases/timefile

exe: ${CPPFILE} ${TESTCASE} ${TESTOUTPUT}
	g++ -std=c++17 -Wall -Wextra -O2 -o ${EXE} ${CPPFILE} -lm
	/usr/bin/time -v -o ${TIMEFILE} ./${EXE} < ${TESTCASE}
	# diff -c ${OUTPUT} ${TESTOUTPUT} > ${DIFF}

clear: ${TIMEFILE} ${OUTPUT} ${DIFF}
	rm -rf ${DIFF} ${OUTPUT} ${TIMEFILE}