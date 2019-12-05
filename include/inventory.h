/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
  @author Jared Sisco, <j.sisco@uleth.ca>
* @date 2019-11
*/
#ifndef INCLUDE_INVENTORY_H_
#define INCLUDE_INVENTORY_H_

/**
* Data structure that stores all in game items
*/

#include <string>
#include <vector>
#include "./item.h"

class Inventory {
 public:
  /**
  * Default constructor
  */
  Inventory();

  /**
  * Default destructor
  */
  virtual ~Inventory();

  /**
  * Access the items in an inventory
  * @return A pointer to the vector of Item pointers
  */
  std::vector<Item*>* getContents() const;

  /**
  * Adds an item to the inventory
  * @param item A pointer to the Item to be added
  * @return A bool value to represent a successful addition
  */
  bool addItem(Item* item);

  /**
  * Removes an item from the inventory
  * @param Slot_Num The position of the item to remove
  * @param full_deletion Deletes from memory if true,
  removes pointer only if false
  */
  Item* removeItem(int Slot_Num, bool full_deletion);

  /**
  * Removes all items
  */
  void removeAll();

  /**
  * Creates a list of all the items in the inventory
  * @return A list of items as a string
  */
  std::string listInventory();

  /**
  *
  */
  void Save_Inventory(std::ofstream& Output_File);

  /**
  * Accessing an item in an inventory
  * @param Slot_Num Position of the item in the inventory
  * @return A pointer to the item
  */
  Item* getItem(int Slot_Num) const;

  /**
  * Accessing an item in an inventory
  * @param Needed_Item Type of the item in the inventory
  * @return A pointer to the item
  */
  Item* getItem(ItemType Needed_Item) const;

  /**
  * Transfers an item from one inventory to another
  * @param From_Inv The inventory to take an item from
  * @param From_Slot The position of the item in the inventory
  * @param To_Inv The new inventory to give the item to
  * @return A bool value based on if the item was successfully transferred
  */
  bool TransferItem(int From_Slot, Inventory* To_Inv);


 private:
  // Actual container of all item objects.
  std::vector<Item*>* contents;
};

#endif  // INCLUDE_INVENTORY_H_
