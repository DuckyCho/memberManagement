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
	struct mem_t * rootNodeN;
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

/* ����� Ʈ�� - id�� ����*/
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

/*����� Ʈ�� - name���� ����*/
void redBlackTreeN(member *, rootPointer *, member *);
void insertN_case1(member *, rootPointer *, member *);
void insertN_case2(member *, rootPointer *, member *);
void insertN_case3(member *, rootPointer *, member *);
void insertN_case4(member *, rootPointer *, member *);
void insertN_case5(member *, rootPointer *, member *);
void rotateRightN(member*, member *, rootPointer *);
void rotateLeftN(member*, member *, rootPointer *);
member * searchMyFatherN(member *, member*, member *);
member * searchMyUncleN(member *);

/*����� Ʈ�� - �����ϱ�*/
member * findSuccessor(member *, member *);
member * findLeftSuccessor(member *, member *);
member * findRightSuccessor(member *, member *);
void replaceNode(member *, rootPointer *, member *);
member * searchMySibling(member *);
void deleteNode_step1(member *, rootPointer *, member *);
void deleteNode_step2(member *, rootPointer *, member *);
void deleteNode_step3(member *, rootPointer *, member *);
void deleteNode_step4(member *, rootPointer *, member *);

/* 1. ȸ����� ���� */
void readTree(member *, member *, void(*)(member *));
int printList(member *, member*);

/* 2. ȸ�� ����ϱ� */
int addData(rootPointer * RP, member*);
void inputData(member * node, member * leafNull);
int searchBiggestId(member *, member *);
void phoneCheck(member*);
void nameCheck(member*);

/* 3. ȸ�� �����ϱ� */
int deleteUI(member*, rootPointer *, member *);

/* 4. ȸ������ �˻�/����/����*/
void showMember(member* searchPerson);
member* searchName(char*, member *, member *);
member* searchId(int, member *, member *);
int selectSearch(rootPointer, member *);
int searchUI(int);

//�̸����� �˻�
int find_byName(rootPointer , member * );
void modify_byName(member* , rootPointer* , member* );

//ȸ����ȣ�� �˻�
int find_byId(rootPointer , member * );
void modify_byId(member* , rootPointer* RP, member* );

/* 6. �����ϱ�*/
int saveData(rootPointer *, member *);
void writeDataToTxt(member *);

/* 8. credit ���� */
int credit(void);

/* 0.���� �Լ� */
void readData(member *, FILE *, member *);
void attachTree(member *, rootPointer *, member *);

void attachTreeN(member *, rootPointer * , member *);
member * makeTree(rootPointer *, member*);
member * makeTree_Name(rootPointer * , member *);
member * addNode(void);

/* ���� UI�Լ� */
int printMain(void);
int mainUI(int);
void centerJustIndent(int /*input strlen*/, HANDLE);
int functionKeyInput(void);
int functionKeyInput_WhenSearchResultVoid(void);

