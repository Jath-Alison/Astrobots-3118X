#include "AutonPaths.h"
#include "RobotConfig.h"

std::vector<Jath::Point> testPathUPoints = {Jath::Point(-11.834, -58.938, 97.367), Jath::Point(-10.834, -58.928, 97.548), Jath::Point(-9.834, -58.924, 97.727), Jath::Point(-8.834, -58.924, 97.904), Jath::Point(-7.834, -58.929, 98.08), Jath::Point(-6.834, -58.938, 98.254), Jath::Point(-5.834, -58.951, 98.428), Jath::Point(-4.834, -58.967, 98.601), Jath::Point(-3.834, -58.986, 98.775), Jath::Point(-2.835, -59.008, 99.124), Jath::Point(-1.835, -59.032, 99.301), Jath::Point(-0.835, -59.057, 99.48), Jath::Point(0.164, -59.084, 99.662), Jath::Point(1.164, -59.112, 99.848), Jath::Point(2.164, -59.14, 99.963), Jath::Point(3.163, -59.168, 99.57), Jath::Point(4.163, -59.196, 99.365), Jath::Point(5.163, -59.222, 99.153), Jath::Point(6.162, -59.247, 98.933), Jath::Point(7.162, -59.27, 98.705), Jath::Point(8.162, -59.291, 98.181), Jath::Point(9.162, -59.309, 96.878), Jath::Point(10.161, -59.322, 95.558), Jath::Point(11.161, -59.331, 94.22), Jath::Point(12.161, -59.336, 92.862), Jath::Point(13.161, -59.334, 91.485), Jath::Point(14.161, -59.325, 90.086), Jath::Point(15.161, -59.309, 88.665), Jath::Point(16.161, -59.284, 87.221), Jath::Point(17.16, -59.249, 85.752), Jath::Point(18.159, -59.203, 84.258), Jath::Point(19.158, -59.145, 82.737), Jath::Point(20.155, -59.072, 81.188), Jath::Point(21.151, -58.985, 79.608), Jath::Point(22.145, -58.879, 77.996), Jath::Point(23.138, -58.755, 76.351), Jath::Point(24.127, -58.607, 74.669), Jath::Point(25.112, -58.436, 72.948), Jath::Point(26.091, -58.234, 71.186), Jath::Point(27.064, -58.002, 69.379), Jath::Point(28.027, -57.735, 67.524), Jath::Point(28.978, -57.425, 65.617), Jath::Point(29.913, -57.07, 63.652), Jath::Point(30.826, -56.663, 61.625), Jath::Point(31.712, -56.2, 59.529), Jath::Point(32.563, -55.675, 57.357), Jath::Point(33.368, -55.083, 55.099), Jath::Point(34.118, -54.422, 52.745), Jath::Point(34.801, -53.693, 50.886), Jath::Point(35.407, -52.898, 50.542), Jath::Point(35.93, -52.046, 51.804), Jath::Point(36.365, -51.147, 54.514), Jath::Point(36.712, -50.21, 58.312), Jath::Point(36.977, -49.246, 62.75), Jath::Point(37.165, -48.264, 66.792), Jath::Point(37.041, -47.287, 70.659), Jath::Point(36.806, -46.315, 68.838), Jath::Point(36.572, -45.343, 66.967), Jath::Point(36.341, -44.37, 65.043), Jath::Point(36.111, -43.397, 63.061), Jath::Point(35.885, -42.423, 61.013), Jath::Point(35.662, -41.448, 58.895), Jath::Point(35.443, -40.472, 56.698), Jath::Point(35.227, -39.496, 54.412), Jath::Point(34.988, -38.525, 52.026), Jath::Point(34.681, -37.573, 95.171), Jath::Point(34.352, -36.629, 98.849), Jath::Point(34.025, -35.684, 97.693), Jath::Point(33.701, -34.738, 96.385), Jath::Point(33.379, -33.791, 95.058), Jath::Point(33.059, -32.844, 93.712), Jath::Point(32.742, -31.895, 92.347), Jath::Point(32.426, -30.947, 90.961), Jath::Point(32.111, -29.997, 89.554), Jath::Point(31.798, -29.048, 88.125), Jath::Point(31.485, -28.098, 86.672), Jath::Point(31.174, -27.147, 85.194), Jath::Point(30.864, -26.197, 83.69), Jath::Point(30.554, -25.246, 82.158), Jath::Point(30.245, -24.295, 80.598), Jath::Point(29.978, -23.331, 79.006), Jath::Point(29.713, -22.367, 77.382), Jath::Point(29.448, -21.403, 75.723), Jath::Point(29.182, -20.439, 74.027), Jath::Point(28.917, -19.474, 72.291), Jath::Point(28.652, -18.51, 70.512), Jath::Point(28.387, -17.546, 68.688), Jath::Point(28.122, -16.582, 66.813), Jath::Point(27.857, -15.618, 64.885), Jath::Point(27.592, -14.653, 62.897), Jath::Point(27.326, -13.689, 60.844), Jath::Point(27.061, -12.725, 58.72), Jath::Point(26.796, -11.761, 56.515)};
Jath::Path testPathU = Jath::Path::in(testPathUPoints);

void followPath(Jath::Path p, Jath::Distance lookaheadDist)
{
    Jath::Point lookahead = p.getLookahead(smartDrive.m_centerPos, lookaheadDist);
    Jath::Point closest = p.getClosestPoint(smartDrive.m_centerPos);

    // std::cout << closest.m_pos.x <<" "<< p.m_points.back().m_pos.x  << ", " << closest.m_pos.y <<" "<< p.m_points.back().m_pos.y << "\n";
    // std::cout << "\t" << (closest.m_pos.x != p.m_points.back().m_pos.x) << ", " << (closest.m_pos.y != p.m_points.back().m_pos.y) << "\n";
    // std::cout << "\t\t" << ((closest.m_pos.x != p.m_points.back().m_pos.x) && (closest.m_pos.y != p.m_points.back().m_pos.y)) << "\n";

    smartDrive.driveTowardPoint(lookahead, true);
    while( closest.m_pos.x != p.m_points.back().m_pos.x || closest.m_pos.y != p.m_points.back().m_pos.y ){
        // smartDrive.driveTowardPoint(lookahead);
        smartDrive.driveTowardPoint(lookahead.m_pos, (100.f/closest.m_speed) * 50.f);
        // smartDrive.driveTowardPoint(lookahead.m_pos, controller1.Axis2.position());
        // smartDrive.LeftSplitArcade(controller1);

        Brain.Screen.clearScreen();
        Brain.Screen.setPenColor(vex::color::white);
        for (size_t i = 0; i < p.m_points.size(); i++)
        {

            Brain.Screen.drawCircle( p.m_points[i].m_pos.x+100, p.m_points[i].m_pos.y+100,10);
        }

        Brain.Screen.setPenColor(vex::color::blue);
        Brain.Screen.drawCircle( lookahead.m_pos.x+100, lookahead.m_pos.y+100,20);
        Brain.Screen.setPenColor(vex::color::green);
        Brain.Screen.drawCircle( closest.m_pos.x+100, closest.m_pos.y+100,15);
        Brain.Screen.setPenColor(vex::color::red);
        Brain.Screen.drawCircle( smartDrive.m_pos.x+100, smartDrive.m_pos.y+100,10);
        Brain.Screen.setPenColor(vex::color::cyan);
        Brain.Screen.drawCircle( smartDrive.m_centerPos.x+100, smartDrive.m_centerPos.y+100,5);

        lookahead = p.getLookahead(smartDrive.m_pos, lookaheadDist);
        closest = p.getClosestPoint(smartDrive.m_pos);
        vex::wait(20, vex::msec);
    }
}
