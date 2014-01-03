#include "phHTML.h"
#include "phState.h"

CParseHTMLState::CParseHTMLState()
{
static int OptIDs[] = { 
NODE_ID_HTML,
NODE_ID_HEAD,
NODE_ID_BODY,
NODE_ID_TBODY,
//
NODE_ID_COLGROUP, 
NODE_ID_DD, 
NODE_ID_DT, 
NODE_ID_LI, 
NODE_ID_OPTION, 
NODE_ID_P,
NODE_ID_TD,
NODE_ID_TFOOT,
NODE_ID_TH,
NODE_ID_THEAD,
NODE_ID_TR,
};
size_t i;

	for(i=0;i<NODE_ID_MAX;i++)
		{
		m_TagIsOpt[i] = false;
		m_OpenTagCount[i] = 0;
		}

	for(i=0;i<sizeof(OptIDs)/sizeof(OptIDs[0]);i++)
		m_TagIsOpt[OptIDs[i]] = true;
	//
	m_iHTML_Optionals = 0;
	m_bPreFormatted = false;
}
