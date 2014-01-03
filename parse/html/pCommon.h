#ifndef _PARSE_HTML_COMMON_H
#define _PARSE_HTML_COMMON_H

/*
** The common HTML features for attributes, elements and entities.
** All the data represented here is static for the class.

** Everything includes this somewhere along the line.
*/
#define PARSE_SLIMLINE						0
#define PARSE_PIXELS_ALLOW_PERCENTILES		1	//to permit widths in tables with % (whereas the spec says not)
#define PARSE_LENIENT_SPELLING				1	//to permit 'middle' instead of center in halign and similar monostrosities :)

// TODO: Extend PARSE_LENIENT_SPELLING to allow variations of colour in ATTRINFO_ATTR. 
// (At the moment, each ATTRINFO_ATTR is treated like a new attrib, we need one that
// acts as a synonym)

/*
**
*/
#define HTML_START_TAG					ML_START_TAG
#define HTML_END_TAG					ML_END_TAG
#define HTML_END_SLASH					ML_END_SLASH
#define HTML_DTD						ML_DTD
#define HTML_INSTRUCTION				ML_INSTRUCTION
#define HTML_SINGLE_QUOTE				ML_SINGLE_QUOTE
#define HTML_DOUBLE_QUOTE				ML_DOUBLE_QUOTE

/*
** Flags, describing the node type
*/
#define NODE_FLG_NULL					0x0000
#define NODE_FLG_ENDTAG_FORBIDDEN		0x0001
#define NODE_FLG_ENDTAG_OPTIONAL		0x0002
#define NODE_FLG_BOTHTAGS_OPTIONAL		0x0004
#define NODE_FLG_INSTRUCTION			0x0010
#define NODE_FLG_DTD					0x0020		// only the '<-- -->' comment is supported in HTML, though

#define NODE_FLG_CDATA					0x0040
#define NODE_FLG_ELEMENT				0x0080

#define NODE_FLG_DEPRECATED				0x0100

#define NODE_FLG_ROOTNODE				0x8000

/*
** Each element is given a unique ID for quick determination of the class type
** TODO: Look for C++ language feature to implement this nicer
*/
#define NODE_ID_NULL						 0	/* For non-tags */


/*
** GetAttrInfo return values
*/
#define ATTR_PARSE_SUCCESS			1
#define ATTR_PARSE_INVALID_NAME		0
#define ATTR_PARSE_INVALID_ATTR		-1
#define ATTR_PARSE_DUPLICATE_ATTR	-2

#define ATTR_GETNAME_SUCCESS		1

#define ATTR_GETVAL_SUCCESS			1

/*
** Enums for 'GetAttrInfo' to indicate which sub-functional process to execute
*/
typedef enum {
		eParseAttr,
		eGetNumAttr,
		eGetAttrName,
		eGetAttrVal,
		eIsSpecified,
		} eAttrInfo;

/*
** Helper macros to create the classes for each element
*/
#define DECLARE_BASE_ELEMENT()					\
		public:									\
			virtual int		GetID(void)=0;		\
			virtual int		GetFlags(void)=0;	\
			virtual const char	*GetName(void)=0;			

#define DECLARE_ELEMENT()										\
		public:													\
			static const char *	m_szName;						\
		private:												\
			static int			m_iID;							\
			static int			m_iFlags;						\
		public:													\
			virtual int			GetID(void)		{ return m_iID; }	\
			virtual int			GetFlags(void)	{ return m_iFlags; }\
			virtual const char	*GetName(void)	{ return m_szName; }\
			virtual int			GetAttrInfo(int idx, CBDString *pAttr, CBDString *pVal, eAttrInfo info);
				
#define IMPLEMENT_ELEMENT(__elementclass,__elementname,__elementID,__elementFlags)											\
			const char *	__elementclass::m_szName	= __elementname;			\
			int		__elementclass::m_iID		= __elementID;				\
			int		__elementclass::m_iFlags	= __elementFlags;			
		
/*
** Helper macros to create the classes for each element
*/
#define DECLARE_ATTRIBUTE()												\
		public:															\
			virtual int		ParseAttr(CBDString *pAttr, CBDString *pVal);\
			virtual int		GetAttrValue(int idx, CBDString *pVal);	// although called 'pVal', this is actually the 'pAttr' variable. It makes more sence
																	// to call it 'val' though, since that is what's stored in it

/*
**
*/
#define DECLARE_ENTITY()											\
		public:													\
			virtual int	GetAttrInfo(int idx, CBDString *pAttr, CBDString *pVal, eAttrInfo info);

/*
** These are used for entities and elements
*/
#define ATTRINFO_BEGIN(__class)					int	__class::GetAttrInfo(int index, CBDString *pAttr, CBDString *pVal, eAttrInfo info)	\
												{ int idx=index;

#define ATTRINFO_ATTR(__name, __var)		if (idx==0) { switch(info) {	\
											case eParseAttr:	if (*pAttr == __name) { if (__var.IsSpecified()) return ATTR_PARSE_DUPLICATE_ATTR;	return	__var.ParseAttr(pAttr,pVal);   } break;		\
											case eGetAttrName:	*pAttr=__name;				return 1;	\
											case eGetAttrVal:	return __var.GetAttrValue(idx,pAttr);	\
											case eIsSpecified:	return __var.IsSpecified(idx);			\
											case eGetNumAttr:	idx-=__var.GetNumAttr()-1;	break;	\
											}} if (info != eParseAttr)		idx--;
										
#define ATTRINFO_ENTITY(__name, __var)		if (idx<__var.GetNumAttr()) { switch(info) {	\
											case eParseAttr:	{ int rt; if ((rt=__var.ParseAttr(pAttr,pVal)))	return rt; } break;		\
											case eGetAttrName:	return __var.GetAttrName(idx,pAttr);	\
											case eGetAttrVal:	return __var.GetAttrValue(idx,pAttr);	\
											case eIsSpecified:	return __var.IsSpecified(idx);			\
											case eGetNumAttr:	idx-=__var.GetNumAttr();	break;	\
											}} if (info != eParseAttr && info != eGetNumAttr)		idx-=__var.GetNumAttr();


#define ATTRINFO_NULL							index=index; pVal=pVal; pAttr=pAttr; info=info

#define ATTRINFO_END()							if (info == eGetNumAttr)	return (-idx)-1; else return 0; }

/*
** Super class - everything inherits from this
*/
class CBDParser;
class CParseHTMLNode;

class CHTMLBase {
		public:
				virtual ~CHTMLBase() {}
				int		m_iLine, m_iCol;	// only public so the parser can write to them
				
				virtual int	GetAttrInfo(int idx, CBDString *pAttr, CBDString *pVal, eAttrInfo info) { idx=idx; pAttr=pAttr; pVal=pVal; info=info; return 0; }

				virtual int	ParseAttr(CBDString *pAttr, CBDString *pVal){ return GetAttrInfo(0, pAttr, pVal, eParseAttr); }
				virtual int GetNumAttr(void)							{ return GetAttrInfo(-1, NULL, NULL, eGetNumAttr); }
				virtual int	GetAttrName(int idx, CBDString *pAttr)		{ return GetAttrInfo(idx, pAttr, pAttr/*unused*/, eGetAttrName); }
				virtual int	GetAttrValue(int idx, CBDString *pAttr)		{ return GetAttrInfo(idx, pAttr, pAttr/*unused*/, eGetAttrVal); }
				virtual bool IsSpecified(int idx)						{ return GetAttrInfo(idx, NULL, NULL, eIsSpecified)?true:false; }
						bool IsAttrLegal(CBDString *pAttr);
				//
				inline int GetLine(void) { return m_iLine; }
				inline int GetCol(void) { return m_iCol; }
				};
		
/*
** Base Classes
*/
class CHTMLElement : public CHTMLBase {
				DECLARE_BASE_ELEMENT();
		private:
				bool			m_bValid;
		public:
				CHTMLElement() { m_bValid = false; }
				size_t			m_UserData;

		inline	void			SetValid(bool v) { m_bValid = v; }
		inline	bool			IsValid(void) { return m_bValid; }

		virtual bool			CloseTagAfterOpen(void);
		virtual bool			ValidateTree(CBDParser *pParser, CParseHTMLNode *pThisEle);		// return true if this is handled manually
		virtual bool			IsChildValid(CHTMLElement *pEle);
		virtual CParseHTMLNode *GetTagToClose(CBDParser *pParser, CParseHTMLNode *pPreviouslyOpenTag, int id) { return NULL; }	// certain optional elements should overide this
		virtual bool			ValidateRequiredAttrs(CBDParser *pParser);
				bool			AtLeastOneID(CParseHTMLNode *pThisEle, int id);
				bool			AtLeastOneIDOf2(CParseHTMLNode *pThisEle, int id, int id2);

		};


class CHTMLAttribute : public CHTMLBase {
			protected:
						bool m_bSpecified;

			public:
						CHTMLAttribute()			{ m_bSpecified = false; }

				virtual int GetNumAttr()			{ return 1; }
				virtual int GetAttrName(int idx, CBDString *pAttr) { idx=idx; pAttr=pAttr; return 0; }		/* Nonsense, since the attrib holds only data value, not the name */
				virtual bool IsSpecified(int idx=0)	{ idx=idx; return m_bSpecified; }
				};

class CHTMLEntity : public CHTMLBase {
				};


#endif	// _PARSE_HTML_COMMON_H
