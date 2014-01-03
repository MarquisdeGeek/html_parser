#ifndef _PARSE_HTML_TEXT_MARKUP_H
#define _PARSE_HTML_TEXT_MARKUP_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_TT							1
#define NODE_ID_ITALIC					    2
#define NODE_ID_BOLD					    3
#define NODE_ID_UNDERLINE					4
#define NODE_ID_STRIKE						5
#define NODE_ID_BIG							6
#define NODE_ID_SMALL					    7

#define NODE_ID_EM							10
#define NODE_ID_STRONG						11
#define NODE_ID_DFN						    12
#define NODE_ID_CODE					    13
#define NODE_ID_SAMP					    14
#define NODE_ID_KBD							15
#define NODE_ID_VAR						    16
#define NODE_ID_CITE						17
#define NODE_ID_ABBR					    18

#define NODE_ID_SUB							20
#define NODE_ID_SUP						    21
#define NODE_ID_SPAN						22
#define NODE_ID_BDO						    23

#define NODE_ID_BASEFONT					25
#define NODE_ID_FONT						26
#define NODE_ID_BR							27

/* fontstyle */
class CHTMLElement_TT : public CHTMLElement {	DECLARE_ELEMENT(); 
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_I : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_B : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_U : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_S : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Strike : public CHTMLElement {	DECLARE_ELEMENT(); 
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Big : public CHTMLElement {	DECLARE_ELEMENT(); 
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Small : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};
/* phrase */
class CHTMLElement_EM : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Strong : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Dfn : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Code : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Samp : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Kbd : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Var : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Cite : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Abbr : public CHTMLElement {	DECLARE_ELEMENT();
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};



class CHTMLElement_Sub : public CHTMLElement {	DECLARE_ELEMENT();	
	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_Sup : public CHTMLElement {	DECLARE_ELEMENT();
 	public: CHTMLEntity_Attrs	m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
		};

class CHTMLElement_BDO : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_LanguageCode	m_LangCode; 
				CHTMLAttr_Dir			m_Dir; 
				CHTMLEntity_CoreAttrs	m_CoreAttrs; 
			virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			virtual bool ValidateRequiredAttrs(CBDParser *pParser);
			};

class CHTMLElement_Span : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLEntity_Attrs		m_Attrs; 
				CHTMLAttr_Charset		m_Charset; 
				CHTMLAttr_ContentType	m_Type; 
				CHTMLAttr_URL			m_href; 
				CHTMLAttr_LanguageCode	m_hreflang; 
				CHTMLAttr_FrameTarget	m_Target; 
				CHTMLAttr_LinkTypes		m_Rel; 
				CHTMLAttr_LinkTypes		m_Rev; 
				CHTMLAttr_MediaDesc		m_Media; 
				/* ALSO RESERVED */
				virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			};

class CHTMLElement_BaseFont : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_ID			m_ID; 
				CHTMLAttr_CData			m_Size; 
				CHTMLAttr_CData			m_Face; 
				CHTMLAttr_Color			m_Color; 
			virtual bool ValidateRequiredAttrs(CBDParser *pParser);
			};

class CHTMLElement_Font : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_CData			m_Size; 
				CHTMLAttr_CData			m_Face; 
				CHTMLAttr_Color			m_Color; 
				CHTMLEntity_CoreAttrs	m_CoreAttrs; 
				CHTMLEntity_i18n		m_i18n; 
				virtual bool IsChildValid(CHTMLElement *pEle) {	return entIsInline(pEle->GetID()); }
			};

class CHTMLElement_BR : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLEntity_CoreAttrs	m_CoreAttrs; 
				CHTMLAttr_BRClear		m_Clear;
				};

#endif // _PARSE_HTML_TEXT_MARKUP_H
