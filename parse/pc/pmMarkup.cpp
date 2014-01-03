#include "pmMarkup.h"
#include <ctype.h>
#include <string.h>

bool CParseMarkupNode::IsWS(char c)
{
	if (c == ' '  || c == '\t')	return true;
	if (c == '\r' || c == '\n')	return true;
	return false;
}

int CParseMarkupNode::SkipWS(CBDParser *pParser)
{
char c;
int cont;

	do
		{
		if ((cont = pParser->ReadChar(&c)))
			{
			if (!IsWS(c))	
				return pParser->UngetChar();
			}
		}
	while(cont);
	//
	return 0;
}

int CParseMarkupNode::GetWS(CBDParser *pParser, CBDString &str)
{
char c;
int cont;

	do
		{
		if ((cont = pParser->ReadChar(&c)))
			{
			if (IsWS(c))	
				str += c;
			else
				return pParser->UngetChar();
			}
		}
	while(cont);
	//
	return 0;
}

int CParseMarkupNode::GetQuotedText(CBDParser *pParser, CBDString &str, char cQuote)
{
char c;

	// Read up to (but ignoring) the final quote labelled as 'cQuote'
	// If there is no quote character, read until whitespace (to indicate break
	// in attributes), or end tag.
	while(pParser->ReadChar(&c))
		{
		if (!cQuote && IsWS(c))		return 1;
		if (cQuote && c == cQuote)	return 1;
		if (c == ML_END_TAG)		{ pParser->UngetChar(); return 1; }

		str += c;
		}

	return 0;	// EOF
}

int CParseMarkupNode::GetName(CBDParser *pParser, CBDString &str, bool bFirstCharacterRead/*=false*/)
{
char c;
bool bFirstCharacter = !bFirstCharacterRead;

	while(pParser->ReadChar(&c))
		{
		if (IsWS(c))	return 1;
		//
		if (bFirstCharacter)
			{
			if (!isalpha(c))	
				return pParser->UngetChar();
			}
		else
			{
			if (!isalnum(c) && c!='_' && c!='-' && c!=':')	
				return pParser->UngetChar();
			}
		//
		str += c;
		bFirstCharacter = false;
		}
	//
	return 0;
}

int CParseMarkupNode::GetCData(CBDParser *pParser, CBDString &str, bool bCompressWS/*=true*/)
{
char c;
bool bLastCharWasWS=false;
int cont, idx=-1;

	if (str.Length() && IsWS(str[0]))
		bLastCharWasWS = true;
	//
	do
		{
		if ((cont = pParser->ReadChar(&c)))
			{
			if (c == '<')	
				{
				return pParser->UngetChar();
				}
			else
				{
				if (IsWS(c) && bCompressWS)
					{
					if (!bLastCharWasWS)
						str += ' ';
					bLastCharWasWS = true;
					}
				else
					{
					str += c;
					bLastCharWasWS = false;
					}
				//
				if (c == '&')
					idx = str.Length()-1;
				else if ((c == ';' || IsWS(c)) && idx!=-1)	// end of possible entity string
					{
					ExpandEntities(str, idx, str.Length()-idx);
					idx = -1;
					}
				}
			}
		}
	while(cont);
	//
	return 0;
}

int CParseMarkupNode::ExpandEntities(CBDString &str, int idx, int len)
{
static char *pEntities[] = {
"amp", "&",
"lt", "<",	"gt", ">",
};
char *pText = &str[idx+1];
size_t i;

	if (len<3)	return 0;	// just an '&'
	len-=2;
	for(i=0;i<sizeof(pEntities)/sizeof(pEntities[0]);i+=2)
		{
		if (strnicmp(pText, pEntities[i], len)==0)
			{
			str.Left(idx);
			str += pEntities[i+1];
			}
		}

	return 0;
}

