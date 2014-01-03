#ifndef _BD_DISKFILE_H
#define _BD_DISKFILE_H

#include <stdio.h>
#include "BDFile.h"

class CBDDiskFile:public CBDFile {

	public:
		CBDDiskFile();
		~CBDDiskFile();

		virtual	int		Open(const char *pFilename);
		virtual	int		Close(void);
		virtual	int		GetChar(char *pC);
		virtual	int		ReadChar(char *pC);
		virtual int		Seek(long iAmount, int iFrom);
		virtual	int		EndOfFile(void);

	private:
		FILE			*m_fp;
};


#endif // _BD_DISKFILE_H

