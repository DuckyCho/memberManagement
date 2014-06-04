#include "memberManagementSystem.h"

/* 5. 회원 검색하기 */


int searchData(rootPointer RP, member * leafNull)//입력받은 회원의 이름을 이용하여 회원 정보 검색
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
	char * menu1 = "search by name";
	char * menu2 = "search by ID";
	char * menu3 = "return to main menu";
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


/*이름으로 찾기*/

int find_byName(rootPointer RP, member * leafNull)
{
	HANDLE hConsole;
	member* searchPerson = addNode();
	int userInput = 0;
	char * upperDeco = "○─────────────────────────────○";
	char name[32];

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	printf("\n\n\n\n\n\n");

	centerJustIndent(40, hConsole);
	printf("name: ");
	fflush(stdin);
	gets(name);
	printf("\n\n");

	searchPerson = searchName(name, RP.rootNodeN, leafNull);

	if (searchPerson == leafNull) //회원검색했을 때 결과가 없는경우
	{
		printf("error: cannot find the name.\n");
		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : 회원검색 다시하기
			return userInput;
		case (-1) : //F10 : 메인메뉴
			return userInput;
		}
	}

	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n", upperDeco);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("│%-9d%-9s%-25s\t%s│\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s", upperDeco);

	userInput = functionKeyInput();
	switch (userInput){
	case (0) : //F1 : 회원보기
		return userInput;
	case (1) : //F2 : 회원등록
		return userInput;
	case (2) :  //F5 : 회원검색
		return userInput;
	case (6) : //F3 : 회원삭제
		userInput = deleteUI(searchPerson, &RP, leafNull);
		return userInput;
	case (7) : //F4 : 회원정보수정
		userInput = askModify_byName(searchPerson, &RP, leafNull);
		return userInput;
	case (-1) : //F10 : 메인메뉴
			return userInput;
	}

}

int askModify_byName(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	char choice = 0;
	int userInput = -1;
	char * upperDeco = "○─────────────────────────────○";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n", upperDeco);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("│%-9d%-9s%-25s\t%s│\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s", upperDeco);

	modify_byName(searchPerson, RP, leafNull);

	while (1){
		centerJustIndent(60, hConsole);
		printf("계속 수정하시겠습니까? (y/n) ");
		scanf("%c", &choice);
		if (choice == 'y'){
			modify_byName(searchPerson, RP, leafNull);
		}

		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : 회원검색 다시하기
			return userInput;
		case (-1) : //F10 : 메인메뉴
			return userInput;
		}
	}

}


void modify_byName(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int choice = 0;
	char * upperDeco = "○─────────────────────────────○";
	member* searchPerson_Id;
	printf("\n\n어떤 정보를 변경하시겠습니까?\n1. 이    름\t2. 주    소\t3. 전화번호\n");
	scanf("%d", &choice);
	fflush(stdin);

	if (choice == 1){
		centerJustIndent(60, hConsole);
		printf("이   름: ");
		scanf("%s", searchPerson->name);
		searchPerson_Id = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchPerson_Id->name, searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 2){
		centerJustIndent(60, hConsole);
		printf("주   소: ");
		scanf("%s", searchPerson->address);
		searchPerson_Id = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchPerson_Id->address, searchPerson->address);
		fflush(stdin);
	}
	else if (choice == 3){
		printf("전화번호: ");
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





/*회원번호로 찾기*/
int askModify_byId(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	char choice = 0;
	char * upperDeco = "○─────────────────────────────○";

	int userInput = -1;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n", upperDeco);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("│%-9d%-9s%-25s\t%s│\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s", upperDeco);

	modify_byId(searchPerson, RP, leafNull);

	while (1){
		centerJustIndent(60, hConsole);
		printf("계속 수정하시겠습니까? (y/n) ");
		scanf("%c", &choice);
		if (choice == 'y'){
			modify_byId(searchPerson, RP, leafNull);
		}

		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : 회원검색 다시하기
			return userInput;
		case (-1) : //F10 : 메인메뉴
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
	printf("\n\n어떤 정보를 변경하시겠습니까?\n1. 이    름\t2. 주    소\t3. 전화번호\n");
	scanf("%d", &choice);
	fflush(stdin);

	if (choice == 1){
		centerJustIndent(60, hConsole);
		printf("이   름: ");
		scanf("%s", searchPerson->name);
		searchPerson_Name = searchId(searchPerson->id, RP->rootNodeN, leafNull);
		strcpy(searchPerson_Name->name, searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 2){
		centerJustIndent(60, hConsole);
		printf("주   소: ");
		scanf("%s", searchPerson->address);
		searchPerson_Name = searchId(searchPerson->id, RP->rootNodeN, leafNull);
		strcpy(searchPerson_Name->name, searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 3){
		printf("전화번호: ");
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
	char * upperDeco = "○─────────────────────────────○";
	member* searchPerson = addNode();
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	printf("\n\n\n\n\n");
	printf("검색할 회원의 회원번호를 입력하세요\n");
	printf("───────────────────────────────\n\n");
	printf("회원번호: ");
	fflush(stdin);
	scanf("%d", &id);

	searchPerson = searchId(id, RP.rootNode, leafNull);

	if (searchPerson == leafNull)
	{
		printf("없는 회원번호입니다.\n");
		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : 회원검색 다시하기
			return userInput;
		case (-1) : //F10 : 메인메뉴
			return userInput;
		}
		return userInput;
	}

	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n", upperDeco);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("│%-9d%-9s%-25s\t%s│\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s", upperDeco);

	userInput = functionKeyInput();
	switch (userInput){
	case (0) : //F1 : 회원보기
		return userInput;
	case (1) : //F2 : 회원등록
		return userInput;
	case (2) :  //F5 : 회원검색
		return userInput;
	case (6) : //F3 : 회원삭제
		userInput = deleteUI(searchPerson, &RP, leafNull);
		return userInput;
	case (7) : //F4 : 회원정보수정
		userInput = askModify_byId(searchPerson, &RP, leafNull);
		return userInput;
	case (-1) : //F10 : 메인메뉴
		return userInput;
	}
}





/* 3. 회원 삭제하기 */
int deleteUI(member* gonnaBeDeletedNode, rootPointer * RP, member * leafNull)
{
	int userInput = NULL;
	HANDLE hConsole;
	char * upperDeco = "○─────────────────────────────○";
	
	
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
	printf("│%-9d%-9s%-25s\t%s│\n",gonnaBeDeletedNode->id,gonnaBeDeletedNode->name,gonnaBeDeletedNode->address,gonnaBeDeletedNode->phone);
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


