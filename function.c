#include "memberManagementSystem.h"
#include "redBlackFunctions.h"

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
	node = addNode();
	node->otherTreePointer = addNode();

	node->otherTreePointer->otherTreePointer = node;
	node->treeType = idTree;
	node->otherTreePointer->treeType = nameTree;
	

	nodeOfBiggestId = searchBiggestId(RP->rootNode, leafNull);
	node->id = nodeOfBiggestId + 1;
	inputData(node, leafNull);

	attachTree(node, RP, leafNull);
	redBlackTree(node, RP, leafNull);

	attachTreeN(node->otherTreePointer, RP, leafNull);
	redBlackTreeN(node->otherTreePointer, RP, leafNull);
	
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
	printf("\n");

	centerJustIndent(35, hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("please insert membership information.\n\n\n\n");

	centerJustIndent(50, hConsole);
	printf("name: ");
	fflush(stdin);
	fgets(node->name, mem_tStringSize, stdin);
	removeNewLine(node->name);
	fflush(stdin);
	nameCheck(node);
	printf("\n");

	centerJustIndent(50, hConsole);
	printf("address: ");
	fflush(stdin);
	fgets(node->address, mem_tStringSize, stdin);
	removeNewLine(node->address);
	fflush(stdin);
	printf("\n");

	centerJustIndent(50, hConsole);
	printf("phone: ");
	fflush(stdin);
	fgets(node->phone, mem_tStringSize, stdin);
	removeNewLine(node->phone);
	fflush(stdin);
	phoneCheck(node);
	printf("\n\n\n");


	centerJustIndent(39, hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("Registration complete. Congratulations!!\n");

	node->father = NULL;
	node->color = red;
	node->left = leafNull;
	node->right = leafNull;
	

	node->otherTreePointer->id = node->id;
	strcpy(node->otherTreePointer->address, node->address);
	strcpy(node->otherTreePointer->name, node->name);
	strcpy(node->otherTreePointer->phone, node->phone);
	node->otherTreePointer->left = leafNull;
	node->otherTreePointer->right = leafNull;


}

/*��ȭ��ȣ ����ó��*/
void phoneCheck(member* node)
{
	int count = 0;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (node->phone[count]){

		if (('0' > node->phone[count] || node->phone[count] > '9') && (node->phone[count] != '-') || (count > 15))
		{

			system("cls");
			printf("\n");	
			centerJustIndent(35, hConsole);
			SetConsoleTextAttribute(hConsole, 252);
			printf("please insert membership information.\n\n");
			
			centerJustIndent(41, hConsole);
			SetConsoleTextAttribute(hConsole, 14);
			printf("the phone number is not properly formatted.\n\n");
			 
			centerJustIndent(50, hConsole);
			printf("name: ");
			printf("%s", node->name);
			printf("\n\n");

			centerJustIndent(50, hConsole);
			printf("address: ");
			printf("%s", node->address);
			printf("\n\n");

			centerJustIndent(50, hConsole);
			printf("phone: ");
			scanf("%s", &(node->phone));
			phoneCheck(node);
			count = 0;
		}
		count++;
	}

	return;
}


void phoneCheck_modify(member* node)
{
	int count = 0;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (node->phone[count]){

		if (('0' > node->phone[count] || node->phone[count] > '9') && (node->phone[count] != '-') || (count > 15))
		{

			system("cls");
			printf("\n");
			centerJustIndent(35, hConsole);
			SetConsoleTextAttribute(hConsole, 252);
			printf("please insert membership information.\n\n");

			centerJustIndent(41, hConsole);
			SetConsoleTextAttribute(hConsole, 14);
			printf("the phone number is not properly formatted.\n\n");

			centerJustIndent(50, hConsole);
			printf("phone: ");
			scanf("%s", &(node->phone));
			phoneCheck_modify(node);
			count = 0;
		}
		count++;
	}

	return;
}


/*�̸� ����ó��*/
void nameCheck(member* node)
{
	int count = 0;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (node->name[count]){
		count++;
	}

	if (count > 10)
	{
		
		count = 0;

		system("cls");
		printf("\n");
		centerJustIndent(35, hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("please insert membership information.\n\n");


		centerJustIndent(33, hConsole);
		SetConsoleTextAttribute(hConsole, 14);
		printf("the name is not properly formatted.\n\n");

		centerJustIndent(50, hConsole);
		printf("name: ");
		scanf("%s", &(node->name));
		nameCheck(node);

	}
	return;
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

	printf("\n\n\n\n\n\n\n\n\n\n");
	centerJustIndent(30, hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("Saving has successfully done!\n");
	centerJustIndent(21, hConsole);
	printf("Total member : %d��\n\n", count);
	centerJustIndent(35, hConsole);
	printf("Press anykey to go to MainMenu....\n"/*, count*/);
	if (getch())
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
	char * line3 = "������ ������ �����մϴ�!";
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("\n\n\n\n\n\n\n");
	centerJustIndent(strlen(line1), hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n\n\n\n\n\n\n\n", line1);

	centerJustIndent(strlen(line2), hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n\n", line2);
	centerJustIndent(strlen(line3)+2, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf(" %s \n\n\n\n\n", line3);

	while (getch())
	{
		fflush(stdin);
		return printMain();
	}

}


/* 0. ���� �Լ� */

void readData(member * node, FILE * fp, member * leafNull)
{

	fscanf(fp, "%d\t%[^\t]\t%[^\t]\t%[^\n]", &(node->id), node->name, node->address, node->phone);

	node->left = leafNull;
	node->right = leafNull;

	node->otherTreePointer->left = leafNull;
	node->otherTreePointer->right = leafNull;

	nodeCpy(node, node->otherTreePointer);
	
}


member * makeTree(rootPointer * RP, member * leafNull)
{
	FILE * fp;
	member * node;

	char trash[basicStringSize];
	fp = fopen("data.txt", "rt");

	if (fp == NULL) {
		printf("file open error!\n");
	}

	fgets(trash, basicStringSize, fp);


	do{
		node = addNode();
		node->otherTreePointer = addNode();

		node->otherTreePointer->otherTreePointer = node;
		node->treeType = idTree;
		node->otherTreePointer->treeType = nameTree;

		readData(node, fp, leafNull);
		if (node->id < 0)
		{
			fclose(fp);
			return leafNull;
		}
		attachTree(node, RP, leafNull);
		attachTreeN(node->otherTreePointer, RP, leafNull);
		redBlackTree(node, RP, leafNull);
		redBlackTreeN(node->otherTreePointer, RP, leafNull);

} while (getc(fp) != EOF);

}
