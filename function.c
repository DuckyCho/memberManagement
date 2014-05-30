#include "memberManagementSystem.h"

/* 1. ȸ������*/

//printList�Լ����� �� ������ ����Ʈ�ϰ� readTree�Լ��� �ҷ��ͼ� node�� ���
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

	readTree(node, leafNull,NULL);//tree���� node���� ���� �о ����Ʈ�ϴ��Լ�

	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	return userInput;

}

//���� ��ȸ�� Ʈ���� �о�� id�������� ���ĵǾ� print��
void readTree(member * node, member *leafNull, void (* writeDataToTxt) (member*))
{
	HANDLE hConsole;
	
	

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (node->left != leafNull)
	{
		readTree(node->left, leafNull,writeDataToTxt);
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
		readTree(node->right, leafNull,writeDataToTxt);
	}
}



/* 2. ȸ�� ����ϱ� */
int addData(rootPointer * RP, member * leafNull)//�Է¹��� ȸ���� ������ RB�� ����
{
	int userInput = 0;
	member * node;
	int nodeOfBiggestId;

	fflush(stdin);

	leafNull->color = black;
	node = addNode();

	nodeOfBiggestId = searchBiggestId(RP->rootNode, leafNull);
	node->id = nodeOfBiggestId + 1;
	userInput = inputData(node, leafNull);
	if (userInput == -1)
	{
		return -1;
	}

	attachTree(node, RP, leafNull);
	redBlackTree(node, RP, leafNull);

	userInput = functionKeyInput();

	return userInput;
}

int inputData(member * node, member * leafNull)//���ο� ȸ���� ������ �Է�
{
	HANDLE hConsole;


	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		
	fflush(stdin);
	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("�߰��Ͻ� �����͸� �Է��ϼ���\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("��������������������������������������������������������������\n");


	centerJustIndent(60, hConsole);
	printf("��    ��: ");
	scanf("%s", &(node->name));
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("��    ��: ");
	scanf("%s", &(node->address));
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("��ȭ��ȣ: ");
	scanf("%s", &(node->phone));

	node->father = NULL;
	node->color = red;
	node->left = leafNull;
	node->right = leafNull;
	return 0;
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

/* 3. ȸ�� �����ϱ� */
member * deleteUI(rootPointer * RP, member * leafNull)
{
	int id;
	member * userInput = NULL;
	member * searchPerson = addNode();
	
	scanf("%d",&id);
	
	userInput = searchId(id, RP->rootNode, leafNull, &searchPerson);
	
	return userInput;
}

int deleteMember(rootPointer * RP, member * leafNull)
{
	int userInput;
	
	member * gonnaBeDeletedNode = addNode();
	
	gonnaBeDeletedNode = deleteUI(RP, leafNull);

	replaceNode(gonnaBeDeletedNode, RP, leafNull);
	printf("finish!\n");
	scanf("%d", &userInput);
	return userInput;
}




/* 4. ȸ������ �����ϱ� */





/* 5. ȸ�� �˻��ϱ� */


int searchData(rootPointer RP, member * leafNull)//�Է¹��� ȸ���� �̸��� �̿��Ͽ� ȸ�� ���� �˻�
{
	int now;
	int userInput = 0;

	now = selectSearch();

	if (now == 0)
	{
		userInput = findByName(RP, leafNull);
	}
	else if (now == 1)
	{
		userInput = findById(RP, leafNull);
	}
	else
	{
		printMain();
	}
	return userInput;
}

int selectSearch()
{
	HANDLE hConsole;
	int userInput = 0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	searchUI(0);

	/*
	if (GetAsyncKeyState(VK_UP)) Sleep(300);
	if (GetAsyncKeyState(VK_DOWN)) Sleep(300);
	if (GetAsyncKeyState(VK_RETURN)) Sleep(300);
	*/

	while (1)
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			userInput = searchUI(1);
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			userInput = searchUI(-1);
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


int searchUI(int upOrDown)
{
	static int now = 0;
	HANDLE hConsole;

	char * menu1 = "�̸����� �˻��ϱ�";
	char * menu2 = "ID�� �˻��ϱ�";
	char * menu3 = "����ȭ������ ���ư���";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	now += upOrDown;

	printf("\n\n\n");

	if (now <-20 || now == -1)
	{
		now = 0;
		system("cls");
	}
	else if (now == 3)
	{
		now = 1;
		system("cls");
	}
	system("cls");

	printf("\n\n\n\n\n");

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
		SetConsoleTextAttribute(hConsole, 14);
	}
	else{
		centerJustIndent(strlen(menu2), hConsole);
		SetConsoleTextAttribute(hConsole, 15);
		printf("%s\n\n", menu2);
	}
	if (now == 2){
		centerJustIndent(strlen(menu3), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu3);
		SetConsoleTextAttribute(hConsole, 14);
	}
	else{
		centerJustIndent(strlen(menu3), hConsole);
		SetConsoleTextAttribute(hConsole, 15);
		printf("%s\n\n", menu3);
	}
	printf("\n");

	return now;
}


int findByName(rootPointer RP, member * leafNull)
{
	HANDLE hConsole;
	member* searchPerson = addNode();
	int userInput = 0;
	char name[100];
	char choice=0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	searchPerson->id = initialValue;

	system("cls");
	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("�˻��� ȸ���� �̸��� �Է��ϼ���\n");
	centerJustIndent(60, hConsole);
	printf("��������������������������������������������������������������\n\n");
	fflush(stdin);
	centerJustIndent(60, hConsole);
	printf("��   ��: ");
	scanf("%s", name);
	system("cls");

	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("�˻��� ȸ���� �̸��� �Է��ϼ���\n");
	centerJustIndent(60, hConsole);
	printf("��������������������������������������������������������������\n\n");
	searchName(name, RP.rootNode, leafNull, RP.rootNode, &searchPerson);
	if (searchPerson->id == initialValue){
		fflush(stdin);
		system("cls");
		printf("\n\n\n\n\n");
		centerJustIndent(60, hConsole);
		SetConsoleTextAttribute(hConsole, 14);
		printf("�˻��� ȸ���� �̸��� �Է��ϼ���\n");
		centerJustIndent(60, hConsole);
		printf("��������������������������������������������������������������\n");
		centerJustIndent(60, hConsole);

		printf("���� �̸��Դϴ�. ����ȭ������ ���ư��ðڽ��ϱ�? (y/n)\n");
		centerJustIndent(60, hConsole);
		while (1)
		{
			scanf("%c", &choice);
			if (choice == 'y'){
				return printMain();
			}
			else if (choice == 'n'){
				return findByName(RP, leafNull);
			}
			else {
				centerJustIndent(60, hConsole);
				printf("y/n �߿��� �ϳ��� ������?!");
				continue;
			}
		}
	}
	centerJustIndent(60, hConsole);
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);

	//
	askModify(searchPerson);
	
	userInput = functionKeyInput();
	return userInput;
}

void askModify(member* searchPerson)
{
	HANDLE hConsole;
	char choice = 0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	getchar();
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("�� ȸ���� ������ �����Ͻðڽ��ϱ�? (y/n) ");
	scanf("%c", &choice);
	if (choice == 'y'){
		modify(searchPerson);
		return;
	}
	else if (choice == 'n'){
		printMain();
		return;
			
	}
	else{
		centerJustIndent(60, hConsole);
		printf("y/n �߿��� �ϳ��� ������ϱ�?!");
		Sleep(1500);
		printMain();
		return;
	}
}

void modify(member* searchPerson)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int userInput = 0;
	int choice=0;
	printf("\n\n");
	centerJustIndent(60, hConsole);
	printf("� ������ �����Ͻðڽ��ϱ�?\n");
	centerJustIndent(60, hConsole);
	printf("1. ȸ����ȣ\n");
	centerJustIndent(60, hConsole);
	printf("2. ��    ��\n");
	centerJustIndent(60, hConsole);
	printf("3. ��    ��\n");
	centerJustIndent(60, hConsole);
	printf("4. ��ȭ��ȣ\n");
	
	fflush(stdin);
	centerJustIndent(60, hConsole);
	scanf("%d", &choice);
	fflush(stdin);
	if (choice == 1){
		centerJustIndent(60, hConsole);
		printf("ȸ����ȣ: ");
		scanf("%d", &(searchPerson->id));
		fflush(stdin);
	}
	else if (choice == 2){
		centerJustIndent(60, hConsole);
		printf("��   ��: ");
		scanf("%s", searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 3){
		centerJustIndent(60, hConsole);
		printf("��   ��: ");
		scanf("%s", searchPerson->address);
		fflush(stdin);
	}
	else if(choice==4){
		centerJustIndent(60, hConsole);
		printf("��ȭ��ȣ: ");
		scanf("%s", searchPerson->phone);
		fflush(stdin);
	}
	else
	{
		centerJustIndent(60, hConsole);
		printf("1���� 4������ �����϶�ϱ�?!");
		Sleep(1500);
		system("cls");
		printf("\n\n\n\n\n");
		centerJustIndent(60, hConsole);
		printf("��������������������������������������������������������������\n");
		printf("\n\n\n\n\n\n\n\n\n\n\n");

		userInput = functionKeyInput();
		return;
	}

	userInput = functionKeyInput();
	return;
}

int findById(rootPointer RP, member * leafNull)
{
	int userInput = 0;
	int id;
	char choice = 0;
	member* searchPerson = addNode();
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	searchPerson->id = initialValue;

	system("cls");
	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("�˻��� ȸ���� ȸ����ȣ�� �Է��ϼ���\n");
	centerJustIndent(60, hConsole);
	printf("��������������������������������������������������������������\n\n");
	fflush(stdin);
	centerJustIndent(60, hConsole);
	printf("ȸ����ȣ: ");
	scanf("%d", &id);
	system("cls");

	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("�˻��� ȸ���� ȸ����ȣ�� �Է��ϼ���\n");
	centerJustIndent(60, hConsole);
	printf("��������������������������������������������������������������\n");
	getchar();

	searchId(id, RP.rootNode, leafNull, &searchPerson);
	
	if (searchPerson->id == initialValue)
	{
		fflush(stdin);
		system("cls");
		printf("\n\n\n\n\n");
		centerJustIndent(60, hConsole);
		SetConsoleTextAttribute(hConsole, 14);
		printf("�˻��� ȸ���� ȸ����ȣ�� �Է��ϼ���\n");
		centerJustIndent(60, hConsole);
		printf("��������������������������������������������������������������\n");
		centerJustIndent(60, hConsole);
		printf("���� ��ȣ�Դϴ�. ����ȭ������ ���ư��ðڽ��ϱ�? (y/n)\n");
		centerJustIndent(60, hConsole);
		scanf("%c", &choice);
		if (choice == 'y'){
			return printMain();
		}
		else if (choice == 'n'){
			return findById(RP, leafNull);
		}
		else{
			centerJustIndent(60, hConsole);
			printf("y/n �߿��� �ϳ��� ������ϱ�?!");
			Sleep(1500);
			return findById(RP, leafNull);
		}
	}
	
	centerJustIndent(60, hConsole);
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	askModify(searchPerson);

	userInput = functionKeyInput();
	return userInput;
}


member* searchName(char* name, member * compare, member * leafNull, member* rootNode, member** thisMan)
{
	int userInput = 0;
	
	/*
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	*/

	if (compare->left == leafNull && compare->right == leafNull)
	{
		if (!strcmp(name, compare->name)){
			*thisMan = compare;
		}
	}
	else
	{
		if (compare->left != leafNull)
		{
			searchName(name, compare->left, leafNull, rootNode, thisMan);
			if (!strcmp(name, compare->name)){
				*thisMan = compare;
			}
		}
		if (compare->right != leafNull)
		{
			searchName(name, compare->right, leafNull, rootNode, thisMan);
		}
	}
}

member * searchId(int id, member * compare, member * leafNull, member** thisMan)
{
	if (compare == leafNull)
	{
		return leafNull;
	}
	
	if (id < compare->id)
	{
		return searchId(id, compare->left, leafNull, thisMan);
	}
	else if (id > compare->id)
	{
		return searchId(id, compare->right, leafNull, thisMan);
	}
	else 
	{
		*thisMan = compare;
		return compare;
	}

}
/* 6. �����ϱ� */

int saveData(rootPointer * RP, member * leafNull)
{
	FILE * fp;
	HANDLE hConsole;
	int userInput;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fp = fopen("data.txt", "wt");
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%s\t%s\t%s\t%s\n", "ID", "�̸�", "�ּ�", "��ȭ��ȣ");
	fclose(fp);
	
	readTree(RP->rootNode, leafNull, writeDataToTxt);
	
	scanf("%d",&userInput);
	return userInput;
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


member * firstFunc(rootPointer * RP, member * leafNull)
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
		//fseek(fp, -1, SEEK_CUR);
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






