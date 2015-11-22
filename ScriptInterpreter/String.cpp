#include "String.h"
#include "MemoryHelper.h"

#include <string.h>

String::String()
:
    m_pStr(0)
{}

String::~String()
{

}

void String::SetString(char* str)
{
    MEMORY::SafeDeleteArr(m_pStr);
    m_pStr = new char[strlen(str) + 1];
    strcpy(m_pStr, str);
}

char* String::GetString()
{
    return m_pStr;
}

int String::GetStringLen()
{
    if(m_pStr)
        return strlen(m_pStr);

    return 0;
}
