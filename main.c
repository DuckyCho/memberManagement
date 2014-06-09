#include "memberManagementSystem.h"
#include "redBlackFunctions.h"



int main(void)

{
	int userInput = -1;
	rootPointer RP = { NULL, NULL };
	member * leafNull;

	leafNull = (member *)malloc(sizeof(member)* 1);
	leafNull->color = black;
	
	leafNull = makeTree(&RP, leafNull);

	PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

	while (1)
	{
		switch (userInput){
		case (-1) :
			userInput = printMain();
			break;
		case (0) :
			system("cls"); //id 순으로 회원보기
			userInput = printList(RP.rootNode, leafNull);
			break;
		case (1) : //회원등록하기
			system("cls");
			userInput = addData(&RP, leafNull);
			break;
		case (2) : //회원검색하기
			system("cls");
			userInput = selectSearch(&RP, leafNull);
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
		case (6) : //이름순으로 회원보기
			system("cls");
			userInput = printList(RP.rootNodeN, leafNull);
			break;
		}
	}

	return 0;
}

