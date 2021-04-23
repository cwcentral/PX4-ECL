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
// Date: 2021.3069,
static constexpr const int16_t declination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ {  26018, 24273, 22527, 20782, 19037, 17291, 15546, 13801, 12055, 10310,  8565,  6819,  5074,  3329,  1584,  -162, -1907, -3652, -5398, -7143, -8888,-10633,-12379,-14124,-15869,-17615,-19360,-21105,-22851,-24596,-26342,-28087,-29832, 31254, 29509, 27763, 26018, },
/* LAT: -80 */ {  22588, 20452, 18508, 16731, 15089, 13549, 12084, 10672,  9296,  7945,  6613,  5294,  3985,  2680,  1372,    54, -1285, -2655, -4063, -5512, -7004, -8538,-10113,-11729,-13391,-15107,-16891,-18761,-20741,-22857,-25129,-27562,-30131, 30058, 27435, 24924, 22588, },
/* LAT: -70 */ {  14966, 13570, 12448, 11490, 10626,  9798,  8959,  8074,  7123,  6104,  5034,  3940,  2853,  1796,   772,  -239, -1274, -2375, -3571, -4864, -6239, -7664, -9108,-10548,-11972,-13386,-14812,-16294,-17910,-19812,-22312,-26081, 30833, 24197, 19628, 16840, 14966, },
/* LAT: -60 */ {   8378,  8141,  7868,  7602,  7356,  7108,  6806,  6378,  5767,  4951,  3953,  2842,  1718,   684,  -205,  -969, -1699, -2515, -3508, -4693, -6013, -7376, -8694, -9904,-10970,-11871,-12590,-13086,-13258,-12808,-10721, -3608,  4768,  7566,  8362,  8502,  8378, },
/* LAT: -50 */ {   5452,  5492,  5442,  5359,  5291,  5260,  5230,  5108,  4770,  4113,  3109,  1839,   496,  -695, -1581, -2160, -2564, -3000, -3669, -4661, -5886, -7153, -8294, -9200, -9808,-10058, -9877, -9131, -7633, -5280, -2381,   364,  2473,  3896,  4770,  5245,  5452, },
/* LAT: -40 */ {   3930,  4025,  4037,  3999,  3945,  3915,  3924,  3917,  3748,  3222,  2210,   775,  -791, -2119, -3002, -3472, -3670, -3737, -3893, -4430, -5376, -6441, -7331, -7882, -8006, -7647, -6774, -5397, -3682, -1972,  -506,   717,  1758,  2619,  3271,  3699,  3930, },
/* LAT: -30 */ {   2963,  3050,  3086,  3079,  3026,  2953,  2896,  2865,  2742,  2273,  1252,  -256, -1866, -3136, -3896, -4259, -4355, -4164, -3734, -3481, -3802, -4533, -5238, -5606, -5500, -4931, -3981, -2773, -1553,  -598,    85,   687,  1307,  1904,  2408,  2766,  2963, },
/* LAT: -20 */ {   2320,  2368,  2392,  2402,  2366,  2278,  2175,  2101,  1958,  1471,   430, -1047, -2530, -3609, -4165, -4301, -4116, -3578, -2724, -1907, -1595, -1925, -2572, -3054, -3107, -2761, -2132, -1311,  -524,   -25,   243,   547,   984,  1454,  1869,  2171,  2320, },
/* LAT: -10 */ {   1927,  1922,  1908,  1913,  1892,  1814,  1711,  1624,  1441,   898,  -151, -1520, -2802, -3651, -3945, -3739, -3179, -2405, -1558,  -793,  -310,  -322,  -779, -1290, -1514, -1433, -1123,  -621,  -116,   134,   190,   353,   719,  1146,  1531,  1811,  1927, },
/* LAT:   0 */ {   1714,  1683,  1634,  1633,  1628,  1566,  1470,  1362,  1111,   495,  -537, -1763, -2828, -3436, -3461, -2980, -2220, -1436,  -778,  -236,   184,   310,    44,  -373,  -634,  -695,  -596,  -332,   -36,    61,     8,   100,   435,   867,  1277,  1590,  1714, },
/* LAT:  10 */ {   1582,  1591,  1555,  1578,  1610,  1567,  1455,  1275,   902,   187,  -831, -1910, -2750, -3111, -2929, -2336, -1563,  -846,  -323,    62,   391,   548,   396,    75,  -164,  -272,  -292,  -208,   -99,  -134,  -267,  -237,    59,   503,   975,  1376,  1582, },
/* LAT:  20 */ {   1405,  1555,  1620,  1716,  1807,  1793,  1646,  1351,   809,   -47, -1092, -2051, -2663, -2791, -2478, -1885, -1175,  -521,   -53,   261,   522,   674,   590,   348,   146,    29,   -57,  -116,  -191,  -376,  -608,  -666,  -437,     2,   537,  1051,  1405, },
/* LAT:  30 */ {   1114,  1482,  1744,  1970,  2132,  2147,  1965,  1548,   823,  -208, -1332, -2222, -2653, -2605, -2215, -1640,  -986,  -365,   104,   415,   650,   801,   787,   640,   488,   365,   215,    12,  -264,  -635, -1002, -1163, -1008,  -588,   -15,   593,  1114, },
/* LAT:  40 */ {    769,  1357,  1851,  2243,  2492,  2538,  2325,  1795,   884,  -348, -1599, -2482, -2817, -2675, -2234, -1644,  -991,  -358,   157,   526,   801,  1005,  1105,  1097,  1021,   875,   614,   214,  -316,  -920, -1443, -1691, -1580, -1167,  -568,   107,   769, },
/* LAT:  50 */ {    493,  1242,  1922,  2477,  2841,  2946,  2717,  2061,   915,  -594, -2034, -2966, -3271, -3085, -2597, -1951, -1240,  -539,    81,   592,  1015,  1376,  1662,  1837,  1860,  1679,  1245,   550,  -334, -1236, -1921, -2216, -2097, -1656, -1016,  -277,   493, },
/* LAT:  60 */ {    317,  1174,  1979,  2671,  3170,  3377,  3156,  2335,   802, -1185, -2926, -3918, -4174, -3913, -3338, -2590, -1760,  -915,  -103,   653,  1350,  1985,  2534,  2937,  3105,  2931,  2309,  1212,  -192, -1516, -2397, -2716, -2554, -2055, -1353,  -541,   317, },
/* LAT:  70 */ {    120,  1062,  1962,  2760,  3369,  3654,  3385,  2213,   -95, -2874, -4846, -5662, -5656, -5159, -4378, -3435, -2403, -1330,  -250,   815,  1845,  2816,  3689,  4403,  4860,  4908,  4323,  2883,   716, -1392, -2704, -3156, -2997, -2459, -1698,  -817,   120, },
/* LAT:  80 */ {   -460,   468,  1326,  2021,  2402,  2191,   896, -1936, -5340, -7469, -8159, -7975, -7305, -6359, -5247, -4032, -2753, -1438,  -106,  1228,  2546,  3831,  5060,  6200,  7197,  7958,  8307,  7888,  6049,  2447, -1071, -2812, -3209, -2900, -2232, -1384,  -460, },
/* LAT:  90 */ { -30303,-28557,-26812,-25066,-23321,-21576,-19830,-18085,-16340,-14594,-12849,-11104, -9359, -7614, -5868, -4123, -2378,  -633,  1112,  2857,  4603,  6348,  8093,  9838, 11584, 13329, 15074, 16820, 18565, 20311, 22056, 23802, 25547, 27293, 29038, 30784,-30303, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.3069,
static constexpr const int16_t inclination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ { -12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579, },
/* LAT: -80 */ { -13666,-13533,-13372,-13192,-12997,-12795,-12591,-12390,-12199,-12022,-11865,-11730,-11620,-11533,-11470,-11429,-11409,-11412,-11439,-11493,-11577,-11691,-11835,-12008,-12205,-12422,-12651,-12884,-13112,-13325,-13512,-13663,-13768,-13820,-13818,-13764,-13666, },
/* LAT: -70 */ { -14116,-13798,-13479,-13155,-12823,-12478,-12122,-11764,-11419,-11109,-10855,-10669,-10556,-10503,-10490,-10495,-10504,-10515,-10540,-10596,-10704,-10877,-11121,-11433,-11804,-12220,-12667,-13131,-13597,-14050,-14469,-14816,-15009,-14959,-14729,-14432,-14116, },
/* LAT: -60 */ { -13525,-13172,-12835,-12502,-12159,-11786,-11371,-10915,-10446,-10013, -9679, -9499, -9492, -9627, -9832,-10028,-10160,-10210,-10203,-10190,-10236,-10391,-10674,-11078,-11573,-12126,-12711,-13307,-13896,-14457,-14953,-15245,-15075,-14693,-14289,-13897,-13525, },
/* LAT: -50 */ { -12498,-12158,-11828,-11507,-11184,-10837,-10437, -9965, -9434, -8909, -8513, -8379, -8571, -9028, -9592,-10110,-10480,-10655,-10636,-10491,-10349,-10348,-10559,-10966,-11503,-12093,-12680,-13221,-13669,-13969,-14078,-14006,-13803,-13520,-13193,-12847,-12498, },
/* LAT: -40 */ { -11240,-10894,-10550,-10205, -9866, -9527, -9165, -8738, -8215, -7647, -7212, -7157, -7602, -8418, -9341,-10177,-10845,-11294,-11451,-11300,-10964,-10685,-10665,-10934,-11390,-11894,-12343,-12670,-12833,-12840,-12749,-12610,-12430,-12197,-11911,-11585,-11240, },
/* LAT: -30 */ {  -9601, -9227, -8852, -8464, -8071, -7694, -7335, -6941, -6426, -5812, -5350, -5412, -6159, -7350, -8603, -9707,-10630,-11353,-11772,-11784,-11426,-10919,-10575,-10562,-10806,-11127,-11389,-11508,-11450,-11274,-11097,-10958,-10809,-10600,-10319, -9975, -9601, },
/* LAT: -20 */ {  -7369, -6938, -6527, -6102, -5657, -5225, -4830, -4412, -3842, -3154, -2692, -2925, -4006, -5605, -7237, -8620, -9700,-10492,-10949,-11003,-10656,-10050, -9487, -9233, -9274, -9435, -9580, -9603, -9434, -9161, -8963, -8869, -8758, -8547, -8230, -7821, -7369, },
/* LAT: -10 */ {  -4411, -3888, -3444, -3011, -2554, -2102, -1684, -1221,  -587,   123,   502,   105, -1193, -3094, -5075, -6704, -7823, -8477, -8758, -8710, -8316, -7643, -6978, -6624, -6579, -6672, -6792, -6820, -6635, -6337, -6176, -6174, -6123, -5901, -5518, -4995, -4411, },
/* LAT:   0 */ {   -902,  -293,   161,   558,   975,  1393,  1788,  2242,  2838,  3425,  3644,  3173,  1906,    14, -2034, -3708, -4744, -5193, -5265, -5106, -4679, -3975, -3270, -2892, -2829, -2901, -3028, -3104, -2975, -2738, -2675, -2804, -2851, -2658, -2234, -1611,  -902, },
/* LAT:  10 */ {   2566,  3178,  3603,  3939,  4292,  4660,  5017,  5414,  5877,  6258,  6306,  5837,  4776,  3225,  1533,   139,  -690,  -957,  -877,  -649,  -248,   381,  1013,  1355,  1417,  1368,  1264,  1173,  1217,  1324,  1256,  1004,   827,   906,  1258,  1853,  2566, },
/* LAT:  20 */ {   5419,  5937,  6310,  6602,  6915,  7259,  7606,  7962,  8304,  8513,  8435,  7985,  7163,  6075,  4947,  4027,  3483,  3349,  3489,  3727,  4051,  4510,  4969,  5226,  5281,  5258,  5207,  5150,  5142,  5128,  4961,  4640,  4352,  4268,  4439,  4857,  5419, },
/* LAT:  30 */ {   7569,  7938,  8252,  8533,  8842,  9190,  9551,  9898, 10181, 10302, 10164,  9750,  9127,  8418,  7754,  7237,  6936,  6885,  7020,  7227,  7470,  7765,  8052,  8226,  8281,  8290,  8289,  8280,  8261,  8183,  7967,  7621,  7272,  7055,  7038,  7230,  7569, },
/* LAT:  40 */ {   9266,  9485,  9740, 10025, 10352, 10715, 11086, 11428, 11685, 11773, 11628, 11272, 10800, 10325,  9926,  9639,  9484,  9475,  9580,  9738,  9910, 10092, 10262, 10387, 10464, 10521, 10574, 10607, 10593, 10487, 10249,  9903,  9539,  9256,  9113,  9124,  9266, },
/* LAT:  50 */ {  10801, 10923, 11125, 11396, 11720, 12076, 12433, 12752, 12977, 13040, 12903, 12605, 12240, 11893, 11615, 11426, 11329, 11321, 11384, 11484, 11596, 11710, 11825, 11940, 12057, 12177, 12289, 12362, 12356, 12235, 11993, 11667, 11328, 11044, 10854, 10774, 10801, },
/* LAT:  60 */ {  12318, 12393, 12545, 12765, 13038, 13340, 13644, 13913, 14090, 14118, 13982, 13732, 13441, 13168, 12946, 12787, 12694, 12660, 12674, 12719, 12785, 12869, 12973, 13104, 13262, 13436, 13601, 13711, 13721, 13604, 13382, 13104, 12824, 12587, 12416, 12326, 12318, },
/* LAT:  70 */ {  13759, 13804, 13901, 14046, 14228, 14434, 14644, 14826, 14930, 14908, 14768, 14563, 14344, 14139, 13964, 13828, 13733, 13677, 13657, 13668, 13709, 13780, 13882, 14016, 14182, 14368, 14552, 14695, 14744, 14675, 14515, 14317, 14122, 13957, 13837, 13770, 13759, },
/* LAT:  80 */ {  15002, 15017, 15056, 15118, 15197, 15284, 15364, 15409, 15387, 15303, 15187, 15060, 14936, 14821, 14721, 14638, 14576, 14535, 14515, 14519, 14545, 14593, 14664, 14756, 14867, 14993, 15127, 15259, 15366, 15412, 15377, 15293, 15200, 15117, 15053, 15015, 15002, },
/* LAT:  90 */ {  15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.3069,
static constexpr const int16_t strength_table[19][37] {
//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
/* LAT: -90 */ {  5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, 5459, },
/* LAT: -80 */ {  6065, 6002, 5924, 5833, 5730, 5619, 5501, 5380, 5257, 5137, 5023, 4917, 4823, 4744, 4680, 4635, 4610, 4607, 4628, 4673, 4743, 4837, 4951, 5082, 5225, 5374, 5524, 5667, 5798, 5912, 6005, 6074, 6119, 6139, 6136, 6110, 6065, },
/* LAT: -70 */ {  6309, 6178, 6029, 5865, 5687, 5496, 5291, 5076, 4857, 4641, 4438, 4255, 4097, 3965, 3861, 3783, 3736, 3723, 3750, 3825, 3952, 4130, 4357, 4624, 4918, 5225, 5528, 5812, 6062, 6267, 6419, 6515, 6557, 6551, 6503, 6420, 6309, },
/* LAT: -60 */ {  6194, 6004, 5804, 5596, 5378, 5144, 4888, 4610, 4317, 4027, 3759, 3531, 3350, 3215, 3115, 3042, 2991, 2971, 2996, 3085, 3251, 3500, 3824, 4208, 4630, 5063, 5484, 5869, 6194, 6444, 6609, 6689, 6692, 6630, 6518, 6368, 6194, },
/* LAT: -50 */ {  5850, 5621, 5391, 5161, 4930, 4686, 4416, 4113, 3784, 3452, 3149, 2907, 2744, 2652, 2603, 2570, 2537, 2512, 2516, 2587, 2757, 3042, 3435, 3903, 4409, 4915, 5391, 5810, 6150, 6393, 6533, 6575, 6534, 6425, 6265, 6068, 5850, },
/* LAT: -40 */ {  5397, 5153, 4910, 4671, 4438, 4201, 3947, 3664, 3350, 3023, 2724, 2499, 2380, 2353, 2372, 2395, 2402, 2391, 2380, 2407, 2533, 2801, 3213, 3723, 4269, 4795, 5264, 5654, 5948, 6136, 6226, 6230, 6161, 6032, 5852, 5635, 5397, },
/* LAT: -30 */ {  4881, 4642, 4404, 4171, 3945, 3727, 3509, 3278, 3023, 2747, 2489, 2305, 2232, 2255, 2321, 2394, 2461, 2513, 2538, 2551, 2615, 2806, 3160, 3643, 4173, 4672, 5094, 5414, 5619, 5720, 5747, 5721, 5642, 5511, 5332, 5116, 4881, },
/* LAT: -20 */ {  4323, 4111, 3904, 3701, 3505, 3323, 3154, 2991, 2815, 2618, 2427, 2291, 2246, 2287, 2375, 2485, 2614, 2745, 2837, 2876, 2900, 2990, 3222, 3600, 4047, 4475, 4827, 5067, 5174, 5183, 5153, 5106, 5024, 4896, 4731, 4534, 4323, },
/* LAT: -10 */ {  3791, 3632, 3480, 3334, 3199, 3079, 2977, 2886, 2790, 2677, 2555, 2454, 2405, 2425, 2508, 2636, 2792, 2953, 3080, 3146, 3161, 3185, 3302, 3549, 3872, 4194, 4461, 4627, 4666, 4614, 4547, 4482, 4393, 4268, 4120, 3957, 3791, },
/* LAT:   0 */ {  3412, 3321, 3238, 3166, 3111, 3073, 3048, 3031, 3009, 2962, 2884, 2789, 2706, 2670, 2707, 2808, 2940, 3077, 3194, 3271, 3304, 3324, 3396, 3549, 3755, 3968, 4149, 4258, 4266, 4200, 4112, 4019, 3907, 3775, 3642, 3519, 3412, },
/* LAT:  10 */ {  3283, 3253, 3234, 3231, 3256, 3304, 3362, 3417, 3454, 3446, 3377, 3263, 3134, 3035, 3005, 3043, 3122, 3220, 3321, 3407, 3471, 3532, 3619, 3735, 3868, 4005, 4124, 4196, 4200, 4140, 4032, 3889, 3727, 3568, 3434, 3338, 3283, },
/* LAT:  20 */ {  3400, 3404, 3432, 3487, 3581, 3703, 3833, 3952, 4035, 4049, 3976, 3833, 3664, 3521, 3441, 3426, 3459, 3530, 3626, 3722, 3813, 3910, 4020, 4130, 4238, 4347, 4449, 4515, 4528, 4471, 4336, 4135, 3908, 3700, 3537, 3437, 3400, },
/* LAT:  30 */ {  3723, 3732, 3789, 3890, 4035, 4208, 4385, 4542, 4652, 4679, 4606, 4450, 4259, 4091, 3982, 3933, 3934, 3982, 4067, 4164, 4261, 4365, 4481, 4599, 4717, 4842, 4961, 5048, 5076, 5021, 4867, 4629, 4355, 4102, 3903, 3776, 3723, },
/* LAT:  40 */ {  4223, 4224, 4292, 4418, 4587, 4776, 4960, 5117, 5222, 5248, 5179, 5029, 4840, 4663, 4531, 4453, 4425, 4445, 4503, 4581, 4666, 4762, 4876, 5010, 5160, 5321, 5471, 5582, 5623, 5572, 5418, 5181, 4907, 4648, 4438, 4294, 4223, },
/* LAT:  50 */ {  4831, 4828, 4887, 5000, 5148, 5309, 5459, 5580, 5653, 5661, 5597, 5468, 5303, 5137, 4998, 4898, 4841, 4827, 4850, 4899, 4967, 5057, 5175, 5325, 5500, 5684, 5850, 5970, 6017, 5975, 5845, 5649, 5424, 5207, 5027, 4899, 4831, },
/* LAT:  60 */ {  5392, 5383, 5415, 5481, 5568, 5663, 5750, 5815, 5846, 5836, 5780, 5684, 5562, 5432, 5312, 5214, 5146, 5111, 5108, 5135, 5190, 5276, 5393, 5539, 5705, 5874, 6023, 6129, 6175, 6154, 6072, 5945, 5797, 5654, 5531, 5442, 5392, },
/* LAT:  70 */ {  5726, 5709, 5708, 5722, 5746, 5772, 5795, 5809, 5807, 5786, 5746, 5687, 5615, 5538, 5463, 5398, 5349, 5321, 5315, 5334, 5379, 5448, 5539, 5647, 5765, 5879, 5979, 6053, 6094, 6098, 6069, 6015, 5947, 5877, 5812, 5761, 5726, },
/* LAT:  80 */ {  5789, 5772, 5759, 5747, 5738, 5729, 5719, 5706, 5691, 5672, 5649, 5623, 5595, 5567, 5542, 5521, 5507, 5501, 5505, 5520, 5546, 5581, 5623, 5671, 5721, 5769, 5812, 5847, 5871, 5885, 5887, 5881, 5867, 5848, 5828, 5808, 5789, },
/* LAT:  90 */ {  5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, },
};
