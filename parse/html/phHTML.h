#ifndef _BD_PARSER_HTML_H
#define _BD_PARSER_HTML_H

/*
** This 'high level' parser file gives access to the whole HTML sub-tree
*/


#include "../cmn/BDString.h"
#include "../pc/pmMarkup.h"
#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"
#include "pEntTypes.h"
#include "pElements.h"
#include "pErrorList.h"

#define NODETYPE_HTML		FOURCC('H','T','M','L')

class CParseHTMLNode : public CParseMarkupNode {
	public:
				CParseHTMLNode(){ m_pElement = NULL; }
		virtual CParseNode		*Parse(CBDParser *pParser);
				CParseNode		*ParseStartTag(CBDParser *pParser);
				CParseNode		*ParseEndTag(CBDParser *pParser, CBDString *pStr=NULL);
				CParseNode		*ParseDTDTag(CBDParser *pParser);
				CParseNode		*ParseStartTagElement(CBDParser *pParser, CParseHTMLNode **ppCurrTag, CParseNode **ppTagToClose, char BufferedChar);
				CParseHTMLNode  *ParseEndTagElement(CBDParser *pParser, CParseNode **ppTagToClose);
				CParseNode		*ParseInstructionTag(CBDParser *pParser);
				void			ParseCDataElement(CBDParser *pParser, char BufferedChar);
				void			ParseAttributeString(CBDParser *pParser);
				
				CParseHTMLNode	*GetParentTagID(CBDParser *pParser);
				CParseHTMLNode  *GetPreviousTagID(CBDParser *pParser, int iID);

				bool			IsTagIDBeneathUs(int iNodeID);

		virtual tULONG			GetNodeType(void) { return NODETYPE_HTML; }
		
		virtual	void			ValidateTree(CBDParser *pParser);

	private:
				CParseHTMLNode *CreateTag(CBDParser *pParser, CParseHTMLNode *pParent, const char *pTagname);
				CParseHTMLNode *OpenTag(CBDParser *pParser, CParseHTMLNode *pCurTag);
				CParseHTMLNode *CloseTag(CBDParser *pParser);
				void			CloseAllChildrenTag(CBDParser *pParser);
				CParseHTMLNode *CloseLastTagID(CBDParser *pParser, int id);
				int				GetOptIDFromFlag(int iFlg);
				int				GetOptFlagFromID(int id);
				void			Add(CBDParser *pParser, CParseHTMLNode *pParent);

	public:
				CHTMLElement	*m_pElement;
		};


#endif	// _BD_PARSER_HTML_H
