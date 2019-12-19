#include "Param.h"
#include "Monster.h"
#include "Champion.h"
#include <vector>
#include "Race.h"
#include <list>
#include "Boss.h"
#include <map>
#include <iostream>

using namespace std;

int const Param::windowPositionInitial[2] = {100,0};
int Param::windowWidth = 1000;
int Param::windowHeight = 815; // !!!!!!adapté à mon pc, 850 d'habitude ou 1000
float const Param::boardColor[3] = {1.0f,1.0f,1.0f};
int const Param::nbRows = 10;
int const Param::nbColumns = 10;
int const Param::dimCase = 10;
int const Param::borderSpacingCase = 2;
int const Param::cardHeightUp = 250;
int const Param::cardHeightDown = 50;
int const Param::cardWidth = 150;
int const Param::cardSpace = 20;
float const Param::caseColor[3] = {0.5f,0.5f,0.5f};
map<string, vector<float>> Param::colors;
int const Param::nbCardsOnPick = 5; //Nombre de cartes piochées par tour
//float const Param::percentageWidthTakenByCardsPick = 0.8;
float const Param::Cinf = 100;
int const Param::maxRage = 100; 
int const Param::rageByHit = 10; 
int const Param::rageByHitForBoss = 20;
int const Param::maxMana = 100;
int const Param::manaByHit = 10;
int const Param::sleepTime = 250;

int const Param::healthBonusByLevel = 50;
int const Param::armorBonusByLevel = 10;
int const Param::magicResistanceBonusByLevel = 10;
float const Param::spellPowerBonusByLevel = 0;
int const Param::attackRangeBonusByLevel = 0;
float const Param::attackSpeedBonusByLevel = 0;
int const Param::attackDamageBonusByLevel = 20;

int const Param::levelMax = 4;

int const Param::nbRounds = 6;
int const Param::startingGolds = 10;

//Les monstres par round
vector<vector<Monster*>> Param::monstersByRounds;
vector<Race*> Param::races;
list<Champion*> Param::allChampions;





int Param::getBoardDim(string coordonnee){
    //Renvoie les dimensions du board suivant la coordonnee en paramètre
    int dim = -1;
    if(coordonnee == "x" || coordonnee == "X"){
      dim = dimCase*(nbColumns+borderSpacingCase*2);
    }

    if(coordonnee == "y" || coordonnee == "Y"){
      dim = dimCase*(nbRows+borderSpacingCase*2);
    }

    return dim;
}

/*int Param::getCardsWidth(){
  return percentageWidthTakenByCardsPick*windowWidth/nbCardsOnPick;
}*/


void Param::init() {
	//Initialisation des couleurs
	vector<float> c;
	c.push_back(0.33);
	c.push_back(0.48);
	c.push_back(0.68);
	c.push_back(1);
	colors.emplace("Cheap Ranged", c);
	c.clear();
	c.push_back(0.70);
	c.push_back(0.69);
	c.push_back(0.57);
	c.push_back(1);
	colors.emplace("Cheap CaC", c);
	c.clear();
	c.push_back(0.62);
	c.push_back(0.33);
	c.push_back(0.12);
	c.push_back(1);
	colors.emplace("Earth Mage", c);
	c.clear();
	c.push_back(0.99);
	c.push_back(0.86);
	c.push_back(0.07);
	c.push_back(1);
	colors.emplace("Mid Ranged", c);
	c.clear();
	c.push_back(0.93);
	c.push_back(0);
	c.push_back(0);
	c.push_back(1);
	colors.emplace("Fire Tank", c);
	c.clear();
	c.push_back(0.15);
	c.push_back(0.77);
	c.push_back(0.93);
	c.push_back(1);
	colors.emplace("Ice Mage", c);
	c.clear();
	c.push_back(0.95);
	c.push_back(0.99);
	c.push_back(0.99);
	c.push_back(1);
	colors.emplace("Wind Ranged", c);
	c.clear();
	c.push_back(0.12);
	c.push_back(0.63);
	c.push_back(0.33);
	c.push_back(1);
	colors.emplace("MonstreCac", c);
	c.clear();
	c.push_back(0.53);
	c.push_back(0.91);
	c.push_back(0.56);
	c.push_back(1);
	colors.emplace("MonstreRanged", c);
	c.clear();
	c.push_back(1.0);
	c.push_back(0.0);
	c.push_back(1.0);
	c.push_back(1);
	colors.emplace("BOSS", c);


	//Initialisation des monstres


	vector<Monster*> round_1;
	//round_1.push_back((Monster*)new Boss("BOSS", 30, 30, 0, 20, 1, 5000, 10, 5, 8, 10, 5, 0, 0));
	round_1.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 40, 5, 8, 10, 5, 10));
	Param::monstersByRounds.push_back(round_1);

	vector<Monster*> round_2;
	round_2.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 40, 5, 8, 10, 5, 10));
	round_2.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 40, 6, 8, 10, 10, 10));
	Param::monstersByRounds.push_back(round_2);

	vector<Monster*> round_3;
	round_3.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 20, 5, 8, 10, 5, 10));
	round_3.push_back(new Monster("MonstreRanged", 10, 0, 0, 60, 1, 600, 20, 6, 8, 10, 5, 10));
	round_3.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 20, 5, 7, 10, 5, 10));
	Param::monstersByRounds.push_back(round_3);

	vector<Monster*> round_4;
	round_4.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 5, 8, 10, 5, 10));
	round_4.push_back(new Monster("MonstreRanged", 10, 0, 0, 20, 1, 500, 20, 6, 8, 10, 5, 10));
	round_4.push_back(new Monster("MonstreCac", 10, 0, 0, 60, 1, 500, 20, 5, 7, 10, 5, 10));
	round_4.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 2, 2, 10, 5, 10));
	Param::monstersByRounds.push_back(round_4);

	vector<Monster*> round_5;
	//round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 5, 8, 10, 5, 10));
	//round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 6, 8, 10, 5, 10));
	//round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 5, 7, 10, 5, 10));
	//round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 2, 2, 10, 5, 10));
	//round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 9, 9, 10, 5, 10));
	round_5.push_back((Monster*)new Boss("BOSS", 30, 30, 0, 20, 1, 5000, 10, 5, 8, 10, 5, 0, 0));
	Param::monstersByRounds.push_back(round_5);

	//vector<Monster*> round_6;
	//round_1.push_back((Monster*)new Boss("BOSS", 30, 30, 0, 20, 1, 5000, 10, 5, 8, 10, 5, 0, 0));
	//Param::monstersByRounds.push_back(round_6);


	//Initialisation des races


	Param::races.push_back(new Race("Ranged", 2, 4, "+10 attackRange", "+20 attackRange"));
	Param::races.push_back(new Race("Fighter", 2, 4, "+5 armor", "+15 armor"));
	Param::races.push_back(new Race("Elemental", 2, 4, "+10 attackDamage", "+30 attackDamage"));
	Param::races.push_back(new Race("Mage", 2, 4, "+10 spellPower", "+25 spellPower"));
	Param::races.push_back(new Race("Soldier", 2, 4, "+40 health", "+100 spellPower"));



	//Initialisation des champions


	Param::allChampions.push_back(new Champion("Cheap Ranged", 10, 0, 0, 70, 1.0, 400, 35, 0, 0, 0, 1, 2, Param::races.at(0), Param::races.at(4)));
	Param::allChampions.push_back(new Champion("Cheap CaC", 20, 0, 0, 20, 1.0, 500, 20, 0, 0, 0, 1, 2, Param::races.at(1), Param::races.at(4)));
	Param::allChampions.push_back(new Champion("Earth Mage", 10, 0, 20, 30, 1.0, 450, 0, 0, 0, 0, 1, 3, Param::races.at(3), Param::races.at(2)));
	Param::allChampions.push_back(new Champion("Mid Ranged", 20, 0, 0, 50, 1.0, 470, 50, 0, 0, 0, 1, 4, Param::races.at(0), Param::races.at(4)));
	Param::allChampions.push_back(new Champion("Ice Mage", 10, 0, 60, 70, 1.0, 300, 0, 0, 0, 0, 1, 5, Param::races.at(3), Param::races.at(2)));
	Param::allChampions.push_back(new Champion("Fire Tank", 30, 0, 0, 20, 1.0, 600, 40, 0, 0, 0, 1, 5, Param::races.at(1), Param::races.at(2)));
	Param::allChampions.push_back(new Champion("Wind Ranged", 10, 0, 0, 100, 1.0, 200, 80, 0, 0, 0, 1, 7, Param::races.at(0), Param::races.at(2)));
}
