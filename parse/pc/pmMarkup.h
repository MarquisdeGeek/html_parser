#ifndef _BD_PARSER_MARKUP_H
#define _BD_PARSER_MARKUP_H

#include "../cmn/BDString.h"
#include "../cmn/BDParser.h"

#define NODETYPE_ML		 FOURCC('M','L',0,0)

/*
**
*/
#define ML_START_TAG				'<'
#define ML_END_TAG					'>'
#define ML_END_SLASH				'/'
#define ML_DTD						'!'
#define ML_INSTRUCTION				'?'
#define ML_SINGLE_QUOTE				'\''
#define ML_DOUBLE_QUOTE				'\"'

class CParseMarkupNode : public CParseNode {
	public:
		virtual tULONG		GetNodeType(void) { return NODETYPE_ML; }
	private:
	protected:
		// General helper routines for standard markup languages
		bool		IsWS(char c);
		int			SkipWS(CBDParser *pParser);

		int			GetWS(CBDParser *pParser, CBDString &str);
		int			GetCData(CBDParser *pParser, CBDString &str, bool bCompressWS=true);
		int			GetName(CBDParser *pParser, CBDString &str, bool bFirstCharacterAlreadyRead=false);
		int			GetQuotedText(CBDParser *pParser, CBDString &str, char cQuote);

		int			ExpandEntities(CBDString &str, int idx, int len);
		};


#endif	// _BD_PARSER_MARKUP_H
