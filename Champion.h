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
  void displayCard(int i) const;
  void evolve();
  int buy();
  int sell();
  void moveTo(int _x, int _y);
  void move(Character *target);
  int die();
  void setColor(){color[0] = Param::championColor[0]; color[1] = Param::championColor[1]; color[2] = Param::championColor[2]; color[3] = Param::championColor[3];};
  //void spell(Monster *monster);
  Race * getRace(int i);



  //Constructeurs
  Champion(std::string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID, int _level, int cost, Race * _race1, Race * _race2);
  Champion(Champion * c);

  //Destructeur
  ~Champion();

  //Accesseurs
  std::string getName() { return name; };
};

#endif /* end of include guard: CHAMPION_H */
