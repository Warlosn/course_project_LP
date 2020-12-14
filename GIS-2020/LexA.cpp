#include "stdafx.h"
#include "LexA.h"
#include "FST.h"
#include <fstream>
#include <string>
#include <iostream>
#define LA_ERRORS 200

namespace Lex
{
	LT::LexTable lexT = LT::Create(LT_MAXSIZE);
	IT::IdTable  idT = IT::Create(TI_MAXSIZE);


	int CasеToDecimalBase(std::string input, int base) {
		std::string num = input.substr(1, input.size());
		return std::stoi(num, nullptr, base);
	}

	int SelectFst(char* word)
	{
		FST::FST* ArrOfFst = FST::ArrFst();
		for (int i = 0; i < ARR_FST_SIZE; i++)
		{
			ArrOfFst[i].string = word;
			if (FST::execute(ArrOfFst[i]))
			{
				return i;
			}
		}
		return -1;
	}
	Lex::TABLES Lexic(In::IN in)
	{
		FST::FST* ArrOfFst = FST::ArrFst();
		Error::ARR_OF_ERRORS err;
		TABLES rc;
		int NUM;
		int z = 0;				//счётчик
		int type;				//тип данных
		bool proc = false;		//процедура
		bool error = false;
		bool act = false;
		short head = 0;
		int param = 1;			//является ли параметром
		int ravn = 0;
		int result;
		int lit = 0;
		int ident = 0;
		char pref[6] = "\0";
		char name[ID_MAXSIZE];
		char liter[ID_MAXSIZE] = "literal";
		char* buf;
		while (!in.Words.empty())
		{
			buf = &in.Words.front()[0];
			NUM = SelectFst(buf);
			if (NUM == -1)
			{
				err.AddErr(120, in.Line.front(), -1);
				error = true;
			}
			switch (ArrOfFst[NUM].lexsw)
			{
			case 0:		//lexems
			{
				if (ArrOfFst[NUM].lex == LEX_RIGHTHESIS)
					param = 1;
				if (ArrOfFst[NUM].lex == LEX_RIGHTBRACE)
					strcpy(pref, "");
				if (ArrOfFst[NUM].lex == LEX_RAVNO)
					ravn = 2;
				if (ArrOfFst[NUM].lex == LEX_ACT)
					act = true;
				if (ArrOfFst[NUM].lex == LEX_PROCEDURE)
				{
					proc = true;
					param = 3;
				}
				AddLit(ArrOfFst[NUM].lex, in.Line.front(), -1);
				break;
			}
			case 1:		//type
			{
				if (ArrOfFst[NUM].lex == LEX_CHAR)
					type = 3;
				if (ArrOfFst[NUM].lex == LEX_CYMB)
					type = 2;
				if (ArrOfFst[NUM].lex == LEX_NUM)
					type = 1;
				
				AddLit(ArrOfFst[NUM].lex, in.Line.front(), -1);
				break;
			}
			case 2:		//lit
			{
				char* ind = liter;
				strcat(ind, std::to_string(lit).c_str());
				if (ArrOfFst[NUM].lex == 'd')
				{

					int val = CasеToDecimalBase(buf, 2);
					AddId(ind, lexT.size, 1, 4);
					idT.table[idT.size - 1].value.vint = val;
					lit++;
					ind[7] = '\0';
					AddLit('k', in.Line.front(), idT.size - 1);

				}
				if (ArrOfFst[NUM].lex == 'v')
				{
					int val = CasеToDecimalBase(buf, 8);
					AddId(ind, lexT.size, 1, 4);
					idT.table[idT.size - 1].value.vint = val;
					lit++;
					ind[7] = '\0';
					AddLit('k', in.Line.front(), idT.size - 1);

				}
				if (ArrOfFst[NUM].lex == 'l')
				{
					strncpy(idT.table[idT.size].value.vstr.str, buf, strlen(buf));
					idT.table[idT.size].value.vstr.len = strlen(buf) - 2;
					AddId(ind, lexT.size, 2, 4);
					lit++;
					ind[7] = '\0';
					AddLit('l', in.Line.front(), idT.size - 1);
				}

				if (ArrOfFst[NUM].lex == 'q')
				{
					strncpy(idT.table[idT.size].value.vstr.str, buf, strlen(buf));
					idT.table[idT.size].value.vstr.len = strlen(buf) - 2;
					AddId(ind, lexT.size, 3, 4);
					lit++;
					ind[7] = '\0';
					AddLit('q', in.Line.front(), idT.size - 1);
				}
				break;
			}
			case 3:		//id
			{
				int check = IT::IsDublId(idT, buf);
				strncpy(name, buf, ID_MAXSIZE);
				name[10] = '\0';
				if (proc)//для процедуры
				{
					strncpy(pref, buf, 3);
					pref[3] = '\0';
					strcat(pref, std::to_string(ident).c_str());
					pref[5] = '\0';
					ident++;
					AddId(name, lexT.size, type, 2);
					proc = false;

				}
				else//для переменной
				{
					if (check == TI_NULLIDX)
					{
						buf[5] = '\0';
						strcpy(name, strcat(buf, pref));
						AddId(name, lexT.size, type, param);
						act = false;
					}
				}
				check = IT::IsId(idT, name);
				if (lexT.table[idT.table[check].idxfirstLE - 1].lexema != LEX_NUM && lexT.table[idT.table[check].idxfirstLE - 1].lexema != LEX_CYMB && lexT.table[idT.table[check].idxfirstLE - 1].lexema != LEX_CHAR)
				{
					err.AddErr(121, in.Line.front(), -1);
					error = true;
				}
				AddLit(ArrOfFst[NUM].lex, lexT.size, check);
				break;
				
			}
			case 4:		//lib
			{
				if (ArrOfFst[NUM].lex == 'w')
					AddId(buf, in.Line.front(), type, 2);
				if (ArrOfFst[NUM].lex == 'j')
					AddId(buf, in.Line.front(), type, 2);
				if (ArrOfFst[NUM].lex == 's')
					AddId(buf, in.Line.front(), type, 2);
				if (ArrOfFst[NUM].lex == 'm')
					AddId(buf, in.Line.front(), type, 2);
				int check = IT::IsId(idT, buf);
				AddLit(ArrOfFst[NUM].lex, in.Line.front(), check);
				break;
			}
			case 5:		//head
			{
				strncpy(pref, buf, 3);
				pref[3] = '\0';
				AddLit(ArrOfFst[NUM].lex, in.Line.front(), -1);
				head++;
				break;
			}
			case 6:		//operations
			{
				AddId(buf, in.Line.front(), 3, 5);
				AddLit(ArrOfFst[NUM].lex, lexT.size, IT::IsId(idT, buf));
				break;
			}
			}
			in.Words.pop();
			in.Line.pop();
			ravn--;
			if (idT.size == TI_MAXSIZE)
				throw ERROR_THROW(122);
			if (lexT.size == LT_MAXSIZE)
				throw ERROR_THROW(123);
		}
		if (head == 0)
			throw ERROR_THROW(124);
		if (head >= 2)
			throw ERROR_THROW(125);
		if (error)
			throw err;

		rc.Id = idT;
		rc.Lex = lexT;
		return rc;
	}
	void AddId(char* name, int str, int type, int idtype)
	{
		if (IT::IsDublId(idT, name) == TI_NULLIDX)
		{
			strcpy(idT.table[idT.size].id, name);
			idT.table[idT.size].idxfirstLE = str;
			//тип данных
			if (type == 1)
				idT.table[idT.size].iddatatype = IT::NUM;
			if (type == 2)
				idT.table[idT.size].iddatatype = IT::CYMB;
			if (type == 3)
				idT.table[idT.size].iddatatype = IT::CHAR;

			//тип ид
			if (idtype == 1)
				idT.table[idT.size].idtype = IT::V;
			if (idtype == 2)
				idT.table[idT.size].idtype = IT::F;
			if (idtype == 3)
				idT.table[idT.size].idtype = IT::P;
			if (idtype == 4)
				idT.table[idT.size].idtype = IT::L;
			if (idtype == 5)
				idT.table[idT.size].idtype = IT::O;
			idT.size++;
		}
	}
	void AddLit(char lex, int str, int id)
	{
		lexT.table[lexT.size].lexema = lex;
		lexT.table[lexT.size].sn = str;
		lexT.table[lexT.size].idxTI = id;
		lexT.size++;
	}
}