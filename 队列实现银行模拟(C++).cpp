#include <iostream>
#include <cstdio>
#include <string.h>
#include <cstdlib>
#include<time.h>
#define OK 1
#define ERROR 0

typedef int Status;
using namespace std;
typedef struct{
    int ArrivalTime;
    int Duration;
}QElemType;

typedef struct QNode{
  QElemType data;
  struct QNode *next;

}QNode,*QueuePtr;
typedef struct {
   QueuePtr front;
   QueuePtr rear;
}LinkQueue;
typedef struct{
   int OccurTime;
   int NType;
}Event,ElemType;
typedef struct LNode{
  ElemType  data;
  struct LNode *next;
  }LNode,*LinkList;
typedef LinkList EventList;
//定义全局变量
EventList ev;
Event en;
LinkQueue q;
QElemType customer;
int TotalTime,CustomerNum;
int win[5];
int CloseTime;

//队列数据结构功能函数
Status InitQueue(LinkQueue &Q);
Status DestroyQueue(LinkQueue &Q);
Status ClearQueue(LinkQueue &Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead(LinkQueue Q,QElemType &e);
Status EnQueue(LinkQueue &Q,QElemType e);
Status DeQueue(LinkQueue &Q,QElemType &e);
//队列的实现
Status InitQueue(LinkQueue &Q){
  Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
   if(!Q.front)exit(0);
   Q.front->next=NULL;
   return OK;
   }
Status DestroyQueue(LinkQueue &Q){
    while(Q.front){
        Q.rear=Q.front->next;
        free(Q.front);
        Q.front=Q.rear;
    }
    return OK;
}
Status EnQueue(LinkQueue &Q,QElemType e){
     QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
     if(!p) exit(0);
     p->data=e;   p->next=NULL;
     Q.rear->next=p;
     Q.rear=p;
     return OK;
}
Status DeQueue(LinkQueue &Q,QElemType &e){
      if(Q.front==Q.rear)  return ERROR;
      QueuePtr p;
      p=Q.front->next;
      e=p->data;
      Q.front->next=p->next;
      if(Q.rear==p) Q.rear=Q.front;
      free(p);
      return OK;
}
Status QueueEmpty(LinkQueue Q){
    if(Q.front==Q.rear)
        return 1;
    return 0;

}
Status GetHead(LinkQueue Q,QElemType &e){
   QueuePtr p=Q.front;
   p=p->next;
   e=p->data;
   return OK;

}
void InitList(LinkList &q){
   q=(LinkList)malloc(sizeof(LNode));
   q->next=NULL;
}
void OrderInsert(LinkList q,Event &step){
      LinkList p=(LinkList)malloc(sizeof(LNode));
      (p->data).OccurTime=step.OccurTime;
      (p->data).NType=step.NType;
      while(q->next){
        q=q->next;
      }
      q->next=p;
      p->next=NULL;
}
Status ListEmpty(LinkList p){
   if(p->next==NULL) return OK;
   else return 0;
}
void DelFirst(LinkList &ev,Event &p){
   LinkList k=ev->next;
   p.OccurTime=(k->data).OccurTime;
   p.NType=(k->data).NType;
   k=k->next;
   ev->next=k;


}
void OpenForDay(){
   TotalTime=0;   CustomerNum=0;
   InitList(ev);
   en.OccurTime=0; en.NType=0;
   OrderInsert(ev,en);
   InitQueue(q);
  }
  void CustomerArrival(){
      int i;
      int step5=0;
      ++CustomerNum;

     int intertime = rand() % 101;

     int durtime = rand() % 101;
     int t=en.OccurTime+intertime;
     if (t<CloseTime)
     {Event step; step.OccurTime=t;step.NType=0;OrderInsert(ev,step);}
     QElemType step2;
     step2.ArrivalTime=en.OccurTime;
     step2.Duration=durtime;
     EnQueue(q,step2);
     for( i=0;i<5;i++){
        if(win[i]==0) {step5=1;break;}
     }
     win[i]=1;
     if((step5==1)&&(i!=0)){
     Event step3;
     step3.OccurTime=en.OccurTime+durtime;
     step3.NType=i;
     OrderInsert(ev,step3);
     }
}
void CustomerDeparture(){
     int i=en.NType;
     DeQueue(q,customer);
     TotalTime+=abs(en.OccurTime-customer.ArrivalTime);
     win[i]=0;
     if(!QueueEmpty(q)){
            GetHead(q,customer);
            Event step;
            step.OccurTime=en.OccurTime+customer.Duration;
            step.NType=i;
            OrderInsert(ev,step);win[i]=1;
     }

}

int main()
{ srand((unsigned) time(NULL));
   cout<<"Please Enter CloseTime: "<<endl;
   int CloseTime1;
   cin>>CloseTime1;
   CloseTime=(CloseTime1-8)*60*60;
   for(int i=0;i<5;i++)
     win[i]=0; win[0]=10;
   OpenForDay();
   while(!ListEmpty(ev)){
     Event p; DelFirst(ev,p);  en=p;
      if(en.NType==0)
        CustomerArrival();
      else CustomerDeparture();
   }
   cout<<"The TotalTime is "<<TotalTime<<"s"<<endl;
   cout<<"The CustomerNum is "<<CustomerNum<<endl;
   cout<<"The Average time is "<<float(TotalTime)/(CustomerNum)<<"s"<<endl;
     return 0;
}
