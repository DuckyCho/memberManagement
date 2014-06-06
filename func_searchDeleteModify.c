#include "memberManagementSystem.h"

/* 5. ȸ�� �˻��ϱ� */


int selectSearch(rootPointer* RP, member * leafNull)
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
			break;
		}
	}

	if (userInput == 0)
	{
		userInput = find_byName(RP, leafNull);
		return userInput;
	}
	else if (userInput == 1)
	{
		userInput = find_byId(RP, leafNull);
		return userInput;
	}
	else{
		return -1;
	}
}

int searchUI(int upOrDown)
{
	HANDLE hConsole;
	static int now = 0;
	char * menu1 = "search by name";
	char * menu2 = "search by ID";
	char * menu3 = "return to main menu";
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	now += upOrDown;

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


/* �����ϱ� */
int selectModify(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char choice = 0;
	int userInput = 0;
	char * upperDeco = "�ۦ�����������������������������������������������������������";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	showMember(searchPerson);

	modifyUI(0, searchPerson);
	 
	if (GetAsyncKeyState(VK_UP)) Sleep(100);
	if (GetAsyncKeyState(VK_DOWN))Sleep(100);
	if (GetAsyncKeyState(VK_RETURN))Sleep(100);

	while (1)
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			userInput = modifyUI(1, searchPerson);
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			userInput = modifyUI(-1, searchPerson);
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

int modifyUI(int upOrDown, member* searchPerson)
{
	HANDLE hConsole;
	static int now = 0;
	char * menu1 = "name";
	char * menu2 = "address";
	char * menu3 = "phone";
	char * upperDeco = "�ۦ�����������������������������������������������������������";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	now += upOrDown;

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
	
	
	printf("\n\n\n");
	showMember(searchPerson);
	printf("\n\n\n\n");

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

void showMember(member* searchPerson)
{
	char * upperDeco = "�ۦ�����������������������������������������������������������";
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n", upperDeco);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("��%-9d%-9s%-25s\t%-13s��\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s", upperDeco);
}


/*�̸����� ã��*/

int find_byName(rootPointer* RP, member * leafNull)
{
	HANDLE hConsole;
	member* searchPerson = addNode();
	int userInput = -1;
	char * upperDeco = "�ۦ�����������������������������������������������������������";
	char name[32];
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (GetAsyncKeyState(VK_UP)) Sleep(100);
	if (GetAsyncKeyState(VK_DOWN))Sleep(100);
	if (GetAsyncKeyState(VK_RETURN))Sleep(100);


	system("cls");
	printf("\n\n\n\n\n\n");
	centerJustIndent(40, hConsole);
	printf("name: ");
	fflush(stdin);
	gets(name);
	fflush(stdin);
	printf("\n\n");

	searchPerson = searchName(name, RP->rootNodeN, leafNull);

	if (searchPerson == leafNull) //ȸ���˻����� �� ����� ���°��
	{
		centerJustIndent(40, hConsole);
		SetConsoleTextAttribute(hConsole, 14);
		printf("error: cannot find the name.\n");
		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : ȸ���˻� �ٽ��ϱ�
			return userInput;
		case (-1) : //F10 : ���θ޴�
			return userInput;
		}
	}

	showMember(searchPerson);

	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	switch (userInput){
	case (0) : //F1 : ȸ������
		system("cls");
		userInput = printList(RP->rootNodeN, leafNull);
		return userInput;
	case (1) : //F2 : ȸ�����
		system("cls");
		userInput = addData(RP, leafNull);
		return userInput;
	case (2) :  //F5 : ȸ���˻�
		system("cls");
		userInput = selectSearch(RP, leafNull);
		return userInput;
	case (6) : //F3 : ȸ������
		userInput = deleteUI(searchPerson, &RP, leafNull);
		return userInput;
	case (7) : //F4 : ȸ����������
		modify_byId(searchPerson, &RP, leafNull);
		return userInput;
	case (-1) : //F10 : ���θ޴�
		return userInput;
	}
}

int modify_byName(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	int userInput = -1;
	member* searchedPerson;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	userInput = selectModify(searchPerson, RP, leafNull);
	
	system("cls");
	printf("\n\n");
	showMember(searchPerson);
	printf("\n\n");

	if (userInput == 0){
		centerJustIndent(60, hConsole);
		printf("name: ");
		fflush(stdin);
		scanf("%s", searchPerson->name);
		fflush(stdin);
		nameCheck(searchPerson);
		searchedPerson = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchedPerson->name, searchPerson->name);
	}
	else if (userInput == 1){
		centerJustIndent(60, hConsole);
		printf("address: ");
		fflush(stdin);
		scanf("%s", searchPerson->address);
		fflush(stdin);
		searchedPerson = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchedPerson->address, searchPerson->address);
	}
	else{
		centerJustIndent(60, hConsole);
		printf("phone: ");
		fflush(stdin);
		scanf("%s", searchPerson->phone);
		fflush(stdin);
		phoneCheck_modify(searchPerson);
		searchedPerson = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchedPerson->phone, searchPerson->phone);
	}

	printf("\n");
	centerJustIndent(60, hConsole);
	printf("data has successfully changed!!\n\n");
	showMember(searchPerson);

	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	switch (userInput){
	case (0) : //F1 : ȸ������
		system("cls");
		userInput = printList(RP->rootNodeN, leafNull);
		return userInput;
	case (1) : //F2 : ȸ�����
		system("cls");
		userInput = addData(RP, leafNull);
		return userInput;
	case (2) :  //F5 : ȸ���˻�
		system("cls");
		userInput = selectSearch(RP, leafNull);
		return userInput;
	case (6) : //F3 : ȸ������
		userInput = deleteUI(searchPerson, &RP, leafNull);
		return userInput;
	case (7) : //F4 : ȸ����������
		modify_byId(searchPerson, &RP, leafNull);
		return userInput;
	case (-1) : //F10 : ���θ޴�
		return userInput;
	}

}


/*ȸ����ȣ�� ã��*/


int find_byId(rootPointer* RP, member * leafNull)
{
	HANDLE hConsole;
	member* searchPerson = addNode();
	int userInput = -1;
	char * upperDeco = "�ۦ�����������������������������������������������������������";
	int id =0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (GetAsyncKeyState(VK_UP)) Sleep(100);
	if (GetAsyncKeyState(VK_DOWN))Sleep(100);
	if (GetAsyncKeyState(VK_RETURN))Sleep(100);


	system("cls");
	printf("\n\n\n\n\n\n");

	centerJustIndent(40, hConsole);
	printf("id: ");
	fflush(stdin);
	scanf("%d", &id);
	fflush(stdin);
	printf("\n\n");

	searchPerson = searchId(id, RP->rootNode, leafNull);

	if (searchPerson == leafNull) //ȸ���˻����� �� ����� ���°��
	{
		centerJustIndent(40, hConsole);
		SetConsoleTextAttribute(hConsole, 14);
		printf("error: cannot find the name.\n");
		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : ȸ���˻� �ٽ��ϱ�
			return userInput;
		case (-1) : //F10 : ���θ޴�
			return userInput;
		}
	}

	showMember(searchPerson);

	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	switch (userInput){
	case (0) : //F1 : ȸ������
		system("cls");
		userInput = printList(RP->rootNodeN, leafNull);
		return userInput;
	case (1) : //F2 : ȸ�����
		system("cls");
		userInput = addData(RP, leafNull);
		return userInput;
	case (2) :  //F5 : ȸ���˻�
		system("cls");
		userInput = selectSearch(RP, leafNull);
		return userInput;
	case (6) : //F3 : ȸ������
		userInput = deleteUI(searchPerson, &RP, leafNull);
		return userInput;
	case (7) : //F4 : ȸ����������
		modify_byId(searchPerson, &RP, leafNull);
		return userInput;
	case (-1) : //F10 : ���θ޴�
		return userInput;
	}
}

int modify_byId(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	int userInput = -1;
	member* searchedPerson;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	userInput = selectModify(searchPerson, RP, leafNull);

	system("cls");
	printf("\n\n");
	showMember(searchPerson);
	printf("\n\n");

	if (userInput == 0){
		centerJustIndent(60, hConsole);
		printf("name: ");
		fflush(stdin);
		scanf("%s", searchPerson->name);
		fflush(stdin);
		nameCheck(searchPerson);
		searchedPerson = searchId(searchPerson->id, RP->rootNodeN, leafNull);
		strcpy(searchedPerson->name, searchPerson->name);
	}
	else if (userInput == 1){
		centerJustIndent(60, hConsole);
		fflush(stdin);
		printf("address: ");
		fflush(stdin);
		scanf("%s", searchPerson->address);
		searchedPerson = searchId(searchPerson->id, RP->rootNodeN, leafNull);
		strcpy(searchedPerson->address, searchPerson->address);
	}
	else{
		centerJustIndent(60, hConsole);
		printf("phone: ");
		fflush(stdin);
		scanf("%s", searchPerson->phone);
		fflush(stdin);
		phoneCheck_modify(searchPerson);
		searchedPerson = searchId(searchPerson->id, RP->rootNodeN, leafNull);
		strcpy(searchedPerson->phone, searchPerson->phone);
	}

	printf("\n");
	centerJustIndent(60, hConsole);
	printf("data has successfully changed!!\n\n");
	
	showMember(searchPerson);

	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	switch (userInput){
	case (0) : //F1 : ȸ������
		system("cls");
		userInput = printList(RP->rootNodeN, leafNull);
		return userInput;
	case (1) : //F2 : ȸ�����
		system("cls");
		userInput = addData(RP, leafNull);
		return userInput;
	case (2) :  //F5 : ȸ���˻�
		system("cls");
		userInput = selectSearch(RP, leafNull);
		return userInput;
	case (6) : //F3 : ȸ������
		userInput = deleteUI(searchPerson, &RP, leafNull);
		return userInput;
	case (7) : //F4 : ȸ����������
		modify_byId(searchPerson, &RP, leafNull);
		return userInput;
	case (-1) : //F10 : ���θ޴�
		return userInput;
	}

}

/* 3. ȸ�� �����ϱ� */

//id�� �˻��ϱ⿡�� �����ϱ⸦ ������ ��
int deleteUI(member* gonnaBeDeletedNode, rootPointer * RP, member * leafNull)
{
	int userInput = NULL;
	member * nameTreeNode;
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
			nameTreeNode = searchName(gonnaBeDeletedNode->name, RP->rootNodeN, leafNull);
			replaceNodeN(nameTreeNode, RP, leafNull);
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


//�̸����� �˻��ϱ⿡�� �����ϱ⸦ ������ ��
int deleteNUI(member* gonnaBeDeletedNode, rootPointer * RP, member * leafNull)
{
	int userInput = NULL;
	member * idTreeNode;
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
	printf("��%-9d%-9s%-25s\t%s��\n", gonnaBeDeletedNode->id, gonnaBeDeletedNode->name, gonnaBeDeletedNode->address, gonnaBeDeletedNode->phone);
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
			idTreeNode = searchId(gonnaBeDeletedNode->id, RP->rootNode, leafNull);
			replaceNode(idTreeNode, RP, leafNull);
			replaceNodeN(gonnaBeDeletedNode, RP, leafNull);

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


