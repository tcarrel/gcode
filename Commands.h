#ifndef COMMANDS_H
#define COMMANDS_H

#include<cmath>
#include<iostream>

using std::abs;
using std::cout;

#include"position.h"
#include"Aux_Data.h"
#include"motor.h"

const char BEEP = 7;

class Command
{
  public:
    Command( void );

    virtual void execute( Position& ) = 0;
  protected: 
};

class Linear_move_command : public Command
{
  public:
    Linear_move_command( Position&, int );

    /*virtual*/ void execute( Position& );
  protected:
    Position end_;
    int plane_;
};
#endif
