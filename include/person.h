/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#ifndef INCLUDE_PERSON_H_
#define INCLUDE_PERSON_H_

/**
* An abstract representation of a person
* Gives all NPC's and the Player common inventory functionality
*/

#include <string>
#include "./inventory.h"

class Person {
 public:
  /**
  * Default Constructor
  */
  Person();

  /**
  * Default destructor
  */
  virtual ~Person();

  /**
  * Access the inventory of a person
  * @return A pointer to the related inventory
  */
  Inventory* getInventory();

  /**
  * Gives an item to another person, and removes it from itself
  * @param id The name of the Item to give
  * @param receiver A pointer to the person receiving the item
  */
  void giveItem(int Slot_Num, Person* receiver);

 private:
  Inventory* inventory;
};

#endif  // INCLUDE_PERSON_H_
