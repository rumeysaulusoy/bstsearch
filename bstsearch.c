// Rumeysa Ulusoy
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



struct node {
	char word[20];
	int frequency;
	struct node *left, *right;
};

struct node_bt {
	char word[20];
    int frequency;
	struct node *left, *right;		
};

struct linked_list{
    char word[20];
    int freq;
    struct linked_list *next;
 };

struct node* insert(int num, char name[], struct node *root); // inserts node to bst.
void inorder(struct node *root); // prints bst inorder.
void inorder_bt(struct node_bt *root); // prints bt inorder.
struct linked_list* swap(struct linked_list* ptr1, struct linked_list* ptr2 ); // swap two nodes of a linked list.
struct node_bt* insert_bt(int arr[], char *arr_char[],  struct node_bt* root, int a, int b); // inserts node to bt.
int compare_times (struct node *root, char key[], int comp); // Computes access time for a node of bst.
int compare_times_bt (struct node_bt *root, char key[], int comp); // Computes access time for a node of bt.
void sort_linkedlist (struct linked_list** head, int list); // Sorts linked list.

int main() {
FILE *file = fopen("input.txt", "r");
char id_string[10];
int id;
char word [20];
char freq_string [20];	
int freq;
char string[100];

fscanf(file, "%[^\n]%*c", string); 
char *tokenPtr = strtok(string, ","); 	
	
strcpy( id_string,   tokenPtr);
id = atoi(id_string);
tokenPtr = strtok(NULL, ",");

strcpy( word,   tokenPtr);
tokenPtr = strtok(NULL, ",");

strcpy( freq_string,   tokenPtr);
freq = atoi(freq_string);
tokenPtr = strtok(NULL, ",");
printf("The word and frequency list: \n");
printf("\n1 %s %d\n", word,freq );

struct linked_list* head = NULL;
head = malloc(sizeof(struct linked_list));
strcpy(head->word , word);
head->freq = freq;
struct linked_list* temp = head;

struct node* root = NULL;
root = insert(freq, word, root);

int last_id;
   
 while (!feof(file)) {  
    
fscanf(file, "%[^\n]%*c", string); 
char *tokenPtr = strtok(string, ","); 	
	
strcpy( id_string,   tokenPtr);
id = atoi(id_string);
tokenPtr = strtok(NULL, ",");

int i;
for(i = 0; tokenPtr[i]; i++){
  tokenPtr[i] = tolower(tokenPtr[i]);
}

strcpy( word,   tokenPtr);
tokenPtr = strtok(NULL, ",");

strcpy( freq_string,   tokenPtr);
freq = atoi(freq_string);
tokenPtr = strtok(NULL, ",");

insert(freq, word, root);	

struct linked_list* new = NULL;
new = malloc(sizeof(struct linked_list));
strcpy(new->word , word);
new->freq = freq;
temp->next = new;
new->next = NULL;
temp = new;

printf("%d %s %d\n", id,word,freq ); 
 
last_id = id;
}  	

printf("\na) BST's words with LNR (inorder): ");
inorder(root);

struct linked_list* temp2 = head;

int total_access_time;
int a = 0;
for (a; a < last_id; a++) {
 int compare = 0;
 total_access_time += compare_times(root, temp2->word, compare);	
 temp2 = temp2->next;	
}

 printf("\n\nb) Total Access Time of BST: %d", total_access_time);
 
sort_linkedlist(&head, last_id); 

struct linked_list* new_temp = head;
int arr_freq [last_id];
 
int i; 
for (i = 0; i < last_id; i++)  {
 arr_freq[i] = new_temp->freq;
 new_temp = new_temp->next; 	
}

struct linked_list* new_temp_arr = head;
const char *arr_word [last_id];

for (i = 0; i < last_id; i++)  {
 arr_word[i] = new_temp_arr->word;
 new_temp_arr = new_temp_arr->next; 	
}

struct node_bt* root_bt = insert_bt(arr_freq, &arr_word, root, 0, last_id);

printf("\n\nc) BT's words with LNR (inorder): ");
inorder_bt(root_bt);

struct linked_list* temp_bt = head;

int total_access_time_bt;
int num;
int k = 0;
for (k; k < last_id; k++) {
int compare_bt = 0; 
num = compare_times_bt(root_bt, temp_bt->word, compare_bt);

total_access_time_bt = total_access_time_bt + num;

temp_bt = temp_bt->next;	
}

printf("\n\nd) Total Access Time of BT: %d", total_access_time_bt);

}  	

struct node_bt* insert_bt(int arr[], char *arr_char[],  struct node_bt* root, int a, int b) {
 
 if (a < b) {
 	
  struct node_bt* node = (struct node_bt*)malloc(sizeof(struct node_bt));	
  node->frequency = arr[a];
  strcpy(node->word, arr_char[a]);
  node->left = node->right = NULL;
  root = node;
 
 
  root->left = insert_bt(arr, arr_char, root->left, 2*a+1, b);	
 
  root->right = insert_bt(arr, arr_char, root->right, 2*a+2, b);		
}
  return root;
}

void sort_linkedlist (struct linked_list** head, int list) {
int a, b;
int swapped;

struct linked_list** hd;

for (a = 0; a <= list; a++) {
 hd = head;	
 swapped = 0;

 for (b = 0; b < list - a - 1; b++) {

  struct linked_list* ptr1 = *hd;
  struct linked_list* ptr2 = ptr1->next;	
 
  if (ptr1->freq < ptr2->freq) {
  *hd = swap(ptr1,ptr2);
 
  swapped = 1;	
  }
 hd = &(*hd)->next;
 }	
	
 if (swapped == 0) {
 break;	
 }	

}	
}	

struct linked_list* swap(struct linked_list* ptr1, struct linked_list* ptr2 ) {

struct linked_list* temp = ptr2->next;
ptr2->next = ptr1;
ptr1->next = temp;
return ptr2;
}

struct node* insert(int num, char name[], struct node *root) {

if(root == NULL) {
	
 struct node* root = (struct node*)malloc(sizeof(struct node));

 root->frequency = num;

 strcpy(root->word, name);
 root->left = root->right = NULL;

 return root;

 }		
 
else if ( strcmp(name, root->word) == -1 ) {

 root->left = insert(num, name, root->left);	
 }	
	
else if (strcmp(name, root->word) == 1) {
	
root->right = insert(num, name, root->right);	
}	
   
return root;			
}

int compare_times_bt (struct node_bt *root, char key[], int comp) {
int access_time;	

if (root != NULL) {

 if (strcmp(key, root->word) == 0)	{
	
 comp++;	
 access_time = comp * root->frequency;
 return access_time;	
 }	
 
 else {
 comp++;	
 access_time =  compare_times_bt (root->left, key, comp) + compare_times_bt (root->right, key, comp);
 } 
}

}

int compare_times (struct node *root, char key[], int comp) {
if (root != NULL) {
	
 if ( strcmp(key, root->word) == -1 ) {
 comp++;	
 compare_times(root->left, key, comp);

 }	
	
 else if (strcmp(key, root->word) == 1) {
 comp++;	
 compare_times(root->right, key, comp);	

 }	
 else if (strcmp(key, root->word) == 0)	{
 comp++;	
 int access_time;
 access_time = comp * root->frequency;

 return access_time;	
}	

}
}

void inorder(struct node *root) {
    if(root!=NULL) 
    {
        inorder(root->left); 
        printf("\n%s ", root->word); 
        inorder(root->right);
    }
}

void inorder_bt(struct node_bt *root) {
    if(root!=NULL) 
    {
        inorder(root->left); 
        printf("\n%s ", root->word); 
        inorder(root->right);
    }
}

