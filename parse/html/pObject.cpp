#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_Object,	"OBJECT",		NODE_ID_OBJECT,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Param,	"PARAM",		NODE_ID_PARAM,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);
IMPLEMENT_ELEMENT(CHTMLElement_Applet,	"APPLET",		NODE_ID_APPLET,		NODE_FLG_ELEMENT | NODE_FLG_DEPRECATED);


ATTRINFO_BEGIN(CHTMLElement_Object);
	ATTRINFO_ATTR("declare", m_bDeclare);
	ATTRINFO_ATTR("classid", m_Class);
	ATTRINFO_ATTR("codebase", m_Codebase);
	ATTRINFO_ATTR("data", m_Data);
	ATTRINFO_ATTR("type", m_Type);
	ATTRINFO_ATTR("codetype", m_CodeType);
	ATTRINFO_ATTR("archive", m_Archived);
	ATTRINFO_ATTR("standby", m_Standby);
	ATTRINFO_ATTR("height", m_Height);
	ATTRINFO_ATTR("width", m_Width);
	ATTRINFO_ATTR("align", m_Align);
	ATTRINFO_ATTR("border", m_Border);
	ATTRINFO_ATTR("hspace", m_HSpace);
	ATTRINFO_ATTR("vspace", m_VSpace);
	ATTRINFO_ATTR("usemap", m_UseMap);
	ATTRINFO_ATTR("shapes", m_Shapes);
	ATTRINFO_ATTR("export", m_Export);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("tabindex", m_TabIdx);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CHTMLElement_Object::CHTMLElement_Object()
{
	m_Width.m_Pixels = m_Height.m_Pixels = 100;
	m_Width.m_bInPercent = m_Height.m_bInPercent = 1;
	m_Border.m_Pixels = 1;
	m_TabIdx.m_Num = 1;
}

bool CHTMLElement_Object::IsChildValid(CHTMLElement *pEle)
{
	if (pEle->GetID()==NODE_ID_PARAM)
		return true;
			 
	return entIsFlow(pEle->GetID()); 
}


ATTRINFO_BEGIN(CHTMLElement_Param);
	ATTRINFO_ATTR("id", m_ID);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("value", m_Value);
	ATTRINFO_ATTR("valuetype", m_ValueType);
	ATTRINFO_ATTR("type", m_Type);
ATTRINFO_END();

bool CHTMLElement_Param::ValidateRequiredAttrs(CBDParser *pParser)
{ 
	if (!m_Name.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'name' attribute", GetName(), NULL, GetLine(), GetCol());
		return false;
		}
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Applet);
	ATTRINFO_ATTR("codebase", m_Codebase);
	ATTRINFO_ATTR("archive", m_Archive);
	ATTRINFO_ATTR("code", m_Code);
	ATTRINFO_ATTR("object", m_Object);
	ATTRINFO_ATTR("alt", m_Alt);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("height", m_Height);
	ATTRINFO_ATTR("width", m_Width);
	ATTRINFO_ATTR("align", m_Align);
	ATTRINFO_ATTR("hspace", m_HSpace);
	ATTRINFO_ATTR("vspace", m_VSpace);
	ATTRINFO_ENTITY("", m_CoreAttrs);
ATTRINFO_END();

CHTMLElement_Applet::CHTMLElement_Applet()
{
	m_Width.m_Pixels = m_Height.m_Pixels = 100;
	m_Width.m_bInPercent = m_Height.m_bInPercent = 1;
}


bool CHTMLElement_Applet::ValidateRequiredAttrs(CBDParser *pParser)
{ 
bool rt=true;

	if (!m_Height.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'height' attribute", GetName(), NULL, GetLine(), GetCol());
		rt = false;
		}
	if (!m_Width.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'width' attribute", GetName(), NULL, GetLine(), GetCol());
		rt = false;
		}
	return rt;
}

bool CHTMLElement_Applet::IsChildValid(CHTMLElement *pEle)
{
	if (pEle->GetID()==NODE_ID_PARAM)
		return true;
			 
	return entIsFlow(pEle->GetID()); 
}

