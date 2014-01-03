#ifndef _PARSE_HTML_LINKS_H
#define _PARSE_HTML_LINKS_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_A							35
#define NODE_ID_LINK					    36

class CHTMLElement_A : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_A()		{ m_Shape.m_Shape = CHTMLAttr_Shape::eRect; m_TabIdx.m_Num = 1; }
				CHTMLAttr_Charset		m_Charset;
				CHTMLAttr_ContentType	m_ContentType;
				CHTMLAttr_Text			m_Name;
				CHTMLAttr_URL			m_href;
				CHTMLAttr_LanguageCode	m_hrefLang;
				CHTMLAttr_FrameTarget	m_Target;
				CHTMLAttr_LinkTypes		m_Rel;
				CHTMLAttr_LinkTypes		m_Rev;
				CHTMLAttr_AccessKey		m_Key;
				CHTMLAttr_Shape			m_Shape;
				CHTMLAttr_Coords		m_Coords;
				CHTMLAttr_Number		m_TabIdx;
				CHTMLAttr_Script		m_OnFocus;
				CHTMLAttr_Script		m_OnBlur;
				CHTMLEntity_Attrs		m_Attrs;
				//
		virtual	bool	IsChildValid(CHTMLElement *pEle);
				};

class CHTMLElement_Link : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Charset		m_Charset;
				CHTMLAttr_ContentType	m_ContentType;
				CHTMLAttr_URL			m_href;
				CHTMLAttr_LanguageCode	m_hrefLang;
				CHTMLAttr_FrameTarget	m_Target;
				CHTMLAttr_LinkTypes		m_Rel;
				CHTMLAttr_LinkTypes		m_Rev;
				CHTMLAttr_MediaDesc		m_Media;
				CHTMLEntity_Attrs		m_Attrs;
				};

#endif	// _PARSE_HTML_LINKS_H
