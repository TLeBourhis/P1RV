#include "Param.h"
#include "Monster.h"
#include "Champion.h"
#include <vector>
#include "Race.h"
#include <list>

using namespace std;

int const Param::windowPositionInitial[2] = {100,0};
int Param::windowWidth = 1000;
int Param::windowHeight = 1000;
float const Param::boardColor[3] = {1.0f,1.0f,1.0f};
int const Param::nbRows = 10;
int const Param::nbColumns = 10;
int const Param::dimCase = 10;
int const Param::borderSpacingCase = 2;
const int Param::cardHeightUp = 250;
const int Param::cardHeightDown = 50;
const int Param::cardWidth = 150;
const int Param::cardSpace = 20;
float const Param::caseColor[3] = {0.5f,0.5f,0.5f};
float Param::championColor[4] = {1.0f, 0.0f, 0.0f, 1.0f};
float Param::monsterColor[4] = {0.0f, 1.0f, 0.0f, 1.0f};;
int const Param::nbCardsOnPick = 5; //Nombre de cartes piochées par tour
float const Param::percentageWidthTakenByCardsPick = 0.8;
float const Param::Cinf = 100;
int const Param::maxRage = 100; 
int const Param::rageByHit = 10; 
int const Param::rageByHitForBoss = 20;
int const Param::maxMana = 100;
int const Param::manaByHit = 10;
int const Param::sleepTime = 250;


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
	//Initialisation des monstres

	vector<Monster*> round_1;
	round_1.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 5, 8, 10, 5, 10));
	Param::monstersByRounds.push_back(round_1);

	vector<Monster*> round_2;
	round_2.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 5, 8, 10, 5, 10));
	round_2.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 6, 8, 10, 10, 10));
	Param::monstersByRounds.push_back(round_2);

	vector<Monster*> round_3;
	round_3.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 5, 8, 10, 5, 10));
	round_3.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 6, 8, 10, 5, 10));
	round_3.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 5, 7, 10, 5, 10));
	Param::monstersByRounds.push_back(round_3);

	vector<Monster*> round_4;
	round_4.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 5, 8, 10, 5, 10));
	round_4.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 6, 8, 10, 5, 10));
	round_4.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 5, 7, 10, 5, 10));
	round_4.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 2, 2, 10, 5, 10));
	Param::monstersByRounds.push_back(round_4);

	vector<Monster*> round_5;
	round_5.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 5, 8, 10, 5, 10));
	round_5.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 6, 8, 10, 5, 10));
	round_5.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 5, 7, 10, 5, 10));
	round_5.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 2, 2, 10, 5, 10));
	round_5.push_back(new Monster("Esteban", 10, 0, 0, 20, 1, 500, 20, 9, 9, 10, 5, 10));
	Param::monstersByRounds.push_back(round_5);


	//Initialisation des races


	Param::races.push_back(new Race("Unskilled", 2, 4, "+5 armor", "+15 armor"));
	Param::races.push_back(new Race("Braindead", 2, 4, "+5 dmg", "+15 dmg"));






	Param::allChampions.push_back(new Champion("PE", 10, 0, 0, 60, 1, 200, 20, 0, 0, 0, 0, 5, Param::races.at(0), Param::races.at(1)));
	Param::allChampions.push_back(new Champion("Thomas", 10, 0, 0, 60, 1, 100, 20, 0, 0, 0, 0, 2, Param::races.at(0), Param::races.at(1)));
}
