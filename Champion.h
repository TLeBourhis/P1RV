#ifndef CHAMPION_H
#define CHAMPION_H


#include "Character.h"
#include "Race.h"
#include "Param.h"
#include <list>

class Champion : public Character{
private:
  int level;
  Race *races[2];
  int cost;

public:
  virtual void display() const;
  void fight(std::list<Character*> allies, std::list<Character*> ennemies);
  void evolve();
  int buy();
  int sell();
  void move(Character *target);
  int die();
  //void spell(Monster *monster);
  Race * getRace(int i);
  void reset(int _i, int _j);



  //Constructeurs
  Champion(std::string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID, int _level, int cost, Race * _race1, Race * _race2);
  Champion(Champion * c);

  //Destructeur
  ~Champion();

  //Accesseurs
  std::string getName() { return name; };
  int getCost() { return cost; };
  int getLevel() { return level; };
};

#endif /* end of include guard: CHAMPION_H */
