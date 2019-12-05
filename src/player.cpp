/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include "../include/player.h"
#include <string>
#include <iostream>
#include "../include/person.h"
#include "../include/item.h"
#include "../include/room.h"
#include "../include/mathProblem.h"
#include "../include/gameController.h"

Player::Player(float newHealth, float newTemp, GameController* Controller) :
  health{ newHealth }, temp{ newTemp }, Controller_Ref{ Controller } {}

Player::~Player() {}

float Player::getTemp() const {
  return temp;
}

float Player::getHealth() const {
  return health;
}

void Player::setTemp(float newTemp) {
  if (newTemp > MAX_TEMP)
    temp = MAX_TEMP;
  else
    temp = newTemp;

  tempCheck();
}

void Player::setHealth(float newHealth) {
  if (newHealth > MAX_HEALTH)
    health = MAX_HEALTH;
  else
    health = newHealth;

  healthCheck();
}

void Player::tempCheck() {
  if (temp <= -40.0f)
    killPlayer(TEMPERATURE);
}

void Player::healthCheck() {
  if (health <= 0.0f)
    killPlayer(KILLED);
}

bool Player::useItem(Item* Used_Item, Room* Room_Ref) {
  switch (Used_Item->getType()) {
  case I_Hand_Warmer: {
    temp += 10.0f;
    return true;
  }
  break;
  case I_Coffee_Mug: {
    temp += 5.0f;
    return true;
  }
  break;
  case I_Spare_Part: {
    if (Room_Ref->getType() == RN_Engine && !Room_Ref->Room_Flag) {
      Room* New_R = Controller_Ref->FindorCreate_Room(RN_Corridor_B);
      New_R->setCondition(true);
      New_R->Lock_Flag = false;

      Room_Ref->setCondition(true);
      return true;
    }
  }
  break;
  case I_Cargo_Key: {
    if (Room_Ref->getType() == RN_Corridor_C && !Room_Ref->Room_Flag) {
      Room* New_R = Controller_Ref->FindorCreate_Room(RN_Cargo);
      New_R->setCondition(true);
      New_R->Lock_Flag = false;

      Room_Ref->setCondition(true);
      return true;
    }
  }
  break;
  case I_Safe_Code: {
    if (Room_Ref->getType() == RN_Closet_B && !Room_Ref->Room_Flag) {
      MathProblem MP;
      MP.generate();
      int Answer;
      std::cout << MP.output_Str() << "\n";
      std::cin >> Answer;

      if (MP.solve(Answer)) {
        Item* New_Item = new Item(I_Cargo_Key);
        Room_Ref->setCondition(true);
        Room_Ref->getInventory()->addItem(New_Item);
        return true;
      } else {
        std::cout << "Seems like it was the wrong code \n";
        return false;
      }
    }
  }
  break;
  }
  // Needs implementation
  return false;
}

// Needs implementation
void Player::killPlayer(DEATHType dType) {
  switch (dType) {
  case TEMPERATURE:
    break;
  case KILLED:
    break;
  }

  Death_Flag = true;
}
