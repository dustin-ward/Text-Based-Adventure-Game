/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
  @author Jared Sisco, <j.sisco@uleth.ca>
* @date 2019-11
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include "../include/inventory.h"
#include "../include/item.h"

Inventory::Inventory() {
  contents = new std::vector<Item*>;
}

Inventory::~Inventory() {
  for (std::size_t i = 0; i < contents->size(); i++)
    delete (*contents)[i];
  delete contents;
}

std::vector<Item*>* Inventory::getContents() const {
  return contents;
}

bool Inventory::addItem(Item* i) {
  contents->push_back(i);
  return true;    // Optional return if inventory is full
}

Item* Inventory::removeItem(int Slot_Num, bool full_deletion) {
  Item* item = this->getItem(Slot_Num);
  if (item == nullptr)
    return nullptr;

  contents->erase(contents->begin() + Slot_Num);
  if (full_deletion) {
    delete item;
    return nullptr;
  }

  return item;
}

void Inventory::removeAll() {
  while (contents->size() != 0) {
    delete (*contents)[contents->size()-1];
    contents->pop_back();
  }
}

Item* Inventory::getItem(int Slot_Num) const {
  if (Slot_Num > (contents->size()))
    return nullptr;
  return (*contents)[Slot_Num];
  // Throw item not found error, or return NULL
}

Item* Inventory::getItem(ItemType Needed_Item) const {
  std::vector<Item*> Content_Interal = *contents;
  int Slot_Num = -1;

  for (size_t ii = 0; ii < contents->size(); ++ii) {
    if (Content_Interal[ii]->getType() == Needed_Item) {
      Slot_Num = ii;
      break;
    }
  }

  if (Slot_Num == -1)
    return nullptr;
  return (*contents)[Slot_Num];
  // Throw item not found error, or return NULL
}


std::string Inventory::listInventory() {
  std::string Str_List = "";
  std::vector<Item*> Contents = *Inventory::getContents();
  std::size_t Content_Size = Contents.size();

  for (std::size_t ii = 0; ii < Content_Size; ++ii) {
    Str_List.append(Contents[ii]->getId());
    if (ii != (Content_Size - 1U))
      Str_List = Str_List + ", ";
  }
  return Str_List;
}

bool Inventory::TransferItem(int From_Slot,
                             Inventory* To_Inv) {
  Item* Removed_Item = this->removeItem(From_Slot, false);
  if (Removed_Item == nullptr)
    return false;
  return To_Inv->addItem(Removed_Item);
}

void Inventory::Save_Inventory(std::ofstream& Output_File) {
  std::size_t Content_Size = contents->size();

  for (std::size_t ii = 0; ii < Content_Size; ++ii) {
    Output_File << static_cast<int>((*contents)[ii]->getType());
    if (ii != Content_Size - 1)
      Output_File << " ";
  }
  return;
}
