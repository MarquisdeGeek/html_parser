#include "../cmn/BDString.h"
#include "../cmn/BDTypes.h"
#include "pCommon.h"
#include "pAttributes.h"
#include "pEntities.h"

/*
** Parameter Entities
*/
ATTRINFO_BEGIN(CHTMLEntity_BodyColors);
	ATTRINFO_ATTR("bgcolor", m_ColBg);
	ATTRINFO_ATTR("text", m_ColText);
	ATTRINFO_ATTR("link", m_ColLink);
	ATTRINFO_ATTR("vlink", m_ColVLink);
	ATTRINFO_ATTR("alink", m_ColALink);
ATTRINFO_END();

/*
** Generic Attributes
*/
ATTRINFO_BEGIN(CHTMLEntity_CoreAttrs);
	ATTRINFO_ATTR("id", m_ID);
	ATTRINFO_ATTR("class", m_Class);
	ATTRINFO_ATTR("style", m_Style);
	ATTRINFO_ATTR("title", m_Title);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLEntity_i18n);
	ATTRINFO_ATTR("dir", m_DirLTR);
	ATTRINFO_ATTR("lang", m_LangCode);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLEntity_Events);
	ATTRINFO_ATTR("onClick",	m_OnClick);
	ATTRINFO_ATTR("onDblClick", m_OnDoubleClick);
	ATTRINFO_ATTR("onMouseDown", m_OnMouseDown);
	ATTRINFO_ATTR("onMouseUp",	m_OnMouseUp);
	ATTRINFO_ATTR("onMouseOver",m_OnMouseOver);
	ATTRINFO_ATTR("onMouseMove",m_OnMouseMove);
	ATTRINFO_ATTR("onMouseOut", m_OnMouseOut);
	ATTRINFO_ATTR("onKeyPress", m_OnKeyPress);
	ATTRINFO_ATTR("onKeyDown",	m_OnKeyDown);
	ATTRINFO_ATTR("onKeyUp",	m_OnKeyUp);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLEntity_Attrs);
	ATTRINFO_ENTITY("", m_CoreAttrs);
	ATTRINFO_ENTITY("", m_i18n);
	ATTRINFO_ENTITY("", m_Events);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLEntity_Align);
	ATTRINFO_ATTR("align", m_Align);
ATTRINFO_END();

/*
** from Tables
*/
CHTMLEntity_CellHAlign::CHTMLEntity_CellHAlign()
{
	m_AlignmentChar.m_Char = '\0';
	m_AlignmentCharOffset.m_Pixels = 0;
	m_AlignmentCharOffset.m_bInPercent = false;
}

ATTRINFO_BEGIN(CHTMLEntity_CellHAlign);
	ATTRINFO_ATTR("align",	m_Align);
	ATTRINFO_ATTR("char",	m_AlignmentChar);
	ATTRINFO_ATTR("charoff",	m_AlignmentCharOffset);
ATTRINFO_END();

ATTRINFO_BEGIN(CHTMLEntity_CellVAlign);
	ATTRINFO_ATTR("valign",	m_VAlign);
ATTRINFO_END();

