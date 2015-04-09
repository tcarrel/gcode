#include<chrono>
#include<fstream>
#include<iostream>

using std::ifstream;
using std::getline;
using std::string;
using std::cout;
using std::endl;
using std::ostream;

#ifndef SETUP_H
#define SETUP_H

class Setup
{
  public:
   Setup( void );

   inline unsigned long long int& cpu_speed( void );
   inline long long int& xmax( void );
   inline long long int& ymax( void );
   inline long long int& zmax( void );
   inline long long int& xmin( void );
   inline long long int& ymin( void );
   inline long long int& zmin( void );

   friend ostream& operator<< (ostream&, Setup&);

   bool successful;
  private:

   unsigned long long int core_speed_;
   long long int x_max_, x_min_;
   long long int y_max_, y_min_;
   long long int z_max_, z_min_;
};
#endif
