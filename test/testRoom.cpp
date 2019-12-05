/*
* Copyright 2019 Dustin Ward <dustin.ward@uleth.ca>
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include <gtest/gtest.h>
#include <vector>
#include "../include/room.h"
#include "../include/inventory.h"
#include "../include/NPC.h"

TEST(testRoom, bridgeTest) {
  Room* room1 = new Room(RN_Bridge, false);

  EXPECT_EQ("Bridge", room1->getName());
  EXPECT_EQ("You arrive at the bridge of the ship. The crew has seemingly \n"
            "vanished. The storm must have really damaged the ship, as \n"
            "some of the windows have been smashed.",
            room1->getDescription());

  EXPECT_EQ(0, room1->getCharacters()->size());
  EXPECT_EQ(0, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, closetBTest) {
  Room* room1 = new Room(RN_Closet_B, false);

  EXPECT_EQ("Dusty_Closet", room1->getName());
  EXPECT_EQ("A medium sized closet cluttered with boots and expensive \n"
            "jackets. A small safe lies in the corner",
            room1->getDescription());

  EXPECT_EQ(1, room1->getCharacters()->size());
  EXPECT_EQ(0, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, mechStorageTest) {
  Room* room1 = new Room(RN_Mech_Storage, false);

  EXPECT_EQ("Storage_Room", room1->getName());
  EXPECT_EQ("You enter the mechanical storage room. It reeks of automotive \n"
            "oil and exhaust fumes. Spare parts and tools lay scattered \n"
            "across the floor.",
            room1->getDescription());

  EXPECT_EQ(0, room1->getCharacters()->size());
  EXPECT_EQ(1, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  EXPECT_EQ("Spare Engine Part", room1->listItems());

  delete room1;
}

TEST(testRoom, engineTest) {
  Room* room1 = new Room(RN_Engine, false);

  EXPECT_EQ("Engine_Room", room1->getName());
  EXPECT_EQ("Opening the door to the engine room lets out a plume of smoke.\n"
            "This can't be how the engine normally works... something must\n"
            "be broken. Wandering deeper into all the machinery, you spot\n"
            "one of the ships crew...",
            room1->getDescription());

  EXPECT_EQ(1, room1->getCharacters()->size());
  EXPECT_EQ(0, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, corridorATest) {
  Room* room1 = new Room(RN_Corridor_A, false);

  EXPECT_EQ("Corridor_A", room1->getName());
  EXPECT_EQ("The first corridor of the ship contained most of its\n"
            "mechanical functions. There is a door on each side, and one at\n"
            "the end of the corridor. An audible hum can be heard from the\n"
            "rightmost door.",
            room1->getDescription());

  EXPECT_EQ(0, room1->getCharacters()->size());
  EXPECT_EQ(0, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, corridorBTest) {
  Room* room1 = new Room(RN_Corridor_B, false);

  EXPECT_EQ("Corridor_B", room1->getName());
  EXPECT_EQ("The second corridor is definitely illuminated better. There\n"
            "are doors on either side of the hallway, with another\n"
            "connection at the end. \"I think I've seen some of the more\n"
            "important crew members around here before...\"",
            room1->getDescription());

  EXPECT_EQ(0, room1->getCharacters()->size());
  EXPECT_EQ(0, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, corridorCTest) {
  Room* room1 = new Room(RN_Corridor_C, false);

  EXPECT_EQ("Corridor_C", room1->getName());
  EXPECT_EQ("The third corridor seems a lot more ominous than before. There\n"
            "are doors on either side of the hallway, with another\n"
            "connection at the end. \"Im pretty sure the mess hall was\n"
            "around here...\" you think to yourself.",
            room1->getDescription());

  EXPECT_EQ(0, room1->getCharacters()->size());
  EXPECT_EQ(0, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, captainTest) {
  Room* room1 = new Room(RN_Captain, false);

  EXPECT_EQ("Captains_Room", room1->getName());
  EXPECT_EQ("A plush room with polished hardwood flooring. \"The captain\n"
            "was really living it up out here...\" you think with a hint of\n"
            "jealousy. You suddenly hear some movement from one of the\n"
            "attached rooms. A pirate then reveals himself It doesn't look\n"
            "like he's seen you yet. You begin to wonder if you can take\n"
            "him down...",
            room1->getDescription());

  EXPECT_EQ(1, room1->getCharacters()->size());
  EXPECT_EQ(0, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, lunchTest) {
  Room* room1 = new Room(RN_Lunch, false);

  EXPECT_EQ("Lunch_Room", room1->getName());
  EXPECT_EQ("A room lined with steel panels with a large wooden table\n"
            "centering the room. \"There were some good memories made in\n"
            "here\" you think to yourself. Those times seem to have come\n"
            "and gone. Amongst the silverware scattered across the room,\n"
            "there appears to be a note left on the table...",
            room1->getDescription());

  EXPECT_EQ(0, room1->getCharacters()->size());
  EXPECT_EQ(1, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, emptyATest) {
  Room* room1 = new Room(RN_Empty_A, false);

  EXPECT_EQ("Empty_Room", room1->getName());
  EXPECT_EQ("A small square room, several cardboard boxes sit in a dusty\n"
            "corner. \"Man... my life would be made a lot easier right now\n"
            "if there happened to be some items in there\" you think.",
            room1->getDescription());

  EXPECT_EQ(0, room1->getCharacters()->size());
  EXPECT_EQ(1, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, emptyBTest) {
  Room* room1 = new Room(RN_Empty_B, false);

  EXPECT_EQ("Empty_Room 2", room1->getName());
  EXPECT_EQ("A small square room, several cardboard boxes sit in a dusty\n"
            "corner. \"This looks eerily similar to the last empty\" you\n"
            "think to yourself.",
            room1->getDescription());

  EXPECT_EQ(0, room1->getCharacters()->size());
  EXPECT_EQ(1, room1->getInventory()->getContents()->size());

  EXPECT_FALSE(room1->checkCondition());

  delete room1;
}

TEST(testRoom, cargoTest) {
  Room* room1 = new Room(RN_Cargo, false);

  EXPECT_EQ("Cargo_Room", room1->getName());
  EXPECT_EQ("You enter the Cargo Hold of the ship. For some unexplainable\n"
            "reason, you begin to hear some ominous music in your head. You\n"
            "never were sure what was in here, but were told that it was\n"
            "some very important cargo. After wandering a little further,\n"
            "you come to a sudden realization that someone else is in here!\n"
            "The pirate leader! He hasn't seen you yet, but defeating him\n"
            "might make this scary music go away...",
            room1->getDescription());
  EXPECT_EQ("It appears to be locked up tight.", room1->getLockText());
  EXPECT_EQ("A large door that leads to the Cargo Hold.", room1->getExamine());
  EXPECT_EQ(RN_Cargo, room1->getType());

  EXPECT_EQ(C_Pirate_Leader,
            room1->getCharacter(C_Pirate_Leader)->getType());

  EXPECT_EQ(1, room1->getCharacters()->size());
  EXPECT_EQ(0, room1->getInventory()->getContents()->size());

  EXPECT_EQ("The Pirate Leader", room1->listNPC());

  // room1->removeCharacter(room1->getCharacter(C_Pirate_Leader));
  // EXPECT_EQ(nullptr, room1->getCharacter(C_Crew_Member));
  //
  // EXPECT_EQ(0, room1->getCharacters()->size());
  EXPECT_EQ(1, room1->getConnected().size());

  EXPECT_FALSE(room1->checkCondition());

  room1->setCondition(true);

  EXPECT_TRUE(room1->checkCondition());

  EXPECT_EQ(RN_Cargo, room1->Obtain_Room_Properties(RN_Cargo).Room_Typing);

  delete room1;
}
