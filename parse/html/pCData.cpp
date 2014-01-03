#include "../cmn/BDString.h"
#include "../cmn/BDParser.h"
#include "phHTML.h"

IMPLEMENT_ELEMENT(CHTMLElement_CData,	"CData",	NODE_ID_NULL, NODE_FLG_CDATA);


CHTMLElement *htmlCreateCData(void)
{
	return (CHTMLElement *)new CHTMLElement_CData;
}

int	CHTMLElement_CData::ParseAttr(CBDString &attr, CBDString &val)
{
	attr=attr; val=val;
	return 0;
}

void CHTMLElement_CData::SetCData(CBDString &str)
{ 
	m_String = str;
}

void CHTMLElement_CData::SetCData(const char *pStr)
{ 
	m_String = pStr;
}

char *CHTMLElement_CData::GetString(void)
{ 
	return (char *)m_String.GetString();
}

ATTRINFO_BEGIN(CHTMLElement_CData);
ATTRINFO_NULL;
ATTRINFO_END();

