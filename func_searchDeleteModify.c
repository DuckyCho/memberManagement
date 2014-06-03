#include "memberManagementSystem.h"

/* 5. ȸ�� �˻��ϱ� */


int searchData(rootPointer RP, member * leafNull)//�Է¹��� ȸ���� �̸��� �̿��Ͽ� ȸ�� ���� �˻�
{
	int now;
	int userInput = 0;

	now = selectSearch();

	if (now == 0)
	{
		userInput = find_byName(RP, leafNull);
		return userInput;
	}
	else if (now == 1)
	{
		userInput = find_byId(RP, leafNull);
		return userInput;
	}
	else
	{
		return -1;
	}
}

int selectSearch()
{
	HANDLE hConsole;
	int userInput = 0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	searchUI(0);

	if (GetAsyncKeyState(VK_UP)) Sleep(100);
	if (GetAsyncKeyState(VK_DOWN))Sleep(100);
	if (GetAsyncKeyState(VK_RETURN))Sleep(100);

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
			searchUI(-80);
			getchar();
			return userInput;
		}
	}
}


int searchUI(int upOrDown)
{
	HANDLE hConsole;
	static int now = 0;
	char * menu1 = "�̸����� �˻��ϱ�";
	char * menu2 = "ID�� �˻��ϱ�";
	char * menu3 = "����ȭ������ ���ư���";
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	now += upOrDown;

	printf("\n\n\n");
	if (now <= -1)
	{
		now = 0;
		system("cls");
	}
	else if (now >= 3)
	{
		now = 2;
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


member * searchName(char* name, member * compare, member * leafNull)
{
	if (compare == leafNull)
	{
		return leafNull;
	}

	if (strcmp(name, compare->name)<0)
	{
		return searchName(name, compare->left, leafNull);
	}
	else if (strcmp(name, compare->name)>0)
	{
		return searchName(name, compare->right, leafNull);
	}
	else
	{
		return compare;
	}
}


member * searchId(int id, member * compare, member * leafNull)
{
	if (compare == leafNull)
	{
		return leafNull;
	}

	if (id < compare->id)
	{
		return searchId(id, compare->left, leafNull);
	}
	else if (id > compare->id)
	{
		return searchId(id, compare->right, leafNull);
	}
	else
	{
		return compare;
	}

}


/*�̸����� ã��*/

int find_byName(rootPointer RP, member * leafNull)
{
	member* searchPerson = addNode();
	int userInput = 0;
	char name[32];

	system("cls");
	printf("\n\n\n\n\n");
	printf("�˻��� ȸ���� �̸��� �Է��ϼ���\n");
	printf("��������������������������������������������������������������\n\n");
	printf("��   ��: ");
	fflush(stdin);
	gets(name);

	searchPerson = searchName(name, RP.rootNodeN, leafNull);

	if (searchPerson == leafNull) //ȸ���˻����� �� ����� ���°��
	{
		printf("���� ȸ���Դϴ�.\n");
		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : ȸ���˻� �ٽ��ϱ�
			return userInput;
		case (-1) : //F10 : ���θ޴�
			return userInput;
		}
	}


	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);

	userInput = functionKeyInput();
	switch (userInput){
	case (0) : //F1 : ȸ������
		return userInput;
	case (1) : //F2 : ȸ�����
		return userInput;
	case (2) :  //F5 : ȸ���˻�
		return userInput;
	case (6) : //F3 : ȸ������
		userInput = deleteUI(searchPerson, &RP, leafNull);
		return userInput;
	case (7) : //F4 : ȸ����������
		userInput = askModify_byName(searchPerson, &RP, leafNull);
		return userInput;
	case (-1) : //F10 : ���θ޴�
			return userInput;
	}

}

int askModify_byName(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	char choice = 0;
	int userInput = -1;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	printf("\n\n\n\n");
	centerJustIndent(60, hConsole);
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);

	modify_byName(searchPerson, RP, leafNull);

	while (1){
		centerJustIndent(60, hConsole);
		printf("��� �����Ͻðڽ��ϱ�? (y/n) ");
		scanf("%c", &choice);
		if (choice == 'y'){
			modify_byName(searchPerson, RP, leafNull);
		}

		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : ȸ���˻� �ٽ��ϱ�
			return userInput;
		case (-1) : //F10 : ���θ޴�
			return userInput;
		}
	}

}


void modify_byName(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int choice = 0;
	member* searchPerson_Id;
	printf("\n\n� ������ �����Ͻðڽ��ϱ�?\n1. ��    ��\t2. ��    ��\t3. ��ȭ��ȣ\n");
	scanf("%d", &choice);
	fflush(stdin);

	if (choice == 1){
		centerJustIndent(60, hConsole);
		printf("��   ��: ");
		scanf("%s", searchPerson->name);
		searchPerson_Id = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchPerson_Id->name, searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 2){
		centerJustIndent(60, hConsole);
		printf("��   ��: ");
		scanf("%s", searchPerson->address);
		searchPerson_Id = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchPerson_Id->address, searchPerson->address);
		fflush(stdin);
	}
	else if (choice == 3){
		printf("��ȭ��ȣ: ");
		scanf("%s", searchPerson->phone);

		phoneCheck(searchPerson);

		searchPerson_Id = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchPerson_Id->phone, searchPerson->phone);
		fflush(stdin);
	}
	else
	{
		return;
	}
	return;
}





/*ȸ����ȣ�� ã��*/
int askModify_byId(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	char choice = 0;
	int userInput = -1;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	printf("\n\n\n\n");
	centerJustIndent(60, hConsole);
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);

	modify_byId(searchPerson, RP, leafNull);

	while (1){
		centerJustIndent(60, hConsole);
		printf("��� �����Ͻðڽ��ϱ�? (y/n) ");
		scanf("%c", &choice);
		if (choice == 'y'){
			modify_byId(searchPerson, RP, leafNull);
		}

		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : ȸ���˻� �ٽ��ϱ�
			return userInput;
		case (-1) : //F10 : ���θ޴�
			return userInput;
		}
	}
}

void modify_byId(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int choice = 0;
	member* searchPerson_Name;
	printf("\n\n� ������ �����Ͻðڽ��ϱ�?\n1. ��    ��\t2. ��    ��\t3. ��ȭ��ȣ\n");
	scanf("%d", &choice);
	fflush(stdin);

	if (choice == 1){
		centerJustIndent(60, hConsole);
		printf("��   ��: ");
		scanf("%s", searchPerson->name);
		searchPerson_Name = searchId(searchPerson->id, RP->rootNodeN, leafNull);
		strcpy(searchPerson_Name->name, searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 2){
		centerJustIndent(60, hConsole);
		printf("��   ��: ");
		scanf("%s", searchPerson->address);
		searchPerson_Name = searchId(searchPerson->id, RP->rootNodeN, leafNull);
		strcpy(searchPerson_Name->name, searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 3){
		printf("��ȭ��ȣ: ");
		scanf("%s", searchPerson->phone);
		
		phoneCheck(searchPerson);

		searchPerson_Name = searchId(searchPerson->id, RP->rootNodeN, leafNull);
		strcpy(searchPerson_Name->name, searchPerson->name);
		fflush(stdin);
	}
	else
	{
		return;
	}
	return;
}

int find_byId(rootPointer RP, member * leafNull)
{
	int id;
	int userInput = 0;
	member* searchPerson = addNode();
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	printf("\n\n\n\n\n");
	printf("�˻��� ȸ���� ȸ����ȣ�� �Է��ϼ���\n");
	printf("��������������������������������������������������������������\n\n");
	printf("ȸ����ȣ: ");
	fflush(stdin);
	scanf("%d", &id);

	searchPerson = searchId(id, RP.rootNode, leafNull);

	if (searchPerson == leafNull)
	{
		printf("���� ȸ����ȣ�Դϴ�.\n");
		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : ȸ���˻� �ٽ��ϱ�
			return userInput;
		case (-1) : //F10 : ���θ޴�
			return userInput;
		}
		return userInput;
	}
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	userInput = functionKeyInput();
	switch (userInput){
	case (0) : //F1 : ȸ������
		return userInput;
	case (1) : //F2 : ȸ�����
		return userInput;
	case (2) :  //F5 : ȸ���˻�
		return userInput;
	case (6) : //F3 : ȸ������
		userInput = deleteUI(searchPerson, &RP, leafNull);
		return userInput;
	case (7) : //F4 : ȸ����������
		userInput = askModify_byId(searchPerson, &RP, leafNull);
		return userInput;
	case (-1) : //F10 : ���θ޴�
		return userInput;
	}
}





/* 3. ȸ�� �����ϱ� */
int deleteUI(member* gonnaBeDeletedNode, rootPointer * RP, member * leafNull)
{
	int userInput = NULL;
	HANDLE hConsole;
	char * upperDeco = "�ۦ�����������������������������������������������������������";
	
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	system("cls");
	printf("\n");

	centerJustIndent(15, hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("Sure to delete??\n\n\n\n\n\n\n\n\n");

	
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n", upperDeco);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("��%-9d%-9s%-25s\t%s��\n",gonnaBeDeletedNode->id,gonnaBeDeletedNode->name,gonnaBeDeletedNode->address,gonnaBeDeletedNode->phone);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n\n\n\n\n\n\n\n", upperDeco);

	centerJustIndent(32, hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("  cancel ESC    delete ENTER  \n");
	SetConsoleTextAttribute(hConsole, 13);
	
	while (1)
	{
		fflush(stdin);
		userInput = getch();
		if (userInput == 27) {
			userInput = -1;
			return userInput;
		}
		else if (userInput == 13) {
			replaceNode(gonnaBeDeletedNode, RP, leafNull);
			centerJustIndent(18, hConsole);
			printf(".");
			Sleep(100);
			printf(".");
			Sleep(100);
			printf(".");
			Sleep(100);
			printf(".");
			Sleep(100);
			printf("Delete done!!");
			centerJustIndent(15, hConsole);
			break;
		}
		else{
			printf("\a");
			continue;
		}
	}

		userInput = functionKeyInput_WhenSearchResultVoid();
		return userInput;
}


/*��ȭ��ȣ ����ó��*/
void phoneCheck(member* node)
{
	int i = 0;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	while (node->phone[i]){

		if(('0' > node->phone[i] || node->phone[i] > '9')&&(node->phone[i] != '-'))
		{
			
				system("cls");
				printf("\n\n\n\n\n");
				centerJustIndent(60, hConsole);
				SetConsoleTextAttribute(hConsole, 14);
				printf("�߰��Ͻ� ȸ���� ������ �Է��ϼ���\n");
				centerJustIndent(60, hConsole);
				SetConsoleTextAttribute(hConsole, 14);
				printf("��������������������������������������������������������������\n");
				printf("���ڸ� �Է��ϼ���.\n");

				centerJustIndent(60, hConsole);
				printf("��    ��: ");
				printf("%s", node->name);

				printf("\n\n");
				centerJustIndent(60, hConsole);
				printf("��    ��: ");
				printf("%s", node->address);
				printf("\n\n");

				centerJustIndent(60, hConsole);
				printf("��ȭ��ȣ: ");
				scanf("%s", &(node->phone));
				phoneCheck(node);

		}
		i++;
	}
	return;

}
