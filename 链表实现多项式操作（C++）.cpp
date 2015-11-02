#include <iostream>
#include <cstdio>
#include<cstring>
#include <cstdlib>
#include <conio.h>
using namespace std;
typedef struct{
 float coaf;
 int expn;
}term,ElemType;

typedef struct LNode{
  ElemType  data;
  struct LNode *next;
  }LNode,*LinkList;

typedef LinkList polynomail;
void Insert(polynomail m,polynomail k){
polynomail p=m;
if(m->next ==NULL) {m->next =k; return;}
while(p->next !=NULL) {
	polynomail q=p->next ;
	if((q->data).expn > (k->data).expn ) { k->next =q ; p->next=k; return;}
	if ((q->data).expn ==(k->data).expn ) {
		(q->data).coaf +=(k->data).coaf;
		if ((q->data).coaf ==0) {
			p->next =q->next; free(q);
		}
		return;
	}
	else p=p->next ;
}
p->next =k;
return;
}
void InsertSub(polynomail m,polynomail k){
polynomail p=m;
if(m->next ==NULL) {

        (k->data).coaf=0-(k->data).coaf;
        m->next =k; return;}
while(p->next !=NULL) {
	polynomail q=p->next ;
	if((q->data).expn > (k->data).expn ) {
             (k->data).coaf=0-(k->data).coaf; k->next =q ; p->next =k; return;}
	if ((q->data).expn ==(k->data).expn ) {
		(q->data).coaf -=(k->data).coaf;

		return;
	}
	else p=p->next ;
}
p->next =k;
return;
}

void CreatePolyn(polynomail &P,int m);//创建有序列
void DestroyPloyn(polynomail &P);//销毁链表
void PrintPolyn(polynomail P);//输出链表
int PolynLength(polynomail P);//返回一元多项式P
void AddPolyn(polynomail &Pa,polynomail &Pb);//完成多项式相加运算
void SubsractPolyn(polynomail &Pa,polynomail &Pb);//完成多项式减法
void MultipluPolyn (polynomail &Pa,polynomail &Pb);//多项式乘法
void CreatePolyn(polynomail &P,int m){
    polynomail head,p1;
    int n =1;
    head=(polynomail)malloc(sizeof(LNode));head->next=NULL;
    while(m--){
       p1=(polynomail)malloc(sizeof(LNode));
      cout<<"Enter "<<(n)<<" data:";
      cin>>(p1->data).coaf;   cin>>(p1->data).expn;
      p1->next=NULL;
      n+=1;
     Insert(head,p1);
     }
    P=head;

}
void PrintPolyn(polynomail P){
    P=P->next;
   while(P){
       if(P->next)
        {cout<<(P->data).coaf<<"x^"<<(P->data).expn<<"+";
       P=P->next;}
       else{cout<<(P->data).coaf<<"x^"<<(P->data).expn;P=P->next;
       }
}
cout<<endl;
}
void DestroyPloyn(polynomail &P){
     polynomail q=P->next;
     while(P->next){free(P);P=q;q=q->next;}

}
int PolynLength(polynomail P){
    P=P->next;int i=0;
    while(P){
        i++;
        P=P->next;
    }
    return i;

}
void AddPolyn(polynomail &Pa,polynomail &Pb){
       polynomail P=Pb->next;
       while(P){
         Insert(Pa,P);  P=P->next;
       }
       }
void SubsractPolyn(polynomail &Pa,polynomail &Pb){
     polynomail P=Pb->next;
       while(P){
         InsertSub(Pa,P);  P=P->next;
       }
}
void MultipluPolyn (polynomail &Pa,polynomail &Pb){
        polynomail Pc=(polynomail)malloc(sizeof(LNode));
        polynomail P=(polynomail)malloc(sizeof(LNode));
        polynomail p1=Pa->next,p2=Pb->next,p3;
        P->next=NULL;
        while(p1){
                p3=p2;
            while(p3){
                    Pc=(polynomail)malloc(sizeof(LNode));
                (Pc->data).coaf=(p1->data).coaf*(p3->data).coaf;
                (Pc->data).expn=(p1->data).expn+(p3->data).expn;
                Pc->next=NULL;
                 Insert(P,Pc);
                p3=p3->next;
            }
            p1=p1->next;
        }
      Pa->next=P->next;


}
void printmenu(){
    cout<<endl;
  cout<<"1.CreatePolyn"<<endl<<"2.DestroyPloyn"<<endl<<"3.PrintPolyn"<<endl;
  cout<<"4.PolynLength"<<endl<<"5.AddPolyn"<<endl<<"6.SubsractPolyn"<<endl<<"7.MultipluPolyn"<<endl<<"8.finish this"<<endl;
}
int main ()
{  polynomail head1=NULL,head2=NULL;int m;
  printmenu();
 fflush(stdin);char c=getche();system("cls");
 while(1){
  switch (c)
            {

    case '1':cout<<"Number:";cin>>m;CreatePolyn(head1,m);printmenu();fflush(stdin);break;
    case '2':DestroyPloyn(head1);printmenu();break;
    case '3':PrintPolyn(head1);printmenu();break;
    case '4':PolynLength(head1);printmenu();break;
            }
         if(c=='8') {cout<<"The second poly";printmenu();break;}
          c=getche();system("cls");
 }
 while(1){
  switch (c)
            {
    case '1':cout<<"Number:";cin>>m;CreatePolyn(head2,m);printmenu();break;
    case '2':DestroyPloyn(head2);printmenu();break;
    case '3':PrintPolyn(head2);printmenu();break;
    case '4':PolynLength(head2);printmenu();break;
    case '5':AddPolyn(head1,head2);PrintPolyn(head1);printmenu();break;
    case '6':SubsractPolyn(head1,head2);PrintPolyn(head1);printmenu();break;
    case '7':MultipluPolyn(head1,head2);PrintPolyn(head1);printmenu();break;
            }
            c=getche();system("cls");
            if(c=='8') break;
}
}
