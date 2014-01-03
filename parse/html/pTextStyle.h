#ifndef _PARSE_HTML_TEXT_STYLE_H
#define _PARSE_HTML_TEXT_STYLE_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_HR							50
#define NODE_ID_P							51
#define NODE_ID_H1							52
#define NODE_ID_H2							53
#define NODE_ID_H3							54
#define NODE_ID_H4							55
#define NODE_ID_H5							56
#define NODE_ID_H6							57
#define NODE_ID_PRE							58
#define NODE_ID_Q							59
#define NODE_ID_BLOCKQUOTE					60
#define NODE_ID_INS							61
#define NODE_ID_DEL							62

class CHTMLElement_HR : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_HR()		{ m_Width.m_Pixels = 100; m_Width.m_bInPercent = true; }
				CHTMLAttr_HRAlign		m_Align; 
				CHTMLAttr_Boolean		m_NoShade; 
				CHTMLAttr_Pixels		m_Size; 
				CHTMLAttr_Length		m_Width; 
				CHTMLEntity_Events		m_Events; 
				CHTMLEntity_CoreAttrs	m_Attrs; 
			};

class CHTMLElement_P : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_HRAlign	m_Align; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		virtual CParseHTMLNode * GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
			};

class CHTMLElement_H1 : public CHTMLElement {	
			DECLARE_ELEMENT();
			public: 
				CHTMLAttr_HRAlign	m_Align; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			};

class CHTMLElement_H2 : public CHTMLElement {	
			DECLARE_ELEMENT();
			public: 
				CHTMLAttr_HRAlign	m_Align; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			};

class CHTMLElement_H3 : public CHTMLElement {	
			DECLARE_ELEMENT();
			public: 
				CHTMLAttr_HRAlign	m_Align; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			};

class CHTMLElement_H4 : public CHTMLElement {	
			DECLARE_ELEMENT();
			public: 
				CHTMLAttr_HRAlign	m_Align; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			};

class CHTMLElement_H5 : public CHTMLElement {	
			DECLARE_ELEMENT();
			public: 
				CHTMLAttr_HRAlign	m_Align; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			};

class CHTMLElement_H6 : public CHTMLElement {	
			DECLARE_ELEMENT();
			public: 
				CHTMLAttr_HRAlign	m_Align; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			};

class CHTMLElement_Pre : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_Pre() { m_Width.m_Num = 100; }
				CHTMLAttr_Number	m_Width; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle);
			};

class CHTMLElement_Q : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_URL		m_Cite; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			};

class CHTMLElement_BlockQuote : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_URL		m_Cite; 
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsFlow(pEle->GetID()); }
			};

class CHTMLElement_Ins : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_URL		m_Cite; 
				CHTMLAttr_DateTime	m_Date;
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsFlow(pEle->GetID()); }
			};

class CHTMLElement_Del : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_URL		m_Cite; 
				CHTMLAttr_DateTime	m_Date;
				CHTMLEntity_Attrs	m_Attrs; 
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsFlow(pEle->GetID()); }
			};



#endif	// _PARSE_HTML_TEXT_STYLE_H
