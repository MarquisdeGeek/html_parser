#include <stdio.h>
#include <string.h>
#include "BDParser.h"
#include "../pc/pmMarkup.h"

#define BDP_NEWLINE		'\n'

CBDParser::CBDParser()
{
	m_pFile = NULL;
	m_pRoot = NULL;
	m_pErrorList = NULL;
	m_pHTMLState = &m_HTMLState;
}

int	CBDParser::Open(CBDFile *pFile)
{
	m_pFile = pFile;
	return 1;
}

int	CBDParser::Parse(CParseNode *pRoot)
{
	if (!m_pFile)		return 0;
	//
	if (pRoot)
		{
		m_pRoot = pRoot;
		m_bAllocatedRoot = false;
		}
	else
		{
		m_pRoot = new CParseNode;
		m_bAllocatedRoot = true;
		}
	//
	m_pFile->Seek(0, BD_SEEK_SET);
	m_Line = 1;
	m_Col = 0;
	//
	do
		(void)m_pRoot->Parse(this);
	while(!m_pFile->EndOfFile());
	//
	m_pRoot->ValidateTree(this);
	//
	return 0;
}

int	CBDParser::GetChar(char *pC)
{
	return m_pFile?m_pFile->GetChar(pC):0; 
}

int	CBDParser::ReadChar(char *pC)
{
	if (m_pFile) 
		{
		int c = m_pFile->ReadChar(pC); 
		if (*pC == BDP_NEWLINE)	
			{
			m_Line++;
			m_CharsOnLastLine = m_Col;
			m_Col=0;
			}
		else
			{
			m_Col++;
			}
		return c;
		}
	 
	return 0; 
}

int	CBDParser::UngetChar(void)
{
	if (m_pFile) 
		{
		char c;

		if (!m_pFile->Seek(-1, BD_SEEK_CUR))	return 0;
		if (!m_pFile->GetChar(&c))				return 0;

		if (c == BDP_NEWLINE)
			{
			m_Line--;
			m_Col = m_CharsOnLastLine;
			}
		return 1;
		}
	return 0;
}

void CBDParser::AddError(int id, const char *pErrStr, const char *pParam1, const char *pParam2, int iLine/*=-1*/, int iCol/*=-1*/)
{
	if (m_pErrorList) 
		{
		int len = strlen(pErrStr);

		if (pParam1)	len += strlen(pParam1);
		if (pParam2)	len += strlen(pParam2);

		char *pStr = new char[len+1];	// +1 for NULL terminator
		if (!pStr)	return;

		sprintf(pStr, pErrStr, pParam1, pParam2);
		
		if (iLine == -1)	iLine = m_Line;
		if (iCol == -1)		iCol = m_Col;

		m_pErrorList->AddError(id, iLine, iCol, pStr); 
		delete pStr;
		}
}

int	CBDParser::Close(void)
{
	m_pFile = 0;
	if (m_bAllocatedRoot)
		delete m_pRoot;
	m_pRoot = 0;
	return 1;
}

