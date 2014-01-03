#ifndef _HTML_ATTRIBUTES_LISTS_H
#define _HTML_ATTRIBUTES_LISTS_H

/*
** List Items (OL & UL)
*/
class CHTMLAttr_OLStyle :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				CHTMLAttr_OLStyle() { m_Style = '1'; }
				char		m_Style;
				};

class CHTMLAttr_ULStyle :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tNumStyle { eDisc=0, eSquare, eCircle, };
				CHTMLAttr_ULStyle() { m_Style = eDisc; }
				tNumStyle		m_Style;
				};


class CHTMLAttr_LIStyle :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				};


#endif	// _HTML_ATTRIBUTES_LISTS_H
