#ifndef _HTML_ATTRIBUTES_FORMS_H
#define _HTML_ATTRIBUTES_FORMS_H

class CHTMLAttr_GetOrPost :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				CHTMLAttr_GetOrPost() { m_bGet = true; }
				bool		m_bGet;
				};

class CHTMLAttr_InputType :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tInputType { eText=0, ePassword, eCheckbox, 
								eRadio, eSubmit, eReset, 
								eFile, eHidden, eImage, 
								eButton,
								};
				CHTMLAttr_InputType() { m_Type = eText; }
				tInputType		m_Type;
				};

class CHTMLAttr_LAlign :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tLAlignType { eTop=0, eBottom, eLeft, eRight, };
				CHTMLAttr_LAlign() { m_Align = eTop; }
				tLAlignType		m_Align;
				};

class CHTMLAttr_ButtonType :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tButtonType { eButton=0, eSubmit, eReset, };
				CHTMLAttr_ButtonType() { m_Type = eButton; }
				tButtonType		m_Type;
				};




#endif	// _HTML_ATTRIBUTES_FORMS_H
