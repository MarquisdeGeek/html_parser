#ifndef _PARSE_HTML_DOCUMENT_H
#define _PARSE_HTML_DOCUMENT_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_BODY						30
#define NODE_ID_ADDRESS						31
#define NODE_ID_DIV							32
#define NODE_ID_CENTER						33

class CHTMLElement_Body : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_Body();
				CHTMLAttr_Script	m_OnLoad;
				CHTMLAttr_Script	m_OnUnload;
				CHTMLAttr_URL		m_Background; 
				CHTMLEntity_Attrs	m_Attrs;
				CHTMLEntity_BodyColors	m_BodyColor;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
				};

class CHTMLElement_Address : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle);
				};

class CHTMLElement_Div : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Charset		m_Charset;
				CHTMLAttr_ContentType	m_Type;
				CHTMLAttr_URL			m_href;
				CHTMLAttr_LanguageCode	m_hrefLang;
				CHTMLAttr_FrameTarget	m_Target;
				CHTMLAttr_LinkTypes		m_Rel;
				CHTMLAttr_LinkTypes		m_Rev;
				CHTMLAttr_MediaDesc		m_Media;
				CHTMLEntity_Attrs		m_Attrs;
				CHTMLEntity_Align		m_Align;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsFlow(pEle->GetID()); }
				};

class CHTMLElement_Center : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsFlow(pEle->GetID()); }
				};


#endif	// _PARSE_HTML_DOCUMENT_H
