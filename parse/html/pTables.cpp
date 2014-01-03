#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_Table,		"TABLE",	NODE_ID_TABLE,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Caption,		"CAPTION",	NODE_ID_CAPTION,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_ColGroup,	"COLGROUP",	NODE_ID_COLGROUP,	NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_Col,			"COL",		NODE_ID_COL,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);
IMPLEMENT_ELEMENT(CHTMLElement_THead,		"THEAD",	NODE_ID_THEAD,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_TBody,		"TBODY",	NODE_ID_TBODY,		NODE_FLG_ELEMENT | NODE_FLG_BOTHTAGS_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_TFoot,		"TFOOT",	NODE_ID_TFOOT,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_TR,			"TR",		NODE_ID_TR,			NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_TH,			"TH",		NODE_ID_TH,			NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_TD,			"TD",		NODE_ID_TD,			NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);

ATTRINFO_BEGIN(CHTMLElement_Table);
	ATTRINFO_ATTR("summary", m_Summary);
	ATTRINFO_ATTR("align", m_Align);
	ATTRINFO_ATTR("bgcolor", m_BGColor);
	ATTRINFO_ATTR("width", m_Width);
	ATTRINFO_ATTR("border", m_Border);
	ATTRINFO_ATTR("frame", m_Frame);
	ATTRINFO_ATTR("rules", m_Rules);
	ATTRINFO_ATTR("cellspacing", m_CellSpacing);
	ATTRINFO_ATTR("cellpadding", m_CellPadding);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CHTMLElement_Table::CHTMLElement_Table() 
{
	m_CellSpacing.m_Pixels = m_CellPadding.m_Pixels = 1; 
	m_CellSpacing.m_bInPercent = m_CellPadding.m_bInPercent = false; 
	m_Width.m_Pixels = 100;
	m_Width.m_bInPercent = true;
}

bool CHTMLElement_Table::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
CParseHTMLNode *pEle;
CHTMLElement *pE;
bool bValid=true, iOneCOL=false;
int iState=0, id;
// <!ELEMENT TABLE - -
//     (CAPTION?, (COL*|COLGROUP*), THEAD?, TFOOT?, TBODY+)>

	pEle = (CParseHTMLNode *)pThisEle->GetFirstChild();
	while(pEle && bValid)
		{
		if ((pE = pEle->m_pElement))
			{
			id = pE->GetID();

			if (entIsPCData(id))
				;
			else
				switch(iState)
				{
				case	0:
						iState = 1;
						if (id == NODE_ID_CAPTION)
							break;
						/* no break here */
				case	1:
						if (id == NODE_ID_COL || id == NODE_ID_COLGROUP)
							{
							iState = 1;	//else
							iOneCOL = true;
							break;	// including this makes the COL/COLGROUP optional
							}
						/* no break here */
				case	3:
/*						if (iOneCOL == false)
							{
							SetValid(false);
							pParser->AddError(0, "The <TABLE> tag was expecting a <COL> or <COLGROUP>", NULL, NULL, pEle->m_pElement->m_iLine, pEle->m_pElement->m_iCol);
							}
*/				case	4:
						iState = 4;
						if (id == NODE_ID_THEAD)
							iState = 5;
						else if (id == NODE_ID_TFOOT)
							iState = 6;
						else if (id == NODE_ID_TBODY)
							iState = 7;
						else
							{
							SetValid(false);
							pParser->AddError(0, "The <TABLE> tag was expecting a <THEAD>, <TFOOT> or <TBODY>", NULL, NULL, GetLine(), GetCol());
							}
						break;

				case	5:
						if (id == NODE_ID_TFOOT)
							iState = 6;
						else if (id == NODE_ID_TBODY)
							iState = 7;
						else if (id == NODE_ID_TR || NODE_ID_TH || NODE_ID_TD)
							;
						else
							{
							SetValid(false);
							pParser->AddError(0, "The <TABLE> tag was expecting a <TFOOT> or a <TBODY>", NULL, NULL, GetLine(), GetCol());
							}
						break;

				case	6:
						if (id == NODE_ID_TBODY)
							iState = 7;
						else if (id == NODE_ID_TR || NODE_ID_TH || NODE_ID_TD)
							;
						else
							{
							SetValid(false);
							pParser->AddError(0, "The <TABLE> tag was expecting a <TBODY>", NULL, NULL, GetLine(), GetCol());
							}
						break;

				case	7:
						if (id == NODE_ID_TR || NODE_ID_TH || NODE_ID_TD)
							;
						else
							{
							SetValid(false);
							pParser->AddError(0, "The <TABLE> tag was expecting a <TR>, <TH> or <TD>", NULL, NULL, GetLine(), GetCol());
							}
						break;

				}
			}
		//
		pEle = (CParseHTMLNode *)pThisEle->GetNextChild(pEle);
		}
	//
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Caption);
	ATTRINFO_ATTR("align", m_Align);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_ColGroup);
	ATTRINFO_ATTR("span", m_Span);
	ATTRINFO_ATTR("width", m_Widths);
	ATTRINFO_ENTITY("", m_CellHAlign);
	ATTRINFO_ENTITY("", m_CellVAlign);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CParseHTMLNode * CHTMLElement_ColGroup::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	if (id == NODE_ID_COLGROUP)	
		return pPreviouslyOpenTag->GetPreviousTagID(pParser, NODE_ID_TABLE);
	return NULL;
}


ATTRINFO_BEGIN(CHTMLElement_Col);
	ATTRINFO_ATTR("repeat", m_Repeat);
	ATTRINFO_ATTR("width", m_Width);
	ATTRINFO_ENTITY("", m_CellHAlign);
	ATTRINFO_ENTITY("", m_CellVAlign);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_THead);
	ATTRINFO_ENTITY("", m_CellHAlign);
	ATTRINFO_ENTITY("", m_CellVAlign);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_THead::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneID(pThisEle, NODE_ID_TR))
		{
		SetValid(false);
		pParser->AddError(0, "The <THEAD> tag must include at least one <TR>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

CParseHTMLNode * CHTMLElement_THead::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	/*
	** Because we are still building the tree, only the LHS branches will have
	** been built. Therefore, if there's a <TABLE> beneath us, it means we were
	** planning on spawning this tag beneath a *different* <TABLE>, and therefore is
	** no need spawn the previously opened TABLE.
	*/
	if (pPreviouslyOpenTag->IsTagIDBeneathUs(NODE_ID_TABLE))
		return NULL;

	if (id == NODE_ID_THEAD || id == NODE_ID_TFOOT || id == NODE_ID_TBODY)	
		return pPreviouslyOpenTag->GetPreviousTagID(pParser, NODE_ID_TABLE);

	return NULL;
}


ATTRINFO_BEGIN(CHTMLElement_TBody);
	ATTRINFO_ENTITY("", m_CellHAlign);
	ATTRINFO_ENTITY("", m_CellVAlign);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_TBody::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneID(pThisEle, NODE_ID_TR))
		{
		SetValid(false);
		pParser->AddError(0, "The <TBODY> tag must include at least one <TR>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_TFoot);
	ATTRINFO_ENTITY("", m_CellHAlign);
	ATTRINFO_ENTITY("", m_CellVAlign);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_TFoot::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneID(pThisEle, NODE_ID_TR))
		{
		SetValid(false);
		pParser->AddError(0, "The <TFOOT> tag must include at least one <TR>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

CParseHTMLNode * CHTMLElement_TFoot::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	if (pPreviouslyOpenTag->IsTagIDBeneathUs(NODE_ID_TABLE))
		return NULL;

	if (id == NODE_ID_THEAD || id == NODE_ID_TFOOT || id == NODE_ID_TBODY)	
		return pPreviouslyOpenTag->GetPreviousTagID(pParser, NODE_ID_TABLE);

	return NULL;
}


ATTRINFO_BEGIN(CHTMLElement_TR);
	ATTRINFO_ATTR("bgcolor", m_Color);
	ATTRINFO_ENTITY("", m_CellHAlign);
	ATTRINFO_ENTITY("", m_CellVAlign);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_TR::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneIDOf2(pThisEle, NODE_ID_TH, NODE_ID_TD))
		{
		SetValid(false);
		pParser->AddError(0, "The <TR> tag must include at least one <TH>, or <TD>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

CParseHTMLNode * CHTMLElement_TR::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	if (pPreviouslyOpenTag->IsTagIDBeneathUs(NODE_ID_TABLE))
		return NULL;

	if (id == NODE_ID_TR || id == NODE_ID_THEAD || id == NODE_ID_TFOOT || id == NODE_ID_TBODY)	
		return pPreviouslyOpenTag->GetPreviousTagID(pParser, NODE_ID_TABLE);

	return NULL;
}


ATTRINFO_BEGIN(CHTMLElement_TH);
	ATTRINFO_ATTR("abbr", m_Abbr);
	ATTRINFO_ATTR("axis", m_Axis);
	ATTRINFO_ATTR("headers", m_Headers);
	ATTRINFO_ATTR("scope", m_Scope);
	ATTRINFO_ATTR("nowrap", m_bNoWrap);
	ATTRINFO_ATTR("bgcolor", m_Color);
	ATTRINFO_ATTR("rowspan", m_RowSpan);
	ATTRINFO_ATTR("colspan", m_ColSpan);
	ATTRINFO_ATTR("width", m_Width);
	ATTRINFO_ATTR("height", m_Height);
	ATTRINFO_ENTITY("", m_CellHAlign);
	ATTRINFO_ENTITY("", m_CellVAlign);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CParseHTMLNode * CHTMLElement_TH::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	if (pPreviouslyOpenTag->IsTagIDBeneathUs(NODE_ID_TABLE))
		return NULL;

	if (id == NODE_ID_THEAD || id == NODE_ID_TFOOT || id == NODE_ID_TBODY ||
		id == NODE_ID_TD || id == NODE_ID_TR || id == NODE_ID_TH)	
		return pPreviouslyOpenTag->GetPreviousTagID(pParser, NODE_ID_TABLE);

	return NULL;
}


ATTRINFO_BEGIN(CHTMLElement_TD);
	ATTRINFO_ATTR("abbr", m_Abbr);
	ATTRINFO_ATTR("axis", m_Axis);
	ATTRINFO_ATTR("headers", m_Headers);
	ATTRINFO_ATTR("scope", m_Scope);
	ATTRINFO_ATTR("nowrap", m_bNoWrap);
	ATTRINFO_ATTR("bgcolor", m_Color);
	ATTRINFO_ATTR("rowspan", m_RowSpan);
	ATTRINFO_ATTR("colspan", m_ColSpan);
	ATTRINFO_ATTR("width", m_Width);
	ATTRINFO_ATTR("height", m_Height);
	ATTRINFO_ENTITY("", m_CellHAlign);
	ATTRINFO_ENTITY("", m_CellVAlign);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CParseHTMLNode * CHTMLElement_TD::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	if (pPreviouslyOpenTag->IsTagIDBeneathUs(NODE_ID_TABLE))
		return NULL;

	if (id == NODE_ID_THEAD || id == NODE_ID_TFOOT || id == NODE_ID_TBODY ||
		id == NODE_ID_TD || id == NODE_ID_TR || id == NODE_ID_TH)
		return pPreviouslyOpenTag->GetPreviousTagID(pParser, NODE_ID_TABLE);

	return NULL;
}

