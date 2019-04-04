#include"head.h"


int main(int argc,char** argv){
	int id=1;
	int Id=1401;
	User* head=regin();
	Lottery* a_head=lot();
	History* b_head=buylot();
	loadlot(a_head,&id);  //???
	loaduser(head);
	loadHist(b_head);
	while(1){
		int ch=0;
		printf("**********欢迎来到彩民福利系统**********\n");
		printf("          1：管理员登录\n");
		printf("          2：公证人员登录\n");
		printf("          3：用户注册\n");
		printf("          4：用户登录\n");
		printf("          0：退出系统\n");
		printf("          请选择:\n");
		scanf("%d",&ch);
		while(getchar()!='\n');
		//system(clear);
		switch(ch){
			case 1:
				loginadmin(a_head,head,b_head,&id);
				break;
			case 2:
				logingre(head,b_head,a_head);
				break;
			case 3:
				system("clear");
				reginuser(head,a_head);
				sleep(1);				
				break;
			case 4:
				loginuser(head,a_head,b_head);
				sleep(1);
				system("clear");
				break;
			case 0:
				savehist(b_head);
				freeHist(b_head);
				saveuser(head);
				freeUser(head);
				savelot(a_head);
				freeLottery(a_head);
				return 0;
			default:
				printf("输入错误，请重新输入:\n");
				break;
		}	
	}	
	return 0;
}
