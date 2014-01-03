#ifndef _HTML_ELEMENT_DTD_H
#define _HTML_ELEMENT_DTD_H

class CHTMLElement_DTD : public CHTMLElement {
		DECLARE_ELEMENT();
		private:
			CBDString	m_String;
		public:
			virtual int		ParseAttr(CBDString &attr, CBDString &val);
			virtual int		GetNumAttr(void) { return 0; }
					void	SetString(CBDString &str);
					char *	GetString(void);
			};

/*
** Global creation function
**	It mirrors the working of element tags, but has no real code inside, since
**	all DTD elements, are plain text copies.
*/
CHTMLElement *htmlCreateDTD(void);


#endif	// _HTML_ELEMENT_DTD_H
