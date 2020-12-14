#pragma once
#define LEXEMA_FIXZISE 1				//������������� ������ �������
#define LT_MAXSIZE 4096					//������������ ���-�� ����� � ������� ������
#define LT_TI_NULLIDX 0xffffffff		//��� �������� ������� ���������������
#define LEX_NUM			'n'		//	������� ��� �����
#define LEX_CYMB		'c'		//	������� ��� �����
#define LEX_CHAR		'u'	
#define LEX_ACT			'a'		//	������� ��� ���������� ���������������
#define LEX_PROCEDURE	'p'		//	������� ��� ���������� ��������
#define LEX_RC			'r'		//	����������� ��������
#define LEX_HEAD		'h'		//	����� �����
#define LEX_WRITE		'w'		//	����� ������
#define LEX_ID			'i'		//	�������������
#define LEX_LITERALCHAR	'q'		//	������� ���������
#define LEX_LITERALCYMB	'l'		//	������� ���������
#define LEX_LITERALNUMV	'v'		//	������� ��������
#define LEX_LITERALNUMD	'd'	
#define LEX_LITERALNUM	'k'	
#define LEX_SEMICOLON	';'		//	;
#define LEX_COMMA		','		//	,
#define LEX_LEFTBRACE	'{'		//	{
#define LEX_RIGHTBRACE	'}'		//	}
#define LEX_LEFTHESIS	'('		//	(
#define LEX_RIGHTHESIS	')'		//	)
#define LEX_PLUS		'+'		//	+
#define LEX_MINUS		'-'		//	-
#define LEX_STAR		'*'		//	*
#define	LEX_SLASH		'/'		//	/
#define LEX_RAVNO		'='		//=

namespace LT
{							//������� ������
	struct Entry
	{
		char lexema;		//�������
		int sn;				//����� ������ � �������� ����
		int idxTI;			//������ � ������� ��������������� 
	};
	struct LexTable
	{
		int maxize;							//������� ������� ������ 
		int size;							//������� ������ ������� ������
		Entry* table;						//������ ����� ������� ������	
	};
	LexTable Create(						//������� ������
		int size							//�������
	);
	Entry GetEntry(LexTable& lextable, int n);
	Entry Add(								//�������� ������ ������� ������
		LexTable& lextable,					//��������� ������� ������
		Entry entry							//������ ������ ������
	);
	void Delete(LexTable& lextable);		//������� ������� ������
}
