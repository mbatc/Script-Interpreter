#pragma once

#include <string.h>
#include <stdio.h>

class String
{
public:
    String();
    ~String();

    void SetString(char* str);
    char* GetString();
    int GetStringLen();

    String operator+(String in)
    {
        String out;
        int len_1 = this->GetStringLen();
        int len_2 = in.GetStringLen();

        char* newStr = new char[len_1 + len_2 + 1];

        strcpy(newStr, this->GetString());
        strcpy(&newStr[len_1], in.GetString());

        out.SetString(newStr);

        return out;
    }

    void operator=(String in)
    {
        char* newStr = new char[in.GetStringLen() + 1];

        if(in.GetString())
            strcpy(newStr, in.GetString());
        newStr[in.GetStringLen()] = '\0';

        this->SetString(newStr);
    }

    bool operator==(String in)
    {
        return !strcmp(this->GetString(), in.GetString());
    }

    bool operator!=(String in)
    {
        return (bool)strcmp(this->GetString(), in.GetString());
    }

    String operator +=(String in)
    {
        return *this + in;
    }

    String operator + (int in)
    {
        char temp[512];
        sprintf(temp,"%d", in);
        String tempString;
        tempString.SetString(temp);
        return *this + tempString;
    }

    String operator + (float in)
    {
        char temp[512];
        sprintf(temp,"%f", in);
        String tempString;
        tempString.SetString(temp);
        return *this + tempString;
    }

    String operator + (bool in)
    {
        String temp;
        switch(in)
        {
        case true:
            temp.SetString("true");
            break;
        case false:
            temp.SetString("false");
            break;
        }

		return *this + temp;
    }

private:
    char* m_pStr;
};
