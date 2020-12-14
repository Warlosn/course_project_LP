#pragma once
#include "stdafx.h"
#include <iostream>
#define LEX_NEWPROC '@'

namespace PN
{
	void PolishNateishion(LT::LexTable* LexT, IT::IdTable* IdT);
	void Conversation(LT::LexTable* LexT, IT::IdTable* IdT, int position);
	int ArifmPriorities(char symb);
}
