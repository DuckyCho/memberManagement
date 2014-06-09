#include "memberManagementSystem.h"
#include "redBlackFunctions.h"

/* 1. 회원보기 */

//printList함수에서 맨위 서식을 프린트하고 readTree함수를 불러와서 node을 출력


int printList(member * node, member * leafNull)
{
	int userInput = 0;
	int count = 1;	
	idxHead * head = (idxHead *)malloc(sizeof(idxHead) * 1);
	index * key;


	head->indexHead = addIdx();
	readTree(node, leafNull, NULL, head->indexHead,&count);//tree의 노드들로 인덱스를 구성

	key = head->indexHead->next;
	while (key->next != NULL)
	{
		key = key->next;
	}
	head->indexHead->next->prev = key;
	key->next = head->indexHead->next;
	key = head->indexHead->next;

	while (1)
	{
		key = printList_printf(key, head);
		fflush(stdin);
		userInput = functionKeyInput_memberListPrint();
		fflush(stdin);

		switch (userInput){
		case(-1) : //메인메뉴
			return userInput;
		case(0) : //id순으로 정렬 회원보기
			return userInput;
		case(2) : //회원검색
			return userInput;
		case(3) : //이전 회원 리스트보기
			if (key == head->indexHead->prev)
			{
				for (int i = 0; i < consoleRow; i++)
				{
					key = key->prev;
				}
			}
			break;
		case(4) : //다음 회원 리스트 보기
			if (key->next == head->indexHead->next)
			{
				key = head->indexHead->next;
			}
			break;
		case(6) : //이름순으로 정렬된 회원 보기
			return userInput;
		}
	}
}

index * printList_printf(index * idx, idxHead * head)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	system("cls");
	centerJustIndent(60, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf(" I  D\t   이  름\t    주  소\t\t   전화번호\n");
	centerJustIndent(63, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("───────────────────────────────\n");

	for (int i = 0; i < consoleRow; i++)
	{
		SetConsoleTextAttribute(hConsole, 15);
		centerJustIndent(60, hConsole);
		printf("%-9d%-9s%-25s\t%s\n", idx->value->id, idx->value->name, idx->value->address, idx->value->phone);
		if (idx->next == head->indexHead->next)
		{
			return idx;
		}
		idx = idx->next;
	}

	return idx;
}

index * addIdx(void)
{
	index * idx1 = (index *)malloc(sizeof(index) * (1));
	idx1->next = NULL;
	idx1->prev = NULL;
	idx1->value = NULL;
	return idx1;
}

int test_someone();

//중위 순회로 트리를 읽어옴 id기준으로 정렬되어 print됨
index * readTree(member * node, member *leafNull, void(*writeDataToTxt)(member *), index * idx,int * count)
{
	HANDLE hConsole;
	int userInput;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	index *newIdx;
	if (!*writeDataToTxt)
	{
		if (node->left != leafNull)
		{
			idx = readTree(node->left, leafNull, writeDataToTxt, idx, count);
		}

		newIdx = addIdx();
		idx->next = addIdx();
		idx->next->value = node;
		idx->next->prev = idx;
		idx = idx->next;
		(*count)++;

		if (node->right != leafNull)
		{
			idx=readTree(node->right, leafNull, writeDataToTxt, idx,count);
		}

		return idx;
	}
	else
	{
		if (node->left != leafNull)
		{
			readTree(node->left, leafNull, writeDataToTxt, idx,count);
			writeDataToTxt(node);
		}

		else
		{
			writeDataToTxt(node);
		}

		if (node->right != leafNull)
		{
			readTree(node->right, leafNull, writeDataToTxt, idx,count);
		}
		return NULL;

	}

	/*
	
	else
	{
		if (!*writeDataToTxt)
		{
			
		}
		else
		{
			writeDataToTxt(node);
		}
	}
	*/
	
}



/* 2. 회원 등록하기 */
int addData(rootPointer * RP, member * leafNull)//입력받은 회원의 정보를 RB에 넣음
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

void inputData(member * node, member * leafNull)//새로운 회원의 정보를 입력
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

/*전화번호 예외처리*/
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


/*이름 예외처리*/
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

	readTree(RP->rootNode, leafNull, writeDataToTxt,NULL,NULL);


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
	printf("Total member : %d명\n\n", count);
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




/* 8.Credit 띄우기 */

int credit(void)
{
	HANDLE hConsole;
	char * line1 = "NHN NEXT 2014 프로그래밍연습 기말과제";
	char * line2 = "김 정 봉   조 영 대";
	char * line3 = "박은종 교수님 감사합니다!";
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


/* 0. 메인 함수 */

void readData(member * node, FILE * fp, member * leafNull)
{

	fscanf(fp, "%d\t%[^\t]\t%[^\t]\t%[^\n]", &(node->id), node->name, node->address, node->phone);
	//fscanf(fp, "%d\t%[^\t]\t%[^\t]\t%[^\n]", &(node->id), node->name, node->address, node->phone);

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
