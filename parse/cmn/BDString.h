#ifndef _BD_STRING_H
#define _BD_STRING_H

#include "BDTypes.h"

class CBDString {

	public:
		CBDString();
		virtual 		~CBDString();

		virtual		CBDString &operator+=(char c);
		virtual		CBDString &operator+=(const char *pStr);
//		virtual		CBDString &operator+=(const CBDString &Str);
		virtual		CBDString &operator=(char c);
		virtual		CBDString &operator=(const char *pStr);
		virtual		CBDString &operator=(CBDString &str);
		virtual		bool	operator==(const char *pStr) const;
		virtual		bool	operator==(const CBDString &str) const;
		virtual		bool	operator!=(CBDString str) const;
		virtual		char	&operator[](unsigned int idx);

		virtual		const char	*GetString(void) const;

		/* Standard string equivalents */
		virtual		int				GetAsInt(void) const;
		virtual		unsigned int Length(void) const;
		virtual		void		Left(int iNum);
		virtual		const char	*InStr(char c) const;

		virtual		void	SetString(const char *);

	private:
		virtual		int		AddChar(char c);
		virtual		int		AddString(const char *pStr);

		char		*m_pStr;
		unsigned int m_iLen, m_iMax, m_iIncSize;
};

#endif	// _BD_STRING_H
