#ifndef _head_h
#define _head_h
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>  
#include <unistd.h>  
# include <termios.h>  
# include <assert.h> 
# include <time.h> 
/*---------------用户头文件-------------------*/
typedef struct Data{
	char name[20];
	char pswd[20];
	double money;
}Data;

typedef struct User{
	Data data;
	struct User* prev;
	struct User* next;
}User;

typedef struct LData{
	int id;   //彩票期号
	double price;  //彩票价格
	double bonus;   //奖池金额
	int win[4]; //获奖号码。
	int num;  //发行总数
	char state[50]; //开奖状态
	int flag;  //发奖标志
}LData;

typedef struct Lottery{
	LData ldata;
	struct Lottery* prev;
	struct Lottery* next;
}Lottery;

typedef struct Buydata{
	int Id;//彩票的唯一标识符
	int id;
	char name[50];
	char num1[50]; //下注号码的保存
	char state1[50];
	double cash;	//中奖金额
	int bet;  //下注注数
}Buydata;

typedef struct History{
	Buydata buydata;
	struct History* prev;
	struct History* next;
}History;

User* regin();
int getch();
void Secno();
void printPswd(char* pswd);
User* finduser(User*head);
void reginuser(User*head,Lottery*a_head);
void saveuser(User*head);
void loaduser(User*head);
void freeUser(User* head);
void loginuser(User*head,Lottery*a_head,History*b_head);
void userface(User* p,Lottery*a_head,History*b_head);
void updata(User*p);
void recharge(User*p);
void deluser(User*p);
void printuser(User*p);
void removehist1(User*p,History*b_head);

/*---------------管理员头文件-------------------*/


Lottery* lot();
void loginadmin(Lottery*a_head,User*head,History*b_head,int*id);
void issurelot(Lottery*a_head,int*id);
void findper(User*head);
void loadlot(Lottery*a_head,int*id);
void savelot(Lottery*a_head);
void printlot(Lottery*a_head);
Lottery* findlot(Lottery*a_head);
void freeLottery(Lottery* a_head);
void adminface(Lottery*a_head,User*head,int*id);
void sortman(User*head);
void printall(User*head);
void look(Lottery*a_head);

/*---------------公证员头文件-------------------*/
//int getch();
//void printPswd(char* pswd);
void openbonus(Lottery* q);
void open(User*head,Lottery*a_head,History* b_head);
void logingre(User*head,History*b_head,Lottery*a_head);
void printPswd(char* pswd);
void confirm(User*head,Lottery*q,History* b_head);
void greffierface(User*head,History*b_head,Lottery*a_head);
/*---------------购买彩票头文件-------------------*/


History* buylot();
void printdown(char* downnum);
void buy(User*p,Lottery*a_head,History*b_head);
void freeHist(History*b_head);
void savehist(History*b_head);
void loadHist(History*b_head);
void findhist(User*p,History*b_head);
void removehist(User*p,History*b_head);

#endif
