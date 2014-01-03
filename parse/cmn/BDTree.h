#ifndef _BD_TREE_H
#define _BD_TREE_H

class CBDTreeItem {

	public:
		CBDTreeItem();
		CBDTreeItem(CBDTreeItem *pParent);

		void			Add(CBDTreeItem *pParent);
		void			Remove(void);

inline 	CBDTreeItem		*GetParent(void) const { return m_pParent; }
inline 	int				GetNumChildren(void) const { return m_pFirstChild?1/* this one */+m_pFirstChild->GetNumSiblings()/* the others */:0; }
inline 	CBDTreeItem		*GetFirstChild(void) const { return m_pFirstChild; }
	 	CBDTreeItem		*GetNextChild(CBDTreeItem *pPrev) const;
	 	int				GetNumSiblings(void) const;
inline 	CBDTreeItem		*GetFirstSibling(void) const { return m_pNextSibling; }
inline 	CBDTreeItem		*GetNextSibling(CBDTreeItem *pPrev) const { return pPrev->m_pNextSibling; }

	private:
		CBDTreeItem		*m_pParent;
		CBDTreeItem		*m_pFirstChild;
		CBDTreeItem		*m_pNextSibling;


};


#endif	// _BD_TREE_H
