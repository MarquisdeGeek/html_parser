#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_Body,	"BODY",		NODE_ID_BODY,		NODE_FLG_ELEMENT | NODE_FLG_BOTHTAGS_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_Address,	"ADDRESS",	NODE_ID_ADDRESS,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Div,		"DIV",		NODE_ID_DIV,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Center,	"CENTER",	NODE_ID_CENTER,		NODE_FLG_ELEMENT | NODE_FLG_DEPRECATED);


ATTRINFO_BEGIN(CHTMLElement_Body);
	ATTRINFO_ATTR("onLoad", m_OnLoad);
	ATTRINFO_ATTR("onUnload", m_OnUnload);
	ATTRINFO_ATTR("background", m_Background);
	ATTRINFO_ENTITY("", m_BodyColor);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CHTMLElement_Body::CHTMLElement_Body()
{
	m_BodyColor.m_ColBg.m_Color		= 0xffffff; 
	m_BodyColor.m_ColText.m_Color	= 0x000000; 
	m_BodyColor.m_ColLink.m_Color	= 0x00ff00; 
	m_BodyColor.m_ColVLink.m_Color	= 0x007f00; 
	m_BodyColor.m_ColALink.m_Color	= 0x00ff7f; 
}

bool CHTMLElement_Body::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
CParseHTMLNode *pEle;
CHTMLElement *pE;
char cInsDel=0;
// <!ELEMENT BODY O O (%flow;)* +(INS|DEL) -- document body -->

	pEle = (CParseHTMLNode *)pThisEle->GetFirstChild();
	while(pEle)
		{
		if ((pE = pEle->m_pElement))
			{
			if (pE->GetID() == NODE_ID_INS)			cInsDel |= 1;
			else if (pE->GetID() == NODE_ID_DEL)	cInsDel |= 2;
			else if (entIsFlow(pE->GetID()))		;
			else									pE->SetValid(false);
			}
		//
		pEle = (CParseHTMLNode *)pThisEle->GetNextChild(pEle);
		}
	// There must be at either an INS, or a DEL - but not both
	if (cInsDel == 3)
		pThisEle->m_pElement->SetValid(false);
	//
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Address);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Address::IsChildValid(CHTMLElement *pEle)
{
	if (pEle->GetID()==NODE_ID_P) 
		return true; 
	return entIsInline(pEle->GetID()); 
}

ATTRINFO_BEGIN(CHTMLElement_Div);
	ATTRINFO_ATTR("charset", m_Charset);
	ATTRINFO_ATTR("type", m_Type);
	ATTRINFO_ATTR("href", m_href);
	ATTRINFO_ATTR("hreflang", m_hrefLang);
	ATTRINFO_ATTR("target", m_Target);
	ATTRINFO_ATTR("rel", m_Rel);
	ATTRINFO_ATTR("rev", m_Rev);
	ATTRINFO_ATTR("media", m_Media);
	ATTRINFO_ENTITY("", m_Align);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_Center);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();
