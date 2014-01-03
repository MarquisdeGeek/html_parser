#include "../cmn/BDString.h"
#include "../cmn/BDParser.h"
#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_DTD,	"DTD",	NODE_ID_NULL, HTML_DTD);


CHTMLElement *htmlCreateDTD(void)
{
	return (CHTMLElement *)new CHTMLElement_DTD;
}

int	CHTMLElement_DTD::ParseAttr(CBDString &attr, CBDString &val)
{
	attr=attr; val=val;
	return 0;
}

void CHTMLElement_DTD::SetString(CBDString &str)
{ 
	m_String = str;
}

char *CHTMLElement_DTD::GetString(void)
{ 
	return (char *)m_String.GetString();
}

ATTRINFO_BEGIN(CHTMLElement_DTD);
ATTRINFO_NULL;
ATTRINFO_END();

