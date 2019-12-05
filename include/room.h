/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
  @author Jared Sisco, <j.sisco@uleth.ca>
* @date 2019-11
*/

#ifndef INCLUDE_ROOM_H_
#define INCLUDE_ROOM_H_

/**
* A class used to implement all rooms
*/

#include <vector>
#include <string>
#include "./NPC.h"

/**
* An enum to identify each room
*/
enum Room_Type { RN_NULL, RN_Closet_A, RN_Closet_B, RN_Bridge, RN_Mech_Storage,
                 RN_Engine, RN_Corridor_A, RN_Corridor_B, RN_Corridor_C,
                 RN_Captain, RN_Lunch, RN_Empty_A, RN_Empty_B, RN_Cargo
               };

/**
* A struct that is used to initialize the room
*/
struct Room_Properties {
  std::string Friendly_Name;
  Room_Type Room_Typing;
  std::string Description;
  std::string Examine_Text;
  std::string Locked_Text;
  std::vector<Room_Type> Connections = {};

  Room_Properties() {}
  Room_Properties(const std::string &RN, Room_Type RT, const std::string &Desc,
                  const std::vector<Room_Type> &Conn, const std::string &EX,
                  const std::string &LTXT) :
    Friendly_Name(RN), Room_Typing(RT), Description(Desc),
    Connections(Conn), Examine_Text(EX), Locked_Text(LTXT) {}
};

class Room {
 public:
  /**
  * Default Constructor
  * @param Room_N A completed Room_Type that loads all values
  */
  Room(Room_Type Room_N,  bool From_Load);

  /**
  * Default destructor
  */
  virtual ~Room();

  /**
  * Access the name of the room
  * @return The name of the room as a string
  */
  std::string getName() const;

  /**
  * Access the description of the room
  * @return The description of the room as a string
  */
  std::string getDescription() const;

  /**
  * Access the exanination text of the room
  * @return The exanination text of the room as a string
  */
  std::string getExamine() const;

  /**
  * Access the locked message of the room
  * @return The locked message of the room as a string
  */
  std::string getLockText() const;

  /**
  * Access the items that are contained in the room
  * @return A pointer to an inventory that contains all of the room's items
  */
  class Inventory* getInventory() const;

  /**
  * Access the NPC's that exist in the room
  * @return A pointer to a vector of NPC pointers
  */
  std::vector<NPC*>* getCharacters() const;

  /**
  * Access the type of the room
  * @return The type of the room
  */
  Room_Type getType() const;

  /**
  * Access the first NPC of type in a room
  * @param reqName The name of the NPC to be returned
  * @return A pointer to the requested NPC
  */
  NPC* getCharacter(Character_Type reqName) const;

  /**
  * Access a specific NPC index in a room
  * @param reqName The room slot num of the NPC to be returned
  * @return A pointer to the requested NPC
  */
  NPC* getCharacter(int Slot_Num) const;

  /**
  * Access the connected rooms
  * @return A vector of connected rooms
  */
  std::vector<Room_Type> getConnected() const;

  /**
  * Remove an NPC from a room
  * @param reqNPC A pointer to the NPC to be removed
  */
  void removeCharacter(NPC* reqNPC);

  /**
  * Access the Room_Properties of the room
  * @param Needed_Room What room data to load
  * @return The completed Room_Properties
  */
  Room_Properties Obtain_Room_Properties(Room_Type Needed_Room);

  /**
  * Obtain a list of all the available items in the room
  * @return A list of all available items as a string
  */
  std::string listItems();

  /**
  * Obtain a list of all the available npcs in the room
  * @return A list of all available npcs as a string
  */
  std::string listNPC();

  /**
  * Loading NPC data from file
  * @return A bool value based on if the load was successful
  */
  bool load(const std::string &fileName);

  /**
  * Loading specific details into the class
  * @param Needed_Type The details to be added
  * @return Completed Room_Properties
  */
  static Room_Properties loadDetails(Room_Type Needed_Type);

  /**
  * Filling rooms with their required items
  * @param Needed_Type Room identifier
  */
  void New_Data_Creation(Room_Type Needed_Type);

  /**
  * Fill rooms with their required characters
  * @param Needed_Type Room identifier
  */
  void NPC_Creation(Room_Type Needed_Type);

  /**
  * Check if the condition of the room is complete
  * @return bool based on completion of the room
  */
  bool checkCondition();

  /**
  * Flips the room codition upon completion of a task
  * @param New_Condition A value to set the room to
  */
  void setCondition(bool New_Condition);

  /**
  * Save room status to file
  * @param Output_File Filename to write to
  */
  void Save_Room(std::ofstream& Output_File);

  /**
  * Load room status from file
  * @param Input_File Filename to read from
  */
  void Load_Room(std::ifstream& Input_File);

  bool Room_Flag = false;
  bool Lock_Flag = false;

 protected:
  Room_Properties Contained_Properties;

  class Inventory* items;

  std::vector<NPC*>* characters;
};

#endif  // INCLUDE_ROOM_H_
