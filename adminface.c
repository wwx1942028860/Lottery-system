
#include"head.h"
/*管理员界面*/

void adminface(Lottery*a_head,User*head,int*id){
	
	int ch=0;
	
	while(1){
		printf("**********欢迎来到管理员功能界面**********\n");
		printf("          1：发行彩票\n");
		printf("          2：查询彩民信息\n");
		printf("          3：排序彩民信息\n");
		printf("          4：查询往期彩票信息\n");
		printf("          0：退出\n");
		printf("          请选择：\n");
		scanf("%d",&ch);
		while(getchar()!='\n');
		switch(ch){
			case 1:
				system("clear");
				issurelot(a_head,id);
				break;
			case 2:
				system("clear");
				findper(head);
				break;
			case 3:
				system("clear");
				sortman(head);
				printall(head);
				break;
			case 4:
				system("clear");
				look(a_head);
				sleep(2);
				system("clear");
				break;
			case 0:
				return;
			default:
				printf("输入错误，请重新输入:\n");
				system("clear");
		}
	}
}
