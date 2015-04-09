#include"position.h"

#include<cmath>

using std::sqrt;

Position::Position( void ) : current_( 0, 0, 0 ) {}
Position::Position( long _x, long _y, long _z ) : current_( _x, _y, _z ) {}

void Position::set( long _x, long _y, long _z )
{ current_.x = _x; current_.y = _y; current_.z = _z; }

///////////////////////////////////////////////////////////////////////////////
//  
//  Boolean operators == and !=.
//
//  <,>,<=, and >= are meaningless in this context, so they are
//  not inplemented.
//
///////////////////////////////////////////////////////////////////////////////
bool Position::operator==( Position& rhs )
{
  return
    (this->current_.x == rhs.current_.x) &&
    (this->current_.y == rhs.current_.y) &&
    (this->current_.z == rhs.current_.z);
}
bool Position::operator!=( Position& rhs )
{ return !(*this == rhs); }

///////////////////////////////////////////////////////////////////////////////
//
//  Assignment operator
//
///////////////////////////////////////////////////////////////////////////////
Position& Position::operator=( Position& rhs )
{
  if( *this == rhs )
    return *this;

  current_.x = rhs.x();
  current_.y = rhs.y();
  current_.z = rhs.z();
  return *this;
}

ostream& operator<< ( ostream& S, Position& rhs )
{
  return (S << 
      "X:" << rhs.current_.x << 
      " Y:" << rhs.current_.y << 
      " Z:" << rhs.current_.z);
}
