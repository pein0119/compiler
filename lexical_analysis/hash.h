#ifndef HASH
#define HASH

#include <string.h>

#define MAX_IDENTIFIER_LENGTH 16        // 定义标识符的最大长度
#define HASH_LENGTH 41                  // hash表的最大长度
#define ID_TABLE_LENGTH 41              // 标识符的最大数量


typedef struct
{
    char str[MAX_IDENTIFIER_LENGTH];
    unsigned char flag;                 // 表示该表项目是否为空，初始为0
}keyword;

// keyword HashTable[HASH_LENGTH];

int createHash(const char* str, keyword* HashTable)
{
    unsigned int i, key, step;
    //
        else
        {
            key = (key + step) % HASH_LENGTH;
        }
    }
    return -1;
}

int searchHash(const char* str, keyword* HashTable)
{
    unsigned int i, key, step;
    // i是遍历字符串时的迭代器，key是字符连加之和，step是解决哈希表冲突时的值

    i =  key = 0;
    step = 11;                          // 随便选的一个值

    unsigned int length = strlen(str);
    // 需要存入哈希表的字符串

    for(i = 0; i < length; ++i)
        key += str[i];
    // 将每个字符的ascii码值相加

    key %= HASH_LENGTH;                          // 取字符相加之和模37（小于40的最小质数）作为哈兮函数

    while(1)
    {
        if(HashTable[key].flag == 0)
            return -1;                  // 如果说找到的这个对应关键字的表项为空，该字符串在表中肯定不存在
                                        //共35个关键字，37个存储空间

        if( (HashTable[key].flag == 1) && (strcmp(HashTable[key].str, str)==0) )
            return key;                 // 如果找到一个表项不为空，且字符串与要查找的相等，则返回关键字

        key = (key + step) % HASH_LENGTH;
    }
}
char* word[38]={
    "and","array","begin","case","const","div","do","downto","else","end",
    "file","for","function","goto","if","in","label","mod","nil","not",
    "of","or","packed","procedure","program","record","repeat","set","then","to",
    "type","until","var","while","with","int","real","string"
};
#endif