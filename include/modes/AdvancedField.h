#ifndef CAMPO_AVANZATO_H
#define CAMPO_AVANZATO_H

#include "field/BattleField.h"
#include "GameCore.h"

class CampoAvanzato : public CampoDiBattaglia {
public:
  CampoAvanzato(int dimensione);
  void posizionaNavi() override;
  void muoviNavi();
};

#endif
