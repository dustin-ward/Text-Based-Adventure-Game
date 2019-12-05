/*
* Copyright 2019 Dustin Ward <dustin.ward@uleth.ca>
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include <gtest/gtest.h>
#include "../include/NPC.h"

TEST(testNPC, crewTest) {
  NPC* npc = new NPC(C_Crew_Member, false, true);

  EXPECT_EQ("Mechanic", npc->getName());
  EXPECT_EQ("One of the ships crew. He appears to be a mechanic.",
            npc->getDescription());
  EXPECT_EQ(C_Crew_Member, npc->getType());
  EXPECT_EQ("\"You there! Get over here! We gotta get this engine back up\n"
            "and running! It will turn the power back on for the whole ship\n"
            "I need an extra part to fix this thing up, do you think you\n"
            "can find it for me?\"",
            npc->getExamine_Txt());

  delete npc;
}

TEST(testNPC, pirateTest) {
  NPC* npc = new NPC(C_Pirate, false, true);

  EXPECT_EQ("Pirate Grunt", npc->getName());
  EXPECT_EQ("A small and scrawny-looking pirate. \"He can't be very high\n"
            "ranking, hes probably trying to see what he can snag from the\n"
            "captain!\"",
            npc->getDescription());
  EXPECT_EQ(C_Pirate, npc->getType());
  EXPECT_EQ("ARRRR! Who are ye? The only way you will get past me is by\n"
            "solving 3 math problems, my greatest weakness!\n"
            "(Yes... seriously)",
            npc->getExamine_Txt());

  delete npc;
}

TEST(testNPC, pirateLeaderTest) {
  NPC* npc = new NPC(C_Pirate_Leader, false, true);

  EXPECT_EQ("The Pirate Leader", npc->getName());
  EXPECT_EQ("This pirate is a lot bigger and more intimidating than the\n"
            "last one. \"He's definitely the head honcho around here...\"\n"
            "you think to yourself. \"I feel like I will achieve some kind\n"
            "of victory if I take him down...\"",
            npc->getDescription());
  EXPECT_EQ(C_Pirate_Leader, npc->getType());
  EXPECT_EQ("ARRRR! Who are ye? Im clearly not just the same pirate as last\n"
            "time, im the pirate LEADER! I've boarded yer ship, and im\n"
            "stealing all yer cargo, ARRR! The only way you could stop me\n"
            "is by giving me the answer to 5 difficult math problems.\n"
            "Beware, for I am stronger than yer last opponent. Incorrectly\n"
            "solving just 1 problem will instantly kill you!",
            npc->getExamine_Txt());

  delete npc;
}

TEST(testNPC, safeTest) {
  NPC* npc = new NPC(C_Safe, false, true);

  EXPECT_EQ("A sturdy safe", npc->getName());
  EXPECT_EQ("This safe must contain something really valuable, or it could\n"
            "contain an item vital to the progression of the game. Either\n"
            "way, it needs a 6 digit code to unlock it",
            npc->getDescription());
  EXPECT_EQ(C_Safe, npc->getType());
  EXPECT_EQ("A rusty safe with a code dial on the front, this could contain\n"
            "anything",
            npc->getExamine_Txt());

  delete npc;
}
