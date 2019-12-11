#pragma once


#include <string>
#include <list>


class Champion;





class Race{
private:
  std::string name;
  int bonusTreshold[2];
  std::string bonus[2];

public:
  Race(std::string _name, int _bT1, int _bT2, std::string _b1, std::string _b2);

  void addBonus(std::list<Champion*> champions) const;
  void display() const;

  bool operator==(Race const& r);

  std::string getName() { return name; };
  int getBonusTreshold(int i) { return bonusTreshold[i]; };
};


