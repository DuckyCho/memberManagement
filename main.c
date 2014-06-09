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


		fflush(stdin);
		switch (userInput){
		case (-1) :
			userInput = printMain();
			break;
		case (0) :
			system("cls"); //id ������ ȸ������
			userInput = printList(RP.rootNode, leafNull);
			break;
		case (1) : //ȸ������ϱ�
			system("cls");
			userInput = addData(&RP, leafNull);
			break;
		case (2) : //ȸ���˻��ϱ�
			system("cls");
			userInput = selectSearch(&RP, leafNull);
			break;
		case (3) : //�����ϱ�
			system("cls");
			userInput = selectSearch(&RP, leafNull);
			break;
		case (4) : //�����ϱ�
			system("cls");
			userInput = selectSearch(&RP, leafNull);
			break;
		case (5) : //�����ϱ�
			system("cls");
			userInput = saveData(&RP, leafNull);
			break;
		case (6) : //�����ϱ�
			system("cls");
			return 0;
		case (7) : //credit
			system("cls");
			userInput = credit();
			PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
			break;
		case (8) : //�̸������� ȸ������
			system("cls");
			userInput = printList(RP.rootNodeN, leafNull);
			break;
		}
	}

	return 0;
}

