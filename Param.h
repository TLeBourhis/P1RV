#ifndef PARAM_H
#define PARAM_H

#include <string>
#include <vector>
#include <list>
#include <map>

class Champion;

class Monster;

class Race;

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
   static const int cardHeightUp;
  static const int cardHeightDown;
  static const int cardWidth;
  static const int cardSpace;
  static const float caseColor[3];
  static const int nbCardsOnPick;
  static const int cardsHeight;
  //static const float percentageWidthTakenByCardsPick;
  static std::map<std::string, std::vector<float>> colors;
  static const float Cinf; //Constante utilisé dans le calcul du poids des connexions dans le graphe d'adjacence
  static std::vector<std::vector<Monster*>> monstersByRounds; //A initialiser correctement
  static const int maxRage; //Rage maximale pour les montres = 100
  static const int rageByHit; //Gain de rage par aa = 10
  static const int rageByHitForBoss; //Gain de rage par aa pour les boss = 20
  static const int maxMana; //Mana maximum pour les boss = 100
  static const int manaByHit; //Gain de mana par aa = 10
  static const int sleepTime;

  static const int healthBonusByLevel;
  static const int armorBonusByLevel;
  static const int magicResistanceBonusByLevel;
  static const float spellPowerBonusByLevel;
  static const int attackRangeBonusByLevel;
  static const float attackSpeedBonusByLevel;
  static const int attackDamageBonusByLevel;

  static const int levelMax;
  
  static const int nbRounds;
  static const int startingGolds;

  static std::list<Champion*> allChampions;
  static std::vector<Race*> races;


  static int getBoardDim(std::string coordonnee);
  //static int getCardsWidth();
  static void init();
};

#endif /* end of include guard: PARAM_H */
