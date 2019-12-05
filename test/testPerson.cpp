/*
* Copyright 2019 Dustin Ward <dustin.ward@uleth.ca>
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include <gtest/gtest.h>
#include "../include/person.h"
#include "../include/item.h"
#include "../include/inventory.h"
#include "../include/NPC.h"


TEST(testPerson, constructorTest) {
  NPC* npc = new NPC(C_Pirate, false, true);

  Inventory* pirateInv = npc->getInventory();

  EXPECT_EQ(0, pirateInv->getContents()->size());

  delete npc;
}

TEST(testPerson, giveItemTest) {
  NPC* npc = new NPC(C_Pirate, false, true);
  NPC* npc2 = new NPC(C_Pirate_Leader, false, true);

  Inventory* inv = npc->getInventory();
  Inventory* inv2 = npc2->getInventory();

  Item* i = new Item(I_Cargo_Key);
  inv->addItem(i);

  EXPECT_EQ(1, inv->getContents()->size());
  EXPECT_EQ("Cargo Hold Key", inv->getItem(0)->getId());

  npc->giveItem(0, npc2);

  EXPECT_EQ(0, inv->getContents()->size());
  EXPECT_EQ(1, inv2->getContents()->size());
  EXPECT_EQ("Cargo Hold Key", inv2->getItem(0)->getId());

  delete npc;
  delete npc2;
}

