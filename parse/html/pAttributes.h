#ifndef _HTML_ATTRIBUTES_H
#define _HTML_ATTRIBUTES_H

#include "pAttrLists.h"
#include "pAttrForms.h"
#include "pAttrTables.h"
#include "pAttrFrames.h"


class CHTMLAttr_CData : public CHTMLAttribute {		// According to RFC2045
			DECLARE_ATTRIBUTE();
			public:
				CBDString		m_Data;
				};

class CHTMLAttr_Length : public CHTMLAttribute {	
			DECLARE_ATTRIBUTE();
			public:
				CHTMLAttr_Length() {  m_Pixels=1; m_bInPercent=false; }
				int			m_Pixels;
				bool		m_bInPercent;		
				};

class CHTMLAttr_MultiLength : public CHTMLAttr_Length {		// note inheritance
			DECLARE_ATTRIBUTE();
			public: 
				CHTMLAttr_MultiLength() { m_Relative=0; }
				int			m_Relative;		// -1, 0, +1
				};

class CHTMLAttr_Dir : public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				CHTMLAttr_Dir() { m_bLTR=true; }
				bool			m_bLTR;
				};

/*
** Unknown Names
*/
class CHTMLAttr_ID :	public CHTMLAttr_CData { };
class CHTMLAttr_IDREF :	public CHTMLAttr_CData { };
class CHTMLAttr_IDREFS :	public CHTMLAttr_CData { };

/*
** Imported Names
*/
class CHTMLAttr_ContentType :	public CHTMLAttr_CData { };
class CHTMLAttr_ContentTypes :	public CHTMLAttr_CData { };
class CHTMLAttr_Charset :		public CHTMLAttr_CData { };
class CHTMLAttr_Charsets :		public CHTMLAttr_CData { };
class CHTMLAttr_LinkTypes :		public CHTMLAttr_CData { };
class CHTMLAttr_MediaDesc :		public CHTMLAttr_CData { };
class CHTMLAttr_URL :			public CHTMLAttr_CData { };
class CHTMLAttr_DateTime :		public CHTMLAttr_CData { };
class CHTMLAttr_Script :		public CHTMLAttr_CData { };
class CHTMLAttr_FrameTarget :	public CHTMLAttr_CData { };
class CHTMLAttr_Text :			public CHTMLAttr_CData { };
class CHTMLAttr_Name :			public CHTMLAttr_CData { };
class CHTMLAttr_Version :		public CHTMLAttr_CData { public: CHTMLAttr_Version(); };

class CHTMLAttr_LanguageCode :	public CHTMLAttribute {		// According to RFC1766
			DECLARE_ATTRIBUTE();
			public:
				CBDString		m_Code;
				};

class CHTMLAttr_Character :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				CHTMLAttr_Character() { m_Char = '\0'; }
				char			m_Char;
				};

class CHTMLAttr_Number :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				CHTMLAttr_Number() { m_Num = 0; }
				tLONG			m_Num;
				};

class CHTMLAttr_Boolean :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				CHTMLAttr_Boolean() { m_Val = false; }
				bool			m_Val;
				};

/*
** Parameter Entities
*/
class CHTMLAttr_Color :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				CHTMLAttr_Color() { m_Color = 0L; }
				tULONG			m_Color;
				};

class CHTMLAttr_Align :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tAlignment { eLeft=0, eRight, eCenter, eJustify, };
				CHTMLAttr_Align() { m_Align = eLeft; }
				tAlignment		m_Align;
				};

/*
** Anchor
*/
class CHTMLAttr_Shape :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				typedef enum { eDefault=0, eRect, eCircle, ePoly, } tShape;
				CHTMLAttr_Shape() { m_Shape = eDefault; }
				tULONG			m_Shape;
				};

class CHTMLAttr_Coords :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				CBDString		m_CoordList;		// comma separated list of numbers 
				};

class CHTMLAttr_AccessKey :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				CHTMLAttr_AccessKey() { m_Key = 0; }
				char			m_Key;
				};

/*
** IMG
*/
class CHTMLAttr_MultiLengths :		public CHTMLAttr_CData { };

#if PARSE_PIXELS_ALLOW_PERCENTILES
class CHTMLAttr_Pixels :			public CHTMLAttr_Length { };
#else
class CHTMLAttr_Pixels :			public CHTMLAttr_Number { };
#endif

class CHTMLAttr_IAlign :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tIAlign { eTop=0, eMiddle, eBottom, eLeft, eRight, };
				CHTMLAttr_IAlign() { m_Align = eLeft; }
				tIAlign			m_Align;
				};
/*
** HR - only support 3 alignment options
*/
class CHTMLAttr_HRAlign :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tAlignment { eLeft=0, eRight, eCenter, };
				CHTMLAttr_HRAlign() { m_Align = eLeft; }
				tAlignment		m_Align;
				};

/*
** BR 
*/
class CHTMLAttr_BRClear :		public CHTMLAttribute {
			DECLARE_ATTRIBUTE();
			public:
				enum tAlignment { eNone=0, eLeft, eRight, eAll, };
				CHTMLAttr_BRClear() { m_Clear = eNone; }
				tAlignment		m_Clear;
				};

#endif	// _HTML_ATTRIBUTES_H

