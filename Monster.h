#include <string>
#include "Character.h"
#include "Champion.h"
#include "Param.h"

#ifndef MONSTER_H
#define MONSTER_H

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
  void setColor(){color[0] = Param::monsterColor[0]; color[1] = Param::monsterColor[1]; color[2] = Param::monsterColor[2]; color[3] = Param::monsterColor[3];};


  //Constructeurs
  Monster(std::string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID, int _gold, int _rage);
  //Destructeur
  ~Monster(){};
  //Accesseurs
};

#endif /* end of include guard: MONSTER_H */
