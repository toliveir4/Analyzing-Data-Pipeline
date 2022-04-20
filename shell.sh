#  Utilização
#  Adicionar gocompiler (compilado) ao PATH
#  (uma boa opção é adicionar a directoria da meta1 ao PATH)
#  Após compilar executar este script
#
#  Funcionalidade
#  Compara todos os casos de teste na pasta meta1
#  Cria o ficheiro *casoteste*.out_temp com resultado de correr cada caso de teste
#
#  Flags
#  -c apagar os ficheiros *casotest*.out_temp após correr cada caso de teste

echo make

TIMEFILE="testCases/timefile"

out=`ls ./testCases/*.txt`
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