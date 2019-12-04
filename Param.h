#include <string>

#ifndef PARAM_H
#define PARAM_H

class Param{
public:
  static const int windowPositionInitial[2];
  static int windowWidth;
  static int windowHeight;
  static const float boardColor[3];
  static const int nbRows;
  static const int nbColumns;
  static const int dimCase;
  static const int borderSpacingCase;
  static const float caseColor[3];
  static const int nbCardsOnPick;
  static const int cardsHeight;
  static const float percentageWidthTakenByCardsPick;
  static float championColor[4];
  static float monsterColor[4];


  static int getBoardDim(std::string coordonnee);
  static int getCardsWidth();
};

#endif /* end of include guard: PARAM_H */
