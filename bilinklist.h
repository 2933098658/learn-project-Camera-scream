#ifndef __BILINKLIST_H__
#define __BILINKLIST_H__

//数据结点
typedef char Elemtype;	//数据类型
typedef struct binode
{
    Elemtype data[128];	//数据域
    struct binode *prev;	//指针域，保存前驱结点的地址
    struct binode *next;	//指针域，保存后继结点的地址
}Binode;

//头节点
typedef struct Linklist
{
    Binode *first;	//指向链表的第一个数据结点的地址
    Binode *last;	//指向链表的最后一个数据结点的地址
    int num;		//记录链表中结点的个数
}Bilinklist;


Bilinklist* create_bilinklist();
Binode* create_binode(Elemtype *data);
void tail_insert_binode(Bilinklist *head,Binode *pnew);

void delete_bilinklist(Bilinklist *head);
void printf_bilinklist(Bilinklist *head);


#endif
