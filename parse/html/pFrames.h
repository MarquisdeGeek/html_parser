#ifndef _PARSE_HTML_FRAMES_H
#define _PARSE_HTML_FRAMES_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_FRAMESET					115
#define NODE_ID_FRAME						116
#define NODE_ID_IFRAME						117
#define NODE_ID_NOFRAMES					118


class CHTMLElement_FrameSet : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLAttr_MultiLengths	m_Rows;
			CHTMLAttr_MultiLengths	m_Cols;
			CHTMLAttr_Script		m_OnLoad;
			CHTMLAttr_Script		m_OnUnload;
			CHTMLAttr_Text			m_Border;
			CHTMLEntity_CoreAttrs	m_CoreAttrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		};

class CHTMLElement_Frame : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLElement_Frame();
			CHTMLAttr_URL			m_LongDesc;
			CHTMLAttr_CData			m_Name;
			CHTMLAttr_URL			m_Src;
			CHTMLAttr_Boolean		m_bFrameBorder;
			CHTMLAttr_Pixels		m_MarginWidth;
			CHTMLAttr_Pixels		m_MarginHeight;
			CHTMLAttr_Boolean		m_bNoResize;
			CHTMLAttr_FrameScroll	m_Scrolling;
			CHTMLEntity_CoreAttrs	m_CoreAttrs;
		};

class CHTMLElement_IFrame : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLElement_IFrame();
			CHTMLAttr_URL			m_LongDesc;
			CHTMLAttr_CData			m_Name;
			CHTMLAttr_URL			m_Src;
			CHTMLAttr_Boolean		m_bFrameBorder;
			CHTMLAttr_Pixels		m_MarginWidth;
			CHTMLAttr_Pixels		m_MarginHeight;
			CHTMLAttr_Boolean		m_bNoResize;
			CHTMLAttr_FrameScroll	m_Scrolling;
			CHTMLAttr_IAlign		m_Align;
			CHTMLAttr_Length		m_Height;
			CHTMLAttr_Length		m_Width;
			CHTMLEntity_CoreAttrs	m_CoreAttrs;
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsFlow(pEle->GetID()); }
		};

class CHTMLElement_NoFrames : public CHTMLElement {	
			DECLARE_ELEMENT(); 
		public:
			CHTMLEntity_Attrs		m_Attrs;
		// TODO: This changes on whether the 'browser' supports framed rendering
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsFlow(pEle->GetID()); }
		};

#endif	// _PARSE_HTML_FRAMES_H
