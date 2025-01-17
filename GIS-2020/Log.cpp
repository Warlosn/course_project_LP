#include "stdafx.h"


namespace Log
{
	LOG GetLog(wchar_t logfile[])
	{
		static std::ofstream stream(logfile);
		stream.seekp(0);
		LOG f;
		f.stream = &stream;
		wcscpy_s(f.logfile, logfile);
		f.stream->is_open();
		if (f.stream->fail())
		{
			throw ERROR_THROW(112);
		}
		return f;
	}
	void WriteLine(LOG log, char* c, ...)
	{
		char** p = &c;
		while (strcmp(*p, ""))
		{
			*(log.stream) << *p;
			p++;
		}
	}
	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t** p = &c;
		char buf[PARM_MAX_SIZE];
		while (wcscmp(*p, L""))
		{
			wcstombs(buf, *p, PARM_MAX_SIZE);
			*(log.stream) << buf;
			p++;
		}
	}
	void WriteLog(LOG log)
	{
		*(log.stream) << "--- �������� ----" << std::endl;
		time_t sec;
		char buf[80];
		time(&sec);
		tm* k = localtime(&sec);
		strftime(buf, 80, " %x %X", k);
		*(log.stream) << "����: " << buf << std::endl;
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char buf[PARM_MAX_SIZE];
		*(log.stream) << "---- ��������� --------" << std::endl;
		wcstombs(buf, parm.log, PARM_MAX_SIZE);
		*(log.stream) << "-log: " << buf << std::endl;
		wcstombs(buf, parm.in, PARM_MAX_SIZE);
		*(log.stream) << "-in: " << buf << std::endl;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*(log.stream) << "--- �������� ������ ------" << std::endl;
		*(log.stream) << "���������� ��������: " << in.size << std::endl;
		*(log.stream) << "���������� �����: " << in.lines << std::endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		*(log.stream) << "������ " << error.id << ": " << error.message << std::endl;
		*(log.stream) << "������ " << error.inext.line << " ������� " << error.inext.col << std::endl;
	}
	void WriteLexTable(LOG log, LT::LexTable lexT)
	{
		*(log.stream) << "\n\n------------------������� ������--------------------" << std::endl;
		*(log.stream) << "����� | ������� |  ��� � ��  \n";
		for (int i = 0; i < lexT.size; i++)
			*(log.stream) << i << "\t   " << lexT.table[i].lexema << "\t   " << lexT.table[i].idxTI << std::endl;
	}
	void WriteIdTable(LOG log, IT::IdTable idT)
	{
		*(log.stream) << "\n------------������� ���������������-------------" << std::endl;

		for (int i = 0; i < idT.size; i++)
		{
			*(log.stream) << "� " << i << std::endl;
			*(log.stream) << "��� ��������������: " << idT.table[i].id << std::endl;
			if (idT.table[i].iddatatype == 1)
				*(log.stream) << "��� ������ : NUM" << std::endl;
			if (idT.table[i].iddatatype == 2)
				*(log.stream) << "��� ������ : CYMB" << std::endl;
			if (idT.table[i].iddatatype == 3) {
				*(log.stream) << "��� ������ : CHAR" << std::endl;
			}
			if (idT.table[i].idtype == 1)
				*(log.stream) << "��� ��������������: ����������" << std::endl;
			if (idT.table[i].idtype == 2)
				*(log.stream) << "��� ��������������: �������" << std::endl;
			if (idT.table[i].idtype == 3)
				*(log.stream) << "��� ��������������: ��������" << std::endl;
			if (idT.table[i].idtype == 4)
				*(log.stream) << "��� ��������������: �������" << std::endl;
			if (idT.table[i].idtype == 5)
				*(log.stream) << "��� ��������������: ��������" << std::endl;
			if (idT.table[i].idtype != 2)
			{
				if (idT.table[i].iddatatype == IT::NUM)
					*(log.stream) << "��������: " << idT.table[i].value.vint << std::endl;
				if (idT.table[i].iddatatype == IT::CYMB)
				{
					*(log.stream) << "��������: " << idT.table[i].value.vstr.str << std::endl;
					*(log.stream) << "�����: " << idT.table[i].value.vstr.len << std::endl;
				}
				if (idT.table[i].iddatatype == IT::CHAR)
				{
					*(log.stream) << "��������: " << idT.table[i].value.vstr.str << std::endl;
				}
			}
			*(log.stream) << std::endl;
		}
	}

	void writeIntermediateCode(LOG& log, LT::LexTable& Lextable)
	{
		int pb = NULL;
		char* buffer = new char[1024];
		*log.stream << "\n---------������������� ���------------------------------\n";
		for (int i = 0; i < Lextable.size; i++)
		{
			buffer[pb] = Lextable.table[i].lexema;
			pb++;
			if (Lextable.table[i + 1].sn != Lextable.table[i].sn)
			{
				buffer[pb] = '\0';
				if (Lextable.table[i].sn < 10)
				{
					*log.stream << '0';
				}

				*log.stream << Lextable.table[i].sn << ' ';
				*log.stream << buffer << std::endl;
				pb = NULL;
			}
		}
	}

	void Close(LOG log)
	{
		log.stream->close();
	}
}
