#include"interpreter.h"

Interpreter::Interpreter( ifstream& file, Setup s ) :
  in_(file),
  config_(&s),
  plane_(XZ_PLANE),
  speed_(0)
{}                     

Interpreter::~Interpreter( void )
{
  if( in_.is_open() )
    in_.close();
}

bool Interpreter::load( void )
{
  bool is_error = false;

  char ch = 0;
  double decimal = 0.0;
  int integer = 0;

  in_ >> ch;

  while( !in_.eof() && !is_error )
  {

    ignore_spaces();

    switch( ch )
    {
      case ';':
        line_comment();
        break;

      case '(':
        block_comment();
        break;

      case 'G':
      case 'g':
        is_error = g_code();
        break;

      case 'M':
      case 'm':
        is_error = m_code();
        break;

      case 'N':
      case 'n':
        //discard line numbers
        in_ >> integer;
        integer = 0;
        break;

      default:
        ;
    } 

    decimal = 0.0;
    integer = 0;
    ch = 0;
  }
  return true;
}

void Interpreter::go( void )
{
  cout << "\n" << pos_curr_ << endl;
  for( unsigned i = 0; i < commands_.size(); i++ )
  {
    commands_[i]->execute( pos_curr_ );
    cout << BEEP << pos_curr_ << endl;
  }
  cout << "\033[1m" << "OPERATION COMPLETE" << "\033[0m" << endl;
}

void Interpreter::line_comment( void )
{
  while( !iscntrl( in_.peek() ) )
    in_.ignore();

  in_.ignore();
}

void Interpreter::block_comment( void )
{
  while( in_.peek() != ')' )
    in_.ignore();

  in_.ignore( 2 );
}

void Interpreter::ignore_spaces( void )
{
  while( isspace( in_.peek() ) )
    in_.ignore();
}

bool Interpreter::iscoord( char check )
{
  return 
    ( check == 'f' ) ||
    ( check == 'F' ) ||
    ( check == 'x' ) ||
    ( check == 'X' ) ||
    ( check == 'y' ) ||
    ( check == 'Y' ) ||
    ( check == 'z' ) ||
    ( check == 'Z' );
}

bool Interpreter::g_code( void )
{
  int num = 0;
  char letter = 0;

  Position next_pos;

  if( !isdigit( in_.peek() ) )
    return true;

  in_ >> num;

  switch( num )
  {
    case 0:
      //fall through
    case 1:
      ignore_spaces();
      if( isalpha( in_.peek() ) )
      {
        in_ >> letter;

        while( iscoord(letter) )
        {
          in_ >> num;
          switch( letter )
          {
            case 'f':
            case 'F':
              speed_ = num;
              break;

            case 'x':
            case 'X':
              next_pos.x() = num;
              break;

            case 'y':
            case 'Y':
              next_pos.y() = num;
              break;

            case 'z':
            case 'Z':
              next_pos.z() = num;
              break;

            default:
              ;
          }
          in_ >> letter;
        }
      }
      else
        return true;

      commands_.push_back( new Linear_move_command( next_pos, plane_ ) );
      break;

    case 17:
      plane_ = XY_PLANE;
      break;

    case 18:
      plane_ = XZ_PLANE;
      break;

    case 19:
      plane_ = YZ_PLANE;

    case 94:

    default:
      ;
  }
  return false;
}

bool Interpreter::m_code( void )
{
  return false;
}
