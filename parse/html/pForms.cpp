#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_Form,		"FORM",		NODE_ID_FORM,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Label,		"LABEL",	NODE_ID_LABEL,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Input,		"INPUT",	NODE_ID_INPUT,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_FORBIDDEN);
IMPLEMENT_ELEMENT(CHTMLElement_Select,		"SELECT",	NODE_ID_SELECT,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_OptGroup,	"OPTGROUP",	NODE_ID_OPTGROUP,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Option,		"OPTION",	NODE_ID_OPTION,		NODE_FLG_ELEMENT | NODE_FLG_ENDTAG_OPTIONAL);
IMPLEMENT_ELEMENT(CHTMLElement_TextArea,	"TEXTAREA",	NODE_ID_TEXTAREA,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_FieldSet,	"FIELDSET",	NODE_ID_FIELDSET,	NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Legend,		"LEGEND",	NODE_ID_LEGEND,		NODE_FLG_ELEMENT);
IMPLEMENT_ELEMENT(CHTMLElement_Button,		"BUTTON",	NODE_ID_BUTTON,		NODE_FLG_ELEMENT);

ATTRINFO_BEGIN(CHTMLElement_Form);
	ATTRINFO_ATTR("action", m_ActionURL);
	ATTRINFO_ATTR("method", m_bGetOrNotPost);
	ATTRINFO_ATTR("enctype", m_Encoded);
	ATTRINFO_ATTR("onSubmit", m_OnSubmit);
	ATTRINFO_ATTR("onReset", m_OnReset);
	ATTRINFO_ATTR("target", m_Target);
	ATTRINFO_ATTR("accept-charset", m_SupportCharsets);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Form::ValidateRequiredAttrs(CBDParser *pParser)
{
	if (!m_ActionURL.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'action' attribute", GetName(), NULL, GetLine(), GetCol());
		return false;
		}
	return true;
}

bool CHTMLElement_Form::IsChildValid(CHTMLElement *pEle)
{
	if (pEle->GetID() == NODE_ID_FORM)	
		return false;
	return entIsFlow(pEle->GetID()); 
}

ATTRINFO_BEGIN(CHTMLElement_Label);
	ATTRINFO_ATTR("for", m_For);
	ATTRINFO_ATTR("accesskey", m_AccessKey);
	ATTRINFO_ATTR("onFocus", m_OnFocus);
	ATTRINFO_ATTR("onBlur", m_OnBlur);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Label::IsChildValid(CHTMLElement *pEle)
{
	if (pEle->GetID() == NODE_ID_LABEL)	
		return false;
	return entIsInline(pEle->GetID()); 
}

ATTRINFO_BEGIN(CHTMLElement_Input);
	ATTRINFO_ATTR("type", m_WidgetType);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("value", m_Value);
	ATTRINFO_ATTR("checked", m_bChecked);
	ATTRINFO_ATTR("disabled", m_bDisabled);
	ATTRINFO_ATTR("readonly", m_bReadOnly);
	ATTRINFO_ATTR("size", m_Size);
	ATTRINFO_ATTR("maxlength", m_MaxLen);
	ATTRINFO_ATTR("src", m_Src);
	ATTRINFO_ATTR("alt", m_Alt);
	ATTRINFO_ATTR("usemap", m_UsemapURL);
	ATTRINFO_ATTR("align", m_Align);
	ATTRINFO_ATTR("tabindex", m_TabbingOrder);
	ATTRINFO_ATTR("accesskey", m_AccessKey);
	ATTRINFO_ATTR("onFocus", m_OnFocus);
	ATTRINFO_ATTR("onBlur", m_OnBlur);
	ATTRINFO_ATTR("onSelect", m_OnSelect);
	ATTRINFO_ATTR("onChange", m_OnChange);
	ATTRINFO_ATTR("accept", m_AcceptableMIMETypes);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Input::ValidateRequiredAttrs(CBDParser *pParser)
{
	if (m_WidgetType.m_Type == CHTMLAttr_InputType::eRadio ||
		m_WidgetType.m_Type == CHTMLAttr_InputType::eCheckbox)
		return m_Value.IsSpecified();
	//
	return true;
}


ATTRINFO_BEGIN(CHTMLElement_Select);
	ATTRINFO_ATTR("name", m_FieldName);
	ATTRINFO_ATTR("size", m_RowsVisible);
	ATTRINFO_ATTR("multiple", m_bMultiple);
	ATTRINFO_ATTR("disabled", m_bDisabled);
	ATTRINFO_ATTR("tabindex", m_TabbingOrder);
	ATTRINFO_ATTR("onFocus", m_OnFocus);
	ATTRINFO_ATTR("onBlur", m_OnBlur);
	ATTRINFO_ATTR("onChange", m_OnChange);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Select::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneIDOf2(pThisEle, NODE_ID_OPTGROUP, NODE_ID_OPTION))
		{
		SetValid(false);
		pParser->AddError(0, "The <SELECT> tag must include at least one <OPTGROUP> or <OPTION>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_OptGroup);
	ATTRINFO_ATTR("label", m_Label);
	ATTRINFO_ATTR("disabled", m_bDisabled);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_OptGroup::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
	CHTMLElement::ValidateTree(pParser, pThisEle);
	//
	if (!AtLeastOneIDOf2(pThisEle, NODE_ID_OPTGROUP, NODE_ID_OPTION))
		{
		SetValid(false);
		pParser->AddError(0, "The <OPTGROUP> tag must include at least one <OPTGROUP> or <OPTION>", NULL, NULL, GetLine(), GetCol());
		}
	//
	return true;
}

bool CHTMLElement_OptGroup::ValidateRequiredAttrs(CBDParser *pParser)
{
	if (!m_Label.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'label' attribute", GetName(), NULL, GetLine(), GetCol());
		return false;
		}
	return true;
}

ATTRINFO_BEGIN(CHTMLElement_Option);
	ATTRINFO_ATTR("label", m_Label);
	ATTRINFO_ATTR("disabled", m_bDisabled);
	ATTRINFO_ATTR("selected", m_bSelected);
	ATTRINFO_ATTR("value", m_Value);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

CParseHTMLNode *CHTMLElement_Option::GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id)
{
	// See table for explanation of this method:
	if (pPreviouslyOpenTag->IsTagIDBeneathUs(NODE_ID_OPTGROUP))
		return NULL;
	if (pPreviouslyOpenTag->IsTagIDBeneathUs(NODE_ID_SELECT))
		return NULL;
	//
	if (id == NODE_ID_OPTGROUP || id == NODE_ID_OPTION)
		return pPreviouslyOpenTag->GetParentTagID(pParser);
	return NULL;
}


ATTRINFO_BEGIN(CHTMLElement_TextArea);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("rows", m_Rows);
	ATTRINFO_ATTR("cols", m_Cols);
	ATTRINFO_ATTR("disabled", m_bDisabled);
	ATTRINFO_ATTR("readonly", m_bReadOnly);
	ATTRINFO_ATTR("tabindex", m_TabbingOrder);
	ATTRINFO_ATTR("onFocus", m_OnFocus);
	ATTRINFO_ATTR("onBlur", m_OnBlur);
	ATTRINFO_ATTR("onSelect", m_OnSelect);
	ATTRINFO_ATTR("onChange", m_OnChange);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_TextArea::ValidateRequiredAttrs(CBDParser *pParser)
{ 
bool rt=true;

	if (!m_Rows.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'rows' attribute", GetName(), NULL, GetLine(), GetCol());
		rt = false;
		}
	if (!m_Cols.IsSpecified())
		{
		pParser->AddError(HERR_NO_REQD_ATTR, "The <%s> tag requires the 'cols' attribute", GetName(), NULL, GetLine(), GetCol());
		rt = false;
		}
	return rt;
}

ATTRINFO_BEGIN(CHTMLElement_FieldSet);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_FieldSet::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
// <!ELEMENT FIELDSET - - (#PCDATA,LEGEND,(%flow;)*) -- form control group -->

CParseHTMLNode *pEle;
CHTMLElement *pE;
bool bValid=true;
int iOrder=0;

	pEle = (CParseHTMLNode *)pThisEle->GetFirstChild();
	while(pEle && bValid)
		{
		if ((pE = pEle->m_pElement))
			{
			switch(iOrder)
				{
				case	0:
						if (entIsPCData(pE->GetID()))
							{
							iOrder=1;
							}
						else
							{
							bValid=false;
							pParser->AddError(0, "Expecting %%PCDATA in <%s> tag", pEle->m_pElement->GetName(), NULL, GetLine(), GetCol());
							}

						break;
				case	1:
						if (pE->GetID() == NODE_ID_LEGEND)
							{
							iOrder=2;
							}
						else
							{
							bValid=false;
							pParser->AddError(0, "Expecting <LEGEND> in <%s> tag", pEle->m_pElement->GetName(), NULL, GetLine(), GetCol());
							}
						break;
				case	2:
						if (!entIsFlow(pE->GetID()))
							{
							bValid=false;
							pParser->AddError(0, "Expecting %%flow entity in <%s> tag", pEle->m_pElement->GetName(), NULL, GetLine(), GetCol());
							}
						break;
				}
			}
		//
		pEle = (CParseHTMLNode *)pThisEle->GetNextChild(pEle);
		}
	//
	if (!bValid)
		SetValid(false);
	//
	return true;
}


ATTRINFO_BEGIN(CHTMLElement_Legend);
	ATTRINFO_ATTR("align", m_Align);
	ATTRINFO_ATTR("accesskey", m_AccessKey);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLElement_Button);
	ATTRINFO_ATTR("name", m_Name);
	ATTRINFO_ATTR("value", m_Value);
	ATTRINFO_ATTR("type", m_Type);
	ATTRINFO_ATTR("disabled", m_bDisabled);
	ATTRINFO_ATTR("tabindex", m_TabbingOrder);
	ATTRINFO_ATTR("accesskey", m_AccessKey);
	ATTRINFO_ATTR("onFocus", m_OnFocus);
	ATTRINFO_ATTR("onBlur", m_OnBlur);
	ATTRINFO_ENTITY("", m_Attrs);
ATTRINFO_END();

bool CHTMLElement_Button::IsChildValid(CHTMLElement *pEle)
{ 
int id=pEle->GetID();

	if (id==NODE_ID_A || id==NODE_ID_FORM || id==NODE_ID_ISINDEX)	return false;
	if (id==NODE_ID_FIELDSET || id==NODE_ID_IFRAME)	return false;
	if (entIsFormCtrl(id))	return false;
	return entIsFlow(id); 
}
