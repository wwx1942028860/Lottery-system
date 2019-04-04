#include"head.h"

void userface(User* p,Lottery*a_head,History*b_head){
	int ch=0;
	while(1){
	printf("**********欢迎来到彩民福利系统**********\n");
	printf("          1：查看账户信息\n");
	printf("          2：购买彩票\n");
	printf("          3：查看购买记录\n");
	printf("          4：删除购买记录\n");
	printf("          5：更改密码\n");
	printf("          6：注销账户\n");
	printf("          7：充值账户\n");
	printf("          0：退出用户界面\n");
	printf("          请选择：\n");
	scanf("%d",&ch);
	while(getchar()!='\n');
		switch(ch){
			case 1:
				system("clear");
				printuser(p);
				break;
			case 2:
				system("clear");
				buy(p,a_head,b_head);				
				break;
			case 3:
				system("clear");
				findhist(p,b_head);
				break;
			case 4:
				system("clear");
				removehist(p,b_head);
				break;
			case 5:
				system("clear");
				updata(p);
				break;
			case 6:
				system("clear");
				removehist1(p,b_head);
				deluser(p);
				return;
			case 7:
				system("clear");
				recharge(p);
				return;
			case 0:
				return;
			default:
				printf("输入错误!\n");
				system("clear");
				break;
		}
	}
	return ;
}

