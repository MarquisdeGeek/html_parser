/*
** Blue Dust - Error List
*/
#include "MyErrorList.h"

/*
** This class is a nothingess class. Only the 'AddError' function needs to be 
** available for the parser. Other member functions may be added at the discretion
** of the coder.
** (being a parser, it only feels the need to report errors - not handle them - 
** therefore there is no 'remove', 'sort' or other list handling functions)
*/

void CMyErrorList::AddError(int id, int iLine, int iCol, const char *pErrStr)
{
CMyError err;

	err.m_iLine = iLine;
	err.m_iCol = iCol;
	err.m_iID = id;
	strncpy(err.m_Error, pErrStr, sizeof(err.m_Error));
	err.m_Error[sizeof(err.m_Error)-1] = '\0';
	m_ErrList.push_back(err);
}

int	CMyErrorList::GetNumErrors(void) const
{
	return m_ErrList.size();
}

const CMyError	&CMyErrorList::GetError(int idx) const
{
	return m_ErrList.at(idx);
}

