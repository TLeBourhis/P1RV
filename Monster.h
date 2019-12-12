#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Character.h"
#include "Champion.h"
#include "Param.h"

class Monster : public Character{
protected:
  int gold;
  int rage;

public:
  void fight(std::list<Character*> allies, std::list<Character *> ennemies);
  virtual void display() const;
  void boostedAttack(Character *champion) const; //Ici on prend en argument un Character car dans fight on a des characters puisque Champion aussi l'utilise, et on ne peut convertir un Character en CHampion
  void move(Character *target);
  int die();

  //Constructeurs
  Monster(std::string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID, int _gold, int _rage);
  //Destructeur
  ~Monster(){};
  //Accesseurs
};

#endif /* end of include guard: MONSTER_H */
