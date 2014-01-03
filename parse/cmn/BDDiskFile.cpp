/*
** Blue Dust - File code (cut-down, read only)
*/
#include <stdio.h>
#include <stdlib.h>
#include "BDDiskFile.h"
#include "BDTypes.h"

CBDDiskFile::CBDDiskFile()
{
	m_fp = 0;
}

CBDDiskFile::~CBDDiskFile()
{
	Close();
}

int	CBDDiskFile::Open(const char *pFilename)
{
	m_fp = fopen(pFilename, "r");
	if (!m_fp)	return 0;
	//
	return 1;
}

int	CBDDiskFile::Close(void)
{
	if (m_fp)		fclose(m_fp);
	m_fp = NULL;
	return 1;
}


int	CBDDiskFile::GetChar(char *pC)
{
int c;

	if (!m_fp)									return 0;
	if ((c = fgetc(m_fp)) == EOF)				return 0;
	fseek(m_fp, -1, SEEK_CUR);
	*pC = (char)c;
	return 1;
}

int	CBDDiskFile::ReadChar(char *pC)
{
int c;

	if (!m_fp)									return 0;
	if ((c = fgetc(m_fp)) == EOF)				return 0;
	*pC = (char)c;
	return 1;
}

int	CBDDiskFile::Seek(long iAmount, int iFrom)
{
	if (!m_fp)									return 0;
	//
	switch(iFrom)
		{
		case	BD_SEEK_SET:
				if (fseek(m_fp, iAmount, SEEK_SET))	return 0;
				break;

		case	BD_SEEK_CUR:
				if (fseek(m_fp, iAmount, SEEK_CUR))	return 0;
				break;

		case	BD_SEEK_END:
				if (fseek(m_fp, iAmount, SEEK_END))	return 0;
				break;

		}
	return 1;
}

int	CBDDiskFile::EndOfFile(void)
{
	if (m_fp)
		return feof(m_fp);
	else
		return 1;
}
