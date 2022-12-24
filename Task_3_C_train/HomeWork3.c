#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define LOCALIZATION "EN"



struct node {

   int NUMBER_IN_THE_SERIES;
   char* TITLE; 
   char* LANGUAGE;
   double PRICE;
   uint16_t NUMBER_OF_PAGES;
   uint16_t WEIGHT;
   uint16_t YEAR;

   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

//display the list
void printList() {
   struct node *ptr = head;
   printf("\n");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("%d,%s,\"%s\", pages = %d, Year = %d, Prise = %.2f$,Weight = %dg\n\r",ptr->NUMBER_IN_THE_SERIES,ptr->LANGUAGE,ptr->TITLE,ptr->NUMBER_OF_PAGES,ptr->YEAR,ptr->PRICE,ptr->WEIGHT);
      ptr = ptr->next;
   }
	
   
}

//insert link at the first location
void insertFirst(int NUMBER_IN_THE_SERIES, char* LANGUAGE, char* TITLE, uint16_t NUMBER_OF_PAGES, uint16_t YEAR, double PRICE, uint16_t WEIGHT) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->NUMBER_IN_THE_SERIES = NUMBER_IN_THE_SERIES;
   link->TITLE = TITLE;
	link->LANGUAGE = LANGUAGE;
   link->PRICE = PRICE;
   link->NUMBER_OF_PAGES = NUMBER_OF_PAGES;
   link->WEIGHT = WEIGHT;
   link->YEAR = YEAR;

   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

//delete first item
struct node* deleteFirst() {

   //save reference to first link
   struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

int length() {
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given NUMBER_IN_THE_SERIES
struct node* find(int NUMBER_IN_THE_SERIES) {

   //start from the first link
   struct node* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->NUMBER_IN_THE_SERIES != NUMBER_IN_THE_SERIES) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if TITLE found, return the current Link
   return current;
}

//delete a link with given NUMBER_IN_THE_SERIES
struct node* delete(int NUMBER_IN_THE_SERIES) {

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->NUMBER_IN_THE_SERIES != NUMBER_IN_THE_SERIES) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return current;
}


void reverse(struct node** head_ref) {
   struct node* prev   = NULL;
   struct node* current = *head_ref;
   struct node* next;
	
   while (current != NULL) {
      next  = current->next;
      current->next = prev;   
      prev = current;
      current = next;
   }
	
   *head_ref = prev;
}

void main() {

   insertFirst(7,LOCALIZATION,"Harry Potter and the Deathly Hallows",607,2007,30.00,380);//NUMBER_IN_THE_SERIES,LANGUAGE, TITLE,NUMBER_OF_PAGES,YEAR,PRICE,WEIGHT   
   insertFirst(6,LOCALIZATION,"Harry Potter and the Half-Blood Prince",607,2005,29.52,378);//NUMBER_IN_THE_SERIES,LANGUAGE, TITLE,NUMBER_OF_PAGES,YEAR,PRICE,WEIGHT   
   insertFirst(5,LOCALIZATION,"Harry Potter and the Order of the Phoenix",766,2003,37.89,477);//NUMBER_IN_THE_SERIES,LANGUAGE, TITLE,NUMBER_OF_PAGES,YEAR,PRICE,WEIGHT   
   insertFirst(4,LOCALIZATION,"Harry Potter and the Goblet of Fire",636,2000,30.54,396);//NUMBER_IN_THE_SERIES,LANGUAGE, TITLE,NUMBER_OF_PAGES,YEAR,PRICE,WEIGHT   
   insertFirst(3,LOCALIZATION,"Harry Potter and the Prisoner of Azkaban",317,1999,18.13,209);//NUMBER_IN_THE_SERIES,LANGUAGE, TITLE,NUMBER_OF_PAGES,YEAR,PRICE,WEIGHT   
   insertFirst(2,LOCALIZATION,"Harry Potter and the chamber of secrets",251,1998,13.96,161);//NUMBER_IN_THE_SERIES,LANGUAGE, TITLE,NUMBER_OF_PAGES,YEAR,PRICE,WEIGHT
   insertFirst(1,LOCALIZATION,"Harry Potter and the Philosopher's Stone",223,1997,10.92,122);//NUMBER_IN_THE_SERIES,LANGUAGE, TITLE,NUMBER_OF_PAGES,YEAR,PRICE,WEIGHT

   printf("Harry Potter” books series List: "); 
	//print list
   printList();
   printf("\n");

   
}
