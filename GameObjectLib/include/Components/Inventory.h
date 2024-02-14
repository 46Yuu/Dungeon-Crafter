#pragma once

#include "Component.h"
#include "Item.h"
#include "vector"


class Inventory : public Component
{
public:
	Inventory() = default;
	~Inventory() override = default;

	void AddItem(std::string _item,float _amount);

	void ClearInventory() { inventory.clear(); }
	bool CompareInventory(Inventory* targetInventory);
	std::vector<Item*> getInventory() { return inventory; }

private: 
	std::vector<Item*> inventory;
};