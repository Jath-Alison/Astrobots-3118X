#include "robotConfig.h"
#include "Rei\utils.h"

#include <string>

namespace Rei
{
  using namespace vex;

  // Enumerate different possible screens on robot.
  enum screenState
  {
    MAIN_MENU_1 = 0,
    MAIN_MENU_2 = 1,
    SELECTING_1 = 2,
    SELECTING_2 = 3,
    FIELD_PRINTING = 4,
    CATA_PRINTING = 5,
    DIAGNOSTICS_1 = 6, // odom values, speeds, and flags. Robot knowledge.
    DIAGNOSTICS_2 = 7, // temperature and wattage. Robot health.
    VISION_PRINTING = 8,
    SIGNALLING = 9,
  };

  // screen thread values:
  enum button_shape
  {
    circle = 0,
    square = 1
  };
  int screenstep = 0; // diagnostic value for screen.

  // screen dimentions: 316 wide, 212 tall.
  const int screen_width = 480;
  const int screen_length = 272;

  // Current state of the screen:
  screenState scrstate;

  void valPrint(int rows, int indent, std::string(title), double printval,
                int cols = 10, int sigfs = 2, std::string(units) = "")
  {
    // cols is where the decimal point goes.
    Brain.Screen.setCursor(rows, 1 + indent);
    Brain.Screen.print(title.c_str());
    Brain.Screen.print("           ");
    int temp = trunclog10(absolute(printval));
    if (temp < 1)
    {
      temp = 1;
    }
    Brain.Screen.setCursor(rows, cols - 1 - temp);
    if (printval >= 0)
    {
      Brain.Screen.print("+");
    }
    Brain.Screen.print(printval);
    Brain.Screen.print("    ");                     // get rid of any trailing digits from previous prints.
    Brain.Screen.setCursor(rows, cols + 2 + sigfs); // place units on space after decimal+offset
    Brain.Screen.print(units.c_str());
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // Initialize Autons:
  class auton
  {
  private:
    static void printCategory()
    {
      Brain.Screen.setFont(mono30);
      switch (currentCategory)
      {
      case aLeft:
        Brain.Screen.printAt(100, 30, "Left Autons:");
        break;
      case aRight:
        Brain.Screen.printAt(100, 30, "Right Autons:");
        break;
      case aSkills:
        Brain.Screen.printAt(100, 30, "Skills Auton:");
        break;
      case aSolowp:
        Brain.Screen.printAt(100, 30, "SoloWP Auton:");
        break;
      case aTest:
        break;
      }
    }
    static void printSelected()
    {
      Brain.Screen.setFont(mono30);
      Brain.Screen.setCursor(3, 1);
      Brain.Screen.print("Selected ");
      if (currentCategory != aTest)
      {
        Brain.Screen.print(
            bundleOf(currentCategory)  // find category
                ->program(currentType) // find program
                .getTitle()            // get title
                .c_str()               // convert title to const char[]
        );
        Brain.Screen.print(" ");
        Brain.Screen.print(
            bundleOf(currentCategory)
                ->getTitle()
                .c_str());
        // Wait 2sec to start auton.
        this_thread::sleep_for(2000);
        Brain.Screen.clearScreen();
      }
      else
      {
        Brain.Screen.print("Test Auton");
        // Wait 2sec to start auton.
        this_thread::sleep_for(500);
        Brain.Screen.clearScreen();
      }
      Brain.Screen.print(".");
    }
    // Actually properties of auton:
    static bool done;
    static thread t;

  public:
    enum category
    {
      aLeft = 20,
      aRight = 30,
      aSkills = 40,
      aSolowp = 60,
      aTest = 5
    };
    enum flavor
    {
      aSafe = 2,
      aNormal = 3,
      aRisky = 4
    };
    class killtimer
    {
    private:
      static double timeStarted;
      static double limitTime;
      static bool ison;

    public:
      // Timed Disengage System:
      // Reset starting time and start off:
      static void restart()
      {
        timeStarted = Brain.Timer.time(sec);
        ison = 0;
      }
      // make isDone return 0;
      static void turnOff() { ison = 0; }
      // Set timer for a length of time after call
      static void setFor(double length, timeUnits units)
      {
        if (units == msec)
        {
          length *= 1000;
        }
        // Set new  limit time.
        limitTime = length + Brain.Timer.time(sec);
        // Turn Timer on by default.
        ison = 1;
      }
      // Set timer to end at a point of time in auton
      static void setTo(double autonTime, timeUnits units)
      {
        // recalculate to sec if necessary.
        if (units == msec)
        {
          autonTime *= 1000;
        }
        // Set new limittime.
        limitTime = timeStarted + autonTime;
        // turn timer on by default.
        ison = 1;
      }

      // Fetch current time from start of auton
      static double currentTime()
      {
        return Brain.Timer.time(sec) - timeStarted;
      }
      // return 1 if time has expried.
      static bool isdone()
      {
        // return true if timer is on and time is greater the time.
        return (ison) * (Brain.Timer.time(sec) >= limitTime);
      }
    };
    // Store properties of last selected auton;
    static bool ready;
    static category currentCategory;
    static flavor currentType;

    // individual programs to be plugged into each of the categories
    class program
    {
    private:
      std::string(title);
      std::string(desc);
      static void nullroutine(bool, bool){};
      void (*callback)(bool, bool) = nullroutine;
      bool a1, a2;

    public:
      // constructors
      program(std::string(TITLE), std::string(description), void (*program)(bool, bool), bool arg1, bool arg2) : title(TITLE), desc(description), callback(program), a1(arg1), a2(arg2) {}
      // Default constructor.
      program() : program("", "", nullroutine, 0, 0)
      {
      }
      // accessors
      std::string(getTitle)() { return title; }
      std::string(getDesc)() { return desc; }
      // execution
      void run()
      {
        callback(a1, a2);
      }
    };
    // Have a null placeholder program to fill bundles before the actual ones are defined.
    static program nullprogram;

    class autonbundle
    {
    private:
      std::string(title);
      category code;
      program *sprogram;
      program *nprogram;
      program *rprogram;

    public:
      autonbundle(
          // Parameters:
          std::string(TITLE), category category_code,
          program &safeprogram, program &normprogram, program &riskprogram)
          : // Use Parameters to initialize:
            title(TITLE), code(category_code),
            sprogram(&safeprogram), nprogram(&normprogram), rprogram(&riskprogram)
      {
      }
      autonbundle() {}
      // accessors:
      std::string(getTitle)() { return title; }
      category getCode() { return code; }
      program program(flavor autontype)
      {
        switch (autontype)
        {
        case aSafe:
          return *sprogram;
        case aNormal:
          return *nprogram;
        case aRisky:
          return *rprogram;
        }
      }
      // mutator:
      void setPrograms(class program &safeprogram, class program &normprogram, class program &riskprogram)
      {
        sprogram = &safeprogram;
        nprogram = &normprogram;
        rprogram = &riskprogram;
      }
    };
    // define the bundles
    static autonbundle leftAutons;
    static autonbundle rightAutons;
    static autonbundle solowpAutons;
    static autonbundle skillsAutons;
    static autonbundle nullabundle;
    static void initializeBundles();
    static void thetestauton();

    // Fetch bundle corresponding to category.
    static autonbundle *bundleOf(category cat)
    {
      switch (cat)
      {
      case aLeft:
        return &leftAutons;
      case aRight:
        return &rightAutons;
      case aSkills:
        return &skillsAutons;
      case aSolowp:
        return &solowpAutons;
      default:
        return &nullabundle;
      }
    }
    static void pause(int)
    {
      ready = 0;
    }

    //////////////////////
    // Set auton categories:
    //////////////////////

    static void setLeft(int)
    {
      currentCategory = aLeft;
      printCategory();
    }
    static void setRight(int)
    {
      currentCategory = aRight;
      printCategory();
    }
    static void setSolowp(int)
    {
      currentCategory = aSolowp;
      printCategory();
    }
    static void setSkills(int)
    {
      currentCategory = aSkills;
      printCategory();
    }
    static void setTest(int)
    {
      currentCategory = aTest;
      printSelected();
      ready = 1;
    }
    static void setAuton(int type)
    {
      // Handle invalid inputs:
      if ((type != aRisky) * (type != aNormal) * (type != aSafe))
      {
        type = aSafe;
      }
      // Set auton type:
      currentType = static_cast<flavor>(type);

      // Set to ready
      printSelected();
      ready = 1;
    }
    // execution:
    static int run()
    {
      // Reset done and timer.
      done = 0;
      killtimer::restart();

      if (currentCategory == aTest)
      {
        thetestauton();
      }
      else
      {
        ((bundleOf(currentCategory))->program(currentType)).run();
      }
      // mark as done.
      done = 1;
      return 1;
    }
    static double dctest(const controller::button &terminateButton, double timelimit)
    {
      done = 0;
      // run the thread of
      t = thread(run);

      double limitTime, newtime;

      // Continuously check to terminate the
      for (
          limitTime = Brain.Timer.time(sec) + timelimit; // initialized
          !done;                                         // end process naturally if thread finishes.
      )
      {
        // fetch new time
        newtime = Brain.Timer.time(sec);

        // Check to break
        if (
            limitTime <= Brain.Timer.time(sec) || // Check for timelimit.
            terminateButton.pressing())           // Check for manual termination
        {
          t.interrupt(); // stop thread manually.
          break;
        }

        // Wait a little to prevent wasted resources:
        wait(20, msec);
      }
      // Turn timer off just in case:
      killtimer::turnOff();
      // return remaining.
      return -newtime + limitTime;
    }
  };
  // Initialize the auton states:
  thread auton::t = thread();
  bool auton::done = 0;
  auton::category auton::currentCategory = aLeft;
  auton::flavor auton::currentType = aSafe;
  double auton::killtimer::timeStarted = 0;
  double auton::killtimer::limitTime = 0;
  bool auton::killtimer::ison = 0;
  // Declare programs to initialize later.
  auton::program auton::nullprogram = auton::program();
  auton::autonbundle auton::leftAutons("Left", aLeft, nullprogram, nullprogram, nullprogram);
  auton::autonbundle auton::rightAutons("Right", aRight, nullprogram, nullprogram, nullprogram);
  auton::autonbundle auton::skillsAutons("Skills", aSkills, nullprogram, nullprogram, nullprogram);
  auton::autonbundle auton::solowpAutons("Solo Win Point", aSolowp, nullprogram, nullprogram, nullprogram);
  auton::autonbundle auton::nullabundle("", aLeft, nullprogram, nullprogram, nullprogram);

  // initialize auton::ready
  bool auton::ready = 0;
  // button-tied functions
  void nullv(int buttonval) {}

  class scrButton // class for buttons
  {
  private:
    // button size and place.
    int x = 0, y = 0;
    int size = 50; // width of button in pixels
    // button appearance
    std::string(text) = "";
    std::string(desc) = "";
    vex::color c = vex::color(100, 100, 100);
    bool issquare = 1;
    // whether or not the hitbox on the button is on.
    bool ison = 1;
    // whether or not the button is real.
    bool isnull = 0;
    void (*pressAction)(int) = nullv;
    screenState newscreen;

  public:
    //////////////////////
    // Button constructors:
    //////////////////////
    scrButton(std::string(texttitle), void (*pressedaction)(int), screenState nextscreen) : // initialize members
                                                                                            pressAction(pressedaction),
                                                                                            text(texttitle),
                                                                                            newscreen(nextscreen)
    {
      ison = 0;
    }
    scrButton(std::string(texttitle), void (*pressedaction)(int), screenState nextscreen, int setr, int setg, int setb) : scrButton(texttitle, pressedaction, nextscreen)
    {
      setColor(setr, setg, setb);
    }
    scrButton(std::string(texttitle), void (*pressedaction)(int), screenState nextscreen, vex::color setcolor) : scrButton(texttitle, pressedaction, nextscreen)
    {
      c = (setcolor);
    }
    scrButton(bool nullbutton)
    {
      isnull = nullbutton;
    }
    //////////////////////
    // Activation/Deactivation
    //////////////////////
    void On()
    {
      ison = !isnull;
    }
    void Off()
    {
      ison = 0;
    }
    //////////////////////
    // Modificaiton/mutators.
    //////////////////////
    void setlocation(int setx, int sety)
    {
      x = setx;
      y = sety;
    }
    void setshape(button_shape s)
    {
      issquare = s;
    }
    void setColor(int setr, int setg, int setb)
    {
      c = vex::color(setr, setg, setb);
    }
    void setColor(vex::color newC)
    {
      c = newC;
    }
    void setText(std::string(title), std::string(description))
    {
      text = title;
      desc = description;
    }
    ///////////////////////
    // Actual handling on Screen:
    ///////////////////////
    void print()
    {
      Brain.Screen.setPenWidth(1);
      Brain.Screen.setPenColor(white);
      Brain.Screen.setFont(mono20);
      if (ison)
      {
        // print button shape:
        if (issquare)
        {
          Brain.Screen.drawRectangle(x, y, size, size, c);
        }
        else
        {
          Brain.Screen.drawCircle(x + size / 2, y + size / 2, size / 2, c);
        }
        // print button text:
        if (desc.length() > 0)
        {
          Brain.Screen.printAt(x + size, y + size * 0.75 - 10, true, text.c_str());
          Brain.Screen.printAt(x + size + 23, y + size * 0.75 + 13, true, desc.c_str());
        }
        else
        {
          Brain.Screen.printAt(x + size, y + size * 0.75, true, text.c_str());
        }
      }
    }
    bool ispressed()
    {
      int pressX = Brain.Screen.xPosition();
      int pressY = Brain.Screen.yPosition();
      if (ison)
      {
        if (issquare)
        {
          return // square hitbox:
              (pressX > x) * (pressX < size + x) *
              (pressY > y) * (pressY < size + y);
        }
        else
        {
          // get x and y distance from center
          pressX = pressX - (x + size / 2);
          pressY = pressY - (y + size / 2);
          int temp = size / 2;
          // circular hitbox:
          return (pressX * pressX + pressY * pressY) < (temp * temp);
        }
      }
      else
      {
        return 0;
      }
    }
    void pressedAction(int x)
    {
      // jump to a new screen.
      scrstate = newscreen;
      // execute some sort of action.
      pressAction(x);
    }
  };
  class diagval // class for diagnostic values to print in diagnostic screens
  {
  private:
    bool iscallback = 0;

    // types of variable printed:
    double *printval = nullptr; // variable itself
    double (*printeval)() = nullptr;

    // formatting:
    // title formatting:
    std::string(title) = "";
    int indent = 0;
    // variable.
    int cols = 12; // column of ones place of print value
    int sigfs = 2; // number of decimals to show
    // units of variable:
    std::string(unit) = "";

    bool isnull = 1;

    // template constructor:
    diagval(std::string(header), int decimals, std::string(units) = "") : title(header), sigfs(decimals), unit(units)
    {
      isnull = 0;
    }

  public:
    ////////////////
    // Constructors:
    ////////////////
    diagval()
    {
      isnull = 1;
    }
    diagval(std::string(header), double &variable, int decimals, std::string(units) = "") : diagval(header, decimals, units)
    {
      printval = &variable;
      iscallback = 0;
    }
    diagval(std::string(header), double (&evariable)(), int decimals, std::string(units) = "") : diagval(header, decimals, units)
    {
      printeval = &evariable;
      iscallback = 0;
    }
    // Modify formatting:
    void setformatting(int indentTitle, int column, int decimals)
    {
      indent = indentTitle;
      cols = column;
      sigfs = decimals;
    }
    // print the row of diagnostics.
    void print(int row)
    {
      if (!isnull)
      {
        // Determine value to print.
        double toprint;
        if (iscallback)
        {
          toprint = printeval();
        }
        else
        {
          toprint = *printval;
        }

        // print title and clear row after title.
        Brain.Screen.setCursor(row, 1 + indent);
        Brain.Screen.print(title.c_str());
        Brain.Screen.print("           ");

        // Set cursor so that decimal point is at cols
        // honestly math here is pretty sketch...
        int temp = trunclog10(absolute(toprint));
        // cap min temp at 1
        if (temp < 1)
        {
          temp = 1;
        }
        Brain.Screen.setCursor(row, cols - 1 - temp);

        // print number:
        // print sign if positive
        if (toprint >= 0)
        {
          Brain.Screen.print("+");
        }
        Brain.Screen.print(toprint);
        Brain.Screen.print("    "); // clear any previous trailing digits.

        // print units:
        Brain.Screen.setCursor(row, cols + 2 + sigfs); // place units on space after decimal+offset
        Brain.Screen.print(unit.c_str());
      }
    }
  };
  // deploy nullval: value which doesn't print anything
  diagval nulldiagnostic = diagval();
  class screen
  {
  private:
    static screenState currentState;

  protected:
    bool isOn = 0;
    bool pressed()
    {
      return Brain.Screen.PRESSED;
    }
    bool ispressed = 0;

  public:
    ////////////
    // Changing screenstates.:
    ////////////
    static void setState(screenState newState) { currentState = newState; }
    static screenState getState() { return currentState; }
    ////////////
    // Progress bar:
    ////////////
    class progbar
    {
    private:
      int step = 0;
      double maxValue = 15;
      bool isOn = 1;
      // Exit handling
      void (*fillAction)(int) = nullv;
      screenState newscreen = MAIN_MENU_1;

    public:
      // constructors:
      progbar(screenState bar_to, void (*exitAction)(int) = nullv) : newscreen(bar_to), fillAction(exitAction) {}
      progbar() {}

      // Activation/deactivation
      void turnOn()
      {
        isOn = 1;
        step = 0;
        print(0);
      }
      void turnOff()
      {
        isOn = 0;
        step = 0;
      }
      // handling:
      void print(double t)
      {
        if (isOn)
        {
          Brain.Screen.setPenWidth(1);
          Brain.Screen.drawRectangle(screen_width - 5, 0, 5, screen_length, red);
          Brain.Screen.drawRectangle(screen_width - 5, (1 - t) * screen_length, 5, t * screen_length, green);
        }
      }
      void update()
      {
        if (isOn)
        {
          if (Brain.Screen.pressing())
          {
            step++;
          }
          else
          {
            step = 0;
          }
          print(step / maxValue);
        }
        else
        {
          step = 0;
        }
      }
      bool isFull()
      {
        return (step >= maxValue);
      }
      void filledAction(int x)
      {
        // jump to a new screen.
        scrstate = newscreen;
        // execute some sort of action.
        fillAction(x);
      }
    };
    progbar bar;
    const screenState bar_to = MAIN_MENU_1;
    // Pen
    static void resetPen()
    {
      Brain.Screen.setFont(mono20);
      Brain.Screen.setPenColor(white);
      Brain.Screen.setPenWidth(1);
      Brain.Screen.setFillColor(black);
    }
    //////////////////////
    // Activation/Deactivation
    //////////////////////
    virtual void On()
    {
      Brain.Screen.clearScreen();
      isOn = 1;
      bar.turnOn();
    }
    virtual void Off(int a)
    {
      isOn = 0;
      bar.turnOff();
      bar.filledAction(a);
      Brain.Screen.clearScreen();
    }
    //////////////////////
    // Handling:
    //////////////////////
    virtual void print(){};
    virtual void update()
    {
      bar.update();
    };
    virtual int returnvalue()
    {
      ispressed = pressed();
    };
  };
  class scrMenu : public screen
  {
  private:
    // menu title
    std::string(title);
    // x-coordinate of buttons
    int buttonx;
    // button references.
    scrButton &b1, b2, b3, b4, b5;
    bool v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0; // placeholders to hold buttons' ispressed values
    button_shape shapes;
    void setButtonShapes()
    {
      b1.setshape(shapes);
      b2.setshape(shapes);
      b3.setshape(shapes);
      b4.setshape(shapes);
      b5.setshape(shapes);
      // move buttons' location
      if (shapes == square)
      {
        b1.setlocation(buttonx, 0);
        b2.setlocation(buttonx, 50);
        b3.setlocation(buttonx, 100);
        b4.setlocation(buttonx, 150);
        b5.setlocation(buttonx, 200);
      }
      else
      {
        b1.setlocation(buttonx, 0);
        b2.setlocation(buttonx + 16, 48);
        b3.setlocation(buttonx, 96);
        b4.setlocation(buttonx + 16, 144);
        b5.setlocation(buttonx, 192);
      }
    }
    // bar use:
    bool hasbar;

  public:
    ///////////////////
    // Constructors:
    ///////////////////

    // Constructor for menu without back bar.
    scrMenu(std::string(TITLE), int lane, button_shape shape, scrButton &button1,
            scrButton &button2, scrButton &button3,
            scrButton &button4, scrButton &button5) : // initialize buttons used.:
                                                      b1(button1), b2(button2), b3(button3), b4(button4), b5(button5),
                                                      // initialize printed title
                                                      title(TITLE),
                                                      // initialize button format:
                                                      buttonx(300 * (lane - 1)), shapes(shape)
    {
      hasbar = 0;
    }
    // Constructor for menu with back bar.
    scrMenu(std::string(TITLE), int lane, button_shape shape, scrButton &button1,
            scrButton &button2, scrButton &button3,
            scrButton &button4, scrButton &button5,
            const screenState backScreen) : scrMenu(TITLE, lane, shape, button1, button2, button3, button4, button5)
    {
      bar = progbar(backScreen);
      hasbar = 1;
    }
    //////////////////////
    // Activation/Deactivation
    //////////////////////
    void On() override
    {
      if (!hasbar)
      {
        bar.turnOff();
      }
      else
      {
        bar.turnOn();
      }
      Brain.Screen.setPenWidth(1);
      setButtonShapes();
      isOn = 1;
      b1.On();
      b2.On();
      b3.On();
      b4.On();
      b5.On();
    }
    void Off(int pressedB) override
    {
      bar.turnOff();
      isOn = 0;
      b1.Off();
      b2.Off();
      b3.Off();
      b4.Off();
      b5.Off();
      Brain.Screen.clearScreen();
      switch (pressedB)
      {
      case 1:
        b1.pressedAction(pressedB);
        break;
      case 2:
        b2.pressedAction(pressedB);
        break;
      case 3:
        b3.pressedAction(pressedB);
        break;
      case 4:
        b4.pressedAction(pressedB);
        break;
      case 5:
        b5.pressedAction(pressedB);
        break;
      default:
        bar.filledAction(pressedB);
        break;
      }
    }
    //////////////////////
    // Handling:
    //////////////////////
    void print() override
    { // printing all buttons and bar
      b1.print();
      b2.print();
      b3.print();
      b4.print();
      b5.print();
      bar.print(0);
      Brain.Screen.setFont(prop40);
      Brain.Screen.printAt((300 - buttonx) / 2, screen_length / 2, title.c_str());
      Brain.Screen.setFont(mono20);
    }
    void update() override
    {
      bar.update();
    }
    int returnvalue() override
    {
      v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0; // placeholders to hold buttons' ispressed values
      v1 = b1.ispressed();
      v2 = b2.ispressed();
      v3 = b3.ispressed();
      v4 = b4.ispressed();
      v5 = b5.ispressed();

      if (v1 + v2 + v3 + v4 + v5 == 1)
      {
        return (v1 + 2 * v2 + 3 * v3 + 4 * v4 + 5 * v5); //*s;
      }
      else
      {
        return 0;
      }
    }
  };

  class scrDiagnostics : public screen
  {
  private:
    // diagnostic variables.
    diagval vals[12];
    // buttons
    bool v1 = 0; // initialize placeholder to 0.
    std::string(title);

  public:
    scrDiagnostics(std::string(TITLE),
                   diagval &v1 = nulldiagnostic, diagval &v2 = nulldiagnostic, diagval &v3 = nulldiagnostic, diagval &v4 = nulldiagnostic,
                   diagval &v5 = nulldiagnostic, diagval &v6 = nulldiagnostic, diagval &v7 = nulldiagnostic, diagval &v8 = nulldiagnostic,
                   diagval &v9 = nulldiagnostic, diagval &v0 = nulldiagnostic, diagval &ve = nulldiagnostic, diagval &vw = nulldiagnostic)
    {
      title = TITLE;
      vals[0] = v1;
      vals[1] = v2;
      vals[2] = v3;
      vals[3] = v4;
      vals[4] = v5;
      vals[5] = v6;
      vals[6] = v7;
      vals[7] = v8;
      vals[8] = v9;
      vals[9] = v0;
      vals[10] = ve;
      vals[11] = vw;
    }
    //////////////////////
    // Handling:
    //////////////////////
    void print()
    {
      // Print the title off to the side.
      Brain.Screen.setFont(prop40);
      Brain.Screen.printAt(250, screen_length / 2, title.c_str());
      // Rest font.
      Brain.Screen.setFont(mono20);
    }
    void update()
    {
      for (int i = 0; i < 12; i++)
      {
        vals[i].print(i + 1);
      }
      bar.update();
    }
    int returnvalue()
    {
      v1 = bar.isFull();
      return v1;
    }
  };

  enum signaltype
  {
    NULL_SIGNAL = -10,
    DONE_SIGNAL = 13,
    NONDONE_SIGNAL = 17,
    ERROR_SIGNAL = 19
  };

  class signalPack
  {
  private:
    // colors
    vex::color nullcolor = vex::color(0, 0, 0);      // color black
    vex::color donecolor = vex::color(0, 255, 0);    // color green
    vex::color ndonecolor = vex::color(255, 255, 0); // color yellow
    vex::color errcolor = vex::color(255, 0, 0);     // color red
    // current signal.
    signaltype currentS = ERROR_SIGNAL;
    // flashing
    bool isflash = 0;
    int flashInterval = 2;
    int flashFactor = 2;
    // null handling
    bool isnull = 0;

  public:
    signalPack(bool isNull)
    {
      isnull = isNull;
    }
    void signalTo(signaltype t)
    {
      currentS = t;
    }
    void setColor(signaltype s, int r, int g, int b)
    {
      switch (s)
      {
      case NULL_SIGNAL:
        nullcolor = vex::color(r, g, b);
        break;
      case DONE_SIGNAL:
        donecolor = vex::color(r, g, b);
        break;
      case NONDONE_SIGNAL:
        ndonecolor = vex::color(r, g, b);
        break;
      case ERROR_SIGNAL:
        errcolor = vex::color(r, g, b);
        break;
      }
    }
    void setColor(signaltype s, int rgb)
    {
      switch (s)
      {
      case NULL_SIGNAL:
        nullcolor = rgb;
        break;
      case DONE_SIGNAL:
        donecolor = rgb;
        break;
      case NONDONE_SIGNAL:
        ndonecolor = rgb;
        break;
      case ERROR_SIGNAL:
        errcolor = rgb;
        break;
      }
    }
    void setflashing(bool flashing, int interval = 15, int factor = 3)
    {
      isflash = flashing;
      flashInterval = interval;
      flashFactor = factor;
    }

    bool isOn(int t)
    {
      if (isnull)
      {
        return 0;
      }
      else if (!isflash)
      {
        return 1;
      }
      else
      {
        return ((t / flashInterval) % flashFactor == 0) * !(currentS == NULL_SIGNAL);
      }
    }
    signaltype currentSignal()
    {
      if (isnull)
      {
        return NULL_SIGNAL;
      }
      else
      {
        return currentS;
      }
    }
    vex::color currentColor()
    {
      switch (currentS)
      {
      case NULL_SIGNAL:
        return nullcolor;
      case DONE_SIGNAL:
        return donecolor;
      case NONDONE_SIGNAL:
        return ndonecolor;
      case ERROR_SIGNAL:
        return errcolor;
      }
    }
  };
  signalPack nullSigPack(1);
  class scrSignal : public screen
  {
  private:
    // trigger for holding the screen, and
    int scrStep = 0;
    bool v1;

    signalPack *s1;
    signalPack *s2;

  public:
    scrSignal(signalPack &primary, signalPack &flashing = nullSigPack)
    {
      primary.setflashing(0);
      flashing.setflashing(1);
      s1 = &primary;
      s2 = &flashing;
    }
    void On()
    {
      scrStep = 0;
    }
    void update()
    {

      if (s2->isOn(scrStep) * (s2->currentSignal() != NULL_SIGNAL))
      {
        Brain.Screen.clearScreen(s2->currentColor());
      }
      else
      {
        Brain.Screen.clearScreen(s1->currentColor());
      }
      Brain.Screen.setFont(mono30);
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Signalling:");
      Brain.Screen.setFont(mono20);
      Brain.Screen.setCursor(5, 1);
      Brain.Screen.print("signal 1:");
      Brain.Screen.print(s1->currentSignal());
      Brain.Screen.print("   ");
      Brain.Screen.print(s1->currentColor());
      Brain.Screen.setCursor(6, 1);
      Brain.Screen.print("signal 2:");
      Brain.Screen.print(s2->isOn(scrStep));
      Brain.Screen.print("  ");
      Brain.Screen.print(s2->currentSignal());

      scrStep++;
      bar.update();
    }
    int returnvalue()
    {
      v1 = bar.isFull();
      return v1;
    }
  };

  class scrAuton : public screen
  {
  private:
    // menu title
    std::string(title);
    // x-coordinate of buttons
    int buttonx;
    // button references.
    static scrButton b1;
    static scrButton b2;
    static scrButton b3;
    bool v1 = 0, v2 = 0, v3 = 0; // placeholders to hold buttons' ispressed values
    button_shape shapes;
    //
    void setButtonShapes()
    {
      b1.setshape(shapes);
      b2.setshape(shapes);
      b3.setshape(shapes);
      // move buttons' location
      if (shapes == square)
      {
        b1.setlocation(buttonx, 60);
        b2.setlocation(buttonx, 120);
        b3.setlocation(buttonx, 180);
      }
      else
      {
        b1.setlocation(buttonx, 60);
        b2.setlocation(buttonx, 120);
        b3.setlocation(buttonx, 180);
      }
      b1.setColor(255, 255, 000);
      b2.setColor(255, 180, 050);
      b3.setColor(255, 000, 255);
    }

    // store auton bundles.
    auton::autonbundle *bundle;

  public:
    ///////////////////
    // Constructors:
    ///////////////////

    // Constructor for menu with back bar.
    scrAuton(std::string(TITLE), int lane, button_shape shape, const screenState backScreen) : // initialize printed title
                                                                                               title(TITLE),
                                                                                               // initialize button format:
                                                                                               buttonx(300 * (lane - 1)), shapes(shape)
    {
      bar = progbar(backScreen);
      setButtonShapes();
    }
    //////////////////////
    // Activation/Deactivation
    //////////////////////
    void On() override
    {
      // Reset button shapes:
      resetPen();

      // Retrieve selected auton category.
      bundle = auton::bundleOf(auton::currentCategory);

      // Assign title+descriptions of autons within category.
      b1.setText(
          (bundle->program(auton::aSafe)).getTitle(),
          (bundle->program(auton::aSafe)).getDesc());
      b2.setText(
          (bundle->program(auton::aNormal)).getTitle(),
          (bundle->program(auton::aNormal)).getDesc());
      b3.setText(
          (bundle->program(auton::aRisky)).getTitle(),
          (bundle->program(auton::aRisky)).getDesc());

      // Turn everything on:
      isOn = 1;
      bar.turnOn();
      b1.On();
      b2.On();
      b3.On();
    }
    void Off(int pressedB) override
    {
      // turn all off:
      bar.turnOff();
      isOn = 0;
      b1.Off();
      b2.Off();
      b3.Off();
      Brain.Screen.clearScreen();
      switch (pressedB)
      {
      case 1:
        b1.pressedAction(auton::aSafe);
        break;
      case 2:
        b2.pressedAction(auton::aNormal);
        break;
      case 3:
        b3.pressedAction(auton::aRisky);
        break;
      default:
        bar.filledAction(pressedB);
        break;
      }
    }
    //////////////////////
    // Handling:
    //////////////////////
    void print() override
    { // printing all buttons and bar
      b1.print();
      b2.print();
      b3.print();
      bar.print(0);
      Brain.Screen.setFont(prop40);
      Brain.Screen.printAt((300 - buttonx) / 2, screen_length / 2, title.c_str());
      Brain.Screen.setFont(mono20);
    }
    void update() override
    {
      bar.update();
    }
    int returnvalue() override
    {
      v1 = 0, v2 = 0, v3 = 0; // placeholders to hold buttons' ispressed values
      v1 = b1.ispressed();
      v2 = b2.ispressed();
      v3 = b3.ispressed();

      if (v1 + v2 + v3 == 1)
      {
        return (v1 + 2 * v2 + 3 * v3); //*s;
      }
      else
      {
        return 0;
      }
    }
  };
  // Static buttons of scrAuton defined out of line:
  scrButton scrAuton::b1 = scrButton("", auton::setAuton, MAIN_MENU_1);
  scrButton scrAuton::b2 = scrButton("", auton::setAuton, MAIN_MENU_1);
  scrButton scrAuton::b3 = scrButton("", auton::setAuton, MAIN_MENU_1);

} // namespace Rei