#include "StatTools/BayesianDijetFit/interface/LineShapeDensityPdf.h"
#include "Math/Interpolator.h"
#include "TH1F.h"
#include "TArrayD.h"
#include "TObjArray.h"
#include <iostream>

//Resonance Shape of any mass value using Interpolation technique 
//Author: Sertac Ozturk
// sertac@fnal.gov,  sertac.ozturk@cern.ch

// global variables -- shame on you, Sertac! ;)

double mass;
TObjArray* vy = new TObjArray(6);
//================================= new summer 11 D6T shape=======================================//


// Fat Jets with pt_min > 30 GeV

/// D6T summer11 fat-gg ptmin=30GeV  y500 just a copy of y700. Not used and valid. To be replaced if used
double RSGravitonToJJ_M_500_TuneD6T_ak5GGtoGG_fat30 [50] ={158, 144, 178, 206, 226, 202, 220, 246, 291, 271, 299, 288, 294, 336, 348, 317, 365, 374, 399, 389, 410, 369, 407, 441, 445, 476, 462, 491, 547, 649, 711, 818, 803, 876, 729, 649, 460, 381, 277, 218, 190, 159, 144, 114, 103, 112, 81, 71, 74, 67};
double RSGravitonToJJ_M_700_TuneD6T_ak5GGtoGG_fat30 [50] ={158, 144, 178, 206, 226, 202, 220, 246, 291, 271, 299, 288, 294, 336, 348, 317, 365, 374, 399, 389, 410, 369, 407, 441, 445, 476, 462, 491, 547, 649, 711, 818, 803, 876, 729, 649, 460, 381, 277, 218, 190, 159, 144, 114, 103, 112, 81, 71, 74, 67};
double RSGravitonToJJ_M_1200_TuneD6T_ak5GGtoGG_fat30 [50] ={82, 130, 118, 110, 135, 144, 137, 153, 158, 174, 176, 211, 186, 184, 219, 202, 194, 195, 229, 207, 233, 238, 257, 258, 245, 251, 262, 329, 352, 391, 443, 478, 588, 582, 555, 476, 324, 209, 140, 144, 114, 102, 60, 50, 58, 48, 45, 35, 36, 31};
double RSGravitonToJJ_M_2000_TuneD6T_ak5GGtoGG_fat30 [50] ={65, 73, 65, 78, 93, 77, 86, 89, 98, 116, 100, 114, 117, 103, 126, 109, 137, 134, 124, 147, 150, 151, 141, 160, 165, 170, 195, 177, 184, 194, 298, 293, 394, 446, 389, 345, 227, 143, 95, 60, 47, 53, 32, 28, 21, 18, 18, 8, 15, 9};
double RSGravitonToJJ_M_3500_TuneD6T_ak5GGtoGG_fat30 [50] ={57, 47, 47, 47, 61, 49, 53, 40, 49, 34, 46, 47, 50, 48, 55, 33, 41, 53, 38, 64, 49, 43, 44, 51, 55, 59, 53, 58, 64, 78, 71, 124, 123, 149, 154, 99, 67, 33, 27, 16, 15, 2, 9, 10, 1, 3, 2, 1, 2, 0};
double RSGravitonToJJ_M_4000_TuneD6T_ak5GGtoGG_fat30 [50] ={15, 17, 21, 18, 14, 15, 21, 9, 11, 8, 12, 9, 11, 9, 10, 10, 12, 8, 7, 6, 9, 13, 13, 12, 13, 8, 7, 6, 9, 10, 10, 15, 17, 17, 22, 11, 6, 3, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};


/// D6T summer11 fat-qq ptmin=30GeV  y500 just a copy of y700. Not used and valid. To be replaced if used

double RSGravitonToJJ_M_500_TuneD6T_ak5QQtoQQ_fat30 [50] ={15, 23, 17, 19, 20, 31, 32, 24, 27, 34, 42, 34, 42, 52, 47, 49, 58, 75, 76, 72, 75, 97, 119, 137, 166, 179, 191, 200, 245, 336, 398, 471, 593, 709, 754, 682, 577, 400, 292, 173, 115, 97, 77, 53, 40, 27, 32, 19, 20, 24};
double RSGravitonToJJ_M_700_TuneD6T_ak5QQtoQQ_fat30 [50] ={15, 23, 17, 19, 20, 31, 32, 24, 27, 34, 42, 34, 42, 52, 47, 49, 58, 75, 76, 72, 75, 97, 119, 137, 166, 179, 191, 200, 245, 336, 398, 471, 593, 709, 754, 682, 577, 400, 292, 173, 115, 97, 77, 53, 40, 27, 32, 19, 20, 24};
double RSGravitonToJJ_M_1200_TuneD6T_ak5QQtoQQ_fat30 [50] ={29, 31, 34, 27, 31, 34, 34, 32, 42, 42, 44, 57, 59, 70, 76, 82, 96, 100, 111, 132, 135, 149, 170, 187, 198, 200, 267, 295, 361, 456, 552, 790, 983, 1247, 1325, 1257, 973, 632, 391, 223, 136, 123, 81, 54, 44, 44, 34, 25, 15, 19};
double RSGravitonToJJ_M_2000_TuneD6T_ak5QQtoQQ_fat30 [50] ={50, 46, 45, 57, 53, 61, 54, 63, 69, 67, 66, 79, 100, 120, 126, 123, 158, 149, 182, 262, 222, 259, 271, 347, 383, 379, 480, 521, 620, 744, 1022, 1314, 1816, 2334, 2569, 2283, 1645, 920, 498, 285, 158, 116, 81, 47, 44, 25, 26, 15, 22, 17};
double RSGravitonToJJ_M_3500_TuneD6T_ak5QQtoQQ_fat30 [50] ={75, 81, 88, 92, 106, 93, 122, 115, 127, 134, 164, 165, 168, 182, 179, 228, 228, 272, 273, 284, 329, 323, 372, 403, 414, 468, 560, 614, 703, 841, 1024, 1312, 1944, 2541, 3035, 2439, 1585, 805, 371, 187, 94, 44, 31, 15, 9, 8, 3, 2, 1, 1};
double RSGravitonToJJ_M_4000_TuneD6T_ak5QQtoQQ_fat30 [50] ={46, 40, 48, 43, 34, 42, 52, 33, 49, 57, 46, 44, 58, 49, 50, 65, 64, 63, 67, 69, 91, 71, 69, 85, 88, 93, 120, 135, 129, 172, 190, 258, 334, 413, 484, 380, 224, 103, 50, 19, 9, 2, 2, 1, 0, 0, 1, 0, 0, 0};


/// D6T summer11 fat-qg ptmin=30GeV  y500 just a copy of y700. Not used and valid. To be replaced if used

double QstarToJJ_M_500_TuneD6T_ak5_fat30 [50] ={108, 159, 161, 179, 200, 256, 255, 290, 304, 370, 370, 457, 514, 539, 607, 687, 716, 825, 857, 961, 1036, 1169, 1210, 1240, 1340, 1460, 1642, 1873, 2187, 2620, 3191, 3803, 4383, 4867, 4982, 4487, 3568, 2702, 1968, 1454, 1125, 790, 669, 607, 454, 389, 352, 331, 259, 239};
double QstarToJJ_M_700_TuneD6T_ak5_fat30 [50] ={108, 159, 161, 179, 200, 256, 255, 290, 304, 370, 370, 457, 514, 539, 607, 687, 716, 825, 857, 961, 1036, 1169, 1210, 1240, 1340, 1460, 1642, 1873, 2187, 2620, 3191, 3803, 4383, 4867, 4982, 4487, 3568, 2702, 1968, 1454, 1125, 790, 669, 607, 454, 389, 352, 331, 259, 239};
double QstarToJJ_M_1200_TuneD6T_ak5_fat30 [50] ={122, 142, 146, 182, 187, 214, 220, 277, 267, 340, 382, 416, 460, 500, 544, 634, 708, 745, 822, 940, 948, 1029, 1126, 1189, 1234, 1364, 1579, 1708, 1946, 2409, 2970, 3724, 4771, 5306, 5527, 5041, 3745, 2705, 1899, 1311, 921, 684, 529, 422, 351, 328, 243, 232, 186, 184};
double QstarToJJ_M_2000_TuneD6T_ak5_fat30 [50] ={122, 139, 146, 179, 178, 204, 213, 231, 283, 318, 309, 371, 386, 488, 509, 589, 626, 706, 709, 806, 889, 889, 956, 1043, 1160, 1263, 1342, 1478, 1751, 2097, 2587, 3344, 4239, 5229, 5390, 4491, 3228, 2152, 1400, 913, 613, 453, 352, 272, 205, 181, 125, 140, 96, 69};
double QstarToJJ_M_3500_TuneD6T_ak5_fat30 [50] ={395, 479, 540, 563, 579, 576, 649, 657, 677, 684, 710, 725, 805, 799, 869, 885, 895, 988, 1072, 1098, 1097, 1160, 1297, 1208, 1333, 1510, 1501, 1664, 1888, 2164, 2574, 3501, 4197, 5238, 5416, 4273, 2724, 1630, 921, 555, 340, 235, 164, 131, 84, 53, 41, 35, 14, 14};
double QstarToJJ_M_4000_TuneD6T_ak5_fat30 [50] ={88, 90, 67, 88, 70, 100, 83, 98, 96, 80, 84, 93, 106, 97, 120, 109, 118, 141, 120, 100, 142, 135, 136, 151, 139, 174, 197, 183, 200, 252, 310, 333, 460, 540, 572, 411, 244, 99, 49, 25, 16, 2, 5, 4, 1, 2, 0, 0, 0, 0};


// Fat Jets with pt_min > 10 GeV


/*
/// D6T summer11 fat-qq: y500 is dummy just a copy of y700 and y400 a copy of y3500 not used for the moment
double y500[50] ={26, 35, 25, 25, 27, 37, 34, 25, 31, 32, 34, 35, 42, 53, 42, 49, 53, 61, 76, 64, 71, 70, 102, 116, 144, 153, 165, 189, 217, 284, 309, 394, 504, 565, 725, 723, 678, 512, 401, 285, 203, 140, 102, 86, 65, 39, 31, 29, 26, 25};

double y700[50] ={26, 35, 25, 25, 27, 37, 34, 25, 31, 32, 34, 35, 42, 53, 42, 49, 53, 61, 76, 64, 71, 70, 102, 116, 144, 153, 165, 189, 217, 284, 309, 394, 504, 565, 725, 723, 678, 512, 401, 285, 203, 140, 102, 86, 65, 39, 31, 29, 26, 25};
double y1200[50] ={35, 41, 28, 37, 25, 36, 36, 34, 45, 38, 50, 52, 50, 56, 70, 88, 80, 82, 116, 129, 112, 146, 157, 173, 208, 189, 211, 268, 335, 397, 509, 657, 814, 1118, 1298, 1307, 1143, 767, 547, 352, 175, 149, 100, 74, 53, 51, 38, 27, 17, 19};
double y2000[50] ={59, 44, 53, 50, 49, 63, 57, 53, 66, 71, 59, 69, 102, 111, 120, 128, 137, 156, 180, 242, 226, 241, 251, 318, 386, 380, 442, 452, 623, 676, 904, 1213, 1620, 2170, 2507, 2405, 1888, 1186, 626, 358, 215, 134, 95, 53, 46, 32, 30, 15, 19, 15};
double y3500[50] ={72, 78, 80, 91, 101, 95, 122, 112, 126, 134, 156, 155, 187, 174, 175, 213, 223, 247, 297, 287, 305, 324, 372, 395, 407, 454, 529, 610, 669, 792, 996, 1250, 1798, 2414, 2991, 2638, 1705, 976, 433, 214, 107, 47, 32, 21, 11, 4, 6, 3, 1, 1};
double y4000[50] ={72, 78, 80, 91, 101, 95, 122, 112, 126, 134, 156, 155, 187, 174, 175, 213, 223, 247, 297, 287, 305, 324, 372, 395, 407, 454, 529, 610, 669, 792, 996, 1250, 1798, 2414, 2991, 2638, 1705, 976, 433, 214, 107, 47, 32, 21, 11, 4, 6, 3, 1, 1};
*/

/*
/// D6T summer11 fat-qg
double y700[50] ={214, 240, 213, 243, 242, 267, 262, 291, 343, 357, 375, 407, 454, 505, 513, 587, 677, 729, 779, 917, 904, 1025, 1084, 1138, 1255, 1334, 1505, 1572, 1794, 2191, 2551, 3114, 3821, 4336, 4848, 4806, 4355, 3551, 2819, 2173, 1643, 1189, 918, 749, 606, 495, 440, 391, 342, 296};
double y1200[50] ={151, 149, 168, 170, 201, 221, 219, 246, 260, 300, 357, 359, 423, 492, 478, 585, 634, 709, 776, 851, 945, 977, 1037, 1144, 1175, 1316, 1441, 1485, 1809, 2142, 2449, 3159, 4203, 4852, 5361, 5418, 4632, 3361, 2476, 1743, 1207, 914, 649, 513, 397, 351, 285, 260, 226, 201};
double y2000[50] ={129, 127, 136, 179, 187, 196, 206, 214, 274, 301, 298, 337, 385, 450, 463, 584, 582, 666, 723, 744, 835, 918, 929, 992, 1089, 1238, 1301, 1369, 1622, 1973, 2327, 3014, 3819, 4906, 5358, 5010, 3712, 2543, 1731, 1122, 741, 506, 381, 316, 240, 201, 125, 152, 107, 82};
double y3500[50] ={363, 462, 529, 541, 585, 574, 647, 646, 673, 686, 697, 711, 779, 791, 860, 897, 862, 970, 1071, 1052, 1109, 1169, 1236, 1254, 1283, 1447, 1493, 1648, 1816, 2062, 2473, 3264, 3990, 5079, 5429, 4624, 3075, 1891, 1047, 639, 360, 266, 183, 133, 99, 62, 40, 36, 20, 17};
*/



/// D6T summer11 fat-gg: y500 is dummy just a copy of y700 and y400 a copy of y3500 not used for the moment
double y500[50] ={150, 138, 181, 206, 203, 209, 249, 231, 259, 268, 297, 259, 297, 318, 306, 311, 332, 324, 384, 374, 423, 357, 370, 410, 422, 474, 380, 488, 500, 533, 584, 735, 755, 881, 787, 782, 671, 557, 422, 315, 238, 223, 180, 155, 117, 118, 104, 80, 87, 84};
double y700[50] ={150, 138, 181, 206, 203, 209, 249, 231, 259, 268, 297, 259, 297, 318, 306, 311, 332, 324, 384, 374, 423, 357, 370, 410, 422, 474, 380, 488, 500, 533, 584, 735, 755, 881, 787, 782, 671, 557, 422, 315, 238, 223, 180, 155, 117, 118, 104, 80, 87, 84};
double y1200[50] ={80, 126, 117, 108, 132, 132, 138, 160, 166, 142, 178, 173, 184, 169, 211, 219, 197, 199, 208, 226, 206, 248, 225, 251, 238, 251, 254, 291, 313, 356, 388, 458, 501, 565, 596, 532, 429, 310, 217, 179, 135, 103, 82, 61, 54, 53, 56, 35, 43, 35};
double y2000[50] ={62, 70, 56, 78, 87, 75, 90, 82, 96, 104, 99, 109, 120, 105, 110, 122, 129, 124, 132, 141, 147, 136, 148, 150, 163, 160, 181, 174, 201, 172, 256, 278, 367, 427, 417, 378, 282, 174, 115, 81, 52, 47, 46, 36, 22, 15, 21, 14, 8, 16};
double y3500[50] ={54, 57, 43, 47, 51, 59, 48, 42, 51, 40, 39, 45, 49, 50, 53, 30, 44, 47, 43, 54, 57, 44, 44, 47, 54, 56, 50, 56, 69, 76, 69, 104, 121, 143, 158, 116, 77, 40, 29, 16, 17, 4, 10, 8, 3, 3, 3, 1, 1, 1};
double y4000[50] ={54, 57, 43, 47, 51, 59, 48, 42, 51, 40, 39, 45, 49, 50, 53, 30, 44, 47, 43, 54, 57, 44, 44, 47, 54, 56, 50, 56, 69, 76, 69, 104, 121, 143, 158, 116, 77, 40, 29, 16, 17, 4, 10, 8, 3, 3, 3, 1, 1, 1};


/// D6T summer11 pf-qq
/*
double y700[50] ={21, 25, 23, 20, 23, 27, 24, 40, 35, 27, 45, 41, 46, 52, 54, 64, 79, 79, 90, 123, 110, 119, 143, 171, 173, 212, 221, 247, 258, 330, 351, 416, 537, 642, 640, 710, 588, 430, 321, 220, 114, 73, 56, 34, 28, 28, 14, 15, 18, 6};
double y1200[50] ={31, 33, 38, 32, 30, 36, 36, 33, 46, 57, 51, 52, 65, 75, 84, 112, 124, 132, 153, 177, 170, 223, 235, 260, 264, 286, 303, 375, 409, 473, 642, 709, 865, 1076, 1223, 1169, 958, 626, 362, 187, 92, 70, 44, 24, 33, 17, 17, 8, 14, 10};
double y2000[50] ={47, 50, 55, 48, 54, 60, 67, 56, 83, 77, 90, 96, 150, 152, 144, 173, 206, 204, 262, 339, 313, 335, 386, 461, 499, 516, 554, 628, 754, 882, 1097, 1345, 1691, 2122, 2301, 1995, 1439, 797, 358, 206, 104, 63, 37, 29, 24, 10, 12, 8, 7, 11};
double y3500[50] ={83, 92, 94, 97, 136, 116, 130, 133, 138, 151, 161, 187, 197, 208, 202, 263, 284, 320, 367, 382, 411, 457, 473, 485, 544, 594, 681, 721, 822, 931, 1189, 1418, 1889, 2270, 2531, 2066, 1307, 631, 271, 120, 52, 21, 18, 9, 1, 4, 0, 4, 0, 1};
*/
/// D6T summer11 pf-qg
/*
double y700[50] ={111, 149, 158, 206, 197, 241, 276, 311, 344, 379, 447, 492, 568, 665, 722, 809, 1001, 961, 1147, 1286, 1375, 1521, 1513, 1652, 1653, 1861, 1936, 2068, 2340, 2586, 2969, 3422, 3747, 4236, 4392, 4318, 3609, 2828, 2043, 1395, 966, 725, 549, 406, 360, 298, 234, 230, 199, 163};
double y1200[50] ={125, 173, 166, 194, 218, 243, 239, 323, 327, 381, 454, 506, 576, 638, 710, 819, 863, 1054, 1084, 1289, 1360, 1449, 1512, 1642, 1650, 1778, 1920, 2001, 2381, 2690, 3021, 3474, 4170, 4724, 4820, 4425, 3449, 2360, 1556, 1006, 661, 486, 349, 260, 230, 178, 159, 122, 118, 121};
double y2000[50] ={122, 147, 156, 183, 207, 243, 258, 281, 329, 344, 418, 449, 558, 600, 697, 749, 910, 920, 1043, 1114, 1264, 1258, 1395, 1421, 1544, 1666, 1658, 1834, 2091, 2382, 2747, 3329, 3972, 4480, 4537, 3702, 2607, 1605, 1002, 532, 389, 261, 185, 130, 123, 87, 62, 56, 56, 41};
double y3500[50] ={437, 508, 592, 608, 665, 634, 729, 698, 726, 758, 809, 866, 929, 951, 1041, 1057, 1140, 1297, 1291, 1394, 1441, 1503, 1515, 1604, 1642, 1756, 1807, 2072, 2203, 2466, 2841, 3330, 3819, 4468, 4286, 3284, 2018, 1057, 519, 282, 167, 103, 68, 42, 28, 20, 12, 11, 9, 4};
*/
/// D6T summer11 pf-gg
/*
double y700[50] ={143, 153, 187, 236, 220, 232, 245, 293, 278, 316, 325, 362, 377, 395, 399, 431, 463, 463, 508, 460, 458, 501, 472, 484, 522, 498, 524, 552, 557, 595, 652, 672, 709, 719, 689, 573, 477, 354, 244, 152, 134, 129, 95, 96, 76, 70, 64, 45, 46, 46};
double y1200[50] ={88, 115, 138, 103, 151, 161, 160, 185, 205, 194, 228, 195, 237, 239, 255, 273, 260, 245, 263, 303, 306, 281, 288, 327, 312, 298, 359, 350, 376, 377, 426, 431, 486, 503, 465, 351, 265, 171, 90, 72, 50, 56, 34, 27, 25, 27, 19, 18, 16, 16};
double y2000[50] ={93, 74, 94, 74, 82, 107, 102, 88, 120, 122, 133, 119, 145, 133, 164, 142, 156, 197, 208, 194, 190, 202, 174, 209, 209, 187, 208, 197, 225, 241, 263, 286, 342, 347, 325, 221, 147, 77, 38, 29, 17, 15, 15, 4, 9, 4, 3, 2, 3, 3};
double y3500[50] ={65, 50, 61, 57, 52, 52, 55, 50, 41, 47, 55, 58, 61, 62, 43, 62, 51, 52, 62, 59, 60, 71, 68, 48, 67, 66, 61, 58, 81, 89, 72, 102, 109, 94, 113, 79, 38, 15, 7, 6, 2, 3, 4, 2, 0, 0, 0, 1, 0, 0};
*/
/// D6T summer11 calo-qq
/*
double y700[50] ={27, 30, 21, 26, 19, 20, 32, 31, 30, 21, 36, 54, 46, 53, 66, 68, 71, 89, 95, 87, 124, 139, 134, 165, 197, 198, 195, 225, 245, 288, 300, 376, 449, 508, 573, 658, 554, 534, 440, 345, 191, 131, 79, 53, 42, 23, 16, 17, 13, 13};
double y1200[50] ={34, 37, 31, 35, 35, 27, 48, 40, 39, 64, 57, 58, 58, 70, 94, 125, 118, 126, 189, 172, 185, 220, 238, 256, 283, 304, 303, 349, 364, 461, 506, 690, 784, 934, 1060, 1146, 1019, 771, 492, 303, 176, 78, 49, 46, 17, 24, 14, 6, 15, 6};
double y2000[50] ={52, 41, 36, 59, 62, 70, 55, 72, 83, 80, 92, 103, 140, 151, 175, 164, 213, 230, 279, 302, 359, 343, 419, 441, 496, 525, 524, 643, 746, 759, 1038, 1260, 1516, 1973, 2176, 2115, 1596, 994, 498, 214, 115, 60, 39, 20, 17, 14, 7, 12, 9, 7};
double y3500[50] ={83, 100, 88, 98, 127, 126, 135, 129, 152, 166, 170, 176, 223, 198, 216, 264, 302, 338, 350, 415, 452, 487, 461, 498, 554, 613, 715, 759, 842, 959, 1232, 1481, 1904, 2349, 2465, 2033, 1144, 521, 189, 72, 35, 18, 11, 4, 2, 1, 1, 3, 0, 1};
*/
/// D6T summer11 calo-qg
/*
double y700[50] ={122, 146, 165, 165, 214, 240, 255, 313, 348, 421, 442, 504, 585, 633, 751, 746, 923, 1068, 1112, 1207, 1374, 1474, 1513, 1620, 1762, 1895, 2022, 2160, 2399, 2662, 3070, 3512, 3863, 4109, 4103, 3974, 3451, 2812, 2142, 1539, 1077, 769, 559, 392, 374, 287, 254, 217, 165, 166};
double y1200[50] ={117, 181, 169, 204, 214, 230, 294, 302, 337, 387, 443, 539, 595, 628, 704, 835, 931, 1011, 1131, 1247, 1324, 1524, 1542, 1645, 1694, 1861, 1986, 2213, 2359, 2651, 3126, 3741, 4251, 4526, 4638, 4168, 3293, 2314, 1545, 1018, 682, 449, 313, 261, 209, 164, 152, 124, 105, 92};
double y2000[50] ={129, 143, 164, 205, 200, 270, 285, 292, 307, 385, 391, 504, 555, 617, 719, 774, 933, 938, 1013, 1142, 1219, 1314, 1363, 1459, 1611, 1643, 1725, 1924, 2198, 2461, 2809, 3355, 4039, 4471, 4415, 3549, 2595, 1512, 881, 521, 320, 218, 192, 133, 99, 80, 64, 51, 47, 39};
double y3500[50] ={459, 515, 585, 632, 696, 642, 716, 684, 746, 808, 819, 843, 961, 980, 1014, 1065, 1214, 1264, 1324, 1414, 1468, 1567, 1538, 1628, 1708, 1825, 1918, 2089, 2319, 2627, 3050, 3615, 4179, 4538, 4090, 2755, 1551, 734, 363, 198, 119, 69, 46, 31, 22, 11, 11, 9, 6, 4};
*/
/// D6T summer11 calo-gg
/*
double y700[50] ={157, 164, 225, 226, 221, 257, 278, 259, 283, 322, 365, 344, 374, 381, 468, 471, 498, 453, 469, 518, 437, 509, 503, 530, 554, 530, 570, 598, 616, 666, 676, 679, 665, 693, 644, 481, 368, 263, 188, 167, 118, 96, 81, 78, 70, 61, 44, 42, 57, 38};
double y1200[50] ={108, 114, 131, 133, 148, 167, 179, 196, 190, 206, 237, 224, 248, 263, 241, 280, 258, 289, 280, 297, 306, 299, 301, 322, 337, 342, 385, 377, 396, 372, 434, 472, 508, 466, 366, 289, 194, 114, 87, 61, 44, 41, 25, 27, 27, 24, 17, 16, 13, 13};
double y2000[50] ={78, 83, 87, 104, 93, 96, 102, 112, 121, 128, 126, 142, 140, 148, 162, 170, 193, 195, 193, 204, 178, 185, 206, 194, 210, 208, 202, 204, 242, 268, 251, 318, 372, 326, 268, 200, 94, 56, 29, 28, 15, 9, 9, 10, 4, 2, 2, 1, 3, 4};
double y3500[50] ={54, 55, 67, 58, 46, 59, 43, 58, 49, 50, 47, 64, 52, 66, 39, 60, 54, 54, 60, 67, 63, 70, 58, 54, 68, 58, 67, 82, 94, 68, 84, 108, 108, 136, 78, 49, 18, 8, 4, 5, 2, 2, 2, 0, 0, 0, 0, 1, 0, 0};
*/

//==================================== old spring 10 D6T shape===========================================//

/////qg
/*
double y500[50]= {146, 172, 193, 193, 200, 271, 286, 331, 375, 395, 477, 543, 613, 629, 769, 853, 908, 1033, 1123, 1265, 1391, 1474, 1522, 1657, 1821, 1880, 2076, 2135, 2478, 2764, 3100, 3376, 3592, 3832, 3812, 3430, 3045, 2493, 1954, 1417, 1083, 764, 609, 439, 381, 311, 281, 251, 222, 192};
double y700[50] = {172, 195, 202, 247, 249, 334, 368, 403, 479, 522, 630, 652, 733, 827, 929, 1067, 1195, 1377, 1482, 1605, 1764, 1859, 2055, 2092, 2213, 2441, 2517, 2887, 3189, 3598, 4070, 4403, 4878, 5220, 4993, 4577, 3687, 3053, 2198, 1493, 1034, 734, 541, 444, 359, 314, 268, 238, 211, 185};
double y1200[50] = {168, 183, 233, 239, 280, 311, 334, 410, 460, 508, 581, 643, 723, 806, 947, 986, 1162, 1328, 1490, 1513, 1661, 1819, 1951, 1917, 2074, 2281, 2400, 2780, 2990, 3386, 3926, 4668, 5247, 5685, 5452, 4709, 3660, 2436, 1633, 958, 643, 470, 349, 284, 223, 242, 173, 157, 136, 97};
double y2000[50] = {147, 189, 199, 241, 248, 286, 328, 313, 390, 420, 427, 556, 638, 684, 746, 856, 965, 1095, 1233, 1296, 1437, 1489, 1543, 1677, 1654, 1802, 2033, 2172, 2487, 2857, 3265, 3973, 4542, 4996, 4770, 3921, 2751, 1601, 961, 563, 355, 239, 182, 145, 117, 88, 81, 64, 39, 35};
double y3500[50] = { 559, 546, 576, 633, 711, 693, 698, 767, 827, 813, 930, 951, 987, 1068, 1129, 1139, 1262, 1312, 1422, 1499, 1547, 1588, 1708, 1678, 1803, 1768, 1894, 2218, 2481, 2733, 3138, 3742, 4484, 4626, 4130, 2801, 1605, 735, 336, 198, 99, 81, 46, 34, 17, 14, 14, 7, 6, 4};
*/

////////////gg

/*
double y500[50]= {262, 274, 288, 343, 385, 433, 480, 455, 519, 523, 592, 586, 645, 693, 681, 744, 719, 772, 833, 803, 836, 795, 876, 866, 830, 914, 920, 910, 1111, 1066, 1096, 1061, 1010, 967, 814, 669, 547, 417, 294, 229, 174, 146, 135, 132, 102, 120, 114, 94, 84, 86};
double y700[50]= {197, 200, 232, 251, 280, 305, 329, 334, 335, 382, 406, 434, 387, 456, 483, 534, 467, 535, 572, 566, 586, 584, 538, 604, 602, 587, 634, 629, 702, 772, 799, 773, 756, 704, 586, 504, 324, 223, 184, 109, 107, 107, 77, 84, 63, 64, 55, 50, 48, 26};
double y1200[50]= {124, 155, 163, 186, 180, 188, 206, 238, 241, 255, 293, 282, 290, 309, 330, 325, 369, 356, 374, 394, 374, 405, 379, 403, 383, 400, 413, 508, 464, 515, 551, 611, 621, 582, 419, 312, 206, 131, 78, 61, 57, 50, 42, 37, 30, 22, 28, 20, 21, 18};
double y2000[50]= {91, 96, 100, 101, 104, 98, 106, 133, 140, 148, 140, 149, 169, 168, 152, 160, 181, 187, 216, 198, 224, 210, 203, 237, 190, 219, 225, 246, 240, 284, 342, 322, 349, 333, 270, 160, 94, 56, 45, 22, 18, 16, 10, 8, 6, 11, 10, 4, 4, 3};
double y3500[50]= {62, 51, 42, 70, 53, 82, 69, 52, 66, 64, 58, 64, 44, 60, 52, 52, 70, 74, 53, 66, 54, 68, 68, 64, 71, 64, 75, 62, 80, 76, 88, 122, 128, 117, 71, 45, 26, 9, 3, 2, 4, 1, 0, 0, 1, 0, 0, 0, 0, 1};
*/

/////////////qq
/*
double y500[50]= {24, 16, 20, 23, 28, 30, 27, 30, 36, 35, 24, 53, 37, 59, 60, 68, 94, 83, 105, 95, 128, 137, 137, 167, 164, 169, 235, 220, 258, 276, 295, 372, 413, 441, 498,543, 515, 477, 379, 271, 198, 145, 96, 63, 39, 32, 36, 19, 16, 19};
double y700[50]= {21, 15, 15, 21, 28, 36, 23, 40, 36, 46, 40, 73, 49, 61, 66, 65, 93, 108, 113, 108, 119, 160, 175, 167, 211, 210, 250, 270, 279, 333, 362, 445, 502, 609, 642, 660, 674, 540, 442, 253, 163, 118, 53, 44, 35, 30, 18, 13, 15, 11};
double y1200[50]= {38, 44, 43, 49, 44, 49, 47, 60, 58, 64, 70, 89, 71, 108, 117, 135, 167, 183, 211, 226, 257, 299, 295, 331, 309, 365, 434, 442, 475, 617, 724, 882, 1011, 1319, 1385, 1408, 1165, 931, 521, 277, 135, 86, 57, 26, 23, 23, 14, 17, 11, 14};
double y2000[50]= {42, 57, 48, 51, 58, 56, 61, 80, 92, 89, 93, 114, 125, 167, 170, 215, 206, 264, 302, 321, 342, 385, 441, 489, 464, 521, 616, 664, 759, 879, 1067, 1304, 1611, 2048, 2215, 2136, 1622, 1013, 497, 224, 112, 60, 40, 26, 21, 14, 15, 6, 4, 3};
double y3500[50]= {103, 75, 107, 96, 92, 109, 151, 124, 149, 169, 170, 201, 161, 214, 249, 277, 287, 362, 344, 407, 414, 466, 493, 537, 554, 617, 680, 769, 930, 968, 1202, 1524, 1947, 2451, 2482, 1890, 1169, 479, 183, 43, 25, 13, 8, 4, 4, 1, 2, 2, 0, 1};
*/


///// PF-qg
/*
double y500[50] ={41, 41, 62, 72, 91, 103, 145, 157, 173, 238, 292, 365, 448, 496, 526, 672, 688, 822, 912, 1049, 1066, 1144, 1198, 1322, 1418, 1457, 1485, 1680, 1887, 2082, 2392, 2678, 3003, 3179, 3199, 2896, 2397, 1874, 1396, 1032, 764, 569, 395, 321, 312, 248, 230, 183, 204, 155};
double y700[50] ={84, 103, 138, 150, 186, 204, 293, 260, 368, 395, 447, 507, 567, 600, 709, 780, 855, 975, 1128, 1196, 1253, 1436, 1413, 1542, 1556, 1712, 1785, 2050, 2284, 2524, 2740, 3388, 3704, 4021, 3961, 3557, 2969, 2216, 1564, 1066, 740, 551, 444, 343, 275, 251, 204, 186, 153, 158};
double y1200[50] ={117, 140, 147, 152, 143, 202, 223, 260, 286, 341, 363, 390, 457, 507, 581, 611, 699, 820, 879, 957, 1036, 1113, 1140, 1187, 1209, 1345, 1474, 1639, 1833, 1909, 2331, 2703, 3276, 3626, 3591, 3183, 2407, 1724, 1012, 713, 447, 321, 224, 177, 178, 159, 127, 94, 92, 84};
double y2000[50] ={142, 168, 206, 225, 246, 252, 297, 319, 344, 379, 439, 523, 557, 673, 681, 792, 895, 980, 1141, 1222, 1336, 1432, 1428, 1586, 1604, 1641, 1849, 2049, 2216, 2632, 3028, 3539, 4240, 4831, 4903, 4191, 3000, 1708, 1085, 679, 411, 278, 212, 137, 122, 106, 79, 67, 55, 45};
double y3500[50] ={464, 514, 499, 575, 581, 647, 658, 624, 740, 763, 819, 797, 911, 905, 1007, 1001, 1093, 1128, 1219, 1316, 1347, 1410, 1441, 1515, 1522, 1551, 1667, 1831, 2035, 2252, 2590, 3052, 3775, 4184, 3963, 3088, 1946, 1047, 489, 243, 144, 89, 58, 36, 27, 20, 15, 9, 4, 6};
*/

///// PF-gg
/*
double y500[50] ={14, 23, 11, 16, 26, 39, 43, 52, 65, 79, 93, 118, 97, 128, 151, 179, 181, 183, 203, 207, 244, 226, 243, 244, 225, 222, 220, 247, 267, 282, 283, 297, 314, 273, 305, 250, 186, 133, 97, 86, 75, 55, 34, 40, 38, 32, 33, 30, 34, 25};
double y700[50] ={63, 90, 103, 133, 169, 204, 233, 283, 253, 332, 327, 329, 345, 390, 403, 405, 446, 408, 486, 469, 476, 503, 490, 488, 506, 512, 477, 518, 548, 553, 629, 672, 699, 701, 609, 501, 387, 265, 191, 150, 119, 90, 86, 68, 58, 45, 58, 55, 49, 35};
double y1200[50] ={106, 137, 107, 145, 137, 166, 173, 183, 219, 217, 219, 219, 261, 262, 260, 278, 296, 285, 298, 333, 323, 337, 328, 335, 324, 334, 342, 387, 408, 399, 405, 503, 553, 540, 487, 359, 243, 138, 92, 83, 46, 49, 40, 31, 33, 23, 23, 20, 18, 13};
double y2000[50] ={63, 74, 68, 90, 89, 88, 101, 102, 111, 135, 124, 134, 120, 132, 135, 153, 147, 164, 158, 168, 189, 168, 194, 189, 167, 166, 200, 196, 216, 254, 246, 281, 292, 346, 285, 205, 97, 60, 53, 22, 18, 21, 15, 11, 8, 8, 7, 9, 2, 2};
double y3500[50] ={53, 56, 46, 57, 50, 71, 66, 66, 47, 54, 64, 58, 48, 56, 55, 50, 51, 59, 60, 64, 60, 70, 55, 61, 60, 61, 62, 65, 66, 75, 82, 105, 109, 114, 95, 61, 37, 18, 10, 4, 2, 3, 2, 0, 0, 1, 0, 0, 0, 0};
*/


///// PF-qq
/*
double y500[50] ={0, 1, 1, 0, 1, 1, 3, 1, 3, 0, 4, 1, 2, 5, 1, 3, 3, 6, 4, 3, 6, 5, 8, 4, 7, 3, 3, 5, 5, 8, 3, 5, 1, 9, 13, 6, 3, 6, 8, 9, 9, 4, 9, 9, 9, 4, 7, 7, 13, 11};
double y700[50] ={14, 9, 14, 14, 14, 24, 24, 25, 32, 32, 44, 32, 44, 47, 49, 57, 74, 67, 102, 101, 116, 116, 143, 134, 196, 217, 196, 236, 245, 318, 353, 427, 532, 609, 648, 622, 513, 371, 275, 146, 97, 78, 44, 32, 34, 13, 16, 20, 11, 10};
double y1200[50] ={37, 52, 35, 30, 42, 46, 45, 39, 48, 47, 55, 60, 78, 91, 81, 117, 125, 146, 177, 177, 230, 237, 251, 277, 275, 300, 357, 364, 412, 520, 691, 786, 976, 1176, 1366, 1260, 962, 639, 392, 198, 125, 83, 47, 33, 27, 25, 14, 10, 7, 8};
double y2000[50] ={41, 45, 49, 54, 44, 60, 54, 65, 74, 73, 80, 88, 102, 118, 136, 172, 175, 197, 234, 269, 309, 320, 349, 390, 405, 453, 494, 583, 623, 746, 901, 1116, 1491, 1817, 2074, 1973, 1455, 844, 417, 254, 120, 61, 43, 25, 13, 20, 18, 8, 5, 2};
double y3500[50] ={86, 87, 93, 87, 95, 105, 141, 126, 150, 145, 144, 186, 173, 175, 232, 233, 265, 325, 327, 371, 387, 418, 424, 487, 513, 583, 617, 690, 832, 882, 1105, 1384, 1774, 2159, 2471, 2103, 1345, 705, 268, 110, 46, 19, 14, 7, 6, 2, 2, 3, 1, 1};
*/

///// FAT11 - qg
/*
double y500[50] ={27, 30, 41, 53, 52, 74, 106, 117, 114, 167, 204, 279, 295, 357, 375, 438, 486, 615, 625, 731, 805, 872, 883, 992, 1061, 1119, 1121, 1340, 1494, 1720, 2047, 2425, 2875, 3240, 3488, 3312, 3032, 2569, 1925, 1555, 1229, 948, 739, 553, 469, 427, 369, 292, 291, 245};
double y700[50] ={69, 79, 118, 120, 150, 138, 213, 206, 260, 290, 339, 406, 421, 451, 504, 560, 653, 728, 812, 878, 951, 993, 1026, 1119, 1192, 1250, 1344, 1572, 1795, 2043, 2314, 3019, 3638, 4157, 4541, 4438, 3806, 3025, 2293, 1661, 1243, 983, 723, 596, 490, 430, 344, 303, 243, 236};
double y1200[50] ={94, 135, 134, 133, 121, 161, 178, 186, 220, 258, 284, 301, 360, 345, 421, 453, 515, 617, 678, 693, 730, 795, 808, 897, 898, 1012, 1102, 1238, 1421, 1601, 2024, 2460, 3174, 3749, 4050, 4034, 3216, 2453, 1653, 1155, 786, 599, 462, 352, 298, 287, 214, 189, 168, 123};
double y2000[50] ={118, 153, 161, 185, 200, 230, 237, 260, 268, 308, 359, 408, 415, 471, 541, 607, 655, 751, 814, 915, 932, 1017, 1100, 1137, 1177, 1259, 1415, 1589, 1790, 2109, 2553, 3223, 4164, 5153, 5693, 5516, 4157, 2728, 1772, 1156, 783, 563, 390, 357, 251, 199, 184, 147, 124, 89};
double y3500[50] ={420, 470, 449, 498, 524, 609, 615, 527, 644, 694, 712, 680, 766, 799, 852, 913, 903, 968, 1033, 1026, 1070, 1167, 1189, 1139, 1308, 1330, 1421, 1499, 1687, 1996, 2259, 2818, 3864, 4728, 4922, 4151, 2967, 1753, 1026, 544, 341, 234, 147, 80, 73, 51, 47, 31, 13, 16};
*/

///// FAT11 - gg
/*
double y500[50] ={8, 17, 11, 8, 23, 25, 22, 28, 37, 55, 53, 83, 77, 109, 102, 120, 127, 139, 148, 152, 183, 185, 198, 209, 193, 208, 206, 226, 236, 276, 243, 298, 328, 336, 344, 291, 269, 213, 166, 154, 138, 103, 59, 56, 72, 47, 62, 45, 33, 39};
double y700[50] ={45, 60, 83, 93, 117, 133, 181, 217, 209, 236, 268, 275, 260, 295, 346, 340, 362, 333, 365, 367, 381, 430, 406, 435, 401, 438, 418, 460, 480, 505, 588, 636, 735, 800, 787, 737, 611, 445, 358, 298, 256, 172, 150, 129, 110, 87, 97, 77, 61, 56};
double y1200[50] ={83, 104, 103, 124, 93, 132, 145, 173, 186, 173, 180, 171, 211, 207, 208, 215, 239, 254, 238, 275, 273, 269, 278, 264, 264, 313, 277, 309, 342, 361, 382, 475, 558, 661, 679, 590, 422, 273, 200, 125, 118, 108, 83, 85, 54, 43, 46, 34, 34, 25};
double y2000[50] ={59, 56, 58, 67, 82, 81, 76, 93, 85, 108, 104, 108, 115, 116, 111, 113, 141, 134, 147, 117, 152, 128, 127, 145, 164, 157, 135, 164, 183, 225, 231, 261, 311, 392, 423, 328, 214, 121, 116, 83, 58, 45, 41, 26, 18, 25, 17, 22, 12, 5};
double y3500[50] ={46, 40, 52, 60, 53, 61, 71, 54, 53, 44, 56, 53, 43, 58, 44, 58, 46, 42, 49, 55, 50, 57, 58, 56, 46, 58, 52, 54, 54, 64, 70, 104, 127, 135, 134, 108, 77, 53, 27, 20, 11, 6, 6, 4, 3, 1, 2, 1, 0, 1};
*/

///// FAT11 - qq

/*
double y500[50] ={0, 1, 1, 0, 1, 1, 3, 1, 2, 0, 4, 1, 1, 4, 0, 2, 4, 3, 0, 2, 6, 2, 7, 3, 8, 4, 5, 5, 3, 4, 2, 6, 2, 4, 11, 5, 2, 7, 4, 8, 10, 8, 12, 8, 7, 6, 11, 5, 4, 5};
double y700[50] ={12, 7, 11, 14, 10, 15, 18, 24, 28, 24, 34, 28, 38, 42, 38, 33, 52, 54, 81, 70, 90, 79, 107, 90, 150, 144, 167, 181, 201, 262, 290, 371, 508, 604, 688, 689, 585, 499, 340, 219, 162, 125, 82, 69, 50, 28, 30, 37, 25, 17};
double y1200[50] ={34, 50, 37, 39, 37, 36, 44, 40, 30, 47, 50, 50, 53, 63, 66, 78, 97, 114, 132, 135, 158, 155, 174, 210, 201, 230, 290, 307, 309, 417, 550, 672, 914, 1207, 1429, 1461, 1254, 817, 549, 350, 196, 152, 86, 61, 59, 43, 36, 27, 14, 16};
double y2000[50] ={33, 39, 40, 54, 36, 57, 46, 59, 57, 53, 79, 72, 82, 83, 106, 118, 157, 173, 180, 188, 247, 256, 240, 286, 315, 353, 334, 477, 504, 607, 763, 950, 1410, 1815, 2241, 2297, 1799, 1141, 660, 397, 212, 117, 104, 68, 36, 44, 24, 21, 17, 12};
double y3500[50] ={80, 80, 101, 78, 90, 94, 113, 117, 143, 134, 128, 153, 160, 163, 192, 201, 226, 268, 273, 292, 310, 348, 314, 383, 419, 438, 543, 557, 691, 786, 929, 1253, 1649, 2243, 2814, 2561, 1803, 1009, 429, 179, 108, 42, 29, 15, 9, 5, 4, 4, 1, 1};
*/

double bincenter[50]={
  0.31,  0.33,  0.35,  0.37,  0.39,  0.41,  0.43,  0.45,  0.47,  0.49,
  0.51,  0.53,  0.55,  0.57,  0.59,  0.61,  0.63,  0.65,  0.67,  0.69,
  0.71,  0.73,  0.75,  0.77,  0.79,  0.81,  0.83,  0.85,  0.87,  0.89,
  0.91,  0.93,  0.95,  0.97,  0.99,  1.01,  1.03,  1.05,  1.07,  1.09,
  1.11,  1.13,  1.15,  1.17,  1.19,  1.21,  1.23,  1.25,  1.27,  1.29};


std::vector<double> v;

double mqstar[5] = {700., 1200., 2000., 3500., 4000.};

const int nMassBins = 103;
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
				      354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687,
				      1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509,
				      4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072, 10430, 
				      10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

double binwidth[nMassBins+1] = {2, 3, 4, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 18, 19, 20, 21, 23, 24, 26, 26, 29, 29, 32, 33, 34, 36, 37, 39, 41, 43, 
				44, 47, 48, 50, 52, 54, 56, 58, 60, 63, 65, 67, 70, 72, 75, 77, 80, 83, 86, 89, 92, 95, 99, 101, 106, 108, 113, 116, 120, 124, 128, 132, 137, 142, 146,
				150, 156, 161, 166, 172, 177, 183, 189, 195, 202, 208, 214, 222, 229, 236, 244, 252, 260, 269, 277, 286, 295, 305, 315, 324, 335, 346, 358, 368, 381, 
				392, 406, 418, 432, 445, 460, 268};

double massnew[nMassBins+1];
double FoundQstarBinnedProb[nMassBins+1];

const unsigned int n = 50;
double x[n];
double y[n];
double f[n];


void LineShapeDensity_pdf(double mass, int iResonance){

  vy->Clear();

  TArrayD *dv500, *dv700, *dv1200, *dv2000, *dv3500, *dv4000;

  std::cout << "iResonance = " << iResonance << std::endl;

  switch (iResonance){

  case 11: 
    std::cout << "RSGraviton_ak5_GGtoGG_fat30" << std::endl;
    dv500 = new TArrayD(50,  RSGravitonToJJ_M_500_TuneD6T_ak5GGtoGG_fat30);
    dv700 = new TArrayD(50,  RSGravitonToJJ_M_700_TuneD6T_ak5GGtoGG_fat30);
    dv1200 = new TArrayD(50, RSGravitonToJJ_M_1200_TuneD6T_ak5GGtoGG_fat30);
    dv2000 = new TArrayD(50, RSGravitonToJJ_M_2000_TuneD6T_ak5GGtoGG_fat30);
    dv3500 = new TArrayD(50, RSGravitonToJJ_M_3500_TuneD6T_ak5GGtoGG_fat30);
    dv4000 = new TArrayD(50, RSGravitonToJJ_M_4000_TuneD6T_ak5GGtoGG_fat30);
    break;
  case 12:   
    std::cout << "RSGraviton_ak5_QQtoQQ_fat30" << std::endl;
    dv500 = new TArrayD(50,  RSGravitonToJJ_M_500_TuneD6T_ak5QQtoQQ_fat30);
    dv700 = new TArrayD(50,  RSGravitonToJJ_M_700_TuneD6T_ak5QQtoQQ_fat30);
    dv1200 = new TArrayD(50, RSGravitonToJJ_M_1200_TuneD6T_ak5QQtoQQ_fat30);
    dv2000 = new TArrayD(50, RSGravitonToJJ_M_2000_TuneD6T_ak5QQtoQQ_fat30);
    dv3500 = new TArrayD(50, RSGravitonToJJ_M_3500_TuneD6T_ak5QQtoQQ_fat30);
    dv4000 = new TArrayD(50, RSGravitonToJJ_M_4000_TuneD6T_ak5QQtoQQ_fat30);
    break;
  case 13:   
    std::cout << "Qstar_ak5_fat30" << std::endl; 
    dv500 = new TArrayD(50,  QstarToJJ_M_500_TuneD6T_ak5_fat30);
    dv700 = new TArrayD(50,  QstarToJJ_M_700_TuneD6T_ak5_fat30);
    dv1200 = new TArrayD(50, QstarToJJ_M_1200_TuneD6T_ak5_fat30);
    dv2000 = new TArrayD(50, QstarToJJ_M_2000_TuneD6T_ak5_fat30);
    dv3500 = new TArrayD(50, QstarToJJ_M_3500_TuneD6T_ak5_fat30);
    dv4000 = new TArrayD(50, QstarToJJ_M_4000_TuneD6T_ak5_fat30);
    break;
  default:
    std::cout << "Nothing would crash" << std::endl; 
    break;
  }

  vy->Add((TObject*) dv500); 
  vy->Add((TObject*) dv700); vy->Add((TObject*) dv1200); vy->Add((TObject*) dv2000); 
  vy->Add((TObject*) dv3500); vy->Add((TObject*) dv4000);

  setArray(mass);

}


void setArray (double mass){ 



  for (int bin = 0; bin < 6; bin++){
    double sum = 0;
    for (int k = 0; k < 50; k++){
      sum += ((TArrayD*) vy->At(bin))->GetAt(k);
    }
    for (int k = 0; k < 50; k++){
      double val = ((TArrayD*) vy->At(bin))->GetAt(k);
      ((TArrayD*) vy->At(bin))->AddAt(k, val/sum);
    }
  }


  for(int ind=0;ind<nMassBins; ind++){
    double bin_width = -1;		 
    double peak_low = 0.31;
    double peak_high = 1.27;
    double mjj = (massBoundaries[ind]+massBoundaries[ind+1])/2;
    //	  cout<<ind<<"\t "<<mjj<<"\t "<<peak_low*mass<<endl;
    //if (mjj<0.3*mass || mjj>1.3*mass) {
    if (mjj<peak_low*mass || mjj>peak_high*mass) {
      FoundQstarBinnedProb[ind] = 0.;
      // Create a vector and fill it with variable x bins according to entered mass value
    }
    else {
	for(int i=0;i<103; i++){
	  massnew[i] = massBoundaries[i]/mass;
	  if (massBoundaries[i]<=mjj && massBoundaries[i+1]>=mjj) 
	    bin_width = binwidth[i];
	  if (massnew[i]<=1.32 && massnew[i]>=0.28){ // x distribution is from peak_low to peak_high
	    //if (massnew[i]<=peak_high && massnew[i]>=peak_low){ // x distribution is from peak_low to peak_high
	    v.push_back(massnew[i]);
	  }
	}
	
        const unsigned int s = v.size();
	
	// Definition of arrays with variable bins 
	double bins[1000]; // variable bins for x distribution
	double m[1000]; // variable mass bins for dijet mass distribution
	double dndm[1000];
	double prob[1000];
	
	
	// Fill the bin values to array
	for(unsigned int j=0; j<v.size(); j++){
	  bins[j] = v[j];
	  m[j] = v[j] * mass;
	}
	
	// Definition of histograms
	TH1F* h_new2 = new TH1F("h_new2","with variale bins2",s-1 , m); // Histogram for dijet mass distribution with variable mass bins
	
	if(TMath::Abs(mass - mqstar[0]) < 1e-5){ // If mass = 0.7 TeV
	  for(unsigned int k=0; k<n; k++){
	    x[k] = bincenter[k];
	    y[k] = ((TArrayD*) vy->At(1))->GetAt(k);}
	}
	
	if(TMath::Abs(mass - mqstar[1]) < 1e-5){ // If mass = 1.2 TeV
	  for(unsigned int k=0; k<n; k++){
	    x[k] = bincenter[k];
	    y[k] = ((TArrayD*) vy->At(2))->GetAt(k);}
	}
	
	if(TMath::Abs(mass - mqstar[2]) < 1e-5){ // If mass = 2 TeV
	  for(unsigned int k=0; k<n; k++){
	    x[k] = bincenter[k];
	    y[k] = ((TArrayD*) vy->At(3))->GetAt(k);}
	}
	
	if(TMath::Abs(mass - mqstar[3]) < 1e-5){ // If mass = 3.5 TeV
	  for(unsigned int k=0; k<n; k++){
	    x[k] = bincenter[k];
	    y[k] = ((TArrayD*) vy->At(4))->GetAt(k);}
	}
	if(TMath::Abs(mass-mqstar[4]) < 1e-5){ // If mass = 4.0 TeV
	  for(unsigned int k=0; k<n; k++){
	    x[k] = bincenter[k];
	    y[k] = ((TArrayD*) vy->At(4))->GetAt(k);}
	}	
	
	// Calculate and create new x distribution with fixed bins at entered mass value which is between 0.7 TeV and 1.2 TeV. 
	if(mass > mqstar[0] && mass < mqstar[1]){
	  for(unsigned int k=0; k<n; k++){
	    double bincont1 = ((TArrayD*) vy->At(1))->GetAt(k);
	    double bincont2 = ((TArrayD*) vy->At(2))->GetAt(k);
	    double Mjj1 = mqstar[0];
	    double Mjj2 = mqstar[1];
	    double Mq = mass;
	    double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
	    double eff = bincont2 - bincont1;
	    double neff = eff * norm;
	    double mqstar1 = bincont1 + neff;
	    y[k] = mqstar1;
	    x[k] = bincenter[k];}
	}
	
	// Calculate and create new x distribution with fixed bins at entered mass value which is between 1.2 TeV and 2 TeV. 
	if(mass > mqstar[1] && mass < mqstar[2]){
	  for(unsigned int k=0; k<n; k++){
	    double bincont1 = ((TArrayD*) vy->At(2))->GetAt(k);
	    double bincont2 = ((TArrayD*) vy->At(3))->GetAt(k);
	    double Mjj1 = mqstar[1];
	    double Mjj2 = mqstar[2];
	    double Mq = mass;
	    double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
	    double eff = bincont2 - bincont1;
	    double neff = eff * norm;
	    double mqstar1 = bincont1 + neff;
	    y[k] = mqstar1;
	    x[k] = bincenter[k];}
	}
	
	// Calculate and create new x distribution with fixed bins at entered mass value which is between 2 TeV and 3.5 TeV. 
	if(mass > mqstar[2] && mass < mqstar[3]){
	  for(unsigned int k=0; k<n; k++){
	    double bincont1 = ((TArrayD*) vy->At(3))->GetAt(k);
	    double bincont2 = ((TArrayD*) vy->At(4))->GetAt(k);
	    double Mjj1 = mqstar[2];
	    double Mjj2 = mqstar[3];
	    double Mq = mass;
	    double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
	    double eff = bincont2 - bincont1;
	    double neff = eff * norm;
	    double mqstar1 = bincont1 + neff;
	    y[k] = mqstar1;
	    x[k] = bincenter[k];}
	}
	
	if((mass > mqstar[3] && mass < mqstar[4]) || mass > mqstar[4]){
	  for(unsigned int k=0; k<n; k++){
	    double bincont1 = ((TArrayD*) vy->At(3))->GetAt(k);
	    double bincont2 = ((TArrayD*) vy->At(4))->GetAt(k);
	    double Mjj1 = mqstar[3];
	    double Mjj2 = mqstar[4];
	    double Mq = mass;
	    double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
	    double eff = bincont2 - bincont1;
	    double neff = eff * norm;
	    double mqstar1 = bincont1 + neff;
	    y[k] = mqstar1;
	    x[k] = bincenter[k];}
	}
	
	// Interpolation tecnique is used to convert distribution in x to distribution in dijet mass with variable bins
	ROOT::Math::Interpolator inter(n, ROOT::Math::Interpolation::kCSPLINE); // If CSPLINE is not valid, please use kCSPLINE
	inter.SetData(n, x, y);
	
	// Generate the new distribution in x with variable bins
	for(unsigned int t=0; t<n; t++)
	  f[t] = inter.Eval(x[t]);
	
	//  int bin_number = h_new->GetNbinsX();
	for(unsigned int z=0; z<s; z++){
	  double bin = 0;
	  if(v[z]>peak_low && v[z]<peak_high && v[z+1]>peak_low && v[z+1]<peak_high)
	    bin = inter.Integ(v[z], v[z+1]); 
	  
	  dndm[z] = bin;
	  h_new2->SetBinContent(z+1,bin); // histogram in dijet mass distribution with variable bins
	}
	
	v.clear();
	
	double integ = h_new2->Integral();
	h_new2->Delete();
	
	for(unsigned int p=0; p<s; p++){
	  double nor = dndm[p] / integ;
	  prob[p] = nor;
	  if(m[p]<mjj && m[p+1]>=mjj){
	    FoundQstarBinnedProb[ind] = prob[p] / bin_width;	
	    ///cout << "bin_width=" << bin_width << endl;
	  }
	}
    }
    //	 cout<<ind<<"\t mjj: "<<mjj<<"\t prob: "<<FoundQstarBinnedProb[ind]<<endl;
  }	
}


// This gets the qstar binned probability faster than the original rountine
double FastQstarBinnedProb(double mjj )
{
  int bin=0;
  int binFound=0;
  for(int i=0;i<nMassBins && binFound==0; i++){
    if(massBoundaries[i+1]>mjj){
      binFound=1;
      bin=i;
    }
  }
  return FoundQstarBinnedProb[bin];
}

