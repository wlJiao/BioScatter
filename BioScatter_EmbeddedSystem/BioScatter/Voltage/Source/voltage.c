#include "voltage.h"

extern unsigned int Outburst_Value_Shadow;
extern unsigned int Outburst_Value;

static const float voltage[2000] = {1.2,1.2009,1.2017,1.2026,1.2035,1.2043,1.2052,1.2061,1.2069,1.2078,1.2087,1.2096,1.2104,1.2113,1.2122,1.213,1.2139,1.2148,1.2157,1.2166,1.2174,1.2183,1.2192,1.2201,1.2209,1.2218,1.2227,1.2236,1.2245,1.2254,1.2262,1.2271,1.228,1.2289,1.2298,1.2307,1.2316,1.2324,1.2333,1.2342,1.2351,1.236,1.2369,1.2378,1.2387,1.2396,1.2405,1.2414,1.2423,1.2432,1.2441,1.2449,1.2458,1.2467,1.2476,1.2485,1.2494,1.2503,1.2512,1.2522,1.2531,1.254,1.2549,1.2558,1.2567,1.2576,1.2585,1.2594,1.2603,1.2612,1.2621,1.263,1.2639,1.2649,1.2658,1.2667,1.2676,1.2685,1.2694,1.2703,1.2713,1.2722,1.2731,1.274,1.2749,1.2758,1.2768,1.2777,1.2786,1.2795,1.2805,1.2814,1.2823,1.2832,1.2842,1.2851,1.286,1.2869,1.2879,1.2888,1.2897,1.2906,1.2916,1.2925,1.2934,1.2944,1.2953,1.2962,1.2972,1.2981,1.2991,1.3,1.3009,1.3019,1.3028,1.3037,1.3047,1.3056,1.3066,1.3075,1.3085,1.3094,1.3103,1.3113,1.3122,1.3132,1.3141,1.3151,1.316,1.317,1.3179,1.3189,1.3198,1.3208,1.3217,1.3227,1.3236,1.3246,1.3255,1.3265,1.3275,1.3284,1.3294,1.3303,1.3313,1.3323,1.3332,1.3342,1.3351,1.3361,1.3371,1.338,1.339,1.34,1.3409,1.3419,1.3429,1.3438,1.3448,1.3458,1.3467,1.3477,1.3487,1.3497,1.3506,1.3516,1.3526,1.3536,1.3545,1.3555,1.3565,1.3575,1.3584,1.3594,1.3604,1.3614,1.3624,1.3633,1.3643,1.3653,1.3663,1.3673,1.3683,1.3693,1.3702,1.3712,1.3722,1.3732,1.3742,1.3752,1.3762,1.3772,1.3782,1.3792,1.3802,1.3812,1.3822,1.3832,1.3841,1.3851,1.3861,1.3871,1.3881,1.3891,1.3901,1.3912,1.3922,1.3932,1.3942,1.3952,1.3962,1.3972,1.3982,1.3992,1.4002,1.4012,1.4022,1.4032,1.4043,1.4053,1.4063,1.4073,1.4083,1.4093,1.4103,1.4114,1.4124,1.4134,1.4144,1.4154,1.4165,1.4175,1.4185,1.4195,1.4205,1.4216,1.4226,1.4236,1.4247,1.4257,1.4267,1.4277,1.4288,1.4298,1.4308,1.4319,1.4329,1.4339,1.435,1.436,1.437,1.4381,1.4391,1.4401,1.4412,1.4422,1.4433,1.4443,1.4453,1.4464,1.4474,1.4485,1.4495,1.4506,1.4516,1.4527,1.4537,1.4548,1.4558,1.4569,1.4579,1.459,1.46,1.4611,1.4621,1.4632,1.4642,1.4653,1.4663,1.4674,1.4685,1.4695,1.4706,1.4716,1.4727,1.4738,1.4748,1.4759,1.4769,1.478,1.4791,1.4801,1.4812,1.4823,1.4834,1.4844,1.4855,1.4866,1.4876,1.4887,1.4898,1.4909,1.4919,1.493,1.4941,1.4952,1.4962,1.4973,1.4984,1.4995,1.5006,1.5016,1.5027,1.5038,1.5049,1.506,1.5071,1.5082,1.5092,1.5103,1.5114,1.5125,1.5136,1.5147,1.5158,1.5169,1.518,1.5191,1.5202,1.5213,1.5224,1.5235,1.5246,1.5257,1.5268,1.5279,1.529,1.5301,1.5312,1.5323,1.5334,1.5345,1.5356,1.5367,1.5378,1.5389,1.54,1.5411,1.5422,1.5434,1.5445,1.5456,1.5467,1.5478,1.5489,1.55,1.5512,1.5523,1.5534,1.5545,1.5556,1.5568,1.5579,1.559,1.5601,1.5613,1.5624,1.5635,1.5646,1.5658,1.5669,1.568,1.5692,1.5703,1.5714,1.5726,1.5737,1.5748,1.576,1.5771,1.5782,1.5794,1.5805,1.5817,1.5828,1.5839,1.5851,1.5862,1.5874,1.5885,1.5897,1.5908,1.592,1.5931,1.5943,1.5954,1.5966,1.5977,1.5989,1.6,1.6012,1.6023,1.6035,1.6046,1.6058,1.607,1.6081,1.6093,1.6104,1.6116,1.6128,1.6139,1.6151,1.6162,1.6174,1.6186,1.6197,1.6209,1.6221,1.6233,1.6244,1.6256,1.6268,1.6279,1.6291,1.6303,1.6315,1.6326,1.6338,1.635,1.6362,1.6374,1.6385,1.6397,1.6409,1.6421,1.6433,1.6445,1.6456,1.6468,1.648,1.6492,1.6504,1.6516,1.6528,1.654,1.6552,1.6564,1.6576,1.6587,1.6599,1.6611,1.6623,1.6635,1.6647,1.6659,1.6671,1.6683,1.6695,1.6708,1.672,1.6732,1.6744,1.6756,1.6768,1.678,1.6792,1.6804,1.6816,1.6828,1.6841,1.6853,1.6865,1.6877,1.6889,1.6901,1.6914,1.6926,1.6938,1.695,1.6962,1.6975,1.6987,1.6999,1.7011,1.7024,1.7036,1.7048,1.7061,1.7073,1.7085,1.7097,1.711,1.7122,1.7135,1.7147,1.7159,1.7172,1.7184,1.7196,1.7209,1.7221,1.7234,1.7246,1.7259,1.7271,1.7283,1.7296,1.7308,1.7321,1.7333,1.7346,1.7358,1.7371,1.7383,1.7396,1.7408,1.7421,1.7434,1.7446,1.7459,1.7471,1.7484,1.7497,1.7509,1.7522,1.7534,1.7547,1.756,1.7572,1.7585,1.7598,1.761,1.7623,1.7636,1.7649,1.7661,1.7674,1.7687,1.77,1.7712,1.7725,1.7738,1.7751,1.7764,1.7776,1.7789,1.7802,1.7815,1.7828,1.7841,1.7853,1.7866,1.7879,1.7892,1.7905,1.7918,1.7931,1.7944,1.7957,1.797,1.7983,1.7996,1.8009,1.8022,1.8035,1.8048,1.8061,1.8074,1.8087,1.81,1.8113,1.8126,1.8139,1.8152,1.8165,1.8178,1.8191,1.8204,1.8218,1.8231,1.8244,1.8257,1.827,1.8283,1.8296,1.831,1.8323,1.8336,1.8349,1.8363,1.8376,1.8389,1.8402,1.8416,1.8429,1.8442,1.8455,1.8469,1.8482,1.8495,1.8509,1.8522,1.8535,1.8549,1.8562,1.8576,1.8589,1.8602,1.8616,1.8629,1.8643,1.8656,1.867,1.8683,1.8697,1.871,1.8724,1.8737,1.8751,1.8764,1.8778,1.8791,1.8805,1.8818,1.8832,1.8845,1.8859,1.8873,1.8886,1.89,1.8914,1.8927,1.8941,1.8954,1.8968,1.8982,1.8996,1.9009,1.9023,1.9037,1.905,1.9064,1.9078,1.9092,1.9105,1.9119,1.9133,1.9147,1.9161,1.9174,1.9188,1.9202,1.9216,1.923,1.9244,1.9258,1.9271,1.9285,1.9299,1.9313,1.9327,1.9341,1.9355,1.9369,1.9383,1.9397,1.9411,1.9425,1.9439,1.9453,1.9467,1.9481,1.9495,1.9509,1.9523,1.9537,1.9551,1.9565,1.958,1.9594,1.9608,1.9622,1.9636,1.965,1.9664,1.9679,1.9693,1.9707,1.9721,1.9735,1.975,1.9764,1.9778,1.9792,1.9807,1.9821,1.9835,1.985,1.9864,1.9878,1.9893,1.9907,1.9921,1.9936,1.995,1.9964,1.9979,1.9993,2.0008,2.0022,2.0037,2.0051,2.0065,2.008,2.0094,2.0109,2.0123,2.0138,2.0152,2.0167,2.0182,2.0196,2.0211,2.0225,2.024,2.0254,2.0269,2.0284,2.0298,2.0313,2.0328,2.0342,2.0357,2.0372,2.0386,2.0401,2.0416,2.043,2.0445,2.046,2.0475,2.0489,2.0504,2.0519,2.0534,2.0549,2.0563,2.0578,2.0593,2.0608,2.0623,2.0638,2.0653,2.0668,2.0682,2.0697,2.0712,2.0727,2.0742,2.0757,2.0772,2.0787,2.0802,2.0817,2.0832,2.0847,2.0862,2.0877,2.0892,2.0907,2.0922,2.0937,2.0953,2.0968,2.0983,2.0998,2.1013,2.1028,2.1043,2.1059,2.1074,2.1089,2.1104,2.1119,2.1135,2.115,2.1165,2.118,2.1196,2.1211,2.1226,2.1242,2.1257,2.1272,2.1288,2.1303,2.1318,2.1334,2.1349,2.1364,2.138,2.1395,2.1411,2.1426,2.1442,2.1457,2.1473,2.1488,2.1504,2.1519,2.1535,2.155,2.1566,2.1581,2.1597,2.1612,2.1628,2.1644,2.1659,2.1675,2.169,2.1706,2.1722,2.1737,2.1753,2.1769,2.1784,2.18,2.1816,2.1832,2.1847,2.1863,2.1879,2.1895,2.1911,2.1926,2.1942,2.1958,2.1974,2.199,2.2006,2.2021,2.2037,2.2053,2.2069,2.2085,2.2101,2.2117,2.2133,2.2149,2.2165,2.2181,2.2197,2.2213,2.2229,2.2245,2.2261,2.2277,2.2293,2.2309,2.2325,2.2341,2.2357,2.2373,2.239,2.2406,2.2422,2.2438,2.2454,2.247,2.2487,2.2503,2.2519,2.2535,2.2552,2.2568,2.2584,2.26,2.2617,2.2633,2.2649,2.2666,2.2682,2.2698,2.2715,2.2731,2.2748,2.2764,2.278,2.2797,2.2813,2.283,2.2846,2.2863,2.2879,2.2896,2.2912,2.2929,2.2945,2.2962,2.2978,2.2995,2.3012,2.3028,2.3045,2.3061,2.3078,2.3095,2.3111,2.3128,2.3145,2.3161,2.3178,2.3195,2.3212,2.3228,2.3245,2.3262,2.3279,2.3295,2.3312,2.3329,2.3346,2.3363,2.3379,2.3396,2.3413,2.343,2.3447,2.3464,2.3481,2.3498,2.3515,2.3532,2.3549,2.3566,2.3583,2.36,2.3617,2.3634,2.3651,2.3668,2.3685,2.3702,2.3719,2.3736,2.3753,2.377,2.3788,2.3805,2.3822,2.3839,2.3856,2.3873,2.3891,2.3908,2.3925,2.3942,2.396,2.3977,2.3994,2.4012,2.4029,2.4046,2.4064,2.4081,2.4098,2.4116,2.4133,2.4151,2.4168,2.4185,2.4203,2.422,2.4238,2.4255,2.4273,2.429,2.4308,2.4325,2.4343,2.436,2.4378,2.4396,2.4413,2.4431,2.4448,2.4466,2.4484,2.4501,2.4519,2.4537,2.4554,2.4572,2.459,2.4608,2.4625,2.4643,2.4661,2.4679,2.4696,2.4714,2.4732,2.475,2.4768,2.4786,2.4803,2.4821,2.4839,2.4857,2.4875,2.4893,2.4911,2.4929,2.4947,2.4965,2.4983,2.5001,2.5019,2.5037,2.5055,2.5073,2.5091,2.5109,2.5127,2.5146,2.5164,2.5182,2.52,2.5218,2.5236,2.5255,2.5273,2.5291,2.5309,2.5328,2.5346,2.5364,2.5382,2.5401,2.5419,2.5437,2.5456,2.5474,2.5492,2.5511,2.5529,2.5548,2.5566,2.5585,2.5603,2.5621,2.564,2.5658,2.5677,2.5695,2.5714,2.5733,2.5751,2.577,2.5788,2.5807,2.5825,2.5844,2.5863,2.5881,2.59,2.5919,2.5937,2.5956,2.5975,2.5994,2.6012,2.6031,2.605,2.6069,2.6087,2.6106,2.6125,2.6144,2.6163,2.6182,2.6201,2.6219,2.6238,2.6257,2.6276,2.6295,2.6314,2.6333,2.6352,2.6371,2.639,2.6409,2.6428,2.6447,2.6466,2.6485,2.6505,2.6524,2.6543,2.6562,2.6581,2.66,2.662,2.6639,2.6658,2.6677,2.6696,2.6716,2.6735,2.6754,2.6774,2.6793,2.6812,2.6831,2.6851,2.687,2.689,2.6909,2.6928,2.6948,2.6967,2.6987,2.7006,2.7026,2.7045,2.7065,2.7084,2.7104,2.7123,2.7143,2.7162,2.7182,2.7202,2.7221,2.7241,2.726,2.728,2.73,2.732,2.7339,2.7359,2.7379,2.7398,2.7418,2.7438,2.7458,2.7478,2.7497,2.7517,2.7537,2.7557,2.7577,2.7597,2.7617,2.7637,2.7656,2.7676,2.7696,2.7716,2.7736,2.7756,2.7776,2.7796,2.7816,2.7837,2.7857,2.7877,2.7897,2.7917,2.7937,2.7957,2.7977,2.7998,2.8018,2.8038,2.8058,2.8078,2.8099,2.8119,2.8139,2.8159,2.818,2.82,2.822,2.8241,2.8261,2.8282,2.8302,2.8322,2.8343,2.8363,2.8384,2.8404,2.8425,2.8445,2.8466,2.8486,2.8507,2.8527,2.8548,2.8569,2.8589,2.861,2.863,2.8651,2.8672,2.8692,2.8713,2.8734,2.8755,2.8775,2.8796,2.8817,2.8838,2.8858,2.8879,2.89,2.8921,2.8942,2.8963,2.8983,2.9004,2.9025,2.9046,2.9067,2.9088,2.9109,2.913,2.9151,2.9172,2.9193,2.9214,2.9235,2.9256,2.9278,2.9299,2.932,2.9341,2.9362,2.9383,2.9404,2.9426,2.9447,2.9468,2.9489,2.9511,2.9532,2.9553,2.9575,2.9596,2.9617,2.9639,2.966,2.9681,2.9703,2.9724,2.9746,2.9767,2.9789,2.981,2.9832,2.9853,2.9875,2.9896,2.9918,2.9939,2.9961,2.9983,3.0004,3.0026,3.0047,3.0069,3.0091,3.0113,3.0134,3.0156,3.0178,3.0199,3.0221,3.0243,3.0265,3.0287,3.0309,3.033,3.0352,3.0374,3.0396,3.0418,3.044,3.0462,3.0484,3.0506,3.0528,3.055,3.0572,3.0594,3.0616,3.0638,3.066,3.0682,3.0704,3.0727,3.0749,3.0771,3.0793,3.0815,3.0838,3.086,3.0882,3.0904,3.0927,3.0949,3.0971,3.0994,3.1016,3.1038,3.1061,3.1083,3.1106,3.1128,3.115,3.1173,3.1195,3.1218,3.124,3.1263,3.1286,3.1308,3.1331,3.1353,3.1376,3.1399,3.1421,3.1444,3.1466,3.1489,3.1512,3.1535,3.1557,3.158,3.1603,3.1626,3.1649,3.1671,3.1694,3.1717,3.174,3.1763,3.1786,3.1809,3.1832,3.1855,3.1878,3.1901,3.1924,3.1947,3.197,3.1993,3.2016,3.2039,3.2062,3.2085,3.2108,3.2131,3.2155,3.2178,3.2201,3.2224,3.2247,3.2271,3.2294,3.2317,3.2341,3.2364,3.2387,3.2411,3.2434,3.2457,3.2481,3.2504,3.2528,3.2551,3.2575,3.2598,3.2622,3.2645,3.2669,3.2692,3.2716,3.2739,3.2763,3.2787,3.281,3.2834,3.2858,3.2881,3.2905,3.2929,3.2953,3.2976,3.3,3.3024,3.3048,3.3072,3.3095,3.3119,3.3143,3.3167,3.3191,3.3215,3.3239,3.3263,3.3287,3.3311,3.3335,3.3359,3.3383,3.3407,3.3431,3.3455,3.3479,3.3504,3.3528,3.3552,3.3576,3.36,3.3625,3.3649,3.3673,3.3697,3.3722,3.3746,3.377,3.3795,3.3819,3.3844,3.3868,3.3892,3.3917,3.3941,3.3966,3.399,3.4015,3.4039,3.4064,3.4088,3.4113,3.4138,3.4162,3.4187,3.4212,3.4236,3.4261,3.4286,3.431,3.4335,3.436,3.4385,3.4409,3.4434,3.4459,3.4484,3.4509,3.4534,3.4559,3.4584,3.4608,3.4633,3.4658,3.4683,3.4708,3.4733,3.4759,3.4784,3.4809,3.4834,3.4859,3.4884,3.4909,3.4934,3.496,3.4985,3.501,3.5035,3.5061,3.5086,3.5111,3.5137,3.5162,3.5187,3.5213,3.5238,3.5263,3.5289,3.5314,3.534,3.5365,3.5391,3.5416,3.5442,3.5467,3.5493,3.5519,3.5544,3.557,3.5596,3.5621,3.5647,3.5673,3.5698,3.5724,3.575,3.5776,3.5801,3.5827,3.5853,3.5879,3.5905,3.5931,3.5957,3.5983,3.6009,3.6034,3.606,3.6087,3.6113,3.6139,3.6165,3.6191,3.6217,3.6243,3.6269,3.6295,3.6321,3.6348,3.6374,3.64,3.6426,3.6453,3.6479,3.6505,3.6532,3.6558,3.6584,3.6611,3.6637,3.6663,3.669,3.6716,3.6743,3.6769,3.6796,3.6822,3.6849,3.6876,3.6902,3.6929,3.6955,3.6982,3.7009,3.7035,3.7062,3.7089,3.7116,3.7142,3.7169,3.7196,3.7223,3.725,3.7277,3.7303,3.733,3.7357,3.7384,3.7411,3.7438,3.7465,3.7492,3.7519,3.7546,3.7573,3.7601,3.7628,3.7655,3.7682,3.7709,3.7736,3.7764,3.7791,3.7818,3.7845,3.7873,3.79,3.7927,3.7955,3.7982,3.8009,3.8037,3.8064,3.8092,3.8119,3.8147,3.8174,3.8202,3.8229,3.8257,3.8284,3.8312,3.834,3.8367,3.8395,3.8423,3.845,3.8478,3.8506,3.8534,3.8561,3.8589,3.8617,3.8645,3.8673,3.8701,3.8729,3.8757,3.8785,3.8813,3.8841,3.8869,3.8897,3.8925,3.8953,3.8981,3.9009,3.9037,3.9065,3.9093,3.9122,3.915,3.9178,3.9206,3.9235,3.9263,3.9291,3.932,3.9348,3.9376,3.9405,3.9433,3.9462,3.949,3.9518,3.9547,3.9576,3.9604,3.9633,3.9661,3.969,3.9718,3.9747,3.9776,3.9804,3.9833,3.9862,3.9891,3.9919,3.9948,3.9977,4.0006,4.0035,4.0064,4.0092,4.0121,4.015,4.0179,4.0208,4.0237,4.0266,4.0295,4.0324,4.0354,4.0383,4.0412,4.0441,4.047,4.0499,4.0528,4.0558,4.0587,4.0616,4.0646,4.0675,4.0704,4.0734,4.0763,4.0792,4.0822,4.0851,4.0881,4.091,4.094,4.0969,4.0999,4.1028,4.1058,4.1088,4.1117,4.1147,4.1176,4.1206,4.1236,4.1266,4.1295,4.1325,4.1355,4.1385,4.1415,4.1445,4.1474,4.1504,4.1534,4.1564,4.1594,4.1624,4.1654,4.1684,4.1714,4.1744,4.1775,4.1805,4.1835,4.1865,4.1895,4.1925,4.1956,4.1986,4.2016,4.2047,4.2077,4.2107,4.2138,4.2168,4.2198,4.2229,4.2259,4.229,4.232,4.2351,4.2381,4.2412,4.2443,4.2473,4.2504,4.2534,4.2565,4.2596,4.2627,4.2657,4.2688,4.2719,4.275,4.278,4.2811,4.2842,4.2873,4.2904,4.2935,4.2966,4.2997,4.3028,4.3059,4.309,4.3121,4.3152,4.3183,4.3215,4.3246,4.3277,4.3308,4.3339,4.3371,4.3402,4.3433,4.3464,4.3496,4.3527,4.3559,4.359,4.3621,4.3653,4.3684,4.3716,4.3747,4.3779,4.3811,4.3842,4.3874,4.3905,4.3937,4.3969,4.4001,4.4032,4.4064,4.4096,4.4128,4.4159,4.4191,4.4223,4.4255,4.4287,4.4319,4.4351,4.4383,4.4415,4.4447,4.4479,4.4511,4.4543,4.4575,4.4607,4.464,4.4672,4.4704,4.4736,4.4769,4.4801,4.4833,4.4866,4.4898,4.493,4.4963,4.4995,4.5028,4.506,4.5093,4.5125,4.5158,4.519,4.5223,4.5255,4.5288,4.5321,4.5353,4.5386,4.5419,4.5452,4.5484,4.5517,4.555,4.5583,4.5616,4.5649,4.5682,4.5715,4.5748,4.5781,4.5814,4.5847,4.588,4.5913,4.5946,4.5979,4.6012,4.6045,4.6079,4.6112,4.6145,4.6178,4.6212,4.6245,4.6278,4.6312,4.6345,4.6379,4.6412,4.6445,4.6479,4.6513,4.6546,4.658,4.6613,4.6647,4.668,4.6714,4.6748,4.6782,4.6815,4.6849,4.6883,4.6917,4.6951,4.6984,4.7018,4.7052,4.7086,4.712,4.7154,4.7188,4.7222,4.7256,4.729,4.7324,4.7359,4.7393,4.7427,4.7461,4.7495,4.753,4.7564,4.7598,4.7632,4.7667,4.7701,4.7736,4.777,4.7805,4.7839,4.7874,4.7908,4.7943,4.7977,4.8012,4.8046,4.8081,4.8116,4.815,4.8185,4.822,4.8255,4.829,4.8324,4.8359,4.8394,4.8429,4.8464,4.8499,4.8534,4.8569,4.8604,4.8639,4.8674,4.8709,4.8744,4.8779,4.8815,4.885,4.8885,4.892,4.8956,4.8991,4.9026,4.9062,4.9097,4.9132,4.9168,4.9203,4.9239,4.9274,4.931,4.9345,4.9381,4.9417,4.9452,4.9488,4.9524,4.9559,4.9595,4.9631,4.9667,4.9703,4.9738,4.9774,4.981,4.9846,4.9882,4.9918,4.9954,4.999,5.0026,5.0062,5.0098,5.0134,5.0171,5.0207,5.0243,5.0279,5.0316,5.0352,5.0388,5.0424,5.0461,5.0497,5.0534,5.057,5.0607,5.0643,5.068,5.0716};
static unsigned int dropDuration = 0, preTimePoint = 0;
static const float op0 = PWMInputVolt*11;
static float op1,op2,op3;
static unsigned int stage = 0;

void V_Init()
{
    /* P2.2: Charge and discharge pin */
    P2SEL0 &= ~BIT2;
    P2SEL1 &= ~BIT2;
    P2OUT &= ~BIT2;
    P2DIR |= BIT2;

    /* P2.5: Comparator input(+) pin */
    P2SEL0 |= BIT5;
    P2SEL1 |= BIT5;
}


void VTask_Activate(void)
{
    switch(stage)
    {
    case 0:
    {
        V_stopFlag = 0;
        stage = 1;

        /* TB1��Charging time setting */
        TB1CCR1 = ChargingDuration-1;
        TB1CCTL1 = CAP__COMPARE|CCIE;
        TB1CTL = TBCLR|TBSSEL__ACLK|MC__CONTINUOUS;

        /* Charge the capacitor */
        P2OUT |= BIT2;
    }break;
    case 1:
    {
        stage = 0;

        /* Comparator setup */
        CP1CTL0 = CPNEN_1|CPNSEL_2|CPPEN_1|CPPSEL_0;
        CP1CTL1 = CPMSEL_1|CPEN|CPIIE_1;

        /* Set the reference voltage to the comparator input(-) */
        PMMCTL2 = INTREFEN_1;

        /* TB1��Charging time setting */
        TB1CCTL1 = 0;
        TB1CTL = TBCLR|TBSSEL__ACLK|MC__CONTINUOUS;

        /* Discharge */
        _DINT();
        P2OUT &= ~BIT2;
        preTimePoint = TB1R;
        _EINT();
    }
    }

    TskExit();
}

void VTask_Probe(void)
{
    /* Close the comparator and timer */
    CP1CTL0 = 0;
    CP1CTL1 = 0;
    TB1CTL = 0;
    TB1CCTL0 = 0;
    TB1CCR0 = 0;
    PMMCTL2 = 0;

    /* Supply voltage */
    dropDuration = dropDuration-preTimePoint;
    if(dropDuration<2000)
        V_vp = voltage[dropDuration];

    if(Setup_senseCount>0)
    {
        TskSetReady(VTASK_ACTIVATE);

        /* Calibration */
        op1 = op0*Outburst_Value_Shadow;
        op2 = V_vp*8;
        op3 = op1/op2;
        Outburst_Value = op3+0.4;

        if((V_vp > 1.8)
           && (SS_exceptionFlag == 1 || SS_stopFlag == 1))
            TskSetReady(SSTASK_ACTIVATE);
    }
    else
        V_stopFlag = 1;


    TskExit();
}


#pragma vector = TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void)
{
    switch(__even_in_range(TB1IV, TBIV_14))
    {
    case TBIV__TBCCR1:
    {
        TskSetReady(VTASK_ACTIVATE);
        __low_power_mode_off_on_exit();
    }
    }
}


#pragma vector = ECOMP0_ECOMP1_VECTOR
__interrupt void ECOMP0_ECOMP1_ISR(void)
{
    dropDuration = TB1R;
    switch (__even_in_range(CP1IV,4))
    {
    case CPIV__CPIIFG:
    {
        TskSetReady(VTASK_PROBE);
        __low_power_mode_off_on_exit();
    }
    }
}
