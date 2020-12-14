#pragma once
#include "stdafx.h"
#include <queue>
#define IN_MAX_LEN_TEXT 1024*1024		//������������ ������� ��������� ���� 1��
#define IN_CODE_ENDL	'\n'			//������ ����� ������
#define CYMB_NUMB_SEP	'|'				// ��������� ��� ����� ������
#define IN_CODE_SPACE	' '				//�������
#define IN_WORD_MAX_LEN 255				//������������ ������ �����

//������� �������� ������� ����������, ������ = ��� (Windows 1251) �������
//�������� IN::F - ����������� ������, IN::T  - ����������� ������,  IN::I - ������������(�� �������),
//		���� 0<=�������� <256 - �� �������� ������ ��������
#define IN_CODE_TABLE {\
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::T, IN::T, IN::S, IN::S, IN::S, IN::S, IN::S, IN::S, IN::F, IN::F, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::S, IN::S, IN::S, IN::T, IN::F, \
    IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::F, IN::S, IN::F, IN::F, \
    IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::F, IN::S, IN::F, IN::F, \
     \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T \
    }

//IN::S -- ����������   (  )	*	+	,	-	;	=	{	}
namespace In
{

    struct IN
    {
        enum { T = 1, F = 2, S = 3 };		//� - ����������� ������ F - ������������ S - ��������
        int size;							//������ ��������� ����
        int lines;							//���-�� �����
        std::queue<std::string> Words;
        std::queue<int> Line;
        int code[256] = IN_CODE_TABLE;		//������� �������
    };
    IN getin(wchar_t infile[]);				//������ � �������� ������� �����
};