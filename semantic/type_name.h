#ifndef _TYPE_NAME_H
#define _TYPE_NAME_H

typedef struct
{
    int type;                   // 标识当前类型,现只支持整型(1),布尔型(2)
    int width;                  // 当前类型的宽度(所占字节)
}type_name;

type_name tpNm[10];             // 最多支持10种类型

#endif
