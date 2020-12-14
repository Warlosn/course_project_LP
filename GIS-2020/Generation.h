#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>

namespace CG
{
	struct Gener
	{
		LT::LexTable lexT;
		IT::IdTable idT;
		std::ofstream out;

		Gener(LT::LexTable lexT, IT::IdTable IdT);

		void Head();
		void Constants();
		void Data();
		void Code();
	};
}
