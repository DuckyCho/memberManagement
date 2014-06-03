#include "memberManagementSystem.h"

/* 1. ȸ������ */

//printList�Լ����� ���� ������ ����Ʈ�ϰ� readTree�Լ��� �ҷ��ͼ� node�� ���
int printList(member * node, member * leafNull)
{
	int userInput = 0;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("I    D   �� ��\t      �ּ�  \t\t   ��ȭ��ȣ\n");
	centerJustIndent(63, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("��������������������������������������������������������������\n");

	readTree(node, leafNull, NULL);//tree���� node���� ���� �о ����Ʈ�ϴ��Լ�

	fflush(stdin);
	userInput = functionKeyInput_WhenSearchResultVoid();
	fflush(stdin);
	
	return userInput;

}

//���� ��ȸ�� Ʈ���� �о�� id�������� ���ĵǾ� print��
void readTree(member * node, member *leafNull, void(*writeDataToTxt)(member *))
{
	HANDLE hConsole;


	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (node->left != leafNull)
	{
		readTree(node->left, leafNull, writeDataToTxt);
		if (!*writeDataToTxt)
		{
			SetConsoleTextAttribute(hConsole, 15);
			centerJustIndent(60, hConsole);
			printf("%-9d%-9s%-25s\t%s\n", node->id, node->name, node->address, node->phone);
		}
		else
		{
			writeDataToTxt(node);
		}
	}

	else
	{
		if (!*writeDataToTxt)
		{
			SetConsoleTextAttribute(hConsole, 15);
			centerJustIndent(60, hConsole);
			printf("%-9d%-9s%-25s\t%s\n", node->id, node->name, node->address, node->phone);
		}
		else
		{
			writeDataToTxt(node);
		}
	}

	if (node->right != leafNull)
	{
		readTree(node->right, leafNull, writeDataToTxt);
	}
}



/* 2. ȸ�� ����ϱ� */
int addData(rootPointer * RP, member * leafNull)//�Է¹��� ȸ���� ������ RB�� ����
{
	int userInput = 0;
	int nodeOfBiggestId;
	member * node;
	member * node_copy;
	node = addNode();
	node_copy = addNode();

	nodeOfBiggestId = searchBiggestId(RP->rootNode, leafNull);
	node->id = nodeOfBiggestId + 1;
	inputData(node, leafNull);

	node_copy->id = node -> id;
	strcpy(node_copy->address, node->address);
	strcpy(node_copy->name, node->name);
	strcpy(node_copy->phone, node->phone);
	node_copy->left = leafNull;
	node_copy->right = leafNull;

	attachTree(node, RP, leafNull);
	redBlackTree(node, RP, leafNull);


	attachTreeN(node_copy, RP, leafNull);
	redBlackTreeN(node_copy, RP, leafNull);
	
	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	return userInput;
}

void inputData(member * node, member * leafNull)//���ο� ȸ���� ������ �Է�
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	fflush(stdin);
	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("�߰��Ͻ� ȸ���� ������ �Է��ϼ���\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("��������������������������������������������������������������\n");
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("��    ��: ");
	scanf("%s", &(node->name));

	fflush(stdin);
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("��    ��: ");
	gets(node->address);
	fflush(stdin);
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("��ȭ��ȣ: ");
	gets(node->phone);
	fflush(stdin);

	phoneCheck(node);

	node->father = NULL;
	node->color = red;
	node->left = leafNull;
	node->right = leafNull;

}

int searchBiggestId(member * node, member* leafNull)
{
	if (node->right == leafNull)
	{
		return node->id;
	}
	else
	{
		return searchBiggestId(node->right, leafNull);
	}
}

/* 6. �����ϱ� */

int saveData(rootPointer * RP, member * leafNull)
{
	FILE * fp;
	HANDLE hConsole;
	char forCount[basicStringSize];
	int count = 0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fp = fopen("data.txt", "wt");
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%s\t%s\t%s\t%s\n", "ID", "�̸�", "�ּ�", "��ȭ��ȣ");
	fclose(fp);

	readTree(RP->rootNode, leafNull, writeDataToTxt);


	fp = fopen("data.txt", "rt");
	fseek(fp, 0, SEEK_SET);
	while (fgets(forCount, basicStringSize, fp))
	{
		count++;
	}
	fclose(fp);

	printf("\n\n");
	centerJustIndent(35, hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("Saving has successfully done!\n");
	centerJustIndent(26, hConsole);
	printf("Total member : %d��\n\n", count);
	centerJustIndent(40, hConsole);
	printf("Press anykey to go to MainMenu....\n", count);
	if (getche())
	{
		fflush(stdin);
		return -1;
	}
}

void writeDataToTxt(member * node)
{
	FILE * fp;
	fp = fopen("data.txt", "r+");
	fseek(fp, 0, SEEK_END);

	fprintf(fp, "%d\t%s\t%s\t%s\n", node->id, node->name, node->address, node->phone);

	fclose(fp);

}




/* 8.Credit ���� */

int credit(void)
{
	HANDLE hConsole;
	char * line1 = "NHN NEXT 2014 ���α׷��ֿ��� �⸻����";
	char * line2 = "�� �� ��   �� �� ��";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("\n\n\n\n\n\n\n");
	centerJustIndent(strlen(line1), hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n\n\n\n\n\n\n\n", line1);

	centerJustIndent(strlen(line2), hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n\n\n", line2);

	getchar();
	return printMain();
}


/* 0. ���� �Լ� */

void readData(member * node, FILE * fp, member * leafNull)
{

	fscanf(fp, "%d\t%[^\t]\t%[^\t]\t%[^\n]", &(node->id), node->name, node->address, node->phone);

	node->father = NULL;
	node->color = red;
	node->left = leafNull;
	node->right = leafNull;
}


member * makeTree(rootPointer * RP, member * leafNull)
{
	FILE * fp;
	member * node;

	leafNull->color = black;
	char trash[basicStringSize];
	fp = fopen("data.txt", "rt");

	if (fp == NULL) {
		printf("file open error!\n");
	}

	fgets(trash, basicStringSize, fp);


	do{
		node = addNode();

		readData(node, fp, leafNull);
		if (node->id < 0)
		{
			fclose(fp);
			return leafNull;
		}
		attachTree(node, RP, leafNull);
		redBlackTree(node, RP, leafNull);

} while (getc(fp) != EOF);

}

member * makeTree_Name(rootPointer * RP, member * leafNull)
{
	FILE * fp;
	member * node;

	leafNull->color = black;
	char trash[basicStringSize];
	fp = fopen("data.txt", "rt");

	if (fp == NULL) {
		printf("file open error!\n");
	}

	fgets(trash, basicStringSize, fp);


	do{
		node = addNode();
		readData(node, fp, leafNull);
		if (node->id < 0)
		{
			fclose(fp);
			return leafNull;
		}
		attachTreeN(node, RP, leafNull);
		redBlackTreeN(node, RP, leafNull);
	} while (getc(fp) != EOF);

}





