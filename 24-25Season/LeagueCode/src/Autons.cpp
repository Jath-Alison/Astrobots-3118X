#include "SubAutons.h"
#include "Autons.h"

int intakeAntiJam()
{

    double lastcmd = intake.get();

    while (true)
    {

        if (intake.get() != lastcmd)
        {
            lastcmd = intake.get();
            vex::wait(0.25, vex::sec);
        }

        if (intake.get() > 50 && intake.velocity(vex::pct) < 5)
        {
            double temp = intake.get();

            intake.set(-100);
            vex::wait(0.25, vex::sec);

            intake.set(temp);
        }

        vex::wait(100, vex::msec);
    }
    return 1;
}

std::vector<Jath::Point> testPathPoints = {Jath::Point(0, 0, 10), Jath::Point(-1.999, 0.077, 101.61), Jath::Point(-3.997, 0.159, 99.537), Jath::Point(-5.995, 0.248, 99.537), Jath::Point(-7.992, 0.35, 99.44), Jath::Point(-9.989, 0.457, 99.34), Jath::Point(-11.986, 0.574, 99.34), Jath::Point(-13.982, 0.703, 99.234), Jath::Point(-15.977, 0.839, 99.124), Jath::Point(-17.972, 0.984, 99.124), Jath::Point(-19.966, 1.143, 99.009), Jath::Point(-21.959, 1.31, 98.888), Jath::Point(-23.951, 1.486, 98.762), Jath::Point(-25.942, 1.676, 98.762), Jath::Point(-27.932, 1.877, 98.63), Jath::Point(-29.92, 2.089, 98.492), Jath::Point(-31.908, 2.311, 98.348), Jath::Point(-33.894, 2.549, 98.348), Jath::Point(-35.878, 2.799, 98.197), Jath::Point(-37.861, 3.061, 98.039), Jath::Point(-39.842, 3.336, 97.874), Jath::Point(-41.821, 3.625, 97.701), Jath::Point(-43.797, 3.93, 97.701), Jath::Point(-45.771, 4.251, 97.52), Jath::Point(-47.743, 4.586, 97.331), Jath::Point(-49.712, 4.937, 97.133), Jath::Point(-51.678, 5.304, 96.926), Jath::Point(-53.641, 5.689, 96.71), Jath::Point(-55.6, 6.091, 96.483), Jath::Point(-57.555, 6.511, 96.247), Jath::Point(-59.506, 6.951, 95.999), Jath::Point(-61.453, 7.411, 95.741), Jath::Point(-63.394, 7.892, 95.741), Jath::Point(-65.33, 8.394, 95.19), Jath::Point(-67.26, 8.919, 94.896), Jath::Point(-69.183, 9.468, 94.589), Jath::Point(-71.099, 10.041, 94.269), Jath::Point(-73.008, 10.639, 93.936), Jath::Point(-74.907, 11.264, 93.589), Jath::Point(-76.798, 11.915, 93.228), Jath::Point(-78.679, 12.595, 92.852), Jath::Point(-80.549, 13.305, 92.462), Jath::Point(-82.406, 14.047, 91.637), Jath::Point(-84.249, 14.823, 91.201), Jath::Point(-86.078, 15.632, 90.75), Jath::Point(-87.892, 16.476, 89.803), Jath::Point(-89.685, 17.36, 89.307), Jath::Point(-91.461, 18.281, 88.796), Jath::Point(-93.213, 19.245, 87.732), Jath::Point(-94.942, 20.251, 87.18), Jath::Point(-96.643, 21.302, 86.04), Jath::Point(-98.316, 22.398, 85.454), Jath::Point(-99.953, 23.546, 84.257), Jath::Point(-101.556, 24.742, 83.035), Jath::Point(-103.12, 25.989, 81.802), Jath::Point(-104.637, 27.291, 81.187), Jath::Point(-106.106, 28.649, 79.969), Jath::Point(-107.521, 30.062, 78.785), Jath::Point(-108.878, 31.531, 77.653), Jath::Point(-110.171, 33.057, 76.594), Jath::Point(-111.394, 34.638, 75.627), Jath::Point(-112.543, 36.275, 74.384), Jath::Point(-113.609, 37.967, 73.715), Jath::Point(-114.591, 39.709, 73.184), Jath::Point(-115.484, 41.499, 72.659), Jath::Point(-116.281, 43.333, 72.49), Jath::Point(-116.983, 45.205, 72.496), Jath::Point(-117.585, 47.112, 72.661), Jath::Point(-118.086, 49.048, 73.124), Jath::Point(-118.489, 51.007, 73.808), Jath::Point(-118.792, 52.984, 74.674), Jath::Point(-118.998, 54.973, 75.688), Jath::Point(-119.111, 56.969, 76.83), Jath::Point(-119.131, 58.969, 55.33), Jath::Point(-119.011, 60.965, 62.834), Jath::Point(-118.751, 62.947, 68.251), Jath::Point(-118.371, 64.911, 72.254), Jath::Point(-117.888, 66.851, 75.274), Jath::Point(-117.308, 68.765, 76.89), Jath::Point(-116.646, 70.652, 78.261), Jath::Point(-115.901, 72.508, 79.961), Jath::Point(-115.084, 74.334, 80.91), Jath::Point(-114.199, 76.127, 81.744), Jath::Point(-113.25, 77.887, 82.486), Jath::Point(-112.24, 79.613, 83.153), Jath::Point(-111.172, 81.304, 83.76), Jath::Point(-110.05, 82.959, 84.32), Jath::Point(-108.876, 84.578, 84.843), Jath::Point(-107.653, 86.161, 85.337), Jath::Point(-106.383, 87.705, 85.575), Jath::Point(-105.067, 89.212, 86.039), Jath::Point(-103.71, 90.681, 86.49), Jath::Point(-102.313, 92.112, 86.711), Jath::Point(-100.876, 93.503, 87.149), Jath::Point(-99.405, 94.858, 87.583), Jath::Point(-97.897, 96.171, 87.799), Jath::Point(-96.358, 97.448, 88.23), Jath::Point(-94.786, 98.685, 88.446), Jath::Point(-93.187, 99.886, 88.877), Jath::Point(-91.557, 101.045, 89.093), Jath::Point(-89.903, 102.169, 89.309), Jath::Point(-88.223, 103.254, 89.742), Jath::Point(-86.519, 104.301, 89.959), Jath::Point(-84.795, 105.314, 90.176), Jath::Point(-83.048, 106.288, 90.61), Jath::Point(-81.281, 107.226, 90.826), Jath::Point(-79.497, 108.13, 91.042), Jath::Point(-77.697, 109, 91.473), Jath::Point(-75.878, 109.832, 91.688), Jath::Point(-74.045, 110.631, 91.901), Jath::Point(-72.197, 111.398, 92.114), Jath::Point(-70.337, 112.132, 92.325), Jath::Point(-68.465, 112.835, 92.535), Jath::Point(-66.58, 113.505, 92.95), Jath::Point(-64.685, 114.143, 93.155), Jath::Point(-62.779, 114.75, 93.358), Jath::Point(-60.865, 115.329, 93.559), Jath::Point(-58.942, 115.878, 93.758), Jath::Point(-57.011, 116.399, 93.954), Jath::Point(-55.073, 116.891, 94.148), Jath::Point(-53.127, 117.357, 94.34), Jath::Point(-51.176, 117.795, 94.528), Jath::Point(-49.219, 118.208, 94.714), Jath::Point(-47.257, 118.594, 94.897), Jath::Point(-45.29, 118.956, 95.077), Jath::Point(-43.319, 119.293, 95.254), Jath::Point(-41.343, 119.606, 95.428), Jath::Point(-39.364, 119.896, 95.598), Jath::Point(-37.382, 120.164, 95.766), Jath::Point(-35.397, 120.407, 95.766), Jath::Point(-33.41, 120.627, 95.93), Jath::Point(-31.419, 120.827, 96.091), Jath::Point(-29.428, 121.005, 96.249), Jath::Point(-27.434, 121.164, 96.403), Jath::Point(-25.439, 121.303, 96.554), Jath::Point(-23.442, 121.424, 96.702), Jath::Point(-21.445, 121.522, 96.702), Jath::Point(-19.446, 121.601, 96.846), Jath::Point(-17.447, 121.663, 96.987), Jath::Point(-15.448, 121.708, 97.125), Jath::Point(-13.448, 121.737, 97.259), Jath::Point(-11.448, 121.744, 97.259), Jath::Point(-9.448, 121.735, 97.391), Jath::Point(-7.448, 121.711, 97.518), Jath::Point(-5.449, 121.673, 97.643), Jath::Point(-3.45, 121.615, 97.643), Jath::Point(-1.451, 121.542, 97.76), Jath::Point(0.548, 121.498, 99.639), Jath::Point(2.548, 121.514, 99.639), Jath::Point(4.548, 121.526, 99.424), Jath::Point(6.548, 121.525, 99.424), Jath::Point(8.548, 121.52, 99.187), Jath::Point(10.548, 121.5, 99.187), Jath::Point(12.548, 121.476, 98.924), Jath::Point(14.547, 121.436, 98.924), Jath::Point(16.547, 121.392, 98.635), Jath::Point(18.546, 121.331, 98.635), Jath::Point(20.545, 121.263, 98.314), Jath::Point(22.543, 121.18, 98.314), Jath::Point(24.541, 121.085, 97.959), Jath::Point(26.538, 120.979, 97.959), Jath::Point(28.534, 120.853, 97.566), Jath::Point(30.529, 120.72, 97.13), Jath::Point(32.523, 120.563, 97.13), Jath::Point(34.516, 120.394, 96.647), Jath::Point(36.508, 120.21, 96.647), Jath::Point(38.496, 120, 96.113), Jath::Point(40.484, 119.775, 95.52), Jath::Point(42.469, 119.53, 95.52), Jath::Point(44.45, 119.256, 94.865), Jath::Point(46.428, 118.962, 94.139), Jath::Point(48.403, 118.645, 93.338), Jath::Point(50.372, 118.296, 93.338), Jath::Point(52.335, 117.916, 92.454), Jath::Point(54.293, 117.505, 91.482), Jath::Point(56.243, 117.062, 90.414), Jath::Point(58.184, 116.582, 89.247), Jath::Point(60.115, 116.062, 87.975), Jath::Point(62.034, 115.496, 87.975), Jath::Point(63.937, 114.881, 86.597), Jath::Point(65.823, 114.216, 85.113), Jath::Point(67.689, 113.496, 83.526), Jath::Point(69.53, 112.716, 80.085), Jath::Point(71.341, 111.866, 78.263), Jath::Point(73.116, 110.946, 76.404), Jath::Point(74.852, 109.952, 74.544), Jath::Point(76.54, 108.88, 72.72), Jath::Point(78.173, 107.727, 69.369), Jath::Point(79.733, 106.476, 67.941), Jath::Point(81.222, 105.141, 66.745), Jath::Point(82.625, 103.717, 65.215), Jath::Point(83.931, 102.203, 64.941), Jath::Point(85.14, 100.61, 65.428), Jath::Point(86.236, 98.938, 66.17), Jath::Point(87.229, 97.202, 68.51), Jath::Point(88.109, 95.407, 70.03), Jath::Point(88.887, 93.565, 73.544), Jath::Point(89.566, 91.684, 75.451), Jath::Point(90.154, 89.772, 79.375), Jath::Point(90.659, 87.837, 81.332), Jath::Point(91.092, 85.885, 85.129), Jath::Point(91.459, 83.919, 86.94), Jath::Point(91.774, 81.944, 90.349), Jath::Point(92.039, 79.962, 91.941), Jath::Point(92.269, 77.975, 93.458), Jath::Point(92.467, 75.985, 96.273), Jath::Point(92.64, 73.993, 97.578), Jath::Point(92.797, 71.999, 98.819), Jath::Point(92.942, 70.004, 101.13), Jath::Point(93.08, 68.009, 101.219), Jath::Point(93.217, 66.014, 100.761), Jath::Point(93.358, 64.019, 98.827), Jath::Point(93.508, 62.024, 97.917), Jath::Point(93.67, 60.031, 97.042), Jath::Point(93.847, 58.039, 96.201), Jath::Point(94.044, 56.048, 94.615), Jath::Point(94.266, 54.061, 93.868), Jath::Point(94.515, 52.076, 93.153), Jath::Point(94.792, 50.096, 92.469), Jath::Point(95.102, 48.12, 91.819), Jath::Point(95.445, 46.15, 91.202), Jath::Point(95.829, 44.187, 90.081), Jath::Point(96.253, 42.232, 89.58), Jath::Point(96.718, 40.287, 89.122), Jath::Point(97.226, 38.353, 88.711), Jath::Point(97.778, 36.431, 88.347), Jath::Point(98.376, 34.522, 88.035), Jath::Point(99.02, 32.629, 87.776), Jath::Point(99.712, 30.752, 87.572), Jath::Point(100.451, 28.894, 87.424), Jath::Point(101.238, 27.056, 87.333), Jath::Point(102.073, 25.238, 87.3), Jath::Point(102.955, 23.443, 87.324), Jath::Point(103.884, 21.672, 87.403), Jath::Point(104.859, 19.926, 87.536), Jath::Point(105.879, 18.206, 87.72), Jath::Point(106.942, 16.512, 87.952), Jath::Point(108.048, 14.845, 88.228), Jath::Point(109.194, 13.206, 88.544), Jath::Point(110.378, 11.595, 88.896), Jath::Point(111.6, 10.011, 89.278), Jath::Point(112.857, 8.456, 89.686), Jath::Point(114.147, 6.928, 90.115), Jath::Point(115.469, 5.427, 90.559), Jath::Point(116.826, 3.958, 90.559), Jath::Point(118.214, 2.518, 91.01), Jath::Point(119.479, 0.974, 99.97), Jath::Point(120.661, -0.639, 99.97), Jath::Point(121.834, -2.259, 99.862), Jath::Point(123.003, -3.881, 99.748), Jath::Point(124.165, -5.509, 99.748), Jath::Point(125.321, -7.141, 99.626), Jath::Point(126.472, -8.777, 99.497), Jath::Point(127.613, -10.419, 99.497), Jath::Point(128.748, -12.066, 99.359), Jath::Point(129.878, -13.716, 99.359), Jath::Point(130.996, -15.374, 99.212), Jath::Point(132.108, -17.037, 99.055), Jath::Point(133.214, -18.703, 99.055), Jath::Point(134.307, -20.378, 98.887), Jath::Point(135.393, -22.058, 98.708), Jath::Point(136.471, -23.742, 98.517), Jath::Point(137.537, -25.435, 98.517), Jath::Point(138.592, -27.134, 98.313), Jath::Point(139.637, -28.839, 98.094), Jath::Point(140.673, -30.55, 97.861), Jath::Point(141.694, -32.269, 97.861), Jath::Point(142.702, -33.996, 97.611), Jath::Point(143.699, -35.731, 97.343), Jath::Point(144.682, -37.472, 97.056), Jath::Point(145.65, -39.222, 96.749), Jath::Point(146.603, -40.981, 96.749), Jath::Point(147.538, -42.749, 96.419), Jath::Point(148.456, -44.526, 96.066), Jath::Point(149.355, -46.312, 95.688), Jath::Point(150.236, -48.108, 95.282), Jath::Point(151.096, -49.913, 94.846), Jath::Point(151.933, -51.729, 94.379), Jath::Point(152.747, -53.556, 93.879), Jath::Point(153.535, -55.394, 93.342), Jath::Point(154.296, -57.244, 92.767), Jath::Point(155.027, -59.105, 92.151), Jath::Point(155.727, -60.979, 91.491), Jath::Point(156.394, -62.865, 90.785), Jath::Point(157.024, -64.763, 90.031), Jath::Point(157.61, -66.675, 88.368), Jath::Point(158.152, -68.6, 87.454), Jath::Point(158.648, -70.537, 86.484), Jath::Point(159.095, -72.487, 84.368), Jath::Point(159.477, -74.45, 83.222), Jath::Point(159.801, -76.423, 82.018), Jath::Point(160.054, -78.407, 79.447), Jath::Point(160.232, -80.399, 78.087), Jath::Point(160.324, -82.396, 75.252), Jath::Point(160.33, -84.396, 72.326), Jath::Point(160.228, -86.393, 70.86), Jath::Point(160.021, -88.382, 68.002), Jath::Point(159.698, -90.355, 65.363), Jath::Point(159.251, -92.304, 63.102), Jath::Point(158.674, -94.219, 61.369), Jath::Point(157.962, -96.087, 60.288), Jath::Point(157.115, -97.899, 59.934), Jath::Point(156.136, -99.642, 60.318), Jath::Point(155.03, -101.308, 61.392), Jath::Point(153.805, -102.888, 63.055), Jath::Point(152.473, -104.379, 65.175), Jath::Point(151.045, -105.778, 67.608), Jath::Point(149.531, -107.086, 70.215), Jath::Point(147.945, -108.303, 72.878), Jath::Point(146.297, -109.435, 75.504), Jath::Point(144.595, -110.485, 78.026), Jath::Point(142.848, -111.459, 80.401), Jath::Point(141.064, -112.362, 81.524), Jath::Point(139.247, -113.198, 83.636), Jath::Point(137.403, -113.973, 85.565), Jath::Point(135.538, -114.695, 87.315), Jath::Point(133.654, -115.366, 88.896), Jath::Point(131.754, -115.988, 89.627), Jath::Point(129.84, -116.569, 90.98), Jath::Point(127.915, -117.112, 92.199), Jath::Point(125.98, -117.618, 92.762), Jath::Point(124.037, -118.092, 93.806), Jath::Point(122.087, -118.538, 94.291), Jath::Point(120.131, -118.955, 95.19), Jath::Point(118.171, -119.349, 99.57), Jath::Point(116.207, -119.727, 99.437), Jath::Point(114.241, -120.096, 99.29), Jath::Point(112.274, -120.456, 99.136), Jath::Point(110.305, -120.806, 98.973), Jath::Point(108.334, -121.146, 98.803), Jath::Point(106.361, -121.476, 98.624), Jath::Point(104.387, -121.794, 98.437), Jath::Point(102.41, -122.1, 98.036), Jath::Point(100.432, -122.392, 97.823), Jath::Point(98.451, -122.67, 97.601), Jath::Point(96.468, -122.934, 97.133), Jath::Point(94.484, -123.179, 96.887), Jath::Point(92.497, -123.409, 96.634), Jath::Point(90.508, -123.619, 96.109), Jath::Point(88.517, -123.809, 95.838), Jath::Point(86.524, -123.977, 95.286), Jath::Point(84.529, -124.123, 94.73), Jath::Point(82.533, -124.243, 94.454), Jath::Point(80.535, -124.336, 93.917), Jath::Point(78.536, -124.402, 93.415), Jath::Point(76.537, -124.438, 92.969), Jath::Point(74.537, -124.443, 92.602), Jath::Point(72.537, -124.415, 92.337), Jath::Point(70.538, -124.352, 92.197), Jath::Point(68.54, -124.255, 92.201), Jath::Point(66.545, -124.123, 92.365), Jath::Point(64.552, -123.957, 92.697), Jath::Point(62.562, -123.759, 93.2), Jath::Point(60.575, -123.529, 94.256), Jath::Point(58.592, -123.27, 95.137), Jath::Point(56.612, -122.986, 96.129), Jath::Point(54.635, -122.681, 97.201), Jath::Point(52.661, -122.359, 98.882), Jath::Point(50.69, -122.025, 100.002), Jath::Point(48.719, -121.682, 101.082), Jath::Point(46.749, -121.336, 101.219), Jath::Point(44.78, -120.99, 100.556), Jath::Point(42.809, -120.647, 99.794), Jath::Point(40.837, -120.312, 99.149), Jath::Point(38.864, -119.985, 98.625), Jath::Point(36.889, -119.67, 98.216), Jath::Point(34.912, -119.367, 97.917), Jath::Point(32.933, -119.078, 97.806), Jath::Point(30.952, -118.804, 97.653), Jath::Point(28.969, -118.545, 97.582), Jath::Point(26.984, -118.301, 97.581), Jath::Point(24.997, -118.073, 97.603), Jath::Point(23.008, -117.861, 97.686), Jath::Point(21.018, -117.663, 97.743), Jath::Point(19.026, -117.482, 97.883), Jath::Point(17.033, -117.314, 97.963), Jath::Point(15.039, -117.161, 98.14), Jath::Point(13.044, -117.022, 98.235), Jath::Point(11.048, -116.896, 98.332), Jath::Point(9.051, -116.784, 98.533), Jath::Point(7.054, -116.684, 98.635), Jath::Point(5.056, -116.597, 98.737), Jath::Point(3.057, -116.52, 98.839), Jath::Point(1.058, -116.455, 98.94), Jath::Point(-0.941, -116.4, 97.51), Jath::Point(-2.94, -116.341, 97.471), Jath::Point(-4.939, -116.266, 97.42), Jath::Point(-6.937, -116.175, 97.364), Jath::Point(-8.934, -116.068, 97.303), Jath::Point(-10.93, -115.945, 97.235), Jath::Point(-12.925, -115.805, 97.161), Jath::Point(-14.919, -115.647, 96.994), Jath::Point(-16.911, -115.472, 96.9), Jath::Point(-18.902, -115.279, 96.798), Jath::Point(-20.891, -115.068, 96.688), Jath::Point(-22.877, -114.839, 96.569), Jath::Point(-24.862, -114.591, 96.304), Jath::Point(-26.844, -114.322, 96.155), Jath::Point(-28.823, -114.033, 95.996), Jath::Point(-30.799, -113.724, 95.825), Jath::Point(-32.771, -113.395, 95.443), Jath::Point(-34.74, -113.041, 95.231), Jath::Point(-36.704, -112.664, 95.002), Jath::Point(-38.664, -112.266, 94.756), Jath::Point(-40.618, -111.839, 94.207), Jath::Point(-42.566, -111.388, 93.901), Jath::Point(-44.508, -110.91, 93.571), Jath::Point(-46.442, -110.401, 92.832), Jath::Point(-48.369, -109.863, 92.418), Jath::Point(-50.285, -109.291, 91.487), Jath::Point(-52.191, -108.686, 90.965), Jath::Point(-54.085, -108.044, 89.787), Jath::Point(-55.966, -107.362, 89.123), Jath::Point(-57.83, -106.637, 87.621), Jath::Point(-59.676, -105.869, 85.848), Jath::Point(-61.5, -105.048, 84.844), Jath::Point(-63.298, -104.174, 82.562), Jath::Point(-65.067, -103.241, 79.858), Jath::Point(-66.8, -102.243, 76.655), Jath::Point(-68.489, -101.172, 72.87), Jath::Point(-70.124, -100.02, 68.424), Jath::Point(-71.692, -98.779, 63.251), Jath::Point(-73.175, -97.438, 57.33), Jath::Point(-74.554, -95.99, 50.714), Jath::Point(-75.802, -94.428, 43.588), Jath::Point(-76.876, -92.743, 40), Jath::Point(-77.75, -90.946, 40), Jath::Point(-78.368, -89.045, 40), Jath::Point(-78.711, -87.077, 40), Jath::Point(-78.765, -85.08, 40), Jath::Point(-78.532, -83.095, 40), Jath::Point(-78.052, -81.155, 40), Jath::Point(-77.354, -79.282, 50.608), Jath::Point(-76.476, -77.486, 58.016), Jath::Point(-75.454, -75.768, 64.676), Jath::Point(-74.314, -74.125, 70.477), Jath::Point(-73.079, -72.552, 73.054), Jath::Point(-71.76, -71.048, 77.596), Jath::Point(-70.379, -69.603, 81.398), Jath::Point(-68.942, -68.211, 83.054), Jath::Point(-67.458, -66.871, 85.936), Jath::Point(-65.933, -65.577, 87.187), Jath::Point(-64.377, -64.321, 88.326), Jath::Point(-62.787, -63.108, 90.311), Jath::Point(-61.171, -61.929, 91.174), Jath::Point(-59.074, -60.464, 91.96), Jath::Point(-59.074, -60.464, 0),};
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

    smartDrive.m_pos = art::Vec2::XandY(art::Inches(gpsSensorL.xPosition(vex::inches)), art::Inches(gpsSensorL.yPosition(vex::inches)));
    smartDrive.m_dir = art::Degrees(gpsSensorL.heading(vex::degrees));

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

    smartDrive.m_pos = art::Vec2::XandY(art::Inches(gpsSensorL.xPosition(vex::inches)), art::Inches(gpsSensorL.yPosition(vex::inches)));
    smartDrive.m_dir = art::Degrees(gpsSensorL.heading(vex::degrees));

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

int intakeOffDelay1Sec()
{
    vex::wait(0.45, vex::sec);
    intake.set(0);
    return 1;
}

void JathsSketchyFullFlippingAWP()
{
    vex::task antiJamTask(intakeAntiJam);

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

    // resetPositionFromGPS();

    target = art::Vec2::XandY(art::Tiles(2 * xSign), art::Tiles(0 * ySign));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    intake.set(100);
    smartDrive.driveFor(art::Tiles(1.5), 60);
    smartDrive.driveFor(art::Inches(10), 60);
    
    vex::thread intakeOffDelay(intakeOffDelay1Sec);
    // intake.set(0);
    // AutonArmPosRunning = false;

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(2 * xSign), art::Tiles(1 * ySign)));
    // resetPositionFromGPS();

    smartDrive.arcade(0, 0);
    // resetPositionFromGPS();
    vex::wait(0.25, vex::sec);

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(1.1 * xSign), art::Tiles(1 * ySign)));

    smartDrive.driveForPID(art::Inches(-2));
    clamp.set(true);
    intake.set(100);

    smartDrive.arcade(0,0);
    vex::wait(1, vex::sec);
    armTarget = art::Degrees(130);
    armControl = vex::thread(autonArmPos);

    // resetPositionFromGPS();

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(2 * ySign)));

        smartDrive.driveForPID(art::Inches(5));

    smartDrive.driveForPID(art::Inches(-19));

    target = art::Vec2::XandY(art::Tiles(0.75 * xSign), art::Tiles(0.75 * ySign));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveFor(travel.magnitude(), 50);

    smartDrive.arcade(0, 0);
    AutonArmPosRunning = false;
}

void negStackedRings()
{
    vex::task antiJamTask(intakeAntiJam);

    double xSign = 1.0;

    if (smartDrive.m_pos.x < 0)
    {
        xSign = -1.0;
    }

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(1)));

    // target = art::Vec2::XandY(art::Tiles(1 * xSign), art::Tiles(1));
    // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    // smartDrive.driveForPID();

    smartDrive.driveForPID(art::Inches(-2));
    clamp.set(true);

    intake.set(100);

    smartDrive.arcade(0, 0);
    vex::wait(0.25, vex::sec);

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(2)));

    smartDrive.driveForPID(art::Inches(5));
    smartDrive.driveForPID(art::Inches(-15));

    smartDrive.arcade(0, 0);
    vex::wait(0.35, vex::sec);
    // resetPositionFromGPS();

    driveTowardPoint(art::Vec2::XandY(
        art::Inches(10 * xSign), art::Inches(48 - 2)));

    smartDrive.driveForPID(art::Inches(-12));
    smartDrive.arcade(0, 0);
    vex::wait(0.35, vex::sec);
    // resetPositionFromGPS();

    driveTowardPoint(art::Vec2::XandY(
        art::Inches(8 * xSign), art::Inches(48 + 4)));

    smartDrive.driveForPID(art::Inches(-12));

    armTarget = art::Degrees(120);
    vex::thread armControl(autonArmPos);

    target = art::Vec2::XandY(art::Tiles(0.75 * xSign), art::Tiles(0.75));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveFor(travel.magnitude(), 50);

    smartDrive.arcade(0, 0);
    AutonArmPosRunning = false;
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
    Jath::Point(-118.646, 55.537, 8), Jath::Point(-118.7, 53.537, 74.144), Jath::Point(-118.717, 51.537, 73.144), Jath::Point(-118.694, 49.538, 72.144), Jath::Point(-118.628, 47.539, 71.143), Jath::Point(-118.514, 45.542, 70.143), Jath::Point(-118.34, 43.55, 69.143), Jath::Point(-118.112, 41.563, 68.143), Jath::Point(-117.811, 39.586, 67.142), Jath::Point(-117.439, 37.621, 66.142), Jath::Point(-116.975, 35.676, 64.19), Jath::Point(-116.414, 33.756, 60.559), Jath::Point(-115.742, 31.873, 56.352), Jath::Point(-114.94, 30.042, 51.597), Jath::Point(-113.991, 28.283, 46.412), Jath::Point(-112.879, 26.622, 41.04), Jath::Point(-111.587, 25.097, 33.497), Jath::Point(-110.11, 23.751, 29.547), Jath::Point(-108.455, 22.632, 26.419), Jath::Point(-106.651, 21.773, 27.278), Jath::Point(-104.739, 21.195, 31.589), Jath::Point(-102.763, 20.897, 35.676), Jath::Point(-100.764, 20.858, 42.481), Jath::Point(-98.774, 21.04, 49.079), Jath::Point(-96.811, 21.417, 51.138), Jath::Point(-94.885, 21.956, 50.138), Jath::Point(-93.005, 22.635, 49.138), Jath::Point(-91.17, 23.431, 48.137), Jath::Point(-89.382, 24.326, 47.137), Jath::Point(-87.641, 25.31, 46.137), Jath::Point(-85.946, 26.371, 45.137), Jath::Point(-84.295, 27.5, 44.136), Jath::Point(-82.687, 28.689, 43.136), Jath::Point(-81.122, 29.935, 43.197), Jath::Point(-79.599, 31.23, 43.259), Jath::Point(-78.115, 32.571, 43.32), Jath::Point(-76.671, 33.955, 43.381), Jath::Point(-75.266, 35.378, 43.443), Jath::Point(-73.9, 36.839, 43.504), Jath::Point(-72.573, 38.335, 43.565), Jath::Point(-71.286, 39.866, 43.627), Jath::Point(-70.038, 41.428, 43.688), Jath::Point(-68.828, 43.021, 43.749), Jath::Point(-67.66, 44.644, 43.811), Jath::Point(-66.533, 46.297, 43.872), Jath::Point(-65.448, 47.977, 43.933), Jath::Point(-64.405, 49.683, 43.995), Jath::Point(-63.41, 51.418, 43.891), Jath::Point(-62.46, 53.178, 43.787), Jath::Point(-61.559, 54.963, 43.683), Jath::Point(-60.707, 56.773, 43.579), Jath::Point(-59.912, 58.608, 43.475), Jath::Point(-59.159, 60.461, 43.37), Jath::Point(-58.375, 62.3, 43.267), Jath::Point(-57.518, 64.107, 43.163), Jath::Point(-56.592, 65.88, 43.059), Jath::Point(-55.587, 67.608, 42.955), Jath::Point(-54.507, 69.292, 43.859), Jath::Point(-53.347, 70.921, 44.762), Jath::Point(-52.106, 72.488, 45.666), Jath::Point(-50.787, 73.992, 46.57), Jath::Point(-49.393, 75.425, 47.473), Jath::Point(-47.928, 76.786, 48.377), Jath::Point(-46.397, 78.073, 49.281), Jath::Point(-44.807, 79.285, 50.184), Jath::Point(-43.165, 80.427, 51.088), Jath::Point(-41.479, 81.502, 51.992), Jath::Point(-39.756, 82.517, 50.88), Jath::Point(-38.003, 83.481, 49.769), Jath::Point(-36.228, 84.402, 48.657), Jath::Point(-34.437, 85.291, 47.545), Jath::Point(-32.635, 86.159, 46.434), Jath::Point(-30.828, 87.016, 45.322), Jath::Point(-29.022, 87.876, 44.211), Jath::Point(-27.222, 88.748, 43.099), Jath::Point(-25.435, 89.646, 41.987), Jath::Point(-23.667, 90.581, 40.876), Jath::Point(-21.925, 91.563, 42.603), Jath::Point(-20.217, 92.603, 44.33), Jath::Point(-18.551, 93.709, 46.057), Jath::Point(-16.936, 94.889, 47.784), Jath::Point(-15.382, 96.147, 49.511), Jath::Point(-13.897, 97.487, 51.238), Jath::Point(-12.49, 98.907, 52.965), Jath::Point(-11.165, 100.405, 54.692), Jath::Point(-9.929, 101.977, 56.42), Jath::Point(-8.781, 103.614, 55.653), Jath::Point(-7.722, 105.31, 54.886), Jath::Point(-6.753, 107.059, 54.119), Jath::Point(-5.871, 108.854, 53.352), Jath::Point(-5.064, 110.684, 52.585), Jath::Point(-4.342, 112.549, 51.819), Jath::Point(-3.683, 114.437, 51.052), Jath::Point(-3.1, 116.35, 50.285), Jath::Point(-2.574, 118.279, 49.518), Jath::Point(-2.102, 120.223, 48.751), Jath::Point(-1.69, 122.18, 48.751), Jath::Point(-1.326, 124.146, 48.751), Jath::Point(-1.006, 126.121, 48.751), Jath::Point(-0.727, 128.101, 48.751), Jath::Point(-0.487, 130.086, 48.751), Jath::Point(-0.283, 132.076, 48.751), Jath::Point(-0.114, 134.069, 48.751), Jath::Point(0.025, 136.064, 48.751), Jath::Point(0.133, 138.061, 48.751), Jath::Point(0.215, 140.059, 48.751), Jath::Point(0.272, 142.058, 48.751), Jath::Point(0.305, 144.058, 48.751), Jath::Point(0.316, 146.058, 48.751), Jath::Point(0.308, 148.058, 48.751), Jath::Point(0.277, 150.058, 48.751), Jath::Point(0.226, 152.057, 48.751), Jath::Point(0.159, 154.056, 48.751), Jath::Point(0.077, 156.054, 48.751), Jath::Point(-0.021, 158.052, 48.751), Jath::Point(-0.137, 160.048, 48.751), Jath::Point(-0.391, 163.862, 48.75), Jath::Point(-0.391, 163.862, 0), 
};
Jath::Path rings1Path = Jath::Path::cm(rings1PathPoints);

std::vector<Jath::Point> rings1_5PathPoints = {
    Jath::Point(8.671, 160.354, 8), Jath::Point(8.415, 158.37, 84.059), Jath::Point(8.153, 156.387, 83.376), Jath::Point(7.885, 154.405, 82.694), Jath::Point(7.604, 152.425, 82.011), Jath::Point(7.315, 150.446, 81.328), Jath::Point(7.018, 148.468, 80.645), Jath::Point(6.71, 146.492, 79.963), Jath::Point(6.391, 144.518, 79.28), Jath::Point(6.063, 142.545, 78.597), Jath::Point(5.726, 140.574, 77.914), Jath::Point(5.374, 138.605, 77.231), Jath::Point(5.01, 136.638, 76.549), Jath::Point(4.636, 134.673, 75.866), Jath::Point(4.25, 132.711, 75.183), Jath::Point(3.85, 130.751, 74.5), Jath::Point(3.434, 128.795, 73.818), Jath::Point(3.005, 126.842, 73.135), Jath::Point(2.56, 124.892, 72.452), Jath::Point(2.1, 122.946, 71.769), Jath::Point(1.624, 121.003, 71.087), Jath::Point(1.13, 119.065, 70.404), Jath::Point(0.617, 117.132, 69.721), Jath::Point(0.085, 115.204, 69.038), Jath::Point(-0.468, 113.282, 68.355), Jath::Point(-1.044, 111.367, 67.673), Jath::Point(-1.643, 109.459, 66.99), Jath::Point(-2.268, 107.559, 66.307), Jath::Point(-2.92, 105.668, 65.624), Jath::Point(-3.6, 103.787, 64.942), Jath::Point(-4.312, 101.918, 64.259), Jath::Point(-5.056, 100.062, 63.576), Jath::Point(-5.836, 98.22, 62.893), Jath::Point(-6.656, 96.396, 62.211), Jath::Point(-7.522, 94.593, 61.528), Jath::Point(-8.432, 92.813, 60.845), Jath::Point(-9.396, 91.061, 60.162), Jath::Point(-10.419, 89.342, 59.48), Jath::Point(-11.506, 87.663, 58.797), Jath::Point(-12.663, 86.033, 57.027), Jath::Point(-13.906, 84.466, 51.136), Jath::Point(-15.237, 82.974, 44.134), Jath::Point(-16.669, 81.579, 36.015), Jath::Point(-18.212, 80.308, 26.952), Jath::Point(-19.871, 79.194, 17.41), Jath::Point(-21.648, 78.279, 14), Jath::Point(-23.533, 77.616, 14), Jath::Point(-25.494, 77.233, 14), Jath::Point(-27.491, 77.169, 14), Jath::Point(-29.474, 77.404, 14), Jath::Point(-31.404, 77.923, 15.464), Jath::Point(-33.257, 78.672, 24.787), Jath::Point(-35.019, 79.618, 37.923), Jath::Point(-36.687, 80.719, 45.509), Jath::Point(-38.269, 81.943, 47.872), Jath::Point(-39.769, 83.265, 47.19), Jath::Point(-41.192, 84.67, 46.507), Jath::Point(-42.548, 86.14, 45.824), Jath::Point(-43.846, 87.661, 45.141), Jath::Point(-45.083, 89.232, 44.459), Jath::Point(-46.274, 90.839, 43.776), Jath::Point(-47.415, 92.482, 43.093), Jath::Point(-48.517, 94.151, 42.41), Jath::Point(-49.578, 95.846, 41.728), Jath::Point(-50.602, 97.563, 41.045), Jath::Point(-51.595, 99.299, 40.362), Jath::Point(-52.558, 101.052, 39.679), Jath::Point(-53.489, 102.822, 39.713), Jath::Point(-54.394, 104.606, 39.746), Jath::Point(-55.273, 106.402, 39.78), Jath::Point(-56.129, 108.21, 39.814), Jath::Point(-56.963, 110.028, 39.847), Jath::Point(-57.775, 111.856, 39.881), Jath::Point(-58.567, 113.692, 39.914), Jath::Point(-59.339, 115.537, 39.948), Jath::Point(-60.093, 117.389, 39.982), Jath::Point(-60.83, 119.249, 40.01), Jath::Point(-61.479, 121.14, 40.049), Jath::Point(-62.104, 123.039, 40.082), Jath::Point(-62.739, 124.936, 40.116), Jath::Point(-63.384, 126.829, 40.15), Jath::Point(-64.042, 128.718, 40.183), Jath::Point(-64.713, 130.602, 45.943), Jath::Point(-65.398, 132.481, 51.703), Jath::Point(-66.097, 134.355, 57.463), Jath::Point(-66.813, 136.222, 63.222), Jath::Point(-67.547, 138.083, 68.982), Jath::Point(-68.3, 139.935, 74.742), Jath::Point(-69.076, 141.779, 78.798), Jath::Point(-69.876, 143.612, 77.868), Jath::Point(-70.703, 145.433, 76.82), Jath::Point(-71.563, 147.238, 74.301), Jath::Point(-72.459, 149.026, 72.792), Jath::Point(-73.393, 150.794, 71.085), Jath::Point(-74.377, 152.536, 66.981), Jath::Point(-75.412, 154.247, 64.527), Jath::Point(-76.514, 155.916, 58.663), Jath::Point(-77.69, 157.533, 51.336), Jath::Point(-78.954, 159.082, 42.385), Jath::Point(-80.325, 160.537, 31.846), Jath::Point(-81.818, 161.867, 20.123), Jath::Point(-83.449, 163.022, 14), Jath::Point(-85.22, 163.947, 14), Jath::Point(-87.115, 164.579, 14), Jath::Point(-89.089, 164.886, 14), Jath::Point(-91.087, 164.877, 14), Jath::Point(-93.067, 164.598, 25.052), Jath::Point(-95.006, 164.11, 41.86), Jath::Point(-96.9, 163.472, 47.291), Jath::Point(-98.756, 162.727, 45.631), Jath::Point(-100.58, 161.906, 43.97), Jath::Point(-102.382, 161.038, 42.31), Jath::Point(-104.17, 160.142, 40.649), Jath::Point(-105.951, 159.233, 38.989), Jath::Point(-107.732, 158.323, 37.328), Jath::Point(-109.519, 157.423, 35.668), Jath::Point(-111.314, 156.543, 34.007), Jath::Point(-113.123, 155.689, 32.347), Jath::Point(-114.947, 154.87, 30.686), Jath::Point(-116.79, 154.091, 29.026), Jath::Point(-118.651, 153.359, 29.026), Jath::Point(-120.531, 152.679, 29.026), Jath::Point(-122.433, 152.058, 29.026), Jath::Point(-124.353, 151.5, 29.026), Jath::Point(-126.291, 151.006, 29.026), Jath::Point(-128.244, 150.579, 29.026), Jath::Point(-130.213, 150.228, 29.026), Jath::Point(-132.194, 149.949, 29.026), Jath::Point(-134.183, 149.742, 29.026), Jath::Point(-136.179, 149.616, 29.026), Jath::Point(-138.178, 149.56, 29.026), Jath::Point(-140.177, 149.584, 29.026), Jath::Point(-142.175, 149.673, 29.026), Jath::Point(-144.988, 149.927, 29.02), Jath::Point(-144.988, 149.927, 0), 
};
Jath::Path rings1_5Path = Jath::Path::cm(rings1_5PathPoints);

std::vector<Jath::Point> rings1_6PathPoints = {
    Jath::Point(-153.768, 150.476, 57.74), Jath::Point(-151.768, 150.467, 57.745), Jath::Point(-149.768, 150.459, 57.745), Jath::Point(-147.768, 150.45, 57.745), Jath::Point(-145.768, 150.442, 57.745), Jath::Point(-143.768, 150.433, 57.745), Jath::Point(-141.768, 150.425, 57.745), Jath::Point(-139.768, 150.416, 57.745), Jath::Point(-137.768, 150.408, 57.745), Jath::Point(-135.768, 150.399, 57.745), Jath::Point(-133.768, 150.391, 57.745), Jath::Point(-131.768, 150.382, 57.745), Jath::Point(-129.769, 150.373, 57.745), Jath::Point(-127.769, 150.365, 57.745), Jath::Point(-125.769, 150.356, 57.745), Jath::Point(-123.769, 150.348, 57.745), Jath::Point(-121.769, 150.339, 57.745), Jath::Point(-119.769, 150.331, 57.745), Jath::Point(-117.769, 150.322, 57.745), Jath::Point(-115.769, 150.314, 57.745), Jath::Point(-113.769, 150.305, 57.745), Jath::Point(-111.769, 150.297, 57.745), Jath::Point(-109.769, 150.288, 57.745), Jath::Point(-107.769, 150.28, 57.745), Jath::Point(-105.769, 150.271, 57.745), Jath::Point(-103.769, 150.263, 57.745), Jath::Point(-101.769, 150.254, 57.745), Jath::Point(-99.769, 150.246, 57.745), Jath::Point(-97.769, 150.237, 57.745), Jath::Point(-95.769, 150.229, 57.745), Jath::Point(-93.769, 150.22, 57.745), Jath::Point(-91.769, 150.212, 57.745), Jath::Point(-89.769, 150.203, 57.745), Jath::Point(-87.769, 150.195, 57.745), Jath::Point(-85.769, 150.186, 57.745), Jath::Point(-83.769, 150.178, 57.745), Jath::Point(-81.769, 150.169, 57.745), Jath::Point(-79.769, 150.161, 57.745), Jath::Point(-77.769, 150.152, 57.745), Jath::Point(-75.769, 150.144, 57.745), Jath::Point(-73.769, 150.135, 57.745), Jath::Point(-71.769, 150.127, 57.745), Jath::Point(-69.769, 150.118, 57.745), Jath::Point(-67.769, 150.11, 57.745), Jath::Point(-65.769, 150.101, 57.745), Jath::Point(-63.769, 150.093, 57.745), Jath::Point(-61.769, 150.084, 57.745), Jath::Point(-59.769, 150.076, 57.745), Jath::Point(-57.769, 150.067, 57.745), Jath::Point(-55.769, 150.059, 57.745), Jath::Point(-53.769, 150.05, 57.745), Jath::Point(-51.769, 150.042, 57.745), Jath::Point(-49.769, 150.033, 57.745), Jath::Point(-47.769, 150.025, 57.745), Jath::Point(-45.769, 150.016, 57.745), Jath::Point(-43.769, 150.008, 57.745), Jath::Point(-41.769, 149.999, 57.745), Jath::Point(-39.769, 149.991, 57.745), Jath::Point(-37.769, 149.982, 57.745), Jath::Point(-35.769, 149.973, 57.745), Jath::Point(-33.769, 149.965, 57.745), Jath::Point(-31.769, 149.956, 57.745), Jath::Point(-29.769, 149.948, 57.745), Jath::Point(-27.769, 149.939, 57.745), Jath::Point(-24.805, 149.927, 57.74), Jath::Point(-24.805, 149.927, 0)};
Jath::Path rings1_6Path = Jath::Path::cm(rings1_6PathPoints);

std::vector<Jath::Point> rings1_75PathPoints = {
    Jath::Point(-21.512, 148.28, 48.67), Jath::Point(-22.671, 146.65, 51.081), Jath::Point(-23.771, 144.981, 55.824), Jath::Point(-24.818, 143.276, 59.711), Jath::Point(-25.819, 141.545, 66.564), Jath::Point(-26.785, 139.794, 74.278), Jath::Point(-27.729, 138.031, 72.133), Jath::Point(-28.667, 136.264, 69.989), Jath::Point(-29.616, 134.504, 65.627), Jath::Point(-30.596, 132.76, 54.303), Jath::Point(-31.626, 131.046, 42.843), Jath::Point(-32.726, 129.376, 31.864), Jath::Point(-33.913, 127.767, 22.196), Jath::Point(-35.2, 126.236, 14.783), Jath::Point(-36.594, 124.803, 14), Jath::Point(-38.094, 123.481, 14), Jath::Point(-39.693, 122.281, 14), Jath::Point(-41.378, 121.204, 18.098), Jath::Point(-43.136, 120.252, 22.919), Jath::Point(-44.952, 119.416, 30.983), Jath::Point(-46.815, 118.688, 36.503), Jath::Point(-48.713, 118.057, 39.967), Jath::Point(-50.637, 117.514, 37.822), Jath::Point(-52.582, 117.049, 38.255), Jath::Point(-54.543, 116.653, 38.687), Jath::Point(-56.514, 116.318, 39.12), Jath::Point(-58.494, 116.037, 39.552), Jath::Point(-60.481, 115.808, 39.985), Jath::Point(-62.472, 115.619, 40.417), Jath::Point(-64.467, 115.473, 40.85), Jath::Point(-66.463, 115.358, 41.282), Jath::Point(-68.462, 115.279, 42.702), Jath::Point(-70.461, 115.228, 44.121), Jath::Point(-72.461, 115.203, 45.541), Jath::Point(-74.461, 115.202, 46.96), Jath::Point(-76.461, 115.225, 48.38), Jath::Point(-78.46, 115.268, 49.799), Jath::Point(-80.459, 115.33, 51.219), Jath::Point(-82.458, 115.409, 52.638), Jath::Point(-84.455, 115.505, 54.058), Jath::Point(-86.452, 115.615, 55.477), Jath::Point(-88.448, 115.741, 56.897), Jath::Point(-90.444, 115.879, 58.316), Jath::Point(-92.438, 116.03, 59.736), Jath::Point(-94.431, 116.192, 57.233), Jath::Point(-96.424, 116.365, 54.73), Jath::Point(-98.415, 116.549, 52.227), Jath::Point(-100.406, 116.742, 49.725), Jath::Point(-102.396, 116.945, 47.222), Jath::Point(-104.384, 117.157, 44.719), Jath::Point(-106.372, 117.377, 42.216), Jath::Point(-108.359, 117.605, 39.713), Jath::Point(-110.345, 117.839, 37.21), Jath::Point(-112.331, 118.082, 37.21), Jath::Point(-114.315, 118.332, 37.21), Jath::Point(-116.299, 118.587, 37.21), Jath::Point(-118.281, 118.848, 37.2), Jath::Point(-120.263, 119.117, 37.21), Jath::Point(-122.258, 119.221, 37.21), Jath::Point(-124.257, 119.258, 37.21), Jath::Point(-126.257, 119.295, 37.21), Jath::Point(-128.257, 119.331, 37.21), Jath::Point(-130.256, 119.368, 37.21), Jath::Point(-132.256, 119.405, 37.21), Jath::Point(-134.256, 119.441, 37.21), Jath::Point(-136.255, 119.478, 37.21), Jath::Point(-138.255, 119.515, 37.21), Jath::Point(-140.255, 119.552, 37.21), Jath::Point(-142.254, 119.588, 37.21), Jath::Point(-144.254, 119.625, 37.21), Jath::Point(-146.254, 119.662, 37.21), Jath::Point(-148.253, 119.698, 37.21), Jath::Point(-149.758, 119.726, 37.2), Jath::Point(-149.758, 119.726, 0), 
};
Jath::Path rings1_75Path = Jath::Path::cm(rings1_75PathPoints);

std::vector<Jath::Point> goal3PathPoints = {
    Jath::Point(-177.88, -0.435, 90.46), Jath::Point(-176.216, -1.544, 90.462), Jath::Point(-174.556, -2.659, 90.24), Jath::Point(-172.9, -3.78, 90.008), Jath::Point(-171.25, -4.912, 90.008), Jath::Point(-169.607, -6.051, 89.766), Jath::Point(-167.969, -7.199, 89.514), Jath::Point(-166.336, -8.354, 89.252), Jath::Point(-164.711, -9.52, 89.252), Jath::Point(-163.093, -10.695, 88.98), Jath::Point(-161.481, -11.88, 88.697), Jath::Point(-159.877, -13.074, 88.406), Jath::Point(-158.28, -14.278, 88.104), Jath::Point(-156.691, -15.493, 88.104), Jath::Point(-155.112, -16.72, 87.795), Jath::Point(-153.542, -17.958, 87.477), Jath::Point(-151.98, -19.208, 87.151), Jath::Point(-150.429, -20.47, 86.82), Jath::Point(-148.888, -21.745, 86.484), Jath::Point(-147.358, -23.033, 86.144), Jath::Point(-145.839, -24.334, 85.803), Jath::Point(-144.332, -25.649, 85.463), Jath::Point(-142.837, -26.978, 85.126), Jath::Point(-141.356, -28.322, 84.795), Jath::Point(-139.889, -29.681, 84.164), Jath::Point(-138.437, -31.057, 83.871), Jath::Point(-137, -32.448, 83.6), Jath::Point(-135.579, -33.855, 83.355), Jath::Point(-134.173, -35.278, 82.963), Jath::Point(-132.787, -36.719, 82.829), Jath::Point(-131.417, -38.176, 82.744), Jath::Point(-130.065, -39.65, 82.749), Jath::Point(-128.733, -41.142, 82.853), Jath::Point(-127.418, -42.648, 83.298), Jath::Point(-126.122, -44.172, 83.074), Jath::Point(-124.843, -45.71, 82.779), Jath::Point(-123.581, -47.261, 82.484), Jath::Point(-122.335, -48.825, 82.189), Jath::Point(-121.101, -50.399, 81.894), Jath::Point(-119.878, -51.981, 81.599), Jath::Point(-118.661, -53.569, 81.304), Jath::Point(-117.446, -55.157, 81.009), Jath::Point(-116.228, -56.744, 80.714), Jath::Point(-115.001, -58.323, 80.42), Jath::Point(-113.758, -59.89, 79.458), Jath::Point(-112.493, -61.439, 75.472), Jath::Point(-111.2, -62.965, 71.807), Jath::Point(-109.874, -64.462, 68.648), Jath::Point(-108.51, -65.924, 66.151), Jath::Point(-107.104, -67.347, 64.428), Jath::Point(-105.656, -68.726, 63.532), Jath::Point(-104.165, -70.059, 63.45), Jath::Point(-102.632, -71.343, 64.113), Jath::Point(-101.059, -72.579, 65.403), Jath::Point(-99.45, -73.767, 67.175), Jath::Point(-97.806, -74.906, 68.194), Jath::Point(-96.132, -75.999, 70.405), Jath::Point(-94.432, -77.052, 72.736), Jath::Point(-92.705, -78.061, 73.91), Jath::Point(-90.958, -79.036, 75.701), Jath::Point(-89.191, -79.972, 75.406), Jath::Point(-87.408, -80.878, 75.111), Jath::Point(-85.609, -81.752, 74.816), Jath::Point(-83.797, -82.598, 74.521), Jath::Point(-81.974, -83.419, 74.226), Jath::Point(-80.14, -84.218, 73.931), Jath::Point(-78.296, -84.992, 73.637), Jath::Point(-76.443, -85.746, 73.342), Jath::Point(-74.583, -86.481, 73.047), Jath::Point(-72.717, -87.199, 72.752), Jath::Point(-70.844, -87.9, 72.457), Jath::Point(-68.965, -88.587, 72.162), Jath::Point(-67.082, -89.259, 71.867), Jath::Point(-65.194, -89.918, 71.572), Jath::Point(-63.301, -90.565, 71.277), Jath::Point(-61.405, -91.201, 70.98), Jath::Point(-59.505, -91.826, 70.687), Jath::Point(-57.533, -92.153, 70.393), Jath::Point(-55.558, -92.466, 70.098), Jath::Point(-53.584, -92.787, 69.803), Jath::Point(-51.611, -93.113, 69.508), Jath::Point(-49.638, -93.444, 69.213), Jath::Point(-47.667, -93.779, 68.918), Jath::Point(-45.695, -94.117, 68.623), Jath::Point(-43.724, -94.456, 68.328), Jath::Point(-41.753, -94.795, 68.033), Jath::Point(-39.782, -95.133, 67.738), Jath::Point(-37.81, -95.468, 67.443), Jath::Point(-35.838, -95.799, 67.149), Jath::Point(-33.865, -96.124, 66.854), Jath::Point(-31.89, -96.441, 66.559), Jath::Point(-29.914, -96.749, 66.264), Jath::Point(-27.936, -97.044, 65.969), Jath::Point(-25.955, -97.326, 65.674), Jath::Point(-23.973, -97.591, 65.379), Jath::Point(-21.988, -97.837, 65.084), Jath::Point(-20.001, -98.062, 64.789), Jath::Point(-18.011, -98.262, 64.494), Jath::Point(-16.019, -98.435, 64.199), Jath::Point(-14.024, -98.576, 63.904), Jath::Point(-12.027, -98.684, 63.61), Jath::Point(-10.028, -98.753, 63.315), Jath::Point(-8.028, -98.78, 63.02), Jath::Point(-6.028, -98.761, 62.725), Jath::Point(-4.029, -98.692, 62.43), Jath::Point(-2.033, -98.568, 62.135), Jath::Point(-0.042, -98.386, 61.84), Jath::Point(1.943, -98.142, 61.545), Jath::Point(3.919, -97.831, 59.765), Jath::Point(5.882, -97.449, 60.955), Jath::Point(7.829, -96.994, 57.645), Jath::Point(9.757, -96.463, 54.334), Jath::Point(11.663, -95.855, 51.024), Jath::Point(13.541, -95.17, 47.714), Jath::Point(15.389, -94.406, 44.403), Jath::Point(17.204, -93.566, 41.093), Jath::Point(18.982, -92.65, 37.782), Jath::Point(20.719, -91.66, 34.472), Jath::Point(22.415, -90.6, 31.161), Jath::Point(24.068, -89.473, 27.851), Jath::Point(25.676, -88.284, 24.54), Jath::Point(27.239, -87.036, 27.918), Jath::Point(28.756, -85.734, 31.296), Jath::Point(30.23, -84.382, 34.674), Jath::Point(31.66, -82.984, 38.052), Jath::Point(33.049, -81.545, 41.43), Jath::Point(34.394, -80.065, 44.807), Jath::Point(35.7, -78.551, 48.185), Jath::Point(36.97, -77.005, 48.185), Jath::Point(38.199, -75.428, 48.185), Jath::Point(39.454, -73.888, 48.18), Jath::Point(41.139, -72.81, 48.185), Jath::Point(42.799, -71.695, 48.185), Jath::Point(44.433, -70.541, 48.185), Jath::Point(46.036, -69.346, 48.185), Jath::Point(47.612, -68.115, 48.185), Jath::Point(49.157, -66.844, 48.185), Jath::Point(50.671, -65.538, 48.185), Jath::Point(52.155, -64.197, 48.185), Jath::Point(53.608, -62.823, 48.185), Jath::Point(55.03, -61.416, 48.185), Jath::Point(56.424, -59.983, 48.185), Jath::Point(57.789, -58.52, 48.185), Jath::Point(59.128, -57.035, 48.185), Jath::Point(60.445, -55.53, 48.185), Jath::Point(61.74, -54.006, 48.185), Jath::Point(63.019, -52.468, 48.185), Jath::Point(64.286, -50.921, 48.185), Jath::Point(65.546, -49.367, 48.185), Jath::Point(66.805, -47.813, 48.185), Jath::Point(68.069, -46.264, 48.185), Jath::Point(69.347, -44.725, 48.185), Jath::Point(70.645, -43.204, 48.185), Jath::Point(71.974, -41.709, 48.185), Jath::Point(73.341, -40.249, 48.185), Jath::Point(74.755, -38.835, 48.185), Jath::Point(76.225, -37.48, 47.309), Jath::Point(77.761, -36.198, 37.463), Jath::Point(79.365, -35.004, 31.975), Jath::Point(81.039, -33.911, 27.849), Jath::Point(82.782, -32.932, 25.447), Jath::Point(84.589, -32.076, 24.986), Jath::Point(86.452, -31.35, 26.477), Jath::Point(88.361, -30.756, 29.717), Jath::Point(90.306, -30.29, 34.33), Jath::Point(92.276, -29.947, 39.851), Jath::Point(94.262, -29.715, 45.813), Jath::Point(96.257, -29.587, 48.185), Jath::Point(98.257, -29.558, 48.185), Jath::Point(100.256, -29.607, 48.185), Jath::Point(102.252, -29.738, 48.185), Jath::Point(104.242, -29.93, 48.185), Jath::Point(106.226, -30.187, 48.185), Jath::Point(108.201, -30.497, 48.185), Jath::Point(110.169, -30.854, 48.185), Jath::Point(112.129, -31.252, 48.185), Jath::Point(114.08, -31.694, 48.185), Jath::Point(116.022, -32.17, 48.185), Jath::Point(117.956, -32.678, 48.185), Jath::Point(119.883, -33.215, 48.185), Jath::Point(121.802, -33.778, 48.185), Jath::Point(123.714, -34.366, 48.185), Jath::Point(125.618, -34.976, 48.185), Jath::Point(127.516, -35.606, 48.185), Jath::Point(129.408, -36.255, 48.185), Jath::Point(131.293, -36.924, 48.185), Jath::Point(133.172, -37.609, 48.185), Jath::Point(135.046, -38.309, 48.185), Jath::Point(136.914, -39.022, 48.185), Jath::Point(138.778, -39.748, 48.185), Jath::Point(140.636, -40.487, 48.185), Jath::Point(142.489, -41.239, 48.185), Jath::Point(144.339, -42.001, 48.185), Jath::Point(146.184, -42.772, 48.185), Jath::Point(148.024, -43.555, 48.185), Jath::Point(149.861, -44.347, 48.185), Jath::Point(151.695, -45.145, 48.185), Jath::Point(153.524, -45.954, 48.185), Jath::Point(155.35, -46.77, 48.185), Jath::Point(157.173, -47.592, 48.185), Jath::Point(158.992, -48.424, 48.185), Jath::Point(160.808, -49.261, 48.185), Jath::Point(162.622, -50.103, 48.185), Jath::Point(165.869, -51.631, 48.18), Jath::Point(165.869, -51.631, 0), 
};
Jath::Path goal3Path = Jath::Path::cm(goal3PathPoints);

std::vector<Jath::Point> RingsFinal1Points = {
    Jath::Point(120.477, -0.435, 97.64),
    Jath::Point(120.31, -2.428, 97.644),
    Jath::Point(120.133, -4.42, 97.46),
    Jath::Point(119.948, -6.411, 96.369),
    Jath::Point(119.753, -8.402, 94.825),
    Jath::Point(119.549, -10.391, 93.281),
    Jath::Point(119.333, -12.38, 91.737),
    Jath::Point(119.107, -14.367, 90.194),
    Jath::Point(118.868, -16.352, 88.65),
    Jath::Point(118.616, -18.337, 87.106),
    Jath::Point(118.351, -20.319, 85.562),
    Jath::Point(118.073, -22.299, 84.018),
    Jath::Point(117.78, -24.278, 82.475),
    Jath::Point(117.471, -26.254, 80.931),
    Jath::Point(117.146, -28.227, 79.387),
    Jath::Point(116.802, -30.198, 77.843),
    Jath::Point(116.44, -32.164, 76.3),
    Jath::Point(116.057, -34.127, 74.756),
    Jath::Point(115.654, -36.086, 73.212),
    Jath::Point(115.227, -38.04, 71.668),
    Jath::Point(114.777, -39.989, 70.124),
    Jath::Point(114.298, -41.931, 68.581),
    Jath::Point(113.79, -43.865, 67.037),
    Jath::Point(113.252, -45.791, 65.493),
    Jath::Point(112.678, -47.707, 63.949),
    Jath::Point(112.066, -49.611, 60.747),
    Jath::Point(111.414, -51.502, 57.545),
    Jath::Point(110.716, -53.376, 54.343),
    Jath::Point(109.967, -55.23, 51.141),
    Jath::Point(109.163, -57.062, 47.939),
    Jath::Point(108.296, -58.864, 44.736),
    Jath::Point(107.358, -60.63, 41.534),
    Jath::Point(106.343, -62.353, 38.332),
    Jath::Point(105.242, -64.022, 38.248),
    Jath::Point(104.044, -65.623, 38.163),
    Jath::Point(102.737, -67.136, 38.079),
    Jath::Point(101.316, -68.543, 32.963),
    Jath::Point(99.774, -69.815, 23.157),
    Jath::Point(98.112, -70.925, 18),
    Jath::Point(96.334, -71.839, 18),
    Jath::Point(94.462, -72.538, 18),
    Jath::Point(92.519, -73.008, 18),
    Jath::Point(90.535, -73.25, 22.822),
    Jath::Point(88.536, -73.278, 32.11),
    Jath::Point(86.544, -73.108, 37.321),
    Jath::Point(84.574, -72.77, 37.237),
    Jath::Point(82.633, -72.289, 37.152),
    Jath::Point(80.727, -71.684, 37.068),
    Jath::Point(78.857, -70.975, 36.984),
    Jath::Point(77.022, -70.179, 38.869),
    Jath::Point(75.222, -69.309, 40.754),
    Jath::Point(73.453, -68.375, 42.639),
    Jath::Point(71.715, -67.386, 44.524),
    Jath::Point(70.004, -66.351, 46.41),
    Jath::Point(68.319, -65.273, 48.295),
    Jath::Point(66.658, -64.16, 50.18),
    Jath::Point(65.017, -63.016, 52.065),
    Jath::Point(63.397, -61.844, 53.95),
    Jath::Point(61.794, -60.648, 55.83),
    Jath::Point(60.263, -59.364, 57.721),
    Jath::Point(58.805, -57.995, 59.606),
    Jath::Point(57.347, -56.626, 61.491),
    Jath::Point(55.889, -55.257, 63.376),
    Jath::Point(54.432, -53.887, 69.647),
    Jath::Point(52.975, -52.517, 75.918),
    Jath::Point(51.518, -51.147, 82.188),
    Jath::Point(50.062, -49.776, 88.459),
    Jath::Point(48.607, -48.404, 94.729),
    Jath::Point(47.153, -47.031, 101),
    Jath::Point(45.7, -45.656, 100.431),
    Jath::Point(44.249, -44.279, 99.863),
    Jath::Point(42.801, -42.901, 99.294),
    Jath::Point(41.355, -41.518, 98.725),
    Jath::Point(39.913, -40.132, 98.157),
    Jath::Point(38.477, -38.74, 97.588),
    Jath::Point(37.047, -37.342, 97.019),
    Jath::Point(35.626, -35.935, 96.451),
    Jath::Point(34.212, -34.52, 95.882),
    Jath::Point(32.807, -33.097, 95.313),
    Jath::Point(31.407, -31.669, 94.744),
    Jath::Point(30.011, -30.236, 94.176),
    Jath::Point(28.617, -28.802, 93.607),
    Jath::Point(27.224, -27.367, 93.038),
    Jath::Point(25.83, -25.933, 88.994),
    Jath::Point(24.436, -24.5, 84.949),
    Jath::Point(23.04, -23.067, 80.904),
    Jath::Point(21.643, -21.636, 76.859),
    Jath::Point(20.245, -20.205, 72.814),
    Jath::Point(18.846, -18.776, 68.769),
    Jath::Point(17.446, -17.348, 64.725),
    Jath::Point(16.044, -15.921, 60.68),
    Jath::Point(14.642, -14.495, 56.635),
    Jath::Point(13.239, -13.07, 52.59),
    Jath::Point(11.835, -11.646, 48.545),
    Jath::Point(10.43, -10.223, 44.5),
    Jath::Point(9.024, -8.8, 40.456),
    Jath::Point(7.617, -7.378, 36.411),
    Jath::Point(6.21, -5.957, 36.411),
    Jath::Point(4.802, -4.536, 36.411),
    Jath::Point(3.394, -3.117, 36.411),
    Jath::Point(1.985, -1.697, 36.411),
    Jath::Point(0.575, -0.278, 36.411),
    Jath::Point(-0.835, 1.14, 36.411),
    Jath::Point(-2.246, 2.558, 36.411),
    Jath::Point(-3.657, 3.975, 36.411),
    Jath::Point(-5.068, 5.392, 36.411),
    Jath::Point(-6.48, 6.808, 36.411),
    Jath::Point(-7.893, 8.224, 36.411),
    Jath::Point(-9.306, 9.64, 36.411),
    Jath::Point(-10.719, 11.055, 36.411),
    Jath::Point(-12.132, 12.47, 36.411),
    Jath::Point(-14.265, 14.603, 36.41),
    Jath::Point(-14.265, 14.603, 0),
};
Jath::Path RingsFinal1 = Jath::Path::cm(RingsFinal1Points);

std::vector<Jath::Point> RingsFinal2Points = {
    Jath::Point(122.882, -4.522, 82.17), Jath::Point(121.788, -2.848, 81.986), Jath::Point(120.684, -1.181, 81.792), Jath::Point(119.571, 0.481, 81.592), Jath::Point(118.447, 2.135, 81.171), Jath::Point(117.312, 3.782, 80.951), Jath::Point(116.166, 5.421, 80.01), Jath::Point(115.007, 7.051, 78.94), Jath::Point(113.836, 8.672, 77.87), Jath::Point(112.651, 10.284, 76.8), Jath::Point(111.453, 11.885, 75.729), Jath::Point(110.24, 13.475, 74.659), Jath::Point(109.012, 15.054, 73.589), Jath::Point(107.768, 16.62, 72.519), Jath::Point(106.506, 18.172, 71.449), Jath::Point(105.228, 19.709, 70.379), Jath::Point(103.931, 21.232, 69.308), Jath::Point(102.614, 22.738, 68.238), Jath::Point(101.278, 24.226, 67.168), Jath::Point(99.921, 25.695, 66.098), Jath::Point(98.543, 27.144, 65.028), Jath::Point(97.142, 28.572, 63.958), Jath::Point(95.719, 29.977, 62.888), Jath::Point(94.274, 31.359, 61.817), Jath::Point(92.805, 32.716, 60.747), Jath::Point(91.313, 34.049, 59.677), Jath::Point(89.799, 35.356, 58.607), Jath::Point(88.265, 36.638, 57.537), Jath::Point(86.71, 37.896, 56.467), Jath::Point(85.137, 39.131, 55.397), Jath::Point(83.547, 40.345, 54.326), Jath::Point(81.945, 41.542, 53.256), Jath::Point(80.333, 42.725, 52.186), Jath::Point(78.713, 43.899, 51.116), Jath::Point(77.091, 45.068, 50.046), Jath::Point(75.469, 46.238, 48.976), Jath::Point(73.851, 47.414, 47.906), Jath::Point(72.241, 48.601, 46.835), Jath::Point(70.643, 49.804, 45.765), Jath::Point(69.059, 51.025, 44.695), Jath::Point(67.493, 52.269, 43.625), Jath::Point(65.946, 53.536, 42.555), Jath::Point(64.42, 54.829, 44.388), Jath::Point(62.918, 56.149, 46.22), Jath::Point(61.438, 57.495, 48.053), Jath::Point(59.983, 58.867, 49.88), Jath::Point(58.644, 60.351, 51.718), Jath::Point(57.363, 61.887, 53.551), Jath::Point(56.126, 63.459, 55.383), Jath::Point(54.939, 65.068, 57.216), Jath::Point(53.81, 66.718, 59.049), Jath::Point(52.74, 68.408, 60.881), Jath::Point(51.738, 70.138, 62.714), Jath::Point(50.814, 71.912, 59.364), Jath::Point(49.975, 73.728, 56.014), Jath::Point(49.229, 75.583, 52.664), Jath::Point(48.583, 77.476, 49.314), Jath::Point(48.048, 79.402, 45.964), Jath::Point(47.632, 81.358, 42.614), Jath::Point(47.338, 83.336, 39.264), Jath::Point(47.168, 85.328, 35.914), Jath::Point(47.127, 87.328, 32.564), Jath::Point(47.214, 89.325, 34.104), Jath::Point(47.42, 91.314, 35.644), Jath::Point(47.745, 93.287, 37.185), Jath::Point(48.176, 95.24, 38.725), Jath::Point(48.706, 97.168, 40.265), Jath::Point(49.326, 99.07, 41.805), Jath::Point(50.023, 100.944, 43.345), Jath::Point(50.792, 102.79, 44.885), Jath::Point(51.62, 104.611, 46.425), Jath::Point(52.499, 106.407, 47.965), Jath::Point(53.424, 108.18, 47.965), Jath::Point(54.385, 109.934, 47.965), Jath::Point(55.375, 111.672, 47.965), Jath::Point(56.389, 113.396, 47.965), Jath::Point(57.419, 115.11, 47.965), Jath::Point(58.461, 116.817, 47.965), Jath::Point(59.508, 118.521, 47.965), Jath::Point(60.556, 120.225, 47.965), Jath::Point(61.598, 121.932, 47.965), Jath::Point(62.628, 123.646, 47.965), Jath::Point(63.64, 125.371, 47.965), Jath::Point(64.629, 127.11, 47.965), Jath::Point(65.587, 128.865, 47.965), Jath::Point(66.505, 130.642, 47.965), Jath::Point(67.378, 132.441, 47.965), Jath::Point(68.194, 134.267, 47.965), Jath::Point(68.945, 136.121, 47.965), Jath::Point(69.619, 138.004, 46.268), Jath::Point(70.205, 139.916, 42.577), Jath::Point(70.474, 140.925, 40.7), Jath::Point(70.474, 140.925, 0),
};
Jath::Path RingsFinal2 = Jath::Path::cm(RingsFinal2Points);

void skills()
{
    vex::task antiJamTask(intakeAntiJam);

    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(-2.5), art::Tiles(0));
    smartDrive.m_dir = art::Degrees(-90);

    // resetPositionFromGPS();

    arm.set(100);
    vex::wait(1, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-5));

    armTarget = art::Degrees(0);
    vex::thread armControl(autonArmPos);

    // followPathRev(goal1Path, art::Inches(13));

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(-2.15), art::Tiles(0.95)
    ));

    // maybe add additional drive
    smartDrive.driveForPID(art::Inches(-2));
    clamp.set(true);
    smartDrive.arcade(0,0);

    vex::wait(0.75, vex::sec);

    resetPositionFromGPS();

    intake.set(100);
    followPath(rings1Path, art::Inches(13));
    smartDrive.arcade(40, 0);
    vex::wait( 0.3,vex::sec);

    smartDrive.driveForPID(art::Inches(-3));
    smartDrive.turnForPID(art::Degrees(165));
    smartDrive.arcade(0,0);
    vex::wait(0.75, vex::sec);
    resetPositionFromGPS();

    // followPath(rings1_5Path, art::Inches(13));
    // smartDrive.driveForPID(art::Inches(5));

    // followPathRev(rings1_6Path, art::Inches(13));

    followPath(rings1_75Path, art::Inches(13));
    smartDrive.arcade(75, 0);
    vex::wait( 0.3,vex::sec);

    smartDrive.driveForPID(art::Inches(-5));

    target = art::Vec2::XandY(art::Tiles(-2.75), art::Tiles(2.75));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.arcade(-75, 0);
    vex::wait(1,vex::sec);

    clamp.set(false);
    intake.set(0);

    smartDrive.driveForPID(art::Inches(24));

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPS();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(-2), art::Tiles(0)
    ));

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPS();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(-2), art::Tiles(-0.95)
    ));

    // maybe add additional drive
    smartDrive.driveForPID(art::Inches(-2));
    clamp.set(true);
    smartDrive.arcade(0,0);

    smartDrive.arcade(0,0);
    vex::wait(0.75, vex::sec);
    resetPositionFromGPS();

    intake.set(100);
    followPath_flipY(rings1Path, art::Inches(13));
    smartDrive.arcade(40, 0);
    vex::wait( 0.3,vex::sec);

    smartDrive.driveForPID(art::Inches(-3));
    smartDrive.turnForPID(art::Degrees(-15));
    smartDrive.arcade(0,0);
    vex::wait(0.75, vex::sec); logger.logStringEntry(Auton_Console, "Waiting to reset");
    resetPositionFromGPS();

    // followPath_flipY(rings1_5Path, art::Inches(13));
    // smartDrive.driveForPID(art::Inches(5));

    // followPathRev_flipY(rings1_6Path, art::Inches(13));

    followPath_flipY(rings1_75Path, art::Inches(13));
    smartDrive.arcade(75, 0);
    vex::wait( 0.3,vex::sec);

    smartDrive.driveForPID(art::Inches(-5));

    target = art::Vec2::XandY(art::Tiles(-2.75), art::Tiles(2.75 * -1.0));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.arcade(-75, 0);
    vex::wait(1,vex::sec);

    clamp.set(false);
    intake.set(0);

    smartDrive.driveForPID(art::Inches(48));

    //End of Red

    smartDrive.turnToPID(art::Degrees(135));

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPS(); // Delete this

    smartDrive.arcade(0,0);
    vex::wait(0.75, vex::sec);
    resetPositionFromGPS();

    intake.set(100);
    followPath(goal3Path, art::Inches(13));

    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec);
    // resetPositionFromGPS();

    // target = art::Vec2::XandY(art::Tiles(2.5), art::Tiles(-1.0));
    // travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(art::Degrees(135));
    intake.set(-100);

    smartDrive.arcade(75, 0);
    vex::wait(1.75, vex::sec);

    smartDrive.driveForPID(art::Inches(-54));
    smartDrive.turnToPID(art::Degrees(60));
    intake.set(0);

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPS();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(2), art::Tiles(-1.0)
    ));

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPS();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(2), art::Tiles(0.0)
    ));

    // maybe add additional drive
    smartDrive.driveForPID(art::Inches(-3));
    clamp.set(true);
    smartDrive.arcade(0,0);

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPS();

    intake.set(100);

    // followPath(RingsFinal1, art::Inches(13));
    // smartDrive.turnToPID(art::Degrees(45));
    
    followPath(RingsFinal2, art::Inches(13));

    smartDrive.driveForPID(art::Inches(5));
    smartDrive.driveForPID(art::Inches(-5));

    // smartDrive.arcade(0,0);
    // vex::wait(0.5, vex::sec);
    // resetPositionFromGPS();

    // driveTowardPoint(art::Vec2::XandY(
    //     art::Tiles(2),art::Tiles(1.95)
    // ));

    // smartDrive.driveForPID(art::Inches(-15));

    // driveTowardPoint(art::Vec2::XandY(
    //     art::Tiles(2),art::Tiles(2.5)
    // ));

    // smartDrive.driveForPID(art::Inches(-5));

    // smartDrive.arcade(0,0);
    // vex::wait(0.5, vex::sec);
    // resetPositionFromGPS();

    // target = art::Vec2::XandY(art::Tiles(2.75), art::Tiles(2.75));
    // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnForPID(art::Degrees(travel.direction()) + art::Degrees(180));

    smartDrive.turnToPID(art::Degrees(-135));
    smartDrive.arcade(-75, 0);
    vex::wait(1.75, vex::sec);

    clamp.set(false);
    intake.set(0);

    smartDrive.driveForPID(art::Inches(24));

    smartDrive.arcade(0, 0);
}

void ladyBrownTest()
{
    armTarget = art::Degrees(3);
    vex::thread armControl(autonArmPos);

    intake.set(100);

    smartDrive.driveForPID(art::Inches(20));

    vex::wait(1.5,vex::sec);

    // for (size_t i = 0; i < 3; i++)
    // {
    //     intake.set(100);
    //     vex::wait(.125,vex::sec);
    //     intake.set(0);
    //     vex::wait(.125,vex::sec);
    // }
    
    smartDrive.arcade(25,0);

    intake.set(0);

    armTarget = art::Degrees(135);

    vex::wait(1, vex::sec);

    smartDrive.arcade(-25,0);
    vex::wait(.125, vex::sec);

    smartDrive.arcade(75,0);
    vex::wait(.25, vex::sec);
    
    smartDrive.driveForPID(art::Inches(-10));
}

void coolBeansRushRed()
{
    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(-2.25), art::Tiles(-1.5));
    smartDrive.m_dir = art::Degrees(90);

    vex::task antiJamTask(intakeAntiJam);

    smartDrive.driveForPID(art::Inches(41));
    smartDrive.turnToPID(art::Degrees(125));

    smartDrive.driveForPID(art::Inches(1));

    arm.set(100);
    vex::wait(1.25, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    armTarget = art::Degrees(120);
    vex::thread armControl(autonArmPos);

    smartDrive.turnToPID(art::Degrees(135));

    smartDrive.driveForPID(art::Inches(-18));
    smartDrive.driveForPID(art::Inches(-6));
    clamp.set(true);
    vex::wait(0.5,vex::sec);
    smartDrive.driveForPID(art::Inches(6));

    smartDrive.turnToPID(art::Degrees(175));
    intake.set(100);
    smartDrive.driveForPID(art::Inches(30));
    smartDrive.driveForPID(art::Inches(-10));
}
