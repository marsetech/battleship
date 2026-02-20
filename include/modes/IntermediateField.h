#ifndef CAMPO_INTERMEDIO_H
#define CAMPO_INTERMEDIO_H

#include "field/BattleField.h"
#include "GameCore.h"

class CampoIntermedio : public CampoDiBattaglia {
public:
  CampoIntermedio(int dimensione);
  void posizionaNavi() override;
};

#endif
