#include "cmn/BDTypes.h"
#include "cmn/BDString.h"
#include "cmn/BDDiskFile.h"
#include "beautify.h"
#include "html/phHTML.h"

CBeautyConfig::CBeautyConfig()
{
	for(int i=0;i<NODE_ID_MAXIMUM;i++)
		{
		if (0)
			;
		else if (i==NODE_ID_SPAN)
			DefaultCmdStr(&m_cmdTag[i]);
		else if (i==NODE_ID_UL || i==NODE_ID_OL || i==NODE_ID_MAP || i==NODE_ID_IMG)
			DefaultListCmdStr(&m_cmdTag[i]);
		else if (i==NODE_ID_LI || i==NODE_ID_DT || i==NODE_ID_AREA)
			DefaultNewlineCmdStr(&m_cmdTag[i]);
		else if (i==NODE_ID_SCRIPT || i==NODE_ID_TITLE)
			DefaultNewlineCmdStr(&m_cmdTag[i]);
		else if (i==NODE_ID_META || i==NODE_ID_BASE || i==NODE_ID_STYLE || i==NODE_ID_ISINDEX)
			DefaultNewlineCmdStr(&m_cmdTag[i]);
		else if (i>=NODE_ID_H1 && i<=NODE_ID_H6)
			DefaultInlineCmdStr(&m_cmdTag[i]);
		else if (i==NODE_ID_BR || i==NODE_ID_HR)
			DefaultNewlineCmdStr(&m_cmdTag[i]);
		else if (i==NODE_ID_TEXTAREA || i==NODE_ID_PRE)
			DefaultInlineCmdStr(&m_cmdTag[i]);
		else if (i==NODE_ID_P)
			DefaultListCmdStr(&m_cmdTag[i]);
		else if (entIsInline(i))
			DefaultInlineCmdStr(&m_cmdTag[i]);
		else
			DefaultCmdStr(&m_cmdTag[i]);
		}

	//
	m_ShowAllAttribs = false;
	m_WordWrapCData = false;
	m_WordWrapWidth = 60;
}

#define INSTR(c,p)	pCmd->cmd[i].cCommand=c; pCmd->cmd[i].cParam=p; i++;


void CBeautyConfig::DefaultListCmdStr(CCommandString *pCmd)
{
int i=0;

	INSTR(BDB_PRINT, BDB_PRINT_NEWLINE);
	INSTR(BDB_PRINT, BDB_PRINT_TAB);
	INSTR(BDB_PRINT, BDB_PRINT_STARTTAG);
	INSTR(BDB_PRINT, BDB_PRINT_NEWLINE);
		INSTR(BDB_TAB_INC, 1);
		INSTR(BDB_PRINT, BDB_PRINT_TAB);
		INSTR(BDB_PRINT, BDB_PRINT_SUBTREE);
		INSTR(BDB_PRINT, BDB_PRINT_NEWLINE);
		INSTR(BDB_TAB_DEC, 1);
	INSTR(BDB_PRINT, BDB_PRINT_TAB);
	INSTR(BDB_PRINT, BDB_PRINT_ENDTAG);
	INSTR(BDB_PRINT, BDB_PRINT_NEWLINE);
	INSTR(BDB_PRINT, BDB_PRINT_TAB);
	INSTR(BDB_END, 0);

	pCmd->sAttrFormat = " %s = '%s'";	// note the leading space
}

void CBeautyConfig::DefaultCmdStr(CCommandString *pCmd)
{
int i=0;

	INSTR(BDB_PRINT, BDB_PRINT_STARTTAG);
	INSTR(BDB_PRINT, BDB_PRINT_NEWLINE);
		INSTR(BDB_TAB_INC, 1);
		INSTR(BDB_PRINT, BDB_PRINT_TAB);
		INSTR(BDB_PRINT, BDB_PRINT_SUBTREE);
		INSTR(BDB_PRINT, BDB_PRINT_NEWLINE);
		INSTR(BDB_TAB_DEC, 1);
	INSTR(BDB_PRINT, BDB_PRINT_TAB);
	INSTR(BDB_PRINT, BDB_PRINT_ENDTAG);
	INSTR(BDB_PRINT, BDB_PRINT_NEWLINE);
	INSTR(BDB_PRINT, BDB_PRINT_TAB);
	INSTR(BDB_END, 0);

	pCmd->sAttrFormat = " %s = '%s'";	// note the leading space
}

void CBeautyConfig::DefaultInlineCmdStr(CCommandString *pCmd)
{
int i=0;

	INSTR(BDB_PRINT, BDB_PRINT_STARTTAG);
	INSTR(BDB_PRINT, BDB_PRINT_SUBTREE);
	INSTR(BDB_PRINT, BDB_PRINT_ENDTAG);
	INSTR(BDB_END, 0);

	pCmd->sAttrFormat = " %s = '%s'";	// note the leading space
}


void CBeautyConfig::DefaultNewlineCmdStr(CCommandString *pCmd)
{
int i=0;

	INSTR(BDB_PRINT, BDB_PRINT_STARTTAG);
	INSTR(BDB_PRINT, BDB_PRINT_SUBTREE);
	INSTR(BDB_PRINT, BDB_PRINT_ENDTAG);
	INSTR(BDB_PRINT, BDB_PRINT_NEWLINE);
	INSTR(BDB_PRINT, BDB_PRINT_TAB);
	INSTR(BDB_END, 0);

	pCmd->sAttrFormat = " %s = '%s'";	// note the leading space
}


#undef INSTR
