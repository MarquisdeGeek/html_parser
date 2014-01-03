#ifndef _PM_ATTRHELPERS_H
#define _PM_ATTRHELPERS_H


typedef struct sAttrRemap {
		const char *pName;
		int			iEnumValue;
		} ATTR_REMAP;

bool ahParseAttrRemaps(int *pVal, const CBDString &str, const ATTR_REMAP *pRemap, int iRemapSize);
bool ahGetAttrRemaps(CBDString &str, const int iVal, const ATTR_REMAP *pRemap, int iRemapSize);

#endif	// _PM_ATTRHELPERS_H
