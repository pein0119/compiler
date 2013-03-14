#ifndef LEXICAL_ERROR_H
#define LEXICAL_ERROR_H

#include "micro.h"

inline
void open_file_error()
{
    printf("打开文件失败！\n");
}

inline
void create_file_error()
{
    printf("创建词法分析输出文件失败！");
}
inline
void ch_error()
{
    printf("文件中存在非法字符\n");
}

void error_handle(int error_number)
{
    switch(error_number)
    {
    case file_exist_error:
        open_file_error();
        break;

    case illegal_ch_error:
        ch_error();
        break;

    default:
        break;
    }
}

#endif