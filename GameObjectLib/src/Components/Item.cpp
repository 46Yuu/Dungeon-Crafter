#include "Components/Item.h"

Item::Item(std::string _name) {
	name = _name;
	amount = 1;
}

Item::Item(std::string _name,float _amount) {
	name = _name;
	amount = _amount;
}