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
	
	void del(Publisher* ctx, int ctxIndex)
	{
		for (int i = Document::getBinder().getRecords().size() - 1; i >= 0; --i)
		{
			if (Document::getBinder().getRecords()[i]->getPublisher() == ctx)
			{
				cout << "Удаление невозможно -- объект используется в документах." << endl;
				return;
			}
		}
		delete Publisher::getBinder().getRecords()[ctxIndex];
		Publisher::getBinder().getRecords().erase(Publisher::getBinder().getRecords().begin() + ctxIndex);
	}

	void del(Reader* ctx, int ctxIndex)
	{
		for (int i = DocumentUseRecord::getBinder().getRecords().size() - 1; i >= 0; --i)
		{
			if (DocumentUseRecord::getBinder().getRecords()[i]->getReader() == ctx)
			{
				delete DocumentUseRecord::getBinder().getRecords()[i];
				DocumentUseRecord::getBinder().getRecords().erase(DocumentUseRecord::getBinder().getRecords().begin() + i);
			}
		}
		DocumentUseRecord::getBinder().saveRecords();
		delete Reader::getBinder().getRecords()[ctxIndex];
		Reader::getBinder().getRecords().erase(Reader::getBinder().getRecords().begin() + ctxIndex);
	}

	void del(User* ctx, int ctxIndex)
	{
		delete User::getBinder().getRecords()[ctxIndex];
		User::getBinder().getRecords().erase(User::getBinder().getRecords().begin() + ctxIndex);
	}
};