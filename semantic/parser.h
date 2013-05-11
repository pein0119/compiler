#ifndef _PARSER_H
#define _PARSER_H

/**
 * 将编译平台生成的LR(1)文法表的动作表列映射为相应的数字
 *prog      0
 *id        1
 *semi      2
 *,         3
 *var       4
 *:         5
 *integer   6
 *if        7
 *then      8
 *else      9
 *assignop 10
 *addop    11
 *subop    12
 *mulop    13
 *divop    14
 *gtop     15
 *lsop     16
 *num      17
 *begin    18
 *end      19
 *readln   20
 *writeln  21
 *(        22
 *)        23
 *real     24
 *while    25
 *do       26
 *$        27
 *
*/

/**
 * 将LR(1)文法表的转移表列映射为相应的数字
 *
 *program            0
 *identifier_list    1
 *declarations       2
 *declaration        3
 *variable           4
 *expression         5
 *type               6
 *statement          7
 *simple_expression  8
 *term               9
 *factor            10
 *procedure         11
 *statement_list    12
 */


typedef struct
{
    char wh;                            // 表示当前要做什么，‘s’表示要转移，'r'要规约
    int  stat;                          // 表示下一个位置
}Action;

Action acChart[100][100];                    // 动作表
int gtChart[100][100];                    // 转移表


typedef struct
{
    int PL;                        // 存储产生式的左部
    char Str[100];                      // 存储产生式
    int Length;                         //存储产生式子右部的元素的个数
}Pro;

Pro produce[100];                  // 存储产生式

// 最多能接收10000个字符的串
Ele w[10000];                  // 将输入表的类型改为Ele

void init_Pro(Pro* produce)
{
    // h1
    produce[1].PL = 0;                  // program
    strcpy(produce[1].Str, "program => prog id semi declarations begin procedure statement_list  procedure end");
    produce[1].Length = 9;

    // h2
    produce[2].PL = 1;                  // identifier_list
    strcpy(produce[2].Str, "identifier_list => id");
    produce[2].Length = 1;

    // h3
    produce[3].PL = 1;                  // identifier_list
    strcpy(produce[3].Str, "identifier_list => identifier_list , id");
    produce[3].Length = 3;

    // h4
    produce[4].PL = 2;                  // declarations
    strcpy(produce[4].Str, "declarations => var declaration semi");
    produce[4].Length = 3;

	//h5
	produce[5].PL = 3;                  //declaration
    strcpy(produce[5].Str, "declaration => identifier_list : type");
    produce[5].Length = 3;

   // h6
    produce[6].PL = 4;                          // variable
    strcpy(produce[6].Str, "variable => id");
    produce[6].Length = 1;

    // h7
	
    produce[7].PL = 5;                  // expression
    strcpy(produce[7].Str, "expression => simple_expression");
    produce[7].Length = 1;

    // h8
    produce[8].PL = 5;                  // expression
    strcpy(produce[8].Str, "expression => simple_expression gtop simple_expression");
    produce[8].Length = 3;

    // h9
	
    produce[9].PL = 5;                  // expression
    strcpy(produce[9].Str, "expression => simple_expression lsop simple_expression");
    produce[9].Length = 3;

    // h10
    produce[10].PL = 6;                 // type
    strcpy(produce[10].Str, "type => integer");
    produce[10].Length = 1;

    // h11
    produce[11].PL = 6;                 // type
    strcpy(produce[11].Str, "type => real");
    produce[11].Length = 1;

    // h12
    produce[12].PL = 7;                 // statement
    strcpy(produce[12].Str, "statement => variable assignop expression semi");
    produce[12].Length = 4;

    // h13
    produce[13].PL = 7;                 // statement
    strcpy(produce[13].Str, "statement => if expression then statement else statement");
    produce[13].Length = 6;

    // h14
    produce[14].PL = 7;                 // statement
    strcpy(produce[14].Str, "statement =>  while expression do statement");
    produce[14].Length = 4;

    // h15
    produce[15].PL = 8;                 // simple_expression
    strcpy(produce[15].Str, "simple_expression => term");
    produce[15].Length = 1;

    // h16
    produce[16].PL = 8;                 // simple_expression
    strcpy(produce[16].Str, "simple_expression => simple_expression addop term");
    produce[16].Length = 3;

    // h17
    produce[17].PL = 8;                 // simple_expression
    strcpy(produce[17].Str, "simple_expression => simple_expression subop term");
    produce[17].Length = 3;

    // h18
    produce[18].PL = 9;                 // term
    strcpy(produce[18].Str, "term => factor");
    produce[18].Length = 1;

    // h19
    produce[19].PL = 9;                 // term
    strcpy(produce[19].Str, "term => term mulop factor");
    produce[19].Length = 3;

    // h20
    produce[20].PL = 9;                 // term
    strcpy(produce[20].Str, "term => term divop factor");
    produce[20].Length = 3;

    // h21
    produce[21].PL = 10;                // factor
    strcpy(produce[21].Str, "factor => id");
    produce[21].Length = 1;

    // h22
    produce[22].PL = 10;                // factor
    strcpy(produce[22].Str, "factor => num");
    produce[22].Length = 1;

    // h23
    produce[23].PL = 11;                // procedure
    strcpy(produce[23].Str, " procedure => readln ( expression ) semi");
    produce[23].Length = 5;

    // h24
    produce[24].PL = 11;                // procedure
    strcpy(produce[24].Str, "procedure => writeln ( expression ) semi");
    produce[24].Length = 5;

    // h25
    produce[25].PL = 12;                // statement_list
    strcpy(produce[25].Str, "statement_list => statement statement_list ");
    produce[25].Length = 2;

    // h26
    produce[26].PL = 12;
    strcpy(produce[26].Str, "statement_list => statement");
    produce[26].Length = 1;
}

/**
 * 初始化语法分析器的输入串
 *
 */

void init_w(Ele* w)
{
	//prog id semi
	w[0].type = 0; w[1].type = 1; w[2].type = 2;
    strcpy(w[0].name, "program"); strcpy(w[1].name, "first"); strcpy(w[2].name, ";");

	//var
	w[3].type = 4;
    strcpy(w[3].name, "var");

	//id , id : integer semi
	w[4].type = 1; w[5].type = 3; w[6].type = 1; w[7].type = 5; w[8].type = 6; w[9].type = 2;
    strcpy(w[4].name, "x"); strcpy(w[5].name,",");
    strcpy(w[6].name, "y"); strcpy(w[7].name, ":"); strcpy(w[8].name, "integer");
    strcpy(w[9].name, ";");

	//begin
	w[10].type = 18;
    strcpy(w[10].name, "begin");

	//readln (id) semi
	w[11].type = 20; w[12].type = 22; w[13].type = 1; w[14].type = 23; w[15].type = 2;
    strcpy(w[11].name, "readln");
    strcpy(w[12].name, "(");
    strcpy(w[13].name, "x");
    strcpy(w[14].name, ")");
	strcpy(w[15].name, ";");

	//id assignop num semi
	 w[16].type = 1;  w[17].type = 10; w[18].type = 17; w[19].type = 2;
	 strcpy(w[16].name,"x"); strcpy(w[17].name, ":="); strcpy(w[18].name, "5"); strcpy(w[19].name, ";");

	//if id gtop num then id assignop id subop id semi
	w[20].type = 7; w[21].type = 1; w[22].type = 15; w[23].type = 17; w[24].type = 8;
	w[25].type = 1; w[26].type = 10; w[27].type = 1; w[28].type = 12; w[29].type = 1; w[30].type =2;
	strcpy(w[20].name, "if"); strcpy(w[21].name, "x"); strcpy(w[22].name, ">"); strcpy(w[23].name, "0"); 
	strcpy(w[24].name, "then"); strcpy(w[25].name, "y" ); strcpy(w[26].name, ":="); strcpy(w[27].name, "y");
	strcpy(w[28].name, "-"); strcpy(w[29].name, "x"); strcpy(w[30].name, ";"); 

	//else id assignop id addop id semi 
 	w[31].type = 9; w[32].type = 1; w[33].type = 10; w[34].type = 1; w[35].type = 11; w[36].type = 1; w[37].type = 2;
	strcpy(w[31].name, "else"); strcpy(w[32].name, "y"); strcpy(w[33].name, ":="); strcpy(w[34].name, "x");
	strcpy(w[35].name, "+");    strcpy(w[36].name, "y"); strcpy(w[37].name, ";");

	//while id lsop num
	w[38].type = 25; w[39].type = 1; w[40].type = 16; w[41].type = 17;
	strcpy(w[38].name, "while"); strcpy(w[39].name, "x"); strcpy(w[40].name, "<"); strcpy(w[41].name, "10");

	//do id assignop num semi
	w[42].type = 26; w[43].type = 1; w[44].type = 10; w[45].type = 17; w[46].type = 2;
	strcpy(w[42].name, "do"); strcpy(w[43].name, "x"); strcpy(w[44].name, ":="); strcpy(w[45].name, "11"); strcpy(w[46].name, ";");

	//writeln (id) semi
	w[47].type = 21; w[48].type = 22; w[49].type = 1;  w[50].type = 23; w[51].type = 2;
	strcpy(w[47].name, "writeln"); strcpy(w[48].name, "("); strcpy(w[49].name, "y"); strcpy(w[50].name,")"); 
	strcpy(w[51].name, ";");

	//end $
	w[52].type = 19; w[53].type = 27;
	strcpy(w[52].name, "end");
}

	// FILE* in;
	// in = fopen("key.txt","r");}
// 初始化我们的动作表
void init_acChart(Action (*acChart)[100])
{
	//h0
	acChart[0][0].wh = 's';
	acChart[0][0].stat = 2;

	//h1
	acChart[1][27].wh = 'a';

    //h2
	acChart[2][1].wh = 's';
    acChart[2][1].stat = 3;

    //h3
	acChart[3][2].wh = 's';
    acChart[3][2].stat = 4;

	//h4
	acChart[4][4].wh = 's';
	acChart[4][4].stat = 6;

	//h5
	acChart[5][18].wh = 's';
	acChart[5][18].stat = 7;

	//h6
	acChart[6][1].wh = 's';
	acChart[6][1].stat = 10;

	//h7
	acChart[7][20].wh = 's';
	acChart[7][20].stat = 12;

	acChart[7][21].wh = 's';
	acChart[7][21].stat = 13;

	//h8
	acChart[8][3].wh = 's';
	acChart[8][3].stat = 14;

	acChart[8][5].wh = 's';
	acChart[8][5].stat = 15;

	//h9
	acChart[9][2].wh = 's';
	acChart[9][2].stat = 16;

	//h10
	acChart[10][3].wh = 'r';
    acChart[10][3].stat = 2;

	acChart[10][5].wh = 'r';
	acChart[10][5].stat = 2;

	//h11
	acChart[11][1].wh = 's';
	acChart[11][1].stat = 20;

	acChart[11][7].wh = 's';
	acChart[11][7].stat = 21;

	acChart[11][25].wh = 's';
	acChart[11][25].stat = 22;

	//h12
	acChart[12][22].wh = 's';
	acChart[12][22].stat = 23;

	//h13
	acChart[13][22].wh = 's';
	acChart[13][22].stat = 24;

	//h14
	acChart[14][1].wh = 's';
	acChart[14][1].stat = 25;

	//h15
	acChart[15][6].wh = 's';
	acChart[15][6].stat = 27;

	acChart[15][24].wh = 's';
	acChart[15][24].stat = 28;

	//h16
	acChart[16][18].wh = 'r';
	acChart[16][18].stat = 4;

	//h17
	acChart[17][10].wh = 's';
	acChart[17][10].stat = 29;

	//h18
	acChart[18][1].wh = 's';
	acChart[18][1].stat = 20;

	acChart[18][7].wh = 's';
	acChart[18][7].stat = 21;

	acChart[18][20].wh = 'r';
	acChart[18][20].stat = 26;

	acChart[18][21].wh = 'r';
	acChart[18][21].stat = 26;

	acChart[18][25].wh = 's';
	acChart[18][25].stat = 22;

	//h19
	acChart[19][20].wh = 's';
	acChart[19][20].stat = 12;

	acChart[19][21].wh = 's';
	acChart[19][21].stat = 13;

	//h20
	acChart[20][10].wh = 'r';
	acChart[20][10].stat = 6;

	//h21
	acChart[21][1].wh = 's';
	acChart[21][1].stat = 36;

	acChart[21][17].wh = 's';
	acChart[21][17].stat = 37;

	//h22
	acChart[22][1].wh = 's';
	acChart[22][1].stat = 36;

	acChart[22][17].wh = 's';
	acChart[22][17].stat = 37;

	//h23
	acChart[23][1].wh = 's';
	acChart[23][1].stat = 39;

	//h24
	acChart[24][1].wh = 's';
	acChart[24][1].stat = 36;

	acChart[24][17].wh = 's';
	acChart[24][17].stat = 37;

	//h25
	acChart[25][3].wh = 'r';
	acChart[25][3].stat = 3;

	acChart[25][5].wh = 'r';
	acChart[25][5].stat = 3;

	//h26
	acChart[26][2].wh = 'r';
	acChart[26][2].stat = 5;

	//h27
	acChart[27][2].wh = 'r';
	acChart[27][2].stat = 10;

	//h28
	acChart[28][2].wh = 'r';
	acChart[28][2].stat = 11;

	//h29
	acChart[29][1].wh = 's';
	acChart[29][1].stat = 36;

	acChart[29][17].wh = 's';
	acChart[29][17].stat = 37;

	//h30
	acChart[30][20].wh = 'r';
	acChart[30][20].stat = 25;

	acChart[30][21].wh = 'r';
	acChart[30][21].stat = 25;

	//31
	acChart[31][19].wh = 's';
	acChart[31][19].stat = 42;

	//h32
	acChart[32][8].wh = 's';
	acChart[32][8].stat = 43;

	//h33
	acChart[33][2].wh = 'r';
	acChart[33][2].stat = 7;

	acChart[33][8].wh = 'r';
	acChart[33][8].stat = 7;

	acChart[33][11].wh = 's';
	acChart[33][11].stat = 44;

	acChart[33][12].wh = 's';
	acChart[33][12].stat = 45;

	acChart[33][15].wh = 's';
	acChart[33][15].stat = 46;

	acChart[33][16].wh = 's';
	acChart[33][16].stat = 47;

	acChart[33][23].wh = 'r';
	acChart[33][23].stat = 7;

	acChart[33][26].wh = 'r';
	acChart[33][26].stat = 7;

	//h34
	acChart[34][2].wh = 'r';
	acChart[34][2].stat = 15;

	acChart[34][8].wh = 'r';
	acChart[34][8].stat = 15;

	acChart[34][11].wh = 'r';
	acChart[34][11].stat = 15;

	acChart[34][12].wh = 'r';
	acChart[34][12].stat = 15;

	acChart[34][13].wh = 's';
	acChart[34][13].stat = 48;

	acChart[34][14].wh = 's';
	acChart[34][14].stat = 49;

	acChart[34][15].wh = 'r';
	acChart[34][15].stat = 15;

	acChart[34][16].wh = 'r';
	acChart[34][16].stat = 15;

	acChart[34][23].wh = 'r';
	acChart[34][23].stat = 15;

	acChart[34][26].wh = 'r';
	acChart[34][26].stat = 15;

	//h35
	acChart[35][2].wh = 'r';
	acChart[35][2].stat = 18;

	acChart[35][8].wh = 'r';
	acChart[35][8].stat = 18;

	acChart[35][11].wh = 'r';
	acChart[35][11].stat = 18;

	acChart[35][12].wh = 'r';
	acChart[35][12].stat = 18;

	acChart[35][13].wh = 'r';
	acChart[35][13].stat = 18;

	acChart[35][14].wh = 'r';
	acChart[35][14].stat = 18;

	acChart[35][15].wh = 'r';
	acChart[35][15].stat = 18;

	acChart[35][16].wh = 'r';
	acChart[35][16].stat = 18;

	acChart[35][23].wh = 'r';
	acChart[35][23].stat = 18;

	acChart[35][26].wh = 'r';
	acChart[35][26].stat = 18;

	//36
	acChart[36][2].wh = 'r';
	acChart[36][2].stat = 21;

	acChart[36][8].wh = 'r';
	acChart[36][8].stat =21;

	acChart[36][11].wh = 'r';
	acChart[36][11].stat = 21;

	acChart[36][12].wh = 'r';
	acChart[36][12].stat = 21;

	acChart[36][13].wh = 'r';
	acChart[36][13].stat = 21;

	acChart[36][14].wh = 'r';
	acChart[36][14].stat = 21;

	acChart[36][15].wh = 'r';
	acChart[36][15].stat = 21;

	acChart[36][16].wh = 'r';
	acChart[36][16].stat = 21;

	acChart[36][23].wh = 'r';
	acChart[36][23].stat = 21;

	acChart[36][26].wh = 'r';
	acChart[36][26].stat = 21;

	//h37
	acChart[37][2].wh = 'r';
	acChart[37][2].stat = 22;

	acChart[37][8].wh = 'r';
	acChart[37][8].stat = 22;

	acChart[37][11].wh = 'r';
	acChart[37][11].stat = 22;

	acChart[37][12].wh = 'r';
	acChart[37][12].stat = 22;

	acChart[37][13].wh = 'r';
	acChart[37][13].stat = 22;

	acChart[37][13].wh = 'r';
	acChart[37][13].stat = 22;

	acChart[37][14].wh = 'r';
	acChart[37][14].stat = 22;

	acChart[37][15].wh = 'r';
	acChart[37][15].stat = 22;

	acChart[37][16].wh = 'r';
	acChart[37][16].stat = 22;

	acChart[37][23].wh = 'r';
	acChart[37][23].stat = 22;

	acChart[37][26].wh = 'r';
	acChart[37][26].stat = 22;

	//h38
	acChart[38][26].wh = 's';
	acChart[38][26].stat = 50;

	//h39
	acChart[39][23].wh = 's';
	acChart[39][23].stat = 51;

	//h40
	acChart[40][23].wh = 's';
	acChart[40][23].stat = 52;

	//h41
	acChart[41][2].wh = 's';
	acChart[41][2].stat = 53;

	//h42
	acChart[42][27].wh = 'r';
	acChart[42][27].stat = 1;

	//h43
	acChart[43][1].wh = 's';
	acChart[43][1].stat = 20;

	acChart[43][7].wh = 's';
	acChart[43][7].stat = 21;

	acChart[43][25].wh = 's';
	acChart[43][25].stat = 22;

	//h44
	acChart[44][1].wh = 's';
	acChart[44][1].stat = 36;

	acChart[44][17].wh = 's';
	acChart[44][17].stat = 37;

	//h45
	acChart[45][1].wh = 's';
	acChart[45][1].stat = 36;

	acChart[45][17].wh = 's';
	acChart[45][17].stat = 37;

	//h46
	acChart[46][1].wh = 's';
	acChart[46][1].stat = 36;

	acChart[46][17].wh = 's';
	acChart[46][17].stat = 37;

	//h47
	acChart[47][1].wh = 's';
	acChart[47][1].stat = 36;

	acChart[47][17].wh = 's';
	acChart[47][17].stat = 37;

	//h48
	acChart[48][1].wh = 's';
	acChart[48][1].stat = 36;

	acChart[48][17].wh = 's';
	acChart[48][17].stat = 37;

	//h49
	acChart[49][1].wh = 's';
	acChart[49][1].stat = 36;

	acChart[49][17].wh = 's';
	acChart[49][17].stat = 37;

	//h50
	acChart[50][1].wh = 's';
	acChart[50][1].stat = 20;

	acChart[50][7].wh = 's';
	acChart[50][7].stat = 21;

	acChart[50][25].wh = 's';
	acChart[50][25].stat = 22;

	//h51
	acChart[51][2].wh = 's';
	acChart[51][2].stat = 62;

	//h52
	acChart[52][2].wh = 's';
	acChart[52][2].stat = 63;

	//h53
	acChart[53][1].wh = 'r';
	acChart[53][1].stat = 12;

	acChart[53][7].wh = 'r';
	acChart[53][7].stat = 12;

	acChart[53][9].wh = 'r';
	acChart[53][9].stat = 12;

	acChart[53][7].wh = 'r';
	acChart[53][7].stat = 12;

	acChart[53][20].wh = 'r';
	acChart[53][20].stat = 12;

	acChart[53][21].wh = 'r';
	acChart[53][21].stat = 12;

	acChart[53][25].wh = 'r';
	acChart[53][25].stat = 12;

	//h54
	acChart[54][9].wh = 's';
	acChart[54][9].stat = 64;

	//h55
	acChart[55][2].wh = 'r';
	acChart[55][2].stat = 16;

	acChart[55][8].wh = 'r';
	acChart[55][8].stat = 16;

	acChart[55][11].wh = 'r';
	acChart[55][11].stat = 16;

	acChart[55][12].wh = 'r';
	acChart[55][12].stat = 16;

	acChart[55][13].wh = 's';
	acChart[55][13].stat = 48;

	acChart[55][14].wh = 's';
	acChart[55][14].stat = 49;

	acChart[55][15].wh = 'r';
	acChart[55][15].stat = 16;

	acChart[55][16].wh = 'r';
	acChart[55][16].stat = 16;

	acChart[55][23].wh = 'r';
	acChart[55][23].stat = 16;

	acChart[55][26].wh = 'r';
	acChart[55][26].stat = 16;

	//h56
	acChart[56][2].wh = 'r';
	acChart[56][2].stat = 17;

	acChart[56][8].wh = 'r';
	acChart[56][8].stat = 17;

	acChart[56][11].wh = 'r';
	acChart[56][11].stat = 17;

	acChart[56][12].wh = 'r';
	acChart[56][12].stat = 17;

	acChart[56][13].wh = 's';
	acChart[56][13].stat = 48;

	acChart[56][14].wh = 's';
	acChart[56][14].stat = 49;

	acChart[56][15].wh = 'r';
	acChart[56][15].stat = 17;

	acChart[56][16].wh = 'r';
	acChart[56][16].stat = 17;

	acChart[56][23].wh = 'r';
	acChart[56][23].stat = 17;

	acChart[56][26].wh = 'r';
	acChart[56][26].stat = 17;

	//h57
	acChart[57][2].wh = 'r';
	acChart[57][2].stat = 8;

	acChart[57][8].wh = 'r';
	acChart[57][8].stat = 8;

	acChart[57][11].wh = 's';
	acChart[57][11].stat = 44;

	acChart[57][12].wh = 's';
	acChart[57][12].stat = 45;

	acChart[57][23].wh = 'r';
	acChart[57][23].stat = 8;

	acChart[57][26].wh = 'r';
	acChart[57][26].stat = 8;

	//h58
	acChart[58][2].wh = 'r';
	acChart[58][2].stat = 9;

	acChart[58][8].wh = 'r';
	acChart[58][8].stat = 9;

	acChart[58][11].wh = 's';
	acChart[58][11].stat = 44;

	acChart[58][12].wh = 's';
	acChart[58][12].stat = 45;

	acChart[58][23].wh = 'r';
	acChart[58][23].stat = 9;

	acChart[58][26].wh = 'r';
	acChart[58][26].stat = 9;

	//h59
	acChart[59][2].wh = 'r';
	acChart[59][2].stat = 19;

	acChart[59][8].wh = 'r';
	acChart[59][8].stat = 19;

	acChart[59][11].wh = 'r';
	acChart[59][11].stat = 19;

	acChart[59][12].wh = 'r';
	acChart[59][12].stat = 19;

	acChart[59][13].wh = 'r';
	acChart[59][13].stat = 19;

	acChart[59][14].wh = 'r';
	acChart[59][14].stat = 19;

	acChart[59][15].wh = 'r';
	acChart[59][15].stat = 19;

	acChart[59][16].wh = 'r';
	acChart[59][16].stat = 19;

	acChart[59][23].wh = 'r';
	acChart[59][23].stat = 19;

	acChart[59][26].wh = 'r';
	acChart[59][26].stat = 19;

	//60
	acChart[60][2].wh = 'r';
	acChart[60][2].stat = 20;

	acChart[60][8].wh = 'r';
	acChart[60][8].stat = 20;

	acChart[60][11].wh = 'r';
	acChart[60][11].stat = 20;

	acChart[60][12].wh = 'r';
	acChart[60][12].stat = 20;

	acChart[60][13].wh = 'r';
	acChart[60][13].stat = 20;

	acChart[60][14].wh = 'r';
	acChart[60][14].stat = 20;

	acChart[60][15].wh = 'r';
	acChart[60][15].stat = 20;

	acChart[60][16].wh = 'r';
	acChart[60][16].stat = 20;

	acChart[60][23].wh = 'r';
	acChart[60][23].stat = 20;

	acChart[60][26].wh = 'r';
	acChart[60][26].stat = 20;

	//h61
	acChart[61][1].wh = 'r';
	acChart[61][1].stat = 14;

	acChart[61][7].wh = 'r';
	acChart[61][7].stat = 14;

	acChart[61][9].wh = 'r';
	acChart[61][9].stat = 14;

	acChart[61][20].wh = 'r';
	acChart[61][20].stat = 14;

	acChart[61][21].wh = 'r';
	acChart[61][21].stat = 14;

	acChart[61][25].wh = 'r';
	acChart[61][25].stat = 14;

	//h62
	acChart[62][1].wh = 'r';
	acChart[62][1].stat = 23;

	acChart[62][7].wh = 'r';
	acChart[62][7].stat = 23;

	acChart[62][19].wh = 'r';
	acChart[62][19].stat = 23;

	acChart[62][25].wh = 'r';
	acChart[62][25].stat = 23;

	//63
	acChart[63][1].wh = 'r';
	acChart[63][1].stat = 24;

	acChart[63][7].wh = 'r';
	acChart[63][7].stat = 24;

	acChart[63][19].wh = 'r';
	acChart[63][19].stat = 24;

	acChart[63][25].wh = 'r';
	acChart[63][25].stat = 24;

	//h64
	acChart[64][1].wh = 's';
  	acChart[64][1].stat = 20;

	acChart[64][7].wh = 's';
  	acChart[64][7].stat = 21;

	acChart[64][25].wh = 's';
  	acChart[64][25].stat = 22;

	//65
	acChart[65][1].wh = 'r';
	acChart[65][1].stat = 13;

	acChart[65][7].wh = 'r';
	acChart[65][7].stat = 13;

	acChart[65][9].wh = 'r';
	acChart[65][9].stat = 13;

	acChart[65][20].wh = 'r';
	acChart[65][20].stat = 13;

	acChart[65][21].wh = 'r';
	acChart[65][21].stat = 13;

	acChart[65][25].wh = 'r';
	acChart[65][25].stat = 13;
}

void init_gtChart(int (*gtChart)[100])
{
	/* h0 */
	gtChart[0][0] = 1;

	/* h1 */

	/* h2 */

	/* h3 */

	/* h4 */
	gtChart[4][2] = 5;

	/* h5 */

	/* h6 */
	gtChart[6][1] = 8;
	gtChart[6][3] = 9;

	/* h7 */
	gtChart[7][11] = 11;

	/* h8 */

	/* h9 */

	/* h10 */

	/* h11 */
	gtChart[11][4] = 17;
	gtChart[11][7] = 18;
	gtChart[11][12] = 19;

	/* h12 */

	/* h13 */

	/* h14 */

	/* h15 */
	gtChart[15][6] = 26;

	/* h16 */

	/* h17 */

	/* h18 */
	gtChart[18][4] =17;
	gtChart[18][7] = 18;
	gtChart[18][12] = 30;

	/* h19 */
	gtChart[19][11] = 31;

	/* h20 */

	/* h21 */
	gtChart[21][5] = 32;
	gtChart[21][8] = 33;
	gtChart[21][9] = 34;
	gtChart[21][10] = 35;

	/* h22 */
	gtChart[22][5] = 38;
	gtChart[22][8] = 33;
	gtChart[22][9] = 34;
	gtChart[22][10] = 35;

	/* h23 */

	/* h24 */
	gtChart[24][5] = 40;
	gtChart[24][8] = 33;
	gtChart[24][9] = 34;
	gtChart[24][10] = 35;

	/* h25 */

	/* h26 */

	/* h27 */

	/* h28 */

	/* h29 */
	gtChart[29][5] = 41;
	gtChart[29][8] = 33;
	gtChart[29][9] = 34;
	gtChart[29][10] = 35;

	/* 30 */

	/* 31 */

	/* 32 */

	/* 33 */

	/* 34 */

	/* 35 */

	/* 36 */

	/* 37 */

	/* 38 */

	/* 39 */

	/* 40 */

	/* 41 */

	/* 42 */

	/* 43 */
	gtChart[43][4] = 17;
	gtChart[43][7] = 54;

	/* h44 */
	gtChart[44][9] = 55;
	gtChart[44][10] = 35;

	/* h45 */
	gtChart[45][9] = 56;
	gtChart[45][10] = 35;

	/* h46 */
	gtChart[46][8] = 57;
	gtChart[46][9] = 34;
	gtChart[46][10] = 35;

	/* h47 */
	gtChart[47][8] = 58;
	gtChart[47][9] = 34;
	gtChart[47][10] = 35;

	/* h48 */
	gtChart[48][10] = 59;

	/* h49 */
	gtChart[49][10] = 60;

	/* h50 */
	gtChart[50][4] = 17;
	gtChart[50][7] = 61;

	/* h51 */

	/* h52 */

	/* h53 */

	/* h54 */

	/* h55 */

	/* h56 */

	/* h57 */

	/* h58 */

	/* h59 */

	/* h60 */

	/* h61 */

	/* h62 */

	/* h63 */

	/* h64 */
	gtChart[64][4] = 17;
	gtChart[64][7] = 65;

	/* h65 */

}
#endif
