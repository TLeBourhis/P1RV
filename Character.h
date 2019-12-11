#ifndef CHARACTER_H
#define CHARACTER_H


#include <string>
#include <list>


class Character{
protected:
  static int staticID;


  int id;
  std::string name;
  //Object objects[3];
  int armor;
  int magicResistance;
  float spellPower;
  int attackRange;
  float attackSpeed;
  bool alive;
  int health;
  int maxHealth;
  int attackDamage;
  int i;
  int j;
  int caseID; //?
  float color[4];

  float distance(Character * c) const;

public:
  virtual void fight(std::list<Character*> allies, std::list<Character*> ennemies) = 0;
  virtual void display() const{};
  virtual void setColor(){};
  virtual void reset(int _i, int _j);

  virtual void move(Character *target){}; //Utilisé lors des combats

  virtual int die(){return 0;};

  void getHit(int damage, std::string type);
  void moveTo(int _x, int _y); //Utilisé pour le dragndrop

  bool isAlive(){return alive;};


  //Constructeurs
  Character(std::string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID );

  //Destructeur
  virtual ~Character(){};

  //Accesseurs
  int getI() { return i; };
  int getJ() { return j; };
  void setIJ(int _i, int _j) { i = _i; j = _j; };

};


#endif /* end of include guard: CHARACTER_H */
