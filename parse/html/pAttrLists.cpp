#include "../cmn/BDString.h"
#include "../cmn/BDTypes.h"
#include "../pc/pmAttrHelpers.h"
#include "pCommon.h"
#include "pAttrLists.h"


/*
** List Item Attributes (OL & UL)
*/
int CHTMLAttr_OLStyle::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
/*
    1   arablic numbers     1, 2, 3, ...
    a   lower alpha         a, b, c, ...
    A   upper alpha         A, B, C, ...
    i   lower roman         i, ii, iii, ...
    I   upper roman         I, II, III, ...
*/
	m_bSpecified = true;
	m_Style = (*pVal)[0];
	if (m_Style!='1' && m_Style!='a' && m_Style!='A' && m_Style!='i' && m_Style!='I')
		{
		m_Style = '1';
		return ATTR_PARSE_INVALID_ATTR;
		}

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_OLStyle::GetAttrValue(int idx, CBDString *pVal)
{
	*pVal = m_Style;
	return 1;
}

static ATTR_REMAP arULNumStyle[] = {
"disc",		CHTMLAttr_ULStyle::eDisc, 
"square",	CHTMLAttr_ULStyle::eSquare, 
"circle",	CHTMLAttr_ULStyle::eCircle, 
};

int CHTMLAttr_ULStyle::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arULNumStyle[0], sizeof(arULNumStyle)/sizeof(arULNumStyle[0])))
		m_Style = (tNumStyle)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_ULStyle::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Style, &arULNumStyle[0], sizeof(arULNumStyle)/sizeof(arULNumStyle[0]))?1:0;
}


int CHTMLAttr_LIStyle::ParseAttr(CBDString *pAttr, CBDString *pVal)
{

		return ATTR_PARSE_INVALID_ATTR;
}

int	CHTMLAttr_LIStyle::GetAttrValue(int idx, CBDString *pVal)
{
		return ATTR_PARSE_INVALID_ATTR;
}

