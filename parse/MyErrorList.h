#ifndef _MYERRORLIST_H
#define _MYERRORLIST_H

#include "cmn/BDErrorList.h"
#include "vector"

#ifdef _WIN32
using namespace std;
#endif
 using namespace std;

class CMyError {
	public:
		int		m_iLine, m_iCol;
		int		m_iID;
		char	m_Error[80];
		};

class CMyErrorList : public CBDErrorList {
	public:
		virtual void AddError(int id, int iLine, int iCol, const char *pErrStr);

		int			GetNumErrors(void) const;
const CMyError		&GetError(int idx) const;

	private:
		vector<CMyError> m_ErrList;
		};

#endif	// _MYERRORLIST_H
