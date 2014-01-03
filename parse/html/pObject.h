#ifndef _PARSE_HTML_OBJECT_H
#define _PARSE_HTML_OBJECT_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_OBJECT						45
#define NODE_ID_PARAM						46
#define NODE_ID_APPLET						47

class CHTMLElement_Object : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public:		
				CHTMLElement_Object();
				CHTMLAttr_Boolean		m_bDeclare; 
				CHTMLAttr_URL			m_Class; 
				CHTMLAttr_URL			m_Codebase; 
				CHTMLAttr_URL			m_Data; 
				CHTMLAttr_ContentType	m_Type; 
				CHTMLAttr_ContentType	m_CodeType; 
				CHTMLAttr_URL			m_Archived; 
				CHTMLAttr_Text			m_Standby; 
				CHTMLAttr_Length		m_Height; 
				CHTMLAttr_Length		m_Width; 
				CHTMLAttr_IAlign		m_Align; 
				CHTMLAttr_Length		m_Border; 
				CHTMLAttr_Pixels		m_HSpace; 
				CHTMLAttr_Pixels		m_VSpace; 
				CHTMLAttr_Boolean		m_UseMap; 
				CHTMLAttr_Boolean		m_Shapes; 
				CHTMLAttr_Boolean		m_Export; 
				CHTMLAttr_CData			m_Name; 
				CHTMLAttr_Number		m_TabIdx; 
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle);
				};

class CHTMLElement_Param : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_ID			m_ID;
				CHTMLAttr_CData			m_Name;
				CHTMLAttr_CData			m_Value;
				CHTMLAttr_CData			m_ValueType;
				CHTMLAttr_ContentType	m_Type;
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
				};

class CHTMLElement_Applet : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_Applet();
				CHTMLAttr_URL			m_Codebase;
				CHTMLAttr_CData			m_Archive;
				CHTMLAttr_CData			m_Code;
				CHTMLAttr_CData			m_Object;
				CHTMLAttr_Text			m_Alt; 
				CHTMLAttr_CData			m_Name;
				CHTMLAttr_Length		m_Height; 
				CHTMLAttr_Length		m_Width; 
				CHTMLAttr_IAlign		m_Align; 
				CHTMLAttr_Pixels		m_HSpace; 
				CHTMLAttr_Pixels		m_VSpace; 
				CHTMLEntity_CoreAttrs	m_CoreAttrs;
		virtual bool IsChildValid(CHTMLElement *pEle);
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
				};


#endif	// _PARSE_HTML_OBJECT_H
