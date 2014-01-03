#include "../cmn/BDString.h"
#include "../cmn/BDTypes.h"
#include "../pc/pmAttrHelpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pCommon.h"
#include "pAttributes.h"

/*
** Standard Attribute Types
*/
int CHTMLAttr_CData::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
	pAttr=pAttr;
	m_Data = *pVal;
	m_bSpecified = true;
	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_CData::GetAttrValue(int idx, CBDString *pVal)
{
	idx=idx;
	*pVal = m_Data;
	return ATTR_PARSE_SUCCESS;
}

/*
** Imported Types
*/
int CHTMLAttr_LanguageCode::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
	pAttr=pAttr;
	m_Code = *pVal;
	m_bSpecified = true;
	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_LanguageCode::GetAttrValue(int idx, CBDString *pVal)
{
	idx=idx;
	*pVal = m_Code;
	return ATTR_PARSE_SUCCESS;
}

int CHTMLAttr_Character::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
	pAttr=pAttr;
	m_Char = (*pVal)[0];
	m_bSpecified = true;
	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_Character::GetAttrValue(int idx, CBDString *pVal)
{
	idx=idx;
	(*pVal)[0] = m_Char;
	(*pVal)[1] = '\0';
	return ATTR_PARSE_SUCCESS;
}

/*
**
*/




/*
** General
*/
CHTMLAttr_Version::CHTMLAttr_Version()
{
	m_Data = "-//W3C//DTD HTML 4.0 Transitional//EN";
}

int CHTMLAttr_Dir::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
	m_bLTR = false;
	m_bSpecified = true;
	if (*pVal == "ltr")
		m_bLTR = true;
	else if (*pVal == "rtl")
		m_bLTR = false;
	else
		return ATTR_PARSE_INVALID_ATTR;
	//
	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_Dir::GetAttrValue(int idx, CBDString *pVal)
{
	if (m_bLTR)
		*pVal = "ltr";
	else
		*pVal = "rtl";
	return ATTR_PARSE_SUCCESS;
}

static ATTR_REMAP arAlign[] = {
"left",		CHTMLAttr_Align::eLeft, 
"right",	CHTMLAttr_Align::eRight, 
"center",	CHTMLAttr_Align::eCenter, 
"justify",	CHTMLAttr_Align::eJustify, 
#if PARSE_LENIENT_SPELLING
"centre",	CHTMLAttr_Align::eCenter, 
"middle",	CHTMLAttr_Align::eCenter, 
#endif
};

int CHTMLAttr_Align::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	pAttr=pAttr;
	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arAlign[0], sizeof(arAlign)/sizeof(arAlign[0])))
		{
		m_Align = (tAlignment)iVal;
		return ATTR_PARSE_SUCCESS;
		}
	else
		{
		return ATTR_PARSE_INVALID_ATTR;
		}
}

int	CHTMLAttr_Align::GetAttrValue(int idx, CBDString *pVal)
{
	idx=idx;
	return ahGetAttrRemaps(*pVal, (int)m_Align, &arAlign[0], sizeof(arAlign)/sizeof(arAlign[0]))?1:0;
}

/*
** Entities (first) used in Anchor
*/
int CHTMLAttr_Coords::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
	pAttr=pAttr;
	m_CoordList = *pVal;
	m_bSpecified = true;
	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_Coords::GetAttrValue(int idx, CBDString *pVal)
{
	idx=idx;
	*pVal = m_CoordList;
	return ATTR_PARSE_SUCCESS;
}

static ATTR_REMAP arShape[] = {
"default",	CHTMLAttr_Shape::eDefault, 
"rect",		CHTMLAttr_Shape::eRect, 
"circle",	CHTMLAttr_Shape::eCircle, 
"poly",		CHTMLAttr_Shape::ePoly, 
};

int CHTMLAttr_Shape::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	pAttr=pAttr;
	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arShape[0], sizeof(arShape)/sizeof(arShape[0])))
		{
		m_Shape = (tShape)iVal;
		return ATTR_PARSE_SUCCESS;
		}
	else
		{
		return ATTR_PARSE_INVALID_ATTR;
		}
}

int	CHTMLAttr_Shape::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Shape, &arShape[0], sizeof(arShape)/sizeof(arShape[0]))?1:0;
}

int CHTMLAttr_AccessKey::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int i,len;

	m_bSpecified = true;
	pAttr=pAttr;
	len = pVal->Length();
	for(i=0;i<len;i++)
		if (isalpha((*pVal)[i]))
			{
			m_Key = (*pVal)[i];
			return ATTR_PARSE_SUCCESS;
			}

	return ATTR_PARSE_INVALID_ATTR;
}

int	CHTMLAttr_AccessKey::GetAttrValue(int idx, CBDString *pVal)
{
char str[2] = {0,0};

	idx=idx;
	str[0] = m_Key;
	*pVal = str;
	return ATTR_PARSE_SUCCESS;
}


int CHTMLAttr_Number::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
	pAttr=pAttr;
	m_Num = atoi(pVal->GetString());
	m_bSpecified = true;
	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_Number::GetAttrValue(int idx, CBDString *pVal)
{
char str[32];

	idx=idx;
	sprintf(str, "%ld", m_Num);
	*pVal = str;
	return ATTR_PARSE_SUCCESS;
}


int CHTMLAttr_Boolean::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
	if (*pVal == "true" || *pVal == *pAttr || atoi(pVal->GetString()))
		m_Val = true;
	else
		m_Val = false;

	m_bSpecified = true;
	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_Boolean::GetAttrValue(int idx, CBDString *pVal)
{
	idx=idx;
	if (m_Val)
		*pVal = "True";
	else
		*pVal = "False";
	return ATTR_PARSE_SUCCESS;
}


/*
** CHTMLAttr_Length
*/
int CHTMLAttr_Length::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
	m_Pixels = pVal->GetAsInt();
	m_bInPercent = pVal->InStr('%')?1:0;
	m_bSpecified = true;
	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_Length::GetAttrValue(int idx, CBDString *pVal)
{
char str[32];

	sprintf(str, "%d%c", m_Pixels, m_bInPercent?'%':'\0');
	*pVal = str;
	return ATTR_PARSE_SUCCESS;
}

int CHTMLAttr_MultiLength::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
CBDString s;

	if ((*pVal)[0] == '-')
		{ m_Relative = -1; s = pVal->GetString()[1]; }
	else if ((*pVal)[0] == '+')
		m_Relative = 1;
	else
		m_Relative = 0;
	//
	return CHTMLAttr_Length::ParseAttr(pAttr, &s);
}

int	CHTMLAttr_MultiLength::GetAttrValue(int idx, CBDString *pVal)
{
char str[32];
int first=0;

	if (m_Relative == -1)
		{ str[0] = '-'; first = 1; }
	else if (m_Relative == 1)
		{ str[0] = '+'; first = 1; }
	//
	sprintf(&str[first], "%d%s", m_Pixels, m_bInPercent?"%":"");
	*pVal = str;
	return ATTR_PARSE_SUCCESS;
}


static ATTR_REMAP arIAlign[] = {
"top",		CHTMLAttr_IAlign::eTop, 
"middle",	CHTMLAttr_IAlign::eMiddle, 
"bottom",	CHTMLAttr_IAlign::eBottom, 
"left",		CHTMLAttr_IAlign::eLeft, 
"right",	CHTMLAttr_IAlign::eRight, 
#if PARSE_LENIENT_SPELLING
"centre",	CHTMLAttr_IAlign::eMiddle, 
"center",	CHTMLAttr_IAlign::eMiddle, 
#endif
};

int CHTMLAttr_IAlign::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arIAlign[0], sizeof(arIAlign)/sizeof(arIAlign[0])))
		{
		m_Align = (tIAlign)iVal;
		return ATTR_PARSE_SUCCESS;
		}
	else
		{
		return ATTR_PARSE_INVALID_ATTR;
		}
}

int	CHTMLAttr_IAlign::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Align, &arIAlign[0], sizeof(arIAlign)/sizeof(arIAlign[0]))?1:0;
}

/*
**
*/
static ATTR_REMAP arHRAlign[] = {
"left",		CHTMLAttr_HRAlign::eLeft, 
"center",	CHTMLAttr_HRAlign::eCenter, 
"right",	CHTMLAttr_HRAlign::eRight, 
#if PARSE_LENIENT_SPELLING
"centre",	CHTMLAttr_HRAlign::eCenter, 
"middle",	CHTMLAttr_HRAlign::eCenter, 
#endif
};

int CHTMLAttr_HRAlign::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arHRAlign[0], sizeof(arHRAlign)/sizeof(arHRAlign[0])))
		{
		m_Align = (tAlignment)iVal;
		return ATTR_PARSE_SUCCESS;
		}
	else
		{
		return ATTR_PARSE_INVALID_ATTR;
		}
}

int	CHTMLAttr_HRAlign::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Align, &arHRAlign[0], sizeof(arHRAlign)/sizeof(arHRAlign[0]))?1:0;
}

/*
** BR - clear, control of text flow
*/
static ATTR_REMAP arBRClear[] = {
"none",		CHTMLAttr_BRClear::eNone, 
"left",		CHTMLAttr_BRClear::eLeft, 
"all",		CHTMLAttr_BRClear::eAll, 
"right",	CHTMLAttr_BRClear::eRight, 
};

int CHTMLAttr_BRClear::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arBRClear[0], sizeof(arBRClear)/sizeof(arBRClear[0])))
		{
		m_Clear = (tAlignment)iVal;
		return ATTR_PARSE_SUCCESS;
		}
	else
		{
		return ATTR_PARSE_INVALID_ATTR;
		}
}

int	CHTMLAttr_BRClear::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Clear, &arBRClear[0], sizeof(arBRClear)/sizeof(arBRClear[0]))?1:0;
}
