/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
  @author Jared Sisco, <j.sisco@uleth.ca>
* @date 2019-11
*/

#include "../include/item.h"
#include <string>

Item::Item(ItemType Needed_Type) :
  Item_Properties{get_Properties(Needed_Type)} {}

Item::~Item() {}

std::string Item::getId() const {
  return Item_Properties.item_name;
}

std::string Item::getDescription() const {
  return Item_Properties.description;
}

ItemType Item::getType() const {
  return Item_Properties.type;
}

std::string Item::getAct() const {
  return Item_Properties.use_text;
}

Item_Data Item::get_Properties(ItemType Needed_Type) {
  std::string item_name_p;
  std::string description_p;
  std::string u_text;

  switch (Needed_Type) {
  case I_Spare_Part:
    item_name_p = "Spare Engine Part";
    description_p = "A loose part for a generator, could be useful.";
    u_text = "You hand the part to the crew member, he inserts the part into\n"
             "the machine. Seconds later the power turns on!";
    break;
  case I_Safe_Code:
    item_name_p = "Note";
    description_p = "A torn out piece of a notebook with 6 numbers on it.";
    u_text = "You enter the code, a small beep is sounded as the safe swings\n"
             "open. \n A set of keys fall onto the floor";
    break;
  case I_Cargo_Key:
    item_name_p = "Cargo Hold Key";
    description_p = "A key to open the cargo bay!";
    u_text = "You turn the key in the door and the cargo bay doors slowly\n"
             "slide open";
    break;
  case I_Hand_Warmer:
    item_name_p = "Hand Warmer";
    description_p = "A small pack of heat to increase your temperature.\n"
                    "Use this item to gain +10 temperature.";
    u_text = "You break the hand warmer pack, activating it and increasing\n"
             "your core temperature by 10!";
    break;
  case I_Coffee_Mug:
    item_name_p = "Coffee Mug";
    description_p = "A mug of some surprisingly warm coffee.\n"
                    "Use this item to gain +5 temperature.";
    u_text = "You swiftly consume the coffee not questioning where it came\n"
             "from or why it was hot. +5 temperature!";
    break;
  case I_NULL:
    item_name_p = "Something went wrong";
    description_p = "Not sure how you did this.";
    u_text = "Cannot use this item?";
    break;
  }

  return Item_Data(Needed_Type, item_name_p, u_text, description_p);
}
