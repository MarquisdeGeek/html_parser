#ifndef _BD_PARSER_H
#define _BD_PARSER_H

#include "BDTypes.h"
#include "BDFile.h"
#include "BDTree.h"
#include "BDString.h"
#include "BDErrorList.h"

// Include state class header for each type of language you want to parse
// (this is were the HTML 'globals' are initialised)
#include "../html/phState.h"


class CBDParser;
class CParseNode;


class CParseNode : public CBDTreeItem {
	public:
		virtual CParseNode *Parse(CBDParser *pParser)	{ pParser=pParser; return 0;}
		virtual tULONG		GetNodeType(void)			{ return FOURCC(0,0,0,0); }
		virtual	void		ValidateTree(CBDParser *pParser) {}
	private:
		};

class CBDParser {
	public:
		CBDParser();
		//
		int				Open(CBDFile *pFile);
		int				Parse(CParseNode *pRoot=0);
		int				Close(void);

		int				GetChar(char *pC);
		int				ReadChar(char *pC);
		int				UngetChar(void);
		CParseNode		*GetRootNode(void)				{ return m_pRoot; }

		CBDErrorList	*GetErrorList(void)				{ return m_pErrorList; }
		void			SetErrorList(CBDErrorList *pE)	{ m_pErrorList=pE; }

		void			AddError(int id, const char *pErrStr, const char *pParam1, const char *pParam2, int iLine=-1, int iCol=-1);

		int				GetCurrentLine(void)			{ return m_Line; }
		int				GetCurrentCol(void)				{ return m_Col; }
														
	private:
		CBDFile			*m_pFile;
		CParseNode		*m_pRoot;
		bool			m_bAllocatedRoot;
		int				m_Line, m_Col, m_CharsOnLastLine;
		CBDErrorList	*m_pErrorList;
		//
		CParseHTMLState	m_HTMLState;

	public:
		CParseHTMLState	*m_pHTMLState;
		};


#endif	// _BD_PARSER_H
