#pragma once

// ������ ��� �������� ���� ����� � �������������
#define CH_NME_EDIT_FIELD(z, x, y) NME_EDIT_FIELD(z, false, Constraints::x::##y##_ALLOWED_CHARS, Constraints::x::##y##_MIN_LENGTH, Constraints::x::##y##_MAX_LENGTH);

// ������ ��� �������� ���� ����� � ������������� � �������� �����
#define CH_NME_EDIT_FIELD_H(z, x, y) NME_EDIT_FIELD(z, true, Constraints::x::##y##_ALLOWED_CHARS, Constraints::x::##y##_MIN_LENGTH, Constraints::x::##y##_MAX_LENGTH);

// ������ ��� �������� ���������� ������� � ��������� ����
#define CH_INIT auto menuElements = Menu::getActive()->getElements(); auto it = menuElements.begin();

// ������ ��� �������� ��������� (������ ��� ���������� �����)
#define CH_MOVE(x) it += x;

// ������ ��� ��������� � �������� ������ �� �������� ��������, ���������� �� ���������
#define CH_CHECKED_GET(y, z, x) string x; x = ((MenuElementEditField *)(*it))->getInput(); if (x.length() < Constraints::y::##z##_MIN_LENGTH) { cout << "����� ���� " << (*it)->getText() << " �� ����� ���� ������ " << Constraints::y::##z##_MIN_LENGTH << " ��������." << endl; system("pause"); return; }
