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

/* 레드블랙 트리 - id로 정렬*/
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

/*레드블랙 트리 - name으로 정렬*/
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

/*레드블랙 트리 - 삭제하기*/
member * findSuccessor(member *, member *);
member * findLeftSuccessor(member *, member *);
member * findRightSuccessor(member *, member *);
void replaceNode(member *, rootPointer *, member *);
member * searchMySibling(member *);
void deleteNode_step1(member *, rootPointer *, member *);
void deleteNode_step2(member *, rootPointer *, member *);
void deleteNode_step3(member *, rootPointer *, member *);
void deleteNode_step4(member *, rootPointer *, member *);

/* 1. 회원명단 보기 */
void readTree(member *, member *, void(*)(member *));
int printList(member *, member*);

/* 2. 회원 등록하기 */
int addData(rootPointer * RP, member*);
void inputData(member * node, member * leafNull);
int searchBiggestId(member *, member *);
void phoneCheck(member*);
void nameCheck(member*);

/* 3. 회원 삭제하기 */
int deleteUI(member*, rootPointer *, member *);

/* 4. 회원정보 검색/수정/삭제*/
void showMember(member* searchPerson);
member* searchName(char*, member *, member *);
member* searchId(int, member *, member *);
int selectSearch(rootPointer, member *);
int searchUI(int);

//이름으로 검색
int find_byName(rootPointer , member * );
void modify_byName(member* , rootPointer* , member* );

//회원번호로 검색
int find_byId(rootPointer , member * );
void modify_byId(member* , rootPointer* RP, member* );

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

