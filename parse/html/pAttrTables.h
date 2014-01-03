#ifndef _HTML_ATTRIBUTES_TABLES_H
#define _HTML_ATTRIBUTES_TABLES_H


class CHTMLAttr_TFrame :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tFrameStyle { eVoid=0, eAbove, eBelow, eHsides, 
									eLhs, eRhs, vSides, eBox, eBorder,
									};
				CHTMLAttr_TFrame() { m_Style = eBox; }
				tFrameStyle		m_Style;
				};

class CHTMLAttr_TRules :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tTRules { eNone=0, eGroups, eRows, eCols, eAll, };
				CHTMLAttr_TRules() { m_Rules = eAll; }
				tTRules			m_Rules;
				};


class CHTMLAttr_CAlign :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tCAlign { eTop=0, eBottom, eLeft, eRight, };
				CHTMLAttr_CAlign() { m_Alignment = eTop; }
				tCAlign			m_Alignment;
				};

class CHTMLAttr_TAlign :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tTAlign { eLeft=0, eCenter, eRight, };
				CHTMLAttr_TAlign() { m_Alignment = eLeft; }
				tTAlign			m_Alignment;
				};

class CHTMLAttr_Scope :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tScope { eRow=0, eCol, eRowgroup, eColgroup, };
				CHTMLAttr_Scope() { m_Scope = eRow; }
				tScope			m_Scope;
				};

class CHTMLAttr_THAlign :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tTHAlign { eLeft=0, eCenter, eRight, eJustify, eChar};
				CHTMLAttr_THAlign() { m_Alignment = eLeft; }
				tTHAlign			m_Alignment;
				};

class CHTMLAttr_TVAlign :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tTVAlign { eTop=0, eMiddle, eBottom, eBaseline, };
				CHTMLAttr_TVAlign() { m_Alignment = eTop; }
				tTVAlign			m_Alignment;
				};


#endif	// _HTML_ATTRIBUTES_TABLES_H
