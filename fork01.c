#include <stdio.h>   // printf
#include <unistd.h>  // getpid, fork
#include <math.h>    // sqrt per il calcolo dell'ipotenusa

//=== Function prototypes ==================================================================
void childProcess(int cateto1, int cateto2);
void fatherProcess(int cateto1, int cateto2);

//=== Local variables ======================================================================
int cateto1 = 3, cateto2 = 4; // inizializzazione dei cateti del triangolo
int ris;

//=== Main =================================================================================

int main() {

  printf("\n[INIZIO] - Esiste solo il processo padre, il padre del padre e' la shell \n");
  printf("[INIZIO] - Prima della fork - pid processo=%d, pid padre=%d\n", getpid(), getppid());

  // Creazione del processo figlio
  int pid = fork();
  if (pid == 0) {
    // Esecuzione codice del processo figlio
    childProcess(cateto1, cateto2);
  } else if (pid > 0) {
    // Esecuzione codice del processo padre
    fatherProcess(cateto1, cateto2);
  } else { // pid < 0
    // Errore
    printf("Creazione del processo figlio fallita!\n");
  }

  // Codice comune a processo padre e figlio
  printf("[FINE] - Termine del processo con pid=%d, ris=%d, padre=%d\n", getpid(), ris, getppid());
}

//=== Local Functions ======================================================================

void childProcess(int cateto1, int cateto2)
{
  // Calcolo del perimetro: cateto1 + cateto2 + ipotenusa
  double ipotenusa = sqrt(cateto1 * cateto1 + cateto2 * cateto2); // teorema di Pitagora
  double perimetro = cateto1 + cateto2 + ipotenusa;

  printf("\n[Figlio] - Il perimetro del triangolo è: %.2f\n", perimetro);
  printf("[Figlio] - pid=%d, pid padre=%d\n", getpid(), getppid());
}

void fatherProcess(int cateto1, int cateto2)
{
  // Calcolo dell'area: (cateto1 * cateto2) / 2
  ris = (cateto1 * cateto2) / 2;

  printf("\n[Padre] - pid=%d, pid padre=%d\n", getpid(), getppid());
  printf("[Padre] - L'area del triangolo è: %d\n", ris);
}
