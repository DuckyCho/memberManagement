#include "memberManagementSystem.h"
#include "redBlackFunctions.h"


void replaceNodeN(member * node, rootPointer * RP, member * leafNull)
{
	member * successor = findSuccessor(node, leafNull);

	/****************************************************************************************************************************************************************/

	///successor�� �����Ͽ� ������ node �� successor�� ��ġ��ų �� �߻��ϴ� ����� ��
	///00. successor�� red�� ��� : ������ node�� successor�� ��ġ��Ű�� delete end

	///01. successor�� black�� ���
	///01-0.successor�� �ڽ��� ���� ��� : deleteStep ����
	///01-1.successor�� �ڽ��� ���� ��� : successor�� successor�� �ڽ����� ��ġ��Ű�� successor�� �ڽ��� ���� successor�� �ٲ� �� delete end


	///c.f. ����case : successor�� root�� ��� : free(root)

	/****************************************************************************************************************************************************************/

	//c.f. successor�� root�ΰ�� : Ʈ���� root��� �� �ϳ��� �����ϴ� ���, root�� free, delete��
	if (successor == RP->rootNodeN)
	{
		RP->rootNodeN = NULL;
		free(successor);
	}

	//00. successor�� red�� ���
	if (successor->color == red)
	{
		if (successor->father->right == successor) //successor�� left branch���� ���� �Ǿ��� ��
		{
			//successor�ƺ��� �������� �η� �ٲٰ� successor�� Į�� ������ ����� ������ ������ ������ ��忡 successor�� ������ ����, successor�� free, delete��
			successor->father->right = leafNull;
			successor->color = node->color;
			node->id = successor->id;
			strcpy(node->address, successor->address);
			strcpy(node->phone, successor->phone);
			strcpy(node->name, successor->name);
			free(successor);
		}

		else //successor�� right branch���� ���� �Ǿ��� ��
		{
			//successor�ƺ��� �������� �η� �ٲٰ� successor�� Į�� ������ ����� ������ ������ ������ ��忡 successor�� ������ ����, successor�� free, delete��
			successor->father->left = leafNull;

			node->id = successor->id;
			strcpy(node->address, successor->address);
			strcpy(node->phone, successor->phone);
			strcpy(node->name, successor->name);

			free(successor);
		}
	}

	//01. successor�� black�� ���
	else
	{
		//������ node�� ������ succeessor�� ��ü
		node->id = successor->id;
		strcpy(node->address, successor->address);
		strcpy(node->phone, successor->phone);
		strcpy(node->name, successor->name);

		//01-00. successor�� �ڽĳ�尡 ������, succeessor delete����
		if (successor->left == leafNull && successor->right == leafNull)
		{

			deleteNodeN_step1(successor, RP, leafNull);
			if (successor->father->left == successor)
			{
				successor->father->left = leafNull;
				free(successor);
			}
			else
			{
				successor->father->right = leafNull;
				free(successor);
			}
		}

		//01-01. successor�� �ڽĳ�尡 ���� ��, successor�ڸ��� successor�� �ڽĳ�带 ��ġ (successor�� �ڽĳ��� �ݵ�� �������̾�� �ϰ�, �ڽ��� 1�� �ϼ��ۿ� ����), successor �ڽĳ�� ���� �������� ĥ�ϰ�  delete��
		else
		{
			if (successor->id < node->id)//successor�� ���� branch���� ���� �Ǿ��� ��
			{
				successor->id = successor->left->id;
				strcpy(successor->address, successor->left->address);
				strcpy(successor->phone, successor->left->phone);
				strcpy(successor->name, successor->left->name);
				free(successor->left);
				successor->left = leafNull;
			}
			else//successor�� ������ branch���� ���� �Ǿ��� ��
			{
				successor->id = successor->right->id;
				strcpy(successor->address, successor->right->address);
				strcpy(successor->phone, successor->right->phone);
				strcpy(successor->name, successor->right->name);
				free(successor->right);
				successor->right = leafNull;
			}
		}
	}
}



//case1 : sibling�� red -> �ƺ��� ������, sibling�� �������� �ٲٰ� rotate�ϰ� delete ����
void deleteNodeN_step1(member * node, rootPointer * RP, member * leafNull)
{
	member * sibling = searchMySibling(node);

	if (sibling->color == red)
	{
		node->father->color = red;
		sibling->color = black;

		if (node->father->left = node) 	//node�� �ƺ� ���ʳ���϶� (Successor�� ������ branch���� ����� ���)
			rotateLeftN(sibling->father, sibling->father->father, RP);
		else 	//node�� �ƺ� �����ʳ���϶� (Successor�� ���� branch���� ����� ���)
			rotateRightN(sibling->father, sibling->father->father, RP);
	}

	else{
		deleteNodeN_step2(node, RP, leafNull);
	}
}

//case2 : node�� ���� ����϶� : sibling�� �ڽ��� �Ѵ� red�ų� ������ red��, �������� black�ΰ�� ( node�� ������ ����϶��� vice versa)
void deleteNodeN_step2(member * node, rootPointer * RP, member * leafNull)
{
	member * sibling = searchMySibling(node);

	if (node->father->left == node)
	{
		if (sibling->color == black &&  sibling->right->color == red && (sibling->left->color == red || sibling->left->color == black))
		{
			sibling->color = sibling->father->color;
			sibling->father->color = black;
			sibling->right->color = black;
			rotateLeftN(sibling->father, sibling->father->father, RP);
		}
		else
		{
			deleteNodeN_step3(node, RP, leafNull);
		}
	}

	else
	{
		if (sibling->color == black &&  sibling->left->color == red && (sibling->right->color == red || sibling->right->color == black))
		{
			sibling->color = sibling->father->color;
			sibling->father->color = black;
			sibling->left->color = black;
			rotateRightN(sibling->father, sibling->father->father, RP);
		}
		else
		{
			deleteNodeN_step3(node, RP, leafNull);
		}
	}
}

//case3 : sibling�� ���� black, sibling�� child ������ red �������� black (successor�� ���� branch���� ����Ǿ��� ��� vice versa)
void deleteNodeN_step3(member * node, rootPointer * RP, member * leafNull)
{
	member * sibling = searchMySibling(node);
	if (node->father->left == node){
		if (sibling->color == black && sibling->left->color == red && sibling->right->color == black)
		{
			sibling->left->color = black;
			sibling->color = red;
			rotateRightN(sibling, sibling->father, RP);
			deleteNodeN_step2(node, RP, leafNull);
		}
		else
		{
			deleteNodeN_step4(node, RP, leafNull);
		}
	}

	else {
		if (sibling->color == black && sibling->right->color == red && sibling->left->color == black)
		{
			sibling->right->color = black;
			sibling->color = red;
			rotateLeftN(sibling, sibling->father, RP);
			deleteNode_step2(node, RP, leafNull);
		}
		else
		{
			deleteNodeN_step4(node, RP, leafNull);
		}
	}

}


//case 4 : sibling�� ���� black, sibling�� ���� �ڽ��� ��� black �� ���
void deleteNodeN_step4(member * node, rootPointer * RP, member * leafNull)
{
	member * sibling = searchMySibling(node);

	if (sibling->color == black && sibling->left->color == black && sibling->right->color == black)
	{
		sibling->color = red;

		if (sibling->father->color == red)
			sibling->father->color = black;

		else
		{
			if (RP->rootNodeN == sibling->father){}
			else{
				deleteNodeN_step1(sibling->father, RP, leafNull);
			}
		}
	}
}

