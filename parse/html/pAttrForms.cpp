#include "../cmn/BDString.h"
#include "../cmn/BDTypes.h"
#include "../pc/pmAttrHelpers.h"
#include "pCommon.h"
#include "pAttrForms.h"

/*
** Forms
*/
int CHTMLAttr_GetOrPost::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
	if (*pVal == "get")
		m_bGet = true;
	else if (*pVal == "post")
		m_bGet = false;
	else
		return 0;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_GetOrPost::GetAttrValue(int idx, CBDString *pVal)
{
	if (m_bGet)
		pVal->SetString("Get");
	else
		pVal->SetString("Post");
	return 1;
}

static ATTR_REMAP arFormInputType[] = {
"text",		CHTMLAttr_InputType::eText, 
"password",	CHTMLAttr_InputType::ePassword, 
"checkbox",	CHTMLAttr_InputType::eCheckbox, 
"radio",	CHTMLAttr_InputType::eRadio, 
"submit",	CHTMLAttr_InputType::eSubmit, 
"reset",	CHTMLAttr_InputType::eReset, 
"file",		CHTMLAttr_InputType::eFile, 
"hidden",	CHTMLAttr_InputType::eHidden, 
"image",	CHTMLAttr_InputType::eImage, 
"button",	CHTMLAttr_InputType::eButton, 
};
int CHTMLAttr_InputType::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arFormInputType[0], sizeof(arFormInputType)/sizeof(arFormInputType[0])))
		m_Type = (tInputType)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_InputType::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Type, &arFormInputType[0], sizeof(arFormInputType)/sizeof(arFormInputType[0]))?1:0;
}

static ATTR_REMAP arFormLegendAlign[] = {
"top",		CHTMLAttr_LAlign::eTop, 
"bottom",	CHTMLAttr_LAlign::eBottom, 
"left",		CHTMLAttr_LAlign::eLeft, 
"right",	CHTMLAttr_LAlign::eRight, 
};
int CHTMLAttr_LAlign::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arFormLegendAlign[0], sizeof(arFormLegendAlign)/sizeof(arFormLegendAlign[0])))
		m_Align = (tLAlignType)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_LAlign::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Align, &arFormLegendAlign[0], sizeof(arFormLegendAlign)/sizeof(arFormLegendAlign[0]))?1:0;
}

static ATTR_REMAP arFormButtonType[] = {
"button",		CHTMLAttr_ButtonType::eButton, 
"submit",		CHTMLAttr_ButtonType::eSubmit, 
"reset",		CHTMLAttr_ButtonType::eReset, 
};

int CHTMLAttr_ButtonType::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arFormButtonType[0], sizeof(arFormButtonType)/sizeof(arFormButtonType[0])))
		m_Type = (tButtonType)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_ButtonType::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Type, &arFormButtonType[0], sizeof(arFormButtonType)/sizeof(arFormButtonType[0]))?1:0;
}
