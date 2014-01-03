#ifndef _HTML_ATTRIBUTES_FRAMES_H
#define _HTML_ATTRIBUTES_FRAMES_H


class CHTMLAttr_FrameScroll :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tScrolling { eYes=0, eNo, eAuto, };
				CHTMLAttr_FrameScroll() { m_Scroll = eYes; }
				tScrolling		m_Scroll;
				};

#endif	// _HTML_ATTRIBUTES_FRAMES_H
