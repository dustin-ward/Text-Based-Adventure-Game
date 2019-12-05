/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

/**
* Class that represents the player
* Handles all the health and temperature related functions
*/

#include <string>
#include "./person.h"
#include "./item.h"

enum DEATHType {TEMPERATURE, KILLED};

class Player : public Person {
 public:
  /**
  * Default constructor
  * @param newHealth The starting health of the player
  * @param newTemp The starting temperature of the player
  */
  Player(float newHealth, float newTemp, class GameController*);

  /**
  * Default destructor
  */
  virtual ~Player();

  /**
  * Constant to represent the max possible temperature
  */
  const float MAX_TEMP = 20.0;

  /**
  * Constant to represent the max possible health
  */
  const float MAX_HEALTH = 100.0;

  /**
  * Access the temperature of the player
  * @return The current temperature of the player
  */
  float getTemp() const;

  /**
  * Access the health of the player
  * @return The current health of the player
  */
  float getHealth() const;

  /**
  * Sets the current temperature of the player
  * Cannot be set above MAX_TEMP
  * @param newTemp The new temperature of the player
  */
  void setTemp(float newTemp);

  /**
  * Sets the current health if the player
  * Cannot be set above MAX_HEALTH
  * @param newHealth The new health of the player
  */
  void setHealth(float newHealth);

  /**
  * Checks the temperature of the player to see if they need to die
  */
  void tempCheck();

  /**
  * Checks the health of the player to see if they need to die
  */
  void healthCheck();

  /**
  * Uses a consumable item related to healing or warming
  * @param item A pointer to the item to be used
  */
  bool useItem(Item* item, class Room* Room_Ref);

  /**
  * Kill the player
  * @param dType How the player was killed
  */
  void killPlayer(DEATHType dType);

  bool Death_Flag = false;

  class GameController* Controller_Ref = nullptr;

 private:
  float temp;

  float health = MAX_HEALTH;
};

#endif  // INCLUDE_PLAYER_H_
