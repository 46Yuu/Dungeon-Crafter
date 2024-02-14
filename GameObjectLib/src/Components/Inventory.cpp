#include "Components/Inventory.h"

void Inventory::AddItem(std::string _item,float _amount) {
    bool itemExists = false;

    for (Item* item : inventory) {
        if (item->getName() == _item) {
            item->increaseAmountByOne();
            itemExists = true;
            break;
        }
    }
    if (!itemExists) {
        auto newItem = new Item();
        newItem->setName(_item);
        newItem->setAmount(_amount);
        inventory.push_back(newItem);
    }
}

bool Inventory::CompareInventory(Inventory* targetInventory) {
    if (inventory.empty() && targetInventory->inventory.empty()) {
        return false;
    }
    for (Item* targetItem : targetInventory->inventory) {
        bool itemMatched = false;
        for (Item* playerItem : inventory) {
            if (playerItem->getName() == targetItem->getName()) {
                if (playerItem->getAmount() >= targetItem->getAmount()) {
                    itemMatched = true;
                    break;
                }
            }
        }
        if (!itemMatched) {
            return false;
        }
    }
    return true;
}