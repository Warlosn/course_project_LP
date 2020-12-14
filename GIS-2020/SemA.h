#pragma once
#include "stdafx.h"
#include <iostream>

namespace SemAn
{
	struct SemAnalize
	{
		LT::LexTable lexT;
		IT::IdTable idT;
		Error::ARR_OF_ERRORS err;
		bool error = false;

		SemAnalize(IT::IdTable IdT, LT::LexTable LexT);
		void Init();
		void CheckRc();
		void ParOfProc();
		void ParOfStandProc();
		void NonProc();
		void TypesOfProc();
		void Types();
		void IsProc();
		void ParOfIf();
	};
}
