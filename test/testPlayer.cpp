/*
* Copyright 2019 Dustin Ward <dustin.ward@uleth.ca>
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include <gtest/gtest.h>
#include "../include/player.h"
#include "../include/person.h"
#include "../include/item.h"
#include "../include/gameController.h"

TEST(testPlayer, constructorTest) {
  GameController* g = new GameController(true);
  Player* p = new Player(100.0, 10.0, g);
  Item* i = new Item(I_Hand_Warmer);
  Item* i2 = new Item(I_Coffee_Mug);

  EXPECT_EQ(100.0, p->getHealth());
  EXPECT_EQ(10.0, p->getTemp());

  p->useItem(i, nullptr);

  EXPECT_EQ(20.0, p->getTemp());

  p->useItem(i2, nullptr);

  EXPECT_EQ(25.0, p->getTemp());

  delete p;
  delete g;
  delete i;
  delete i2;
}

TEST(testPlayer, setTempTest) {
  GameController* g = new GameController(true);
  Player* p = new Player(100.0, 20.0, g);

  p->setTemp(p->getTemp()-5.0);

  EXPECT_EQ(15.0, p->getTemp());

  p->setTemp(21.0);

  EXPECT_EQ(20.0, p->getTemp());

  p->setTemp(-41.0);
  p->tempCheck();

  delete p;
  delete g;
}

TEST(testPlayer, setHealthTest) {
  GameController* g = new GameController(true);
  Player* p = new Player(100.0, 20.0, g);

  p->setHealth(p->getHealth()-10.0);

  EXPECT_EQ(90.0, p->getHealth());

  p->setHealth(101.0);

  EXPECT_EQ(100.0, p->getHealth());

  p->setHealth(0.0);
  p->healthCheck();

  delete p;
  delete g;
}
