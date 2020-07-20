/****************************************************************************
 *
 *   Copyright (c) 2020 Estimation and Control Library (ECL). All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name ECL nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2020.5492,
static constexpr const int16_t declination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ {  26037, 24292, 22546, 20801, 19056, 17310, 15565, 13820, 12074, 10329,  8584,  6838,  5093,  3348,  1603,  -143, -1888, -3633, -5378, -7124, -8869,-10614,-12360,-14105,-15850,-17596,-19341,-21086,-22832,-24577,-26323,-28068,-29813, 31273, 29528, 27782, 26037, },
/* LAT: -80 */ {  22609, 20470, 18525, 16746, 15103, 13562, 12097, 10684,  9308,  7957,  6624,  5304,  3995,  2690,  1383,    65, -1273, -2642, -4048, -5496, -6986, -8518,-10092,-11707,-13368,-15083,-16865,-18733,-20712,-22827,-25098,-27530,-30100, 30088, 27463, 24948, 22609, },
/* LAT: -70 */ {  14960, 13566, 12446, 11490, 10628,  9801,  8964,  8080,  7130,  6112,  5042,  3947,  2859,  1801,   776,  -235, -1269, -2368, -3560, -4850, -6222, -7644, -9086,-10524,-11947,-13360,-14785,-16264,-17877,-19772,-22260,-26012, 30904, 24228, 19632, 16835, 14960, },
/* LAT: -60 */ {   8355,  8123,  7855,  7593,  7350,  7106,  6806,  6381,  5773,  4959,  3962,  2850,  1726,   688,  -206,  -973, -1704, -2517, -3504, -4682, -5996, -7354, -8670, -9879,-10947,-11849,-12569,-13067,-13238,-12788,-10709, -3667,  4689,  7516,  8326,  8474,  8355, },
/* LAT: -50 */ {   5434,  5477,  5430,  5350,  5286,  5257,  5229,  5110,  4775,  4122,  3121,  1853,   507,  -689, -1584, -2172, -2581, -3015, -3674, -4652, -5866, -7128, -8267, -9177, -9789,-10046, -9872, -9134, -7642, -5294, -2398,   347,  2454,  3877,  4751,  5227,  5434, },
/* LAT: -40 */ {   3917,  4013,  4028,  3993,  3941,  3914,  3925,  3920,  3754,  3232,  2226,   795,  -773, -2109, -3003, -3484, -3690, -3761, -3911, -4428, -5356, -6413, -7304, -7863, -7997, -7649, -6785, -5413, -3695, -1981,  -512,   712,  1752,  2610,  3260,  3687,  3917, },
/* LAT: -30 */ {   2952,  3040,  3079,  3075,  3026,  2955,  2901,  2871,  2749,  2285,  1272,  -230, -1842, -3120, -3892, -4265, -4371, -4192, -3765, -3492, -3787, -4507, -5217, -5595, -5501, -4942, -3999, -2789, -1562,  -600,    87,   689,  1308,  1901,  2401,  2756,  2952, },
/* LAT: -20 */ {   2310,  2358,  2386,  2400,  2368,  2282,  2182,  2110,  1967,  1484,   453, -1017, -2503, -3593, -4162, -4310, -4136, -3609, -2760, -1930, -1596, -1911, -2557, -3047, -3109, -2772, -2146, -1323,  -529,   -23,   250,   555,   989,  1454,  1864,  2162,  2310, },
/* LAT: -10 */ {   1916,  1912,  1902,  1911,  1894,  1819,  1720,  1636,  1454,   914,  -127, -1493, -2778, -3640, -3949, -3757, -3204, -2435, -1588,  -816,  -322,  -321,  -771, -1284, -1515, -1439, -1132,  -628,  -117,   139,   200,   365,   727,  1148,  1528,  1803,  1916, },
/* LAT:   0 */ {   1704,  1673,  1628,  1631,  1630,  1572,  1480,  1376,  1126,   512,  -515, -1740, -2811, -3432, -3472, -3003, -2246, -1461,  -799,  -254,   170,   304,    46,  -371,  -636,  -699,  -601,  -334,   -34,    67,    19,   114,   445,   870,  1275,  1582,  1704, },
/* LAT:  10 */ {   1573,  1584,  1551,  1577,  1612,  1574,  1466,  1290,   918,   204,  -813, -1894, -2741, -3114, -2944, -2359, -1587,  -868,  -340,    47,   378,   540,   394,    74,  -168,  -276,  -294,  -207,   -95,  -126,  -254,  -223,    70,   508,   974,  1370,  1573, },
/* LAT:  20 */ {   1401,  1552,  1619,  1718,  1811,  1800,  1657,  1366,   825,   -32, -1077, -2041, -2662, -2800, -2496, -1907, -1198,  -541,   -70,   247,   510,   665,   586,   344,   140,    24,   -58,  -113,  -184,  -366,  -596,  -653,  -427,     8,   538,  1048,  1401, },
/* LAT:  30 */ {   1117,  1485,  1748,  1975,  2138,  2155,  1976,  1562,   837,  -194, -1323, -2220, -2660, -2620, -2235, -1663, -1008,  -385,    87,   400,   637,   791,   780,   634,   482,   359,   213,    16,  -255,  -623,  -989, -1151,  -999,  -582,   -12,   596,  1117, },
/* LAT:  40 */ {    779,  1367,  1861,  2253,  2502,  2548,  2337,  1808,   896,  -340, -1598, -2490, -2834, -2696, -2257, -1668, -1015,  -382,   136,   509,   786,   992,  1096,  1090,  1013,   869,   613,   221,  -304,  -905, -1429, -1680, -1572, -1161,  -562,   115,   779, },
/* LAT:  50 */ {    511,  1262,  1942,  2494,  2857,  2960,  2730,  2073,   923,  -594, -2046, -2986, -3297, -3113, -2626, -1980, -1269,  -567,    56,   570,   995,  1359,  1648,  1827,  1851,  1674,  1247,   562,  -316, -1217, -1906, -2206, -2090, -1649, -1006,  -262,   511, },
/* LAT:  60 */ {    348,  1208,  2013,  2702,  3197,  3399,  3174,  2345,   799, -1206, -2961, -3960, -4216, -3954, -3377, -2627, -1796,  -949,  -134,   624,  1323,  1961,  2513,  2920,  3093,  2926,  2316,  1231,  -165, -1491, -2380, -2705, -2544, -2043, -1334,  -515,   348, },
/* LAT:  70 */ {    175,  1122,  2023,  2819,  3425,  3703,  3421,  2223,  -133, -2958, -4940, -5747, -5730, -5224, -4436, -3487, -2451, -1375,  -291,   776,  1808,  2781,  3657,  4375,  4838,  4895,  4325,  2907,   756, -1350, -2670, -3128, -2968, -2425, -1657,  -768,   175, },
/* LAT:  80 */ {   -324,   607,  1469,  2168,  2548,  2319,   952, -2046, -5589, -7715, -8359, -8134, -7436, -6470, -5343, -4117, -2831, -1510,  -174,  1163,  2484,  3770,  5000,  6140,  7137,  7899,  8251,  7846,  6058,  2561,  -897, -2647, -3062, -2763, -2099, -1251,  -324, },
/* LAT:  90 */ { -30580,-28834,-27089,-25343,-23598,-21853,-20107,-18362,-16617,-14871,-13126,-11381, -9636, -7890, -6145, -4400, -2655,  -910,   835,  2581,  4326,  6071,  7816,  9562, 11307, 13052, 14798, 16543, 18288, 20034, 21779, 23525, 25270, 27016, 28761, 30507,-30580, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2020.5492,
static constexpr const int16_t inclination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ { -12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584,-12584, },
/* LAT: -80 */ { -13672,-13539,-13378,-13198,-13004,-12801,-12597,-12395,-12204,-12027,-11869,-11734,-11624,-11537,-11474,-11433,-11413,-11416,-11444,-11498,-11581,-11695,-11839,-12011,-12209,-12425,-12654,-12887,-13115,-13328,-13515,-13667,-13772,-13825,-13823,-13770,-13672, },
/* LAT: -70 */ { -14123,-13805,-13486,-13162,-12829,-12484,-12128,-11769,-11423,-11112,-10857,-10671,-10557,-10503,-10490,-10496,-10507,-10520,-10545,-10602,-10709,-10881,-11124,-11435,-11805,-12220,-12667,-13130,-13596,-14049,-14469,-14818,-15013,-14965,-14736,-14439,-14123, },
/* LAT: -60 */ { -13529,-13177,-12840,-12508,-12164,-11791,-11375,-10919,-10449,-10015, -9679, -9496, -9487, -9620, -9826,-10025,-10160,-10215,-10210,-10199,-10244,-10397,-10677,-11078,-11570,-12122,-12707,-13302,-13891,-14452,-14948,-15241,-15074,-14695,-14291,-13900,-13529, },
/* LAT: -50 */ { -12500,-12161,-11832,-11511,-11188,-10841,-10441, -9968, -9435, -8909, -8509, -8370, -8558, -9012, -9577,-10099,-10475,-10656,-10645,-10504,-10362,-10357,-10562,-10964,-11497,-12086,-12673,-13215,-13665,-13966,-14076,-14004,-13802,-13520,-13193,-12847,-12500, },
/* LAT: -40 */ { -11240,-10896,-10553,-10209, -9870, -9530, -9168, -8740, -8216, -7645, -7206, -7142, -7579, -8391, -9315,-10155,-10829,-11285,-11453,-11312,-10980,-10698,-10669,-10931,-11382,-11886,-12337,-12668,-12834,-12840,-12749,-12610,-12428,-12195,-11910,-11584,-11240, },
/* LAT: -30 */ {  -9600, -9230, -8857, -8470, -8077, -7699, -7338, -6942, -6426, -5811, -5343, -5392, -6125, -7310, -8564, -9673,-10602,-11333,-11764,-11789,-11440,-10934,-10582,-10562,-10802,-11122,-11386,-11510,-11454,-11278,-11099,-10958,-10806,-10596,-10315, -9972, -9600, },
/* LAT: -20 */ {  -7368, -6941, -6535, -6111, -5666, -5233, -4836, -4414, -3842, -3152, -2682, -2898, -3961, -5550, -7185, -8576, -9667,-10468,-10937,-11004,-10666,-10065, -9499, -9238, -9275, -9436, -9583, -9610, -9443, -9169, -8968, -8869, -8753, -8540, -8223, -7816, -7368, },
/* LAT: -10 */ {  -4409, -3893, -3455, -3024, -2568, -2115, -1693, -1225,  -587,   128,   516,   138, -1139, -3029, -5013, -6657, -7791, -8456, -8748, -8710, -8326, -7660, -6995, -6635, -6587, -6679, -6801, -6832, -6648, -6349, -6184, -6174, -6115, -5889, -5506, -4986, -4409, },
/* LAT:   0 */ {   -898,  -299,   149,   544,   960,  1378,  1776,  2237,  2839,  3433,  3661,  3208,  1959,    78, -1972, -3661, -4715, -5178, -5260, -5107, -4689, -3993, -3289, -2905, -2841, -2914, -3043, -3120, -2992, -2753, -2685, -2803, -2841, -2643, -2220, -1600,  -898, },
/* LAT:  10 */ {   2569,  3173,  3592,  3925,  4278,  4647,  5007,  5410,  5880,  6266,  6324,  5866,  4819,  3278,  1584,   178,  -666,  -946,  -875,  -652,  -257,   365,   997,  1342,  1404,  1351,  1246,  1154,  1199,  1308,  1246,  1005,   838,   922,  1272,  1864,  2569, },
/* LAT:  20 */ {   5421,  5934,  6303,  6593,  6905,  7250,  7599,  7960,  8308,  8522,  8451,  8009,  7195,  6112,  4983,  4055,  3500,  3356,  3490,  3724,  4044,  4499,  4958,  5216,  5269,  5243,  5190,  5134,  5127,  5115,  4954,  4640,  4360,  4279,  4449,  4864,  5421, },
/* LAT:  30 */ {   7570,  7936,  8248,  8528,  8837,  9186,  9549,  9899, 10186, 10311, 10178,  9769,  9150,  8442,  7776,  7254,  6947,  6890,  7020,  7224,  7465,  7758,  8044,  8218,  8272,  8278,  8275,  8267,  8249,  8174,  7961,  7620,  7275,  7060,  7043,  7233,  7570, },
/* LAT:  40 */ {   9265,  9485,  9739, 10024, 10351, 10715, 11087, 11432, 11692, 11783, 11641, 11287, 10816, 10340,  9939,  9649,  9491,  9477,  9580,  9735,  9906, 10085, 10256, 10380, 10456, 10512, 10562, 10595, 10583, 10480, 10245,  9902,  9540,  9257,  9114,  9125,  9265, },
/* LAT:  50 */ {  10801, 10923, 11126, 11397, 11722, 12079, 12438, 12758, 12986, 13050, 12914, 12617, 12251, 11903, 11623, 11432, 11333, 11323, 11383, 11481, 11591, 11704, 11819, 11934, 12050, 12169, 12280, 12353, 12348, 12230, 11990, 11666, 11328, 11043, 10853, 10773, 10801, },
/* LAT:  60 */ {  12317, 12393, 12547, 12769, 13042, 13346, 13651, 13921, 14099, 14128, 13991, 13740, 13448, 13174, 12950, 12790, 12696, 12660, 12672, 12717, 12782, 12864, 12968, 13098, 13255, 13428, 13592, 13704, 13716, 13602, 13380, 13102, 12823, 12585, 12415, 12324, 12317, },
/* LAT:  70 */ {  13759, 13806, 13905, 14051, 14234, 14442, 14653, 14836, 14940, 14916, 14773, 14567, 14346, 14140, 13965, 13829, 13733, 13676, 13655, 13666, 13706, 13776, 13877, 14011, 14176, 14361, 14546, 14689, 14740, 14672, 14513, 14315, 14120, 13955, 13835, 13769, 13759, },
/* LAT:  80 */ {  15005, 15021, 15062, 15125, 15205, 15293, 15375, 15419, 15394, 15306, 15188, 15060, 14935, 14820, 14719, 14636, 14573, 14532, 14512, 14515, 14541, 14589, 14659, 14751, 14862, 14987, 15121, 15252, 15359, 15406, 15373, 15291, 15199, 15117, 15054, 15017, 15005, },
/* LAT:  90 */ {  15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15388, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2020.5492,
static constexpr const int16_t strength_table[19][37] {
//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
/* LAT: -90 */ {  5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, },
/* LAT: -80 */ {  6069, 6007, 5929, 5838, 5736, 5625, 5507, 5386, 5264, 5144, 5029, 4924, 4829, 4749, 4686, 4640, 4615, 4612, 4633, 4678, 4747, 4840, 4953, 5084, 5227, 5377, 5526, 5669, 5800, 5914, 6007, 6077, 6122, 6142, 6139, 6114, 6069, },
/* LAT: -70 */ {  6314, 6183, 6035, 5872, 5694, 5503, 5298, 5084, 4864, 4649, 4445, 4262, 4103, 3971, 3866, 3789, 3741, 3727, 3754, 3828, 3954, 4132, 4358, 4624, 4918, 5224, 5528, 5812, 6062, 6267, 6419, 6516, 6559, 6553, 6505, 6423, 6314, },
/* LAT: -60 */ {  6198, 6009, 5810, 5603, 5386, 5152, 4896, 4618, 4325, 4035, 3766, 3537, 3356, 3220, 3120, 3047, 2996, 2976, 3000, 3088, 3253, 3500, 3823, 4206, 4627, 5060, 5481, 5866, 6192, 6442, 6608, 6688, 6692, 6631, 6520, 6371, 6198, },
/* LAT: -50 */ {  5853, 5626, 5396, 5167, 4936, 4693, 4423, 4120, 3791, 3459, 3155, 2913, 2748, 2655, 2607, 2574, 2542, 2517, 2521, 2590, 2758, 3042, 3432, 3898, 4404, 4910, 5386, 5806, 6147, 6391, 6531, 6574, 6534, 6426, 6266, 6070, 5853, },
/* LAT: -40 */ {  5400, 5156, 4913, 4676, 4443, 4207, 3953, 3670, 3356, 3029, 2729, 2503, 2383, 2355, 2375, 2398, 2406, 2397, 2386, 2413, 2535, 2800, 3208, 3717, 4262, 4788, 5258, 5650, 5944, 6134, 6224, 6228, 6161, 6032, 5853, 5637, 5400, },
/* LAT: -30 */ {  4882, 4644, 4407, 4175, 3950, 3732, 3513, 3283, 3028, 2753, 2494, 2308, 2234, 2256, 2323, 2396, 2464, 2518, 2544, 2558, 2619, 2805, 3155, 3635, 4165, 4665, 5089, 5411, 5617, 5718, 5745, 5720, 5641, 5510, 5332, 5117, 4882, },
/* LAT: -20 */ {  4323, 4113, 3907, 3704, 3508, 3326, 3158, 2996, 2820, 2623, 2432, 2295, 2249, 2287, 2374, 2485, 2615, 2746, 2841, 2882, 2905, 2991, 3218, 3593, 4039, 4468, 4822, 5064, 5173, 5182, 5152, 5105, 5023, 4896, 4730, 4534, 4323, },
/* LAT: -10 */ {  3791, 3633, 3482, 3337, 3202, 3082, 2980, 2889, 2795, 2682, 2561, 2459, 2408, 2426, 2507, 2634, 2790, 2952, 3082, 3150, 3165, 3187, 3301, 3544, 3866, 4187, 4456, 4625, 4665, 4614, 4546, 4481, 4392, 4267, 4119, 3957, 3791, },
/* LAT:   0 */ {  3413, 3322, 3240, 3168, 3113, 3076, 3051, 3035, 3014, 2968, 2890, 2795, 2710, 2672, 2707, 2806, 2938, 3075, 3194, 3272, 3306, 3326, 3395, 3546, 3751, 3963, 4145, 4255, 4264, 4199, 4111, 4018, 3905, 3774, 3641, 3518, 3413, },
/* LAT:  10 */ {  3283, 3254, 3235, 3233, 3259, 3307, 3365, 3422, 3460, 3453, 3384, 3269, 3140, 3039, 3006, 3042, 3121, 3219, 3320, 3406, 3471, 3532, 3617, 3731, 3864, 4000, 4119, 4192, 4197, 4138, 4030, 3887, 3726, 3567, 3433, 3338, 3283, },
/* LAT:  20 */ {  3400, 3405, 3434, 3490, 3584, 3707, 3838, 3959, 4043, 4056, 3984, 3841, 3671, 3526, 3444, 3427, 3459, 3529, 3624, 3720, 3810, 3907, 4016, 4126, 4233, 4341, 4442, 4509, 4523, 4467, 4333, 4132, 3907, 3698, 3536, 3437, 3400, },
/* LAT:  30 */ {  3724, 3734, 3792, 3894, 4040, 4214, 4391, 4550, 4660, 4688, 4615, 4458, 4265, 4095, 3984, 3934, 3933, 3981, 4065, 4161, 4257, 4361, 4476, 4594, 4712, 4836, 4954, 5041, 5071, 5017, 4863, 4626, 4353, 4100, 3901, 3775, 3724, },
/* LAT:  40 */ {  4223, 4226, 4296, 4423, 4593, 4783, 4968, 5125, 5231, 5256, 5187, 5036, 4846, 4667, 4534, 4454, 4424, 4443, 4500, 4577, 4661, 4757, 4871, 5004, 5154, 5314, 5464, 5575, 5618, 5568, 5415, 5179, 4905, 4645, 4435, 4292, 4223, },
/* LAT:  50 */ {  4831, 4830, 4892, 5006, 5156, 5316, 5467, 5587, 5660, 5668, 5602, 5473, 5307, 5140, 4999, 4898, 4840, 4825, 4847, 4895, 4963, 5052, 5170, 5319, 5494, 5677, 5844, 5965, 6013, 5972, 5844, 5648, 5421, 5204, 5024, 4897, 4831, },
/* LAT:  60 */ {  5391, 5385, 5419, 5487, 5575, 5670, 5756, 5821, 5852, 5840, 5784, 5687, 5564, 5433, 5312, 5213, 5145, 5109, 5105, 5131, 5186, 5271, 5387, 5534, 5700, 5869, 6018, 6125, 6172, 6152, 6070, 5943, 5795, 5650, 5528, 5440, 5391, },
/* LAT:  70 */ {  5726, 5710, 5711, 5727, 5751, 5777, 5800, 5813, 5811, 5789, 5747, 5688, 5615, 5537, 5462, 5396, 5347, 5318, 5312, 5331, 5375, 5443, 5534, 5643, 5760, 5875, 5976, 6050, 6091, 6095, 6066, 6013, 5945, 5874, 5810, 5760, 5726, },
/* LAT:  80 */ {  5788, 5773, 5759, 5749, 5739, 5730, 5720, 5708, 5692, 5672, 5649, 5623, 5594, 5566, 5540, 5519, 5504, 5498, 5502, 5517, 5542, 5577, 5620, 5668, 5718, 5766, 5809, 5844, 5869, 5882, 5885, 5878, 5865, 5847, 5827, 5807, 5788, },
/* LAT:  90 */ {  5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, },
};
