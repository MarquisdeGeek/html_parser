/*
** Entities - Used for 2nd pass, validiting the sub-tags are valid
*/
#include "phHTML.h"

/*
** TODO:
**  This is not particularly efficient. In fact, it is probably as
** inefficient as you can get!! I would prefer to store the entity
** types as a flag set inside each element, i.e.
**		m_EntityGroup = entFontStyle | entInline;
** (similar to the way isalpha() et al, work) I haven't changed it yet
** because there are other tasks that need doing.
*/

bool entIsPCData(int id)
{
	return (id == 0)?true:false;
}

bool entIsFontStyle(int id)
{
	if (id >= NODE_ID_TT && id <= NODE_ID_SMALL)	return true;
	return false;
}

bool entIsPhrase(int id)
{
	if (id >= NODE_ID_EM && id <= NODE_ID_ABBR)	return true;
	return false;
}

bool entIsSpecial(int id)
{
	if (id==NODE_ID_A || id==NODE_ID_IMG) return true;
	if (id==NODE_ID_APPLET || id==NODE_ID_OBJECT || id==NODE_ID_MAP) return true;
	if (id==NODE_ID_FONT || id==NODE_ID_BASEFONT) return true;
	if (id==NODE_ID_BR || id==NODE_ID_SCRIPT || id==NODE_ID_Q ||
		 id==NODE_ID_SUB || id==NODE_ID_SUP) return true;
	if (id==NODE_ID_SPAN || id==NODE_ID_BDO || id==NODE_ID_IFRAME) return true;
	return false;
}

bool entIsFormCtrl(int id)
{
	if (id==NODE_ID_INPUT || id==NODE_ID_SELECT || 
		id==NODE_ID_TEXTAREA || id==NODE_ID_LABEL || id==NODE_ID_BUTTON)
		return true;
	return false;
}

bool entIsInline(int id)
{
	if (entIsPCData(id))		return true;
	if (entIsFontStyle(id))		return true;
	if (entIsPhrase(id))		return true;
	if (entIsSpecial(id))		return true;
	if (entIsFormCtrl(id))		return true;
	return false;
}



bool entIsHeading(int id)
{
	if (id>=NODE_ID_H1 && id<=NODE_ID_H6) return true;
	return false;
}

bool entIsList(int id)
{
	if (id==NODE_ID_UL || id==NODE_ID_OL) return true;
	if (id==NODE_ID_DIR || id==NODE_ID_MENU) return true;
	return false;
}

bool entIsPreFormatted(int id)
{
	return (id == NODE_ID_PRE)?true:false;
}

bool entIsBlock(int id)
{
	if (entIsHeading(id))		return true;
	if (entIsList(id))			return true;
	if (entIsPreFormatted(id))	return true;
	//
	if (id==NODE_ID_P)			return true;
	if (id==NODE_ID_DL || id==NODE_ID_DIV || id==NODE_ID_CENTER)	return true;
	if (id==NODE_ID_NOSCRIPT || id==NODE_ID_NOFRAMES)	return true;
	if (id==NODE_ID_BLOCKQUOTE || id==NODE_ID_FORM || id==NODE_ID_ISINDEX)	return true;
	if (id==NODE_ID_HR || id==NODE_ID_TABLE)	return true;
	if (id==NODE_ID_FIELDSET || id==NODE_ID_ADDRESS)	return true;
	return false;
}

bool entIsFlow(int id)
{
	if (entIsBlock(id))		return true;
	if (entIsInline(id))	return true;
	return false;
}

bool entIsPreExclusion(int id)
{
	if (id==NODE_ID_IMG || id==NODE_ID_OBJECT || id==NODE_ID_APPLET)	return true;
	if (id==NODE_ID_BIG || id==NODE_ID_SMALL || id==NODE_ID_APPLET)	return true;
	if (id==NODE_ID_SUB || id==NODE_ID_SUP)	return true;
	if (id==NODE_ID_FONT || id==NODE_ID_BASEFONT)	return true;
	return false;
}

bool entIsHeadMisc(int id)
{
	if (id==NODE_ID_SCRIPT || id==NODE_ID_STYLE)	return true;
	if (id==NODE_ID_META || id==NODE_ID_LINK)	return true;
	return false;
}

bool entIsHeadContent(int id)
{
	if (id==NODE_ID_TITLE || id==NODE_ID_ISINDEX)	return true;
	if (id==NODE_ID_BASE)	return true;
	return false;
}

bool entIsHTMLContent(int id)
{
	if (id==NODE_ID_HEAD || id==NODE_ID_BODY)	return true;
	return false;
}

