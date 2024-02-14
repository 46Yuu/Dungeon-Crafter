#pragma once
#include <string>

class Item
{
public: 
	Item() = default;
	Item(std::string _name);
	Item(std::string _name, float _amount);
	virtual ~Item() = default;

	void setName(std::string _name) { name = _name; }
	void setAmount(float _amount) { amount = _amount; }
	std::string getName() { return name; }
	float getAmount() { return amount; }
	void increaseAmountByOne() { amount++; }
private:
	std::string name = "Item";
	float amount = 0;
};