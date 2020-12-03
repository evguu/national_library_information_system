#pragma once
#include "User.h"
#include "Publisher.h"
#include "Document.h"
#include "Author.h"
#include "Reader.h"
#include "DocumentAuthorBind.h"
#include "DocumentUseRecord.h"

// Узкоприменяемый спагетти-макрос.
#define DOOM_BUTTON(Name, name) NME_FUNC_BUTTON("Удалить элемент ", []() {GET_CTX(Name, name, 2);BindAwareDeleter::del(ctx, ctxIndex);Name::getBinder().saveRecords();Menu::multiPopMenuStack(2);init##Name##ListMenu();##name##ListMenu->addToStack();});

namespace BindAwareDeleter
{
	void del(Author* ctx, int ctxIndex);

	void del(Document* ctx, int ctxIndex);
};