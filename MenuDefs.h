#pragma once

// Основные статичнские меню
void initLoginMenu();
void initRegisterMenu();
void initUserMenu();
void initAdminMenu();
void initStartMenu();
void initDataTypeMenu();
void initRegisterConfirmationMenu();

// Списочные меню
void initAuthorListMenu();
void initDocumentListMenu();
void initReaderListMenu();
void initPublisherListMenu();
void initUserListMenu();

// Добавляющие меню
void initAuthorAddMenu();
void initDocumentAddMenu();
void initReaderAddMenu();
void initPublisherAddMenu();
void initUserAddMenu();

// Редактирующие меню
void initAuthorEditMenu();
void initDocumentEditMenu();
void initReaderEditMenu();
void initPublisherEditMenu();
void initUserEditMenu();

// Прочие меню
void initLogMenu();
void initDocumentGivingMenu();
void initReaderDebtListMenu();

// Инициализировать все статические меню
void menuInitAll();
