#ifndef BATTAGLIA_NAVALE_H
#define BATTAGLIA_NAVALE_H

#include "GameCore.h"

#define NaveBattaglia 'X'
#define Mare '.'
#define Mancato '~'
#define Colpito 'O'

class CampoDiBattaglia {
protected:
  int dimensioneGriglia;
  std::vector<std::vector<char>> griglia;
  int naviRimaste;
  bool sparoNonSalvato;

public:
  CampoDiBattaglia(int dimensione);

  virtual ~CampoDiBattaglia() {}

  virtual void
  posizionaNavi() = 0;
  void stampaGriglia(bool mostraNavi = false) const;
  void caricamentoFile();
  void gestioneSparo();
  bool verificaSparo(int x, int y);
  bool verificaSparoComputer(int x, int y);
  bool tutteNaviAffondate() const;
  bool caricaPartita(const std::string &nomeFile);
  void salvaPartita() const;
  int getDimensioneGriglia() const;
  char getElementoGriglia(int x, int y) const;
  bool getSparoNonSalvato() const;
  void resetSparoNonSalvato();
};

CampoDiBattaglia *creaCampo(int scelta, int dimensione);
bool salvataggioProgressi(CampoDiBattaglia *campo);
bool gestioneChiusura(CampoDiBattaglia *campo);

#endif
