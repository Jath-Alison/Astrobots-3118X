#include "vex.h"

class sol2pneumatics
{
  pneumatics& up;
  pneumatics& down;
  public:

  sol2pneumatics(pneumatics& upP, pneumatics&downP):
  up(upP),down(downP){}
  void release()
  {
    up.close();
    down.close();
  }
  void open()
  {
    up.open();
    down.close();
  }
  void close()
  {
    up.close();
    down.open();
  }
};