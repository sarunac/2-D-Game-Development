#include <iostream>
#include <string>
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"

Manager::~Manager() { 
  // Manager made it, so Manager needs to delete it
  delete orbFrame;
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  backRed( Gamedata::getInstance().getXmlInt("backRed") ),
  backGreen( Gamedata::getInstance().getXmlInt("backGreen") ),
  backBlue( Gamedata::getInstance().getXmlInt("backBlue") ),
  orbFrame( new Frame("greenorb") ),
  orb("greenorb", orbFrame)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);
}

void Manager::drawBackground() const {
  SDL_FillRect( screen, NULL, 
    SDL_MapRGB(screen->format, backRed, backGreen, backBlue) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

void Manager::draw() const {
  drawBackground();
  orb.draw();
  SDL_Flip(screen);
}

void Manager::update() {
  ++clock;
  Uint32 ticks = clock.getElapsedTicks();
  orb.update(ticks);
}

void Manager::play() {
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  while ( not done ) {

    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
    }
    if(event.type == SDL_KEYDOWN) {
      if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
        done = true;
        break;
      }
      if (keystate[SDLK_p] && !keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
    }

    draw();
    update();
  }
}
