#ifndef _BD_MEMFILE_H
#define _BD_MEMFILE_H

#include "BDFile.h"

class CBDMemFile:public CBDFile {

	public:
		CBDMemFile();
		~CBDMemFile();

		virtual	int		Open(const char *pFilename);
		virtual	int		Open(const char *pFilename, size_t iMemSize);
		virtual	int		Close(void);
		virtual	int		GetChar(char *pC);
		virtual	int		ReadChar(char *pC);
		virtual int		Seek(long iAmount, int iFrom);
		virtual	int		EndOfFile(void);

	private:
		unsigned char	*m_pMem;
		unsigned char	*m_pCurrMem;
		size_t			m_iMemSize;
		unsigned char	*m_pFileMem;

};


#endif // _BD_MEMFILE_H
