#include <stdio.h>
#include <stdlib.h>
struct linkedList
{
  int data;
  struct linkedList *next;  
};

struct linkedList *head = NULL;


void printList(){
  struct linkedList *node = head;

  printf("Print linked list:\n");

  while(node!=NULL){
    printf("%d\n", node->data);
    node = node -> next;
  }
}

void insertNode(int data, int num){
	if (head==NULL){
  struct linkedList *link = (struct linkedList*) malloc(sizeof(struct linkedList));
  link->data = data;
  head = link;
  head->next = NULL;
return;
}
    struct linkedList *link = (struct linkedList*) malloc(sizeof(struct linkedList));
    link->data = data;
    link->next = NULL;
    struct linkedList *previous = head;
    struct linkedList *search = previous->next;
    for(int index=0;index<num - 1;index++){
      previous = search;
      search = search->next;
    }
    link->next=search;
    previous->next=link;
  printf("%d node was inserted\n", data);
}

void deleteNode(int num){
  if(num==0){
    printf("Can't delete head node!\n");
    return;
  }

  struct linkedList *previous = head;
  struct linkedList *search = previous->next;

  for(int index=0;index<num - 1;index++){
      previous = search;
      search = search->next;
    }
    previous->next=search->next;
    printf("Deleted %d\n",search->data);
    free(search);
}


int main(){
  insertNode(1,0);
  insertNode(3,1);
  insertNode(5,2);
  printf ("\n");
  printList();

  printf ("\n");

  insertNode(4,2);
 
  printf ("\n");
  printList();

  printf ("\n");
  deleteNode(2);

  printf ("\n");
  printList();

  printf ("\n");

  insertNode(7,2);

  printf ("\n");
  printList();

  return 0;
}
