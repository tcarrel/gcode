#include"setup.h"


Setup::Setup( void ) : successful(false)
{
  core_speed_ = 0;
  x_max_ = x_min_ = 0;
  y_max_ = y_min_ = 0;
  z_max_ = z_min_ = 0;

  ifstream ini( "dat/sys.inf", std::ios::in );

  successful = ini.good();
  string line = "";

  if( successful )
  {    
    while( !(ini >> line).eof() )
    {
      if( line[0] == '#' )
      {
        getline(ini, line);
        ini.ignore();
      }
      else
      {
        if( line == "cpuspeed" )
        {
          ini >> core_speed_;
          cout << "CPU speed set to: " << core_speed_ << endl;
          ini.ignore();
        }
        if( line == "maximums" )
        {
          ini >> x_max_;
          ini >> y_max_;
          ini >> z_max_;
        }         
        if( line == "minimums" )
        {
          ini >> x_min_;
          ini >> y_min_;
          ini >> z_min_;
        }         
        //addition startup.ini options go here.
      }
    }    
    line = "";
  }

  ini.close();
}

inline unsigned long long int& Setup::cpu_speed( void )
{
  return core_speed_;
}
inline long long int& Setup::xmax( void )
{
  return x_max_;
}
inline long long int& Setup::ymax( void )
{
  return y_max_;
}
inline long long int& Setup::zmax( void )
{
  return z_max_;
}
inline long long int& Setup::xmin( void )
{
  return x_min_;
}
inline long long int& Setup::ymin( void )
{
  return y_min_;
}
inline long long int& Setup::zmin( void )
{
  return z_min_;
}

ostream& operator<< (ostream& strm, Setup& dat)
{
  string dline = std::string(80, '=');
  string hline = std::string(80, '-');
  
  strm << "Setup Parameters:\tSet Value:" << endl <<
    dline << endl << 
    " Computer Settings:" << endl <<
    hline << endl <<
    "\tCPU Clk:\t" << dat.core_speed_ << endl << 
    dline << endl <<
    " Machine settings:" << endl <<
    hline << endl <<
    "\tLimits:" << endl <<
    "\t\t" << dat.x_max_ << " >= x >= " << dat.x_min_ << endl << 
    "\t\t" << dat.y_max_ << " >= y >= " << dat.y_min_ << endl <<
    "\t\t" << dat.z_max_ << " >= z >= " << dat.z_min_ << endl <<
    dline << endl << endl;

  return strm;
}
