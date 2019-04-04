#include"head.h"

/*实现将———隐藏*/
void printdown(char* downnum){
	int i=0,j=0,res=0;
	int count=0;
	printf("-- -- -- --");		
	while(1){	
		res=getch();
		if(count==0){
			printf("\b\b\b\b\b\b\b\b\b\b\b");
			count++;
		}			
		if((char)res=='\n' || i==8){
			printf("\n");
			return;
		}else if((char)res==127 && i>0){
			if(i==1){	
				//printf("\b\b-\b");
				printf("\b-\b");
				i--;
			}else if(i%2==0){
				printf("\b\b-\b");
				i--;
			}else{
				printf("\b-\b");
				i--;
			}		
		}else if((char)res >='0' && (char)res <='9'){
			printf(" \b");
			printf("%c",(char)res);
			downnum[i]=(char)res;
			i++;
			//printf("%d",i);
			if(i%2==0 && i!=8){
				printf(" ");
			}
		}
	}	
}

/*实现彩民购买彩票*/
void buy(User*p,Lottery*a_head,History*b_head){
	//History*w=b_head->next;
	Lottery* q=a_head->next;
	//History* w=b_head->next;	
	int i=0,count=0,len=0,Id=0;
	char str[15]={0};
	char downnum[100]={0};
	char downnum2[100]={0};
	char name1[30]={0};
	char state2[30]={0};
	while(q!=a_head){
		if(strcmp(q->ldata.state,"已开奖")!=0){
		printf("**********欢迎购买彩票!************\n");
		printf("      本期期号为：%d\n",q->ldata.id);
		printf("      本期的彩票价格：为每注%.2lf元\n",q->ldata.price);
		for(i=0;i<5;i++){
			printf("      是否下注:[y]或[n](最多下五注)\n");
			scanf("%s",str);
			while(getchar()!='\n');
			if(strcmp(str,"y")==0 && p->data.money - q->ldata.price >=0){
					count++;
					if(count>5){break;}
					printdown(downnum);					
					p->data.money -= q->ldata.price;
					printf("      您的账户余额为%.2lf元\n",p->data.money);
					q->ldata.bonus += q->ldata.price;			
					strcat(downnum2,downnum);  //将下注号码拼接到购买记录中；					 					
				}else{
					q->ldata.num += 1; //发行数目加一 
					system("clear");
					break;
				}
			}
				if(p->data.money - q->ldata.price <0){
					//len=strlen(downnum2);     //得出下注号码的长度；					
					printf("余额不足，请及时充值！\n");
					sleep(1);
					printf("1s后返回到用户界面！\n");
					return;
				}								
				History* newnode=calloc(1,sizeof(History));
				newnode->next=NULL;
				newnode->prev=NULL;
				
				newnode->buydata.Id=q->ldata.id*1000+q->ldata.num;
				strcpy(newnode->buydata.state1,"未中奖");
				newnode->buydata.cash=0;
				// 
				newnode->buydata.bet=count;
				newnode->buydata.id=q->ldata.id; 		//赋值期号
				strcpy(newnode->buydata.num1,downnum2); //将下注号码赋值到链表里面；
				strcpy(newnode->buydata.name,p->data.name);  //赋值名字
				
				History*w=b_head->prev;
				w->next=newnode;
				newnode->next=b_head;
				newnode->prev=w;
				b_head->prev=newnode;

				
				return;
			
		}
		q=q->next;
		//w=w->next;			
	}	
}

/*将购买的彩票信息保存到文件*/
void savehist(History*b_head){
	FILE* fp=fopen("./history.txt","w");
	History* w = b_head->next;
	while(w!=b_head){
		fprintf(fp,"%s %d %d %s %s %lf\n",w->buydata.name,w->buydata.Id,w->buydata.id,w->buydata.state1,w->buydata.num1,w->buydata.cash);
		w=w->next;
	}
	fclose(fp);
}

/*实现彩民账户信息的加载*/
void loadHist(History*b_head){
	Buydata buydata={0};
	FILE* fp=fopen("./history.txt","r");
	while(1){
		if(fp==NULL){return;}
		if(fscanf(fp,"%s %d %d %s %s %lf\n",buydata.name,&buydata.Id,&buydata.id,buydata.state1,buydata.num1,&buydata.cash)!=6){
			//(*Id)=buydata.Id+1;			
			break;
		}
		History* newnode=calloc(1,sizeof(History));
		newnode->buydata=buydata;
		History* w=b_head->prev;
		w->next=newnode;
		newnode->next=b_head;
		newnode->prev=w;
		b_head->prev=newnode;

	}
	fclose(fp);
}

/*实现账户购买彩票历史的查询*/
void findhist(User*p,History*b_head){
	History* w=b_head->next;
	while(w!=b_head){
		if(strcmp(p->data.name,w->buydata.name)==0){
			printf("————————————————————————————————\n");
			printf("彩票期号：%d\n",w->buydata.id);
			printf("彩票Id：%d\n",w->buydata.Id);
			printf("用户姓名：%s\n",w->buydata.name);
			printf("下注号码：%s\n",w->buydata.num1);
			printf("中奖状态：%s\n",w->buydata.state1);			
			printf("中奖金额：%.2lf\n",w->buydata.cash);
			printf("————————————————————————————————\n");
		}
		w=w->next;
	}
}

/*实现将用户购买历史的删除*/
void removehist(User*p,History*b_head){
	char str[5]={0};
	History*w=b_head->next;
	printf("是否删除历史记录？(y 或 n)\n");
	scanf("%s",str);
	while(getchar()!='\n');
	if(strcmp(str,"y")==0){
		while(w!=b_head){
			if(strcmp(p->data.name,w->buydata.name)==0){
				w->next->prev=w->prev;
				w->prev->next=w->next;
			}
			w=w->next;
		}
		printf("删除成功，1s后返回用户界面\n");
		free(w);  //问下放在这里可不可以
		sleep(1);
	}else{
		return;
	}
}




/*将堆空间释放*/
void freeHist(History*b_head){
	History* p=b_head;
	while(p->next!=b_head){	
		p=p->next;
		free(p->prev);
	}
	free(p);
}

