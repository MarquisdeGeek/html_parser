#ifndef _PARSE_HTML_LISTS_H
#define _PARSE_HTML_LISTS_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_DL							65
#define NODE_ID_DT							66
#define NODE_ID_DD							67
#define NODE_ID_OL							68
#define NODE_ID_UL							69
#define NODE_ID_DIR							70
#define NODE_ID_MENU						71
#define NODE_ID_LI							72

class CHTMLElement_DL : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Boolean		m_Compact;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_DT || pEle->GetID()==NODE_ID_DD); }
				};

class CHTMLElement_DT : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		virtual CParseHTMLNode *  GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
				};

class CHTMLElement_DD : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsFlow(pEle->GetID()); }
		virtual CParseHTMLNode *  GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
				};

class CHTMLElement_OL : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_OL() { m_StartSequenceNum.m_Num = 1; }
				CHTMLAttr_Boolean		m_Compact;
				CHTMLAttr_OLStyle		m_NumberStyle;
				CHTMLAttr_Number		m_StartSequenceNum;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_LI); }
				};

class CHTMLElement_UL : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Boolean		m_Compact;
				CHTMLAttr_ULStyle		m_NumberStyle;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_LI); }
				};

class CHTMLElement_Dir : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Boolean		m_Compact;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_LI); }
				};

class CHTMLElement_Menu : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Boolean		m_Compact;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_LI); }
				};

class CHTMLElement_LI : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_LIStyle		m_Style;
				CHTMLAttr_Number		m_ResetSeqNum;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsFlow(pEle->GetID()); }
		virtual CParseHTMLNode *  GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
				};

#endif	// _PARSE_HTML_LISTS_H
