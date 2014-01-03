#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_Head,		"HEAD",		NODE_ID_HEAD,		NODE_FLG_ELEMENT | NODE_FLG_BOTHTAGS_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_Title,		"TITLE",	NODE_ID_TITLE,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_IsIndex,		"ISINDEX",	NODE_ID_ISINDEX,	NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN | NODE_FLG_DEPRECATED);
IMPLEMENT_ELEMENT(CHTMLElement_Meta,		"META",		NODE_ID_META,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);
IMPLEMENT_ELEMENT(CHTMLElement_Base,		"BASE",		NODE_ID_BASE,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);
IMPLEMENT_ELEMENT(CHTMLElement_Style,		"STYLE",	NODE_ID_STYLE,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Script,		"SCRIPT",	NODE_ID_SCRIPT,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_NoScript,	"NOSCRIPT",	NODE_ID_NOSCRIPT,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_HTML,		"HTML",		NODE_ID_HTML,		NODE_FLG_ELEMENT | NODE_FLG_BOTHTAGS_OPTIONAL);


ATTRINFO_BEGIN(CHTMLElement_Head);
	ATTRINFO_ATTR("profile", m_Profile);
	ATTRINFO_ENTITY("", m_i18n);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_Title);
	ATTRINFO_ENTITY("", m_i18n);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_IsIndex);
	ATTRINFO_ATTR("prompt", m_Prompt);
	ATTRINFO_ENTITY("", m_CoreAttrs);
	ATTRINFO_ENTITY("", m_i18n);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_Base);
	ATTRINFO_ATTR("href", m_href);
	ATTRINFO_ATTR("target", m_Target);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_Meta);
	ATTRINFO_ATTR("http-equiv", m_http_equiv);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("content", m_Content);
	ATTRINFO_ATTR("scheme", m_Scheme);
	ATTRINFO_ENTITY("", m_i18n);
ATTRINFO_END();

bool CHTMLElement_Meta::ValidateRequiredAttrs(CBDParser *pParser)
{ 
	if (!m_Content.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'content' attribute", GetName(), NULL, GetLine(), GetCol());
		return false;
		}
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Style);
	ATTRINFO_ATTR("type", m_Type);
	ATTRINFO_ATTR("media", m_Media);
	ATTRINFO_ATTR("title", m_Title);
	ATTRINFO_ENTITY("", m_i18n);
ATTRINFO_END();

bool CHTMLElement_Style::ValidateRequiredAttrs(CBDParser *pParser)
{ 
	if (!m_Type.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'type' attribute", GetName(), NULL, GetLine(), GetCol());
		return false;
		}
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Script);
	ATTRINFO_ATTR("charset", m_Charset);
	ATTRINFO_ATTR("type", m_Type);
	ATTRINFO_ATTR("language", m_Language);
	ATTRINFO_ATTR("src", m_Src);
	ATTRINFO_ATTR("defer", m_bDefer);
ATTRINFO_END();

bool CHTMLElement_Script::ValidateRequiredAttrs(CBDParser *pParser)
{ 
	if (!m_Type.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'type' attribute", GetName(), NULL, GetLine(), GetCol());
		return false;
		}
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_NoScript);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_HTML);
	ATTRINFO_ATTR("version", m_Version);
	ATTRINFO_ENTITY("", m_i18n);
ATTRINFO_END();
