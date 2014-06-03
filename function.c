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

	readTree(node, leafNull, NULL);//tree에서 node들의 값을 읽어서 프린트하는함수

	fflush(stdin);
	userInput = functionKeyInput_WhenSearchResultVoid();
	fflush(stdin);
	
	return userInput;

}

//중위 순회로 트리를 읽어옴 id기준으로 정렬되어 print됨
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



/* 2. 회원 등록하기 */
int addData(rootPointer * RP, member * leafNull)//입력받은 회원의 정보를 RB에 넣음
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
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("이    름: ");
	scanf("%s", &(node->name));

	fflush(stdin);
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("주    소: ");
	gets(node->address);
	fflush(stdin);
	printf("\n");
	centerJustIndent(60, hConsole);
	printf("전화번호: ");
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

/* 6. 저장하기 */

int saveData(rootPointer * RP, member * leafNull)
{
	FILE * fp;
	HANDLE hConsole;
	char forCount[basicStringSize];
	int count = 0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fp = fopen("data.txt", "wt");
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%s\t%s\t%s\t%s\n", "ID", "이름", "주소", "전화번호");
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
	printf("Total member : %d명\n\n", count);
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





