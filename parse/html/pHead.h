#ifndef _PARSE_HTML_HEAD_H
#define _PARSE_HTML_HEAD_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_HEAD					120
#define NODE_ID_TITLE					121
#define NODE_ID_ISINDEX					122
#define NODE_ID_BASE					123
#define NODE_ID_META					124
#define NODE_ID_STYLE					125
#define NODE_ID_SCRIPT					126
#define NODE_ID_NOSCRIPT				127
#define NODE_ID_HTML					128


class CHTMLElement_Head : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:
				CHTMLAttr_URL			m_Profile;
				CHTMLEntity_i18n		m_i18n;
		// I have relaxed these rules slightly. Any number of 'head.contents' may
		// be included. Perhaps this should be a TODO
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsHeadContent(pEle->GetID()) || entIsHeadMisc(pEle->GetID()); }
	
		};

class CHTMLElement_Title : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:
				CHTMLEntity_i18n		m_i18n;
		virtual bool IsChildValid(CHTMLElement *pEle) { if (entIsHeadMisc(pEle->GetID())) return false; else return true; }
		};

class CHTMLElement_IsIndex : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:
				CHTMLAttr_Text			m_Prompt;
				CHTMLEntity_CoreAttrs	m_CoreAttrs;
				CHTMLEntity_i18n		m_i18n;
		};

class CHTMLElement_Base : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:
				CHTMLAttr_URL			m_href;
				CHTMLAttr_FrameTarget	m_Target;
		};

class CHTMLElement_Meta : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:
				CHTMLAttr_Name			m_http_equiv;
				CHTMLAttr_Name			m_Name;
				CHTMLAttr_CData			m_Content;
				CHTMLAttr_CData			m_Scheme;
				CHTMLEntity_i18n		m_i18n;
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
		};

class CHTMLElement_Style : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:
				CHTMLAttr_ContentType	m_Type;
				CHTMLAttr_MediaDesc		m_Media;
				CHTMLAttr_Text			m_Title;
				CHTMLEntity_i18n		m_i18n;
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
		};

class CHTMLElement_Script : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:
				CHTMLAttr_Charset		m_Charset;
				CHTMLAttr_ContentType	m_Type;
				CHTMLAttr_CData			m_Language;
				CHTMLAttr_URL			m_Src;
				CHTMLAttr_Boolean		m_bDefer;
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
		};

class CHTMLElement_NoScript : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsFlow(pEle->GetID()); }
		};

class CHTMLElement_HTML : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:
				CHTMLAttr_Version		m_Version;
				CHTMLEntity_i18n		m_i18n;
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsHTMLContent(pEle->GetID()); }
		};

#endif	// _PARSE_HTML_HEAD_H
