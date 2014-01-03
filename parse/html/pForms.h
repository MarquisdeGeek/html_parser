#ifndef _PARSE_HTML_FORMS_H
#define _PARSE_HTML_FORMS_H

#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Unique ID List
*/
#define NODE_ID_FORM							80
#define NODE_ID_LABEL							81
#define NODE_ID_INPUT							82
#define NODE_ID_SELECT							83
#define NODE_ID_OPTGROUP						84
#define NODE_ID_OPTION							85
#define NODE_ID_TEXTAREA						86
#define NODE_ID_FIELDSET						87
#define NODE_ID_LEGEND							88
#define NODE_ID_BUTTON							89



class CHTMLElement_Form : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_Form() { m_Encoded.m_Data.SetString("application/x-www-form-urlencoded"); }
				CHTMLAttr_URL			m_ActionURL;
				CHTMLAttr_GetOrPost		m_bGetOrNotPost;
				CHTMLAttr_ContentType	m_Encoded;
				CHTMLAttr_Script		m_OnSubmit;
				CHTMLAttr_Script		m_OnReset;
				CHTMLAttr_FrameTarget	m_Target;
				CHTMLAttr_Charsets		m_SupportCharsets;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
		virtual bool IsChildValid(CHTMLElement *pEle);
				};

class CHTMLElement_Label : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_IDREF			m_For;
				CHTMLAttr_Character		m_AccessKey;
				CHTMLAttr_Script		m_OnFocus;
				CHTMLAttr_Script		m_OnBlur;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle);
				};

class CHTMLElement_Input : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_Input()	{ m_WidgetType.m_Type = CHTMLAttr_InputType::eText; }
				CHTMLAttr_InputType		m_WidgetType;
				CHTMLAttr_CData			m_Name;
				CHTMLAttr_CData			m_Value;
				CHTMLAttr_Boolean		m_bChecked;
				CHTMLAttr_Boolean		m_bDisabled;
				CHTMLAttr_Boolean		m_bReadOnly;
				CHTMLAttr_CData			m_Size;
				CHTMLAttr_Number		m_MaxLen;
				CHTMLAttr_URL			m_Src;
				CHTMLAttr_CData			m_Alt;
				CHTMLAttr_URL			m_UsemapURL;
				CHTMLAttr_IAlign		m_Align;
				CHTMLAttr_Number		m_TabbingOrder;
				CHTMLAttr_Character		m_AccessKey;
				CHTMLAttr_Script		m_OnFocus;
				CHTMLAttr_Script		m_OnBlur;
				CHTMLAttr_Script		m_OnSelect;
				CHTMLAttr_Script		m_OnChange;
				CHTMLAttr_ContentTypes	m_AcceptableMIMETypes;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
				};

class CHTMLElement_Select : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_CData			m_FieldName;
				CHTMLAttr_Number		m_RowsVisible;
				CHTMLAttr_Boolean		m_bMultiple;
				CHTMLAttr_Boolean		m_bDisabled;
				CHTMLAttr_Number		m_TabbingOrder;
				CHTMLAttr_Script		m_OnFocus;
				CHTMLAttr_Script		m_OnBlur;
				CHTMLAttr_Script		m_OnChange;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_OPTGROUP || pEle->GetID()==NODE_ID_OPTION); }
				};

class CHTMLElement_OptGroup : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Text			m_Label;
				CHTMLAttr_Boolean		m_bDisabled;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
		virtual bool IsChildValid(CHTMLElement *pEle) {	return (pEle->GetID()==NODE_ID_OPTGROUP || pEle->GetID()==NODE_ID_OPTION); }
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);				
				};

class CHTMLElement_Option : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Text			m_Label;
				CHTMLAttr_Boolean		m_bDisabled;
				CHTMLAttr_Boolean		m_bSelected;
				CHTMLAttr_CData			m_Value;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsPCData(pEle->GetID()); }
		virtual	CParseHTMLNode *  GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id);
				};

class CHTMLElement_TextArea : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_Text			m_Name;
				CHTMLAttr_Number		m_Rows;
				CHTMLAttr_Number		m_Cols;
				CHTMLAttr_Boolean		m_bDisabled;
				CHTMLAttr_Boolean		m_bReadOnly;
				CHTMLAttr_Number		m_TabbingOrder;
				CHTMLAttr_Script		m_OnFocus;
				CHTMLAttr_Script		m_OnBlur;
				CHTMLAttr_Script		m_OnSelect;
				CHTMLAttr_Script		m_OnChange;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsPCData(pEle->GetID()); }
		virtual bool ValidateRequiredAttrs(CBDParser *pParser);
				};

class CHTMLElement_FieldSet : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);
				};

class CHTMLElement_Legend : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLAttr_LAlign		m_Align;
				CHTMLAttr_Character		m_AccessKey;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle) { return entIsInline(pEle->GetID()); }
				};

class CHTMLElement_Button : public CHTMLElement {	
			DECLARE_ELEMENT(); 
			public: 
				CHTMLElement_Button() { m_Type.m_Type = CHTMLAttr_ButtonType::eSubmit; m_TabbingOrder.m_Num=0; m_AccessKey.m_Char = 0;}
				CHTMLAttr_CData			m_Name;
				CHTMLAttr_CData			m_Value;
				CHTMLAttr_ButtonType	m_Type;
				CHTMLAttr_Boolean		m_bDisabled;
				CHTMLAttr_Number		m_TabbingOrder;
				CHTMLAttr_Character		m_AccessKey;
				CHTMLAttr_Script		m_OnFocus;
				CHTMLAttr_Script		m_OnBlur;
				CHTMLEntity_Attrs		m_Attrs;
		virtual bool IsChildValid(CHTMLElement *pEle);
				};


#endif	// _PARSE_HTML_FORMS_H
