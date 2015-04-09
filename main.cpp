#include<iostream>
#include<fstream>
#include<chrono>

using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::endl;
using std::flush;

using std::ifstream;

#include"position.h"
#include"interpreter.h"
#include"enums.h"
#include"setup.h"
#include"Aux_Data.h"

const string BOLD = "\033[1m";
const string NORM = "\033[0m";
const string SCREEN_RESET = "\033[2J\033[0;0H"; 

inline void usage( char executable_name[] )
{
  cout << SCREEN_RESET << flush;
  cout << "$ " << executable_name << " " << BOLD << "<arg1>" << NORM << endl
    << "  Will cause " << executable_name << " attempt to load " << BOLD 
    << "<arg1>" << NORM << ".  " << BOLD
    << "<arg1>" << NORM << " cannot contain any spaces" << endl << endl
    << "Or:" << endl
    << endl
    << "$ " << executable_name << endl
    << "  on its own will case " << executable_name << " to prompt for"
    << endl << " all necessary information."
    << endl << endl;
}

string get_filename( void )
{
  cout << endl;
  string str;
  cout << " Please enter name of file to "
    << "load or [Ctrl-c] to quit: " << flush;

  cin  >> str;
  return str;
}

bool open_file( ifstream& inf, string& fname )
{
  inf.open( fname.c_str(), std::ios::in );
  return inf.is_open();
}

void quit( ifstream& inf, int err_no )
{
  inf.close();
  exit( err_no );
}

bool ask_user( void )
{
  string user = "";
  
  cout <<
    " G-code file contained errors." << endl << endl <<
    "\t\t\tDo you still wish to continue?" << endl << endl <<
    "WARNING: Running this file as-is may result in damage" << endl <<
    "to machining tool!" << endl << endl <<
    "Enter [YES] in all caps to run the file anyway." << endl << endl;

  cin >> user;

  return user == "YES";
}

int main( int argc, char* argv[] )
{

  string user = "";
  Setup setup_data; //Loads configuration info from dat/sys.inf
  cerr << " Loading system info file." << endl;
  if( !setup_data.successful )
  {
    cerr << " Could not load system information file." << endl 
      << " Please check that the file:" << endl
      << "  <" << BOLD << "./dat/sys.info" << NORM << "> exists." << endl << endl;
    return 1;
  }

  cout << SCREEN_RESET << endl;
  cout << setup_data << endl;

  string filename = "";

  if( argc > 1)
  {
    string _arg = argv[1];

    if( _arg ==  "--help" || _arg == "-?" )
    {
      usage( argv[0] );
      return 0;
    }

    if( filename == "" )
    {
      if( _arg[0] != '-' )
      {
        filename = _arg;
      }
    }
  }

  if( filename == "" )
    filename = get_filename();


  cout << endl << " Attempting to open file: <" << filename << ">:" << endl << endl;

  ifstream inf;

  if( !open_file( inf, filename ) )
  {
    cerr << " Could not open file <" << BOLD << filename << NORM << ">." << endl;
    quit( inf, 1 );
  }

  Interpreter interpret( inf, setup_data );

  if( interpret.load() )
  {
    user = ""; //reusing the user variable.
    cout << 
      "Loaded file <" << filename << "> with no errors." << endl <<
      "Enter [go] to run file or [quit] to quit." << endl << endl;

    while( user != "go" && user != "quit" )
      cin >> user;

    if( user == "go" )
      interpret.go();
  }
  else
  {
    if( ask_user() )
      interpret.go();
  }

  quit(inf, 0);
}
