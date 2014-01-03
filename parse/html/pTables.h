#ifndef _PARSE_HTML_TABLES_H
#define _PARSE_HTML_TABLES_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_TABLE						100
#define NODE_ID_CAPTION						101
#define NODE_ID_COLGROUP					102
#define NODE_ID_COL							103
#define NODE_ID_THEAD						104
#define NODE_ID_TBODY						105
#define NODE_ID_TFOOT						106
#define NODE_ID_TR							107
#define NODE_ID_TH							108
#define NODE_ID_TD							109
		


class CHTMLElement_Table : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLElement_Table();
			CHTMLAttr_Text		m_Summary;
			CHTMLAttr_TAlign	m_Align;
			CHTMLAttr_Color		m_BGColor;
			CHTMLAttr_Pixels	m_Width;
			CHTMLAttr_CData		m_Border;
			CHTMLAttr_TFrame	m_Frame;
			CHTMLAttr_TRules	m_Rules;
			CHTMLAttr_Length	m_CellSpacing;
			CHTMLAttr_Length	m_CellPadding;
			CHTMLEntity_Attrs	m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		};

class CHTMLElement_Caption : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLAttr_CAlign		m_Align;
			CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_ColGroup : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLElement_ColGroup() { m_Span.m_Num = 1; }
			CHTMLAttr_Number		m_Span;
			CHTMLAttr_MultiLength	m_Widths;
			CHTMLEntity_CellHAlign	m_CellHAlign;
			CHTMLEntity_CellVAlign	m_CellVAlign;
			CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) { return (pEle->GetID()==NODE_ID_COL); }
		virtual CParseHTMLNode * GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
		};

class CHTMLElement_Col : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLElement_Col() { m_Repeat.m_Num = 1; }
			CHTMLAttr_Number		m_Repeat;
			CHTMLAttr_MultiLength	m_Width;
			CHTMLEntity_CellHAlign	m_CellHAlign;
			CHTMLEntity_CellVAlign	m_CellVAlign;
			CHTMLEntity_Attrs		m_Attrs;
		};

class CHTMLElement_THead : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLEntity_CellHAlign	m_CellHAlign;
			CHTMLEntity_CellVAlign	m_CellVAlign;
			CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_TR); }
		virtual CParseHTMLNode * GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
		};

class CHTMLElement_TBody : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLEntity_CellHAlign	m_CellHAlign;
			CHTMLEntity_CellVAlign	m_CellVAlign;
			CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_TR); }
		};

class CHTMLElement_TFoot : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLEntity_CellHAlign	m_CellHAlign;
			CHTMLEntity_CellVAlign	m_CellVAlign;
			CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual CParseHTMLNode * GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
		};

class CHTMLElement_TR : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLAttr_Color			m_Color;
			CHTMLEntity_CellHAlign	m_CellHAlign;
			CHTMLEntity_CellVAlign	m_CellVAlign;
			CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_TH || pEle->GetID()==NODE_ID_TD); }
		virtual CParseHTMLNode * GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
		};

class CHTMLElement_TH : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLElement_TH() { m_RowSpan.m_Num = m_ColSpan.m_Num = 1; }
			CHTMLAttr_Text		m_Abbr;
			CHTMLAttr_CData		m_Axis;
			CHTMLAttr_IDREFS	m_Headers;
			CHTMLAttr_Scope		m_Scope;
			CHTMLAttr_Boolean	m_bNoWrap;
			CHTMLAttr_Color		m_Color;
			CHTMLAttr_Number	m_RowSpan;
			CHTMLAttr_Number	m_ColSpan;
			CHTMLAttr_Pixels	m_Width;
			CHTMLAttr_Pixels	m_Height;

			CHTMLEntity_CellHAlign	m_CellHAlign;
			CHTMLEntity_CellVAlign	m_CellVAlign;
			CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsFlow(pEle->GetID()); }
		virtual CParseHTMLNode * GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
		};

class CHTMLElement_TD : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLElement_TD() { m_RowSpan.m_Num = m_ColSpan.m_Num = 1; }
			CHTMLAttr_Text		m_Abbr;
			CHTMLAttr_CData		m_Axis;
			CHTMLAttr_IDREFS	m_Headers;
			CHTMLAttr_Scope		m_Scope;
			CHTMLAttr_Boolean	m_bNoWrap;
			CHTMLAttr_Color		m_Color;
			CHTMLAttr_Number	m_RowSpan;
			CHTMLAttr_Number	m_ColSpan;
			CHTMLAttr_Pixels	m_Width;
			CHTMLAttr_Pixels	m_Height;

			CHTMLEntity_CellHAlign	m_CellHAlign;
			CHTMLEntity_CellVAlign	m_CellVAlign;
			CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsFlow(pEle->GetID()); }
		virtual CParseHTMLNode * GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
		};

#endif	// _PARSE_HTML_TABLES_H
