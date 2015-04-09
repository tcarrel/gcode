#include"motor.h"

long int inch_to_steps( double inches )
{
  return (long int) inches * 10000;
}

long int mm_to_steps( double millimeters )
{
  return (long int) millimeters * 100;
}
