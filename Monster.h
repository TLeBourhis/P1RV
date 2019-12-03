#include <string>
#include "Character.h"
#include "Champion.h"

#ifndef MONSTER_H
#define MONSTER_H

class Monster : public Character{
protected:
  int gold;
  int rage;

public:
  virtual void fight(std::list<Character*> allies, std::list<Character*> ennemies);
  void boostedAttack(Champion *champion) const;
  virtual void display() const;
  void move(Character *target);
  int die();

  //Constructeurs
  Monster();
  //Destructeur
  ~Monster(){};
  //Accesseurs
};

#endif /* end of include guard: MONSTER_H */
