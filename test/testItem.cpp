/*
* Copyright 2019 Dustin Ward <dustin.ward@uleth.ca>
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include <gtest/gtest.h>
#include "../include/item.h"


TEST(testItem, sparePartTest) {
  Item* i = new Item(I_Spare_Part);

  EXPECT_EQ("Spare Engine Part", i->getId());
  EXPECT_EQ("A loose part for a generator, could be useful.",
            i->getDescription());
  EXPECT_EQ(I_Spare_Part, i->getType());
  EXPECT_EQ("You hand the part to the crew member, he inserts the part into\n"
            "the machine. Seconds later the power turns on!",
            i->getAct());

  delete i;
}

TEST(testItem, safeCodeTest) {
  Item* i = new Item(I_Safe_Code);

  EXPECT_EQ("Note", i->getId());
  EXPECT_EQ("A torn out piece of a notebook with 6 numbers on it.",
            i->getDescription());
  EXPECT_EQ(I_Safe_Code, i->getType());

  delete i;
}

TEST(testItem, cargoKeyTest) {
  Item* i = new Item(I_Cargo_Key);

  EXPECT_EQ("Cargo Hold Key", i->getId());
  EXPECT_EQ("A key to open the cargo bay!",
            i->getDescription());
  EXPECT_EQ(I_Cargo_Key, i->getType());

  delete i;
}

TEST(testItem, handWarmerTest) {
  Item* i = new Item(I_Hand_Warmer);

  EXPECT_EQ("Hand Warmer", i->getId());
  EXPECT_EQ("A small pack of heat to increase your temperature.\n"
            "Use this item to gain +10 temperature.",
            i->getDescription());
  EXPECT_EQ(I_Hand_Warmer, i->getType());

  delete i;
}

TEST(testItem, coffeeMugTest) {
  Item* i = new Item(I_Coffee_Mug);

  EXPECT_EQ("Coffee Mug", i->getId());
  EXPECT_EQ("A mug of some surprisingly warm coffee.\n"
            "Use this item to gain +5 temperature.",
            i->getDescription());
  EXPECT_EQ(I_Coffee_Mug, i->getType());

  delete i;
}

TEST(testItem, nullTest) {
  Item* i = new Item(I_NULL);

  EXPECT_EQ("Something went wrong", i->getId());
  EXPECT_EQ("Not sure how you did this.", i->getDescription());
  EXPECT_EQ(I_NULL, i->getType());

  delete i;
}
