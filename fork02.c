#include <stdio.h>   
#include <unistd.h>  
#include <stdlib.h>  

//=== Function prototypes ==================================================================
void childProcess(int led);

//=== Local variables ======================================================================
int led; // Variabile globale per il LED (1=verde, 2=rosso, 3=giallo)

//=== Main =================================================================================

int main() {
    char command;

    printf("[INIZIO] - In attesa di un comando da tastiera...\n");

    // Ciclo principale per l'ascolto dei comandi
    while (1) {
        printf("Inserisci un comando (v=verde, r=rosso, g=giallo, q=esci): ");
        scanf(" %c", &command);  // Aggiungiamo uno spazio per ignorare eventuali caratteri di nuova linea precedenti

        if (command == 'q') {
            printf("[PADRE] - Terminazione del programma.\n");
            break; // Esce dal ciclo e termina il programma
        }

        // Assegna il valore a "led" in base al comando
        if (command == 'v') {
            led = 1; // Verde
        } else if (command == 'r') {
            led = 2; // Rosso
        } else if (command == 'g') {
            led = 3; // Giallo
        } else {
            printf("[PADRE] - Comando non valido.\n");
            continue; // Ripete il ciclo se il comando non è valido
        }

        // Creazione del processo figlio
        int pid = fork();
        if (pid == 0) {
            // Esecuzione del codice del processo figlio
            childProcess(led);
            exit(0);  // Termina il processo figlio
        } else if (pid > 0) {
            // Processo padre, continua ad ascoltare
            printf("[PADRE] - Processo figlio con pid=%d creato.\n", pid);
        } else {
            // Errore nella creazione del processo figlio
            printf("[PADRE] - Errore nella creazione del processo figlio.\n");
        }
    }

    return 0;
}

//=== Local Functions ======================================================================

void childProcess(int led)
{
    int i;
    switch (led) {
        case 1: // Verde
            for (i = 0; i < 10; i++) {
                printf("[FIGLIO] - LED verde acceso\n");
                usleep(300000); // 0.3 secondi
                printf("[FIGLIO] - LED verde spento\n");
                usleep(300000); // 0.3 secondi
            }
            break;
        case 2: // Rosso
            for (i = 0; i < 10; i++) {
                printf("[FIGLIO] - LED rosso acceso\n");
                usleep(700000); // 0.7 secondi
                printf("[FIGLIO] - LED rosso spento\n");
                usleep(700000); // 0.7 secondi
            }
            break;
        case 3: // Giallo
            for (i = 0; i < 10; i++) {
                printf("[FIGLIO] - LED giallo acceso\n");
                usleep(1200000); // 1.2 secondi
                printf("[FIGLIO] - LED giallo spento\n");
                usleep(1200000); // 1.2 secondi
            }
            break;
        default:
            printf("[FIGLIO] - Comando non valido.\n");
            break;
    }
}
