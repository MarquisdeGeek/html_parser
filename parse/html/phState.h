#ifndef _BD_PARSER_HTMLSTATE_H
#define _BD_PARSER_HTMLSTATE_H


#define NODE_ID_MAX				128


class CParseHTMLState {
		public:
			CParseHTMLState();

			bool		m_bPreFormatted;

			int			m_OpenTagCount[NODE_ID_MAX];
			int			m_iHTML_Optionals;	// bit-wise flags, of those optional tags still open???CHANGE USAGE
		
	inline	bool		IsTagOptional(int id) { return m_TagIsOpt[id]; }
	inline	bool		IsTagOpen(int id)	{ return m_OpenTagCount[id]?true:false; }
	inline	bool		IsTagClosed(int id)	{ return m_OpenTagCount[id]==0?true:false; }

	private:
			bool		m_TagIsOpt[NODE_ID_MAX];

			};


#endif	// _BD_PARSER_HTMLSTfATE_H
