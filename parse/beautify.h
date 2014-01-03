#ifndef _HTML_BEAUTIFY_H
#define _HTML_BEAUTIFY_H


#define NODE_ID_MAXIMUM						1024


#define BDB_MAX_COMMAND_LENGTH		32

#define BDB_END			0x00
#define BDB_PRINT		0x10
#define		BDB_PRINT_STARTTAG	0x01
#define		BDB_PRINT_ENDTAG	0x02
#define		BDB_PRINT_SUBTREE	0x03
#define		BDB_PRINT_TAB		0x04
#define		BDB_PRINT_NEWLINE	0x05
#define BDB_TAB_SET		0x20
#define BDB_TAB_INC		0x30
#define BDB_TAB_DEC		0x40

typedef struct sCmd {
			tUCHAR	cCommand;
			tUCHAR	cParam;	
			} BDB_COMMAND;

class CCommandString {
		public:
			BDB_COMMAND	cmd[BDB_MAX_COMMAND_LENGTH];
			CBDString	sAttrFormat;
			};

class CBeautyConfig {
		private:
			void		DefaultCmdStr(CCommandString *pCmd);
			void		DefaultInlineCmdStr(CCommandString *pCmd);
			void		DefaultNewlineCmdStr(CCommandString *pCmd);
			void		DefaultListCmdStr(CCommandString *pCmd);
			
		public:
			CBeautyConfig();
			//
			CCommandString	m_cmdTag[NODE_ID_MAXIMUM];
			bool			m_ShowAllAttribs;
			bool			m_WordWrapCData;
			int			m_WordWrapWidth;
			};

class CBeautyState {
		public:
			CBeautyState();
			int			m_iTab;
			bool			m_bPreformatted;
			};


#endif	// _HTML_BEAUTIFY_H
