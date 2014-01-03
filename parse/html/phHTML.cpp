#include "phHTML.h"

CParseNode *CParseHTMLNode::ParseStartTag(CBDParser *pParser)
{
	return 0;
}

CParseNode *CParseHTMLNode::ParseEndTag(CBDParser *pParser, CBDString *pStr)
{
char c;

	while(pParser->ReadChar(&c))
		{
		if (c == HTML_END_TAG)	return this;
		if (pStr)	*pStr += c;
		}
	//
	return this;
}

CParseNode *CParseHTMLNode::ParseDTDTag(CBDParser *pParser)
{
CParseHTMLNode *pChild;
CHTMLElement_DTD *pEle;
CBDString str;
char c, lastc=0;
bool bCommentToggle=false;

	pChild = new CParseHTMLNode;
	pChild->Add(pParser, this);
	pChild->m_pElement = htmlCreateDTD();
	pEle = (CHTMLElement_DTD *)pChild->m_pElement;

	str = "<!";
	while(pParser->ReadChar(&c))
		{
		str += c;
		if (lastc == '-' && c == '-')	
			bCommentToggle = !bCommentToggle;
				
		if (!bCommentToggle && c == HTML_END_TAG)	break;
		lastc = c;
		}
	//
	pEle->SetString(str);
	//
	return this;
}

CParseNode *CParseHTMLNode::ParseInstructionTag(CBDParser *pParser)
{
CParseHTMLNode *pChild;
CHTMLElement_DTD *pEle;
CBDString str;
char c;

	pChild = new CParseHTMLNode;
	pChild->Add(pParser, this);
	pChild->m_pElement = htmlCreateDTD();
	pEle = (CHTMLElement_DTD *)pChild->m_pElement;

	str = "<?";
	while(pParser->ReadChar(&c))
		{
		str += c;
		if (c == HTML_END_TAG)	break;
		}
	//
	pEle->SetString(str);
	//
	return this;
}

/*
** The node should return from 'Parse' when 'this' tag has been closed.
** The return param is the node ptr which _needs_ to be closed.
**
** eg. TABLE -> TR -> TD. If a TD is found when in TR, each TD returns
** itself to TR. If, however, a /TABLE is found, then _that_ ptr is returned,
** and the TR should close itself, before passing itself back to the parent.
** All un-closed tags are automatically closed (helps mis-matched tags)
*/

/*
** During development, this function increase to 500+ lines of code :( To
** make this mangeable I've split into separate functions. However, the nature
** of the parser requires the state variables 'pTagToClose' and 'pCurrTag' to
** exist locally. This meant a couple of 'ptr to ptr (**)' to allow the Parse
** functions to, effectively, return two pieces of data.
*/
CParseNode *CParseHTMLNode::Parse(CBDParser *pParser)
{
CParseNode *pTagToClose = this;
CParseHTMLNode *pCurrTag = this;	// this can change from 'this' when optional end tags aren't closed, i.e. <P>
char c;

	do 
		{
		if (!pParser->ReadChar(&c))		return pTagToClose;
		//
		if (c == HTML_START_TAG)
			{
			// 1. Parse tag type
			if (!SkipWS(pParser))		return pTagToClose;
			if (!pParser->ReadChar(&c))	{ pParser->AddError(HERR_EOF_MIDTAG, "EOF reached in middle of tag", NULL, NULL); return pTagToClose; }

			switch(c)
				{
				case	HTML_DTD:
								pCurrTag->ParseDTDTag(pParser);
								break;

				case	HTML_INSTRUCTION:
								pCurrTag->ParseInstructionTag(pParser);
								break;

				case	HTML_END_SLASH:
								{ 
								CParseHTMLNode *pChild;

								if ((pChild=ParseEndTagElement(pParser, &pTagToClose)))
									return pChild; 
								}
								break;

				default:
								{
								CParseNode *pCloseNode;

								if ((pCloseNode=ParseStartTagElement(pParser, &pCurrTag, &pTagToClose, c)))
									return pCloseNode; 
								}
								break;
				}
			}
		else	// c != '<'
			{
			// 2. Create node
			pCurrTag->ParseCDataElement(pParser, c);
			}
		}
	while(1);
	//
	return pTagToClose;
}

CParseNode *CParseHTMLNode::ParseStartTagElement(CBDParser *pParser, CParseHTMLNode **ppCurrTag, CParseNode **ppTagToClose, char c)
{
CBDString ele;
CParseHTMLNode *pChild;

	// Read element name
	// If name is invalid (i.e. starts with a numeral)
	// the whole thing is stored as text
	// (tag)
	ele += c;
	pChild = new CParseHTMLNode;
	if (GetName(pParser, ele, true) == false)
		{
		delete pChild;
		}
	else
		{	// valid element name
		if ((pChild->m_pElement = htmlCreateElement(ele)))
			{
			// We open our new tag, by default, as a child of the
			// current one. With optional tags, we get added to
			// a different element. (eg, <LI> followed by <LI>, the
			// second <LI> is added to the <OL> or <UL> tag.
			// With dual-optionals, we may need to create a new tag
			// i.e. <HEAD> before adding outself.
			pChild->OpenTag(pParser, *ppCurrTag);
			pChild->ParseAttributeString(pParser);
			*ppCurrTag = pChild;

			if (pChild->m_pElement->GetFlags() & NODE_FLG_DEPRECATED)
				pParser->AddError(HERR_DEPRECATED_TAG, "The <%s> tag has been deprecated", pChild->m_pElement->GetName(), NULL);

			// Close the tag automatically?
			if (pChild->m_pElement->CloseTagAfterOpen())
				{
				// we don't need to recurse on these tags (like <BR>) since
				// nothing can appear 'inside' them, so we
				// continue parsing other children, from our parent
				*ppCurrTag = (CParseHTMLNode *)pChild->GetParent(); 
				*ppTagToClose = *ppCurrTag;
				}
			else
				{
				CParseNode *pClosed;

					pClosed = pChild->Parse(pParser);
					// We want to close 'pClosed', if this is us we can
					// continue parsing, adding new elements to ourselves.
					// Otherwise, we return so the correct tag can be closed
					if (pChild == pClosed)
						{
						// We're closing the one we sent in, so our child
						// is now complete.
						// Continue parsing other children, from our parent
						*ppCurrTag = (CParseHTMLNode *)pChild->GetParent(); 
						*ppTagToClose = *ppCurrTag;
						}
					else
						{
						// We're closing somebody above us in the tree.
						// (probably thru optional, or mismatched, tags)
						return pClosed;
						}
				}
			}
		else	// no such element tag
			{
			pParser->AddError(HERR_INVALID_TAG, "Unknown tag element <%s>", ele.GetString(), NULL);
			while(pParser->ReadChar(&c))
				{
				if (c == HTML_END_TAG)	break;
				}
			delete pChild;
			}
		}

	return NULL;
}


CParseHTMLNode *CParseHTMLNode::ParseEndTagElement(CBDParser *pParser, CParseNode **ppTagToClose)
{
CBDString ele;
CHTMLElement	*pEle;

	*ppTagToClose = ParseEndTag(pParser, &ele);

	if ((pEle = htmlCreateElement(ele)))	// Create pEle, solely to validate tag string
		{
		if ((*ppTagToClose)->GetNodeType() == NODETYPE_HTML)
			{
			CParseHTMLNode *pLastOpened;

			// This should also close optional tags that are still open,
			// preventing the need to explicitly study each opt-open tag
			// above us in the tree.
			if ((pLastOpened = GetPreviousTagID(pParser, pEle->GetID())))
				return pLastOpened->CloseTag(pParser);
			else if (pEle->GetFlags() & NODE_FLG_ENDTAG_FORBIDDEN)
				;
			else
				pParser->AddError(HERR_ENDTAG_NOTOPENED, "The <%s> end tag is not open", ele.GetString(), NULL);
			}
		else
			{
			// We only close HTML nodes here. Other types (such as
			// javascript) are not handled. However, if you're closing an
			// HTML tag inside a script you've got bigger problems :)
			}
		//
		if (pEle->GetFlags() & NODE_FLG_ENDTAG_FORBIDDEN)
			pParser->AddError(HERR_ENDTAG_FORBIDDEN, "The <%s> end tag is forbidden", ele.GetString(), NULL);
		//
		delete pEle;
		}
	else
		{
		pParser->AddError(HERR_INVALID_ENDTAG, "Unknown end tag element <%s>", ele.GetString(), NULL);
		}
	//
	return NULL;
}

void CParseHTMLNode::ParseCDataElement(CBDParser *pParser, char c)
{
CParseHTMLNode *pChild;
CBDString cd;
bool bAddThisTag=true;

	if (IsWS(c) && pParser->m_pHTMLState->m_bPreFormatted==false)
		cd = ' ';
	else
		cd = c;

	if (m_pElement && pParser->m_pHTMLState->m_bPreFormatted)
		{
		GetCData(pParser, cd, false);
		}
	else
		{
		GetCData(pParser, cd);
		// If the whole string is WS, don't bother adding it (we're
		// not handling pre formatted text
		if (cd.Length()==1 && IsWS(cd[0]))	bAddThisTag = false;
		}
	//
	if (bAddThisTag)
		{
		pChild = new CParseHTMLNode;
		pChild->Add(pParser, this);
		pChild->m_pElement = htmlCreateCData();

		((CHTMLElement_CData *)pChild->m_pElement)->SetCData(cd);
		}
}

void CParseHTMLNode::ParseAttributeString(CBDParser *pParser)
{
CBDString attr, val;
bool bFoundEndTag=0;
int err;
char c;
	//
	do
		{
		if (!SkipWS(pParser))			break;
		if (!pParser->ReadChar(&c))		break;
		if (c == HTML_END_TAG)			break;

		attr=c;
		if (!GetName(pParser, attr))	break;
		//
		if (!SkipWS(pParser))			break;
		if (!pParser->ReadChar(&c))		break;
		if (c == '=')
			{
			char quote =0;

			val="";
			if (!SkipWS(pParser))		break;
			if (!pParser->ReadChar(&c))	break;
			if (c == HTML_SINGLE_QUOTE)
				quote = c;
			else if (c == HTML_DOUBLE_QUOTE)
				quote = c;
			else
				val += c;
			//
			if (!GetQuotedText(pParser, val, quote))	break;
			}
		else if (c == HTML_END_TAG)
			{
			val = attr;
			bFoundEndTag = 1;
			}
		else
			{
			pParser->UngetChar();
			val = attr;
			}
		//
		err = m_pElement->ParseAttr(&attr, &val);
		if (err == ATTR_PARSE_INVALID_ATTR)
			pParser->AddError(HERR_INVALID_ATTR_VALUE, "Value of attribute '%s' ('%s') is invalid", attr.GetString(), val.GetString());
		else if (err == ATTR_PARSE_INVALID_NAME)
			pParser->AddError(HERR_INVALID_ATTR_NAME, "The <%s> tag does not support '%s' attributes", m_pElement->GetName(), attr.GetString());
		else if (err == ATTR_PARSE_DUPLICATE_ATTR)
			pParser->AddError(HERR_INVALID_ATTR_VALUE, "Duplicate attribute '%s' found", attr.GetString(), NULL);
		}
	while(!bFoundEndTag);

	m_pElement->SetValid(true);
}


CParseHTMLNode *CParseHTMLNode::OpenTag(CBDParser *pParser, CParseHTMLNode *pCurrTag)
{
CParseHTMLNode *pSpawnFromTag = pCurrTag;
CParseHTMLNode *pNewTag;
int ele = m_pElement->GetID();

	// Create new tags for those elements (like HTML, HEAD BODY, and
	// TBODY) that are dual-optionals. If we reach a 'HEAD', but have yet
	// to produce an HTML tag, we create it here, and spawn ourselves
	// as _its_ child.
	// (optional flags are added later)

	// HTML must exist as the first element.
	if (ele != NODE_ID_HTML && pParser->m_pHTMLState->IsTagClosed(NODE_ID_HTML))
		{
		if ((pNewTag = CreateTag(pParser, pSpawnFromTag, "HTML")))
			pSpawnFromTag = pNewTag;
		}

	// HEAD
	if (ele != NODE_ID_HEAD && pParser->m_pHTMLState->IsTagClosed(NODE_ID_HEAD))
		if (entIsHeadMisc(ele) || entIsHeadContent(ele))
			{
			if (pParser->m_pHTMLState->IsTagOpen(NODE_ID_BODY))
				{/*
				** Don't create another head if we've already reached the body.
				** Let the rest of the parser produce errors if it wants, but we won't
				** introduce new ones here :)
				** (this check will also stop elements that are legal in head & body
				** trying to open a head here, where a body would do, i.e. SCRIPT)	
				*/}
			else
				{
				pNewTag = pSpawnFromTag->GetPreviousTagID(pParser, NODE_ID_HTML);
				if ((pNewTag = CreateTag(pParser, pNewTag, "HEAD")))
					pSpawnFromTag = pNewTag;
				}
			}

	// BODY
	if (ele != NODE_ID_BODY && pParser->m_pHTMLState->IsTagClosed(NODE_ID_BODY))
		if (entIsFlow(ele) || ele==NODE_ID_INS || ele==NODE_ID_DEL)
			{
			// TODO - Create an (empty) head, if one doesn't exist
			if ((entIsHeadMisc(ele) || entIsHeadContent(ele)) && pParser->m_pHTMLState->IsTagOpen(NODE_ID_HEAD))
				{
				/* 
				** As above. Don't open a <BODY> if it's ok to include the tag
				** in the head instead. i.e. SCRIPT
				*/
				}
			else
				{
				pNewTag = pSpawnFromTag->GetPreviousTagID(pParser, NODE_ID_HTML);
				if ((pNewTag = CreateTag(pParser, pNewTag, "BODY")))
					pSpawnFromTag = pNewTag;
				}
			}

	// TBODY
	if (ele != NODE_ID_TBODY && pParser->m_pHTMLState->IsTagClosed(NODE_ID_TBODY))
		if (ele == NODE_ID_TR)	// could include TD, but then that would breach HTML
								// which expects a TR first (for the row)
			{
			pNewTag = pSpawnFromTag->GetPreviousTagID(pParser, NODE_ID_TABLE);
			// Only create TBODY tag if we're actually inside a table
			if (pNewTag && (pNewTag = CreateTag(pParser, pNewTag, "TBODY")))
				pSpawnFromTag = pNewTag;
			}


	// New tags are children of the current one.

	// The exception is 'optional end tags': in these cases
	// we close the previously opened tag of this type (i.e. <P>)
	// and create the node from it's parent.

	// The standard algorithm for 'when to close an optional tag'
	// does not seem to be well known (and I'm not about to trawl
	// through Mozilla to find out:) so I employ a virtual function
	// where each element indicates when (and how) to close itself.
	// (see comments below for examples)

	// This might seem a bit chunky, but I've more confidence
	// doing it here, than re-building the parse tree later and
	// doing error recovery.

	// There's an optional above us in the tree (if must be open), 
	// so see if the current element should be added here, or above
	for(int id=0;id<NODE_ID_MAX;id++)
		{
		if (pParser->m_pHTMLState->IsTagOptional(id) && pParser->m_pHTMLState->IsTagOpen(id))
			{
			CParseHTMLNode	*pNode;

				// OPT: If virtual function doesn't close tag,
				// getting previous tag is a wasted effort
				if ((pNode = pSpawnFromTag->GetPreviousTagID(pParser, id)))
					{ // pNode should NEVER be null since it's the 'id' type used
					// to set the flag in the first place

					// There is current an open tag (pNode), but we're about to open another tag
					// (pChild). Which tag (if any) do we close before continuing to open pChild?
					
					// Examples:
					// If <P> is still open, and we find a block tag, then we close the <P> tag.
					// and continue all new tags from <P>'s parent.
					// (sim. OPTION & OPTGROUP, DL & DT|DD)
					
					// If <TD> is still open, and we find a <TFOOT> we rollback to the TABLE.
					// (sim. other <TABLE> elements)
					CParseHTMLNode *pNewSpawningTag=NULL;

					if ((pNewSpawningTag = pNode->m_pElement->GetTagToClose(pParser, pNode, m_pElement->GetID())))
						{
						pNewSpawningTag->CloseAllChildrenTag(pParser);
						pSpawnFromTag = pNewSpawningTag;
						}
					}
			}
		}
	//
	// Now add the element from the parsed document
	// (making a couple of checks first, however)
	// KNOWN: Adding a BODY tag (manually from the doc) can cause two BODYs to appear
	// in a tree.
	Add(pParser, pSpawnFromTag);

	return this;
}

void CParseHTMLNode::Add(CBDParser *pParser, CParseHTMLNode *pParent)
{
	if (m_pElement) {
		int id = m_pElement->GetID();
		
		//
		// Turn on pre-formatted switch
		//
		if (id == NODE_ID_PRE || id == NODE_ID_TEXTAREA)
			pParser->m_pHTMLState->m_bPreFormatted = true;

		++pParser->m_pHTMLState->m_OpenTagCount[id];
		
		m_pElement->m_iLine = pParser->GetCurrentLine();
		m_pElement->m_iCol = pParser->GetCurrentCol();
		}

	CParseMarkupNode::Add(pParent);
}

CParseHTMLNode *CParseHTMLNode::CreateTag(CBDParser *pParser, CParseHTMLNode *pParent, const char *pTagname)
{
CParseHTMLNode *pForced = new CParseHTMLNode;
CBDString str;

	str = pTagname;
	if ((pForced->m_pElement = htmlCreateElement(str)))
		{
		pForced->Add(pParser, pParent);
		}
	else
		{
		delete pForced;
		pForced = NULL;
		}
	//
	return pForced;
}


CParseHTMLNode *CParseHTMLNode::CloseTag(CBDParser *pParser)
{
int ele = m_pElement->GetID();

	if (ele == NODE_ID_PRE || ele == NODE_ID_TEXTAREA)
		pParser->m_pHTMLState->m_bPreFormatted = false;

	--pParser->m_pHTMLState->m_OpenTagCount[m_pElement->GetID()];

	return this;
}

void CParseHTMLNode::CloseAllChildrenTag(CBDParser *pParser)
{
CParseHTMLNode *pEle;

	// Close our children...
	pEle = (CParseHTMLNode *)GetFirstChild();
	while(pEle)
		{
		pEle->CloseAllChildrenTag(pParser);
		pEle = (CParseHTMLNode *)GetNextChild(pEle);
		}
	// ...then close ourselves
	CloseTag(pParser);
}

CParseHTMLNode *CParseHTMLNode::CloseLastTagID(CBDParser *pParser, int iIDToClose)
{
CParseHTMLNode *pParent = (CParseHTMLNode *)GetParent();

	if (!m_pElement && !pParent)
		return NULL;
	//
	if (!m_pElement)
		return pParent->CloseLastTagID(pParser, iIDToClose);

	if (m_pElement->GetID() == iIDToClose)
		return this;
	//

	if (pParent)
		{
		int f = m_pElement->GetFlags();

		if (f & (NODE_FLG_ENDTAG_OPTIONAL | NODE_FLG_BOTHTAGS_OPTIONAL)) 
			;
		else
			pParser->AddError(HERR_TAG_NOTCLOSED, "The <%s> tag is not closed", m_pElement->GetName(), NULL);

		return pParent->CloseLastTagID(pParser, iIDToClose);
		}
	//
	return NULL;
}

CParseHTMLNode *CParseHTMLNode::GetParentTagID(CBDParser *pParser)
{
	return (CParseHTMLNode *)GetParent();
}

CParseHTMLNode *CParseHTMLNode::GetPreviousTagID(CBDParser *pParser, int iID)
{
CParseHTMLNode *pParent = (CParseHTMLNode *)GetParent();

	if (!m_pElement && !pParent)
		return NULL;
	//
	if (m_pElement && m_pElement->GetID() == iID)
		return this;
	//
	if (pParent)
		return pParent->GetPreviousTagID(pParser, iID);
	//
	return NULL;
}

bool CParseHTMLNode::IsTagIDBeneathUs(int iNodeID)
{
CParseHTMLNode *pEle;

	pEle = (CParseHTMLNode *)GetFirstChild();
	while(pEle)
		{
		if (pEle->m_pElement&& pEle->m_pElement->GetID())	return true;
		if (pEle->IsTagIDBeneathUs(iNodeID))				return true;
		pEle = (CParseHTMLNode *)GetNextChild(pEle);
		}
	return false;
}

void CParseHTMLNode::ValidateTree(CBDParser *pParser)
{
CParseHTMLNode *pEle;

	if (m_pElement)
		m_pElement->ValidateTree(pParser, this);
	//
	pEle = (CParseHTMLNode *)GetFirstChild();
	while(pEle)
		{
		pEle->ValidateTree(pParser);
		pEle = (CParseHTMLNode *)GetNextChild(pEle);
		}
	// The sub-tree element tags are correct:

	// Now check that all '#REQUIRED' attributes (of this element) are, 
	// in fact, specified
	if (m_pElement)// && m_pElement->IsValid())	// don't report errors on tags that already have problems
		if (!m_pElement->ValidateRequiredAttrs(pParser))
			m_pElement->SetValid(false);
}

