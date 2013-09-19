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
  void start() ;
private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;


  const Frame * const backFrame;
  Sprite back;

    
 
  void makeOrbs();
  
  //std::vector<Frame *> orbFrame;
  //void makeFrames();

  const Frame * const orbFrame; 
  const Frame * const pirateFrame;
  const Frame * const boomFrame;
 

   std::vector<Sprite> orbs;

  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);


};
