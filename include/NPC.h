/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#ifndef INCLUDE_NPC_H_
#define INCLUDE_NPC_H_

/**
* An abstract representation of an Non Playable Character
*/

#include <string>
#include "./person.h"

/**
* An enum to distinguish between a friendly NPC and an enemy NPC
*/
enum Character_Type { C_NULL, C_Crew_Member, C_Pirate, C_Pirate_Leader, C_Safe};

/**
* Sruct that contains all properties of a character
* Used to initialize characters
*/
struct Character_Properties {
  std::string Friendly_Name;
  Character_Type Character_Typing;
  std::string Description;
  std::string Interact_Text;

  Character_Properties() {}
  Character_Properties(const std::string &CN, Character_Type CT,
                       const std::string &Desc,
                       const std::string &EX) :
    Friendly_Name(CN), Character_Typing(CT), Description(Desc),
    Interact_Text(EX) {}
};

class NPC : public Person {
 public:
  /**
  * Default constructor
  */
  NPC(Character_Type Char_Name, bool From_Load, bool Completion_Flag);

  /**
  * Default destructor
  */
  virtual ~NPC();

  /**
  * Access the name of the NPC
  * @return The name of the NPC as a string
  */
  std::string getName() const;

  /**
  * Initialize a character_properties based on the given name
  * @param Needed_Type An Enum representation of the charater to load
  * @return A properties struct that contains all the neccessary details
  */
  static Character_Properties loadDetails(Character_Type Needed_Type);

  /**
  * Access the description of the NPC
  * @return The description of the NPC as a string
  */
  std::string getDescription() const;

  /**
  * Access the examine text of the NPC
  * @return The examine text of the NPC as a string
  */
  std::string getExamine_Txt() const;

  /**
  * Access the type of the NPC
  * @return The type of the NPC as an NPCType
  */
  Character_Type getType() const;

  /**
  * Calls interaction of the NPC
  */
  bool Interaction_Process(class GameController* GC_Ref) const;

 private:
  Character_Properties Contained_Properties;

  bool Complete_Flag = false;
};

#endif  // INCLUDE_NPC_H_
