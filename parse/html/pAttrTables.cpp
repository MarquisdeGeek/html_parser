#include "../cmn/BDString.h"
#include "../cmn/BDTypes.h"
#include "../pc/pmAttrHelpers.h"
#include "pCommon.h"
#include "pAttrTables.h"




static ATTR_REMAP arTFrame[] = {
"void",		CHTMLAttr_TFrame::eVoid,
"above",	CHTMLAttr_TFrame::eAbove,
"below",	CHTMLAttr_TFrame::eBelow,
"hsides",	CHTMLAttr_TFrame::eHsides,
"lhs",		CHTMLAttr_TFrame::eLhs,
"rhs",		CHTMLAttr_TFrame::eRhs,
"vsides",	CHTMLAttr_TFrame::vSides,
"box",		CHTMLAttr_TFrame::eBox,
"border",	CHTMLAttr_TFrame::eBorder,
};

int CHTMLAttr_TFrame::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arTFrame[0], sizeof(arTFrame)/sizeof(arTFrame[0])))
		m_Style = (tFrameStyle)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_TFrame::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Style, &arTFrame[0], sizeof(arTFrame)/sizeof(arTFrame[0]))?1:0;
}


static ATTR_REMAP arTRules[] = {
"none",		CHTMLAttr_TRules::eNone, 
"groups",	CHTMLAttr_TRules::eGroups, 
"rows",		CHTMLAttr_TRules::eRows, 
"cols",		CHTMLAttr_TRules::eCols, 
"all",		CHTMLAttr_TRules::eAll, 
};

int CHTMLAttr_TRules::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arTRules[0], sizeof(arTRules)/sizeof(arTRules[0])))
		m_Rules = (tTRules)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_TRules::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Rules, &arTRules[0], sizeof(arTRules)/sizeof(arTRules[0]))?1:0;
}


static ATTR_REMAP arTAlign[] = {
"left",		CHTMLAttr_TAlign::eLeft, 
"center",	CHTMLAttr_TAlign::eCenter, 
"right",	CHTMLAttr_TAlign::eRight, 
#if PARSE_LENIENT_SPELLING
"centre",	CHTMLAttr_TAlign::eCenter, 
"middle",	CHTMLAttr_TAlign::eCenter, 
#endif
};

int CHTMLAttr_TAlign::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arTAlign[0], sizeof(arTAlign)/sizeof(arTAlign[0])))
		m_Alignment = (tTAlign)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_TAlign::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Alignment, &arTAlign[0], sizeof(arTAlign)/sizeof(arTAlign[0]))?1:0;
}

static ATTR_REMAP arCAlign[] = {
"top",		CHTMLAttr_CAlign::eTop, 
"bottom",	CHTMLAttr_CAlign::eBottom, 
"left",		CHTMLAttr_CAlign::eLeft, 
"right",	CHTMLAttr_CAlign::eRight, 
};

int CHTMLAttr_CAlign::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arCAlign[0], sizeof(arCAlign)/sizeof(arCAlign[0])))
		m_Alignment = (tCAlign)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_CAlign::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Alignment, &arCAlign[0], sizeof(arCAlign)/sizeof(arCAlign[0]))?1:0;
}

static ATTR_REMAP arScope[] = {
"row",		CHTMLAttr_Scope::eRow, 
"col",		CHTMLAttr_Scope::eCol, 
"rowgroup",	CHTMLAttr_Scope::eRowgroup, 
"colgroup",	CHTMLAttr_Scope::eColgroup, 
};

int CHTMLAttr_Scope::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arScope[0], sizeof(arScope)/sizeof(arScope[0])))
		m_Scope = (tScope)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_Scope::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Scope, &arScope[0], sizeof(arScope)/sizeof(arScope[0]))?1:0;
}


static ATTR_REMAP arTHAlign[] = {
"left",		CHTMLAttr_THAlign::eLeft, 
"center",	CHTMLAttr_THAlign::eCenter, 
"right",	CHTMLAttr_THAlign::eRight, 
"justify",	CHTMLAttr_THAlign::eJustify, 
"char",		CHTMLAttr_THAlign::eChar, 
#if PARSE_LENIENT_SPELLING
"centre",	CHTMLAttr_THAlign::eCenter, 
"middle",	CHTMLAttr_THAlign::eCenter, 
#endif
};

int CHTMLAttr_THAlign::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arTHAlign[0], sizeof(arTHAlign)/sizeof(arTHAlign[0])))
		m_Alignment = (tTHAlign)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_THAlign::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Alignment, &arTHAlign[0], sizeof(arTHAlign)/sizeof(arTHAlign[0]))?1:0;
}


static ATTR_REMAP arTVAlign[] = {
"top",		CHTMLAttr_TVAlign::eTop, 
"middle",	CHTMLAttr_TVAlign::eMiddle, 
"bottom",	CHTMLAttr_TVAlign::eBottom, 
"baseline",	CHTMLAttr_TVAlign::eBaseline, 
#if PARSE_LENIENT_SPELLING
"center",	CHTMLAttr_TVAlign::eMiddle, 
"centre",	CHTMLAttr_TVAlign::eMiddle, 
#endif
};

int CHTMLAttr_TVAlign::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arTVAlign[0], sizeof(arTVAlign)/sizeof(arTVAlign[0])))
		m_Alignment = (tTVAlign)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_TVAlign::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Alignment, &arTVAlign[0], sizeof(arTVAlign)/sizeof(arTVAlign[0]))?1:0;
}

