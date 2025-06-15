#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bilinklist.h"

/*
    create_bilinklist:创建一个双向链表(空链表)
    返回值：
        Bilinklist *
*/
Bilinklist* create_bilinklist()
{
    Bilinklist *head = malloc(sizeof(Bilinklist));
    head->first = NULL;
    head->last = NULL;
    head->num = 0;

    return head;
}



/*
    create_bilinklist:创建一个双向链表(空链表)
    返回值：
        Bilinklist *
*/
Binode* create_binode(Elemtype *data)
{
    Binode *pnew = (Binode*)malloc(sizeof(Binode));
	strcpy( pnew->data , data );
    
    pnew->next = NULL;
    pnew->prev = NULL;

    return pnew;
}

/*
    tail_insert_binodeL:使用尾插法往双向链表中插入数据结点
    @head:链表的头结点的地址
    @pnew：待插入的数据结点
    返回值：
        void
*/
void tail_insert_binode(Bilinklist *head,Binode *pnew)
{
    //1.参数有效性验证
    if(head == NULL || pnew == NULL)
    {
        return ;
    }

    if(head->first == NULL) //空链表插入情况
    {
        head->first = pnew;
        head->last = pnew;
    }
    else    //拿到第二个数据节点或两个以上
    {
        head->last->next = pnew;
        pnew->prev = head->last;
        head->last = pnew;
    }
    head->num++;
}





/*
    delete_bilinklist:删除整个链表
    @head：待删除链表的头节点地址
    返回值：
        void
 */
void delete_bilinklist(Bilinklist *head)
{
    if(head == NULL)
    {
        return ;
    }
    //删除所有的数据结点
    Binode *del = head->first;
    while (del)
    {
        head->first = head->first->next;
        if(head->first == NULL) //删除只剩下一个结点的情况
        {
            head->last = NULL;
        }
        else    //还有多个数据节点的情况
        {
            head->first->prev = NULL;
        }
        del->next = NULL;
        free(del);
        del = head->first;
    }
    //删除头节点
    free(head);    
}




/*
    printf_bilinklist：打印双向链表
    @head:要打印的链表的头节点
    返回值：
        void
*/
void printf_bilinklist(Bilinklist *head)
{
    if(head == NULL || head->first == NULL)
    {
        return ;
    }
    Binode *p = head->first;
    while (p)
    {
        printf("%s\n",p->data);
        p = p->next;
    }
    printf("\n");
}



