#include "Character.h"
#include <string>
#include <cmath>

using namespace std;

int Character::staticID = 0;

Character::Character(std::string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID/*, float _color[4]*/){
  staticID++;
  id = staticID;

  name = _name;
  armor = _armor;
  magicResistance = _magicResistance;
  spellPower = _spellPower;
  attackRange = _attackRange;
  attackSpeed = _attackSpeed;
  alive = true;
  health = _health;
  attackDamage = _attackDamage;
  i = _i;
  j = _j;
  caseID = _caseID;
  color[0] = 1.0f;
  color[1] = 0.0f;
  color[2] = 0.0f;
  color[3] = 1.0f;
  //color = _color;
}


void Character::getHit(int damage, string type){
  if(type == "ATTACK_DAMAGE"){
    health -= (damage - armor);
    if(health <= 0){
      this->die();
    }
  }else{
    health -= (damage - magicResistance);
    if(health <= 0){
      this->die();
    }
  }
}


float Character::distance(Character * c) const{
  return sqrt(pow(c->getX()-this->getX(),2) + pow(c->getY()-this->getY(),2));
}

void Character::moveTo(int _x, int _y){
  this->x = _x;
  this->y = _y;
}
