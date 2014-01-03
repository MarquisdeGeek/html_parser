#ifndef _HTML_ELEMENTS_H
#define _HTML_ELEMENTS_H

/*
** All element classes can be included by include this single file
*/
#include "pCData.h"
#include "pDTD.h"
#include "pTextMarkup.h"		// ids=001-029
#include "pDocument.h"			// ids=030-034
#include "pLinks.h"				// ids=035-039
#include "pImages.h"			// ids=040-044
#include "pObject.h"			// ids=045-049
#include "pTextStyle.h"			// ids=050-064
#include "pLists.h"				// ids=065-074
#include "pForms.h"				// ids=080-099
#include "pTables.h"			// ids=100-114
#include "pFrames.h"			// ids=115-119
#include "pHead.h"				// ids=120-124

/*
** Global function, to construct an appropriate class for the name element tag
*/
CHTMLElement	*htmlCreateElement(CBDString &str);
//
int				htmlGetTagID(const char *pName);

#endif	// _HTML_ELEMENTS_H
