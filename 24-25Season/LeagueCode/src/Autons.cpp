#include "SubAutons.h"
#include "Autons.h"

std::vector<Jath::Point> testPathPoints = {Jath::Point(-0.934, -1.781, 66), Jath::Point(-0.921, 0.219, 64.572), Jath::Point(-0.898, 2.218, 63.143), Jath::Point(-0.857, 4.218, 61.715), Jath::Point(-0.793, 6.217, 60.286), Jath::Point(-0.715, 8.215, 58.858), Jath::Point(-0.615, 10.213, 57.43), Jath::Point(-0.489, 12.209, 56.001), Jath::Point(-0.342, 14.203, 54.573), Jath::Point(-0.174, 16.196, 53.144), Jath::Point(0.026, 18.186, 51.716), Jath::Point(0.256, 20.173, 50.288), Jath::Point(0.515, 22.156, 48.859), Jath::Point(0.806, 24.135, 47.431), Jath::Point(1.132, 26.108, 46.002), Jath::Point(1.497, 28.074, 44.574), Jath::Point(1.904, 30.032, 43.146), Jath::Point(2.357, 31.98, 41.717), Jath::Point(2.86, 33.916, 40.289), Jath::Point(3.418, 35.837, 38.86), Jath::Point(4.036, 37.739, 37.432), Jath::Point(4.717, 39.619, 36.004), Jath::Point(5.467, 41.473, 34.575), Jath::Point(6.289, 43.296, 33.147), Jath::Point(7.192, 45.08, 31.718), Jath::Point(8.189, 46.813, 30.29), Jath::Point(9.272, 48.494, 28.862), Jath::Point(10.459, 50.103, 27.433), Jath::Point(11.739, 51.639, 26.005), Jath::Point(13.13, 53.076, 24.576), Jath::Point(14.615, 54.415, 23.148), Jath::Point(16.192, 55.644, 21.72), Jath::Point(17.856, 56.753, 24.269), Jath::Point(19.595, 57.739, 26.818), Jath::Point(21.396, 58.609, 29.367), Jath::Point(23.246, 59.366, 31.917), Jath::Point(25.136, 60.021, 34.466), Jath::Point(27.054, 60.585, 37.015), Jath::Point(28.994, 61.073, 39.564), Jath::Point(30.948, 61.499, 42.114), Jath::Point(32.911, 61.879, 44.663), Jath::Point(34.88, 62.229, 47.212), Jath::Point(36.852, 62.567, 43.813), Jath::Point(38.822, 62.91, 40.414), Jath::Point(40.788, 63.277, 37.015), Jath::Point(42.745, 63.69, 33.616), Jath::Point(44.686, 64.171, 30.217), Jath::Point(46.602, 64.744, 26.818), Jath::Point(48.478, 65.435, 23.419), Jath::Point(50.296, 66.266, 20.02), Jath::Point(52.032, 67.259, 16.621), Jath::Point(53.654, 68.427, 13.222), Jath::Point(55.135, 69.769, 15.701), Jath::Point(56.458, 71.267, 18.179), Jath::Point(57.613, 72.898, 20.657), Jath::Point(58.605, 74.634, 23.136), Jath::Point(59.437, 76.452, 25.614), Jath::Point(60.129, 78.328, 28.093), Jath::Point(60.704, 80.243, 30.571), Jath::Point(61.162, 82.189, 33.05), Jath::Point(61.53, 84.155, 35.528), Jath::Point(61.821, 86.134, 38.006), Jath::Point(62.034, 88.122, 40.485), Jath::Point(62.185, 90.116, 42.963), Jath::Point(62.282, 92.114, 42.963), Jath::Point(62.33, 94.113, 42.963), Jath::Point(62.335, 96.113, 42.963), Jath::Point(62.301, 98.113, 42.963), Jath::Point(62.233, 100.111, 42.963), Jath::Point(62.134, 102.109, 42.963), Jath::Point(62.003, 104.105, 42.963), Jath::Point(61.844, 106.098, 42.963), Jath::Point(61.522, 109.553, 42.963), Jath::Point(61.522, 109.553, 0)};
Jath::Path testPath = Jath::Path::cm(testPathPoints);

void blueSoloAWP()
{
    logger.logStringEntry(Auton_Console, "BlueSoloAWP Started");

    // Grab Goal1
    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25), art::Tiles(-1.0));
    smartDrive.m_dir = art::Degrees(90);

    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-1));
    travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.driveFor(travel.magnitude() * -.78, -50);
    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");
    smartDrive.arcade(0, 0);

    // score preload
    intake.set(100);
    vex::wait(0.75, vex::sec);

    // Grab and score ring2
    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-2));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveFor(travel.magnitude() * .75, 35);
    smartDrive.arcade(0, 0);

    vex::wait(0.25, vex::sec);
    clamp.set(false);
    intake.set(-30);
    smartDrive.arcade(-20, 0);
    vex::wait(0.5, vex::sec);
    clamp.set(true);
    intake.set(100);
    smartDrive.arcade(0, 0);
    vex::wait(0.25, vex::sec);

    // drop goal & drive to centerline
    target = art::Vec2::XandY(art::Tiles(2), art::Tiles(0));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveForPID(travel.magnitude() * 0.85);
    clamp.set(false);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");
    smartDrive.arcade(0, 0);

    // Grab Goal2
    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(1));
    travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.driveFor(travel.magnitude() * -.80, -50);//disabled to hard code instead

    smartDrive.turnToPID(art::Degrees(-40) + art::Degrees(180));
    smartDrive.driveFor(art::Inches(-35), -50);
    smartDrive.arcade(0, 0);

    clamp.set(true);

    // // Grab ring2 and score

    smartDrive.turnToPID(art::Degrees(0));
    intake.set(100);
    smartDrive.driveFor(art::Inches(12), 75);
    smartDrive.turnToPID(art::Degrees(-15));
    smartDrive.arcade(0, 0);
    vex::wait(0.35, vex::sec);
    smartDrive.driveFor(art::Inches(-30), -100);
    smartDrive.arcade(0, 0);

    vex::wait(4, vex::sec);

    intake.set(0);
    smartDrive.arcade(0, 0);
}
void redSoloAWP()
{
    logger.logStringEntry(Auton_Console, "RedSoloAWP Started");
    double xFlip = -1.0;

    // Grab Goal1
    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25) * -1, art::Tiles(-1.0));
    smartDrive.m_dir = art::Degrees(90 * -1);

    target = art::Vec2::XandY(art::Tiles(1) * -1, art::Tiles(-1));
    travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.driveFor(travel.magnitude() * -.78, -50);
    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");
    smartDrive.arcade(0, 0);

    // score preload
    intake.set(100);
    vex::wait(0.75, vex::sec);

    // Grab and score ring2
    target = art::Vec2::XandY(art::Tiles(1) * -1, art::Tiles(-2));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveFor(travel.magnitude() * .5, 35);
    smartDrive.arcade(0, 0);

    vex::wait(0.25, vex::sec);
    clamp.set(false);
    intake.set(-30);
    smartDrive.arcade(-20, 0);
    vex::wait(0.5, vex::sec);
    clamp.set(true);
    intake.set(100);
    smartDrive.arcade(0, 0);
    vex::wait(0.25, vex::sec);

    // drop goal & drive to centerline
    target = art::Vec2::XandY(art::Tiles(2) * -1, art::Tiles(0));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveForPID(travel.magnitude() * 0.85);
    clamp.set(false);
    smartDrive.arcade(0, 0);

    // Grab Goal2
    target = art::Vec2::XandY(art::Tiles(1) * -1, art::Tiles(1));
    travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.driveFor(travel.magnitude() * -.80, -50);//disabled to hard code instead

    smartDrive.turnToPID(art::Degrees(-40 * -1) + art::Degrees(180));
    intake.set(-100);
    smartDrive.driveFor(art::Inches(-35), -50);
    smartDrive.arcade(0, 0);

    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");

    // // Grab ring2 and score

    smartDrive.turnToPID(art::Degrees(0));
    intake.set(100);
    smartDrive.driveFor(art::Inches(12), 75);
    smartDrive.turnToPID(art::Degrees(-15));
    smartDrive.arcade(0, 0);
    vex::wait(0.45, vex::sec);
    smartDrive.driveFor(art::Inches(-30), -100);
    smartDrive.arcade(0, 0);

    vex::wait(4, vex::sec);

    intake.set(0);
    smartDrive.arcade(0, 0);
}

void blueElims()
{
    logger.logStringEntry(Auton_Console, "BlueElims Started");

    int xFlip = 1.0;

    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25 * xFlip), art::Tiles(-1.0));
    smartDrive.m_dir = art::Degrees(90 * xFlip);

    target = art::Vec2::XandY(art::Tiles(1 * xFlip), art::Tiles(-1));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.driveFor(travel.magnitude() * -.78, -50);
    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");

    intake.set(100);
    smartDrive.arcade(0, 0);
    vex::wait(0.5, vex::sec);
    smartDrive.arcade(30, 0);
    vex::wait(0.45, vex::sec);

    // smartDrive.turnToPID(art::Degrees(125));
    // smartDrive.arcade(0,0); vex::wait(0.25,vex::sec);
    // clamp.set(false);
    // logger.logStringEntry(100, timePassed(), "Goal Dropped");

    // vex::wait(0.25, vex::sec);

    // target = art::Vec2::XandY(art::Tiles(0 * xFlip), art::Tiles(-2));
    // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.arcade(0,0); vex::wait(0.25,vex::sec);
    // smartDrive.driveFor(travel.magnitude() * -.75 , -35);
    // clamp.set(true);
    // logger.logStringEntry(100, timePassed(), "Goal Grabbed");
    // smartDrive.arcade(0, 0);

    // vex::wait(0.25, vex::sec);

    target = art::Vec2::XandY(art::Tiles(1 * xFlip), art::Tiles(-2));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.arcade(0, 0);
    vex::wait(0.25, vex::sec);

    intake.set(100);
    smartDrive.driveFor(travel.magnitude() * .7, 45);
    smartDrive.arcade(0, 0);

    intake.set(100);
    smartDrive.arcade(0, 50);

    vex::wait(0.5, vex::sec);

    smartDrive.arcade(0, 0);
    intake.set(100);

    vex::wait(1, vex::sec);
    intake.set(0);

    smartDrive.turnToPID(art::Degrees(-90) * xFlip);
    clamp.set(false);
    smartDrive.turnToPID(art::Degrees(90) * xFlip);

    smartDrive.driveFor(art::Inches(-2), -30);
}
void redElims()
{
    logger.logStringEntry(Auton_Console, "RedElims Started");

    int xFlip = -1.0;

    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25 * xFlip), art::Tiles(-1.0));
    smartDrive.m_dir = art::Degrees(90 * xFlip);

    target = art::Vec2::XandY(art::Tiles(1 * xFlip), art::Tiles(-1));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.driveFor(travel.magnitude() * -.78, -50);
    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");

    intake.set(100);
    smartDrive.arcade(0, 0);
    vex::wait(0.5, vex::sec);
    smartDrive.arcade(30, 0);
    vex::wait(0.45, vex::sec);

    // smartDrive.turnToPID(art::Degrees(125));
    // smartDrive.arcade(0,0); vex::wait(0.25,vex::sec);
    // clamp.set(false);
    // logger.logStringEntry(100, timePassed(), "Goal Dropped");

    // vex::wait(0.25, vex::sec);

    // target = art::Vec2::XandY(art::Tiles(0 * xFlip), art::Tiles(-2));
    // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.arcade(0,0); vex::wait(0.25,vex::sec);
    // smartDrive.driveFor(travel.magnitude() * -.75 , -35);
    // clamp.set(true);
    // logger.logStringEntry(100, timePassed(), "Goal Grabbed");
    // smartDrive.arcade(0, 0);

    // vex::wait(0.25, vex::sec);

    target = art::Vec2::XandY(art::Tiles(1 * xFlip), art::Tiles(-2));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.arcade(0, 0);
    vex::wait(0.25, vex::sec);

    intake.set(100);
    smartDrive.driveFor(travel.magnitude() * .7, 45);
    smartDrive.arcade(0, 0);

    intake.set(100);
    smartDrive.arcade(0, 50);

    vex::wait(0.5, vex::sec);

    smartDrive.arcade(0, 0);
    intake.set(100);

    vex::wait(1, vex::sec);
    intake.set(0);

    smartDrive.turnToPID(art::Degrees(-90) * xFlip);
    clamp.set(false);
    smartDrive.turnToPID(art::Degrees(90) * xFlip);

    smartDrive.driveFor(art::Inches(-2), -30);
}

std::vector<Jath::Point> redRushPath1Points = {Jath::Point(-141.052, -146.788, 101), Jath::Point(-139.053, -146.77, 101), Jath::Point(-137.053, -146.752, 100.129), Jath::Point(-135.053, -146.733, 99.883), Jath::Point(-133.053, -146.712, 98.765), Jath::Point(-131.053, -146.689, 97.648), Jath::Point(-129.053, -146.665, 96.53), Jath::Point(-127.053, -146.639, 95.413), Jath::Point(-125.053, -146.611, 94.296), Jath::Point(-123.054, -146.581, 93.178), Jath::Point(-121.054, -146.547, 92.061), Jath::Point(-119.054, -146.511, 90.943), Jath::Point(-117.055, -146.472, 89.826), Jath::Point(-115.055, -146.43, 88.709), Jath::Point(-113.056, -146.383, 87.591), Jath::Point(-111.056, -146.333, 86.474), Jath::Point(-109.057, -146.277, 85.356), Jath::Point(-107.058, -146.217, 84.239), Jath::Point(-105.059, -146.151, 83.122), Jath::Point(-103.06, -146.078, 82.004), Jath::Point(-101.062, -145.999, 80.887), Jath::Point(-99.064, -145.912, 79.77), Jath::Point(-97.066, -145.817, 78.652), Jath::Point(-95.069, -145.713, 77.535), Jath::Point(-93.072, -145.599, 76.417), Jath::Point(-91.076, -145.474, 75.3), Jath::Point(-89.081, -145.337, 74.183), Jath::Point(-87.086, -145.188, 73.065), Jath::Point(-85.093, -145.024, 71.948), Jath::Point(-83.101, -144.846, 70.83), Jath::Point(-81.11, -144.652, 69.713), Jath::Point(-79.122, -144.441, 68.596), Jath::Point(-77.135, -144.212, 70.306), Jath::Point(-75.15, -143.965, 72.015), Jath::Point(-73.168, -143.697, 73.725), Jath::Point(-71.189, -143.41, 75.435), Jath::Point(-69.213, -143.101, 77.145), Jath::Point(-67.24, -142.772, 78.855), Jath::Point(-65.271, -142.421, 80.565), Jath::Point(-63.306, -142.049, 82.275), Jath::Point(-61.345, -141.657, 83.985), Jath::Point(-59.388, -141.245, 85.695), Jath::Point(-57.435, -140.814, 87.405), Jath::Point(-55.486, -140.365, 89.115), Jath::Point(-53.541, -139.899, 89.115), Jath::Point(-51.6, -139.417, 89.115), Jath::Point(-49.662, -138.921, 89.115), Jath::Point(-47.728, -138.411, 89.115), Jath::Point(-45.798, -137.889, 89.115), Jath::Point(-43.87, -137.357, 89.115), Jath::Point(-41.945, -136.815, 89.115), Jath::Point(-40.022, -136.265, 89.115), Jath::Point(-38.101, -135.707, 89.115), Jath::Point(-36.182, -135.143, 89.115), Jath::Point(-34.265, -134.573, 89.115), Jath::Point(-32.35, -133.999, 89.115), Jath::Point(-30.435, -133.42, 89.115), Jath::Point(-28.522, -132.838, 89.115), Jath::Point(-26.609, -132.253, 89.115), Jath::Point(-24.697, -131.666, 89.115), Jath::Point(-22.658, -131.038, 89.115), Jath::Point(-22.658, -131.038, 0)};
Jath::Path redRushPath1 = Jath::Path::cm(redRushPath1Points);

void redRushAWP()
{
    // logger.logStringEntry(100, timePassed(), "RedRushAWP Started");

    // smartDrive.m_pos = art::Vec2::XandY(art::Tiles(-2.25), art::Tiles(-2.5));
    // smartDrive.m_dir = art::Degrees(90);

    // doinkerDeploy.set(true);

    // followPath(redRushPath1, art::Inches(15));

    // doinkerClamp.set(true);
    // smartDrive.driveForPID(art::Inches(-24));
    // doinkerClamp.set(false);
}

std::vector<Jath::Point> blueRushPath1Points = {Jath::Point(148.96, -151.675, 103), Jath::Point(146.961, -151.725, 101.465), Jath::Point(144.961, -151.771, 101.311), Jath::Point(142.962, -151.814, 101.149), Jath::Point(140.962, -151.853, 100.981), Jath::Point(138.962, -151.887, 100.804), Jath::Point(136.962, -151.918, 100.62), Jath::Point(134.963, -151.943, 100.428), Jath::Point(132.963, -151.962, 100.227), Jath::Point(130.963, -151.976, 100.019), Jath::Point(128.963, -151.983, 99.577), Jath::Point(126.963, -151.983, 99.343), Jath::Point(124.963, -151.975, 99.101), Jath::Point(122.963, -151.959, 98.85), Jath::Point(120.963, -151.934, 98.591), Jath::Point(118.963, -151.898, 98.047), Jath::Point(116.964, -151.852, 97.763), Jath::Point(114.965, -151.796, 97.472), Jath::Point(112.966, -151.727, 96.866), Jath::Point(110.968, -151.645, 96.552), Jath::Point(108.97, -151.549, 96.232), Jath::Point(106.973, -151.439, 95.575), Jath::Point(104.977, -151.312, 95.239), Jath::Point(102.982, -151.169, 94.899), Jath::Point(100.989, -151.008, 94.209), Jath::Point(98.997, -150.828, 93.861), Jath::Point(97.007, -150.628, 93.165), Jath::Point(95.019, -150.407, 92.819), Jath::Point(93.034, -150.164, 92.135), Jath::Point(91.052, -149.897, 91.8), Jath::Point(89.073, -149.607, 91.151), Jath::Point(87.098, -149.29, 90.839), Jath::Point(85.128, -148.949, 90.248), Jath::Point(83.162, -148.579, 89.972), Jath::Point(81.202, -148.181, 89.463), Jath::Point(79.248, -147.754, 89.233), Jath::Point(77.301, -147.297, 88.83), Jath::Point(75.361, -146.812, 88.657), Jath::Point(73.429, -146.293, 88.377), Jath::Point(71.506, -145.746, 88.187), Jath::Point(69.592, -145.165, 88.126), Jath::Point(67.688, -144.554, 88.078), Jath::Point(65.794, -143.911, 88.089), Jath::Point(63.911, -143.237, 88.183), Jath::Point(62.039, -142.533, 88.264), Jath::Point(60.179, -141.797, 88.494), Jath::Point(58.331, -141.032, 88.807), Jath::Point(56.496, -140.237, 88.992), Jath::Point(54.673, -139.415, 89.415), Jath::Point(52.863, -138.564, 89.651), Jath::Point(51.066, -137.686, 90.163), Jath::Point(49.282, -136.783, 90.437), Jath::Point(47.51, -135.855, 91.015), Jath::Point(45.752, -134.902, 91.316), Jath::Point(44.005, -133.928, 91.936), Jath::Point(42.272, -132.929, 92.253), Jath::Point(40.55, -131.912, 92.572), Jath::Point(38.841, -130.874, 93.215), Jath::Point(37.143, -129.817, 93.537), Jath::Point(35.456, -128.743, 93.857), Jath::Point(33.781, -127.65, 94.491), Jath::Point(32.116, -126.542, 94.802), Jath::Point(30.461, -125.419, 95.11), Jath::Point(28.816, -124.281, 95.71), Jath::Point(27.181, -123.129, 96.002), Jath::Point(25.555, -121.965, 96.288), Jath::Point(23.937, -120.789, 96.567), Jath::Point(22.329, -119.6, 97.105), Jath::Point(20.728, -118.401, 97.364), Jath::Point(19.136, -117.191, 97.615), Jath::Point(17.55, -115.972, 97.858), Jath::Point(15.971, -114.744, 98.095), Jath::Point(14.4, -113.507, 98.323), Jath::Point(11.424, -111.13, 98.758), Jath::Point(11.424, -111.13, 0)};
Jath::Path blueRushPath1 = Jath::Path::cm(blueRushPath1Points);

std::vector<Jath::Point> blueRushPath2Points = {Jath::Point(10.881, -111.13, 97), Jath::Point(10.931, -113.129, 78.947), Jath::Point(11.059, -115.124, 77.851), Jath::Point(11.278, -117.112, 75.607), Jath::Point(11.598, -119.086, 74.48), Jath::Point(12.021, -121.04, 72.284), Jath::Point(12.556, -122.967, 71.245), Jath::Point(13.213, -124.855, 69.37), Jath::Point(13.989, -126.698, 67.872), Jath::Point(14.889, -128.484, 67.3), Jath::Point(15.92, -130.197, 66.565), Jath::Point(17.073, -131.83, 66.407), Jath::Point(18.342, -133.375, 66.817), Jath::Point(19.721, -134.823, 67.735), Jath::Point(21.199, -136.17, 69.062), Jath::Point(22.766, -137.411, 70.684), Jath::Point(24.414, -138.545, 71.569), Jath::Point(26.128, -139.574, 73.418), Jath::Point(27.899, -140.503, 75.298), Jath::Point(29.716, -141.337, 77.139), Jath::Point(31.572, -142.082, 78.89), Jath::Point(33.461, -142.738, 79.722), Jath::Point(35.377, -143.313, 81.287), Jath::Point(37.312, -143.816, 82.714), Jath::Point(39.264, -144.25, 83.375), Jath::Point(41.231, -144.615, 84.595), Jath::Point(43.207, -144.923, 85.685), Jath::Point(45.191, -145.175, 86.184), Jath::Point(47.181, -145.372, 87.097), Jath::Point(49.175, -145.524, 87.906), Jath::Point(51.172, -145.627, 88.274), Jath::Point(53.171, -145.688, 88.947), Jath::Point(55.171, -145.71, 89.252), Jath::Point(57.171, -145.693, 89.81), Jath::Point(59.17, -145.642, 90.063), Jath::Point(61.168, -145.555, 90.524), Jath::Point(63.165, -145.439, 90.929), Jath::Point(65.159, -145.29, 91.112), Jath::Point(67.152, -145.114, 91.445), Jath::Point(69.141, -144.909, 91.595), Jath::Point(71.128, -144.679, 91.865), Jath::Point(73.112, -144.424, 91.986), Jath::Point(75.092, -144.144, 92.202), Jath::Point(77.069, -143.842, 92.385), Jath::Point(79.042, -143.516, 92.465), Jath::Point(81.012, -143.169, 92.601), Jath::Point(82.978, -142.801, 92.658), Jath::Point(84.939, -142.412, 92.748), Jath::Point(86.897, -142.002, 92.808), Jath::Point(88.851, -141.574, 92.835), Jath::Point(90.8, -141.125, 92.836), Jath::Point(92.744, -140.657, 92.807), Jath::Point(94.683, -140.168, 92.733), Jath::Point(96.618, -139.66, 92.605), Jath::Point(98.547, -139.132, 92.406), Jath::Point(100.469, -138.582, 91.925), Jath::Point(102.386, -138.008, 91.422), Jath::Point(104.294, -137.41, 90.202), Jath::Point(105.512, -137.012, 89.6), Jath::Point(105.512, -137.012, 0)};
Jath::Path blueRushPath2 = Jath::Path::cm(blueRushPath2Points);

void blueRushAWP()
{
    // logger.logStringEntry(100, timePassed(), "BlueRushAWP Started");

    // smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25), art::Tiles(-2.5));
    smartDrive.m_dir = art::Degrees(-90);

    // doinkerDeploy.set(true);

    // followPath(blueRushPath1, art::Inches(15));

    // doinkerClamp.set(true);
    // // smartDrive.driveForPID(art::Inches(-24));
    // followPathRev(blueRushPath2, art::Inches(15));
    // smartDrive.driveForPID(art::Inches(-15)); //<

    // smartDrive.turnToPID(art::Degrees(-90));

    // doinkerClamp.set(false);
    // doinkerDeploy.set(false);

    // smartDrive.driveForPID(art::Inches(-5));

    // smartDrive.turnToPID(art::Degrees(0));
    // smartDrive.driveForPID(art::Inches(15));

    doinkerDeploy.set(false);
    doinkerDeploy.set(true);

    smartDrive.driveFor(art::Inches(33), 100);
    doinkerClamp.set(true);

    smartDrive.driveForPID(art::Inches(-48));
    smartDrive.turnToPID(art::Degrees(180));

    doinkerClamp.set(false);
    smartDrive.driveForPID(art::Inches(-5));
    doinkerDeploy.set(false);

    smartDrive.m_pos = art::Vec2::XandY(art::Inches(gpsSensor.xPosition(vex::inches)), art::Inches(gpsSensor.yPosition(vex::inches)));
    smartDrive.m_dir = art::Degrees(gpsSensor.heading(vex::degrees));

    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-1));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction() + art::Degrees(180));

    smartDrive.driveForPID(art::Inches(-24));

    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");

    arm.set(100);
    vex::wait(0.25, vex::sec);

    smartDrive.driveForPID(art::Inches(15));

    arm.set(0);
    arm.stop(vex::hold);

    intake.set(100);

    smartDrive.m_pos = art::Vec2::XandY(art::Inches(gpsSensor.xPosition(vex::inches)), art::Inches(gpsSensor.yPosition(vex::inches)));
    smartDrive.m_dir = art::Degrees(gpsSensor.heading(vex::degrees));

    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-2));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction() - art::Degrees(5));

    smartDrive.driveForPID(travel.magnitude());
}

void redAWPGoalFirstNeg()
{
    logger.logStringEntry(Auton_Console, "RedAWP Started - 1");
    int redFlip = -1;

    arm.set(100);
    logger.logStringEntry(Auton_Console, "RedAWP Started - 2");
    vex::wait(.5, vex::sec);

    arm.set(0);
    arm.stop(vex::hold);

    // Grab Goal1
    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(redFlip * 2.25), art::Tiles(-1.0));
    smartDrive.m_dir = art::Degrees(redFlip * 90);

    target = art::Vec2::XandY(art::Tiles(redFlip * 1), art::Tiles(-1));
    travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.driveFor(travel.magnitude() * -.78, -50);
    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");
    smartDrive.arcade(0, 0);

    // score preload
    intake.set(100);
    vex::wait(0.75, vex::sec);

    // Grab and score ring2
    target = art::Vec2::XandY(art::Tiles(redFlip * 1), art::Tiles(-2));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveFor(travel.magnitude() * .75, 35);
    smartDrive.arcade(0, 0);

    vex::wait(5, vex::seconds);

    intake.set(0);
    arm.set(50);
    vex::wait(0.5, vex::sec);

    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.arcade(-25, 0);
    vex::wait(3, vex::sec);
    smartDrive.arcade(0, 0);
}
void blueAWPGoalFirstNeg()
{
    logger.logStringEntry(Auton_Console, "BlueAWP Started - 1");

    arm.set(100);
    vex::wait(.5, vex::sec);
    logger.logStringEntry(Auton_Console, "BlueAWP Started - 2");

    arm.set(0);
    arm.stop(vex::hold);

    // Grab Goal1
    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25), art::Tiles(-1.0));
    smartDrive.m_dir = art::Degrees(90);

    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-1));
    travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.driveFor(travel.magnitude() * -.78, -50);
    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");
    smartDrive.arcade(0, 0);

    // score preload
    intake.set(100);
    vex::wait(0.75, vex::sec);

    // Grab and score ring2
    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-2));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveFor(travel.magnitude() * .75, 35);
    smartDrive.arcade(0, 0);

    vex::wait(5, vex::seconds);

    intake.set(0);
    arm.set(50);
    vex::wait(0.5, vex::sec);

    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.arcade(-25, 0);
    vex::wait(3, vex::sec);
    smartDrive.arcade(0, 0);
}

void redAWPStakeFirstPos()
{
    vex::wait(4, vex::sec);

    smartDrive.driveForPID(art::Inches(2));

    arm.set(100);
    vex::wait(1.25, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-16));

    arm.set(-100);
    vex::wait(1.25 / 4.f, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    target = art::Vec2::XandY(art::Tiles(-1), art::Tiles(-1));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.driveFor(travel.magnitude() * -.9, -50);]

    smartDrive.driveForPID(-travel.magnitude());
    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");
    smartDrive.arcade(0, 0);

    vex::wait(0.25, vex::sec);

    target = art::Vec2::XandY(art::Tiles(-1), art::Tiles(-2));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    intake.set(100);
    smartDrive.driveForPID(travel.magnitude());
    smartDrive.arcade(0, 0);
    smartDrive.driveForPID(art::Inches(-5));

    vex::wait(1.0, vex::seconds);

    // intake.set(0);
    // arm.set(-50);
    // vex::wait(0.5, vex::sec);

    // arm.set(0);
    // arm.stop(vex::hold);

    target = art::Vec2::XandY(art::Tiles(-1), art::Tiles(0));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());

    smartDrive.arcade(35, 0);
    vex::wait(3, vex::sec);
    smartDrive.arcade(0, 0);
}
void blueAWPStakeFirstPos()
{
    vex::wait(4, vex::sec);

    smartDrive.driveForPID(art::Inches(2));

    arm.set(100);
    vex::wait(1.25, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-16));

    arm.set(-100);
    vex::wait(1.25 / 4.f, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-1));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.driveFor(travel.magnitude() * -.9, -50);]

    smartDrive.driveForPID(-travel.magnitude());
    clamp.set(true);
    logger.logStringEntry(Auton_Console, "Goal Grabbed");
    smartDrive.arcade(0, 0);

    vex::wait(0.25, vex::sec);

    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-2));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    intake.set(100);
    smartDrive.driveForPID(travel.magnitude());
    smartDrive.arcade(0, 0);
    smartDrive.driveForPID(art::Inches(-5));

    vex::wait(1.0, vex::seconds);

    // intake.set(0);
    // arm.set(-50);
    // vex::wait(0.5, vex::sec);

    // arm.set(0);
    // arm.stop(vex::hold);

    target = art::Vec2::XandY(art::Tiles(1), art::Tiles(0));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());

    smartDrive.arcade(35, 0);
    vex::wait(3, vex::sec);
    smartDrive.arcade(0, 0);
}

bool AutonArmPosRunning = true;
int autonArmPos()
{
    logger.logStringEntry(Auton_Console, "Auton Arm Macro started");

    AutonArmPosRunning = true;
    // armTarget = art::Degrees(10);
    armPID.reset();

    while (AutonArmPosRunning)
    {
        if (abs(shortestTurnPath(armTarget - art::Degrees(armRot.angle())).degrees()) >= 0.5)
        {
            if (shortestTurnPath(armTarget - art::Degrees(armRot.angle())).degrees() > 30 && armTarget.degrees() < 50)
            {
                armOut = armPID.calculate(shortestTurnPath(armTarget - art::Degrees(armRot.angle())));
                arm.set(-armOut);
            }
            else
            {
                armOut = armPID.calculate(shortestTurnPath(armTarget - art::Degrees(armRot.angle())));
                arm.set(armOut);
            }
        }
        else
        {
            arm.set(0);
            arm.stop(vex::hold);
        }

        vex::wait(20, vex::msec);
    }

    logger.logStringEntry(Auton_Console, "Auton Arm Macro ended");

    arm.set(0);
    arm.stop(vex::hold);
    return 1;
}

void winfred_redAWPStakeFirstPos()
{
    smartDrive.driveForPID(art::Inches(2));

    arm.set(100);
    vex::wait(1.25, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-16));

    arm.set(-100);
    vex::wait(1.25 / 4.f, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(-2), art::Tiles(-1)));

    smartDrive.turnToPID(art::Degrees(0));
    intake.set(100);
    smartDrive.driveForPID(art::Tiles(2));
    smartDrive.arcade(0, 0);
}
void winfred_blueAWPStakeFirstPos()
{
    smartDrive.driveForPID(art::Inches(2));

    arm.set(100);
    vex::wait(1.25, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-20));

    armTarget = art::Degrees(0);
    vex::thread armControl(autonArmPos);

    // driveTowardPointRev(art::Vec2::XandY(
    //     art::Tiles(2), art::Tiles(-1)));

    resetPositionFromGPS();

    target = art::Vec2::XandY(art::Tiles(2), art::Tiles(0));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    intake.set(100);
    smartDrive.driveFor(art::Tiles(1.5), 35);
    intake.set(0);
    AutonArmPosRunning = false;

    resetPositionFromGPS();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(2), art::Tiles(-1)));
    resetPositionFromGPS();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(1), art::Tiles(-1)));

    clamp.set(true);
    intake.set(100);

    vex::wait(1, vex::sec);
    armTarget = art::Degrees(130);
    armControl = vex::thread(autonArmPos);

    resetPositionFromGPS();

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1), art::Tiles(-2)));

    smartDrive.driveForPID(art::Inches(-14));

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1), art::Tiles(0)));

    smartDrive.arcade(0, 0);
    AutonArmPosRunning = false;
}

void JathsSketchyFullFlippingAWP()
{
    double xSign = 1.0;
    double ySign = 1.0;

    if (smartDrive.m_pos.x < 0)
    {
        xSign = -1.0;
    }
    if (smartDrive.m_pos.y < 0)
    {
        ySign = -1.0;
    }

    smartDrive.driveForPID(art::Inches(2));

    arm.set(100);
    vex::wait(1.25, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-20));

    armTarget = art::Degrees(0);
    vex::thread armControl(autonArmPos);

    resetPositionFromGPS();

    target = art::Vec2::XandY(art::Tiles(2 * xSign), art::Tiles(0 * ySign));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    intake.set(100);
    smartDrive.driveFor(art::Tiles(1.5), 35);
    intake.set(0);
    AutonArmPosRunning = false;

    resetPositionFromGPS();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(2 * xSign), art::Tiles(1 * ySign)));
    resetPositionFromGPS();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(1 * ySign)));

    clamp.set(true);
    intake.set(100);

    vex::wait(1, vex::sec);
    armTarget = art::Degrees(130);
    armControl = vex::thread(autonArmPos);

    resetPositionFromGPS();

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(2 * ySign)));

    smartDrive.driveForPID(art::Inches(-14));

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(0 * ySign)));

    smartDrive.arcade(0, 0);
    AutonArmPosRunning = false;
}

void negStackedRings()
{
    double xSign = 1.0;

    if (smartDrive.m_pos.x < 0)
    {
        xSign = -1.0;
    }

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(0.95 * xSign), art::Tiles(1)));

    // target = art::Vec2::XandY(art::Tiles(1 * xSign), art::Tiles(1));
    // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.driveForPID();

    clamp.set(true);

    intake.set(100);

    smartDrive.arcade(0, 0);
    vex::wait(0.25, vex::sec);

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(2)));

    smartDrive.driveForPID(art::Inches(-10));

    smartDrive.arcade(0, 0);
    vex::wait(0.35, vex::sec);
    resetPositionFromGPS();

    driveTowardPoint(art::Vec2::XandY(
        art::Inches(10 * xSign), art::Inches(48 - 2)));

    smartDrive.driveForPID(art::Inches(-12));
    smartDrive.arcade(0, 0);
    vex::wait(0.35, vex::sec);
    resetPositionFromGPS();

    driveTowardPoint(art::Vec2::XandY(
        art::Inches(8 * xSign), art::Inches(48 + 4)));
    
    smartDrive.driveForPID(art::Inches(-12));

    armTarget = art::Degrees(120);
    vex::thread armControl(autonArmPos);

    driveTowardPoint(art::Vec2::XandY(
        art::Inches(24 * xSign), art::Inches(0)));

    smartDrive.arcade(0, 0);
}
void negStackedRingsStakeFirst()
{
    double xSign = 1.0;

    if (smartDrive.m_pos.x < 0)
    {
        xSign = -1.0;
    }

    smartDrive.driveForPID(art::Inches(2));

    arm.set(100);
    vex::wait(1.25, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-20));

    armTarget = art::Degrees(0);
    vex::thread armControl(autonArmPos);

    negStackedRings();
}

std::vector<Jath::Point> rings1PathPoints = {
    Jath::Point(-118.646, 55.537, 8), Jath::Point(-118.7, 53.537, 74.144), Jath::Point(-118.717, 51.537, 74.023), Jath::Point(-118.694, 49.538, 73.902), Jath::Point(-118.628, 47.539, 73.781), Jath::Point(-118.514, 45.542, 72.955), Jath::Point(-118.34, 43.55, 72.016), Jath::Point(-118.112, 41.563, 70.986), Jath::Point(-117.811, 39.586, 68.622), Jath::Point(-117.439, 37.621, 67.271), Jath::Point(-116.975, 35.676, 64.19), Jath::Point(-116.414, 33.756, 60.559), Jath::Point(-115.742, 31.873, 56.352), Jath::Point(-114.94, 30.042, 51.597), Jath::Point(-113.991, 28.283, 46.412), Jath::Point(-112.879, 26.622, 41.04), Jath::Point(-111.587, 25.097, 33.497), Jath::Point(-110.11, 23.751, 29.547), Jath::Point(-108.455, 22.632, 26.419), Jath::Point(-106.651, 21.773, 27.278), Jath::Point(-104.739, 21.195, 31.589), Jath::Point(-102.763, 20.897, 35.676), Jath::Point(-100.764, 20.858, 42.481), Jath::Point(-98.774, 21.04, 49.079), Jath::Point(-96.811, 21.417, 53.038), Jath::Point(-94.885, 21.956, 58.143), Jath::Point(-93.005, 22.635, 60.988), Jath::Point(-91.17, 23.431, 63.423), Jath::Point(-89.382, 24.326, 65.491), Jath::Point(-87.641, 25.31, 67.238), Jath::Point(-85.946, 26.371, 69.354), Jath::Point(-84.295, 27.5, 70.482), Jath::Point(-82.687, 28.689, 70.391), Jath::Point(-81.122, 29.935, 70.27), Jath::Point(-79.599, 31.23, 70.149), Jath::Point(-78.115, 32.571, 70.028), Jath::Point(-76.671, 33.955, 69.907), Jath::Point(-75.266, 35.378, 69.786), Jath::Point(-73.9, 36.839, 69.665), Jath::Point(-72.573, 38.335, 69.544), Jath::Point(-71.286, 39.866, 65.894), Jath::Point(-70.038, 41.428, 62.244), Jath::Point(-68.828, 43.021, 58.594), Jath::Point(-67.66, 44.644, 54.944), Jath::Point(-66.533, 46.297, 51.295), Jath::Point(-65.448, 47.977, 47.645), Jath::Point(-64.405, 49.683, 43.995), Jath::Point(-63.41, 51.418, 43.891), Jath::Point(-62.46, 53.178, 43.787), Jath::Point(-61.559, 54.963, 43.683), Jath::Point(-60.707, 56.773, 43.579), Jath::Point(-59.912, 58.608, 43.475), Jath::Point(-59.16, 60.461, 43.37), Jath::Point(-58.381, 62.303, 43.267), Jath::Point(-57.542, 64.118, 43.163), Jath::Point(-56.645, 65.906, 43.059), Jath::Point(-55.689, 67.662, 42.955), Jath::Point(-54.675, 69.386, 45.084), Jath::Point(-53.602, 71.073, 47.213), Jath::Point(-52.477, 72.727, 49.342), Jath::Point(-51.293, 74.339, 51.472), Jath::Point(-50.061, 75.914, 53.601), Jath::Point(-48.782, 77.452, 55.73), Jath::Point(-47.456, 78.949, 57.859), Jath::Point(-46.091, 80.411, 59.988), Jath::Point(-44.691, 81.838, 62.117), Jath::Point(-43.256, 83.232, 64.246), Jath::Point(-41.794, 84.596, 66.375), Jath::Point(-40.308, 85.934, 68.504), Jath::Point(-38.802, 87.251, 65.993), Jath::Point(-37.279, 88.547, 63.481), Jath::Point(-35.745, 89.83, 60.969), Jath::Point(-34.203, 91.104, 58.458), Jath::Point(-32.657, 92.372, 55.946), Jath::Point(-31.11, 93.64, 53.434), Jath::Point(-29.566, 94.911, 50.923), Jath::Point(-28.028, 96.191, 48.411), Jath::Point(-26.502, 97.483, 45.899), Jath::Point(-24.99, 98.792, 43.388), Jath::Point(-23.496, 100.122, 40.876), Jath::Point(-22.023, 101.475, 43.435), Jath::Point(-20.577, 102.856, 45.994), Jath::Point(-19.159, 104.267, 48.553), Jath::Point(-17.773, 105.709, 51.112), Jath::Point(-16.426, 107.186, 53.671), Jath::Point(-15.116, 108.698, 56.231), Jath::Point(-13.849, 110.245, 58.79), Jath::Point(-12.628, 111.829, 61.349), Jath::Point(-11.452, 113.447, 63.908), Jath::Point(-10.33, 115.102, 66.467), Jath::Point(-9.254, 116.788, 69.026), Jath::Point(-8.235, 118.509, 71.585), Jath::Point(-7.265, 120.257, 72.683), Jath::Point(-6.351, 122.036, 71.605), Jath::Point(-5.488, 123.841, 69.066), Jath::Point(-4.677, 125.668, 66.526), Jath::Point(-3.92, 127.52, 63.987), Jath::Point(-3.212, 129.39, 61.448), Jath::Point(-2.55, 131.277, 58.908), Jath::Point(-1.94, 133.182, 56.369), Jath::Point(-1.376, 135.101, 53.83), Jath::Point(-0.855, 137.032, 51.29), Jath::Point(-0.376, 138.973, 48.751), Jath::Point(0.062, 140.925, 48.751), Jath::Point(0.461, 142.884, 48.751), Jath::Point(0.822, 144.851, 48.751), Jath::Point(1.146, 146.825, 48.751), Jath::Point(1.436, 148.804, 48.751), Jath::Point(1.693, 150.787, 48.751), Jath::Point(1.92, 152.774, 48.751), Jath::Point(2.116, 154.765, 48.751), Jath::Point(2.283, 156.758, 48.751), Jath::Point(2.423, 158.753, 48.751), Jath::Point(2.536, 160.749, 48.751), Jath::Point(2.626, 162.747, 48.751), Jath::Point(2.692, 164.746, 48.751), Jath::Point(2.736, 166.746, 48.751), Jath::Point(2.76, 168.746, 48.751), Jath::Point(2.761, 170.746, 48.751), Jath::Point(2.74, 172.746, 48.751), Jath::Point(2.702, 174.745, 48.751), Jath::Point(2.648, 176.744, 48.751), Jath::Point(2.576, 178.743, 48.751), Jath::Point(2.484, 180.741, 48.751), Jath::Point(2.377, 182.738, 48.751), Jath::Point(2.258, 184.734, 48.75), Jath::Point(2.085, 187.244, 48.751), Jath::Point(2.085, 187.244, 0), 
};
Jath::Path rings1Path = Jath::Path::cm(rings1PathPoints);

std::vector<Jath::Point> rings1_5PathPoints = {
    Jath::Point(8.671, 160.354, 8), Jath::Point(8.412, 158.37, 83.233), Jath::Point(8.144, 156.389, 83.026), Jath::Point(7.866, 154.408, 82.555), Jath::Point(7.569, 152.43, 81.803), Jath::Point(7.261, 150.454, 81.05), Jath::Point(6.94, 148.48, 80.298), Jath::Point(6.602, 146.509, 79.546), Jath::Point(6.248, 144.54, 78.794), Jath::Point(5.878, 142.575, 78.042), Jath::Point(5.494, 140.612, 77.289), Jath::Point(5.091, 138.653, 76.537), Jath::Point(4.667, 136.699, 75.785), Jath::Point(4.224, 134.748, 75.033), Jath::Point(3.763, 132.802, 74.281), Jath::Point(3.28, 130.861, 73.528), Jath::Point(2.776, 128.926, 72.776), Jath::Point(2.249, 126.997, 72.024), Jath::Point(1.696, 125.075, 71.272), Jath::Point(1.116, 123.161, 70.52), Jath::Point(0.509, 121.255, 69.767), Jath::Point(-0.127, 119.359, 69.015), Jath::Point(-0.794, 117.473, 68.263), Jath::Point(-1.493, 115.599, 67.511), Jath::Point(-2.227, 113.739, 66.759), Jath::Point(-3, 111.895, 66.006), Jath::Point(-3.814, 110.068, 65.254), Jath::Point(-4.669, 108.26, 64.502), Jath::Point(-5.569, 106.474, 63.75), Jath::Point(-6.515, 104.712, 62.998), Jath::Point(-7.522, 102.984, 62.245), Jath::Point(-8.582, 101.288, 61.493), Jath::Point(-9.704, 99.633, 60.741), Jath::Point(-10.894, 98.026, 59.648), Jath::Point(-12.155, 96.473, 55.618), Jath::Point(-13.491, 94.986, 53.439), Jath::Point(-14.913, 93.58, 48.794), Jath::Point(-16.42, 92.267, 43.862), Jath::Point(-18.017, 91.063, 38.824), Jath::Point(-19.703, 89.989, 33.937), Jath::Point(-21.477, 89.068, 29.517), Jath::Point(-23.331, 88.319, 25.903), Jath::Point(-25.25, 87.763, 23.4), Jath::Point(-27.22, 87.421, 22.14), Jath::Point(-29.215, 87.296, 22.998), Jath::Point(-31.212, 87.384, 25.051), Jath::Point(-33.188, 87.687, 29.787), Jath::Point(-35.124, 88.184, 33.606), Jath::Point(-37.007, 88.854, 37.628), Jath::Point(-38.828, 89.68, 43.581), Jath::Point(-40.578, 90.648, 47.201), Jath::Point(-42.256, 91.735, 46.449), Jath::Point(-43.862, 92.926, 45.697), Jath::Point(-45.397, 94.208, 44.945), Jath::Point(-46.861, 95.57, 44.192), Jath::Point(-48.257, 97.001, 43.44), Jath::Point(-49.587, 98.495, 42.688), Jath::Point(-50.854, 100.043, 41.936), Jath::Point(-52.055, 101.641, 41.184), Jath::Point(-53.196, 103.284, 40.431), Jath::Point(-54.279, 104.965, 39.679), Jath::Point(-55.305, 106.682, 39.718), Jath::Point(-56.273, 108.432, 39.757), Jath::Point(-57.184, 110.212, 39.796), Jath::Point(-58.043, 112.018, 39.834), Jath::Point(-58.847, 113.849, 39.873), Jath::Point(-59.595, 115.704, 39.912), Jath::Point(-60.293, 117.578, 39.951), Jath::Point(-60.935, 119.472, 39.98), Jath::Point(-61.555, 121.374, 40.028), Jath::Point(-62.182, 123.273, 40.067), Jath::Point(-62.818, 125.169, 40.106), Jath::Point(-63.464, 127.062, 40.144), Jath::Point(-64.124, 128.95, 40.183), Jath::Point(-64.796, 130.834, 45.943), Jath::Point(-65.483, 132.712, 51.703), Jath::Point(-66.184, 134.585, 57.463), Jath::Point(-66.902, 136.452, 63.222), Jath::Point(-67.638, 138.311, 68.982), Jath::Point(-68.394, 140.163, 74.742), Jath::Point(-69.173, 142.005, 78.798), Jath::Point(-69.976, 143.837, 77.868), Jath::Point(-70.807, 145.656, 75.637), Jath::Point(-71.672, 147.459, 74.301), Jath::Point(-72.572, 149.245, 72.792), Jath::Point(-73.511, 151.011, 69.158), Jath::Point(-74.502, 152.748, 66.981), Jath::Point(-75.543, 154.455, 61.764), Jath::Point(-76.654, 156.118, 58.663), Jath::Point(-77.841, 157.728, 51.336), Jath::Point(-79.118, 159.266, 42.385), Jath::Point(-80.502, 160.709, 31.846), Jath::Point(-82.009, 162.022, 14.091), Jath::Point(-83.66, 163.148, 14), Jath::Point(-85.449, 164.038, 14), Jath::Point(-87.356, 164.631, 14), Jath::Point(-89.335, 164.897, 14), Jath::Point(-91.333, 164.852, 14), Jath::Point(-93.308, 164.546, 30.891), Jath::Point(-95.242, 164.04, 46.89), Jath::Point(-97.131, 163.385, 55.948), Jath::Point(-98.982, 162.628, 67.119), Jath::Point(-100.803, 161.801, 73.165), Jath::Point(-102.603, 160.93, 80.502), Jath::Point(-104.39, 160.031, 80.502), Jath::Point(-106.171, 159.121, 80.502), Jath::Point(-107.952, 158.212, 80.502), Jath::Point(-109.739, 157.314, 79.985), Jath::Point(-111.536, 156.436, 77.521), Jath::Point(-113.347, 155.586, 75.298), Jath::Point(-115.173, 154.772, 73.287), Jath::Point(-117.018, 153.999, 71.472), Jath::Point(-118.881, 153.273, 69.849), Jath::Point(-120.765, 152.601, 68.422), Jath::Point(-122.668, 151.985, 67.203), Jath::Point(-124.59, 151.434, 66.676), Jath::Point(-126.53, 150.95, 65.799), Jath::Point(-128.486, 150.533, 65.171), Jath::Point(-130.456, 150.188, 64.955), Jath::Point(-132.438, 149.92, 64.723), Jath::Point(-134.428, 149.723, 64.76), Jath::Point(-136.425, 149.605, 64.878), Jath::Point(-138.424, 149.56, 65.301), Jath::Point(-140.423, 149.59, 65.602), Jath::Point(-142.421, 149.692, 66.361), Jath::Point(-144.988, 149.927, 66.81), Jath::Point(-144.988, 149.927, 0), 
};
Jath::Path rings1_5Path = Jath::Path::cm(rings1_5PathPoints);

std::vector<Jath::Point> rings1_6PathPoints = {
    Jath::Point(-153.768, 150.476, 57.74), Jath::Point(-151.768, 150.467, 57.745), Jath::Point(-149.768, 150.459, 57.745), Jath::Point(-147.768, 150.45, 57.745), Jath::Point(-145.768, 150.442, 57.745), Jath::Point(-143.768, 150.433, 57.745), Jath::Point(-141.768, 150.425, 57.745), Jath::Point(-139.768, 150.416, 57.745), Jath::Point(-137.768, 150.408, 57.745), Jath::Point(-135.768, 150.399, 57.745), Jath::Point(-133.768, 150.391, 57.745), Jath::Point(-131.768, 150.382, 57.745), Jath::Point(-129.769, 150.373, 57.745), Jath::Point(-127.769, 150.365, 57.745), Jath::Point(-125.769, 150.356, 57.745), Jath::Point(-123.769, 150.348, 57.745), Jath::Point(-121.769, 150.339, 57.745), Jath::Point(-119.769, 150.331, 57.745), Jath::Point(-117.769, 150.322, 57.745), Jath::Point(-115.769, 150.314, 57.745), Jath::Point(-113.769, 150.305, 57.745), Jath::Point(-111.769, 150.297, 57.745), Jath::Point(-109.769, 150.288, 57.745), Jath::Point(-107.769, 150.28, 57.745), Jath::Point(-105.769, 150.271, 57.745), Jath::Point(-103.769, 150.263, 57.745), Jath::Point(-101.769, 150.254, 57.745), Jath::Point(-99.769, 150.246, 57.745), Jath::Point(-97.769, 150.237, 57.745), Jath::Point(-95.769, 150.229, 57.745), Jath::Point(-93.769, 150.22, 57.745), Jath::Point(-91.769, 150.212, 57.745), Jath::Point(-89.769, 150.203, 57.745), Jath::Point(-87.769, 150.195, 57.745), Jath::Point(-85.769, 150.186, 57.745), Jath::Point(-83.769, 150.178, 57.745), Jath::Point(-81.769, 150.169, 57.745), Jath::Point(-79.769, 150.161, 57.745), Jath::Point(-77.769, 150.152, 57.745), Jath::Point(-75.769, 150.144, 57.745), Jath::Point(-73.769, 150.135, 57.745), Jath::Point(-71.769, 150.127, 57.745), Jath::Point(-69.769, 150.118, 57.745), Jath::Point(-67.769, 150.11, 57.745), Jath::Point(-65.769, 150.101, 57.745), Jath::Point(-63.769, 150.093, 57.745), Jath::Point(-61.769, 150.084, 57.745), Jath::Point(-59.769, 150.076, 57.745), Jath::Point(-57.769, 150.067, 57.745), Jath::Point(-55.769, 150.059, 57.745), Jath::Point(-53.769, 150.05, 57.745), Jath::Point(-51.769, 150.042, 57.745), Jath::Point(-49.769, 150.033, 57.745), Jath::Point(-47.769, 150.025, 57.745), Jath::Point(-45.769, 150.016, 57.745), Jath::Point(-43.769, 150.008, 57.745), Jath::Point(-41.769, 149.999, 57.745), Jath::Point(-39.769, 149.991, 57.745), Jath::Point(-37.769, 149.982, 57.745), Jath::Point(-35.769, 149.973, 57.745), Jath::Point(-33.769, 149.965, 57.745), Jath::Point(-31.769, 149.956, 57.745), Jath::Point(-29.769, 149.948, 57.745), Jath::Point(-27.769, 149.939, 57.745), Jath::Point(-24.805, 149.927, 57.74), Jath::Point(-24.805, 149.927, 0)
};
Jath::Path rings1_6Path = Jath::Path::cm(rings1_6PathPoints);

std::vector<Jath::Point> rings1_75PathPoints = {
    Jath::Point(-21.512, 148.28, 52.76), Jath::Point(-22.671, 146.65, 54.903), Jath::Point(-23.771, 144.981, 59.112), Jath::Point(-24.818, 143.276, 62.561), Jath::Point(-25.819, 141.545, 68.641), Jath::Point(-26.785, 139.794, 75.486), Jath::Point(-27.729, 138.031, 73.583), Jath::Point(-28.667, 136.264, 71.68), Jath::Point(-29.616, 134.504, 67.81), Jath::Point(-30.596, 132.76, 57.762), Jath::Point(-31.626, 131.046, 47.593), Jath::Point(-32.726, 129.376, 37.851), Jath::Point(-33.913, 127.767, 29.272), Jath::Point(-35.2, 126.236, 22.694), Jath::Point(-36.594, 124.803, 22), Jath::Point(-38.094, 123.481, 22), Jath::Point(-39.693, 122.281, 22), Jath::Point(-41.378, 121.204, 25.637), Jath::Point(-43.136, 120.252, 29.914), Jath::Point(-44.952, 119.416, 37.07), Jath::Point(-46.815, 118.688, 41.967), Jath::Point(-48.713, 118.057, 45.041), Jath::Point(-50.637, 117.514, 43.138), Jath::Point(-52.582, 117.049, 43.522), Jath::Point(-54.543, 116.653, 43.906), Jath::Point(-56.514, 116.318, 44.289), Jath::Point(-58.494, 116.037, 44.673), Jath::Point(-60.481, 115.808, 45.057), Jath::Point(-62.472, 115.619, 45.441), Jath::Point(-64.467, 115.473, 45.825), Jath::Point(-66.463, 115.358, 46.208), Jath::Point(-68.462, 115.279, 47.468), Jath::Point(-70.461, 115.228, 48.727), Jath::Point(-72.461, 115.203, 49.987), Jath::Point(-74.461, 115.202, 51.247), Jath::Point(-76.461, 115.225, 52.506), Jath::Point(-78.46, 115.268, 53.766), Jath::Point(-80.459, 115.33, 55.025), Jath::Point(-82.458, 115.409, 56.285), Jath::Point(-84.455, 115.505, 57.544), Jath::Point(-86.452, 115.615, 58.804), Jath::Point(-88.448, 115.741, 60.063), Jath::Point(-90.444, 115.879, 61.323), Jath::Point(-92.438, 116.03, 62.583), Jath::Point(-94.431, 116.192, 59.512), Jath::Point(-96.424, 116.365, 56.442), Jath::Point(-98.415, 116.549, 53.372), Jath::Point(-100.406, 116.742, 50.302), Jath::Point(-102.396, 116.945, 47.232), Jath::Point(-104.384, 117.157, 44.162), Jath::Point(-106.372, 117.377, 41.091), Jath::Point(-108.359, 117.605, 38.021), Jath::Point(-110.345, 117.839, 38.021), Jath::Point(-112.331, 118.082, 38.021), Jath::Point(-114.315, 118.332, 38.021), Jath::Point(-116.299, 118.587, 38.021), Jath::Point(-118.281, 118.848, 38.02), Jath::Point(-120.263, 119.117, 38.021), Jath::Point(-122.258, 119.198, 38.021), Jath::Point(-124.258, 119.202, 38.021), Jath::Point(-126.258, 119.205, 38.021), Jath::Point(-128.258, 119.209, 38.021), Jath::Point(-130.258, 119.213, 38.021), Jath::Point(-132.258, 119.217, 38.021), Jath::Point(-134.258, 119.22, 38.021), Jath::Point(-136.258, 119.224, 38.021), Jath::Point(-138.258, 119.228, 38.021), Jath::Point(-140.258, 119.232, 38.021), Jath::Point(-142.258, 119.236, 38.021), Jath::Point(-144.258, 119.239, 38.021), Jath::Point(-146.258, 119.243, 38.021), Jath::Point(-148.258, 119.247, 38.021), Jath::Point(-150.258, 119.251, 38.021), Jath::Point(-152.258, 119.254, 38.021), Jath::Point(-154.258, 119.258, 38.021), Jath::Point(-156.258, 119.262, 38.021), Jath::Point(-158.258, 119.266, 38.021), Jath::Point(-160.258, 119.27, 38.021), Jath::Point(-162.258, 119.273, 38.021), Jath::Point(-164.258, 119.277, 38.021), Jath::Point(-166.258, 119.281, 38.021), Jath::Point(-168.258, 119.285, 38.021), Jath::Point(-170.258, 119.288, 38.021), Jath::Point(-172.258, 119.292, 38.021), Jath::Point(-174.258, 119.296, 38.021), Jath::Point(-176.258, 119.3, 38.021), Jath::Point(-178.258, 119.304, 38.021), Jath::Point(-180.258, 119.307, 38.021), Jath::Point(-182.258, 119.311, 38.021), Jath::Point(-184.258, 119.315, 38.021), Jath::Point(-186.258, 119.319, 38.021), Jath::Point(-188.258, 119.322, 38.021), Jath::Point(-190.258, 119.326, 38.021), Jath::Point(-191.56, 119.329, 38.02), Jath::Point(-191.56, 119.329, 0), 
};
Jath::Path rings1_75Path = Jath::Path::cm(rings1_75PathPoints);

std::vector<Jath::Point> goal3PathPoints = {
    Jath::Point(-177.88, -0.435, 90.46), Jath::Point(-176.216, -1.544, 90.462), Jath::Point(-174.556, -2.659, 90.24), Jath::Point(-172.9, -3.78, 90.008), Jath::Point(-171.25, -4.912, 90.008), Jath::Point(-169.607, -6.051, 89.766), Jath::Point(-167.969, -7.199, 89.514), Jath::Point(-166.336, -8.354, 89.252), Jath::Point(-164.711, -9.52, 89.252), Jath::Point(-163.093, -10.695, 88.98), Jath::Point(-161.481, -11.88, 88.697), Jath::Point(-159.877, -13.074, 88.406), Jath::Point(-158.28, -14.278, 88.104), Jath::Point(-156.691, -15.493, 88.104), Jath::Point(-155.112, -16.72, 87.795), Jath::Point(-153.542, -17.958, 87.477), Jath::Point(-151.98, -19.208, 87.151), Jath::Point(-150.429, -20.47, 86.82), Jath::Point(-148.888, -21.745, 86.484), Jath::Point(-147.358, -23.033, 86.144), Jath::Point(-145.839, -24.334, 85.803), Jath::Point(-144.332, -25.649, 85.463), Jath::Point(-142.837, -26.978, 85.126), Jath::Point(-141.356, -28.322, 84.795), Jath::Point(-139.889, -29.681, 84.164), Jath::Point(-138.437, -31.057, 83.871), Jath::Point(-137, -32.448, 83.6), Jath::Point(-135.579, -33.855, 83.355), Jath::Point(-134.173, -35.278, 82.963), Jath::Point(-132.787, -36.719, 82.829), Jath::Point(-131.417, -38.176, 82.744), Jath::Point(-130.065, -39.65, 82.749), Jath::Point(-128.733, -41.142, 82.853), Jath::Point(-127.418, -42.648, 83.298), Jath::Point(-126.122, -44.172, 83.654), Jath::Point(-124.843, -45.71, 84.666), Jath::Point(-123.581, -47.261, 85.333), Jath::Point(-122.335, -48.825, 87.015), Jath::Point(-121.101, -50.399, 89.18), Jath::Point(-119.878, -51.981, 91.835), Jath::Point(-118.661, -53.569, 93.745), Jath::Point(-117.446, -55.157, 91.506), Jath::Point(-116.228, -56.744, 87.642), Jath::Point(-115.001, -58.323, 83.574), Jath::Point(-113.758, -59.89, 79.458), Jath::Point(-112.493, -61.439, 75.472), Jath::Point(-111.2, -62.965, 71.807), Jath::Point(-109.874, -64.462, 68.648), Jath::Point(-108.51, -65.924, 66.151), Jath::Point(-107.104, -67.347, 64.428), Jath::Point(-105.656, -68.726, 63.532), Jath::Point(-104.165, -70.059, 63.45), Jath::Point(-102.632, -71.343, 64.113), Jath::Point(-101.059, -72.579, 65.403), Jath::Point(-99.45, -73.767, 67.175), Jath::Point(-97.806, -74.906, 68.194), Jath::Point(-96.132, -75.999, 70.405), Jath::Point(-94.432, -77.052, 72.736), Jath::Point(-92.705, -78.061, 73.91), Jath::Point(-90.958, -79.036, 76.22), Jath::Point(-89.191, -79.972, 77.337), Jath::Point(-87.408, -80.878, 78.421), Jath::Point(-85.609, -81.752, 80.466), Jath::Point(-83.797, -82.598, 81.421), Jath::Point(-81.974, -83.419, 82.329), Jath::Point(-80.14, -84.218, 83.189), Jath::Point(-78.296, -84.992, 84.766), Jath::Point(-76.443, -85.746, 85.484), Jath::Point(-74.583, -86.481, 86.157), Jath::Point(-72.717, -87.199, 86.786), Jath::Point(-70.844, -87.9, 87.373), Jath::Point(-68.965, -88.587, 87.921), Jath::Point(-67.082, -89.259, 88.43), Jath::Point(-65.194, -89.918, 88.904), Jath::Point(-63.301, -90.565, 89.345), Jath::Point(-61.405, -91.201, 89.75), Jath::Point(-59.505, -91.826, 89.754), Jath::Point(-57.532, -92.145, 90.704), Jath::Point(-55.553, -92.436, 90.337), Jath::Point(-53.573, -92.716, 90.15), Jath::Point(-51.592, -92.988, 89.768), Jath::Point(-49.609, -93.25, 89.576), Jath::Point(-47.625, -93.5, 89.19), Jath::Point(-45.639, -93.739, 88.807), Jath::Point(-43.652, -93.966, 88.434), Jath::Point(-41.663, -94.18, 88.253), Jath::Point(-39.674, -94.38, 87.906), Jath::Point(-37.682, -94.566, 87.586), Jath::Point(-35.69, -94.737, 87.3), Jath::Point(-33.696, -94.893, 87.056), Jath::Point(-31.701, -95.033, 86.861), Jath::Point(-29.704, -95.157, 86.72), Jath::Point(-27.707, -95.264, 86.639), Jath::Point(-25.709, -95.354, 86.622), Jath::Point(-23.711, -95.427, 86.672), Jath::Point(-21.711, -95.483, 86.788), Jath::Point(-19.712, -95.523, 86.971), Jath::Point(-17.712, -95.546, 87.216), Jath::Point(-15.712, -95.553, 87.52), Jath::Point(-13.712, -95.545, 87.876), Jath::Point(-11.712, -95.523, 88.277), Jath::Point(-9.712, -95.487, 88.716), Jath::Point(-7.713, -95.438, 89.183), Jath::Point(-5.714, -95.377, 89.669), Jath::Point(-3.715, -95.305, 90.167), Jath::Point(-1.717, -95.223, 90.667), Jath::Point(0.281, -95.133, 91.161), Jath::Point(2.279, -95.034, 91.644), Jath::Point(4.276, -94.928, 92.109), Jath::Point(6.273, -94.816, 92.552), Jath::Point(8.269, -94.699, 92.764), Jath::Point(10.265, -94.577, 93.166), Jath::Point(12.261, -94.451, 93.539), Jath::Point(14.257, -94.322, 93.714), Jath::Point(16.253, -94.19, 94.04), Jath::Point(18.248, -94.056, 94.335), Jath::Point(20.244, -93.921, 94.47), Jath::Point(22.239, -93.784, 94.719), Jath::Point(24.234, -93.647, 95), Jath::Point(26.23, -93.509, 84.934), Jath::Point(28.225, -93.372, 74.869), Jath::Point(30.22, -93.234, 64.803), Jath::Point(32.216, -93.097, 54.737), Jath::Point(34.211, -92.961, 44.672), Jath::Point(36.206, -92.825, 34.606), Jath::Point(38.202, -92.691, 24.54), Jath::Point(40.197, -92.557, 27.496), Jath::Point(42.193, -92.425, 30.452), Jath::Point(44.189, -92.295, 33.407), Jath::Point(46.185, -92.166, 36.363), Jath::Point(48.18, -92.038, 39.318), Jath::Point(50.176, -91.912, 42.274), Jath::Point(52.173, -91.788, 45.23), Jath::Point(54.169, -91.666, 48.185), Jath::Point(56.165, -91.546, 48.185), Jath::Point(58.162, -91.427, 48.185), Jath::Point(60.158, -91.31, 48.18), Jath::Point(62.157, -91.261, 48.185), Jath::Point(64.157, -91.231, 48.185), Jath::Point(66.156, -91.165, 48.185), Jath::Point(68.153, -91.059, 48.185), Jath::Point(70.147, -90.907, 48.185), Jath::Point(72.137, -90.708, 48.185), Jath::Point(74.121, -90.461, 48.185), Jath::Point(76.099, -90.162, 48.185), Jath::Point(78.065, -89.797, 48.185), Jath::Point(80.019, -89.372, 48.185), Jath::Point(81.957, -88.878, 48.185), Jath::Point(83.874, -88.309, 48.185), Jath::Point(85.765, -87.659, 48.185), Jath::Point(87.627, -86.928, 48.185), Jath::Point(89.448, -86.101, 48.185), Jath::Point(91.223, -85.181, 48.185), Jath::Point(92.945, -84.165, 48.185), Jath::Point(94.605, -83.05, 48.185), Jath::Point(96.194, -81.836, 48.185), Jath::Point(97.705, -80.526, 48.185), Jath::Point(99.132, -79.126, 48.185), Jath::Point(100.471, -77.641, 48.185), Jath::Point(101.721, -76.08, 48.185), Jath::Point(102.884, -74.453, 48.185), Jath::Point(103.962, -72.769, 48.185), Jath::Point(104.96, -71.036, 48.185), Jath::Point(105.884, -69.262, 48.185), Jath::Point(106.744, -67.457, 48.185), Jath::Point(107.549, -65.626, 48.185), Jath::Point(108.308, -63.776, 48.185), Jath::Point(109.03, -61.911, 48.185), Jath::Point(109.726, -60.035, 48.185), Jath::Point(110.403, -58.154, 48.185), Jath::Point(111.073, -56.269, 48.185), Jath::Point(111.744, -54.385, 48.185), Jath::Point(112.428, -52.506, 48.185), Jath::Point(113.134, -50.635, 48.185), Jath::Point(113.872, -48.776, 48.185), Jath::Point(114.652, -46.934, 48.185), Jath::Point(115.486, -45.117, 48.185), Jath::Point(116.383, -43.329, 48.185), Jath::Point(117.353, -41.58, 48.185), Jath::Point(118.402, -39.878, 48.185), Jath::Point(119.542, -38.235, 48.185), Jath::Point(120.777, -36.662, 48.185), Jath::Point(122.107, -35.169, 48.185), Jath::Point(123.532, -33.767, 48.185), Jath::Point(125.048, -32.463, 48.185), Jath::Point(126.65, -31.266, 48.185), Jath::Point(128.328, -30.178, 48.185), Jath::Point(130.072, -29.201, 48.185), Jath::Point(131.873, -28.332, 48.185), Jath::Point(134.341, -27.329, 48.18), Jath::Point(134.341, -27.329, 0), 
};
Jath::Path goal3Path = Jath::Path::cm(goal3PathPoints);

std::vector<Jath::Point> RingsFinal1Points = {
    Jath::Point(120.477, -0.435, 97.64), Jath::Point(120.31, -2.428, 97.644), Jath::Point(120.133, -4.42, 97.46), Jath::Point(119.948, -6.411, 96.369), Jath::Point(119.753, -8.402, 94.825), Jath::Point(119.549, -10.391, 93.281), Jath::Point(119.333, -12.38, 91.737), Jath::Point(119.107, -14.367, 90.194), Jath::Point(118.868, -16.352, 88.65), Jath::Point(118.616, -18.337, 87.106), Jath::Point(118.351, -20.319, 85.562), Jath::Point(118.073, -22.299, 84.018), Jath::Point(117.78, -24.278, 82.475), Jath::Point(117.471, -26.254, 80.931), Jath::Point(117.146, -28.227, 79.387), Jath::Point(116.802, -30.198, 77.843), Jath::Point(116.44, -32.164, 76.3), Jath::Point(116.057, -34.127, 74.756), Jath::Point(115.654, -36.086, 73.212), Jath::Point(115.227, -38.04, 71.668), Jath::Point(114.777, -39.989, 70.124), Jath::Point(114.298, -41.931, 68.581), Jath::Point(113.79, -43.865, 67.037), Jath::Point(113.252, -45.791, 65.493), Jath::Point(112.678, -47.707, 63.949), Jath::Point(112.066, -49.611, 60.747), Jath::Point(111.414, -51.502, 57.545), Jath::Point(110.716, -53.376, 54.343), Jath::Point(109.967, -55.23, 51.141), Jath::Point(109.163, -57.062, 47.939), Jath::Point(108.296, -58.864, 44.736), Jath::Point(107.358, -60.63, 41.534), Jath::Point(106.343, -62.353, 38.332), Jath::Point(105.242, -64.022, 38.248), Jath::Point(104.044, -65.623, 38.163), Jath::Point(102.737, -67.136, 38.079), Jath::Point(101.316, -68.543, 32.963), Jath::Point(99.774, -69.815, 23.157), Jath::Point(98.112, -70.925, 18), Jath::Point(96.334, -71.839, 18), Jath::Point(94.462, -72.538, 18), Jath::Point(92.519, -73.008, 18), Jath::Point(90.535, -73.25, 22.822), Jath::Point(88.536, -73.278, 32.11), Jath::Point(86.544, -73.108, 37.321), Jath::Point(84.574, -72.77, 37.237), Jath::Point(82.633, -72.289, 37.152), Jath::Point(80.727, -71.684, 37.068), Jath::Point(78.857, -70.975, 36.984), Jath::Point(77.022, -70.179, 38.869), Jath::Point(75.222, -69.309, 40.754), Jath::Point(73.453, -68.375, 42.639), Jath::Point(71.715, -67.386, 44.524), Jath::Point(70.004, -66.351, 46.41), Jath::Point(68.319, -65.273, 48.295), Jath::Point(66.658, -64.16, 50.18), Jath::Point(65.017, -63.016, 52.065), Jath::Point(63.397, -61.844, 53.95), Jath::Point(61.794, -60.648, 55.83), Jath::Point(60.263, -59.364, 57.721), Jath::Point(58.805, -57.995, 59.606), Jath::Point(57.347, -56.626, 61.491), Jath::Point(55.889, -55.257, 63.376), Jath::Point(54.432, -53.887, 69.647), Jath::Point(52.975, -52.517, 75.918), Jath::Point(51.518, -51.147, 82.188), Jath::Point(50.062, -49.776, 88.459), Jath::Point(48.607, -48.404, 94.729), Jath::Point(47.153, -47.031, 101), Jath::Point(45.7, -45.656, 100.431), Jath::Point(44.249, -44.279, 99.863), Jath::Point(42.801, -42.901, 99.294), Jath::Point(41.355, -41.518, 98.725), Jath::Point(39.913, -40.132, 98.157), Jath::Point(38.477, -38.74, 97.588), Jath::Point(37.047, -37.342, 97.019), Jath::Point(35.626, -35.935, 96.451), Jath::Point(34.212, -34.52, 95.882), Jath::Point(32.807, -33.097, 95.313), Jath::Point(31.407, -31.669, 94.744), Jath::Point(30.011, -30.236, 94.176), Jath::Point(28.617, -28.802, 93.607), Jath::Point(27.224, -27.367, 93.038), Jath::Point(25.83, -25.933, 88.994), Jath::Point(24.436, -24.5, 84.949), Jath::Point(23.04, -23.067, 80.904), Jath::Point(21.643, -21.636, 76.859), Jath::Point(20.245, -20.205, 72.814), Jath::Point(18.846, -18.776, 68.769), Jath::Point(17.446, -17.348, 64.725), Jath::Point(16.044, -15.921, 60.68), Jath::Point(14.642, -14.495, 56.635), Jath::Point(13.239, -13.07, 52.59), Jath::Point(11.835, -11.646, 48.545), Jath::Point(10.43, -10.223, 44.5), Jath::Point(9.024, -8.8, 40.456), Jath::Point(7.617, -7.378, 36.411), Jath::Point(6.21, -5.957, 36.411), Jath::Point(4.802, -4.536, 36.411), Jath::Point(3.394, -3.117, 36.411), Jath::Point(1.985, -1.697, 36.411), Jath::Point(0.575, -0.278, 36.411), Jath::Point(-0.835, 1.14, 36.411), Jath::Point(-2.246, 2.558, 36.411), Jath::Point(-3.657, 3.975, 36.411), Jath::Point(-5.068, 5.392, 36.411), Jath::Point(-6.48, 6.808, 36.411), Jath::Point(-7.893, 8.224, 36.411), Jath::Point(-9.306, 9.64, 36.411), Jath::Point(-10.719, 11.055, 36.411), Jath::Point(-12.132, 12.47, 36.411), Jath::Point(-14.265, 14.603, 36.41), Jath::Point(-14.265, 14.603, 0), 
};
Jath::Path RingsFinal1 = Jath::Path::cm(RingsFinal1Points);

std::vector<Jath::Point> RingsFinal2Points = {
    Jath::Point(-12.46, -11.864, 9), Jath::Point(-11.034, -10.461, 92.415), Jath::Point(-9.608, -9.059, 91.435), Jath::Point(-8.182, -7.657, 90.455), Jath::Point(-6.756, -6.255, 89.475), Jath::Point(-5.33, -4.852, 88.495), Jath::Point(-3.904, -3.45, 87.515), Jath::Point(-2.478, -2.048, 86.535), Jath::Point(-1.052, -0.646, 85.556), Jath::Point(0.374, 0.757, 84.576), Jath::Point(1.8, 2.159, 83.596), Jath::Point(3.226, 3.561, 82.616), Jath::Point(4.652, 4.964, 81.636), Jath::Point(6.078, 6.366, 80.656), Jath::Point(7.504, 7.768, 79.676), Jath::Point(8.931, 9.17, 78.696), Jath::Point(10.357, 10.573, 77.716), Jath::Point(11.783, 11.975, 76.736), Jath::Point(13.209, 13.377, 75.756), Jath::Point(14.635, 14.78, 74.776), Jath::Point(16.061, 16.182, 73.796), Jath::Point(17.487, 17.584, 72.816), Jath::Point(18.913, 18.986, 71.836), Jath::Point(20.339, 20.389, 70.856), Jath::Point(21.765, 21.791, 69.876), Jath::Point(23.191, 23.193, 68.896), Jath::Point(24.617, 24.596, 67.916), Jath::Point(26.043, 25.998, 66.936), Jath::Point(27.469, 27.4, 65.956), Jath::Point(28.895, 28.802, 64.976), Jath::Point(30.321, 30.205, 63.996), Jath::Point(31.747, 31.607, 63.017), Jath::Point(33.173, 33.009, 62.037), Jath::Point(34.599, 34.411, 61.057), Jath::Point(36.025, 35.814, 60.077), Jath::Point(37.451, 37.216, 59.097), Jath::Point(38.878, 38.618, 58.117), Jath::Point(40.304, 40.021, 57.137), Jath::Point(41.73, 41.423, 56.157), Jath::Point(43.156, 42.825, 55.177), Jath::Point(44.582, 44.227, 54.197), Jath::Point(46.008, 45.63, 53.217), Jath::Point(47.434, 47.032, 52.237), Jath::Point(48.86, 48.434, 51.257), Jath::Point(50.286, 49.837, 50.277), Jath::Point(51.712, 51.239, 49.297), Jath::Point(53.138, 52.641, 48.317), Jath::Point(54.564, 54.043, 47.337), Jath::Point(55.99, 55.446, 49.22), Jath::Point(57.416, 56.848, 51.103), Jath::Point(58.842, 58.25, 52.986), Jath::Point(60.088, 59.788, 54.86), Jath::Point(61.029, 61.553, 56.752), Jath::Point(61.937, 63.335, 58.634), Jath::Point(62.814, 65.133, 60.517), Jath::Point(63.651, 66.949, 62.4), Jath::Point(64.451, 68.782, 64.283), Jath::Point(65.208, 70.633, 66.166), Jath::Point(65.915, 72.504, 68.049), Jath::Point(66.57, 74.393, 64.177), Jath::Point(67.169, 76.301, 60.305), Jath::Point(67.705, 78.228, 56.433), Jath::Point(68.173, 80.172, 52.561), Jath::Point(68.568, 82.133, 48.689), Jath::Point(68.883, 84.108, 44.817), Jath::Point(69.111, 86.094, 40.945), Jath::Point(69.249, 88.089, 37.073), Jath::Point(69.292, 90.089, 39.683), Jath::Point(69.239, 92.088, 42.293), Jath::Point(69.086, 94.082, 44.904), Jath::Point(68.838, 96.066, 47.514), Jath::Point(68.498, 98.037, 50.124), Jath::Point(68.07, 99.99, 52.734), Jath::Point(67.564, 101.925, 55.345), Jath::Point(66.989, 103.841, 57.955), Jath::Point(66.357, 105.738, 60.565), Jath::Point(65.679, 107.619, 63.175), Jath::Point(64.966, 109.488, 63.175), Jath::Point(64.232, 111.348, 63.175), Jath::Point(63.487, 113.205, 63.175), Jath::Point(62.744, 115.061, 63.175), Jath::Point(62.014, 116.923, 63.175), Jath::Point(61.307, 118.794, 63.175), Jath::Point(60.633, 120.677, 63.175), Jath::Point(60.003, 122.575, 63.175), Jath::Point(59.426, 124.49, 63.175), Jath::Point(58.908, 126.422, 62.487), Jath::Point(58.456, 128.37, 60.971), Jath::Point(58.076, 130.333, 59.375), Jath::Point(57.77, 132.31, 58.776), Jath::Point(57.544, 134.297, 58.561), Jath::Point(57.395, 136.291, 58.85), Jath::Point(57.317, 139.12, 59.86), Jath::Point(57.317, 139.12,0 ), 
};
Jath::Path RingsFinal2 = Jath::Path::cm(RingsFinal2Points);

int intakeAntiJam(){

    double lastcmd = intake.get();

    while (true)
    {

        if(intake.get() != lastcmd){
            lastcmd = intake.get();
            vex::wait(0.25, vex::sec);
        }

        if(intake.get() > 50 && intake.velocity(vex::pct) < 5){
            double temp = intake.get();

            intake.set(-100);
            vex::wait(0.25, vex::sec);

            intake.set(temp);
        }

        vex::wait(100, vex::msec);
    }
    return 1;
}

void skills()
{
    vex::task antiJamTask(intakeAntiJam);

    intake.set(75);

    vex::wait(10, vex::sec);

    // smartDrive.m_pos = art::Vec2::XandY(art::Tiles(-2.5), art::Tiles(0));
    // smartDrive.m_dir = art::Degrees(-90);

    // // resetPositionFromGPS();

    // arm.set(100);
    // vex::wait(1, vex::seconds);
    // arm.set(0);
    // arm.stop(vex::hold);

    // smartDrive.driveForPID(art::Inches(-5));

    // armTarget = art::Degrees(0);
    // vex::thread armControl(autonArmPos);

    // // followPathRev(goal1Path, art::Inches(13));

    // driveTowardPointRev(art::Vec2::XandY(
    //     art::Tiles(-2.15), art::Tiles(0.95)
    // ));

    // // maybe add additional drive
    // smartDrive.driveForPID(art::Inches(-2));
    // clamp.set(true);
    // smartDrive.arcade(0,0);

    // vex::wait(0.75, vex::sec);

    // resetPositionFromGPS();

    // intake.set(100);
    // followPath(rings1Path, art::Inches(13));

    // smartDrive.driveForPID(art::Inches(-3));
    // smartDrive.turnForPID(art::Degrees(165));
    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec);
    // resetPositionFromGPS();

    // followPath(rings1_5Path, art::Inches(13));

    // followPathRev(rings1_6Path, art::Inches(13));

    // followPath(rings1_75Path, art::Inches(13));

    // target = art::Vec2::XandY(art::Tiles(-2.75), art::Tiles(2.75));
    // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.driveForPID(-travel.magnitude() * .9);

    // clamp.set(false);
    // intake.set(0);

    // smartDrive.driveForPID(art::Inches(24));

    // smartDrive.arcade(0,0);
    // vex::wait(0.5, vex::sec);
    // resetPositionFromGPS();

    // driveTowardPointRev(art::Vec2::XandY(
    //     art::Tiles(-2), art::Tiles(0)
    // ));

    // smartDrive.arcade(0,0);
    // vex::wait(0.5, vex::sec);
    // resetPositionFromGPS();

    // driveTowardPointRev(art::Vec2::XandY(
    //     art::Tiles(-2), art::Tiles(-0.95)
    // ));

    // // maybe add additional drive
    // smartDrive.driveForPID(art::Inches(-2));
    // clamp.set(true);
    // smartDrive.arcade(0,0);

    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec);
    // resetPositionFromGPS();

    // intake.set(100);
    // followPath_flipY(rings1Path, art::Inches(13));

    // smartDrive.driveForPID(art::Inches(-3));
    // smartDrive.turnForPID(art::Degrees(-15));
    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec); logger.logStringEntry(Auton_Console, "Waiting to reset");
    // resetPositionFromGPS();

    // followPath_flipY(rings1_5Path, art::Inches(13));

    // followPathRev_flipY(rings1_6Path, art::Inches(13));

    // followPath_flipY(rings1_75Path, art::Inches(13));

    // target = art::Vec2::XandY(art::Tiles(-2.75), art::Tiles(2.75 * -1.0));
    // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.driveForPID(-travel.magnitude() * .9);

    // clamp.set(false);
    // intake.set(0);

    // smartDrive.driveForPID(art::Inches(48));

    // resetPositionFromGPS(); // Delete this

    // smartDrive.turnToPID(art::Degrees(135));

    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec);
    // resetPositionFromGPS();

    // followPath(goal3Path, art::Inches(13));

    // smartDrive.arcade(0,0);
    // // vex::wait(0.75, vex::sec);
    // // resetPositionFromGPS();

    // // target = art::Vec2::XandY(art::Tiles(2.5), art::Tiles(-1.0));
    // // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(art::Degrees(135));
    // intake.set(-100);
    // smartDrive.arcade(75, 0);

    // vex::wait(3, vex::sec);

    // smartDrive.driveForPID(art::Inches(-30));
    // smartDrive.turnToPID(art::Degrees(60));
    // intake.set(0);

    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec);
    // resetPositionFromGPS();

    // driveTowardPointRev(art::Vec2::XandY(
    //     art::Tiles(2), art::Tiles(0.0)
    // ));

    // // maybe add additional drive
    // smartDrive.driveForPID(art::Inches(-2));
    // clamp.set(true);
    // smartDrive.arcade(0,0);

    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec);
    // resetPositionFromGPS();
    
    // intake.set(100);

    // followPath(RingsFinal1, art::Inches(13));
    // smartDrive.turnToPID(art::Degrees(45));
    // followPath(RingsFinal2, art::Inches(13));

    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec);
    // resetPositionFromGPS();

    // driveTowardPoint(art::Vec2::XandY(
    //     art::Tiles(2),art::Tiles(1.95)
    // ));

    // smartDrive.driveForPID(art::Inches(-15));

    // driveTowardPoint(art::Vec2::XandY(
    //     art::Tiles(2),art::Tiles(2.5)
    // ));

    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec);
    // resetPositionFromGPS();

    // smartDrive.turnForPID(art::Degrees(-135));
    // smartDrive.arcade(-75, 0);
    // vex::wait(3, vex::sec);

    // clamp.set(false);
    // intake.set(0);

    // smartDrive.driveForPID(art::Inches(24));

    // smartDrive.arcade(0, 0);
}
