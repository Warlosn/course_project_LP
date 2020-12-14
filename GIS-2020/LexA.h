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

	TABLES Lexic(In::IN in);				//лексический анализ
	int  SelectFst(char* word);			//выбор автомата
	void AddId(char*, int, int, int);	//добавление идентификатора
	void AddLit(char lex, int str, int id);		//добавление литера
}
