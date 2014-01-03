#include "../cmn/BDString.h"
#include "../cmn/BDTypes.h"
#include "../pc/pmAttrHelpers.h"
#include "pCommon.h"
#include "pAttrFrames.h"

static ATTR_REMAP arScroll[] = {
"yes",	CHTMLAttr_FrameScroll::eYes,
"no",	CHTMLAttr_FrameScroll::eNo,
"auto",	CHTMLAttr_FrameScroll::eAuto,
#if PARSE_LENIENT_SPELLING
"true",	CHTMLAttr_FrameScroll::eYes,
"false",CHTMLAttr_FrameScroll::eNo,
#endif
};

int CHTMLAttr_FrameScroll::ParseAttr(CBDString *pAttr, CBDString *pVal)
{
int iVal;

	m_bSpecified = true;
	if (ahParseAttrRemaps(&iVal, *pVal, &arScroll[0], sizeof(arScroll)/sizeof(arScroll[0])))
		m_Scroll = (tScrolling)iVal;
	else
		return ATTR_PARSE_INVALID_ATTR;

	return ATTR_PARSE_SUCCESS;
}

int	CHTMLAttr_FrameScroll::GetAttrValue(int idx, CBDString *pVal)
{
	return ahGetAttrRemaps(*pVal, (int)m_Scroll, &arScroll[0], sizeof(arScroll)/sizeof(arScroll[0]))?1:0;
}
