#include "levels.h"

//char CAVE01[CAVE01_ROW_SIZE][CAVE01_COL_SIZE+1] = {
//   //0123456789
//    "..........", // 0
//    "YYYYY.....", // 1
//    "....Y.....", // 2
//    "YYY.Y.....", // 3
//    "....Y.....", // 4
//    "YY.YYYYY.Y", // 5
//    "..V....Y..", // 6
//    "YYYY......", // 7
//    "YYYYYYYYYY", // 8
//    "YYYYYYYYYY", // 9
//};

//char CAVE01[CAVE01_ROW_SIZE][CAVE01_COL_SIZE+1] = {
//    //0123456789
//    ".....V....", // 0
//    "YYYYYY.Y..", // 1
//    "....YY.Y..", // 2
//    "YYY.YYYY..", // 3
//    "....Y.YY..", // 4
//    "YY.YYYYY.Y", // 5
//    "Y......Y..", // 6
//    "YYYY......", // 7
//    "YYYYYYYYYY", // 8
//    "YYYYYYYYYY", // 9
//};

char CAVE01[CAVE01_ROW_SIZE][CAVE01_COL_SIZE+1] = {
    ".X.......m",
    "...bGUAWLF",
    "....*|!?..",
    "....YDCQ..",
    "....`.....",
    ".CCCCCCCC.",
    "..........",
    "..V.......",
    "....V.....",
    ".........B",
};

// WALL shapes: '+' '-' '|' '/' '\'
char CAVE02[CAVE02_ROW_SIZE][CAVE02_COL_SIZE+1] = {
    ".X.............",
    ".......m..m....",
    "...------+..---",
    ".|...mm..|...$.",
    ".+-----+$|.....",
    "m.m...?|.|--+..",
    "m+----.|....|..",
    "!|.......|..|A.",
    "-+.+ ----+.....",
    "C..|.....X...U.",
    ".--+...........",
    ".........|.----",
    "....B...B|.W..X",
    "....`````+-----",
    "..D.D......LF..",
};

char CAVE03[CAVE03_ROW_SIZE][CAVE03_COL_SIZE+1] = {
    "X.|...|..m..m......X",
    "..|.|.|b|m.m........",
    "...b|.|.|.m...B.....",
    "..+-+...|...........",
    "..|!?+--+...........",
    "bb|CBD........``````",
    "--+--+-------+-----D",
    "X....|.......|..B.B.",
    "..m..|....A..|......",
    ".m.B.|.......+----- ",
    "..B m|.!...U...Q.m..",
    "--+-D|..............",
    "??|..|..C...Lm...m..",
    "?BD..|..m.*......B..",
    "--+..|.....m.......m",
    "CC|.B|...B....B.....",
    "CBD..|..*....F...W..",
    "--+m.|.....*....m...",
    "!!|.m|..............",
    "!BD.mD.bbb````````.X",
};
