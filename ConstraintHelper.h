#pragma once

// ������ ��� �������� ���� ����� � �������������
#define CH_NME_EDIT_FIELD(z, x, y) NME_EDIT_FIELD(z, false, Constraints::x::##y##_ALLOWED_CHARS, Constraints::x::##y##_MIN_LENGTH, Constraints::x::##y##_MAX_LENGTH);

// ������ ��� �������� ���� ����� � ������������� � �������� �����
#define CH_NME_EDIT_FIELD_H(z, x, y) NME_EDIT_FIELD(z, true, Constraints::x::##y##_ALLOWED_CHARS, Constraints::x::##y##_MIN_LENGTH, Constraints::x::##y##_MAX_LENGTH);

// ������ ��� �������� ���� ����� � �������������, ����� ��������
#define CH_NME_EDIT_FIELD_S(z, x, y) NME_EDIT_FIELD(z, false, Constraints::x::##y##_ALLOWED_CHARS, 0, Constraints::x::##y##_MAX_LENGTH);

// ������ ��� �������� ���� ����� � ������������� � �������� �����, ����� ��������
#define CH_NME_EDIT_FIELD_SH(z, x, y) NME_EDIT_FIELD(z, true, Constraints::x::##y##_ALLOWED_CHARS, 0, Constraints::x::##y##_MAX_LENGTH);

// ������ ��� �������� ���������� ������� � ��������� ����
#define CH_INIT auto menuElements = Menu::getActive()->getElements(); auto it = menuElements.begin();

// ������ ��� �������� ��������� (������ ��� ���������� �����)
#define CH_MOVE(x) it += x;

#define CH_GET_AS(x) ((x*)(*it))

// ������ ��� ��������� � �������� ������ �� �������� ��������, ���������� �� ���������
#define CH_GET_AS_EF_AND_CHECK(y, z, x) string x; x = CH_GET_AS(MenuElementEditField)->getInput(); if (x.length() < Constraints::y::##z##_MIN_LENGTH) { ELK; cout << "����� ���� " << (*it)->getText() << " �� ����� ���� ������ " << Constraints::y::##z##_MIN_LENGTH << " ��������." << endl; EULK; return; }
