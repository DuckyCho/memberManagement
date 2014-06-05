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
			system("cls"); //ȸ������
			userInput = printList(RP.rootNode, leafNull);
			break;
		case (1) : //ȸ������ϱ�
			system("cls");
			userInput = addData(&RP, leafNull);
			break;
		case (2) : //ȸ���˻��ϱ�
			system("cls");
			userInput = selectSearch(RP, leafNull);
			break;
		case (3) : //�����ϱ�
			system("cls");
			userInput = saveData(&RP, leafNull);
			break;
		case (4) : //�����ϱ�
			system("cls");
			return 0;
		case (5) : //credit
			system("cls");
			userInput = credit();
		}
	}

	return 0;
}

