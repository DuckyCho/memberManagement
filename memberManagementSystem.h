#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#define basicStringSize 80
#define black 0
#define red 1
#define initialValue 100
#define zero 0
#pragma warning (disable : 4996)

typedef struct {
	struct mem_t * rootNode;

} rootPointer;

typedef struct mem_t {
	int id;
	char name[32];
	char address[32];
	char phone[32];
	int color;
	struct mem_t * father;
	struct mem_t * left;
	struct mem_t * right;

} member;


/* ����� Ʈ�� */
void redBlackTree(member *, rootPointer *, member *);
void insert_case1(member *, rootPointer *, member *);
void insert_case2(member *, rootPointer *, member *);
void insert_case3(member *, rootPointer *, member *);
void insert_case4(member *, rootPointer *, member *);
void insert_case5(member *, rootPointer *, member *);
void rotateRight(member*, member *, rootPointer *);
void rotateLeft(member*, member *, rootPointer *);
member * searchMyFather(member *, member*, member *);
member * searchMyUncle(member *);

member * findSuccessor(member *, member *);
member * findLeftSuccessor(member *, member *);
member * findRightSuccessor(member * , member *);
void replaceNode(member * , rootPointer * , member * );
member * searchMySibling(member * );
void deleteNode_step1(member * , rootPointer * , member * );
void deleteNode_step2(member *, rootPointer *, member *);
void deleteNode_step3(member *, rootPointer *, member *);
void deleteNode_step4(member *, rootPointer *, member *);


/* 1. ȸ����� ���� */
void readTree(member *, member *);
int printList(member *, member*);

/* 2. ȸ�� ����ϱ� */
int addData(rootPointer * RP, member*);
int inputData(member * node, member * leafNull);
int searchBiggestId(member *, member *);

void askModify(member* searchPerson);
void modify(member* searchPerson);

/* 3. ȸ�� �����ϱ� */
member * deleteUI(rootPointer * , member *);

/* 5. ȸ�� �˻��ϱ�*/

int searchData(rootPointer RP, member * leafNull);
int selectSearch();
int searchUI(int upOrDown);
int findById(rootPointer RP, member * leafNull);
int findByName(rootPointer RP, member * leafNull);
member* searchName(char* name, member * compare, member * leafNull, member* rootNode, member** searchPerson);
member* searchId(int id, member * compare, member * leafNull, member** thisMan);


/* 8. credit ���� */
int credit(void);


/* 0.���� �Լ� */
void readData(member *, FILE *, member *);
void attachTree(member *, rootPointer *, member *);
member * firstFunc(rootPointer *, member*);
member * addNode(void);

/* ���� UI�Լ� */
int printMain(void);
int mainUI(int);
void centerJustIndent(int /*input strlen*/, HANDLE);
int functionKeyInput(void);