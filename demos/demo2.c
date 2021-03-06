/**
 *       _____
 * ANSI / ___/
 *     / /__  
 *     \___/  
 *
 * Filename: demo2.c
 * Author  : Dan Levin
 * Date    : Wed Feb 20 11:59:40 GMT 2013
 * Version : 0.15
 * ---
 * Description: A short C demo program testing the function interface of library LevAWC, doubly-linked list. 
 * 
 * Revision history: (this is where you document the diffs between versions...)
 * Date   Revision
 * 121212 Created this program the first time..
 * 121218 After some editing I consider this hack ready for going public :-)
 * 130205 Used the new function 'int DLISTfind_remove()'...
 * 130205 Further editing - more extensive error handling than before..
 * 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dlist.h"

#ifndef OK
#define OK 0
#endif

#define NR_OF_ITEMS 10
#define NR_OF_REMOVALS 3
#define NR_OF_INSERTS 3

/* Function declarations */
void my_destroy(void *data);
void print(const void *data);
int my_cmp(const void *key1, const void *key2);
int my_random(int start, int stop);
void my_clearscrn(void);
void prompt_and_pause(char *message);
int my_match(const void *k1, const void *k2);

void add_nodes(Dlist list, int nr_of_nodes);
void remove_nodes(Dlist list, int nr_of_removes);
void insert_nodes(Dlist list, int nr_of_insertions);

/* Function definitions - the rest of the program */
/* --- Function: int my_random(int start, int stop) --- */
int my_random(int start, int stop)
{
  return start+rand()%(stop-start+1);
}

/* --- Function: void my_destroy(void *data) --- */
void my_destroy(void *data)
{
  free(data);
}

/* --- Function: void print(const void *data) --- */
void print(const void *data)
{
  printf(" %02d", *(int *)data);
}

/* --- Function: int my_cmp(const int *key1, const int *key2) --- */
int my_cmp(const void *key1, const void *key2)
{
  return (*(int *)key1 - *(int *)key2);
}

/* --- Function: void my_clearscrn(void) --- */
void my_clearscrn(void)
{
#ifdef __unix__
  system("clear");
#elif _WIN32
  system("cls");
#endif
}

/* --- Function: void prompt_and_pause(char *message) --- */
void prompt_and_pause(char *message)
{
  printf("%s", message);
  printf(" - Hit <Enter> to continue...");
  getchar();
}

/* --- Function: int my_match(const void *k1, const void *k2) --- */
int my_match(const void *k1, const void *k2)
{
  return *(int *)k1 == *(int *)k2;
}

/* --- void init_nodes(Dlist list, int nr_of_nodes) --- */
void add_nodes(Dlist list, int nr_of_nodes)
{
  int i=0, *pi, retval;

  do
    {
      pi = (int *)malloc(sizeof(int));
      *pi = my_random(1,50);

      /* Defensive programming... */
      i == 0 ? (retval=DLISTinsprev(list, NULL, pi)) : (retval=DLISTinsprev(list, DLISThead(list), pi)) ;
      assert(retval == OK);

    } while (++i < nr_of_nodes);

  printf("\nCurrent list content(%d nodes): ", DLISTsize(list));
  DLISTtraverse(list, print, DLIST_FWD);
}

/* --- Function: void remove_nodes(Dlist list, int nr_of_removes) --- */
void remove_nodes(Dlist list, int nr_of_removes)
{
  int i=0, tmp, *pi, retval;

  do
    {
      printf("\nCurrent list content(%d nodes): ", DLISTsize(list));
      DLISTtraverse(list, print, DLIST_FWD);

      printf("\nEnter keydata for node to be removed: ");
      scanf("%d", &tmp);
      getchar(); /* Remove CR from input buffer */

      /* Remove node - and free memory */
      pi = &tmp;

      if ((retval = DLISTfind_remove(list, (void **)&pi)) != 0)
	{
	  if (retval == 1)
	    printf("Node %d not found in list...!", tmp);	    
	  else 
	    {
	      if (retval == -2)
		printf("\nMatch-callback is missing... - bailing out!");
	      else
 		printf("\nFatal error... - bailing out!");
	      exit(retval);
	    }
	}
      else
	{
	  printf("Node %d removed...!", *pi);
	  free(pi);
	}

      i++;

    } while (i < nr_of_removes);
}

/* --- Function: void insert_nodes(Dlist list, int nr_of_insertions) --- */
void insert_nodes(Dlist list, int nr_of_insertions)
{
  int i=0, tmp, *pi;
  DlistNode node;

  do
    {
      printf("\nCurrent list content(%d nodes): ", DLISTsize(list));
      DLISTtraverse(list, print, DLIST_FWD);

      printf("\nEnter nodedata of node after which 99 should be inserted: ");
      scanf("%d", &tmp);
      getchar(); /* Remove CR from input buffer */

      if ((node = DLISTfindnode(list, &tmp)) != NULL) /* Node found */
	{
	  /* Insert node after first occurance of user-specified node */
	  pi = (int *)malloc(sizeof(int));
	  *pi = 99;

	  if ((DLISTinsnext(list, node, pi)) != 0)
	    {
	      printf("Fatal error - exiting...");
	      exit(-1);
	    }
	  else
	    printf("Node 99 inserted after node %d", *(int *)DLISTdata(node));
	}
      else
	  printf("Node %d not found...!", tmp);

      i++;

    } while (i < nr_of_insertions);
}

int main(void)
{
  /* Declare YOUR variables here ! */
  Dlist mylist;

  srand((unsigned int)time(NULL));
  my_clearscrn();

  printf("--- INITIALIZING A DOUBLY-LINKED LIST, %d NODES, RANDOM INTEGER DATA ---", NR_OF_ITEMS);
  mylist = DLISTinit(my_destroy); /* Initialize the list */
  if ((mylist = DLISTinit(my_destroy)) == NULL) /* Initialize the list */
    {
      printf("\nFatal error... - bailing out!");
      exit(-1);
    }

  add_nodes(mylist, NR_OF_ITEMS); /* Populate the list */
  prompt_and_pause("\nNext - let's SORT the list...");

  printf("--- SORTED LIST ---");
  DLISTsort(mylist, my_cmp);
  printf("\nCurrent list content(%d nodes): ", DLISTsize(mylist));
  DLISTtraverse(mylist, print, DLIST_FWD);
  
  prompt_and_pause("\nNow - let's TRAVERSE the list - backwards...");
  printf("--- LIST TRAVERSED - BACKWARDS ---");
  printf("\nCurrent list content(%d nodes): ", DLISTsize(mylist));
  DLISTtraverse(mylist, print, DLIST_BWD);
  prompt_and_pause("\nNext - let's REMOVE some nodes..");

  DLISTsetmatch(mylist, my_match);

  printf("--- REMOVE %d NODES/DATA FROM THE LIST ---", NR_OF_REMOVALS);
  remove_nodes(mylist, NR_OF_REMOVALS);
  printf("\nCurrent list content(%d nodes): ", DLISTsize(mylist));
  DLISTtraverse(mylist, print, DLIST_FWD);
  prompt_and_pause("\nFinally - let's ADD some nodes...");
  
  my_clearscrn();
  printf("--- ADD NODES WITH DATA=99 AFTER %d SPECIFIED NODES ---", NR_OF_INSERTS);
  insert_nodes(mylist, NR_OF_REMOVALS);
  printf("\nFinal list content(%d nodes): ", DLISTsize(mylist));
  DLISTtraverse(mylist, print, DLIST_FWD);

  prompt_and_pause("\n\nLet's tidy up and destroy the list.. - Bye!");

  DLISTdestroy(mylist);

  return 0;
}

