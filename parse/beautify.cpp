/*
 * beautifyi.c - An HTML Beautifier, demonstrating the HTML parser library
 * Version 0.9
 *
 *  AUTHOR: Steven Goodwin (StevenGoodwin@gmail.com)
 *          Copyright 2000-2008, Steven Goodwin
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <ctype.h>
#include "cmn/BDTypes.h"
#include "cmn/BDParser.h"
#include "cmn/BDDiskFile.h"
#include "cmn/BDMemFile.h"
#include "html/phHTML.h"
#include "MyErrorList.h"
#include "beautify.h"

#define PARSE_FROM_MEMORY		1
/*
The command string (is given in setup files) is very simple. It supports a number
of micro instructions (listed below) which are compiled into a byte-code and executed
for each node of the tree. Only the layout of the attribute pairs supports arbitary strings,
i.e. attr="%s = '%s'". The maximum number of commands per string is defined with 'BDB_MAX_COMMAND_LENGTH'

Code

0x0000	Terminate instruction list

0x1000	Mask for 'print' operations, specified with '?'
0x1001		?		Print start tag and attribute list
0x1002		?/		Print end tag (if valid)
0x1003		?sub	Print the sub-tree; the data between the tags
0x1004		?tab	Print the number of tabs specified by 'variable' tab
0x1005		?CR		Print CR/LF
0x10--		?[--]	Print character. Uses character of target machine. (supports ?\t etc for single tab, etc)

0x2000	Mask for 'tab' operations: Absolute set.
0x2000		tab=0	Set current tab width (absolutely) to 0 (rare)
0x2001		tab=1	Set current tab width (absolutely) to 1..etc...

0x3000	Mask for 'tab' operations: Increment
0x3001		tab=1	Increment tab width by 1
0x3002		tab=2	Increment tab width by 2..etc...

0x4000	Mask for 'tab' operations: Decrement
0x4001		tab=1	Decrement tab width by 1
0x4002		tab=2	Decrement tab width by 2..etc...


*/
CBeautyState::CBeautyState() 
{
	m_iTab = 0; 
	m_bPreformatted = false;
}

void OutputWordWrapString(const char *pStr, const CBeautyConfig *pConfig, CBeautyState *pState)
{
	if (pConfig->m_WordWrapCData && pState->m_bPreformatted==false)
		{
		const char *p = pStr;
		int len = strlen(p);

		while (len > pConfig->m_WordWrapWidth)
			{
			const char *p2 = p+pConfig->m_WordWrapWidth;

				while(*p2!=' ' && *p2!='\t' && p2!=p)
					--p2;

				if (p==p2)	//no spaces in entire word! Just cut it at N chars
					p2 = p+pConfig->m_WordWrapWidth;

				do
					{
					putchar(*p++);
					--len;
					}
				while(p!=p2);
				putchar('\n');
			}
		//
		printf("%s", p);
		}
	else
		{
		printf("%s", pStr);
		}
}


void OutputHTML(const CParseHTMLNode *pRoot, const CBeautyConfig *pConfig, CBeautyState *pState)
{
	if (!pRoot)	return;
	//
	if (!pRoot->m_pElement)
		{
		CBDTreeItem *p = pRoot->GetFirstChild();

		while(p)
			{
			OutputHTML((CParseHTMLNode *)p, pConfig, pState);
			p = pRoot->GetNextChild(p);
			}
		return;
		}
	//
	if (pRoot->m_pElement->GetFlags() & NODE_FLG_CDATA)
		{
		CHTMLElement_CData *pCD = (CHTMLElement_CData *)pRoot->m_pElement;
		OutputWordWrapString(pCD->GetString(), pConfig, pState);
		return;
		}
	//
	if (pRoot->m_pElement->GetFlags() & NODE_FLG_DTD)
		{
		CHTMLElement_DTD *pDTD = (CHTMLElement_DTD *)pRoot->m_pElement;
		OutputWordWrapString(pDTD->GetString(), pConfig, pState);
		return;
		}

	// Execute command string
	if (pRoot->m_pElement->GetFlags() & NODE_FLG_ELEMENT)
		{
		int id = pRoot->m_pElement->GetID();
		const CCommandString *pCmdStr = &pConfig->m_cmdTag[id];
		const BDB_COMMAND *pCurrCmd = &pCmdStr->cmd[0];
		bool bContinue=true;

		if (id == NODE_ID_PRE)		pState->m_bPreformatted = true;

		do {
			switch (pCurrCmd->cCommand)
				{
				case	BDB_END:
						bContinue = false;
						break;

				case	BDB_PRINT:
						switch(pCurrCmd->cParam)
							{
							case	BDB_PRINT_STARTTAG:
									{
									CBDString n,v;

									printf("<%s", pRoot->m_pElement->GetName());

									int attr=pRoot->m_pElement->GetNumAttr();
									for(int i=0;i<attr;i++)
										{
										if (pRoot->m_pElement->IsSpecified(i) || pConfig->m_ShowAllAttribs)
											{
											pRoot->m_pElement->GetAttrName(i,&n);
											pRoot->m_pElement->GetAttrValue(i,&v);
											// TODO: Needs to parse string to
											// change " to ', or vice-versa, depending on option
											printf(pCmdStr->sAttrFormat.GetString(), n.GetString(), v.GetString());
											}
										}
									printf(">");
									}
									break;

							case	BDB_PRINT_ENDTAG:
									if (pRoot->m_pElement->GetFlags() & NODE_FLG_ENDTAG_FORBIDDEN)
										;
									else
										printf("</%s>", pRoot->m_pElement->GetName());
									break;

							case	BDB_PRINT_SUBTREE:
									{
									CBDTreeItem *p = pRoot->GetFirstChild();

									while(p)
										{
										OutputHTML((CParseHTMLNode *)p, pConfig, pState);
										p = pRoot->GetNextChild(p);
										}
									}
									break;

							case	BDB_PRINT_TAB:
									if (!pState->m_bPreformatted)
										{
										for(int j=0;j<pState->m_iTab;j++)
											printf("\t");
										}
									break;
							case	BDB_PRINT_NEWLINE:
									if (!pState->m_bPreformatted)
										printf("\n");
									break;
							default:
									if (isprint(pCurrCmd->cParam))
										printf("%c", pCurrCmd->cParam);
									else
										printf("?");
							}
						break;

				case	BDB_TAB_SET:
						pState->m_iTab = pCurrCmd->cParam;
						break;

				case	BDB_TAB_INC:
						pState->m_iTab += pCurrCmd->cParam;
						break;

				case	BDB_TAB_DEC:
						pState->m_iTab -= pCurrCmd->cParam;
						break;

				}
			//
			pCurrCmd++;
			}
		while(bContinue);

		if (id == NODE_ID_PRE)		{ pState->m_bPreformatted = false; putchar('\n'); }
		}
}

void OutputErrors(const CParseHTMLNode *pRoot, const CMyErrorList *pErrorList)
{
	for(int i=0;i<pErrorList->GetNumErrors();i++)
		{
		CMyError e = pErrorList->GetError(i);
		fprintf(stderr, "%d\t%d\t%s\n", e.m_iLine, e.m_iCol, e.m_Error);
		}
}


bool BeautifyFile(CBDFile &fp, const CBeautyConfig *pConfig)
{
CParseHTMLNode HTMLroot;
CBeautyState State;
CBDParser par;
CMyErrorList err;

	HTMLroot.m_pElement = NULL;
	fp.Seek(0, BD_SEEK_SET);
	par.Open(&fp);
	par.SetErrorList(&err);
	par.Parse(&HTMLroot);
	OutputHTML(&HTMLroot, pConfig, &State);
	OutputErrors(&HTMLroot, &err);
	par.Close();

	return true;
}

void Usage(const char *pName)
{
	printf("%s <filename>\n", pName);
	printf("Copyright Steven Goodwin, 2000-2008. Released under the GPL v2\n");
	printf("All Rights Reserved\n");
	printf("\n");
	printf("This program will use stdout to produce a beautified output of the \n");
	printf("input source files, whilst stderr will list the verification errors found.\n\n");
}

int main(int argc, char* argv[])
{
CBeautyConfig cfg;
#if PARSE_FROM_MEMORY
CBDMemFile fp;
#else
CBDDiskFile	fp;
#endif
int i;

	if (argc == 1)
		Usage(argv[0]);

	for(i=1;i<argc;i++)
		{
		if (fp.Open(argv[i]))
			{
			BeautifyFile(fp, &cfg);
			fp.Close();
			}
		else
			{
			fprintf(stderr, "Can not open file '%s'\n", argv[i]);
			}
		}
	//
	return 0;
}
