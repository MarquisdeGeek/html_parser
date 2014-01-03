#ifndef _BD_ERRORLIST_H
#define _BD_ERRORLIST_H

class CBDErrorList {
	public:
		virtual ~CBDErrorList() {}
		virtual void	AddError(int id, int iLine, int iCol, const char *pErrStr)=0;
		};

#endif	// _BD_ERRORLIST_H
