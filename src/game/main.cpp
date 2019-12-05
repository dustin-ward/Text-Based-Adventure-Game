#include <iostream>
#include "../../include/room.h"
#include "../../include/gameController.h"


int main() {
  GameController* g = new GameController(false);
  delete g;
  return 0;
}
