#ifndef INTERPRETER_H
#define INTERPRETER_H

#include<fstream>
#include<iostream>
#include<cctype>
#include<vector>

using std::ifstream;
using std::vector;
using std::iscntrl;
using std::isspace;

#include"setup.h"
#include"position.h"
#include"Commands.h"
#include"Aux_Data.h"
#include"motor.h"

class Interpreter
{
  public:
    Interpreter( ifstream&, Setup );
   ~Interpreter( void );

    bool load();
    void go();

  private:
    ifstream& in_;

    Setup* config_;
    
    Position pos_curr_;

    int plane_;
    int speed_;

    vector<Command*> commands_;

    void line_comment( void );
    void block_comment( void );
    void ignore_spaces( void );
    bool iscoord( char );

    bool g_code( void );
    bool m_code( void );
};
#endif
