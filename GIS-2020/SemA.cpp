#include "stdafx.h"
#include "SemA.h"

namespace SemAn
{
	SemAnalize::SemAnalize(IT::IdTable IdT, LT::LexTable LexT)
	{
		lexT = LexT;
		idT = IdT;
		IsProc();
		Init();
		CheckRc();
		ParOfProc();
		ParOfStandProc();
		ParOfIf();
		Types();
		if (error)
			throw err;
	}
	void SemAnalize::IsProc()
	{
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == 'i')
			{
				if (idT.table[lexT.table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					if (lexT.table[i + 1].lexema != LEX_LEFTHESIS)
						throw ERROR_THROW_IN(703, lexT.table[i + 1].sn, -1);
				}
			}
		}
	}
	void SemAnalize::Init()
	{
		char ident[ID_MAXSIZE];
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == 'a')
			{
				strcpy(ident, idT.table[lexT.table[i + 2].idxTI].id);
				for (int j = 0; j < i; j++)
				{
					if (lexT.table[j].lexema == 'i')
						if (!strcmp(ident, idT.table[lexT.table[j].idxTI].id))
						{
							err.AddErr(700, lexT.table[j].sn, -1);
							error = true;
						}
				}
			}
		}
	}
	void SemAnalize::CheckRc()
	{
		
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == LEX_PROCEDURE)
			{
				int type = idT.table[lexT.table[i + 2].idxTI].iddatatype;

				for (int j = i; lexT.table[j].lexema != LEX_RIGHTBRACE; j++)
				{

					if (lexT.table[j].lexema == LEX_RC)
					{
						if (lexT.table[j + 1].lexema == LEX_ID)
						{
							if (idT.table[lexT.table[j + 1].idxTI].idtype == IT::IDTYPE::F || idT.table[lexT.table[j + 1].idxTI].idtype == IT::IDTYPE::O)
							{
								throw ERROR_THROW_IN(701, lexT.table[j].sn, -1);
							}

							if ((int)idT.table[lexT.table[j + 1].idxTI].iddatatype != type) //проверка на правильное возвращаемое значение
							{
								throw ERROR_THROW_IN(701, lexT.table[j].sn, -1);
							}

						}
					}
					i = j;
				}
			}
		}
	}
	void SemAnalize::ParOfProc()
	{
		char buf[ID_MAXSIZE];
		int par = 0;
		int procpar = 0;
		int str = 0;
		int count = 0;

		for (int i = 0; i < lexT.size; i++)
		{

			if (lexT.table[i].lexema == '=')
			{
				str = lexT.table[i].sn;
				while (lexT.table[i].lexema != ';')
				{
					i++;
					if (lexT.table[i].lexema == LEX_ID)
					{
						if (idT.table[lexT.table[i].idxTI].idtype == IT::IDTYPE::F)
						{
							strcpy(buf, idT.table[lexT.table[i].idxTI].id);
							for (int j = 0; j < i; j++)
							{
								if (lexT.table[j].lexema == LEX_ID && lexT.table[j - 2].lexema == LEX_PROCEDURE)
								{
									if (!strcmp(buf, idT.table[lexT.table[j].idxTI].id))
									{
										j++;
										for (j; lexT.table[j].lexema != ')'; j++)
										{
											if (lexT.table[j].lexema == LEX_ID)
											{
												procpar++;
												i += 2;
												if (idT.table[lexT.table[j].idxTI].iddatatype == IT::IDDATATYPE::NUM)
												{
													if (lexT.table[i].lexema == 'k')
														par++;
													if (lexT.table[i].lexema == LEX_ID)
														if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::NUM)
															par++;
												}
												if (idT.table[lexT.table[j].idxTI].iddatatype == IT::IDDATATYPE::CYMB)
												{
													if (lexT.table[i].lexema == 'l')
														par++;
													if (lexT.table[i].lexema == LEX_ID)
														if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::CYMB)
															par++;
												}
												if (idT.table[lexT.table[j].idxTI].iddatatype == IT::IDDATATYPE::CHAR)
												{
													if (lexT.table[i].lexema == 'q')
														par++;
													if (lexT.table[i].lexema == LEX_ID)
														if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::CHAR)
															par++;
												}
											}
										}
										if (procpar != par)
											throw ERROR_THROW_IN(702, str, -1)
										else if (lexT.table[i + 2].lexema != ';')
											throw ERROR_THROW_IN(702, str, -1)
											procpar = par = 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	void SemAnalize::ParOfStandProc()
	{
		for (int i = 0; i < lexT.size; i++)
		{
			switch (lexT.table[i].lexema)
			{
			case 'y':
			{
				if (lexT.table[i + 2].lexema == 'i')
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::CYMB && idT.table[lexT.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::CHAR)
					{
						err.AddErr(702, lexT.table[i].sn, -1);
						error = true;
					}
				break;
			}
			case 'x':
			{
				if (lexT.table[i + 2].lexema == 'i')
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::NUM)
					{
						err.AddErr(702, lexT.table[i].sn, -1);
						error = true;
					}
				break;
			}
			case 's':
			{
				if (lexT.table[i + 2].lexema == 'i')
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::NUM)
					{
						err.AddErr(702, lexT.table[i].sn, -1);
						error = true;
					}
				if (lexT.table[i + 4].lexema == 'i')
					if (idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::NUM)
					{
						err.AddErr(702, lexT.table[i].sn, -1);
						error = true;
					}
				break;
			}
			case 'j':
			{
				if (lexT.table[i + 2].lexema == 'i' && lexT.table[i + 4].lexema == 'i')
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::NUM &&
						idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::NUM)
						{
							err.AddErr(702, lexT.table[i].sn, -1);
							error = true;
						}
			
				break;
			}
			case 'w':
			{
				if (lexT.table[i + 2].lexema == 'i')
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::NUM)
						if (idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::NUM)
						{
							err.AddErr(702, lexT.table[i].sn, -1);
							error = true;
						}
				if (lexT.table[i + 4].lexema == 'i')
					if (idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::NUM)
						if (idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::NUM)
						{
							err.AddErr(702, lexT.table[i].sn, -1);
							error = true;
						}
				break;
			}
			case 'm':
			{
				if (lexT.table[i + 2].lexema == 'i')
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::CYMB)
						if (idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::CYMB)
						{
							err.AddErr(702, lexT.table[i].sn, -1);
							error = true;
						}
				if (lexT.table[i + 4].lexema == 'i')
					if (idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::CYMB)
						if (idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::CYMB)
						{
							err.AddErr(702, lexT.table[i].sn, -1);
							error = true;
						}
				break;
			}
			}
		}
	}
	/*void SemAnalize::NonProc()
	{
	for (int i = 0; i < lexT.size; i++)
	{
	if (lexT.table[i].lexema == '=')
	{
	if (idT.table[lexT.table[i - 1].idxTI].idtype == IT::IDTYPE::F)
	std::cout << "err of varzh";
	}
	}
	}*/
	void SemAnalize::TypesOfProc()
	{
		int datatype;
		for (int i = 0; i < lexT.size; i++)
		{
			int str = 0;
			if (lexT.table[i].lexema == '=')
			{
				str = lexT.table[i].sn;
				datatype = idT.table[lexT.table[i - 1].idxTI].iddatatype;
				while (lexT.table[i].lexema != LEX_SEMICOLON)
				{
					if (lexT.table[i].lexema == LEX_ID)
						if (idT.table[lexT.table[i].idxTI].idtype == IT::IDTYPE::F)
							if (idT.table[lexT.table[i].idxTI].iddatatype != datatype)
							{
								err.AddErr(704, str, -1);
								error = true;
							}
					if (lexT.table[i].lexema == 'a' || lexT.table[i].lexema == 'g' || lexT.table[i].lexema == 'z' || lexT.table[i].lexema == 's')
						if (datatype == IT::IDDATATYPE::CYMB)
						{
							err.AddErr(704, str, -1);
							error = true;
						}
					i++;
				}
			}
		}
	}
	void SemAnalize::Types()
	{
		int �tr = 0;
		int datatype = 0;
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == '=')
			{
				if (lexT.table[i + 2].lexema != ')')
				{
					�tr = lexT.table[i].sn;
					datatype = idT.table[lexT.table[i - 1].idxTI].iddatatype;
					while (lexT.table[i].lexema != LEX_SEMICOLON)
					{
						if (lexT.table[i].lexema == 'm' || lexT.table[i].lexema == 'j' || lexT.table[i].lexema == 's' || lexT.table[i].lexema == 'w')
							i += 5;
					
						if (lexT.table[i].lexema == LEX_ID)
						{
							if (idT.table[lexT.table[i].idxTI].idtype == IT::IDTYPE::F)
								while (lexT.table[i].lexema != ')')
									i++;

							if (lexT.table[i].lexema == LEX_ID)
							{
								if (idT.table[lexT.table[i].idxTI].iddatatype != datatype)
								{
									err.AddErr(704, �tr, -1);
									error = true;
								}
							}
						}
						i++;
					}
				}
			}
		}
	}
	void SemAnalize::ParOfIf()
	{
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == 'f')
			{
				if (lexT.table[i + 2].lexema == LEX_ID)
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::IDDATATYPE::NUM && 
						idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::NUM ||
						idT.table[lexT.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::NUM &&
						idT.table[lexT.table[i + 4].idxTI].iddatatype == IT::IDDATATYPE::NUM)
						throw ERROR_THROW_IN(702, lexT.table[i].sn, -1)
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::IDDATATYPE::NUM &&
						idT.table[lexT.table[i + 4].idxTI].iddatatype != IT::IDDATATYPE::NUM ||
						idT.table[lexT.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::NUM &&
						idT.table[lexT.table[i + 4].idxTI].iddatatype == IT::IDDATATYPE::NUM)
						throw ERROR_THROW_IN(702, lexT.table[i].sn, -1)		
			}			
		}
	}
}