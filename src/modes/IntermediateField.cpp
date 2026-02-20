#include "modes/IntermediateField.h"

CampoIntermedio::CampoIntermedio(int dimensione)
    : CampoDiBattaglia(dimensione) {}

void CampoIntermedio::posizionaNavi() {
  srand(time(0)); // Genera numeri interi casuali

  // Ciclo di 4 iterazioni (ci saranno 4 navi sulla griglia) per evitare che il
  // gioco si protragga troppo a lungo
  for (int i = 0; i < 4; ++i) {
    int x = rand() % dimensioneGriglia; // CoordinataRiga: Numero casuale tra 0
                                        // e dimensioneGriglia-1 (fa parte della
                                        // griglia del campo)
    int y = rand() % dimensioneGriglia; // CoordinataColonna: Numero casuale tra
                                        // 0 e dimensioneGriglia-1 (fa parte
                                        // della griglia del campo)

    // Verifica se la posizione di quelle coordinate è vuota (Non c'è presenza
    // di navi)
    if (griglia[x][y] == Mare) {
      griglia[x][y] = NaveBattaglia; // Inserisce char della nave
      naviRimaste++;                 // Aumenta contatore delle navi rimaste
    } else {
      --i; // Decrementa l'indice della posizione di 1
    }
  }
}
