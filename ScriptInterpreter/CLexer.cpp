#include "CLexer.h"
#include "ScriptLanguageDefinition.h"
#include "ErrorDefinitions.h"
#include "MemoryHelper.h"
#include <iostream>

using namespace std;

CLexer::CLexer()
:
    m_pToken(0),
    m_nTokens(0),
    m_pCharacter(0),
    m_nCharacters(0)
{}

CLexer::~CLexer()
{
    MEMORY::SafeDeleteArr(m_pToken);
}

unsigned int CLexer::ProcessCharacters()
{
    CCharacter curChar;
    int index = 0;
    int lastPrintIndex = 0;
    do
    {
        unsigned int result = ConstructToken(index);

        if(lastPrintIndex < m_nTokens)
        {
            m_pToken[m_nTokens - 1].PrintDataToConsole();
            lastPrintIndex = m_nTokens;
        }

        if(index >= m_nCharacters)
            break;

        if(result != NO_ERROR)
        {
            if(result == ERROR_INVALID_VALUE)
                OutputErrorMsg(ERROR_INVALID_VALUE, m_pToken[m_nTokens - 1]);
        }
        curChar = m_pCharacter[index];
        index++;
    }while(curChar.GetCargo() != END_MARK);

    return NO_ERROR;
}

unsigned int CLexer::ConstructToken(int& index)
{
    CCharacter curChar;
    CToken token(m_nTokens);

    unsigned int result = NO_ERROR;

    bool tokenEnd = false;
    bool isString = false;
    bool isNum = false;
    bool isDec = false;

    do
    {
        if(index >= m_nCharacters)
            break;
        curChar = m_pCharacter[index];
		if (curChar.GetCargo() == '\0')
		{
			token.AddCharacter(curChar);
			token.SetType(S_ENDMARK);
			MEMORY::AddToList(m_pToken, token, m_nTokens);
			return NO_ERROR;
		}

        bool isSymbol = false;
        char temp[2] = {curChar.GetCargo()};

        if(!isString || m_pCharacter[index].GetCargo() == '"')
            isSymbol = IsSymbol(temp);

        if(isSymbol)
        {
            //FILTERING COMMENTS
            if(curChar.GetCargo() == '/')
            {
                //SINGLE LINE COMMENTS
                if(m_pCharacter[index + 1].GetCargo() == '/')
                {
                    for( ; ; index++)
                    {
                        if(m_pCharacter[index].GetCargo() == '\n')
                            return NO_ERROR;
                    }
                }

                //MULTI LINE COMMENTS
                if(m_pCharacter[index + 1].GetCargo() == '*')
                {
                    for( ; ; index++)
                    {
                        if(m_pCharacter[index].GetCargo() == '*' &&
                           m_pCharacter[index + 1].GetCargo() == '/')
                        {
                            index++;
                            return NO_ERROR;
                        }
                    }
                }
            }

            if(curChar.GetCargo() == '.')
            {
                if(isNum)
                {
                    isDec = true;
                    token.AddCharacter(curChar);
                    index++;
                    continue;
                }
            }

            if(curChar.GetCargo() == '"')
            {
                if(isString)
                {
                    break;
                }

                isString = true;
                index++;
                continue;
            }

            if(!token.GetTokenData())
            {
                token.AddCharacter(curChar);
            }
            else
            {
                index--;
            }
            break;
        }

        if(isString)
        {
            token.AddCharacter(curChar);
            index++;
            continue;
        }

        if(!token.GetTokenData())
        {
            if(curChar.GetCargo() == ' ')
                return NO_ERROR;
            if(curChar.GetCargo() == '\n')
                return NO_ERROR;
            if(curChar.GetCargo() == '\t')
                return NO_ERROR;
			if (curChar.GetCargo() == '\r')
				return NO_ERROR;

            if(curChar.GetCargo() >= '0' && curChar.GetCargo() <= '9')
            {
                isNum = true;
            }
        }
        else
        {
            if(curChar.GetCargo() == ' ')
                break;
            if(curChar.GetCargo() == '\n')
                break;
			if (curChar.GetCargo() == '\r')
				break;

            if(curChar.GetCargo() < '0' && curChar.GetCargo() > '9')
            {
                if(isNum)
                {
                    result = ERROR_INVALID_VALUE;
                }
            }
        }

		if (curChar.GetCargo() == '\0')
			break;

        token.AddCharacter(curChar);
        index++;
    }while(true);

    //token.AddCharacter(CCharacter('\0', 0,0,0, 0));
    if(isString)
    {
        token.SetType(S_STRING);
    }
    else if(isNum)
    {
        if(isDec)
        {
            token.SetType(S_DECIMAL);
        }
        else
        {
            token.SetType(S_NUMBER);
        }
    }
    else
    {
       token.SetType(GetTokenType(token.GetTokenString()));
    }

    MEMORY::AddToList(m_pToken, token, m_nTokens);
    return result;
}

char* CLexer::GetTokenType(char* tokenString)
{
    if(IsType(tokenString))
    {
        return S_TYPE;
    }
    else if(IsFunction(tokenString))
    {
        return S_FUNCTION;
    }
    else if(IsSymbol(tokenString))
    {
        return S_SYMBOL;
    }
    else if(IsKeyword(tokenString))
    {
        return S_KEYWORD;
    }
    else if(IsBool(tokenString))
    {
        return S_BOOL;
    }
    else
    {
        return S_IDENTIFIER;
    }
}

void CLexer::SetCharacters(CCharacter* pCharacter, int nCharacters)
{
    m_pCharacter = pCharacter;
    m_nCharacters = nCharacters;

	MEMORY::SafeDeleteArr(m_pToken);
	m_nTokens = 0;
}

CToken* CLexer::GetTokens()
{
    return m_pToken;
}

int CLexer::GetTokenCount()
{
   return m_nTokens;
}
