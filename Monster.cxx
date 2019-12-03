#include "headers/Monster.h"
#include <string>

using namespace std;

Monster::Monster(string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _x, int _y, int _caseID, int _gold, int _rage) : Character(_name,_armor,_magicResistance, _spellPower, _attackRange, _attackSpeed, _health, _attackDamage, _x, _y, _caseID){
  gold = _gold;
  rage = _rage;
}

void Monster::fight(list<Character*> allies, list<Character*> ennemies){
  //Gère les actions du champion lors du combat.


  if(size(ennemies) == 0){
    //Si pas d'ennemi


  }else{
    //Récupération de l'ennemi le plus proche
    float distMin = this->distance(*ennemies.begin());
    Character * nearestEnnemy = *ennemies.begin();
    for(list<Character*>::iterator it = ennemies.begin(); it != ennemies.end(); ++it){
      float d = this->distance(*it);
      if(d < distMin){
        distMin = d;
        nearestEnnemy = *it;
      }
    }




    if(distMin > attackRange){
      //L'ennemi est en-dehors de la range d'attaque
      //Déplacement vers l'ennemi le plus proche
      this->move(nearestEnnemy);
    }else{
      //Attaque de l'ennemi
      if(rage == 100){
        rage = 0;
        this->boostedAttack(nearestEnnemy);
      }else{
        nearestEnnemy->getHit(attackDamage,"ATTACK_DAMAGE");
        rage += 10; //ATTENTION : Mettre se paramètre d'augmentation de rage dans Param
      }
    }
  }
}

void Monster::boostedAttack(Champion *champion) const{
  //Inflige le double des dégâts d'auto-attaque au champion adverse

  champion->getHit(2*this->attackDamage,"ATTACK_DAMAGE");
}


int Monster::die(){
  this->alive = false;
  return gold;
}
