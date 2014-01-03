#include "../cmn/BDString.h"
#include "../cmn/BDParser.h"
#include "../cmn/BDTypes.h"
#include "phHTML.h"


#define TAG_ALLOC(__classname)	if ((str== __classname::m_szName))	return (CHTMLElement *)new __classname

CHTMLElement *htmlCreateElement(CBDString &str)
{
/* from "pTextMarkup.h" */
	/* fontstyle */
		TAG_ALLOC(CHTMLElement_TT);
		TAG_ALLOC(CHTMLElement_I);
		TAG_ALLOC(CHTMLElement_B);
		TAG_ALLOC(CHTMLElement_U);
		TAG_ALLOC(CHTMLElement_S);
		TAG_ALLOC(CHTMLElement_Strike);
		TAG_ALLOC(CHTMLElement_Big);
		TAG_ALLOC(CHTMLElement_Small);
	/* phrase */
		TAG_ALLOC(CHTMLElement_EM);
		TAG_ALLOC(CHTMLElement_Strong);
		TAG_ALLOC(CHTMLElement_Dfn);
		TAG_ALLOC(CHTMLElement_Code);
		TAG_ALLOC(CHTMLElement_Samp);
		TAG_ALLOC(CHTMLElement_Kbd);
		TAG_ALLOC(CHTMLElement_Var);
		TAG_ALLOC(CHTMLElement_Cite);
		TAG_ALLOC(CHTMLElement_Abbr);
	/* inline */
		TAG_ALLOC(CHTMLElement_Sub);
		TAG_ALLOC(CHTMLElement_Sup);
		TAG_ALLOC(CHTMLElement_Span);
		TAG_ALLOC(CHTMLElement_BDO);

		TAG_ALLOC(CHTMLElement_BaseFont);
		TAG_ALLOC(CHTMLElement_Font);
		TAG_ALLOC(CHTMLElement_BR);

/* from "pLinks.h" */
	TAG_ALLOC(CHTMLElement_A);
	TAG_ALLOC(CHTMLElement_Link);
/* from "pDocument.h" */
	TAG_ALLOC(CHTMLElement_Body);
	TAG_ALLOC(CHTMLElement_Address);
	TAG_ALLOC(CHTMLElement_Div);
	TAG_ALLOC(CHTMLElement_Center);
/* from "pImages.h" */
	TAG_ALLOC(CHTMLElement_Map);
	TAG_ALLOC(CHTMLElement_Area);
	TAG_ALLOC(CHTMLElement_Img);
/* from "pObjects.h" */
	TAG_ALLOC(CHTMLElement_Object);
	TAG_ALLOC(CHTMLElement_Param);
	TAG_ALLOC(CHTMLElement_Applet);
/* from "pTextStyle.h" */
	TAG_ALLOC(CHTMLElement_HR);
	TAG_ALLOC(CHTMLElement_P);
	TAG_ALLOC(CHTMLElement_H1);
	TAG_ALLOC(CHTMLElement_H2);
	TAG_ALLOC(CHTMLElement_H3);
	TAG_ALLOC(CHTMLElement_H4);
	TAG_ALLOC(CHTMLElement_H5);
	TAG_ALLOC(CHTMLElement_H6);
	TAG_ALLOC(CHTMLElement_Pre);
	TAG_ALLOC(CHTMLElement_Q);
	TAG_ALLOC(CHTMLElement_BlockQuote);
	TAG_ALLOC(CHTMLElement_Ins);
	TAG_ALLOC(CHTMLElement_Del);
/* from "pForms.h" */
	TAG_ALLOC(CHTMLElement_Form);
	TAG_ALLOC(CHTMLElement_Label);
	TAG_ALLOC(CHTMLElement_Input);
	TAG_ALLOC(CHTMLElement_Select);
	TAG_ALLOC(CHTMLElement_OptGroup);
	TAG_ALLOC(CHTMLElement_Option);
	TAG_ALLOC(CHTMLElement_TextArea);
	TAG_ALLOC(CHTMLElement_FieldSet);
	TAG_ALLOC(CHTMLElement_Legend);
	TAG_ALLOC(CHTMLElement_Button);
/* from "pLists.h" */
	TAG_ALLOC(CHTMLElement_DL);
	TAG_ALLOC(CHTMLElement_DT);
	TAG_ALLOC(CHTMLElement_DD);
	TAG_ALLOC(CHTMLElement_OL);
	TAG_ALLOC(CHTMLElement_UL);
	TAG_ALLOC(CHTMLElement_Dir);
	TAG_ALLOC(CHTMLElement_Menu);
	TAG_ALLOC(CHTMLElement_LI);
/* from "pTables.h" */
	TAG_ALLOC(CHTMLElement_Table);
	TAG_ALLOC(CHTMLElement_Caption);
	TAG_ALLOC(CHTMLElement_ColGroup);
	TAG_ALLOC(CHTMLElement_Col);
	TAG_ALLOC(CHTMLElement_THead);
	TAG_ALLOC(CHTMLElement_TBody);
	TAG_ALLOC(CHTMLElement_TFoot);
	TAG_ALLOC(CHTMLElement_TR);
	TAG_ALLOC(CHTMLElement_TH);
	TAG_ALLOC(CHTMLElement_TD);
/* from "pFrames.h" */
	TAG_ALLOC(CHTMLElement_FrameSet);
	TAG_ALLOC(CHTMLElement_Frame);
	TAG_ALLOC(CHTMLElement_IFrame);
	TAG_ALLOC(CHTMLElement_NoFrames);
/* from "pHead.h" */
	TAG_ALLOC(CHTMLElement_Head);
	TAG_ALLOC(CHTMLElement_Title);
	TAG_ALLOC(CHTMLElement_IsIndex);
	TAG_ALLOC(CHTMLElement_Base);
	TAG_ALLOC(CHTMLElement_Meta);
	TAG_ALLOC(CHTMLElement_Style);
	TAG_ALLOC(CHTMLElement_Script);
	TAG_ALLOC(CHTMLElement_NoScript);
	TAG_ALLOC(CHTMLElement_HTML);

	return 0;
}

int htmlGetTagID(const char *pName)
{
CBDString str;	str.SetString(pName);
CHTMLElement *pE = htmlCreateElement(str);
int id=0;

	if (pE)
		{
		id = pE->GetID();
		delete pE;
		}
	
	return id;
}

/*
** TODO: It would be quite nice to have a 'GetTagName' function. But the only
** way I see of doing this at present is with a rather nasty macro which encompasses
** the above 'TAG_ALLOC' list, nand is invoked twice with different definitions
** for 'TAG_ALLOC'.
*/

bool CHTMLElement::CloseTagAfterOpen(void)
{
	return GetFlags() & NODE_FLG_ENDTAG_FORBIDDEN?true:false;
}

// This checks that all child tags are valid. Call this from derived classes before/after
// additional checks (i.e. that there is at least one <LI> element).
bool CHTMLElement::ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle)
{
CParseHTMLNode *pEle;
bool rt = true;

	pEle = (CParseHTMLNode *)pThisEle->GetFirstChild();
	while(pEle)
		{
		if (entIsPCData(pEle->m_pElement->GetID()))
			;
		else if (!IsChildValid(pEle->m_pElement))
			{
			pEle->m_pElement->SetValid(rt=false);
			pParser->AddError(HERR_INVALID_SUBTAG, "The <%s> tag does not allow the nested tag, <%s>", GetName(), pEle->m_pElement->GetName(), GetLine(), GetCol());
			}
		//
		pEle = (CParseHTMLNode *)pThisEle->GetNextChild(pEle);
		}
	//
	return rt;
}

bool CHTMLElement::IsChildValid(CHTMLElement *pEle)
{
	return true;
}

bool CHTMLElement::ValidateRequiredAttrs(CBDParser *pParser)
{
	return true;
}

bool CHTMLElement::AtLeastOneID(CParseHTMLNode *pThisEle, int id)
{
CParseHTMLNode *pEle;
CHTMLElement *pE;

	pEle = (CParseHTMLNode *)pThisEle->GetFirstChild();
	while(pEle)
		{
		if ((pE = pEle->m_pElement) && pE->GetID() == id)
			return true;
		//
		pEle = (CParseHTMLNode *)pThisEle->GetNextChild(pEle);
		}
	//
	return false;
}

bool CHTMLElement::AtLeastOneIDOf2(CParseHTMLNode *pThisEle, int id, int id2)
{
CParseHTMLNode *pEle;
CHTMLElement *pE;

	pEle = (CParseHTMLNode *)pThisEle->GetFirstChild();
	while(pEle)
		{
		if ((pE = pEle->m_pElement))
			{
			if (pE->GetID() == id || pE->GetID() == id2)
				return true;
			}
		//
		pEle = (CParseHTMLNode *)pThisEle->GetNextChild(pEle);
		}
	//
	return false;
}

bool CHTMLBase::IsAttrLegal(CBDString *pAttr)
{
CBDString sz;
int iNum, i;

 	iNum = GetNumAttr();
	for(i=0;i<iNum;i++)
		if (GetAttrName(i, &sz))
			if (*pAttr == sz)
				return true;
	return false;
}
