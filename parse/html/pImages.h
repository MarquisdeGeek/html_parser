#ifndef _PARSE_HTML_IMAGES_H
#define _PARSE_HTML_IMAGES_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_MAP							40
#define NODE_ID_AREA					    41
#define NODE_ID_IMG							42

class CHTMLElement_Map : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Text			m_Name;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
			};

class CHTMLElement_Area : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_Area() { m_Shape.m_Shape = CHTMLAttr_Shape::eRect; m_TabIdx.m_Num = 1; }
				CHTMLAttr_Shape			m_Shape;
				CHTMLAttr_Coords		m_Coords;
				CHTMLAttr_URL			m_href;
				CHTMLAttr_FrameTarget	m_Target;
				CHTMLAttr_Boolean		m_Nohref;
				CHTMLAttr_Text			m_Alt;
				CHTMLAttr_Number		m_TabIdx;
				CHTMLAttr_AccessKey		m_AccessKey;
				CHTMLAttr_Script		m_OnFocus;
				CHTMLAttr_Script		m_OnBlur;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
			};

class CHTMLElement_Img : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_Img();
				CHTMLAttr_URL		m_SrcImage;
				CHTMLAttr_Text		m_Alt;
				CHTMLAttr_URL		m_Description;
				CHTMLAttr_Length	m_Height;
				CHTMLAttr_Length	m_Width;
				CHTMLAttr_IAlign	m_Align;
				CHTMLAttr_Length	m_BorderWidth;
				CHTMLAttr_Pixels	m_HSpace;	// gutter
				CHTMLAttr_Pixels	m_VSpace;
				CHTMLAttr_URL		m_UseMap;	// client-side
				CHTMLAttr_Boolean	m_IsMap;	// server-size
				CHTMLEntity_Attrs	m_Attrs;
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
			};

#endif	// _PARSE_HTML_IMAGES_H
