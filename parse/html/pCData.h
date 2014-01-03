#ifndef _HTML_ELEMENT_CDATA_H
#define _HTML_ELEMENT_CDATA_H

class CHTMLElement_CData : public CHTMLElement {
		DECLARE_ELEMENT();
		private:
			CBDString	m_String;
		public:
			virtual int		ParseAttr(CBDString &attr, CBDString &val);
			virtual int		GetNumAttr(void) { return 0; }
					void	SetCData(CBDString &str);
					void	SetCData(const char *pStr);
					char *	GetString(void);
			};

/*
** Global creation function
**	It mirrors the working of element tags, but has no real code inside, since
**	all CDATA elements, are CDATA.
*/
CHTMLElement *htmlCreateCData(void);


#endif	// _HTML_ELEMENT_CDATA_H
