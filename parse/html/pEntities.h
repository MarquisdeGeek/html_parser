#ifndef _HTML_ENTITIES_H
#define _HTML_ENTITIES_H
/*
**
*/
#include "pEntTypes.h"

class CCData				{ public: CBDString m_CData; };

/*
** Parameter Entities
*/
class CHTMLEntity_BodyColors : public CHTMLBase		{ 
		DECLARE_ENTITY();
		public: 
			CHTMLAttr_Color		m_ColBg;
			CHTMLAttr_Color		m_ColText;
			CHTMLAttr_Color		m_ColLink;
			CHTMLAttr_Color		m_ColVLink;
			CHTMLAttr_Color		m_ColALink;
		};

/*
** Generic Attributes
*/
class CHTMLEntity_CoreAttrs	: public CHTMLEntity	{ 
		DECLARE_ENTITY();
		public: 
			CHTMLAttr_ID		m_ID;		
			CHTMLAttr_CData		m_Class;		
			CHTMLAttr_CData		m_Style;		
			CHTMLAttr_Text		m_Title;		
		};

class CHTMLEntity_i18n		: public CHTMLEntity	{ 
		DECLARE_ENTITY();
		public: 
			CHTMLAttr_Dir			m_DirLTR;		
			CHTMLAttr_LanguageCode	m_LangCode;		
		};

class CHTMLEntity_Events : public CHTMLBase		{ 
		DECLARE_ENTITY();
		public: 
			CHTMLAttr_Script m_OnClick;	
			CHTMLAttr_Script m_OnDoubleClick;	
			CHTMLAttr_Script m_OnMouseDown;	
			CHTMLAttr_Script m_OnMouseUp;	
			CHTMLAttr_Script m_OnMouseOver;	
			CHTMLAttr_Script m_OnMouseMove;	
			CHTMLAttr_Script m_OnMouseOut;	
			CHTMLAttr_Script m_OnKeyPress;	
			CHTMLAttr_Script m_OnKeyDown;	
			CHTMLAttr_Script m_OnKeyUp;	
		};

class CHTMLEntity_Attrs : public CHTMLEntity { 
		DECLARE_ENTITY();
		public:
			CHTMLEntity_Events		m_Events;
			CHTMLEntity_CoreAttrs	m_CoreAttrs;
			CHTMLEntity_i18n		m_i18n;
		};

class CHTMLEntity_Align : public CHTMLEntity { 
		DECLARE_ENTITY();
		public:
			CHTMLAttr_Align			m_Align;
		};

/*
** from Tables
*/
class CHTMLEntity_CellHAlign : public CHTMLEntity { 
		DECLARE_ENTITY();
		public:
			CHTMLEntity_CellHAlign();
			CHTMLAttr_THAlign			m_Align;
			CHTMLAttr_Character			m_AlignmentChar;
			CHTMLAttr_Length			m_AlignmentCharOffset;
		};

class CHTMLEntity_CellVAlign : public CHTMLEntity { 
		DECLARE_ENTITY();
		public:
			CHTMLAttr_TVAlign			m_VAlign;
		};


#endif	// _HTML_ENTITIES_H
