#include <iostream>
#include <string>
#include <queue>
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"

Manager::~Manager() { 
  // Manager made it, so Manager needs to delete it
  delete boomFrame;
  delete pirateFrame; 
  delete orbFrame;
 
  delete backFrame;
 }

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  backFrame( new Frame("backboard") ),
  back("backboard", backFrame),
  orbFrame( new Frame("greenorb") ),
  pirateFrame(new Frame ( "pirateorb")),
  boomFrame(new Frame ( "boomorb")),
  orbs(){
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  makeOrbs();
  atexit(SDL_Quit);
}

void Manager::makeOrbs()
{
 unsigned int n = Gamedata::getInstance().getXmlInt("numberOfOrbs");
 for (unsigned int i = 0; i <n; ++i)
 {
  orbs.push_back( Sprite("greenorb",orbFrame));
  orbs.push_back( Sprite("pirateorb",pirateFrame));
  orbs.push_back( Sprite("boomorb",boomFrame));
 }
}

void Manager::draw() const {
  back.draw();
  for (unsigned int i = 0; i < orbs.size(); ++i)
  { 
    orbs[i].draw();
  }
 int numOfOrbs = orbs.size();

 io.printMessageCenteredAt("My First Animation", 30) ;  
 io.printMessageCenteredAt("Hold F to fire many Boomerangs! " , 50);
 io.printMessageValueAt("Number of orbs", numOfOrbs,200,  80) ; 
 io.printMessageValueAt("Total fps", clock.getFps(),500,  60) ; 
 //io.printMessageValueAt("avgfps", averageFps,200,  60) ; 
 

}

void Manager::update() {
  ++clock;
  Uint32 ticks = clock.getElapsedTicks();
  for (unsigned int i = 0; i < orbs.size(); ++i)
  { 
    orbs[i].update(ticks);
  }
}


void Manager::play() {
  SDL_Event event;

  unsigned averageFps = 0;
  unsigned max_size = 100;
  unsigned sum =0;
  
  std::queue<int> myQueue;
 
  bool done = false;
  bool keyCatch = false;

  unsigned int fpsCaps = Gamedata::getInstance().getXmlInt("fpsCaps");
  while ( not done ) {
    unsigned start_time = clock.getSeconds(); 
    unsigned fps = clock.getFps();

    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
    }
    if(event.type == SDL_KEYDOWN) 
    {
      if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
        done = true;
        break;
      }
      
      else if (keystate[SDLK_p] && !keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
      
      else if (keystate[SDLK_f])
	{
	  orbs.push_back( Sprite("boomorb",boomFrame));
	}       
    }

  draw();
  if ( clock.getSeconds() > 0)
  { 
   myQueue.push (fps);
   if (myQueue.size() > max_size )
   {
	sum -=myQueue.front();
	myQueue.pop();
   }
   sum+=fps;
   averageFps = sum / myQueue.size();
 } 

 io.printMessageValueAt("avgfps",averageFps ,200,  60) ;
 
 SDL_Flip(screen);
 update();
  
  
   
 unsigned end_time = clock.getSeconds();  		
  if ((start_time-end_time < 1000 /fpsCaps))
  {
	SDL_Delay( ( 1000 / fpsCaps ) - (start_time-end_time));
  }
			
  }
}
