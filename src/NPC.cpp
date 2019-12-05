/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include "../include/NPC.h"
#include <iostream>
#include <string>
#include "../include/item.h"
#include "../include/gameController.h"
#include "../include/mathProblem.h"
#include "../include/player.h"

NPC::NPC(Character_Type Char_Name, bool From_Load, bool Completion_Flag) :
  Contained_Properties{loadDetails(Char_Name)},
  Complete_Flag(Completion_Flag) {}

NPC::~NPC() {}

std::string NPC::getName() const {
  return Contained_Properties.Friendly_Name;
}

std::string NPC::getDescription() const {
  return Contained_Properties.Description;
}

Character_Type NPC::getType() const {
  return Contained_Properties.Character_Typing;
}

std::string NPC::getExamine_Txt() const {
  return Contained_Properties.Interact_Text;
}

Character_Properties NPC::loadDetails(Character_Type Needed_Type) {
  std::string name_p = "";
  std::string desc_p = "";
  std::string itxt_p = "";

  switch (Needed_Type) {
  case C_Crew_Member: {
    name_p = "Mechanic";
    desc_p = "One of the ships crew. He appears to be a mechanic.";
    itxt_p = "\"You there! Get over here! We gotta get this engine back up\n"
             "and running! It will turn the power back on for the whole ship\n"
             "I need an extra part to fix this thing up, do you think you\n"
             "can find it for me?\"";
  }
  break;
  case C_Pirate: {
    name_p = "Pirate Grunt";
    desc_p = "A small and scrawny-looking pirate. \"He can't be very high\n"
             "ranking, hes probably trying to see what he can snag from the\n"
             "captain!\"";
    itxt_p = "ARRRR! Who are ye? The only way you will get past me is by\n"
             "solving 3 math problems, my greatest weakness!\n"
             "(Yes... seriously)";
  }
  break;
  case C_Pirate_Leader: {
    name_p = "The Pirate Leader";
    desc_p = "This pirate is a lot bigger and more intimidating than the\n"
             "last one. \"He's definitely the head honcho around here...\"\n"
             "you think to yourself. \"I feel like I will achieve some kind\n"
             "of victory if I take him down...\"";
    itxt_p = "ARRRR! Who are ye? Im clearly not just the same pirate as last\n"
             "time, im the pirate LEADER! I've boarded yer ship, and im\n"
             "stealing all yer cargo, ARRR! The only way you could stop me\n"
             "is by giving me the answer to 5 difficult math problems.\n"
             "Beware, for I am stronger than yer last opponent. Incorrectly\n"
             "solving just 1 problem will instantly kill you!";
  }
  break;
  case C_Safe: {
    name_p = "A sturdy safe";
    desc_p = "This safe must contain something really valuable, or it could\n"
             "contain an item vital to the progression of the game. Either\n"
             "way, it needs a 6 digit code to unlock it";
    itxt_p = "A rusty safe with a code dial on the front, this could contain\n"
             "anything";
  }
  break;


  case C_NULL: {
    name_p = "Nothing";
    desc_p = "Actually nothing, why are you reading this?";
    itxt_p = "Seriously nothing, move on.";
  }
  break;
  }

  return Character_Properties(name_p, Needed_Type, desc_p, itxt_p);
}

bool NPC::Interaction_Process(GameController* GC_Ref) const {
  Room* New_R = nullptr;

  switch (Contained_Properties.Character_Typing) {
  case C_Pirate: {
    uint8_t Math_Questions = 3;
    float Damage_Value = 20.0f;
    MathProblem MP;

    for (uint8_t ii = 0; ii < Math_Questions; ++ii) {
      MP.generate();
      int Answer;
      std::cout << MP.output_Str() << "\n";
      std::cin >> Answer;

      if (MP.solve(Answer)) {
        std::cout << "You have correctly answered his question. \n";
      } else {
        std::cout << "He laughs as you incorrectly answer the question, "
                     "and proceeds to shank you with his knife! \n";
        float Current_HP = GC_Ref->player_ref->getHealth();
        GC_Ref->player_ref->setHealth(Current_HP - Damage_Value);
        ii = 0;

        if (GC_Ref->player_ref->Death_Flag = true)
          return false;
      }
    }

    return true;
  }
  break;
  case C_Pirate_Leader: {
    uint8_t Math_Questions = 5;
    float Damage_Value = 100.0f;
    MathProblem MP;

    for (uint8_t ii = 0; ii < Math_Questions; ++ii) {
      MP.generate();
      int Answer;
      std::cout << MP.output_Str() << "\n";
      std::cin >> Answer;

      if (MP.solve(Answer)) {
        std::cout << "You have correctly answered his question. \n";
      } else {
        std::cout << "He laughs as you incorrectly answer the question, and "
                     "throws you off the ship! \n";
        GC_Ref->player_ref->setHealth(GC_Ref->player_ref->getHealth() -
                                      Damage_Value);
        ii = 0;

        if (GC_Ref->player_ref->Death_Flag = true)
          return false;
      }
    }

    std::cout << "Congrats you are the first person to complete the game. "
                 "Probably. \n";
    GC_Ref->Game_Loop = false;
  }
  break;
  case C_NULL: {
  } break;
  }

  return true;
}

