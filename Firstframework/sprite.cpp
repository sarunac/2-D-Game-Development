#include <iostream>
#include <cmath>
#include <limits>

#include "sprite.h"
#include "gamedata.h"


// The next function is backing up one written by Sam Bryce
int randBetween(int low, int high) {
   return ((rand() % (high - low)) + low);
}

float getRand(int min, int max) {
  return min + (rand() / (std::numeric_limits<int>::max()+1.0f))*(max-min);
}

Sprite::Sprite(const std::string& name, const Frame* const frame) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"X"), 
                    Gamedata::getInstance().getXmlInt(name+"Y")), 
           Vector2f(
		(rand()%2?1:-1)*randBetween(100,200),
		(rand()%2?1:-1)*randBetween(100,200))

		),
  frame( frame ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight"))
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()), 
  frame(s.frame),  // shallow copy; Manager may reuse it
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight"))
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  frame = rhs.frame;  // shallow copy; Manager may reuse it
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void Sprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

void Sprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
