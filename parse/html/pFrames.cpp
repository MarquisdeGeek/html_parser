#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_FrameSet,	"FRAMESET",	NODE_ID_FRAMESET,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Frame,		"FRAME",	NODE_ID_FRAME,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);
IMPLEMENT_ELEMENT(CHTMLElement_IFrame,		"IFRAME",	NODE_ID_IFRAME,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_NoFrames,	"NOFRAMES",	NODE_ID_NOFRAMES,	NODE_FLG_ELEMENT);

ATTRINFO_BEGIN(CHTMLElement_FrameSet);
	ATTRINFO_ATTR("rows", m_Rows);
	ATTRINFO_ATTR("cols", m_Cols);
	ATTRINFO_ATTR("onLoad", m_OnLoad);
	ATTRINFO_ATTR("onUnload", m_OnUnload);
	ATTRINFO_ENTITY("", m_CoreAttrs);
ATTRINFO_END();

bool CHTMLElement_FrameSet::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
// <!ELEMENT FRAMESET - - ((FRAMESET|FRAME)+ & NOFRAMES?)
CParseHTMLNode *pEle;
CHTMLElement *pE;
bool bValid=true, bOneFrame=false;

	pEle = (CParseHTMLNode *)pThisEle->GetFirstChild();
	while(pEle && bValid)
		{
		if ((pE = pEle->m_pElement))
			{
			bValid = true;

			if (pE->GetID() == NODE_ID_FRAMESET || pE->GetID() == NODE_ID_FRAME)
				bOneFrame = true;
			else if (pE->GetID() == NODE_ID_NOFRAMES || entIsPCData(pE->GetID()))
				;
			else
				bValid=false;
			}
		//
		pEle = (CParseHTMLNode *)pThisEle->GetNextChild(pEle);
		}
	//
	if (!bValid || !bOneFrame)
		{
		SetValid(false);
		pParser->AddError(0, "The <FRAMESET> tag may only include <FRAMESET>s and <FRAME>s", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}


ATTRINFO_BEGIN(CHTMLElement_Frame);
	ATTRINFO_ATTR("longdesc", m_LongDesc);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("src", m_Src);
	ATTRINFO_ATTR("frameborder", m_bFrameBorder);
	ATTRINFO_ATTR("marginwidth", m_MarginWidth);
	ATTRINFO_ATTR("marginheight", m_MarginHeight);
	ATTRINFO_ATTR("noresize", m_bNoResize);
	ATTRINFO_ATTR("scrolling", m_Scrolling);
	ATTRINFO_ENTITY("", m_CoreAttrs);
ATTRINFO_END();

CHTMLElement_Frame::CHTMLElement_Frame()
{ 
	m_bFrameBorder.m_Val = true; 
	m_Scrolling.m_Scroll = CHTMLAttr_FrameScroll::eAuto; 
}

ATTRINFO_BEGIN(CHTMLElement_IFrame);
	ATTRINFO_ATTR("longdesc", m_LongDesc);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("src", m_Src);
	ATTRINFO_ATTR("frameborder", m_bFrameBorder);
	ATTRINFO_ATTR("marginwidth", m_MarginWidth);
	ATTRINFO_ATTR("marginheight", m_MarginHeight);
	ATTRINFO_ATTR("noresize", m_bNoResize);
	ATTRINFO_ATTR("scrolling", m_Scrolling);
	ATTRINFO_ATTR("align", m_Align);
	ATTRINFO_ATTR("height", m_Height);
	ATTRINFO_ATTR("width", m_Width);
	ATTRINFO_ENTITY("", m_CoreAttrs);
ATTRINFO_END();

CHTMLElement_IFrame::CHTMLElement_IFrame()
{
	m_bFrameBorder.m_Val = true; 
	m_Scrolling.m_Scroll = CHTMLAttr_FrameScroll::eAuto; 
	m_Height.m_Pixels = m_Width.m_Pixels = 100;
	m_Height.m_bInPercent = m_Width.m_bInPercent = true;
}

ATTRINFO_BEGIN(CHTMLElement_NoFrames);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

