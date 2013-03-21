#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "micro.h"
#include "error.h"
#include "hash.h"
#include "stack.h"

keyword HashTable[HASH_LENGTH];         // 建立存储关键字的哈希表
keyword IdTable[ID_TABLE_LENGTH];       // 建立存储标识符的哈希表


inline
int check_ch(char ch)                   // 判定字符是否为非法字符
{
    if((ch >= 'A'&& ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
       (ch >= '0'&& ch <= '9') || (ch == '+') || (ch == '-')||
       ch == '*'|| ch =='/' || ch == '=' || ch == '>' || ch == '<'||
       ch == '(' || ch == ')' || ch == '[' || ch == ']'||
       ch == ':' || ch == '\'' || ch == '.' || ch == '^' || ch == ','||
       ch == '{' || ch == '}' || ch == TAB || ch == NEWLINE ||
       ch == SPACE || ch == '\0' || ch == ';' || ch == '!')
        return 1;
    return 0;
}


void toUp(char* token)                  // 转换为大写字母
{
    unsigned int length = strlen(token),i;

    for( i = 0;i != length; ++i)
        token[i] = toupper(token[i]);

}


// 输出关键字和标识符的函数
void print_word(char* token)
{
    // 首先判断是不是关键字
    int key;
    key = searchHash(token, HashTable);

    if( key != -1 )
    {
        // 是关键字
        toUp(token);                    // 将小写字母转换为大写字母
        printf("(%s,0)\n",token);
    }
    else                                // 不是关键字，是标识符
    {

        int key = searchHash(token,IdTable);
        if(key == -1)                   //判断该标识符是否已插入“标识符哈希表”
            key = createHash(token,IdTable); // 不在哈希表中

        printf("(ID,%d)\n",key);    // 输出该标识符在哈希表中的位置
    }
}


//输出各个进制的数字,目前只能支持十进制

void print_digit(char* token)
{
    printf("(INT,%s)\n",token);
}

// 输出字符串
inline
void print_str(char* token)
{
    printf("(STRING,%s)\n",token);
}

static char token[20];
void copytoken(char* begin, char* forward)
{
    int count = 0;
    while(begin <= forward)
    {
        if(!check_ch(*begin))
        {
            ++begin;
            continue;
        }

        token[count++] = *begin;
        ++begin;
    }
    token[count] = '\0';
}

int main(int argc, char *argv[])
{
    FILE *fin, *fout;

    if(argc == 1)
    {
        // 错误：无输入文件
        error_handle(file_exist_error);
        return 0;
    }
    //打开源程序文件
    fin = fopen(argv[1],"r");

    if(fin ==  NULL)
    {
        open_file_error();
        return 0;
    }

    //打开文件保存词法分析结果
    fout = fopen("temp.txt","w");

    if(fout == NULL)
    {
        create_file_error();
        return 0;
    }
    // 建立关键字的哈希表
    int i;
    for(i = 0; i < 38; ++i)
        createHash(word[i],HashTable);

    //从源程序文件中取字符进行处理
    char ch;
    unsigned char flag = 1;
    char str[100];
    char *buffer = str;

    buffer = fgets(str,100,fin);
    char *begin,*forward;
    int length;
    char *end;


    while(!feof(fin))
    {
        begin = forward = buffer;
        length = strlen(buffer);
        end = buffer + length;
        row = 1;                        // 记录当前的列号

        while(forward < end)
        {
            begin = forward;
            ch = *forward;
            if( check_ch(ch)==0 )
            {
                error_handle(illegal_ch_error);
                ++forward;
                ++row;                  // 移到下一列
                continue;
            }

            if((ch == TAB || ch == NEWLINE || ch == SPACE))
            {
                ++forward;
                ++row;
                begin = forward;
                continue;
            }
            if(isalpha(ch))
            {
                ++forward;
                ++row;
                ch = *forward;

                // if( check_ch(ch) ==0)
                // {
                //     error_handle(illegal_ch_error);
                //     --forward;
                //     copytoken(begin,forward);
                //     ++forward;
                //     print_word(token);
                //     continue;
                // }

                while(isalnum(ch)&&(++row, ++forward != end))
                {
                    ch = *forward;
                }

                --forward;
                --row;
                copytoken(begin,forward);
                ++forward;
                ++row;
                print_word(token);
            }
            else if(isdigit(ch))
            {
                ++forward;
                ++row;
                ch = *forward;
                // if(check_ch(ch)==0)
                // {
                //     error_handle(illegal_ch_error);
                // }
                while(isdigit(ch)&&(++row, ++forward != end))
                {
                    ch = *forward;
                    // if( check_ch(ch) == 0)
                    //     error_handle(illegal_ch_error);
                }

                --forward;
                --row;
                copytoken(begin,forward);
                ++forward;
                ++row;
                print_digit(token);
            }
            else
            {
                switch(ch)
                {
                case '*':
                    ++forward;
                    ++row;
                    ch = *forward;
                    if( check_ch(ch)==0 )
                    {
                        // error_handle(illegal_ch_error);
                        // ++forward;
                        printf("(MULTI,0)\n");
                        break;
                    }

                    if(ch == '*')
                        printf("(EXP,0)\n");
                    else
                    {
                        --forward;
                        --row;
                        printf("(MULTI,0)\n");
                    }
                    ++forward;
                    ++row;
                    break;
                case ':':
                    ++forward;
                    ++row;
                    ch = *forward;
                    if( check_ch(ch)==0 )
                    {
                        // error_handle(illegal_ch_error);
                        // ++forward;
                        printf("(COLON,0)\n");
                        break;
                    }

                    if(ch == '=')
                        printf("(ASSIGN,0)\n");
                    else
                    {
                        --forward;
                        --row;
                        printf("(COLON,0)\n");
                    }
                    ++forward;
                    ++row;
                    break;
                case '<':
                    ++forward;
                    ++row;
                    ch = *forward;

                    if( check_ch(ch)==0 )
                    {
                        // error_handle(illegal_ch_error);
                        // ++forward;
                        printf("(LT,0)\n");
                        break;
                    }


                    if(ch == '=')
                    {
                        printf("(LE,0)\n");
                    }
                    else if(ch == '>')
                    {
                        printf("(NE,0)\n");
                    }
                    else
                    {
                        --forward;
                        --row;
                        printf("(LT,0)\n");
                    }
                    ++forward;
                    ++row;
                    break;
                case '=':
                    printf("(EQ,0)\n");
                    ++forward;
                    ++row;
                    break;
                case '>':
                    ++forward;
                    ++row;
                    ch = *forward;
                    if( check_ch(ch)==0 )
                    {
                        // error_handle(illegal_ch_error);
                        // ++forward;
                        printf("(GT,0)\n");
                        break;
                    }

                    if(ch == '=')
                        printf("(GE,0)\n\n");
                    else
                    {
                        --forward;
                        --row;
                         printf("(GT,0)\n");
                    }
                    ++forward;
                    ++row;
                    break;
                case '+':
                    printf("(PLUS,0)\n");
                    ++forward;
                    ++row;
                    break;
                case '-':
                    printf("(MINUS,0)\n");
                    ++forward;
                    ++row;
                    break;
                case '/':
                    printf("(REIV,0)\n");
                    ++forward;
                    ++row;
                    break;
                case ',':
                    printf("(COMMA,0)\n");
                    ++forward;
                    ++row;
                    break;
                case ';':
                    printf("(SEMIC,0)\n");
                    ++forward;
                    ++row;
                    break;
                case '(':
                    printf("(LR_BRAC,0)\n");
                    int flag = 0; // 用于判断括号是否匹配
                    char* temp;
                    temp = forward;
                    while(++temp != end)
                    {
                        if(ch == '(')
                            ++flag;
                        else if(ch == ')')
                            --flag;
                        if(flag < 0)
                            break;

                        ch = *temp;
                    }
                    if(flag != 0)
                        error_handle(par_not_match);
                    ++forward;
                    ++row;
                    break;
                case ')':
                    printf("(RR_BRAC,0)\n");
                    ++forward;
                    ++row;
                    break;
                case '[':
                    printf("(LS_BRAC,0)\n");
                    ++forward;
                    ++row;
                    break;
                case ']':
                    printf("(RS_BRAC,0)\n");
                    ++forward;
                    ++row;
                    break;
                case '\'':
                    // printf("(Q_MARK,0)\n");
                    ++forward;
                    ++row;
                    ch = *forward;

                    while(ch != '\''&& (++row, ++forward != end))
                    {
                        ch = *forward;
                        if(!check_ch(ch))
                            error_handle(illegal_ch_error);
                        // ++forward;
                    }
                    // --forward;
                    if(ch == '\'')
                    {
                        copytoken(begin, forward); // 输出字符串
                        print_str(token);
                    }
                    else if(forward == end)
                    {
                        error_handle(quo_not_match); // 引号不匹配
                    }
                    ++forward;
                    ++row;
                    break;
                case '.':
                    printf("(F_STOP,0)\n");
                    ++forward;
                    ++row;
                    break;
                case '^':
                    printf("(CAP,0)\n");
                    ++forward;
                    ++row;
                    break;
                default:
                    // error_handle();
                    break;
                }
            }
        }
        // 再从文件中读入一行数据
        buffer = fgets(str,100,fin);
        ++line;
    }
    //关闭源程序和结果文件
    fclose(fin);
    fclose(fout);
    return 0;
}
