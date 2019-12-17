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
  int initialArmor;
  int armor;
  int initialMagicResistance;
  int magicResistance;
  float initialSpellPower;
  float spellPower;
  int initialAttackRange;
  int attackRange;
  float initialAttackSpeed;
  float attackSpeed;
  bool alive;
  int health;
  int maxHealth;
  int initialHealth;
  int initialAttackDamage;
  int attackDamage;
  float x;
  float y;
  int i;
  int j;
  int caseID; //?
  float color[4];

  float distance(Character * c) const;

public:
  virtual void fight(std::list<Character*> allies, std::list<Character*> ennemies) = 0;
  virtual void display() const{};
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
  int getX() { return x; };
  int getY() { return y; };
  int getI() { return i; };
  int getJ() { return j; };
  void setX(int _x) { x = _x; };
  void setY(int _y) { y = _y; };
  void setIJ(int _i, int _j);
  void setColor();
  float getColor(int i) const;

  void addArmor(int a) { armor += a; };
  int getArmor() { return armor; };
  void addMagicResistance(int mr) { magicResistance += mr; };
  int getMagicResistance() { return magicResistance; };
  void addSpellPower(float sp) { spellPower += sp; };
  void addAttackRange(int ar) { attackRange += ar; };
  int getAttackRange() { return attackRange; };
  void addHealth(int h) { maxHealth += h; health += h; };
  int getHealth() { return health; };
  void addAttackSpeed(float as) { attackSpeed += as; };
  void addAttackDamage(int ad) { attackDamage += ad; };
  int getAttackDamage() { return attackDamage; };

};


#endif /* end of include guard: CHARACTER_H */
