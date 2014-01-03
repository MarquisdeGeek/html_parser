#include "../cmn/BDTypes.h"
#include "../cmn/BDString.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pmAttrHelpers.h"

bool ahParseAttrRemaps(int *pVal, const CBDString &str, const ATTR_REMAP *pRemap, int iRemapSize)
{
	for(int i=0;i<iRemapSize;i++)
		if (str == pRemap[i].pName)
			{
			*pVal = pRemap[i].iEnumValue;
			return true;
			}
	//
	return false;
}

bool ahGetAttrRemaps(CBDString &str, const int iVal, const ATTR_REMAP *pRemap, int iRemapSize)
{
	for(int i=0;i<iRemapSize;i++)
		if (iVal == pRemap[i].iEnumValue)
			{
			str = pRemap[i].pName;
			return true;
			}
	//
	return false;
}

