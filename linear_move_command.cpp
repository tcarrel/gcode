#include"Commands.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Linear_move_command(s)
//
///////////////////////////////////////////////////////////////////////////////
Linear_move_command::Linear_move_command( Position& E, int p )
{
  end_ = E;
  plane_ = p;
}

void Linear_move_command::execute( Position& begin ) // begin )
{
  if( plane_ == XY_PLANE )
  {
    long dx = end_.x() - begin.x();
    long dy = end_.y() - begin.y();

    int x_dir = (dx > 0) ? 1 : -1;
    int y_dir = (dy > 0) ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);

    long i;
    long dev;

    if( dx > dy )
    {
      for( i = 0; i < dx; ++i )
      {
        //move_motor_x.onestep(x_dir);
        begin.x() += x_dir;
        dev += dy;
        if( dev >= dx )
        {
          dev -= dx;
          //move_motor_y.onestep(y_dir);
          begin.y() += y_dir;
        }
        //pause
      }
    }
    else
    {
      for( i = 0; i < dy; ++i )
      {
        //move_motor_y.onestep(y_dir);
        begin.y() += y_dir;
        dev += dx;
        if( dev >= dy )
        {
          dev -= dy;
          //move_motor_x.onestep(x_dir);
          begin.x() += x_dir;
        }
        //pause
      }
    }
    if( begin == end_ )
      cout << BEEP;

    return;
  }

  if( plane_ == XZ_PLANE )
  {
    long dx = end_.x() - begin.x();
    long dz = end_.z() - begin.z();

    int x_dir = (dx > 0) ? 1 : -1;
    int z_dir = (dz > 0) ? 1 : -1;

    dx = abs(dx);
    dz = abs(dz);

    long i;
    long dev;

    if( dx > dz )
    {
      for( i = 0; i < dx; ++i )
      {
        //move_motor_x.onestep(x_dir);
        begin.x() += x_dir;
        dev += dz;
        if( dev >= dx )
        {
          dev -= dx;
          //move_motor_z.onestep(z_dir);
          begin.z() += z_dir;
        }
        //pause
      }
    }
    else
    {
      for( i = 0; i < dz; ++i )
      {
        //move_motor_z.onestep(z_dir);
        begin.z() += z_dir;
        dev += dx;
        if( dev >= dz )
        {
          dev -= dz;
          //move_motor_x.onestep(x_dir);
          begin.x() += x_dir;
        }
        //pause
      }
    }
    if( begin == end_ )
      cout << BEEP;

    return;
  }

  if( plane_ == YZ_PLANE ) //almost never used
  {
    long dy = end_.y() - begin.y();
    long dz = end_.z() - begin.z();

    int y_dir = (dy > 0) ? 1 : -1;
    int z_dir = (dz > 0) ? 1 : -1;

    dy = abs(dy);
    dz = abs(dz);

    long i;
    long dev;

    if( dy > dz )
    {
      for( i = 0; i < dy; ++i )
      {
        //move_motor_y.onestep(y_dir);
        begin.y() += y_dir;
        dev += dz;
        if( dev >= dy )
        {
          dev -= dy;
          //move_motor_z.onestep(z_dir);
          begin.z() += z_dir;
        }
        //pause
      }
    }
    else
    {
      for( i = 0; i < dz; ++i )
      {
        //move_motor_z.onestep(z_dir);
        begin.z() += z_dir;
        dev += dy;
        if( dev >= dz )
        {
          dev -= dz;
          //move_motor_y.onestep(y_dir);
          begin.y() += y_dir;
        }
        //pause
      }
    }
    if( begin == end_ )
      cout << BEEP;

    return;
  }
}
