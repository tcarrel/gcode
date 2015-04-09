#ifndef POSITION_H
#define POSITION_H

#include"Aux_Data.h"
#include<iostream>

using std::ostream;

struct Pos
{
  long x;
  long y;
  long z;

  Pos( long _x, long _y, long _z ) :
    x(_x), y(_y), z(_z) {}
};

class Position
{
  public:
    //ctors
    Position();
    Position(long, long, long);

    // Set
    void set(long, long, long);
    /////////

    // Logical operators
    bool operator==( Position& );
    bool operator!=( Position& );
    /////////

    // Assignment operator.
    Position& operator=( Position& );
    /////////

    inline long& x( void ) { return current_.x; }
    inline long& y( void ) { return current_.y; }
    inline long& z( void ) { return current_.z; }

    // Increment and decrement.
    inline void inc_x( void ) { ++current_.x; }
    inline void dec_x( void ) { --current_.x; }

    inline void inc_y( void ) { ++current_.y; }
    inline void dec_y( void ) { --current_.y; }

    inline void inc_z( void ) { ++current_.z; }
    inline void dec_z( void ) { --current_.z; }
    /////////
    
    friend ostream& operator<< ( ostream&, Position& );
  private:

    Pos current_;
};
#endif
