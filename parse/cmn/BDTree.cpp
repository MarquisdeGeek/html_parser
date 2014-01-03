/*
** Blue Dust - Tree
*/
#include "BDTree.h"

CBDTreeItem::CBDTreeItem()
{
	m_pParent = m_pFirstChild = m_pNextSibling = 0;
}

CBDTreeItem::CBDTreeItem(CBDTreeItem *pParent)
{
	m_pParent = pParent;
	m_pFirstChild = m_pNextSibling = 0;
}

void CBDTreeItem::Add(CBDTreeItem *pParent)
{
	// Update parent, by adding us as the last sibling
	if ((m_pParent = pParent))
		{
		CBDTreeItem *pCurrChild = m_pParent->m_pFirstChild;
		CBDTreeItem *pPrevChild = 0;

		if (pCurrChild == 0)
			{
			m_pParent->m_pFirstChild = this;
			}
		else
			{
			while(pCurrChild)
				{
				pPrevChild = pCurrChild;
				pCurrChild = pCurrChild->m_pNextSibling;
				// If we're trying to add the same entry twice - exit now!
				if (this == pPrevChild)		return;
				}

			pPrevChild->m_pNextSibling = this;
			}
		}
}

void CBDTreeItem::Remove(void)
{
	// Only try to remove if we're attached to a parent
	if (!m_pParent)		return;
	// Remove us, by:
	
	// 1. Changing the parents' pChild
	// (only if we're the first child)
	if (this == m_pParent->m_pFirstChild)
		{
		m_pParent->m_pFirstChild = m_pNextSibling;
		}
	else
		{			
		// 2. Updating the siblings list
		CBDTreeItem *pCurrChild = m_pParent->m_pFirstChild;
		CBDTreeItem *pPrevChild = 0;

			while(pCurrChild)
				{
				if (this == pCurrChild)
					pPrevChild->m_pNextSibling = m_pNextSibling;
				//
				pPrevChild = pCurrChild;
				pCurrChild = pCurrChild->m_pNextSibling;
				}
		}
	//
	m_pParent = 0;
	m_pNextSibling = 0;
}


CBDTreeItem *CBDTreeItem::GetNextChild(CBDTreeItem *pPrev) const
{
	if (!m_pFirstChild)		return 0;

CBDTreeItem *pCurrChild = m_pFirstChild;
	
	while(pCurrChild)
		{
		if (pPrev == pCurrChild)
			return pCurrChild->m_pNextSibling;

		pCurrChild = pCurrChild->m_pNextSibling;
		}

	return 0;
}

int CBDTreeItem::GetNumSiblings(void) const
{
CBDTreeItem *pPrevChild = m_pNextSibling;
int i=0;

	while(pPrevChild)
		{
		pPrevChild = pPrevChild->m_pNextSibling;
		i++;
		}
	//
	return i;
}

