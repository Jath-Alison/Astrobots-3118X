#include "Vision.h"
vex::vision::signature GREEN_BROAD = vex::vision::signature (1, -5163, -3827, -4495, -5767, -3681, -4724, 3, 0);
vex::vision::signature GREEN_SHARP = vex::vision::signature (2, -5093, -3823, -4458, -5699, -3787, -4743, 1.9, 0);
vex::vision::signature SIG_3 = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Vision = vex::vision (vex::PORT18, 150, GREEN_BROAD, GREEN_SHARP, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);