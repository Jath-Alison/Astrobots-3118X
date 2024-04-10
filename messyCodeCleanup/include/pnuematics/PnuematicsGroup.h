#include "vex.h"

class pneumatics_group
{
  private:
    pneumatics* p1=nullptr;
    pneumatics* p2=nullptr;
    pneumatics* p3=nullptr;
    pneumatics* p4=nullptr;
    int qt=0;
  public:
    pneumatics_group(pneumatics& pis1, pneumatics& pis2)
    {
      p1= &pis1;
      p2= &pis2;
      qt=2;
    }
    pneumatics_group(pneumatics& pis1, pneumatics& pis2, pneumatics& pis3)
    {
      p1= &pis1;
      p2= &pis2;
      p3= &pis3;
      qt=3;
    }
    pneumatics_group(pneumatics& pis1, pneumatics& pis2, pneumatics& pis3, pneumatics& pis4)
    {
      p1= &pis1;
      p2= &pis2;
      p3= &pis3;
      p4= &pis4;
      qt=4;
    }
    void open()
    {
      p1->open();
      p2->open();
      if (qt>2)
      {
        p3->open();
      }
      if (qt>3)
      {
        p4->open();
      }
    }
    void close()
    {
      p1->close();
      p2->close();
      if (qt>2)
      {
        p3->close();
      }
      if (qt>3)
      {
        p4->close();
        
      }
    }
    void set(bool value)
    {
      p1->set(value);
      p2->set(value);
      if (qt>2)
      {
        p3->set(value);
      }
      if (qt>3)
      {
        p4->set(value); 
      }
    }

};