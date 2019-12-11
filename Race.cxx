#include "Race.h"

#include "Champion.h";

using namespace std;

Race::Race(string _name, int _bT1, int _bT2, string _b1, string _b2){
   name = _name;

   bonusTreshold[0] = _bT1;
   bonusTreshold[1] = _bT2;
   bonus[0] = _b1;
   bonus[1] = _b2;
}

void Race::addBonus(list<Champion*> champions) const{
   
}

void Race::display() const{

}

bool Race::operator==(Race const& r) {
	return name == r.name;
}