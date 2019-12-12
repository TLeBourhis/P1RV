#include "Param.h"
#include "Monster.h"
#include "Champion.h"
#include <vector>
#include "Race.h"
#include <list>
#include <map>

using namespace std;

int const Param::windowPositionInitial[2] = {100,0};
int Param::windowWidth = 1000;
int Param::windowHeight = 1000;
float const Param::boardColor[3] = {1.0f,1.0f,1.0f};
int const Param::nbRows = 10;
int const Param::nbColumns = 10;
int const Param::dimCase = 10;
int const Param::borderSpacingCase = 2;
float const Param::caseColor[3] = {0.5f,0.5f,0.5f};
map<string, vector<float>> Param::colors;
int const Param::nbCardsOnPick = 5; //Nombre de cartes piochées par tour
float const Param::percentageWidthTakenByCardsPick = 0.8;
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

int const Param::cardHeightUp = 250;
int const Param::cardHeightDown = 50;
int const Param::cardWidth = 150;
int const Param::cardSpace = 20;



int const Param::nbRounds = 5;
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

int Param::getCardsWidth(){
  return percentageWidthTakenByCardsPick*windowWidth/nbCardsOnPick;
}


void Param::init() {
	//Initialisation des couleurs
	vector<float> c;
	c.push_back(0);
	c.push_back(1);
	c.push_back(0);
	c.push_back(1);
	colors.emplace("Cheap Ranged", c);
	c.clear();
	c.push_back(0);
	c.push_back(0);
	c.push_back(1);
	c.push_back(1);
	colors.emplace("Cheap CaC", c);
	c.clear();
	c.push_back(1);
	c.push_back(0);
	c.push_back(0);
	c.push_back(1);
	colors.emplace("MonstreCac", c);


	//Initialisation des monstres

	vector<Monster*> round_1;
	round_1.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 40, 5, 8, 10, 5, 10));
	Param::monstersByRounds.push_back(round_1);

	vector<Monster*> round_2;
	round_2.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 40, 5, 8, 10, 5, 10));
	round_2.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 40, 6, 8, 10, 10, 10));
	Param::monstersByRounds.push_back(round_2);

	vector<Monster*> round_3;
	round_3.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 20, 5, 8, 10, 5, 10));
	round_3.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 20, 6, 8, 10, 5, 10));
	round_3.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 600, 20, 5, 7, 10, 5, 10));
	Param::monstersByRounds.push_back(round_3);

	vector<Monster*> round_4;
	round_4.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 5, 8, 10, 5, 10));
	round_4.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 6, 8, 10, 5, 10));
	round_4.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 5, 7, 10, 5, 10));
	round_4.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 2, 2, 10, 5, 10));
	Param::monstersByRounds.push_back(round_4);

	vector<Monster*> round_5;
	round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 5, 8, 10, 5, 10));
	round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 6, 8, 10, 5, 10));
	round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 5, 7, 10, 5, 10));
	round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 2, 2, 10, 5, 10));
	round_5.push_back(new Monster("MonstreCac", 10, 0, 0, 20, 1, 500, 20, 9, 9, 10, 5, 10));
	Param::monstersByRounds.push_back(round_5);


	//Initialisation des races


	Param::races.push_back(new Race("Unskilled", 2, 4, "+50 health", "+100 health"));
	Param::races.push_back(new Race("Braindead", 2, 4, "+10 attackDamage", "+20 attackDamage"));




	//Initialisation des champions

	Param::allChampions.push_back(new Champion("Cheap Ranged", 10, 0, 0, 70, 1.0, 400, 35, 0, 0, 0, 4, 2, Param::races.at(0), Param::races.at(1)));
	//Param::allChampions.push_back(new Champion("Cheap CaC", 20, 0, 0, 20, 0.9, 500, 20, 0, 0, 0, 1, 2, Param::races.at(0), Param::races.at(1)));
	//Param::allChampions.push_back(new Champion("Mid Ranged", 20, 0, 0, 50, 1.3, 470, 50, 0, 0, 0, 1, 4, Param::races.at(0), Param::races.at(1)));
	//Param::allChampions.push_back(new Champion("Tank", 10, 0, 0, 100, 1.5, 400, 80, 0, 0, 0, 1, 5, Param::races.at(0), Param::races.at(1)));
	//Param::allChampions.push_back(new Champion("Ranged", 10, 0, 0, 100, 1.5, 400, 80, 0, 0, 0, 1, 7, Param::races.at(0), Param::races.at(1)));
}