#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_HR,		"HR",	NODE_ID_HR,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);
IMPLEMENT_ELEMENT(CHTMLElement_P,		"P",	NODE_ID_P,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_H1,		"H1",	NODE_ID_H1,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_H2,		"H2",	NODE_ID_H2,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_H3,		"H3",	NODE_ID_H3,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_H4,		"H4",	NODE_ID_H4,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_H5,		"H5",	NODE_ID_H5,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_H6,		"H6",	NODE_ID_H6,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Pre,		"PRE",	NODE_ID_PRE,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Q,		"Q",	NODE_ID_Q,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_BlockQuote,	"BLOCKQUOTE",	NODE_ID_BLOCKQUOTE,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Ins,		"INS",	NODE_ID_INS,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Del,		"DEL",	NODE_ID_DEL,	NODE_FLG_ELEMENT);


ATTRINFO_BEGIN(CHTMLElement_HR);
	ATTRINFO_ATTR("align",	m_Align);
	ATTRINFO_ATTR("noshade",	m_NoShade);
	ATTRINFO_ATTR("size",	m_Size);
	ATTRINFO_ATTR("width",	m_Width);
	ATTRINFO_ENTITY("", m_Attrs);
	ATTRINFO_ENTITY("", m_Events);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_P);
	ATTRINFO_ATTR("align",	m_Align);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

CParseHTMLNode * CHTMLElement_P::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	if (id == NODE_ID_P || entIsBlock(id))	
		return pPreviouslyOpenTag->GetParentTagID(pParser);
	return NULL;
}


ATTRINFO_BEGIN(CHTMLElement_H1);
	ATTRINFO_ATTR("align",	m_Align);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_H2);
	ATTRINFO_ATTR("align",	m_Align);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_H3);
	ATTRINFO_ATTR("align",	m_Align);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_H4);
	ATTRINFO_ATTR("align",	m_Align);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_H5);
	ATTRINFO_ATTR("align",	m_Align);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_H6);
	ATTRINFO_ATTR("align",	m_Align);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_Pre);
	ATTRINFO_ATTR("width",	m_Width);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Pre::IsChildValid(CHTMLElement *pEle)
{
	if (entIsPreExclusion(pEle->GetID()))
		return false;
	return entIsInline(pEle->GetID());
}

ATTRINFO_BEGIN(CHTMLElement_Q);
	ATTRINFO_ATTR("cite",	m_Cite);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_BlockQuote);
	ATTRINFO_ATTR("cite",	m_Cite);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_Ins);
	ATTRINFO_ATTR("cite",	m_Cite);
	ATTRINFO_ATTR("datetime",	m_Date);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_Del);
	ATTRINFO_ATTR("cite",	m_Cite);
	ATTRINFO_ATTR("datetime",	m_Date);
	ATTRINFO_ENTITY("",	m_Attrs);
ATTRINFO_END();