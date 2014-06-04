#include "memberManagementSystem.h"

int main(void)

{
	int userInput = -1;
	rootPointer RP = { NULL };

	member * leafNull;
	leafNull = (member *)malloc(sizeof(member)* 1);
	
	leafNull = makeTree(&RP, leafNull);
	leafNull = makeTree_Name(&RP, leafNull);

	while (1)
	{
		switch (userInput){
		case (-1) :
			userInput = printMain();
			break;
		case (0) :
			system("cls"); //회원보기
			userInput = printList(RP.rootNode, leafNull);
			break;
		case (1) : //회원등록하기
			system("cls");
			userInput = addData(&RP, leafNull);
			break;
		case (2) : //회원검색하기
			system("cls");
			userInput = selectSearch(RP, leafNull);
			break;
		case (3) : //저장하기
			system("cls");
			userInput = saveData(&RP, leafNull);
			break;
		case (4) : //종료하기
			system("cls");
			return 0;
		case (5) : //credit
			system("cls");
			userInput = credit();
		}
	}

	return 0;
}

