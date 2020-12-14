#include "stdafx.h"
#include "FST.h"
//#include "CustomFST.h";
//using namespace CustomFST;

namespace FST
{
	bool step(FST& fst, short*& rstates)	//один шаг автомата
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);	//смена массивов
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					};
				};
		};
		return rc;
	};
	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;				//продвинули позицию
			rc = step(fst, rstates);	//один шаг автомата
		};
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	}
	RELATION::RELATION(char c, short nn)
	{
		symbol = c;
		nnode = nn;
	};
	NODE::NODE()	//по умолчанию
	{
		n_relation = 0;
		RELATION* relations = NULL;
	};
	NODE::NODE(short n, RELATION rel, ...)	//с параметрами
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	};
	FST::FST(const char* s, char l, LEXAN plexsw, short ns, NODE n, ...)
	{
		string = s;
		lex = l;
		nstates = ns;
		lexsw = plexsw;
		nodes = new NODE[ns];
		NODE* p = &n;
		for (int k = 0; k < ns; k++) nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
	};
	
	FST::FST()
	{}

	FST* ArrFst()
	{
		FST fstNum("", 'n', TYPE, 4,
			NODE(1, RELATION('n', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('m', 3)),
			NODE());
		FST fstCymb("", 'c', TYPE, 5,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('y', 2)),
			NODE(1, RELATION('m', 3)),
			NODE(1, RELATION('b', 4)),
			NODE());
		FST fstChar("", 'u', TYPE, 5,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('h', 2)),
			NODE(1, RELATION('a', 3)),
			NODE(1, RELATION('r', 4)),
			NODE());
		FST fstAct("", 'a', LEXEMS, 4,
			NODE(1, RELATION('a', 1)),
			NODE(1, RELATION('c', 2)),
			NODE(1, RELATION('t', 3)),
			NODE());
		FST fstProcedure("", 'p', LEXEMS, 10,
			NODE(1, RELATION('p', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('o', 3)),
			NODE(1, RELATION('c', 4)),
			NODE(1, RELATION('e', 5)),
			NODE(1, RELATION('d', 6)),
			NODE(1, RELATION('u', 7)),
			NODE(1, RELATION('r', 8)),
			NODE(1, RELATION('e', 9)),
			NODE());
		FST fstRc("", 'r', LEXEMS, 3,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('c', 2)),
			NODE());
		FST fstHead("", 'h', HEAD, 5,
			NODE(1, RELATION('h', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('a', 3)),
			NODE(1, RELATION('d', 4)),
			NODE());
		FST fstWriteS("", 'y', LIB, 7,
			NODE(1, RELATION('w', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('t', 4)),
			NODE(1, RELATION('e', 5)),
			NODE(1, RELATION('s', 6)),
			NODE());
		FST fstWriteD("", 'x', LIB, 7,
			NODE(1, RELATION('w', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('t', 4)),
			NODE(1, RELATION('e', 5)),
			NODE(1, RELATION('d', 6)),
			NODE());
		FST fstKvadro("", 'w', LIB, 7,
			NODE(1, RELATION('k', 1)),
			NODE(1, RELATION('v', 2)),
			NODE(1, RELATION('a', 3)),
			NODE(1, RELATION('d', 4)),
			NODE(1, RELATION('r', 5)),
			NODE(1, RELATION('o', 6)),
			NODE());
		FST fstExpn("", 'j', LIB, 5,
			NODE(1, RELATION('e', 1)),
			NODE(1, RELATION('x', 2)),
			NODE(1, RELATION('p', 3)),
			NODE(1, RELATION('n', 4)),
			NODE());
		FST fstComp("", 'm', LIB, 5,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('m', 3)),
			NODE(1, RELATION('p', 4)),
			NODE());
		FST fstSum("", 's', LIB, 4,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('m', 3)),
			NODE());
		FST fstIf("", 'f', LEXEMS, 5,
			NODE(1, RELATION('w', 1)),
			NODE(1, RELATION('h', 2)),
			NODE(1, RELATION('e', 3)),
			NODE(1, RELATION('n', 4)),
			NODE());
		FST fstElse("", 'e', LEXEMS, 5,
			NODE(1, RELATION('e', 1)),
			NODE(1, RELATION('l', 2)),
			NODE(1, RELATION('s', 3)),
			NODE(1, RELATION('e', 4)),
			NODE());

		FST fstNumLitV("", 'v', LIT, 2,
			NODE(1, RELATION('v', 1)),
			NODE(8, RELATION('0', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1),
				RELATION('4', 1), RELATION('5', 1), RELATION('6', 1), RELATION('7', 1)));

		FST fstNumLitD("", 'd', LIT, 2,
			NODE(1, RELATION('d', 1)),
			NODE(2, RELATION('0', 1), RELATION('1', 1)));

		FST fstSLit("", 'q', LIT, 4,
			NODE(1, RELATION('\'', 1)), \
			NODE(52, RELATION('a', 2), RELATION('A', 2), \
				RELATION('b', 2), RELATION('B', 2), RELATION('c', 2), RELATION('C', 2), RELATION('d', 2), RELATION('D', 2), \
				RELATION('e', 2), RELATION('E', 2), RELATION('f', 2), RELATION('F', 2), RELATION('g', 2), RELATION('G', 2), \
				RELATION('h', 2), RELATION('H', 2), RELATION('i', 2), RELATION('I', 2), RELATION('j', 2), RELATION('J', 2), \
				RELATION('k', 2), RELATION('K', 2), RELATION('l', 2), RELATION('L', 2), RELATION('m', 2), RELATION('M', 2), \
				RELATION('n', 2), RELATION('N', 2), RELATION('o', 2), RELATION('O', 2), RELATION('p', 2), RELATION('P', 2), \
				RELATION('q', 2), RELATION('Q', 2), RELATION('r', 2), RELATION('R', 2), RELATION('s', 2), RELATION('S', 2), \
				RELATION('t', 2), RELATION('T', 2), RELATION('u', 2), RELATION('U', 2), RELATION('v', 2), RELATION('V', 2), \
				RELATION('w', 2), RELATION('W', 2), RELATION('x', 2), RELATION('X', 2), RELATION('y', 2), RELATION('Y', 2), \
				RELATION('z', 2), RELATION('Z', 2)), \
			NODE(1, RELATION('\'', 3)), \
			NODE());

		FST fstCLit("", 'l', LIT, 5,
			NODE(1, RELATION('\"', 1)), \
			NODE(125, RELATION(' ', 2), RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2), ('e', 2), RELATION('f', 2), \
				RELATION('g', 2), RELATION('h', 2), RELATION('i', 2), RELATION('j', 2), RELATION('k', 2), RELATION('l', 2), \
				RELATION('m', 2), RELATION('n', 2), RELATION('o', 2), RELATION('p', 2), RELATION('q', 2), RELATION('r', 2), \
				RELATION('s', 2), RELATION('t', 2), RELATION('u', 2), RELATION('v', 2), RELATION('w', 2), RELATION('x', 2), \
				RELATION('y', 2), RELATION('z', 2), RELATION('A', 2), RELATION('B', 2), RELATION('C', 2), RELATION('D', 2), \
				RELATION('E', 2), RELATION('F', 2), RELATION('G', 2), RELATION('H', 2), RELATION('I', 2), RELATION('J', 2), \
				RELATION('K', 2), RELATION('L', 2), RELATION('M', 2), RELATION('N', 2), RELATION('O', 2), RELATION('P', 2), \
				RELATION('Q', 2), RELATION('R', 2), RELATION('S', 2), RELATION('T', 2), RELATION('U', 2), RELATION('V', 2), \
				RELATION('W', 2), RELATION('X', 2), RELATION('Y', 2), RELATION('Z', 2),
				RELATION('0', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), RELATION('5', 2),
				RELATION('6', 2), RELATION('7', 2), RELATION('8', 2), RELATION('9', 2),
				RELATION('a', 3), RELATION('b', 3), RELATION('c', 3), RELATION('d', 3), \
				RELATION('e', 3), RELATION('f', 3), RELATION('g', 3), RELATION('h', 3), RELATION('i', 3), RELATION('j', 3), \
				RELATION('k', 3), RELATION('l', 3), RELATION('m', 3), RELATION('n', 3), RELATION('o', 3), RELATION('p', 3), \
				RELATION('q', 3), RELATION('r', 3), RELATION('s', 3), RELATION('t', 3), RELATION('u', 3), RELATION('v', 3), \
				RELATION('w', 3), RELATION('x', 3), RELATION('y', 3), RELATION('z', 3),
				RELATION('A', 3), RELATION('B', 3), RELATION('C', 3), RELATION('D', 3), RELATION('E', 3), RELATION('F', 3), \
				RELATION('G', 3), RELATION('H', 3), RELATION('I', 3), RELATION('J', 3), RELATION('K', 3), RELATION('L', 3), \
				RELATION('M', 3), RELATION('N', 3), RELATION('O', 3), RELATION('P', 3), RELATION('Q', 3), RELATION('R', 3), \
				RELATION('S', 3), RELATION('T', 3), RELATION('U', 3), RELATION('V', 3), RELATION('W', 3), RELATION('X', 3), \
				RELATION('Y', 3), RELATION('Z', 3),
				RELATION('0', 3), RELATION('1', 3), RELATION('2', 3), RELATION('3', 3), RELATION('4', 3), RELATION('5', 3), \
				RELATION('6', 3), RELATION('7', 3), RELATION('8', 3), RELATION('9', 3)), \
			NODE(125, RELATION(' ', 2), RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2), ('e', 2), RELATION('f', 2), \
				RELATION('g', 2), RELATION('h', 2), RELATION('i', 2), RELATION('j', 2), RELATION('k', 2), RELATION('l', 2), \
				RELATION('m', 2), RELATION('n', 2), RELATION('o', 2), RELATION('p', 2), RELATION('q', 2), RELATION('r', 2), \
				RELATION('s', 2), RELATION('t', 2), RELATION('u', 2), RELATION('v', 2), RELATION('w', 2), RELATION('x', 2), \
				RELATION('y', 2), RELATION('z', 2), RELATION('A', 2), RELATION('B', 2), RELATION('C', 2), RELATION('D', 2), \
				RELATION('E', 2), RELATION('F', 2), RELATION('G', 2), RELATION('H', 2), RELATION('I', 2), RELATION('J', 2), \
				RELATION('K', 2), RELATION('L', 2), RELATION('M', 2), RELATION('N', 2), RELATION('O', 2), RELATION('P', 2), \
				RELATION('Q', 2), RELATION('R', 2), RELATION('S', 2), RELATION('T', 2), RELATION('U', 2), RELATION('V', 2), \
				RELATION('W', 2), RELATION('X', 2), RELATION('Y', 2), RELATION('Z', 2),
				RELATION('0', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), RELATION('5', 2),
				RELATION('6', 2), RELATION('7', 2), RELATION('8', 2), RELATION('9', 2),
				RELATION('a', 3), RELATION('b', 3), RELATION('c', 3), RELATION('d', 3), \
				RELATION('e', 3), RELATION('f', 3), RELATION('g', 3), RELATION('h', 3), RELATION('i', 3), RELATION('j', 3), \
				RELATION('k', 3), RELATION('l', 3), RELATION('m', 3), RELATION('n', 3), RELATION('o', 3), RELATION('p', 3), \
				RELATION('q', 3), RELATION('r', 3), RELATION('s', 3), RELATION('t', 3), RELATION('u', 3), RELATION('v', 3), \
				RELATION('w', 3), RELATION('x', 3), RELATION('y', 3), RELATION('z', 3),
				RELATION('A', 3), RELATION('B', 3), RELATION('C', 3), RELATION('D', 3), RELATION('E', 3), RELATION('F', 3), \
				RELATION('G', 3), RELATION('H', 3), RELATION('I', 3), RELATION('J', 3), RELATION('K', 3), RELATION('L', 3), \
				RELATION('M', 3), RELATION('N', 3), RELATION('O', 3), RELATION('P', 3), RELATION('Q', 3), RELATION('R', 3), \
				RELATION('S', 3), RELATION('T', 3), RELATION('U', 3), RELATION('V', 3), RELATION('W', 3), RELATION('X', 3), \
				RELATION('Y', 3), RELATION('Z', 3),
				RELATION('0', 3), RELATION('1', 3), RELATION('2', 3), RELATION('3', 3), RELATION('4', 3), RELATION('5', 3), \
				RELATION('6', 3), RELATION('7', 3), RELATION('8', 3), RELATION('9', 3)), \
			NODE(1, RELATION('\"', 4)),
			NODE());

		FST fstId("", 'i', ID, 2,
			NODE(52, RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0), RELATION('e', 0),
				RELATION('f', 0), RELATION('g', 0), RELATION('h', 0), RELATION('i', 0), RELATION('j', 0),
				RELATION('k', 0), RELATION('l', 0), RELATION('m', 0), RELATION('n', 0), RELATION('o', 0),
				RELATION('p', 0), RELATION('q', 0), RELATION('r', 0), RELATION('s', 0), RELATION('t', 0),
				RELATION('u', 0), RELATION('v', 0), RELATION('w', 0), RELATION('x', 0), RELATION('y', 0),
				RELATION('z', 0),
				RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1),
				RELATION('f', 1), RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1),
				RELATION('k', 1), RELATION('l', 1), RELATION('m', 1), RELATION('n', 1), RELATION('o', 1),
				RELATION('p', 1), RELATION('q', 1), RELATION('r', 1), RELATION('s', 1), RELATION('t', 1),
				RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1), RELATION('y', 1),
				RELATION('z', 1)),
			NODE());
		FST fstPlus("", '+', OPERATOR, 2,
			NODE(1, RELATION('+', 1)),
			NODE());
		FST fstMinus("", '-', OPERATOR, 2,
			NODE(1, RELATION('-', 1)),
			NODE());
		FST fstStar("", '*', OPERATOR, 2,
			NODE(1, RELATION('*', 1)),
			NODE());
		FST fstLeftIf("", '[', LEXEMS, 2,
			NODE(1, RELATION('[', 1)),
			NODE());
		FST fstRighIf("", ']', LEXEMS, 2,
			NODE(1, RELATION(']', 1)),
			NODE());
		FST fstLeftBr("", '(', LEXEMS, 2,
			NODE(1, RELATION('(', 1)),
			NODE());
		FST fstRighBr("", ')', LEXEMS, 2,
			NODE(1, RELATION(')', 1)),
			NODE());
		FST fstLeftBlock("", '{', LEXEMS, 2,
			NODE(1, RELATION('{', 1)),
			NODE());
		FST fstRighBlock("", '}', LEXEMS, 2,
			NODE(1, RELATION('}', 1)),
			NODE());
		FST fstSemicolon("", ';', LEXEMS, 2,
			NODE(1, RELATION(';', 1)),
			NODE());
		FST fstDot("", '.', LEXEMS, 2,
			NODE(1, RELATION('.', 1)),
			NODE());
		FST fstComma("", ',', LEXEMS, 2,
			NODE(1, RELATION(',', 1)),
			NODE());
		FST fstRavno("", '=', LEXEMS, 2,
			NODE(1, RELATION('=', 1)),
			NODE());
		FST fstLess("", '<', OPERATOR, 2,
			NODE(1, RELATION('<', 1)),
			NODE());
		FST fstMore("", '>', OPERATOR, 2,
			NODE(1, RELATION('>', 1)),
			NODE());
		FST fstLessOr("", '&', OPERATOR, 2,
			NODE(1, RELATION('&', 1)),
			NODE());
		FST fstMoreOr("", '!', OPERATOR, 2,
			NODE(1, RELATION('!', 1)),
			NODE());

		FST* rc = new FST[ARR_FST_SIZE];
		rc[0] = fstProcedure;		//
		rc[1] = fstHead;
		rc[2] = fstChar;		//
		rc[3] = fstNumLitV;			//
		rc[4] = fstDot;				//
		rc[5] = fstComma;			//
		rc[6] = fstAct;				//
		rc[7] = fstNum;				//	
		rc[8] = fstCymb;				//
		rc[9] = fstLeftBr;			//
		rc[10] = fstLeftBlock;		//
		rc[11] = fstLeftIf;
		rc[12] = fstRc;				//
		rc[13] = fstWriteS;			//
		rc[14] = fstWriteD;
		rc[15] = fstKvadro;
		rc[16] = fstExpn;
		rc[17] = fstComp;
		rc[18] = fstSum;
		rc[19] = fstIf;
		rc[20] = fstElse;
		rc[21] = fstPlus;
		rc[22] = fstMinus;
		rc[23] = fstStar;
		rc[24] = fstLess;
		rc[25] = fstMore;
		rc[26] = fstLessOr;
		rc[27] = fstMoreOr;
		rc[28] = fstRavno;			//
		rc[29] = fstRighBr;			//
		rc[30] = fstRighBlock;		//
		rc[31] = fstRighIf;
		rc[32] = fstSemicolon;		//
		rc[33] = fstId;				//
		rc[34] = fstCLit;
		rc[35] = fstSLit;
		rc[36] = fstNumLitD; //
		return rc;
	}
}