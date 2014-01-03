#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_Map,		"MAP",	NODE_ID_MAP,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Area,	"AREA",	NODE_ID_AREA,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);
IMPLEMENT_ELEMENT(CHTMLElement_Img,		"IMG",	NODE_ID_IMG,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);

ATTRINFO_BEGIN(CHTMLElement_Map);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Map::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
CParseHTMLNode *pEle;
CHTMLElement *pE;

	pEle = (CParseHTMLNode *)pThisEle->GetFirstChild();
	while(pEle)
		{
		if ((pE = pEle->m_pElement) && pE->GetID() == NODE_ID_AREA)	
			return true;
		//
		pEle = (CParseHTMLNode *)pThisEle->GetNextChild(pEle);
		}
	//
	SetValid(false);
	pParser->AddError(0, "The <MAP> tag must include at least one <AREA>", NULL, NULL, GetLine(), GetCol());
	return true;
}

bool CHTMLElement_Map::ValidateRequiredAttrs(CBDParser *pParser)
{ 
	if (!m_Name.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'name' attribute", GetName(), NULL, GetLine(), GetCol());
		return false;
		}
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Area);
	ATTRINFO_ATTR("shape", m_Shape);
	ATTRINFO_ATTR("coords", m_Coords);
	ATTRINFO_ATTR("href", m_href);
	ATTRINFO_ATTR("target", m_Target);
	ATTRINFO_ATTR("nohref", m_Nohref);
	ATTRINFO_ATTR("alt",	m_Alt);
	ATTRINFO_ATTR("tabindex", m_TabIdx);
	ATTRINFO_ATTR("accesskey", m_AccessKey);
	ATTRINFO_ATTR("onFocus", m_OnFocus);
	ATTRINFO_ATTR("onBlur", m_OnBlur);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Area::ValidateRequiredAttrs(CBDParser *pParser)
{ 
	if (!m_Alt.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'alt' attribute", GetName(), NULL, GetLine(), GetCol());
		return false;
		}
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Img);
	ATTRINFO_ATTR("src", m_SrcImage);
	ATTRINFO_ATTR("alt", m_Alt);
	ATTRINFO_ATTR("longdesc", m_Description);
	ATTRINFO_ATTR("height", m_Height);
	ATTRINFO_ATTR("width", m_Width);
	ATTRINFO_ATTR("align", m_Align);
	ATTRINFO_ATTR("border", m_BorderWidth);
	ATTRINFO_ATTR("hspace", m_HSpace);
	ATTRINFO_ATTR("vspace", m_VSpace);
	ATTRINFO_ATTR("usemap", m_UseMap);
	ATTRINFO_ATTR("ismap", m_IsMap);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CHTMLElement_Img::CHTMLElement_Img()
{
	m_Height.m_Pixels = 100;
	m_Height.m_bInPercent = true;
	m_Width.m_Pixels = 100;
	m_Width.m_bInPercent = true;
	m_BorderWidth.m_Pixels = 0;
	m_BorderWidth.m_bInPercent = false;
}

bool CHTMLElement_Img::ValidateRequiredAttrs(CBDParser *pParser)
{ 
bool rt=true;

	if (!m_SrcImage.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'src' attribute", GetName(), NULL, GetLine(), GetCol());
		rt = false;
		}
	if (!m_Alt.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'alt' attribute", GetName(), NULL, GetLine(), GetCol());
		rt = false;
		}
	return rt;
}
