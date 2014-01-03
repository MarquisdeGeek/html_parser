/*
** Blue Dust - File code (cut-down, read only)
*/
#include <stdio.h>
#include <stdlib.h>
#include "BDMemFile.h"
#include "BDTypes.h"

CBDMemFile::CBDMemFile()
{
	m_pMem = m_pCurrMem = NULL;
	m_pFileMem = NULL;
}

CBDMemFile::~CBDMemFile()
{
	Close();
}

int	CBDMemFile::Open(const char *pFilename)
{
FILE *fp = fopen(pFilename, "rb");
size_t sz, bytesread;

	if (!fp)	return 0;
	if (fseek(fp, 0, SEEK_END))
		{
		fclose(fp);
		return 0;
		}
	//
	sz = ftell(fp);
	m_pFileMem = new unsigned char[sz];
	if (!m_pFileMem)
		{
		fclose(fp);
		return 0;
		}
	//
	fseek(fp, 0, SEEK_SET);
	bytesread = fread(m_pFileMem, 1, sz, fp);
	fclose(fp);

	// Now pretend we're just a lump of data!
	m_pMem = m_pCurrMem = m_pFileMem;
	m_iMemSize = bytesread;

	return 1;
}

int	CBDMemFile::Open(const char *pFilename, size_t iMemSize)
{
	m_pMem = (unsigned char	*)pFilename;
	m_iMemSize = iMemSize;

	m_pCurrMem = m_pMem;
	return 1;
}

int	CBDMemFile::Close(void)
{
	m_pMem = 0;
	if (m_pFileMem)		delete m_pFileMem;
	m_pFileMem = NULL;
	return 1;
}


int	CBDMemFile::GetChar(char *pC)
{
	if (!m_pMem)								return 0;
	if (m_pCurrMem >= m_pMem+m_iMemSize)		return 0;
	*pC = *m_pCurrMem;
	return 1;
}

int	CBDMemFile::ReadChar(char *pC)
{
	if (!m_pMem)								return 0;
	if (m_pCurrMem >= m_pMem+m_iMemSize)		return 0;
	*pC = *m_pCurrMem;
	m_pCurrMem++;
	return 1;
}

int	CBDMemFile::Seek(long iAmount, int iFrom)
{
	if (!m_pMem)								return 0;
	//
	switch(iFrom)
		{
		case	BD_SEEK_SET:
				m_pCurrMem = m_pMem+iAmount;
				break;

		case	BD_SEEK_CUR:
				m_pCurrMem += iAmount;
				break;

		case	BD_SEEK_END:
				m_pCurrMem = m_pMem+m_iMemSize+iAmount-1;
				break;

		}
	return 1;
}

int	CBDMemFile::EndOfFile(void)
{
	if (m_pCurrMem >= m_pMem+m_iMemSize)
		return 1;
	else
		return 0;
}
