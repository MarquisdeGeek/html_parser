#ifndef _BD_FILE_H
#define _BD_FILE_H

#define BD_SEEK_SET		0		/* beginning */
#define BD_SEEK_CUR		1		/* current */
#define BD_SEEK_END		2		/* end of file */

class CBDFile {

	public:
		virtual ~CBDFile(){};

		virtual	int		Open(const char *pFilename)=0;
		virtual	int		Close(void)=0;
		virtual	int		GetChar(char *pC)=0;				/* Take current character */
		virtual	int		ReadChar(char *pC)=0;				/* Read character from stream, and move on */
		virtual	int		Seek(long iAmount, int iFrom)=0;
		virtual	int		EndOfFile(void)=0;

		virtual	int		GetLine(char *pLine, int iMaxLen);
};


#endif	// _BD_FILE_H
