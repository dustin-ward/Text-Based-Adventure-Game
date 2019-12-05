/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca
  @author Jared Sisco, <j.sisco@uleth.ca>
* @date 2019-11
*/

#include "../include/room.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "../include/item.h"
#include "../include/inventory.h"
#include "../include/NPC.h"

Room::Room(Room_Type Room_N, bool From_Load) {
  items = new Inventory();
  characters = new std::vector<NPC*>;
  Contained_Properties = loadDetails(Room_N);

  if (!From_Load) {
    New_Data_Creation(Room_N);
    NPC_Creation(Room_N);
    checkCondition();
  }

  // connected = new std::vector<Room*>;
}

Room::~Room() {
  delete items;

  std::vector<NPC*>* v = this->getCharacters();
  while (v->size() > 0) {
    delete v[0][v->size() - 1];
    v->pop_back();
  }

  delete characters;
}

Room_Type Room::getType() const {
  return Contained_Properties.Room_Typing;
}

std::string Room::getName() const {
  return Contained_Properties.Friendly_Name;
}

std::string Room::getDescription() const {
  return Contained_Properties.Description;
}

Inventory* Room::getInventory() const {
  return items;
}

std::string Room::getLockText() const {
  return Contained_Properties.Locked_Text;
}

std::string Room::getExamine() const {
  return Contained_Properties.Examine_Text;
}

std::vector<NPC*>* Room::getCharacters() const {
  return characters;
}

NPC* Room::getCharacter(int Slot_Num) const {
  if (Slot_Num > (characters->size()))
    return nullptr;
  return (*characters)[Slot_Num];
  // Throw item not found error, or return NULL
}

NPC* Room::getCharacter(Character_Type Needed_NPC) const {
  std::vector<NPC*> Content_Interal = *characters;
  int Slot_Num = -1;

  for (size_t ii = 0; ii < characters->size(); ++ii) {
    if (Content_Interal[ii]->getType() == Needed_NPC) {
      Slot_Num = ii;
      break;
    }
  }

  if (Slot_Num == -1)
    return nullptr;
  return (*characters)[Slot_Num];
  // Throw item not found error, or return NULL
}


std::vector<Room_Type> Room::getConnected() const {
  return Contained_Properties.Connections;
}

void Room::removeCharacter(NPC* reqNPC) {
  std::vector<NPC*>* npcs = this->getCharacters();
  npcs->erase(std::remove(npcs->begin(), npcs->end(), reqNPC), npcs->end());
}

Room_Properties Room::loadDetails(Room_Type Needed_Type) {
  std::string name_p = "";
  std::string desc_p = "";
  std::string ex_p = "";
  std::string lock_txt = "";
  std::vector<Room_Type> conn_p = {};

  switch (Needed_Type) {
  case RN_Closet_A: {
    name_p = "Dark_Closet";
    desc_p = "You awake in a small dark closet. \"What happened to the ship?\""
             "\nyou think to yourself. The last thing you can remember was\n"
             "sailing through an intense storm";
    conn_p = { RN_Bridge };
    ex_p = "The closet you woke up in. Its very small and dark";
  }
  break;

  case RN_Closet_B: {
    name_p = "Dusty_Closet";
    desc_p = "A medium sized closet cluttered with boots and expensive \n"
             "jackets. A small safe lies in the corner";
    conn_p = { RN_Captain };
    ex_p = "The Captains closet";
  }
  break;

  case RN_Bridge: {
    name_p = "Bridge";
    desc_p = "You arrive at the bridge of the ship. The crew has seemingly \n"
             "vanished. The storm must have really damaged the ship, as \n"
             "some of the windows have been smashed.";
    conn_p = { RN_Closet_A, RN_Corridor_A };
    ex_p = "The Bridge of the Ship. A great vantage point";
  }
  break;

  case RN_Mech_Storage: {
    name_p = "Storage_Room";
    desc_p = "You enter the mechanical storage room. It reeks of automotive \n"
             "oil and exhaust fumes. Spare parts and tools lay scattered \n"
             "across the floor.";
    conn_p = { RN_Corridor_A };
    ex_p = "The mechanical storage room. Thats where they keep all the parts\n"
           "and tools.";
  }
  break;

  case RN_Engine: {
    name_p = "Engine_Room";
    desc_p = "Opening the door to the engine room lets out a plume of smoke.\n"
             "This can't be how the engine normally works... something must\n"
             "be broken. Wandering deeper into all the machinery, you spot\n"
             "one of the ships crew...";
    conn_p = { RN_Corridor_A };
    ex_p = "The engine room. You're not sure if you've ever been in there...";
  }
  break;

  case RN_Corridor_A: {
    name_p = "Corridor_A";
    desc_p = "The first corridor of the ship contained most of its\n"
             "mechanical functions. There is a door on each side, and one at\n"
             "the end of the corridor. An audible hum can be heard from the\n"
             "rightmost door.";
    conn_p = { RN_Bridge, RN_Engine, RN_Mech_Storage, RN_Corridor_B };
    ex_p = "The first corridor. \"Thats where most of the mechanical stuff\n"
           "is\" you think to yourself.";
  }
  break;

  case RN_Corridor_B: {
    name_p = "Corridor_B";
    desc_p = "The second corridor is definitely illuminated better. There\n"
             "are doors on either side of the hallway, with another\n"
             "connection at the end. \"I think I've seen some of the more\n"
             "important crew members around here before...\"";
    conn_p = { RN_Corridor_A, RN_Empty_A, RN_Captain, RN_Corridor_C };
    ex_p = "The second corridor. \"Im pretty sure the mess hall was around\n"
           "here...\" you think to yourself.";
    lock_txt = "It appears to have no power.";
  }
  break;

  case RN_Corridor_C: {
    name_p = "Corridor_C";
    desc_p = "The third corridor seems a lot more ominous than before. There\n"
             "are doors on either side of the hallway, with another\n"
             "connection at the end. \"Im pretty sure the mess hall was\n"
             "around here...\" you think to yourself.";
    conn_p = { RN_Corridor_B, RN_Lunch, RN_Empty_B, RN_Cargo };
    ex_p = "The third corridor. \"Im pretty sure the mess hall was around\n"
           "there...\" you think to yourself.";
  }
  break;

  case RN_Captain: {
    name_p = "Captains_Room";
    desc_p = "A plush room with polished hardwood flooring. \"The captain\n"
             "was really living it up out here...\" you think with a hint of\n"
             "jealousy. You suddenly hear some movement from one of the\n"
             "attached rooms. A pirate then reveals himself It doesn't look\n"
             "like he's seen you yet. You begin to wonder if you can take\n"
             "him down...";
    conn_p = { RN_Corridor_B, RN_Closet_B };
    ex_p = "The captains quarters. You never were fond of the guy...";
  }
  break;

  case RN_Lunch: {
    name_p = "Lunch_Room";
    desc_p = "A room lined with steel panels with a large wooden table\n"
             "centering the room. \"There were some good memories made in\n"
             "here\" you think to yourself. Those times seem to have come\n"
             "and gone. Amongst the silverware scattered across the room,\n"
             "there appears to be a note left on the table...";
    conn_p = { RN_Corridor_C };
    ex_p = "The door to the mess hall. Its always open, and uncomfortably\n"
           "narrow for the amount of people it serviced.";
  }
  break;

  case RN_Empty_A: {
    name_p = "Empty_Room";
    desc_p = "A small square room, several cardboard boxes sit in a dusty\n"
             "corner. \"Man... my life would be made a lot easier right now\n"
             "if there happened to be some items in there\" you think.";
    conn_p = { RN_Corridor_B };
    ex_p = "An unused room. \"I don't think that room was used very often...\n"
           "but would it hurt to check it out?\"...";
  }
  break;

  case RN_Empty_B: {
    name_p = "Empty_Room 2";
    desc_p = "A small square room, several cardboard boxes sit in a dusty\n"
             "corner. \"This looks eerily similar to the last empty\" you\n"
             "think to yourself.";
    conn_p = { RN_Corridor_C };
    ex_p = "Another unused room. \"I don't think that room was used very\n"
           "often but would it hurt to check it out?\"...";
  }
  break;

  case RN_Cargo: {
    name_p = "Cargo_Room";
    desc_p = "You enter the Cargo Hold of the ship. For some unexplainable\n"
             "reason, you begin to hear some ominous music in your head. You\n"
             "never were sure what was in here, but were told that it was\n"
             "some very important cargo. After wandering a little further,\n"
             "you come to a sudden realization that someone else is in here!\n"
             "The pirate leader! He hasn't seen you yet, but defeating him\n"
             "might make this scary music go away...";
    conn_p = { RN_Corridor_C };
    ex_p = "A large door that leads to the Cargo Hold.";
    lock_txt = "It appears to be locked up tight.";
  }
  break;
  }
  return Room_Properties(name_p, Needed_Type, desc_p, conn_p, ex_p, lock_txt);
}

// For when loading fails, defines boilerplate room
void Room::New_Data_Creation(Room_Type Needed_Type) {
  if (items == nullptr)
    return;

  switch (Needed_Type) {
  case RN_Mech_Storage: {
    Item* New_Item = new Item(I_Spare_Part);
    items->addItem(New_Item);
  }
  break;

  case RN_Empty_A: {
    Item* New_Item = new Item(I_Hand_Warmer);
    items->addItem(New_Item);
  }
  break;

  case RN_Empty_B: {
    Item* New_Item = new Item(I_Coffee_Mug);
    items->addItem(New_Item);
  }
  break;

  case RN_Lunch: {
    Item* New_Item = new Item(I_Safe_Code);
    items->addItem(New_Item);
  }
  break;
  }
}

void Room::NPC_Creation(Room_Type Needed_Type) {
  switch (Needed_Type) {
  case RN_Closet_B: {
    NPC* New_NPC = new NPC(C_Safe, false, Room_Flag);
    characters->emplace_back(New_NPC);
  }
  break;

  case RN_Captain: {
    // if (!Room_Flag) {
    NPC* New_NPC = new NPC(C_Pirate, false, Room_Flag);
    characters->emplace_back(New_NPC);
    // }
  }
  break;

  case RN_Engine: {
    NPC* New_NPC = new NPC(C_Crew_Member, false, Room_Flag);
    characters->emplace_back(New_NPC);
  }
  break;

  case RN_Cargo: {
    if (!Room_Flag) {
      NPC* New_NPC = new NPC(C_Pirate_Leader, false, Room_Flag);
      characters->emplace_back(New_NPC);
    }
  }
  break;
  }
  return;
}

bool Room::checkCondition() {
  switch (Contained_Properties.Room_Typing) {
  case RN_Corridor_B:
  case RN_Cargo: {
    Lock_Flag = !Room_Flag;
  }
  break;
  }

  return Room_Flag;
}

void Room::setCondition(bool New_Condition) {
  Room_Flag = New_Condition;
  return;
}

Room_Properties Room::Obtain_Room_Properties(Room_Type Needed_Room) {
  return loadDetails(Needed_Room);
}

std::string Room::listItems() {
  return items->listInventory();
}

std::string Room::listNPC() {
  std::string Str_List = "";
  std::size_t Content_Size = characters->size();

  for (std::size_t ii = 0; ii < Content_Size; ++ii) {
    Str_List.append((*characters)[ii]->getName());
    if (ii != (Content_Size - 1U))
      Str_List = Str_List + ", ";
  }
  return Str_List;
}

void Room::Save_Room(std::ofstream& Output_File) {
  size_t Needed_items = getInventory()->getContents()->size();
  Output_File << static_cast<int>(getType()) << " ";
  Output_File << Room_Flag << " ";
  Output_File << Needed_items << " ";
  if (Needed_items > 0 && getInventory() != nullptr)
    getInventory()->Save_Inventory(Output_File);

  return;
}

void Room::Load_Room(std::ifstream& Input_File) {
  size_t Needed_items;
  int Needed_Room_Type;

  Input_File >> Needed_Room_Type;
  Input_File >> Room_Flag;
  Input_File >> Needed_items;

  for (size_t ii = 0; ii < Needed_items; ++ii) {
    int Needed_Item_Type;
    Input_File >> Needed_Item_Type;
    getInventory()->addItem(new Item(static_cast<ItemType>(Needed_Item_Type)));
  }

  Contained_Properties = loadDetails(static_cast<Room_Type>(Needed_Room_Type));
  checkCondition();
  NPC_Creation(static_cast<Room_Type>(Needed_Room_Type));

  return;
}
