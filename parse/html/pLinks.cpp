#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_A,			"A",	NODE_ID_A,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Link,		"LINK",	NODE_ID_LINK,	NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);

ATTRINFO_BEGIN(CHTMLElement_A);
 	ATTRINFO_ATTR("charset", m_Charset);
 	ATTRINFO_ATTR("type", m_ContentType);
 	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("href", m_href);
	ATTRINFO_ATTR("hreflang", m_hrefLang);
	ATTRINFO_ATTR("target", m_Target);
	ATTRINFO_ATTR("rel", m_Rel);
	ATTRINFO_ATTR("rev", m_Rev);
	ATTRINFO_ATTR("accesskey", m_Key);
	ATTRINFO_ATTR("shape", m_Shape);
	ATTRINFO_ATTR("coords", m_Coords);
	ATTRINFO_ATTR("tabindex", m_TabIdx);
	ATTRINFO_ATTR("onFocus", m_OnFocus);
	ATTRINFO_ATTR("onBlur", m_OnBlur);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_A::IsChildValid(CHTMLElement *pEle)
{
	if (pEle->GetID() == NODE_ID_A)		return false;
	return entIsInline(pEle->GetID());
}

ATTRINFO_BEGIN(CHTMLElement_Link);
 	ATTRINFO_ATTR("charset", m_Charset);
	ATTRINFO_ATTR("href", m_href);
	ATTRINFO_ATTR("hreflang", m_hrefLang);
 	ATTRINFO_ATTR("type", m_ContentType);
	ATTRINFO_ATTR("rel", m_Rel);
	ATTRINFO_ATTR("rev", m_Rev);
	ATTRINFO_ATTR("media", m_Media);
	ATTRINFO_ATTR("target", m_Target);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

