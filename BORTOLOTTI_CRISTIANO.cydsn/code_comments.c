/* ====================================================================================================================================
                                                    Commenti codice
Per risolvere il problema è stato necessario introdurre due interrupt per gestire separatamente e più agilmente la ricezione dei
byte attraverso l'UART e la gestione del tempo per il timeout mediante il Timer. Per questo nel file MyISR.h vengono dichiarate due
ISR che vengono poi implementate nel file MyISR.c. Le due ISR sono funzioni molto semplici che prevedono il semplice incremento di un
flag una volta che viene chiamata l'interrupt. A entrambe le interrupt è stato assegnata la stessa priorità perchè la condizione in
cui venga mandato il byte esattamente allo scadere del timeout e che la successiva operazione sia il controllo dell'arrivo del byte
è veramente veramente poco probabile e quindi non è stato preso in considerazione; in aggiunta, è ragionevole pensare che per questo
tipo di applicazione se tale situazione dovesse accadere non sarebbe qualcosa di grave. In ogni caso, per evitare basterebbe 
aumentare la priorità del timer e aggiungere una variabile flag che indica che il il byte è arrivato esattamente allo scadere dei 5s.

Sono stati aggiunti i file MyFunction.h e MyFunction.c per raggruppare le varie funzionalità che vengono utilizzate all'interno del
main e snellirlo per migliorarne la comprensione. Volevo fare due chiarimenti:
1) è stata utilizzata in vari punti la funzione "UART_ClearRxBuffer()" in modo tale da pulire il buffer in caso di arrivo di molti
byte indesiderati (ex: premendo ripetutamente una lettera questa funzione evita che il sistema si impalli a causa dell'overflow del
buffer oppure a causa di errori nell'invio del pacchetto [invio di un byte in più o errori di battitura --> A0 FF 00 00 0C0], ecc...)
2) è stata realizzata una funzione errore particolare: quando si verifica un errore è stato implementato un feedback visivo introdu-
cendo un piccolo lampeggio rosso associato all'apparizione di una stringa di errore (diversa in base al tipo di errore, ovvero a
causa di un carattere sbagliato o per il timeout). Per introdurre il lampeggio, prima viene spento il LED (in modo tale che sia
visibile anche quando è impostato il rosso), si aspetta un tempo molto piccolo, si imposta il rosso, si stampa la stringa (decisa
in base all'input dato alla funzione), si rispegne il LED, si aspetta e poi viene rimesso il precedente colore. Dopo vengono resetta-
ti i flag e pulito il buffer.

Passiamo ora alla descrizione del main:
dopo la fase iniziale in cui vengono dichiarate le varie variabili e viene inizializzato il device, si entra nel while(1). All'arrivo
del primo byte (Byte_number=1) viene salvato nella variabile di appoggio "received" e mediante la struttura switch si distinguono 3
casi: 
1) 'v': stampa la stringa richiesta e resetta il sistema alla situazione iniziale di attesa;
2) A0: comincia tutta la sequenza di operazione per la lettura dei byte e controllo timeout;
3) default: errore e reset sistema.
Una volta che arriva il codice A0 parte il timer e si rimane in attesa del successivo byte controllando che non passino più di 5s.
All'arrivo del byte successivo, esso viene salvato nella struct di appoggio "c_partial" e viene resettato il timer azzerando il conta-
tore e rinizializzando il timer attraverso la funzione "Timer_init()". Dopo aver ricevuto i 3 byte vi è un controllo sull'effettivo
arrivo del tail C0:
1) se arrivato correttamente, viene stampata una stringa di coretta avvenuta della richiesta e si utilizzano dei flag per uscire, non
far stampare errori e arrivare alla funzione che aggiorna il colore del LED;
2) errore --> stampa errore, reset sistema e uscita dal ciclo più interno.
E' stato implementato anche il LED on-board come elemento aggiuntivo per indicare, una volta avvenuto l'invio di A0, la scansione
dei vari step di attesa del byte successivo; in porticolare si visualizza questo pattern: 
arrivo A0 --> LED acceso
arrivo byte per il rosso --> LED spento
arrivo byte per il verde --> LED acceso
arrivo byte per il blue --> LED spento
se arriva correttamente C0 --> LED RGB cambia colore
se non arriva correttamente C0 --> segnalazione di errore mediante la funz error
Quando si utlizza l'applicazione fornita o si invia su Coolterm il pacchetto intero questo pattern non si vede: è visibile solo se si 
inviano i byte separatamente (elemento aggiuntivo per prevedere l'utilizzo da parte di una persona che digita i byte uno alla volta).






 * ====================================================================================================================================
*/
