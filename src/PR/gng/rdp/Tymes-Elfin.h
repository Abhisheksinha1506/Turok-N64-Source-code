typedef struct {
  int sl;
  int sh;
  int tl;
  int th;
} TexDesc;

typedef struct {
  int charmin;
  int charmax;
  int nchars;
  TexDesc *chars;
} TexFont;

TexDesc MyDesc[] = {
   {   0,   0,   0,   0 }, /* index 0 */
   {  75,  79,  66,  78 }, /* index 1 */
   {   3,   9, 119, 125 }, /* index 2 */
   {  81,  91,  66,  78 }, /* index 3 */
   { 116, 125,   3,  17 }, /* index 4 */
   {  93, 105,  66,  78 }, /* index 5 */
   { 107, 119,  66,  78 }, /* index 6 */
   {  18,  23, 119, 125 }, /* index 7 */
   {  21,  27,  21,  35 }, /* index 8 */
   {  29,  35,  21,  35 }, /* index 9 */
   {  90,  98, 108, 116 }, /* index 10 */
   {  52,  61,  94, 104 }, /* index 11 */
   {  36,  41, 119, 124 }, /* index 12 */
   {  49,  55, 119, 122 }, /* index 13 */
   {  43,  47, 119, 123 }, /* index 14 */
   {   3,  10,  37,  50 }, /* index 15 */
   {   3,  11,  80,  92 }, /* index 16 */
   {  13,  20,  80,  92 }, /* index 17 */
   {  22,  31,  80,  92 }, /* index 18 */
   {  53,  61,  66,  78 }, /* index 19 */
   { 112, 121,  52,  64 }, /* index 20 */
   {   3,  11,  66,  78 }, /* index 21 */
   {  13,  21,  66,  78 }, /* index 22 */
   {  23,  31,  66,  78 }, /* index 23 */
   {  33,  41,  66,  78 }, /* index 24 */
   {  43,  51,  66,  78 }, /* index 25 */
   {  13,  18, 108, 117 }, /* index 26 */
   {  63,  68,  94, 104 }, /* index 27 */
   {  81,  90,  94, 104 }, /* index 28 */
   { 111, 120, 108, 114 }, /* index 29 */
   {  92, 102,  94, 104 }, /* index 30 */
   { 101, 108,  80,  92 }, /* index 31 */
   {  67,  81,   3,  17 }, /* index 32 */
   {  72,  85,  80,  92 }, /* index 33 */
   {  33,  43,  80,  92 }, /* index 34 */
   {  45,  57,  80,  92 }, /* index 35 */
   { 110, 122,  80,  92 }, /* index 36 */
   {  59,  70,  80,  92 }, /* index 37 */
   {  47,  57,  21,  34 }, /* index 38 */
   {  87,  99,  80,  92 }, /* index 39 */
   {   3,  15,  94, 106 }, /* index 40 */
   {  66,  72,  37,  49 }, /* index 41 */
   {  44,  51,  37,  49 }, /* index 42 */
   {  59,  71,  21,  34 }, /* index 43 */
   {  53,  64,  37,  49 }, /* index 44 */
   {  73,  87,  21,  34 }, /* index 45 */
   {  24,  36,  37,  49 }, /* index 46 */
   {  98, 110,  52,  64 }, /* index 47 */
   {  63,  73,  66,  78 }, /* index 48 */
   {  53,  65,   3,  17 }, /* index 49 */
   {  89, 100,  21,  34 }, /* index 50 */
   {  28,  37,  52,  64 }, /* index 51 */
   {  39,  51,  52,  64 }, /* index 52 */
   {  53,  64,  52,  64 }, /* index 53 */
   {  66,  78,  52,  64 }, /* index 54 */
   {  80,  96,  52,  64 }, /* index 55 */
   {  74,  86,  37,  49 }, /* index 56 */
   {  14,  26,  52,  64 }, /* index 57 */
   {  88,  99,  37,  49 }, /* index 58 */
   {  83,  89,   3,  17 }, /* index 59 */
   { 101, 110,  37,  49 }, /* index 60 */
   { 101, 107,   3,  17 }, /* index 61 */
   { 100, 109, 108, 116 }, /* index 62 */
   {  57,  67, 119, 122 }, /* index 63 */
   {  11,  16, 119, 125 }, /* index 64 */
   { 104, 112,  94, 104 }, /* index 65 */
   {  12,  22,  37,  50 }, /* index 66 */
   {  42,  51, 108, 117 }, /* index 67 */
   {  91,  99,   3,  17 }, /* index 68 */
   {  53,  62, 108, 117 }, /* index 69 */
   {  42,  51,   3,  17 }, /* index 70 */
   {   3,  12,  52,  64 }, /* index 71 */
   {  12,  21,   3,  18 }, /* index 72 */
   { 114, 119,  21,  34 }, /* index 73 */
   {   3,  10,   3,  19 }, /* index 74 */
   {  23,  33,   3,  17 }, /* index 75 */
   {  35,  40,   3,  17 }, /* index 76 */
   {  17,  29,  94, 105 }, /* index 77 */
   {  31,  41,  94, 105 }, /* index 78 */
   {   3,  11, 108, 117 }, /* index 79 */
   {  37,  45,  21,  35 }, /* index 80 */
   {   3,  12,  21,  35 }, /* index 81 */
   {  43,  50,  94, 105 }, /* index 82 */
   { 114, 121,  94, 103 }, /* index 83 */
   { 112, 119,  37,  49 }, /* index 84 */
   {  78,  88, 108, 117 }, /* index 85 */
   {  70,  79,  94, 104 }, /* index 86 */
   {  64,  76, 108, 117 }, /* index 87 */
   {  20,  29, 108, 117 }, /* index 88 */
   { 102, 112,  21,  34 }, /* index 89 */
   {  31,  40, 108, 117 }, /* index 90 */
   { 109, 114,   3,  17 }, /* index 91 */
   {  38,  42,  37,  49 }, /* index 92 */
   {  14,  19,  21,  35 }, /* index 93 */
   {  25,  34, 119, 124 }, /* index 94 */
   {   0,   0,   0,   0 }  /* index 95 */
};

TexFont MyFont = {
  32,
  127,
  96,
  MyDesc
};

