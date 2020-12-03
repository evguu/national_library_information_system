#include "pch.h"
#include "BindAwareDeleters.h"

namespace BindAwareDeleter
{
	void del(Author* ctx, int ctxIndex)
	{
		for (int i = DocumentAuthorBind::getBinder().getRecords().size() - 1; i >= 0; --i)
		{
			if (DocumentAuthorBind::getBinder().getRecords()[i]->getAuthor() == ctx)
			{
				delete DocumentAuthorBind::getBinder().getRecords()[i];
				DocumentAuthorBind::getBinder().getRecords().erase(DocumentAuthorBind::getBinder().getRecords().begin() + i);
			}
		}
		DocumentAuthorBind::getBinder().saveRecords();
		delete Author::getBinder().getRecords()[ctxIndex];
		Author::getBinder().getRecords().erase(Author::getBinder().getRecords().begin() + ctxIndex);
	}

	void del(Document* ctx, int ctxIndex)
	{
		for (int i = DocumentAuthorBind::getBinder().getRecords().size() - 1; i >=0 ; --i)
		{
			if (DocumentAuthorBind::getBinder().getRecords()[i]->getDocument() == ctx)
			{
				delete DocumentAuthorBind::getBinder().getRecords()[i];
				DocumentAuthorBind::getBinder().getRecords().erase(DocumentAuthorBind::getBinder().getRecords().begin() + i);
			}
		}
		for (int i = DocumentUseRecord::getBinder().getRecords().size() - 1; i >= 0; --i)
		{
			if (DocumentUseRecord::getBinder().getRecords()[i]->getDocument() == ctx)
			{
				delete DocumentUseRecord::getBinder().getRecords()[i];
				DocumentUseRecord::getBinder().getRecords().erase(DocumentUseRecord::getBinder().getRecords().begin() + i);
			}
		}
		DocumentAuthorBind::getBinder().saveRecords();
		DocumentUseRecord::getBinder().saveRecords();
		delete Document::getBinder().getRecords()[ctxIndex];
		Document::getBinder().getRecords().erase(Document::getBinder().getRecords().begin() + ctxIndex);
	}

	void del(User* ctx, int ctxIndex)
	{
		// TODO
	}
	
	void del(Publisher* ctx, int ctxIndex)
	{
		// TODO
	}

	void del(Reader* ctx, int ctxIndex)
	{
		// TODO
	}
};