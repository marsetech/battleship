#include "modes/AdvancedField.h"

CampoAvanzato::CampoAvanzato(int dimensione) : CampoDiBattaglia(dimensione) {}

void CampoAvanzato::posizionaNavi() {
  srand(time(0));

  for (int i = 0; i < 4; ++i) {
    int x = rand() % dimensioneGriglia;
    int y = rand() % dimensioneGriglia;

    // Verifica se la posizione di quelle coordinate è vuota
    if (griglia[x][y] == Mare) {
      griglia[x][y] = NaveBattaglia;
      naviRimaste++;
    } else {
      --i;
    }
  }
}

void CampoAvanzato::muoviNavi() {
  std::vector<std::pair<int, int>>
      posizioniNavi; // Creazione vettore di coordinate per salvare posizioni
                     // attuali delle navi

  // Iterazioni per trovare le posizioni delle navi
  for (int i = 0; i < dimensioneGriglia; ++i) {
    for (int j = 0; j < dimensioneGriglia; ++j) {
      // Verifica se la cella corrente contiene una nave e aggiunge le
      // coordinate al vettore posizioniNavi
      if (griglia[i][j] == NaveBattaglia) {
        // Salva le coordinate (i, j) della nave
        posizioniNavi.emplace_back(i, j);
      }
    }
  }

  // Iterazione per muovere ogni nave trovata
  for (const auto &pos : posizioniNavi) {
    int nuovoX = pos.first;
    int nuovoY = pos.second;

    do {
      nuovoX = (nuovoX + rand() % 3 - 1 + dimensioneGriglia) %dimensioneGriglia;
      nuovoY = (nuovoY + rand() % 3 - 1 + dimensioneGriglia) %dimensioneGriglia;
    } while (griglia[nuovoX][nuovoY] != Mare);

    griglia[nuovoX][nuovoY] = NaveBattaglia;
    griglia[pos.first][pos.second] = Mare;
  }
}
