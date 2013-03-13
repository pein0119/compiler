
#ifndef MICRO
#define MICRO

//宏定义
#define AND         1 /// and
#define ARRAY       2 /// array
#define BEGIN       3 /// begin
#define CASE        4 // case
#define CONST       5 // const
#define DIV         6 // div
#define DO          7 // do
#define DOWNTO      8 // downto
#define ELSE        9 // else
#define END         10                  // end
#define FILES       11                  // file
#define FOR         12                  // for
#define FUNCTION    13                  // function
#define GOTO        14                  // goto
#define IF          15                  // if
#define IN          16                  // in
#define LABEL       17                  // label
#define MOD         18                  // mod
#define NIL         19                  // nil
#define NOT         20                  // not
#define OF          21                  // of
#define OR          22                  // or
#define PACKED      23                  // packed
#define PROCEDURE   24                  // procedure
#define PROGRAM     25                  // prgram
#define RECORD      26                  // record
#define REPEAT      27                  // repeat
#define SET         28                  // set
#define THEN        29                  // then
#define TO          30                  // to
#define TYPE        31                  // type
#define UNTIL       32                  // until
#define VAR         33                  // var
#define WHILE       34                  // while
#define WHITH       35                  // whith
#define ID          36                  // 标识符
#define INT         37                  // 整常数
#define REAL        38                  // 实常数
#define STRING      39                  // 字符串
#define PLUS        40                  // +
#define MINUS       41                  // -
#define MULTI       42                  // *
#define RDIV        43                  // /
#define EQ          44                  // =
#define LT          45                  // <
#define GT          46                  // >
#define LE          47                  // <=
#define GE          48                  // >=
#define NE          49                  // <>
#define LR_BRAC     50                  // (
#define RR_BRAC     51                  // )
#define COMMA       52                  // ,
#define P_MARK      53                  // 、
#define F_STOP      54                  // .
#define RANGE       55                  // ..
#define COLON       56                  // :
#define ASSIGN      57                  // :=
#define SEMIC       58                  // ;
#define CAP         59                  // ^
#define EXP         60                  // **
#define LS_BRAC     61                  // [
#define RS_BRAC     62                  // ]
#define Q_MARK      63                  // '

// 定义空白字符
#define TAB         '\t'
#define NEWLINE     '\n'
#define SPACE       ' '

// 定义错误号
int error;

#define file_exist_error       1         // 没有输入文件
#define illegal_ch_error       2         // 存在非法字符
#endif