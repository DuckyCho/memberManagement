#include "memberManagementSystem.h"

/* 1. 회원보기 */

//printList함수에서 맨위 서식을 프린트하고 readTree함수를 불러와서 node을 출력
int printList(member * node, member * leafNull)
{
	int userInput = 0;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("I    D   이 름\t      주소  \t\t   전화번호\n");
	centerJustIndent(63, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("───────────────────────────────\n");

	readTree(node, leafNull);//tree에서 node들의 값을 읽어서 프린트하는함수

	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	return userInput;

}

//중위 순회로 트리를 읽어옴 id기준으로 정렬되어 print됨
void readTree(member * node, member *leafNull)
{
	HANDLE hConsole;
	static int  count =  0;
	

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (node->left != leafNull)
	{
		readTree(node->left, leafNull);
		SetConsoleTextAttribute(hConsole, 15);
		centerJustIndent(60, hConsole);
		printf("%-9d%-9s%-25s\t%s\n", node->id, node->name, node->address, node->phone);
		count++;
	
	}

	else
	{
		SetConsoleTextAttribute(hConsole, 15);
		centerJustIndent(60, hConsole);
		printf("%-9d%-9s%-25s\t%s\n", node->id, node->name, node->address, node->phone);
		count++;
	}

	if (node->right != leafNull)
	{
		readTree(node->right, leafNull);
	}
}



/* 2. 회원 등록하기 */
int addData(rootPointer * RP, member * leafNull)//입력받은 회원의 정보를 RB에 넣음
{
	int userInput = 0;
	int nodeOfBiggestId;
	member * node;

	node = addNode();

	nodeOfBiggestId = searchBiggestId(RP->rootNode, leafNull);
	node->id = nodeOfBiggestId + 1;
	inputData(node, leafNull);

	attachTree(node, RP, leafNull);
	redBlackTree(node, RP, leafNull);
	
	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	return userInput;
}

void inputData(member * node, member * leafNull)//새로운 회원의 정보를 입력
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		
	fflush(stdin);
	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("추가하실 회원의 정보를 입력하세요\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("───────────────────────────────\n");

	centerJustIndent(60, hConsole);
	printf("이    름: ");
	scanf("%s", &(node->name));
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("주    소: ");
	scanf("%s", &(node->address));
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("전화번호: ");
	scanf("%s", &(node->phone));

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


/* 3. 회원 삭제하기 */
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
	char nameInput[basicStringSize];
	member * gonnaBeDeletedNode = addNode();
	
	gonnaBeDeletedNode = deleteUI(RP, leafNull);

	replaceNode(gonnaBeDeletedNode, RP, leafNull);
	printf("finish!\n");
	scanf("%d", &userInput);

}




/* 4. 회원정보 수정하기 */





/* 5. 회원 검색하기 */


int searchData(rootPointer RP, member * leafNull)//입력받은 회원의 이름을 이용하여 회원 정보 검색
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
	char * menu1 = "이름으로 검색하기";
	char * menu2 = "ID로 검색하기";
	char * menu3 = "메인화면으로 돌아가기";
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


int findByName(rootPointer RP, member * leafNull)
{
	HANDLE hConsole;
	member* searchPerson;
	int userInput = 0;
	char name[100];
	//char choice=0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	searchPerson->id = initialValue;

	system("cls");
	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("검색할 회원의 이름을 입력하세요\n");
	centerJustIndent(60, hConsole);
	printf("───────────────────────────────\n\n");
	fflush(stdin);
	centerJustIndent(60, hConsole);
	printf("이   름: ");
	scanf("%s", name);
	system("cls");

	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("검색할 회원의 이름을 입력하세요\n");
	centerJustIndent(60, hConsole);
	printf("───────────────────────────────\n\n");
	searchPerson = searchName(name, RP.rootNode, leafNull, RP.rootNode);//회원이 존재하는지 검색
	
	if (searchPerson == RP.rootNode){ //회원의 정보가 바뀌지 않았을 경우 = 찾는 회원이 존재하지 않을경우
		centerJustIndent(60, hConsole);
		printf("없는 이름입니다." );
		centerJustIndent(60, hConsole);
		userInput = functionKeyInput();
		return userInput;
	}
	centerJustIndent(60, hConsole);
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	
	userInput = functionKeyInput();
	if (userInput == 3)//정보 수정하기를 누른다.
	{
		userInput = askModify(searchPerson);
	}

	return userInput;
}

member* searchName(char* name, member * compare, member * leafNull, member* rootNode)
{
	int userInput = 0;

	if (compare->left == leafNull && compare->right == leafNull)
	{
		if (!strcmp(name, compare->name)){//두 이름이 같다면, compare 반환
			return compare;
		}
	}
	else
	{
		if (compare->left != leafNull)
		{

			if (!strcmp(name, searchName(name, compare->left, leafNull, rootNode)->name)){
				return compare;
			}
		}
		if (compare->right != leafNull)
		{
			searchName(name, compare->right, leafNull, rootNode);
		}
	}

}


int askModify(member* searchPerson)
{
	HANDLE hConsole;
	char choice = 0;
	int userInput = -1;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	printf("\n\n\n\n");
	centerJustIndent(60, hConsole);
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);

	centerJustIndent(60, hConsole);
	printf("1. 회원번호\n");
	centerJustIndent(60, hConsole);
	printf("2. 이    름\n");
	centerJustIndent(60, hConsole);
	printf("3. 주    소\n");
	centerJustIndent(60, hConsole);
	printf("4. 전화번호\n");
	modify(searchPerson);

	while (1){
		centerJustIndent(60, hConsole);
		printf("계속 수정하시겠습니까? (Y/N) ");
		scanf("%c", &choice);
		if (choice == 'y'){
			modify(searchPerson);
		}
		else
		{
			return userInput;
		}
	}
	userInput = functionKeyInput();
	return userInput;
}

void modify(member* searchPerson)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int userInput = 0;
	int choice=0;
	printf("\n\n");
	centerJustIndent(60, hConsole);
	printf("어떤 정보를 변경하시겠습니까?\n");

	
	fflush(stdin);
	centerJustIndent(60, hConsole);
	scanf("%d", &choice);
	fflush(stdin);
	if (choice == 1){
		centerJustIndent(60, hConsole);
		printf("회원번호: ");
		scanf("%d", &(searchPerson->id));
		fflush(stdin);
	}
	else if (choice == 2){
		centerJustIndent(60, hConsole);
		printf("이   름: ");
		scanf("%s", searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 3){
		centerJustIndent(60, hConsole);
		printf("주   소: ");
		scanf("%s", searchPerson->address);
		fflush(stdin);
	}
	else if(choice==4){
		centerJustIndent(60, hConsole);
		printf("전화번호: ");
		scanf("%s", searchPerson->phone);
		fflush(stdin);
	}
	else
	{
		centerJustIndent(60, hConsole);
		printf("1에서 4까지만 선택하라니까?!");
		Sleep(1500);
		system("cls");
		printf("\n\n\n\n\n");
		centerJustIndent(60, hConsole);
		printf("───────────────────────────────\n");
		printf("\n\n\n\n\n\n\n\n\n\n\n");

		//userInput = functionKeyInput();
		return;
	}

	//userInput = functionKeyInput();
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
	printf("검색할 회원의 회원번호를 입력하세요\n");
	centerJustIndent(60, hConsole);
	printf("───────────────────────────────\n\n");
	fflush(stdin);
	centerJustIndent(60, hConsole);
	printf("회원번호: ");
	scanf("%d", &id);
	system("cls");

	printf("\n\n\n\n\n");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("검색할 회원의 회원번호를 입력하세요\n");
	centerJustIndent(60, hConsole);
	printf("───────────────────────────────\n");
	getchar();

	searchId(id, RP.rootNode, leafNull, &searchPerson);
	
	if (searchPerson->id == initialValue)
	{
		fflush(stdin);
		system("cls");
		printf("\n\n\n\n\n");
		centerJustIndent(60, hConsole);
		SetConsoleTextAttribute(hConsole, 14);
		printf("검색할 회원의 회원번호를 입력하세요\n");
		centerJustIndent(60, hConsole);
		printf("───────────────────────────────\n");
		centerJustIndent(60, hConsole);
		printf("없는 번호입니다. 메인화면으로 돌아가시겠습니까? (y/n)\n");
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
			printf("y/n 중에서 하나만 누르라니깐?!");
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



/* 8.Credit 띄우기 */

int credit(void)
{
	HANDLE hConsole;
	char * line1 = "NHN NEXT 2014 프로그래밍연습 기말과제";
	char * line2 = "김 정 봉   조 영 대";

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


/* 0. 메인 함수 */

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






