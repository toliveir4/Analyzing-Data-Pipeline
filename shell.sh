#  Utilização
#  Executar este script
#
#  Funcionalidade
#  Compila o script em cpp
#  Compara todos os casos de teste nas pastas testCases e inputs2
#  Cria o ficheiro *casoteste*.out_temp com resultado de correr cada caso de teste
#
#  Flags
#  -c apagar os ficheiros *casotest*.out_temp após correr cada caso de teste

g++ -std=c++17 -Wall -Wextra -O2 -o e.out pipeline.cpp -lm

TIMEFILE="timefile"

out=`ls ./inputs2/*.txt && ls ./testCases/*.txt`
for ef in $out
do
   echo "$ef"
   A=${ef//\.txt/.out_temp}
   B=${ef//\.txt/out}
   /usr/bin/time -v -o ${TIMEFILE} ./e.out < $ef > $A

   diff -c $A $B
   if test ! -z $1 && test $1 = "-c"; then
      rm -Rf $A ${TIMEFILE}
   fi
done