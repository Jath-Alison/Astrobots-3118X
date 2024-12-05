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
    armControl = vex::thread (autonArmPos);

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

    if(smartDrive.m_pos.x < 0){xSign = -1.0;}
    if(smartDrive.m_pos.y < 0){ySign = -1.0;}

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
    armControl = vex::thread (autonArmPos);

    resetPositionFromGPS();

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(2 * ySign)));

    smartDrive.driveForPID(art::Inches(-14));

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(0 * ySign)));

    smartDrive.arcade(0, 0);
    AutonArmPosRunning = false;
}

std::vector<Jath::Point> goal1PathPoints = {
    Jath::Point(-176.354, -1.238, 10), Jath::Point(-174.354, -1.276, 99.317), Jath::Point(-172.356, -1.365, 97.635), Jath::Point(-170.36, -1.495, 95.952), Jath::Point(-168.367, -1.657, 94.269), Jath::Point(-166.376, -1.844, 92.587), Jath::Point(-164.386, -2.047, 90.904), Jath::Point(-162.397, -2.259, 89.221), Jath::Point(-160.409, -2.473, 87.539), Jath::Point(-158.42, -2.68, 85.856), Jath::Point(-156.429, -2.874, 84.173), Jath::Point(-154.436, -3.045, 82.491), Jath::Point(-152.441, -3.185, 80.808), Jath::Point(-150.444, -3.283, 79.125), Jath::Point(-148.444, -3.329, 77.443), Jath::Point(-146.445, -3.308, 75.76), Jath::Point(-144.447, -3.207, 74.078), Jath::Point(-142.457, -3.008, 72.395), Jath::Point(-140.483, -2.691, 70.712), Jath::Point(-138.536, -2.237, 69.03), Jath::Point(-136.632, -1.627, 67.347), Jath::Point(-134.795, -0.839, 65.664), Jath::Point(-133.05, 0.137, 63.982), Jath::Point(-131.425, 1.301, 62.299), Jath::Point(-129.943, 2.642, 62.764), Jath::Point(-128.62, 4.141, 63.23), Jath::Point(-127.458, 5.768, 63.696), Jath::Point(-126.458, 7.498, 64.161), Jath::Point(-125.603, 9.306, 64.627), Jath::Point(-124.882, 11.171, 65.092), Jath::Point(-124.281, 13.078, 65.558), Jath::Point(-123.893, 15.036, 66.02), Jath::Point(-123.632, 17.019, 66.489), Jath::Point(-123.373, 19.002, 66.955), Jath::Point(-123.117, 20.985, 67.42), Jath::Point(-122.863, 22.969, 67.886), Jath::Point(-122.614, 24.954, 68.351), Jath::Point(-122.37, 26.939, 68.817), Jath::Point(-122.131, 28.924, 71.424), Jath::Point(-121.901, 30.911, 74.031), Jath::Point(-121.678, 32.899, 76.638), Jath::Point(-121.467, 34.887, 79.246), Jath::Point(-121.268, 36.877, 81.853), Jath::Point(-121.082, 38.869, 84.46), Jath::Point(-120.911, 40.862, 87.067), Jath::Point(-120.757, 42.856, 89.674), Jath::Point(-120.62, 44.851, 92.282), Jath::Point(-120.499, 46.847, 94.889), Jath::Point(-120.394, 48.844, 97.496), Jath::Point(-120.305, 50.842, 100.103), Jath::Point(-120.228, 52.841, 100.103), Jath::Point(-120.163, 54.84, 100.103), Jath::Point(-120.108, 56.839, 100.103), Jath::Point(-120.061, 58.839, 100.103), Jath::Point(-120.021, 60.838, 100.103), Jath::Point(-119.987, 62.838, 100.103), Jath::Point(-119.957, 64.838, 100.103), Jath::Point(-119.928, 66.964, 100.10), Jath::Point(-119.928, 66.964, 0), 
};
Jath::Path goal1Path = Jath::Path::cm(goal1PathPoints);

std::vector<Jath::Point> rings1PathPoints = {
    Jath::Point(-119.577, 59.417, 10), Jath::Point(-118.464, 61.079, 100.454), Jath::Point(-117.338, 62.732, 99.908), Jath::Point(-116.196, 64.374, 93.931), Jath::Point(-115.033, 66.001, 92.134), Jath::Point(-113.846, 67.611, 90.811), Jath::Point(-112.628, 69.198, 88.601), Jath::Point(-111.377, 70.757, 86.07), Jath::Point(-110.084, 72.284, 83.156), Jath::Point(-108.746, 73.769, 79.793), Jath::Point(-107.353, 75.205, 77.272), Jath::Point(-105.899, 76.578, 71.501), Jath::Point(-104.377, 77.875, 66.524), Jath::Point(-102.78, 79.078, 61.054), Jath::Point(-101.102, 80.165, 55.26), Jath::Point(-99.342, 81.113, 49.452), Jath::Point(-97.499, 81.889, 42.518), Jath::Point(-95.587, 82.471, 38.706), Jath::Point(-93.621, 82.832, 36.566), Jath::Point(-91.627, 82.962, 37.584), Jath::Point(-89.63, 82.862, 42.247), Jath::Point(-87.657, 82.543, 47.589), Jath::Point(-85.725, 82.03, 53.77), Jath::Point(-83.845, 81.348, 60.154), Jath::Point(-82.024, 80.522, 64.277), Jath::Point(-80.264, 79.573, 70.024), Jath::Point(-78.561, 78.525, 73.487), Jath::Point(-76.913, 77.392, 78.078), Jath::Point(-75.318, 76.186, 80.056), Jath::Point(-73.77, 74.92, 79.284), Jath::Point(-72.266, 73.602, 78.511), Jath::Point(-70.801, 72.24, 73.426), Jath::Point(-69.374, 70.839, 68.34), Jath::Point(-67.982, 69.402, 63.255), Jath::Point(-66.621, 67.937, 58.169), Jath::Point(-65.288, 66.446, 53.083), Jath::Point(-63.984, 64.93, 47.998), Jath::Point(-62.702, 63.395, 42.912), Jath::Point(-61.445, 61.839, 37.826), Jath::Point(-60.209, 60.267, 32.74), Jath::Point(-58.91, 58.747, 41.641), Jath::Point(-57.594, 57.241, 50.54), Jath::Point(-56.275, 55.737, 59.44), Jath::Point(-54.952, 54.237, 68.34), Jath::Point(-53.625, 52.741, 77.24), Jath::Point(-52.294, 51.248, 86.14), Jath::Point(-50.958, 49.76, 95.04), Jath::Point(-49.616, 48.277, 94.994), Jath::Point(-48.269, 46.799, 94.949), Jath::Point(-46.916, 45.326, 94.903), Jath::Point(-45.556, 43.86, 94.858), Jath::Point(-44.188, 42.4, 94.813), Jath::Point(-42.813, 40.948, 94.767), Jath::Point(-41.429, 39.505, 94.722), Jath::Point(-40.035, 38.07, 94.676), Jath::Point(-38.631, 36.645, 94.631), Jath::Point(-37.217, 35.231, 94.586), Jath::Point(-35.792, 33.829, 94.54), Jath::Point(-34.354, 32.438, 94.495), Jath::Point(-32.906, 31.059, 94.449), Jath::Point(-31.446, 29.691, 94.404), Jath::Point(-29.977, 28.334, 94.359), Jath::Point(-28.5, 26.986, 94.313), Jath::Point(-27.018, 25.643, 94.268), Jath::Point(-25.532, 24.304, 94.222), Jath::Point(-24.046, 22.966, 94.177), Jath::Point(-22.562, 21.625, 94.131), Jath::Point(-21.082, 20.28, 94.086), Jath::Point(-19.608, 18.928, 94.041), Jath::Point(-18.14, 17.569, 93.995), Jath::Point(-16.68, 16.202, 93.95), Jath::Point(-15.228, 14.828, 93.904), Jath::Point(-13.783, 13.445, 93.859), Jath::Point(-12.345, 12.054, 93.814), Jath::Point(-10.915, 10.656, 93.768), Jath::Point(-9.492, 9.251, 86.775), Jath::Point(-8.075, 7.839, 79.783), Jath::Point(-6.665, 6.422, 72.79), Jath::Point(-5.26, 4.998, 65.797), Jath::Point(-3.86, 3.569, 58.805), Jath::Point(-2.466, 2.135, 51.812), Jath::Point(-1.076, 0.697, 44.819), Jath::Point(0.309, -0.745, 37.82), Jath::Point(1.708, -2.174, 46.387), Jath::Point(3.135, -3.576, 54.948), Jath::Point(4.589, -4.949, 63.509), Jath::Point(6.071, -6.292, 72.07), Jath::Point(7.577, -7.608, 80.63), Jath::Point(9.109, -8.894, 89.191), Jath::Point(10.664, -10.152, 90.265), Jath::Point(12.241, -11.382, 91.338), Jath::Point(13.838, -12.585, 92.412), Jath::Point(15.457, -13.76, 93.485), Jath::Point(17.093, -14.91, 94.559), Jath::Point(18.746, -16.035, 95.632), Jath::Point(20.415, -17.137, 96.706), Jath::Point(22.099, -18.217, 97.779), Jath::Point(23.795, -19.276, 98.853), Jath::Point(25.503, -20.316, 99.926), Jath::Point(27.222, -21.34, 96.457), Jath::Point(28.948, -22.349, 97.281), Jath::Point(30.682, -23.346, 94.137), Jath::Point(32.421, -24.334, 90.706), Jath::Point(34.164, -25.315, 87.274), Jath::Point(35.908, -26.294, 83.843), Jath::Point(37.652, -27.273, 80.412), Jath::Point(39.393, -28.257, 76.98), Jath::Point(41.129, -29.251, 73.549), Jath::Point(42.855, -30.26, 70.117), Jath::Point(44.57, -31.29, 66.686), Jath::Point(46.267, -32.348, 63.255), Jath::Point(47.942, -33.441, 61.559), Jath::Point(49.586, -34.579, 59.864), Jath::Point(51.194, -35.769, 58.169), Jath::Point(52.75, -37.025, 56.474), Jath::Point(54.244, -38.354, 54.778), Jath::Point(55.658, -39.768, 53.083), Jath::Point(56.971, -41.276, 51.388), Jath::Point(58.16, -42.883, 49.693), Jath::Point(59.202, -44.59, 46.915), Jath::Point(60.073, -46.389, 45.508), Jath::Point(60.76, -48.267, 45.954), Jath::Point(61.255, -50.204, 48.62), Jath::Point(61.562, -52.179, 53.215), Jath::Point(61.696, -54.174, 58.593), Jath::Point(61.672, -56.173, 60.712), Jath::Point(61.508, -58.166, 62.831), Jath::Point(61.221, -60.145, 64.9), Jath::Point(60.578, -62.03, 67.069), Jath::Point(59.838, -63.888, 69.188), Jath::Point(59.104, -65.749, 71.307), Jath::Point(58.379, -67.613, 73.426), Jath::Point(57.666, -69.481, 77.24), Jath::Point(56.967, -71.355, 81.054), Jath::Point(56.286, -73.236, 84.868), Jath::Point(55.627, -75.124, 88.683), Jath::Point(54.993, -77.021, 91.819), Jath::Point(54.389, -78.927, 90.664), Jath::Point(53.821, -80.845, 88.807), Jath::Point(53.294, -82.774, 86.817), Jath::Point(52.815, -84.716, 81.054), Jath::Point(52.391, -86.67, 71.519), Jath::Point(52.03, -88.638, 61.983), Jath::Point(51.74, -90.616, 52.448), Jath::Point(51.529, -92.605, 42.912), Jath::Point(51.403, -94.601, 57.434), Jath::Point(51.37, -96.6, 71.956), Jath::Point(51.435, -98.599, 72.912), Jath::Point(51.602, -100.592, 72.624), Jath::Point(51.872, -102.573, 72.847), Jath::Point(52.242, -104.538, 73.558), Jath::Point(52.711, -106.482, 70.685), Jath::Point(53.274, -108.401, 60.579), Jath::Point(53.923, -110.293, 50.474), Jath::Point(54.654, -112.155, 40.369), Jath::Point(55.459, -113.985, 54.99), Jath::Point(56.329, -115.786, 69.612), Jath::Point(57.259, -117.556, 84.233), Jath::Point(58.243, -119.298, 98.854), Jath::Point(59.274, -121.011, 98.854), Jath::Point(60.347, -122.699, 98.854), Jath::Point(61.459, -124.361, 98.854), Jath::Point(62.605, -126, 98.854), Jath::Point(63.781, -127.618, 98.854), Jath::Point(64.984, -129.216, 98.854), Jath::Point(66.211, -130.795, 98.854), Jath::Point(67.224, -132.066, 98.85), Jath::Point(67.224, -132.066, 0), 
};
Jath::Path rings1Path = Jath::Path::cm(rings1PathPoints);

std::vector<Jath::Point> goal2PathPoints = {
    Jath::Point(88.263, -148.263, 12), Jath::Point(88.418, -146.269, 120), Jath::Point(88.569, -144.274, 120), Jath::Point(88.717, -142.28, 120), Jath::Point(88.863, -140.285, 120), Jath::Point(89.005, -138.29, 120), Jath::Point(89.145, -136.295, 120), Jath::Point(89.283, -134.3, 120), Jath::Point(89.418, -132.304, 120), Jath::Point(89.552, -130.309, 120), Jath::Point(89.684, -128.313, 120), Jath::Point(89.816, -126.318, 120), Jath::Point(89.947, -124.322, 120), Jath::Point(90.078, -122.326, 120), Jath::Point(90.209, -120.33, 120), Jath::Point(90.341, -118.335, 120), Jath::Point(90.476, -116.339, 120), Jath::Point(90.612, -114.344, 120), Jath::Point(90.752, -112.349, 120), Jath::Point(90.895, -110.354, 120), Jath::Point(91.044, -108.36, 120), Jath::Point(91.198, -106.366, 120), Jath::Point(91.358, -104.372, 120), Jath::Point(91.526, -102.379, 120), Jath::Point(91.702, -100.387, 120), Jath::Point(91.888, -98.395, 120), Jath::Point(92.083, -96.405, 120), Jath::Point(92.29, -94.416, 120), Jath::Point(92.509, -92.428, 120), Jath::Point(92.741, -90.441, 120), Jath::Point(92.987, -88.456, 120), Jath::Point(93.247, -86.473, 120), Jath::Point(93.523, -84.493, 120), Jath::Point(93.814, -82.514, 120), Jath::Point(94.123, -80.538, 120), Jath::Point(94.447, -78.564, 120), Jath::Point(94.79, -76.594, 120), Jath::Point(95.148, -74.626, 120), Jath::Point(95.526, -72.662, 120), Jath::Point(95.92, -70.702, 120), Jath::Point(96.333, -68.745, 120), Jath::Point(96.763, -66.791, 120), Jath::Point(97.21, -64.842, 120), Jath::Point(97.674, -62.897, 120), Jath::Point(98.155, -60.955, 120), Jath::Point(98.652, -59.018, 120), Jath::Point(99.165, -57.085, 120), Jath::Point(99.693, -55.156, 120), Jath::Point(100.237, -53.231, 120), Jath::Point(100.794, -51.311, 120), Jath::Point(101.366, -49.394, 120), Jath::Point(101.951, -47.482, 120), Jath::Point(102.549, -45.573, 120), Jath::Point(103.159, -43.668, 120), Jath::Point(103.781, -41.768, 120), Jath::Point(104.415, -39.871, 120), Jath::Point(105.06, -37.978, 120), Jath::Point(105.715, -36.088, 120), Jath::Point(106.38, -34.202, 120), Jath::Point(107.055, -32.319, 120), Jath::Point(107.738, -30.439, 120), Jath::Point(108.43, -28.563, 120), Jath::Point(109.131, -26.69, 120), Jath::Point(109.84, -24.82, 120), Jath::Point(110.556, -22.952, 120), Jath::Point(111.28, -21.088, 120), Jath::Point(112.011, -19.226, 120), Jath::Point(112.748, -17.367, 120), Jath::Point(113.492, -15.51, 120), Jath::Point(114.242, -13.656, 120), Jath::Point(114.998, -11.805, 120), Jath::Point(115.759, -9.955, 120), Jath::Point(116.526, -8.108, 120), Jath::Point(117.298, -6.263, 120), Jath::Point(118.074, -4.42, 120), Jath::Point(118.855, -2.579, 120), Jath::Point(119.641, -0.739, 120), Jath::Point(120.431, 1.098, 120), Jath::Point(121.225, 2.933, 120), Jath::Point(122.024, 4.767, 120), Jath::Point(123.513, 8.163, 12), Jath::Point(123.513, 8.163, 0), 
};
Jath::Path goal2Path = Jath::Path::cm(goal2PathPoints);

std::vector<Jath::Point> rings2PathPoints = {
    Jath::Point(112.464, 8.134, 9), Jath::Point(110.615, 8.896, 96.468), Jath::Point(108.771, 9.671, 95.936), Jath::Point(106.934, 10.462, 91.826), Jath::Point(105.105, 11.27, 91.395), Jath::Point(103.284, 12.096, 90.949), Jath::Point(101.472, 12.944, 90.252), Jath::Point(99.671, 13.813, 89.769), Jath::Point(97.882, 14.707, 89.02), Jath::Point(96.106, 15.626, 88.504), Jath::Point(94.345, 16.575, 87.708), Jath::Point(92.6, 17.552, 86.889), Jath::Point(90.874, 18.562, 86.333), Jath::Point(89.168, 19.606, 85.49), Jath::Point(87.484, 20.686, 84.925), Jath::Point(85.826, 21.804, 84.081), Jath::Point(84.195, 22.961, 83.25), Jath::Point(82.593, 24.158, 82.445), Jath::Point(81.024, 25.399, 81.93), Jath::Point(79.491, 26.683, 81.2), Jath::Point(77.996, 28.011, 80.536), Jath::Point(76.542, 29.384, 79.713), Jath::Point(75.132, 30.803, 78.841), Jath::Point(73.769, 32.266, 77.969), Jath::Point(72.456, 33.774, 77.098), Jath::Point(71.193, 35.325, 76.226), Jath::Point(69.985, 36.919, 75.354), Jath::Point(68.831, 38.553, 74.482), Jath::Point(67.734, 40.224, 73.611), Jath::Point(66.695, 41.933, 72.739), Jath::Point(65.714, 43.676, 71.867), Jath::Point(64.789, 45.449, 70.996), Jath::Point(63.924, 47.252, 70.124), Jath::Point(63.114, 49.081, 63.102), Jath::Point(62.362, 50.934, 56.079), Jath::Point(61.663, 52.808, 49.057), Jath::Point(61.018, 54.701, 42.035), Jath::Point(60.425, 56.611, 35.013), Jath::Point(59.881, 58.535, 27.99), Jath::Point(59.351, 60.461, 34.54), Jath::Point(58.545, 62.292, 41.091), Jath::Point(57.778, 64.138, 47.641), Jath::Point(57.055, 66.003, 54.191), Jath::Point(56.381, 67.886, 60.741), Jath::Point(55.764, 69.789, 67.291), Jath::Point(55.213, 71.711, 73.841), Jath::Point(54.733, 73.652, 74.531), Jath::Point(54.336, 75.612, 71.848), Jath::Point(54.03, 77.589, 70.195), Jath::Point(53.822, 79.577, 68.753), Jath::Point(53.717, 81.574, 68.414), Jath::Point(53.72, 83.574, 69.113), Jath::Point(53.827, 85.571, 71.159), Jath::Point(54.03, 87.561, 74.404), Jath::Point(54.317, 89.54, 78.551), Jath::Point(54.673, 91.508, 83.222), Jath::Point(55.079, 93.466, 85.972), Jath::Point(55.518, 95.417, 87.075), Jath::Point(55.974, 97.365, 88.178), Jath::Point(56.432, 99.312, 89.28), Jath::Point(56.879, 101.261, 90.383), Jath::Point(57.305, 103.215, 88.885), Jath::Point(57.704, 105.175, 87.548), Jath::Point(58.067, 107.142, 86.331), Jath::Point(58.392, 109.115, 85.802), Jath::Point(58.677, 111.094, 85.558), Jath::Point(58.919, 113.08, 97), Jath::Point(59.119, 115.07, 80.057), Jath::Point(59.276, 117.063, 63.115), Jath::Point(59.392, 119.06, 46.172), Jath::Point(59.468, 121.059, 29.2), Jath::Point(59.519, 123.058, 37.508), Jath::Point(59.541, 125.058, 45.786), Jath::Point(59.529, 127.058, 54.064), Jath::Point(59.483, 129.057, 62.342), Jath::Point(59.398, 131.055, 70.62), Jath::Point(59.267, 133.051, 71.471), Jath::Point(59.089, 135.043, 72.322), Jath::Point(58.852, 137.029, 73.172), Jath::Point(58.551, 139.006, 74.023), Jath::Point(58.177, 140.97, 72.04), Jath::Point(57.717, 142.916, 67.453), Jath::Point(57.156, 144.836, 62.155), Jath::Point(56.477, 146.717, 56.169), Jath::Point(55.665, 148.544, 49.616), Jath::Point(54.695, 150.292, 39.311), Jath::Point(53.553, 151.932, 29.812), Jath::Point(52.22, 153.421, 24.91), Jath::Point(50.7, 154.719, 21.081), Jath::Point(49.014, 155.791, 23.714), Jath::Point(47.194, 156.618, 30.546), Jath::Point(45.284, 157.206, 39.619), Jath::Point(43.32, 157.578, 49.222), Jath::Point(41.33, 157.766, 58.223), Jath::Point(39.33, 157.8, 63.608), Jath::Point(37.333, 157.706, 70.639), Jath::Point(35.343, 157.512, 76.475), Jath::Point(33.362, 157.238, 79.78), Jath::Point(31.391, 156.898, 84.006), Jath::Point(29.429, 156.508, 86.418), Jath::Point(27.476, 156.077, 89.555), Jath::Point(25.53, 155.616, 91.391), Jath::Point(23.59, 155.132, 93.068), Jath::Point(21.653, 154.633, 94.447), Jath::Point(19.718, 154.125, 95.298), Jath::Point(17.785, 153.614, 95.883), Jath::Point(15.851, 153.105, 94.571), Jath::Point(13.915, 152.603, 89.745), Jath::Point(11.975, 152.114, 82.491), Jath::Point(10.032, 151.642, 75.236), Jath::Point(8.083, 151.193, 67.981), Jath::Point(6.128, 150.772, 60.727), Jath::Point(4.166, 150.384, 53.472), Jath::Point(2.196, 150.036, 46.217), Jath::Point(0.219, 149.733, 38.963), Jath::Point(-1.758, 149.439, 31.70), Jath::Point(-3.723, 149.063, 42.59), Jath::Point(-5.68, 148.654, 53.472), Jath::Point(-7.63, 148.209, 64.354), Jath::Point(-9.57, 147.724, 75.236), Jath::Point(-11.499, 147.194, 86.118), Jath::Point(-13.413, 146.616, 81.3), Jath::Point(-15.31, 145.982, 78.57), Jath::Point(-17.184, 145.284, 76.62), Jath::Point(-19.032, 144.52, 73.592), Jath::Point(-20.846, 143.677, 71.585), Jath::Point(-22.617, 142.749, 68.785), Jath::Point(-24.339, 141.731, 66.526), Jath::Point(-25.999, 140.616, 64.985), Jath::Point(-27.59, 139.406, 65.381), Jath::Point(-29.107, 138.103, 68.439), Jath::Point(-30.553, 136.721, 74.511), Jath::Point(-31.94, 135.28, 85.761), Jath::Point(-33.29, 133.804, 87.473), Jath::Point(-34.634, 132.323, 80.392), Jath::Point(-36.005, 130.868, 73.31), Jath::Point(-37.435, 129.47, 66.229), Jath::Point(-38.942, 128.155, 59.148), Jath::Point(-40.534, 126.946, 52.067), Jath::Point(-42.207, 125.85, 44.985), Jath::Point(-43.952, 124.874, 37.904), Jath::Point(-45.754, 124.008, 39.639), Jath::Point(-47.602, 123.244, 41.374), Jath::Point(-49.486, 122.572, 43.109), Jath::Point(-51.396, 121.979, 44.844), Jath::Point(-53.327, 121.458, 46.579), Jath::Point(-55.273, 120.999, 48.314), Jath::Point(-57.231, 120.593, 50.049), Jath::Point(-59.199, 120.236, 51.78), Jath::Point(-61.192, 120.094, 53.518), Jath::Point(-63.19, 119.992, 55.253), Jath::Point(-65.187, 119.888, 55.253), Jath::Point(-67.184, 119.783, 55.253), Jath::Point(-69.181, 119.677, 55.253), Jath::Point(-71.179, 119.572, 55.253), Jath::Point(-73.176, 119.467, 55.253), Jath::Point(-75.173, 119.365, 55.253), Jath::Point(-77.171, 119.266, 55.253), Jath::Point(-79.169, 119.173, 55.253), Jath::Point(-81.167, 119.088, 55.253), Jath::Point(-83.165, 119.014, 55.253), Jath::Point(-85.164, 118.954, 55.253), Jath::Point(-87.164, 118.91, 55.253), Jath::Point(-89.164, 118.885, 55.253), Jath::Point(-91.164, 118.879, 55.253), Jath::Point(-93.164, 118.891, 55.253), Jath::Point(-95.164, 118.919, 55.253), Jath::Point(-97.163, 118.963, 55.253), Jath::Point(-99.162, 119.018, 55.253), Jath::Point(-101.161, 119.084, 55.253), Jath::Point(-103.16, 119.158, 55.253), Jath::Point(-105.158, 119.239, 55.253), Jath::Point(-107.156, 119.326, 55.253), Jath::Point(-109.154, 119.417, 55.253), Jath::Point(-111.152, 119.511, 55.253), Jath::Point(-113.15, 119.609, 55.253), Jath::Point(-115.147, 119.709, 55.253), Jath::Point(-117.145, 119.811, 55.253), Jath::Point(-119.142, 119.914, 55.25), Jath::Point(-121.141, 119.947, 55.253), Jath::Point(-123.141, 119.974, 55.253), Jath::Point(-125.141, 120.001, 55.253), Jath::Point(-127.141, 120.029, 55.253), Jath::Point(-129.141, 120.056, 55.253), Jath::Point(-131.141, 120.084, 55.253), Jath::Point(-133.14, 120.111, 55.253), Jath::Point(-135.14, 120.138, 55.253), Jath::Point(-137.14, 120.166, 55.253), Jath::Point(-139.14, 120.193, 55.253), Jath::Point(-141.14, 120.221, 55.253), Jath::Point(-143.139, 120.248, 55.253), Jath::Point(-145.139, 120.275, 55.253), Jath::Point(-147.139, 120.303, 55.253), Jath::Point(-149.139, 120.33, 55.253), Jath::Point(-151.139, 120.357, 55.253), Jath::Point(-151.544, 120.363, 55.25), Jath::Point(-151.544, 120.363, 0), 
};
Jath::Path rings2Path = Jath::Path::cm(rings2PathPoints);


void skills()
{

    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(-2.5), art::Tiles(0));
    smartDrive.m_dir = art::Degrees(-90);

    arm.set(100);
    vex::wait(1.25, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveFor(art::Inches(-5), -50);
    
    armTarget = art::Degrees(0);
    vex::thread armControl(autonArmPos);

    followPathRev(goal1Path, art::Inches(7));
    // maybe add additional drive
    clamp.set(true);

    resetPositionFromGPS();

    smartDrive.turnToPID(art::Degrees(20));
    intake.set(100);

    followPath(rings1Path, art::Inches(7));

    driveTowardPoint(art::Vec2::XandY(art::Tiles(2), art::Tiles(-2.5)));

    target = art::Vec2::XandY(art::Tiles(2.75), art::Tiles(2.75));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.driveForPID(-travel.magnitude() * .9);

    clamp.set(false);    
    intake.set(0);

    smartDrive.driveForPID(art::Inches(48));


    smartDrive.arcade(0, 0);
}
