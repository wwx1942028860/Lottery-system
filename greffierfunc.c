#include"head.h"
/*实现公证员账户登录与公证员管理功能加载*/
void logingre(User*head,History*b_head,Lottery*a_head){
	char name[50]={0};
	char pswd[50]={0};
	printf("请输入公证人员账号：\n");
	scanf("%s",name);
	while(getchar()!='\n');
	if(strcmp(name,"123456")==0){
		printf("请输入密码：\n");
		printPswd(pswd);
		//while(getchar()!='\n');
			if(strcmp(pswd,"123456")==0){
				printf("登陆成功！\n");
				system("clear");
				greffierface(head,b_head,a_head);//调用公证员功能界面
			}
	}
	return;
}

/*公证员管理界面*/
void greffierface(User*head,History*b_head,Lottery*a_head){
	int ch=0;
	while(1){
		printf("****欢迎公证大人前来开奖噻^_^****\n");
		printf("    请选择：\n");
		printf("    1：开奖\n");
		printf("    2：退出\n");
		scanf("%d",&ch);
		while(getchar()!='\n');
		switch(ch){
			case 1:
				system("clear");
				open(head,a_head, b_head);
				break;
			case 2:
				return;
		}		
	}
}

/*彩票开奖功能*/
void open(User*head,Lottery*a_head,History* b_head){
	int id=0,i=0;
	char arr[30]={0};
	printf("请输入开奖彩票的期号：\n");
	scanf("%d",&id);
	while(getchar()!='\n');
	Lottery*q=a_head->next;
	History*w=b_head->next;
	while(w!=b_head ){       //对购买彩票链表进行操作；
		if(id == w->buydata.id){
			strcpy(w->buydata.state1,"已开奖");
		}
		w=w->next;
	}
	while(q!=a_head ){
		if(id == q->ldata.id){
			if(strcmp(q->ldata.state,"已开奖")==0){
				printf("该期已经开过奖啦^_^\n");
				break;
			}else{
				strcpy(q->ldata.state,"已开奖");
				openbonus(q);    //产生中奖号码	
				confirm(head,q, b_head);
				printf("----------------------\n");
				return ;
			}
		}
		q=q->next;	
	}		
}
/*产生中奖号码*/
void openbonus(Lottery* q){
	int arr[4]={0};
	int j=0;
	struct termios org_opts, new_opts; 
			memcpy(&new_opts, &org_opts, sizeof(new_opts));
			tcgetattr(STDIN_FILENO, &org_opts);
			new_opts.c_lflag &=~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);  
			int i=0;
			srand(time(0));
			printf("请按回车开始开奖!\n");
			printf("00-00-00-00");
			fflush(stdout);
			while(getch()!='\n');
			tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
			for(i=0;i<100;i++){
				printf("\033[11D  \b\b");
				arr[0]=rand()%100;
				printf("%2d",arr[0]);				
				fflush(stdout);
				usleep(10000);
			}
			printf(" \b-");
			for(i=0;i<100;i++){
				if(i!=0){
					printf("\b\b  \b\b");
				}else{
					printf("  \b\b");
				}
				arr[1]=rand()%100;
				printf("%2d",arr[1]);
				fflush(stdout);
				usleep(10000);
			}
			printf(" \b-");
			for(i=0;i<100;i++){
				if(i!=0){
					printf("\b\b  \b\b");
				}else{
					printf("  \b\b");
				}
				arr[2]=rand()%100;
				printf("%2d",arr[2]);
				fflush(stdout);
				usleep(10000);
			}
			printf(" \b-");
			for(i=0;i<100;i++){
				if(i!=0){
					printf("\b\b  \b\b");
				}else{
					printf("  \b\b");
				}
				arr[3]=rand()%100;
				printf("%2d",arr[3]);
				fflush(stdout);
				usleep(10000);
			}
			printf(" \b");
			tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
			printf("\n");
			
			for(j=0;j<4;j++){
				q->ldata.win[j]=arr[j];
			}	
				
}

/*确定中奖的彩票并进行发放奖金*/
void confirm(User*head,Lottery*q,History* b_head){
	int len=0,i=0,j=0,k=0,c=0,count=0;
	History* w=b_head->next;
	User* p=head->next;
	len=strlen(w->buydata.num1);
	int num[50]={0};
	while(w!=b_head){
		if(w->buydata.id==q->ldata.id){			
			for(i=0;i<len;i++){
				num[i]=(w->buydata.num1[i]-'0');
			}	
			for(i,j=0;i<len/2 && j<len;i++,j+=2){
				num[i]=(num[j]*10)+num[j+1];
			}				
			for(j=0;j<len/2;j++){
				count=0;
					for(i=0;i<4;i++){
						for(k=0;k<4;k++){						
						if(q->ldata.win[k]==num[j]){
							count++;
						}
							if(count==2){
								//printf("中了三等奖！\n");	
								strcpy(w->buydata.state1,"三等奖");
								w->buydata.cash += 5;
								q->ldata.bonus -= 5; 
								while(p!=head){
									if(strcmp(p->data.name,w->buydata.name)==0){
										p->data.money += 5;
									}
									p=p->next;
								}						
							}else if(count==3){
								//printf("中了二等奖！\n");
								strcat(w->buydata.state1,",二等奖");
								w->buydata.cash += 8;
								q->ldata.bonus -= 8; 
								while(p!=head){
									if(strcmp(p->data.name,w->buydata.name)==0){
										p->data.money += 8;
									}
									p=p->next;
								}
							}else if(count==4){								
								//printf("中了一等奖！\n");
								strcat(w->buydata.state1,",一等奖");
								w->buydata.cash += 2000;
								q->ldata.bonus -= 2000; 
								while(p!=head){
									if(strcmp(p->data.name,w->buydata.name)==0){
										p->data.money += 20;
									}
									p=p->next;
								}
							}else{
								strcpy(w->buydata.state1,"感谢您为中国足球做出的贡献！\n");
							}
						}
					}
				}
			}		
		w=w->next;
	}
}




















