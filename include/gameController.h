/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
  @author Jared Sisco, <j.sisco@uleth.ca>
* @date 2019-11
*/

#ifndef INCLUDE_GAMECONTROLLER_H_
#define INCLUDE_GAMECONTROLLER_H_

/**
* The main Game controller that takes care of loading, saving,
room and player functions
*/

#include <string>
#include <fstream>
#include <vector>
#include "./room.h"

// ForwardD
class Player;
class Room;
class NPC;
class Inventory;

/**
* Enum that lists all possible commands
*/
enum Command_Types { CT_NULL, CT_Use, CT_List, CT_Examine, CT_Goto, CT_Pickup,
                     CT_Save, CT_Load, CT_Clear, CT_Help, CT_Quit, CT_Interact,
                     ECommand_Types_MAX
                   };

/**
* Enum that lists all possible operands
*/
enum List_Types { List_NULL, List_Doors, List_Inventory, List_Items,
                  List_NPC, EList_Types_MAX
                };

class GameController {
 public:
  /**
  * Default Constructor
  * Creates an instance of the game
  * @param testing To be used during testing. Disables the game loop
  */
  explicit GameController(bool testing);

  /**
  * Destructor
  */
  ~GameController();

  /**
  * Handles deletion of rooms
  */
  void Unload_Room_List();

  /**
  * Main game loop responsible for continuosly promting user for input
  * @return Used for ending the gameloop upon death of the player
  */
  bool Game_Tick();

  /**
  * Load if no input file is given
  */
  void loadGame();

  /**
  * Function to load the game from a previous save
  * @param fileName Filename to load from
  * @return Boolean on successful load
  */
  bool loadGame(const std::string &fileName);

  /**
  * Function to save the game to a specific file
  * @param fileName Filename to load from
  * @return Boolean on successful load
  */
  bool saveGame(const std::string &fileName);

  /**
  * Function that handles user input.
  * Determines the command and operand, then executes the proper instructions
  */
  bool input(const std::string &command, const std::string &content);

  /**
  * Search for a room, and if it has not been created, then make it. Otherwise
  return a pointer to the room
  * @param Selected_Room Room to search for
  * @return Pointer to the room
  */
  Room* FindorCreate_Room(Room_Type Selected_Room);

  /**
  * Function responsible for saving player related data
  * @param Output_File Filename to write to
  * @return Boolean on successful save
  */
  bool Save_Player(std::ofstream& Output_File);

  /**
  * Function responsible for loading player related data
  * @param Input_File Filename to read from
  */
  void Load_Player(std::ifstream& Input_File);

  Character_Type Obtain_NPC(const std::string &content);

  /**
  * Handles the execuction of commands
  * @param Main_Command_Type The type of command to execute
  * @param content The operand to use with the command
  * @return Boolean on successful execution
  */
  bool Decide_Content(Command_Types Main_Command_Type,
                      const std::string &content);

  /**
  * Find a specific room in the roomlist
  * @param Selected_Room The specific room to search for
  * @return A pointer the the requeted room
  */
  Room* Search_Room(Room_Type Selected_Room);

  /**
  * Get the correct doorway based on the players input
  * @param Input_Str User input
  * @return A corrected room identifier
  */
  Room_Type Obtain_Doorway(const std::string &Input_Str);

  /**
  * Formats the user input to be more program friendly
  * @param Input_Str User input
  * @return Formatted string
  */
  std::string Format_Input(std::string Input_Str);

  /**
  * Get the correct command based on the users input
  * @param command User input
  * @return A corrected command identifier
  */
  Command_Types Obtain_Command(const std::string &command);

  /**
  * Get the correct list based on user input
  * @param content User input
  * @return A corrected list identifier
  */
  List_Types Obtain_List(const std::string &content);

  /**
  * Get the correct item based on user input
  * @param content User input
  * @return A corrected item identifier
  */
  ItemType Obtain_Item(const std::string &content);

  Player* player_ref = nullptr;
  bool Game_Loop = true;

 private:
  Room* currentRoom;



  Inventory* Player_Inventory = nullptr;

  std::vector<Room*> roomList;

  std::string File_Name = "Savegame.txt";


  bool Input_Blocked = false;

  bool First_Flag = true;

  uint8_t Line_Spacing = 1U;
};

#endif  // INCLUDE_GAMECONTROLLER_H_
