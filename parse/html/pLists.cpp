#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_DL,		"DL",	NODE_ID_DL,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_DT,		"DT",	NODE_ID_DT,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_DD,		"DD",	NODE_ID_DD,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_OL,		"OL",	NODE_ID_OL,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_UL,		"UL",	NODE_ID_UL,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Dir,		"DIR",	NODE_ID_DIR,	NODE_FLG_ELEMENT | NODE_FLG_DEPRECATED);
IMPLEMENT_ELEMENT(CHTMLElement_Menu,	"MENU",	NODE_ID_MENU,	NODE_FLG_ELEMENT | NODE_FLG_DEPRECATED);
IMPLEMENT_ELEMENT(CHTMLElement_LI,		"LI",	NODE_ID_LI,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);

ATTRINFO_BEGIN(CHTMLElement_DL);
	ATTRINFO_ATTR("compact", m_Compact);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_DL::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneIDOf2(pThisEle, NODE_ID_DT, NODE_ID_DD))
		{
		SetValid(false);
		pParser->AddError(0, "The <DL> tag must include at least one <DL> or <DT>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_DT);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CParseHTMLNode * CHTMLElement_DT::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	/* See comments in table for reasons */
	if (pPreviouslyOpenTag->IsTagIDBeneathUs(NODE_ID_DD))
		return NULL;
	
	if (id == NODE_ID_DT || id == NODE_ID_DD)	
		return pPreviouslyOpenTag->GetParentTagID(pParser);
	return NULL;
}


ATTRINFO_BEGIN(CHTMLElement_DD);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CParseHTMLNode * CHTMLElement_DD::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	/* See comments in table for reasons */
	if (pPreviouslyOpenTag->IsTagIDBeneathUs(NODE_ID_DD))
		return NULL;
	
	if (id == NODE_ID_DT || id == NODE_ID_DD)	
		return pPreviouslyOpenTag->GetParentTagID(pParser);
	return NULL;
}

ATTRINFO_BEGIN(CHTMLElement_OL);
	ATTRINFO_ATTR("type", m_NumberStyle);
	ATTRINFO_ATTR("start", m_StartSequenceNum);
	ATTRINFO_ATTR("compact", m_Compact);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_OL::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneID(pThisEle, NODE_ID_LI))
		{
		SetValid(false);
		pParser->AddError(0, "The <OL> tag must include at least one <LI>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}


ATTRINFO_BEGIN(CHTMLElement_UL);
	ATTRINFO_ATTR("type", m_NumberStyle);
	ATTRINFO_ATTR("compact", m_Compact);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_UL::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneID(pThisEle, NODE_ID_LI))
		{
		SetValid(false);
		pParser->AddError(0, "The <UL> tag must include at least one <LI>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Dir);
	ATTRINFO_ATTR("compact", m_Compact);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Dir::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneID(pThisEle, NODE_ID_LI))
		{
		SetValid(false);
		pParser->AddError(0, "The <DIR> tag must include at least one <LI>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Menu);
	ATTRINFO_ATTR("compact", m_Compact);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Menu::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneID(pThisEle, NODE_ID_LI))
		{
		SetValid(false);
		pParser->AddError(0, "The <MENU> tag must include at least one <LI>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_LI);
	ATTRINFO_ATTR("type", m_Style);
	ATTRINFO_ATTR("value", m_ResetSeqNum);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CParseHTMLNode * CHTMLElement_LI::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	// BUGWARN: KNOWN: Nothing is done here. It is possible to mismatch <OL> 
	// tags here by closing one <LI> tag too many. This will occur when
	// nested <OL>'s cause the 'ParseEndTagElement' fn to close an <LI> from
	// the parent <OL>, instead of closing the current <OL> itself.
	// This however, highlights a problem with the HTML spec and it's 
	// interpretation and not a parser problem, per se.
	if (id == NODE_ID_LI)	
		return pPreviouslyOpenTag->GetParentTagID(pParser);
	return NULL;
}

