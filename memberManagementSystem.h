#ifndef memberManagementSystem.h

#define memberManagementSystem

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>

#define basicStringSize 80
#define mem_tStringSize 32
#define black 0
#define red 1
#define initialValue 100
#define zero 0
#define idTree 0
#define nameTree 1
#pragma warning (disable : 4996)

typedef struct {
	struct mem_t * rootNode;
	struct mem_t * rootNodeN;
} rootPointer;

typedef struct mem_t {
	int id;
	char name[mem_tStringSize];
	char address[mem_tStringSize];
	char phone[mem_tStringSize];
	int color;
	struct mem_t * father;
	struct mem_t * left;
	struct mem_t * right;
	struct mem_t * otherTreePointer;
	int treeType;
} member;


/* 1. 회원명단 보기 */
void readTree(member *, member *, void(*)(member *));
int printList(member *, member*);

/* 2. 회원 등록하기 */
void removeNewLine(char * );
int addData(rootPointer * RP, member*);
void inputData(member * node, member * leafNull);
int searchBiggestId(member *, member *);
void phoneCheck(member*);
void nameCheck(member*);
void phoneCheck_modify(member* node);

/* 3. 회원 삭제하기 */
int deleteUI(member*, rootPointer *, member *);


/* 4. 회원정보 검색/수정/삭제*/

void nodeCpy(member *, member *);
void showMember(member* searchPerson);
member* searchName(char*, member *, member *);
member* searchId(int, member *, member *);
int selectSearch(rootPointer*, member *);
int selectModify(member*, rootPointer*, member*);
int searchUI(int);
int modifyUI(int, member*);
int find(rootPointer* , member * , int );
int modify(member*, rootPointer*, member*);




/* 6. 저장하기*/
int saveData(rootPointer *, member *);
void writeDataToTxt(member *);

/* 8. credit 보기 */
int credit(void);

/* 0.메인 함수 */
void readData(member *, FILE *, member *);
void attachTree(member *, rootPointer *, member *);

void attachTreeN(member *, rootPointer * , member *);
member * makeTree(rootPointer *, member*);
member * makeTree_Name(rootPointer * , member *);
member * addNode(void);

/* 메인 UI함수 */
int printMain(void);
int mainUI(int);
void centerJustIndent(int /*input strlen*/, HANDLE);
int functionKeyInput(void);
int functionKeyInput_WhenSearchResultVoid(void);

#endif
