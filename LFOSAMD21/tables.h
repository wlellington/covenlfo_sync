// NOTE: Several tables in this file assume a full 0-1023 DAC/PWM (10 bit) resolution, lop off the last two bits when using in TCC pwm outputs

// 256 point look up table to describe the curve e^(10*(x-1)) which creates a nice sharp rise to 1 when x approaches 1
// remapped to take max value of 1024 when index at 256 (creating upward exp rise when read linearly)
PROGMEM const unsigned char expRiseTable[256] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  5,
  6,
  6,
  6,
  6,
  7,
  7,
  7,
  7,
  8,
  8,
  8,
  9,
  9,
  9,
  10,
  10,
  10,
  11,
  11,
  12,
  12,
  13,
  13,
  14,
  14,
  15,
  15,
  16,
  17,
  17,
  18,
  19,
  19,
  20,
  21,
  22,
  23,
  24,
  25,
  26,
  27,
  28,
  29,
  30,
  31,
  32,
  34,
  35,
  36,
  38,
  39,
  41,
  42,
  44,
  46,
  48,
  50,
  52,
  54,
  56,
  58,
  60,
  63,
  65,
  68,
  71,
  73,
  76,
  79,
  82,
  86,
  89,
  93,
  96,
  100,
  104,
  108,
  113,
  117,
  122,
  127,
  132,
  137,
  142,
  148,
  154,
  160,
  167,
  173,
  180,
  187,
  195,
  203,
  211,
  219,
  228,
  237,
  246,
  255,
};


// *** this isnt currently in use, feel free to delete if need be *** //
// Lookup table for first 1/4 cycle of sine wave, to create full wave, flip and invert in each quadrant
// q1 read samples in order 0-255
// q2 read samples in reverse order 255-0
// q3 read samples in order 0-255 w/ sign inversion
// q4 read samples in reverse order 255-0 w/ sign inversion
PROGMEM const int sineTable[256] = {
  0,
  2,
  3,
  5,
  6,
  8,
  9,
  11,
  13,
  14,
  16,
  17,
  19,
  20,
  22,
  24,
  25,
  27,
  28,
  30,
  31,
  33,
  34,
  36,
  38,
  39,
  41,
  42,
  44,
  45,
  47,
  48,
  50,
  51,
  53,
  55,
  56,
  58,
  59,
  61,
  62,
  64,
  65,
  67,
  68,
  70,
  71,
  73,
  74,
  76,
  77,
  79,
  80,
  82,
  83,
  85,
  86,
  88,
  89,
  91,
  92,
  94,
  95,
  97,
  98,
  99,
  101,
  102,
  104,
  105,
  107,
  108,
  109,
  111,
  112,
  114,
  115,
  117,
  118,
  119,
  121,
  122,
  123,
  125,
  126,
  128,
  129,
  130,
  132,
  133,
  134,
  136,
  137,
  138,
  140,
  141,
  142,
  144,
  145,
  146,
  147,
  149,
  150,
  151,
  152,
  154,
  155,
  156,
  157,
  159,
  160,
  161,
  162,
  164,
  165,
  166,
  167,
  168,
  170,
  171,
  172,
  173,
  174,
  175,
  177,
  178,
  179,
  180,
  181,
  182,
  183,
  184,
  185,
  186,
  188,
  189,
  190,
  191,
  192,
  193,
  194,
  195,
  196,
  197,
  198,
  199,
  200,
  201,
  202,
  203,
  204,
  205,
  206,
  207,
  207,
  208,
  209,
  210,
  211,
  212,
  213,
  214,
  215,
  215,
  216,
  217,
  218,
  219,
  220,
  220,
  221,
  222,
  223,
  224,
  224,
  225,
  226,
  227,
  227,
  228,
  229,
  229,
  230,
  231,
  231,
  232,
  233,
  233,
  234,
  235,
  235,
  236,
  237,
  237,
  238,
  238,
  239,
  239,
  240,
  241,
  241,
  242,
  242,
  243,
  243,
  244,
  244,
  245,
  245,
  245,
  246,
  246,
  247,
  247,
  248,
  248,
  248,
  249,
  249,
  249,
  250,
  250,
  250,
  251,
  251,
  251,
  252,
  252,
  252,
  252,
  253,
  253,
  253,
  253,
  254,
  254,
  254,
  254,
  254,
  255,
  255,
  255,
  255,
  255,
  255,
  255,
  256,
  256,
  256,
  256,
  256,
  256,
  256,
  256,
  256,
  256
};