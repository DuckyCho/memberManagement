#include "memberManagementSystem.h"




//function key�� �̿��� �Է¹ޱ� ȭ��
int functionKeyInput(void)
{
	int userInput;
	char * f1 = "F1ȸ������";
	char * f2 = "F2ȸ�����";
	char * f3 = "F3ȸ������";
	char * f4 = "F4ȸ����������";
	char * f5 = "F5ȸ���˻�";
	char * f10 = "F10���θ޴�";

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 14);
	printf("\n\n\n");
	centerJustIndent(75, hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("%s  %s  %s  ", f1, f2, f3);
	printf("%s  %s  %s", f4, f5, f10);
	SetConsoleTextAttribute(hConsole, 14);
	while (1)
	{
		userInput = getch();

		if (userInput == 59)
		{
			return 0;
		}
		else if (userInput == 60)
		{
			return 1;
		}
		else if (userInput == 61)
		{
			return 2;
		}
		else if (userInput == 62)
		{
			return 3;
		}
		else if (userInput == 63)
		{
			return 4;
		}
		else if (userInput == 68)
		{
			return -1;
		}
		else
		{
			printf("\a");
		}
	}


}

//���� UI�Լ�

int printMain(void)
{
	HANDLE hConsole;
	int userInput = -1;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	mainUI(0);

	//fputs(str, 2);
	/* ���� ����ǥ ��¿�*/
	/*
	for (int k = 0; k < 255; k++)
	{
	SetConsoleTextAttribute(hConsole, k);
	printf("%4d  %s\n", k, "Hello______________");
	}
	*/

	if (GetAsyncKeyState(VK_UP)) Sleep(100);
	if (GetAsyncKeyState(VK_DOWN))Sleep(100);
	if (GetAsyncKeyState(VK_RETURN))Sleep(100);

	while (1)
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			userInput = mainUI(1);
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			userInput = mainUI(-1);
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			Sleep(200);
			mainUI(-80);
			getchar();
			return userInput;
		}
	}
}

void centerJustIndent(int string, HANDLE hConsole)//��� ������ ���� indent�� ��������
{

	int indentForCenterJust;
	char space = ' ';
	indentForCenterJust = (basicStringSize - string) / 2;
	SetConsoleTextAttribute(hConsole, 15);
	for (int i = 0; i < indentForCenterJust; i++)	printf("%c", space);
}


int mainUI(int upOrDown)
{
	static int now=0;
	HANDLE hConsole;

	int userInput = 0;
	char * decoUpperline = "��������������������������������������������������";
	char * block = "��                                              ��";
	char * decoLowerline = "��������������������������������������������������";
	char * title = "��    ȸ   ��   ��   ��   ��   ��   ��   ��     ��";
	char * menu1 = "1. ȸ�� ����";
	char * menu2 = "2. ȸ�� ����ϱ�";
	char * menu3 = "3. ȸ�� �����ϱ�";
	char * menu4 = "4. ȸ������ �����ϱ�";
	char * menu5 = "5. ȸ�� �˻��ϱ�";
	char * menu6 = "6. �����ϱ�";
	char * menu7 = "7. �����ϱ�";
	char * menu8 = "0. Credit";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	now += upOrDown;

	if (now <-20 || now == -1)
	{
		now = 0;
		system("cls");
	}
	else if (now == 8)
	{
		now = 7;
		system("cls");
	}

	system("cls");
	centerJustIndent(strlen(decoUpperline), hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("%s\n", decoUpperline);

	centerJustIndent(strlen(block), hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("%s\n", block);

	centerJustIndent(strlen(title), hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("%s\n", title);

	centerJustIndent(strlen(block), hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("%s\n", block);

	centerJustIndent(strlen(decoUpperline), hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("%s\n", decoLowerline);

	printf("\n\n\n");


	if (now == 0){
		centerJustIndent(strlen(menu1), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu1);
	}
	else{
		centerJustIndent(strlen(menu1), hConsole);
		printf("%s\n\n", menu1);
	}

	if (now == 1){
		centerJustIndent(strlen(menu2), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu2);
	}
	else{
		centerJustIndent(strlen(menu2), hConsole);
		printf("%s\n\n", menu2);
	}

	if (now == 2){
		centerJustIndent(strlen(menu3), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu3);
	}
	else{
		centerJustIndent(strlen(menu3), hConsole);
		printf("%s\n\n", menu3);
	}

	if (now == 3){
		centerJustIndent(strlen(menu4), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu4);
	}
	else{
		centerJustIndent(strlen(menu4), hConsole);
		printf("%s\n\n", menu4);
	}

	if (now == 4){
		centerJustIndent(strlen(menu5), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu5);
	}
	else{
		centerJustIndent(strlen(menu5), hConsole);
		printf("%s\n\n", menu5);
	}

	if (now == 5){
		centerJustIndent(strlen(menu6), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu6);
	}
	else{
		centerJustIndent(strlen(menu6), hConsole);
		printf("%s\n\n", menu6);
	}

	if (now == 6){
		centerJustIndent(strlen(menu7), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu7);
	}
	else{
		centerJustIndent(strlen(menu7), hConsole);
		printf("%s\n\n", menu7);
	}

	if (now == 7){
		centerJustIndent(strlen(menu8), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu8);
		SetConsoleTextAttribute(hConsole, 14);
		printf("\n");
	}
	else{
		centerJustIndent(strlen(menu8), hConsole);
		printf("%s\n\n", menu8);
	}

	printf("\n");
	fflush(stdin);
	return now;
}
