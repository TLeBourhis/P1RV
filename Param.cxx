#include "Param.h"

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
float Param::championColor[4] = {1.0f, 0.0f, 0.0f, 1.0f};
float Param::monsterColor[4] = {0.0f, 1.0f, 0.0f, 1.0f};;
int const Param::nbCardsOnPick = 5; //Nombre de cartes piochées par tour
float const Param::percentageWidthTakenByCardsPick = 0.8;

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
