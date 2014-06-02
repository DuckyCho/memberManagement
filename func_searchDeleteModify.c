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
	}
	else if (now == 1)
	{
		userInput = find_byId(RP, leafNull);
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
	member* searchPerson = addNode();
	int userInput = 0;
	char name[32];

	system("cls");
	printf("\n\n\n\n\n");
	printf("검색할 회원의 이름을 입력하세요\n");
	printf("───────────────────────────────\n\n");
	printf("이   름: ");
	scanf("%s", name);

	searchPerson = searchName(name, RP.rootNodeN, leafNull);

	if (searchPerson == leafNull)
	{
		printf("없는 회원입니다.\n");
		userInput = functionKeyInput();
		return userInput;
	}
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);

	userInput = functionKeyInput();
	if (userInput = 3)
	{
		userInput = askModify_byName(searchPerson, &RP, leafNull);
	}

	return userInput;
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

	centerJustIndent(60, hConsole);
	printf("1. 이    름\n");
	centerJustIndent(60, hConsole);
	printf("2. 주    소\n");
	centerJustIndent(60, hConsole);
	printf("3. 전화번호\n");
	centerJustIndent(60, hConsole);

	modify_byName(searchPerson, RP, leafNull);

	while (1){
		centerJustIndent(60, hConsole);
		printf("계속 수정하시겠습니까? (y/n) ");
		scanf("%c", &choice);
		if (choice == 'y'){
			modify_byName(searchPerson, RP, leafNull);
		}
		else
		{
			userInput = functionKeyInput();
			return userInput;
		}
	}
	userInput = functionKeyInput();
	return userInput;
}


void modify_byName(member* searchPerson, rootPointer* RP, member* leafNull)

{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int choice = 0;
	member* searchPerson_Id;
	printf("\n\n어떤 정보를 변경하시겠습니까? (1~3)\n취소하려면 아무키나 누르세요.\n");
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
	int userInput = -1;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	printf("\n\n\n\n");
	centerJustIndent(60, hConsole);
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);

	centerJustIndent(60, hConsole);
	printf("1. 이    름\n");
	centerJustIndent(60, hConsole);
	printf("2. 주    소\n");
	centerJustIndent(60, hConsole);
	printf("3. 전화번호\n");
	centerJustIndent(60, hConsole);

	modify_byId(searchPerson, RP, leafNull);

	while (1){
		centerJustIndent(60, hConsole);
		printf("계속 수정하시겠습니까? (y/n) ");
		scanf("%c", &choice);
		if (choice == 'y'){
			modify_byId(searchPerson, RP, leafNull);
		}
		else
		{
			userInput = functionKeyInput();
			return userInput;
		}
	}
	userInput = functionKeyInput();
	return userInput;
}

void modify_byId(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int choice = 0;
	member* searchPerson_Name;
	printf("\n\n어떤 정보를 변경하시겠습니까? (1~3)\n취소하려면 아무키나 누르세요.\n");
	scanf("%d", &choice);
	fflush(stdin);

	if (choice == 1){
		centerJustIndent(60, hConsole);
		printf("이   름: ");
		scanf("%s", searchPerson->name);
		searchPerson_Name = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchPerson_Name->name, searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 2){
		centerJustIndent(60, hConsole);
		printf("주   소: ");
		scanf("%s", searchPerson->address);
		searchPerson_Name = searchId(searchPerson->id, RP->rootNode, leafNull);
		strcpy(searchPerson_Name->name, searchPerson->name);
		fflush(stdin);
	}
	else if (choice == 3){
		printf("전화번호: ");
		scanf("%s", searchPerson->phone);
		
		phoneCheck(searchPerson);

		searchPerson_Name = searchId(searchPerson->id, RP->rootNode, leafNull);
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
	printf("검색할 회원의 회원번호를 입력하세요\n");
	printf("───────────────────────────────\n\n");
	printf("회원번호: ");
	scanf("%d", &id);

	searchPerson = searchId(id, RP.rootNode, leafNull);

	if (searchPerson == leafNull)
	{
		printf("없는 회원번호입니다.\n");
		userInput = functionKeyInput();
		return userInput;
	}
	printf("%-9d%-9s%-25s\t%s\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);

	userInput = functionKeyInput();
	if (userInput == 3)
	{
		userInput = askModify_byId(searchPerson, &RP, leafNull);
	}else if (userInput == 2){
	userInput = deleteUI(searchPerson, &RP, leafNull);
	}
	return userInput;
}





/* 3. 회원 삭제하기 */
member * deleteUI(member* searchPerson, rootPointer * RP, member * leafNull)
{
	member * userInput = NULL;
	member * gonnaBeDeletedNode = addNode();

	gonnaBeDeletedNode = searchId(searchPerson->id, RP->rootNode, leafNull);

	replaceNode(gonnaBeDeletedNode, RP, leafNull);
	replaceNode(searchPerson, RP, leafNull);

	printf("finish!\n");

	userInput = functionKeyInput();
	return userInput;
}

/*전화번호 예외처리*/
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
				printf("추가하실 회원의 정보를 입력하세요\n");
				centerJustIndent(60, hConsole);
				SetConsoleTextAttribute(hConsole, 14);
				printf("───────────────────────────────\n");
				printf("숫자만 입력하세요.\n");

				centerJustIndent(60, hConsole);
				printf("이    름: ");
				printf("%s", node->name);

				printf("\n\n");
				centerJustIndent(60, hConsole);
				printf("주    소: ");
				printf("%s", node->address);
				printf("\n\n");

				centerJustIndent(60, hConsole);
				printf("전화번호: ");
				scanf("%s", &(node->phone));
				phoneCheck(node);

		}
		i++;
	}
	return;

}
