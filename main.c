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
			system("cls");
			userInput = printList(RP.rootNode, leafNull);
			break;
		case (1) :
			system("cls");
			userInput = addData(&RP, leafNull);
			break;
		case (2) :
			userInput = printMain();
		case (3) :
			system("cls");
			//userInput = deleteMember(&RP, leafNull);
			break;
		case (4) :
			system("cls");
			userInput = searchData(RP, leafNull);
			break;
		case (5) :
			system("cls");
			userInput = saveData(&RP, leafNull);
			break;
		case (6) :
			system("cls");
			return 0;
		case (7) :
			system("cls");
			userInput = credit();
		}
	}

	return 0;
}

