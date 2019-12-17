#ifndef BOSS_H
#define BOSS_H

#include "Character.h"
#include "Monster.h";
#include <list>
#include <string>

class Boss : public Monster{
private:
  int mana;

public:
  void fight(std::list<Character*> allies, std::list<Character*> ennemies);
  void spell1(std::list<Character*> ennemies);

  Boss(std::string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID, int _gold, int _rage, int _mana);

  ~Boss(){};
};


#endif /* end of include guard: BOSS_H */
