/*
* Copyright 2019 Dustin Ward <dustin.ward@uleth.ca>
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include "../include/inventory.h"
#include "../include/item.h"


TEST(testInventory, constructorTest) {
  Inventory* i = new Inventory();

  EXPECT_EQ(0, i->getContents()->size());

  delete i;
}

TEST(testInventory, addRemoveGetItemTest) {
  Inventory* i = new Inventory();

  Item* item1 = new Item(I_Spare_Part);
  Item* item2 = new Item(I_Hand_Warmer);

  EXPECT_TRUE(i->addItem(item1));
  EXPECT_TRUE(i->addItem(item2));

  Item* ptr1 = i->getItem(0);
  Item* ptr2 = i->getItem(I_Hand_Warmer);

  EXPECT_EQ(item1, ptr1);
  EXPECT_EQ(item2, ptr2);
  EXPECT_EQ(I_Spare_Part, ptr1->getType());
  EXPECT_EQ(I_Hand_Warmer, ptr2->getType());
  EXPECT_EQ(2, i->getContents()->size());

  ptr1 = nullptr;
  ptr2 = nullptr;

  i->removeItem(0, true);
  EXPECT_EQ(nullptr, i->removeItem(3, false));

  EXPECT_EQ(1, i->getContents()->size());

  delete i;
}


TEST(testInventory, removeAllTest) {
  Inventory* i = new Inventory();

  Item* item1 = new Item(I_Safe_Code);
  Item* item2 = new Item(I_Spare_Part);

  i->addItem(item1);
  i->addItem(item2);

  i->removeAll();

  EXPECT_EQ(0, i->getContents()->size());

  delete i;
}

TEST(testInventory, listItemTest) {
  Inventory* i = new Inventory();

  Item* item1 = new Item(I_Safe_Code);
  Item* item2 = new Item(I_Spare_Part);

  i->addItem(item1);
  i->addItem(item2);

  EXPECT_EQ("Note, Spare Engine Part", i->listInventory());

  delete i;
}

TEST(testInventory, transferItemTest) {
  Inventory* i = new Inventory();
  Inventory* i2 = new Inventory();

  Item* item1 = new Item(I_Safe_Code);
  Item* item2 = new Item(I_Spare_Part);

  i->addItem(item1);
  i->addItem(item2);

  i->TransferItem(0, i2);
  EXPECT_EQ(1, i2->getContents()->size());

  i->TransferItem(0, i2);
  EXPECT_EQ(2, i2->getContents()->size());
  EXPECT_EQ(0, i->getContents()->size());

  EXPECT_FALSE(i->TransferItem(3, i2));

  delete i;
  delete i2;
}
