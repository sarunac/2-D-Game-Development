#include "SDL/SDL_rotozoom.h"
#include "ioManager.h"
#include "frame.h"
#include "extractSurface.h"

// The next constructor s/ only be used when the Frames's surface
// starts at (0, 0) in the sprite sheet, and consumes the entire
// sprite sheet. For example, a Frame containing a background.
Frame::Frame( const std::string& name ) : 
  screen(IOManager::getInstance().getScreen()),
  width(Gamedata::getInstance().getXmlInt(name+"Width")), 
  height(Gamedata::getInstance().getXmlInt(name+"Height")),
  surface( IOManager::getInstance().
           loadAndSet(Gamedata::getInstance().getXmlStr(name+"File"), 
           Gamedata::getInstance().getXmlBool(name+"Transparency") ) )
{ }

// The next constructor gets all parameters from surf.
Frame::Frame( SDL_Surface* surf ) :
  screen(IOManager::getInstance().getScreen()),
  width(surf->w), 
  height(surf->h),
  surface(surf)
{}

// The next constructor s/ be used when the Frame's surface is
// found on only a part of sprite sheet, width and height is in XML:
Frame::Frame( SDL_Surface* surf, const std::string& name,
              Sint16 src_x, Sint16 src_y) :
  screen(IOManager::getInstance().getScreen()),
  width(Gamedata::getInstance().getXmlInt(name+"Width")), 
  height(Gamedata::getInstance().getXmlInt(name+"Height")),
  surface( ExtractSurface::getInstance().
    get(surf, width, height, src_x, src_y) 
  )
{ }

// The next constructor s/ be used when the Frame's surface is
// found on only a part of sprite sheet, width and height is passed:
Frame::Frame( SDL_Surface* surf, Sint16 src_x, Sint16 src_y, 
              Sint16 w, Sint16 h) :
  screen(IOManager::getInstance().getScreen()),
  width(w),
  height(h),
  surface( ExtractSurface::getInstance().
    get(surf, width, height, src_x, src_y) 
  )
{ }

Frame::Frame( const Frame& frame ) :
  screen(frame.screen),
  width(frame.width), height(frame.height),
  // Need a deep copy here:
  surface( 
    ExtractSurface::getInstance().get(frame.surface, width, height, 0, 0) 
  )
{ }

Frame& Frame::operator=(const Frame& rhs) {
  screen = rhs.screen;
  width = rhs.width;
  height = rhs.height;
  surface = rhs.surface;
  return *this;
}

void Frame::draw(Sint16 x, Sint16 y) const {
  SDL_Rect src = { 0, 0, width, height };    
  SDL_Rect dest = {x, y, width, height };
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const {
  SDL_Rect src = { sx, sy, width, height };    
  SDL_Rect dest = {dx, dy, width, height };
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 x, Sint16 y, double angle) const {
  SDL_Surface* tmp = rotozoomSurface(surface, angle, 1, 1);
  SDL_Rect src = { 0, 0, tmp->w, tmp->h };    
  SDL_Rect dest = {x, y, 0, 0 };
  SDL_BlitSurface(tmp, &src, screen, &dest);
  SDL_FreeSurface( tmp );
}
