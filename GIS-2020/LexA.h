#pragma once
#include "stdafx.h"
#include "FST.h"
#include "IT.h"
#include "LT.h"
namespace Lex
{
	struct TABLES
	{
		IT::IdTable  Id;
		LT::LexTable Lex;
	};

	TABLES Lexic(In::IN in);				//����������� ������
	int  SelectFst(char* word);			//����� ��������
	void AddId(char*, int, int, int);	//���������� ��������������
	void AddLit(char lex, int str, int id);		//���������� ������
}
