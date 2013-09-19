#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "sprite.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  int backRed;
  int backGreen;
  int backBlue;

  const Frame * const orbFrame;
  Sprite orb;

  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void drawBackground() const;
};
