/*
** Blue Dust - File code (cut-down, read only)
*/
#include "BDFile.h"

int CBDFile::GetLine(char *pLine, int iMaxLen)
{
int iChars = 1;	// the NULL terminator. Although placed at the end, consider it now
char *p = pLine;

	while(iChars < iMaxLen)
		{
		if (!GetChar(p))	break;
		p++;
		iChars++;
		}
	//
	*p = '\0';
	//
	return iChars;
}
