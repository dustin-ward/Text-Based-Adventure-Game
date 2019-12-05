/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include "../include/person.h"
#include <algorithm>
#include <vector>
#include <string>
#include "../include/item.h"
#include "../include/inventory.h"

Person::Person() {
  inventory = new Inventory();
}

Person::~Person() {
  delete inventory;
}

Inventory* Person::getInventory() {
  return inventory;
}

void Person::giveItem(int Slot_Num, Person* receiver) {
  Item* i = inventory->getItem(Slot_Num);
  receiver->getInventory()->addItem(i);

  std::vector<Item*>* oldInv = inventory->getContents();
  oldInv->erase(std::remove(oldInv->begin(), oldInv->end(), i), oldInv->end());
}


