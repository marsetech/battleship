#ifndef CAMPO_PRINCIPIANTE_H
#define CAMPO_PRINCIPIANTE_H

#include "field/BattleField.h"
#include "GameCore.h"

class CampoPrincipiante : public CampoDiBattaglia {
public:
  CampoPrincipiante(int dimensione);
  void posizionaNavi() override;

private:
  void caricaNaviDaFile();
  void creaNaviInFile();
};

#endif
