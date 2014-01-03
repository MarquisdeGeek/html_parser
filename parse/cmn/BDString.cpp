/*
** Blue Dust - String code (cut-down, limited functionality)
*/
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "BDTypes.h"
#include "BDString.h"

CBDString::CBDString()
{
	m_iLen = 0;
	m_iMax = 0;
	m_iIncSize = 32;
	m_pStr = 0;
	AddChar('\0');
}

CBDString::~CBDString()
{
	if (m_pStr)
		delete m_pStr;
}

const char *CBDString::GetString(void) const
{
	return m_pStr;
}

int	CBDString::AddChar(char c)
{
char sz[2];

	sz[0] = c;
	sz[1] = '\0';
	return AddString(sz);
}

void CBDString::SetString(const char *pStr)
{
	if (m_pStr)
		m_pStr[0] = '\0';
	m_iLen=0;
	AddString(pStr);
}

int	CBDString::AddString(const char *pStr)
{
size_t len;
size_t newsz;

	if (!pStr)		return 0;
	len = strlen(pStr);
	newsz = m_iLen+len;

	if (newsz+1 >= m_iMax)	// +1 for NUL
		{
		char *pNewStr = new char[newsz+m_iIncSize];

		if (!pNewStr)	return 0;
		if (m_pStr) strcpy(pNewStr, m_pStr);
		delete m_pStr;
		m_iMax = newsz+m_iIncSize;
		m_pStr = pNewStr;
		}

	strcpy(&m_pStr[m_iLen], pStr);
	m_iLen += len;

	return 1;
}

bool CBDString::operator==(const char *pStr) const
{
	return stricmp(GetString(), pStr)==0;
}

bool	CBDString::operator==(const CBDString &str) const
{
	return stricmp(GetString(), str.GetString())==0;
}

bool	CBDString::operator!=(CBDString str) const
{
	return !(*this==str);
}

CBDString &CBDString::operator=(char c)
{
char str[2] = {0,0};

	str[0] = c;
	SetString(str);
	return *this;
}

CBDString &CBDString::operator=(const char *pStr)
{
	SetString(pStr);
	return *this;
}


CBDString &CBDString::operator=(CBDString &str)
{
	if (this != &str)
		SetString(str.GetString());
	return *this;
}

char &CBDString::operator[](unsigned int idx)
{
static char cErr='\0';

	if (m_pStr && idx < Length())
		return m_pStr[idx];
	else
		return cErr;
}

/*CBDString& CBDString::operator+=(const CBDString& Str)
{
const char *p = Str.GetString();
	AddString("");//Str.GetString());
	return *this;
}*/

CBDString &CBDString::operator+=(char c)
{
	AddChar(c);
	return *this;
}

CBDString &CBDString::operator+=(const char *pStr)
{
	AddString(pStr);
	return *this;
}

int CBDString::GetAsInt(void) const
{
	if (!m_pStr)	return 0;
	return atoi(m_pStr);
}

void CBDString::Left(int iNum)
{
	if (!m_pStr)	return;
	m_pStr[iNum] = '\0';
	m_iLen = iNum;
}

const char *CBDString::InStr(char c) const
{
	if (!m_pStr)	return 0;
	return strchr(m_pStr, c);
}

unsigned int CBDString::Length(void) const
{
	if (!m_pStr)	return 0;
	//
	return strlen(m_pStr);
}

