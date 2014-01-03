#include "../cmn/BDString.h"
#include "../cmn/BDTypes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pCommon.h"
#include "pAttributes.h"
#include "../pc/pmAttrHelpers.h"

static ATTR_REMAP arColor[] = {
"Black",	0x000000, 
"Green",	0x008000, 
"Silver",	0xC0C0C0, 
"Lime",		0x00FF00, 
"Gray",		0x808080, 
"Olive",	0x808000, 
"White",	0xffffff, 
"Yellow",	0xffff00, 
"Maroon",	0x800000, 
"Navy",		0x000080, 
"Red",		0xff0000, 
"Blue",		0x0000ff, 
"Purple",	0x800080, 
"Teal",		0x008080, 
"Fuchsia",	0xff00ff, 
"Aqua",		0x00ffff,
#if PARSE_LENIENT_SPELLING
"Grey",		0x808080,
#endif
};

static int hexVal(char c)
{
	if (c>='A' && c<='F')
		return (c-'A')+0xA;
	if (c>='a' && c<='f')
		return (c-'a')+0xA;
	if (c>='0' && c<='9')
		return (c-'0');
	//
	return 0;	// INVALID CHAR	
}

int CHTMLAttr_Color::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int rt = ATTR_PARSE_SUCCESS;
int iVal;

	if (ahParseAttrRemaps(&iVal, *pVal, &arColor[0], sizeof(arColor)/sizeof(arColor[0])))
		{
		m_Color = (tULONG)iVal;
		}
	else
		{
		const char *p = pVal->GetString();
		int len = pVal->Length();

		if (*p == '#')	p++, len--;

		if (len > 6)	len = 6;
		m_Color = 0;
		for(int i=0;i<len;i++,p++)
			{
			m_Color <<= 4;
			m_Color += hexVal(*p);
			}
		}
	//
	m_bSpecified = true;
	return rt;
}

int	CHTMLAttr_Color::GetAttrValue(int idx, CBDString *pVal)
{
	idx=idx;

	// Try and find a textual description for this colour
	if (!ahGetAttrRemaps(*pVal, (int)m_Color, &arColor[0], sizeof(arColor)/sizeof(arColor[0])))
		{
		char str[9];

			sprintf(str, "#%.6x", (unsigned int)m_Color);
			*pVal = str;

		return ATTR_PARSE_SUCCESS;
		}
	//
	return ATTR_PARSE_INVALID_ATTR;
}
