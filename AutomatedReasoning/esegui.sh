 #!/bin/bash

count=1

gcc genera_istanzaASP.c 

./a.out	

# Verifica se la directory esiste
    # Itera tra tutti i file che terminano con "instance.txt"
    for file in ASPinstance*.txt; do
        # Verifica se il file esiste
        if [ -f "$file" ]; then
            
              cat $file portTavern.lp > provaASP$count.lp 
  

              clingo provaASP$count.lp 0 --time-limit 300 > result$count.txt
              rm provaASP$count.lp
              mkdir inst$count
              mv $file result$count.txt inst$count
              count=$((count+1))
        else
            # Stampa un messaggio di avviso se il file non esiste
            echo "Nessun file trovato con il nome $file"
        fi
    done


countBis=1

for file in MZNinstance*.txt; do

    if [ -f "$file" ]; then 

       cat $file assign.mzn >provaMZN$countBis.mzn
       mv $file provaMZN$countBis.mzn inst$countBis
 
       countBis=$((countBis+1))

    
    else
            # Stampa un messaggio di avviso se il file non esiste
            echo "Nessun file trovato con il nome $file"
        fi
   done
