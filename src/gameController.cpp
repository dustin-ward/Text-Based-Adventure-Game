/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
  @author Jared Sisco, <j.sisco@uleth.ca>
* @date 2019-11
*/

#include "../include/gameController.h"
#include <ctype.h>
#include <limits>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "../include/inventory.h"
#include "../include/item.h"
#include "../include/player.h"
#include "../include/room.h"

GameController::GameController(bool testing) {
  player_ref = new Player(100.0f, 20.0f, this);
  Player_Inventory = new Inventory();

  Game_Loop = !testing;

  Room* Initial_Room = new Room(RN_Closet_A, false);
  currentRoom = Initial_Room;
  roomList.push_back(Initial_Room);

  while (Game_Loop == true) {
    Game_Tick();
  }
  std::cout << "Credits: Jared Sisco, Dustin Ward" << "\n";
}

GameController::~GameController() {
  delete player_ref;
  delete Player_Inventory;

  Unload_Room_List();
}

void GameController::Unload_Room_List() {
  for (size_t ii = 0; ii < roomList.size(); ++ii) {
    if (roomList[ii] != nullptr)
      delete roomList[ii];
  }
  roomList.clear();

  return;
}

bool GameController::Game_Tick() {
  std::string Command_Str = "";
  std::string Content_Str = "";

  if (Input_Blocked)
    return true;
  if (First_Flag) {
    std::cout <<
              "███████╗███████╗ █████╗ ███████╗██╗ ██████╗██╗  ██╗\n";
    std::cout <<
              "██╔════╝██╔════╝██╔══██╗██╔════╝██║██╔════╝██║ ██╔╝\n";
    std::cout <<
              "███████╗█████╗  ███████║███████╗██║██║     █████╔╝\n";
    std::cout <<
              "╚════██║██╔══╝  ██╔══██║╚════██║██║██║     ██╔═██╗\n";
    std::cout <<
              "███████║███████╗██║  ██║███████║██║╚██████╗██║  ██╗\n";
    std::cout <<
              "╚══════╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝ ╚═════╝╚═╝  ╚═╝\n";
    std::cout << currentRoom->getDescription()<< "\n";
    std::cout << "\nEnter a command, type \"help menu\" for assistance : \n";
    First_Flag = false;
  }
  std::cin >> Command_Str >> Content_Str;

  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if (input(Command_Str, Content_Str) == false) {
    std::cout << "Invalid command, try typing it again. \n";
  }

  for (uint8_t t = 0; t < Line_Spacing; ++t)
    std::cout << "\n";

  float Player_Temp = player_ref->getTemp();
  player_ref->setTemp(Player_Temp- 1.0f);

  if (Player_Temp < 0.0f)
    std::cout << "You start to become cold. \n";
  else if (Player_Temp < -20.0f)
    std::cout << "You are very cold, find warmth soon! \n";

  if (player_ref->Death_Flag) {
    std::cout << "You have been killed!. Exiting" << std::endl;
    Game_Loop = false;
    return false;
  }

  return true;
}

void GameController::loadGame() {
  return;
}

bool GameController::loadGame(const std::string &fileName) {
  std::ifstream f(fileName);

  if (!f.good())
    return false;

  Unload_Room_List();

  int Starting_Room_Value;
  f >> Starting_Room_Value;

  Load_Player(f);

  int Needed_Rooms;
  f >> Needed_Rooms;

  for (int ii = 0; ii < Needed_Rooms; ++ii) {
    Room* New_Room_V = new Room(RN_NULL, true);
    New_Room_V->Load_Room(f);

    if (Starting_Room_Value == New_Room_V->getType())
      currentRoom = New_Room_V;
    roomList.push_back(New_Room_V);
  }
  f.close();

  return true;
}

bool GameController::saveGame(const std::string &fileName) {
  std::ofstream f;
  f.open(fileName);

  f << static_cast<int>(currentRoom->getType()) << "\n";

  Save_Player(f);
  f << "\n";
  {
    std::cout << "You have been killed!. Exiting" << std::endl;
    Game_Loop = false;
    return false;
  }
  f << roomList.size();
  f << "\n";

  if (f.is_open()) {
    for (size_t ii = 0; ii < roomList.size(); ++ii) {
      roomList[ii]->Save_Room(f);
      if (ii != roomList.size() -1)
        f << "\n";
    }
    f.close();
    return true;
  }

  return false;
}

bool GameController::input(const std::string &command,
                           const std::string &content) {
  std::string Formatted_Command = Format_Input(command);
  std::string Formatted_Content = Format_Input(content);

  Command_Types Found_Command = Obtain_Command(Formatted_Command);

  return Decide_Content(Found_Command, Formatted_Content);

  return true;
}

Room* GameController::FindorCreate_Room(Room_Type Selected_Room) {
  Room* New_R = Search_Room(Selected_Room);
  if (New_R == nullptr) {
    New_R = new Room(Selected_Room, false);
    roomList.push_back(New_R);
  }
  return New_R;
}

bool GameController::Save_Player(std::ofstream& Output_File) {
  Output_File << player_ref->getTemp() << " ";

  size_t Needed_items = Player_Inventory->getContents()->size();
  Output_File << Needed_items << " ";
  if (Needed_items > 0 && Player_Inventory != nullptr)
    Player_Inventory->Save_Inventory(Output_File);

  return true;
}


void GameController::Load_Player(std::ifstream& Input_File) {
  float Player_T;
  Input_File >> Player_T;
  player_ref->setTemp(Player_T);

  size_t Needed_items;
  Input_File >> Needed_items;

  for (size_t ii = 0; ii < Needed_items; ++ii) {
    int Needed_Item_Type;
    Input_File >> Needed_Item_Type;
    Player_Inventory->addItem(new Item(
                                static_cast<ItemType>(Needed_Item_Type)));
  }
  return;
}

bool GameController::Decide_Content(Command_Types Main_Command_Type,
                                    const std::string &content) {
  bool Valid_Option = false;

  switch (Main_Command_Type) {
  case CT_List: {
    List_Types Needed_List;
    Needed_List = Obtain_List(content);

    switch (Needed_List) {
    case List_Doors: {
      if (currentRoom == nullptr)
        return false;
      std::vector<Room_Type> Connections = currentRoom->getConnected();
      std::size_t Connection_Am = Connections.size();

      std::cout << "Doors Available: ";
      for (std::size_t ii = 0; ii < Connection_Am; ++ii) {
        std::cout << Room::loadDetails(Connections[ii]).Friendly_Name;
        if (ii != (Connection_Am - 1))
          std::cout << ", ";
      }
      std::cout << "\n";
    }
    break;
    case List_NULL: {
      return false;
    }
    break;
    case List_Inventory: {
      if (player_ref == nullptr || Player_Inventory == nullptr)
        return false;
      std::string Item_Str = Player_Inventory->listInventory();
      std::cout << "You have: " << Item_Str << "\n";
    }
    break;
    case List_Items: {
      if (currentRoom == nullptr)
        return false;
      std::cout << "Room Contains: " << currentRoom->listItems() << "\n";
    }
    break;
    case List_NPC: {
      if (currentRoom == nullptr)
        return false;
      std::cout << "Room Contains: " << currentRoom->listNPC() << "\n";
    }
    }
    return true;
  }
  break;
  case CT_Goto: {
    Room_Type Selected_Room = Obtain_Doorway(content);
    bool Found_Option = false;

    std::vector<Room_Type> Connections = currentRoom->getConnected();
    std::size_t Connection_Am = Connections.size();
    for (std::size_t ii = 0; ii < Connection_Am; ++ii) {
      if (Selected_Room == Connections[ii]) {
        Found_Option = true;
      }
    }
    if (Found_Option) {
      Room* New_R = FindorCreate_Room(Selected_Room);
      if (!New_R->Lock_Flag) {
        currentRoom = New_R;
        std::cout << "\n" << currentRoom->getDescription() << "\n";
      } else {
        std::cout << "You try the door however..."
                  << New_R->getLockText() << "\n";
      }
      return true;
    }
  }
  break;

  case CT_Pickup: {
    // Failsafes
    if (Player_Inventory == nullptr)
      return false;
    if (currentRoom == nullptr)
      return false;
    Inventory* Item_Inv = currentRoom->getInventory();
    if (Item_Inv == nullptr)
      break;

    std::vector<Item*> Ground_Items = *(Item_Inv->getContents());
    std::size_t Ground_Items_Am = Ground_Items.size();

    for (std::size_t ii = 0; ii < Ground_Items_Am; ++ii) {
      ItemType Requested_Item = Obtain_Item(content);
      if (Requested_Item == I_NULL) {
        std::cout << "Item does not exist, try something else. \n";
        return false;
      }
      if (Ground_Items[ii]->getType() == Requested_Item) {
        std::cout << "Picked up " + Ground_Items[ii]->getId() << "\n";
        Item_Inv->TransferItem(ii, Player_Inventory);
        return true;
      }
    }
    std::cout << "No item named " << content << " was found on ground. \n";
    return true;
  }
  break;

  case CT_Save: {
    saveGame(File_Name);
    std::cout << "Game has been saved!" << "\n";
    return true;
  }
  break;

  case CT_Load: {
    Unload_Room_List();
    loadGame(File_Name);
    std::cout << "Game has been loaded!" << "\n";
    return true;
  }
  break;

  case CT_Examine: {
    ItemType Test_Item = Obtain_Item(content);
    if (Test_Item != I_NULL) {
      std::cout << Item::get_Properties(Test_Item).description << "\n";
      return true;
    }
    if (content == "room") {
      std::cout << currentRoom->getDescription()<< "\n";
      return true;
    }

    Room_Type Selected_Room = Obtain_Doorway(content);
    bool Found_Option = false;

    std::vector<Room_Type> Connections = currentRoom->getConnected();
    std::size_t Connection_Am = Connections.size();
    for (std::size_t ii = 0; ii < Connection_Am; ++ii) {
      if (Selected_Room == Connections[ii]) {
        Found_Option = true;
      }
    }
    if (Found_Option) {
      std::cout << Room::loadDetails(Selected_Room).Examine_Text << "\n";
      return true;
    }
    return false;
  }
  break;

  case CT_Clear: {
    for (uint8_t ii = 0; ii < 50; ++ii)
      std::cout << "\n";
    return true;
  }
  break;

  case CT_Use: {
    ItemType Test_Item = Obtain_Item(content);

    if (Test_Item == I_NULL) {
      return false;
    }
    Item* Found_Itm = Player_Inventory->getItem(Test_Item);

    if (Found_Itm != nullptr && player_ref != nullptr) {
      std::cout << "You used the " << Found_Itm->getId() << "\n";

      if (player_ref->useItem(Found_Itm, currentRoom)) {
        std::cout << Found_Itm->getAct() << "\n";
      } else {
        std::cout << "The item does not seem to have any use here." << "\n";
        return true;
      }
    } else {
      std::cout << "You searched but could not find a  " << content << ".\n";
    }
    return true;
  }
  break;

  case CT_Help: {
    std::cout << "ALL INPUT MUST BE LOWERCASE "
              "(There are no spaces in item names)\n" << std::endl;
    std::cout << "Use <item> - Use a specific item\n" << std::endl;
    std::cout << "List (rooms, items, npcs, doors) - List out all the "
              "available stuff\n" << std::endl;
    std::cout << "Examine <thing> - Get a closer look at something\n"
              << std::endl;
    std::cout << "Goto <room> - Go to a room\n" << std::endl;
    std::cout << "Pickup <item> - Add an item from the "
              "world to your inventory\n" << std::endl;
    std::cout << "Save <filename> - Saves a game\n" << std::endl;
    std::cout << "Load <filename - Loads a game\n" << std::endl;
    std::cout << "Clear screen - clears the screen\n" << std::endl;
    std::cout << "Quit game - quit the game\n" << std::endl;

    return true;
  }
  break;

  case CT_Quit: {
    std::cout << "Quitting Game" << std::endl;
    Game_Loop = false;
    return true;
  }
  break;

  case CT_Interact: {
    Character_Type Test_Char = Obtain_NPC(content);

    if (Test_Char == C_NULL) {
      return false;
    }
    NPC* Found_Char = currentRoom->getCharacter(Test_Char);

    if (Found_Char == nullptr) {
      return false;
    }
    std::cout << Found_Char->getExamine_Txt() << "\n";
    Found_Char->Interaction_Process(this);

    return true;
  }
  break;
  }

  return false;
}

Room* GameController::Search_Room(Room_Type Selected_Room) {
  for (size_t ii = 0; ii < roomList.size(); ++ii) {
    if (roomList[ii]->getType() == Selected_Room)
      return roomList[ii];
  }
  return nullptr;
}

Room_Type GameController::Obtain_Doorway(const std::string &Input_Str) {
  if (Input_Str == "dark_closet") {
    return RN_Closet_A;
  }

  if (Input_Str == "dusty_closet") {
    return RN_Closet_B;
  }

  if (Input_Str == "bridge" || Input_Str == "bridge_room") {
    return RN_Bridge;
  }

  if (Input_Str == "storage_room" || Input_Str == "storage") {
    return RN_Mech_Storage;
  }

  if (Input_Str == "engine_room" || Input_Str == "engine") {
    return RN_Engine;
  }

  if (Input_Str == "corridor_a" || Input_Str == "corridor_1") {
    return RN_Corridor_A;
  }

  if (Input_Str == "corridor_b" || Input_Str == "corridor_2") {
    return RN_Corridor_B;
  }

  if (Input_Str == "corridor_c" || Input_Str == "corridor_3") {
    return RN_Corridor_C;
  }

  if (Input_Str == "captains_room" || Input_Str == "captain's_room"
      || Input_Str == "captains" || Input_Str == "captain_room") {
    return RN_Captain;
  }

  if (Input_Str == "lunch_room" || Input_Str == "lunch") {
    return RN_Lunch;
  }

  if (Input_Str == "empty_room" || Input_Str == "empty") {
    return RN_Empty_A;
  }

  if (Input_Str == "empty_room_2" || Input_Str == "empty 2") {
    return RN_Empty_B;
  }

  if (Input_Str == "cargo_room" || Input_Str == "cargo") {
    return RN_Cargo;
  }

  return RN_NULL;
}



std::string GameController::Format_Input(std::string Input_Str) {
  std::string temp = Input_Str;
  std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
  return temp;
}

Command_Types GameController::Obtain_Command(const std::string &command) {
  if (command == "quit") {
    return CT_Quit;
  }

  if (command == "use") {
    return CT_Use;
  }

  if (command == "list") {
    return CT_List;
  }

  if (command == "examine") {
    return CT_Examine;
  }

  if (command == "goto" || command == "open" || command == "travel") {
    return CT_Goto;
  }

  if (command == "pickup") {
    return CT_Pickup;
  }

  if (command == "save") {
    return CT_Save;
  }

  if (command == "load") {
    return CT_Load;
  }

  if (command == "clear") {
    return CT_Clear;
  }

  if (command == "help" || command == "/help") {
    return CT_Help;
  }

  if (command == "interact") {
    return CT_Interact;
  }

  return CT_NULL;
}

List_Types GameController::Obtain_List(const std::string &content) {
  if (content == "doors" || content == "door" || content == "room"
      || content == "rooms") {
    return List_Doors;
  }

  if (content == "inv" || content == "inventory") {
    return List_Inventory;
  }

  if (content == "items" || content == "item") {
    return List_Items;
  }

  if (content == "npc" || content == "npcs" || content == "people"
      || content == "person" || content == "persons") {
    return List_NPC;
  }

  return List_NULL;
}

ItemType GameController::Obtain_Item(const std::string &content) {
  if (content == "spare_part" || content == "part") {
    return I_Spare_Part;
  }

  // If another key is added, remove alternative
  if (content == "cargo_key" || content == "key") {
    return I_Cargo_Key;
  }

  if (content == "note") {
    return I_Safe_Code;
  }

  return I_NULL;
}

Character_Type GameController::Obtain_NPC(const std::string &content) {
  if (content == "crew_member" || content == "crew" || content == "mechanic") {
    return C_Crew_Member;
  }

  if (content == "pirate" || content == "grunt" || content == "grunt_pirate"
      || content == "pirate_grunt") {
    return C_Pirate;
  }

  if (content == "pirate_leader" || content == "leader") {
    return C_Pirate_Leader;
  }
  if (content == "safe") {
    return C_Safe;
  }

  return C_NULL;
}
