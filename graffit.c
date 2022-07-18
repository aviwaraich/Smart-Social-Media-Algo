#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024
#ifndef __testing
#define MAT_SIZE 3	// A small graph
#endif

typedef struct user_struct {
    char name[MAX_STR_LEN];
    struct friend_node_struct* friends;
    struct brand_node_struct* brands;
    bool visited;
} User;

typedef struct friend_node_struct {
    User* user;
    struct friend_node_struct* next;
} FriendNode;

typedef struct brand_node_struct {
    char brand_name[MAX_STR_LEN];
    struct brand_node_struct* next;
} BrandNode;

FriendNode* allUsers; 

int brandAdjacencyMatrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];
User *saveduser; //Saved a user
int savedcount = 0; //Save a count

/**
 * Checks if a user is inside a FriendNode LL.
 */
bool in_friend_list(FriendNode *head, User *node) {
  for (FriendNode *cur = head; cur != NULL; cur = cur->next) {
    if (strcmp(cur->user->name, node->name) == 0) {
      return true;
    }
  }
  return false;
}

/**
 * Checks if a brand is inside a BrandNode LL.
 */
bool in_brand_list(BrandNode *head, char *name) {
  for (BrandNode *cur = head; cur != NULL; cur = cur->next) {
    if (strcmp(cur->brand_name, name) == 0) {
      return true;
    }
  }
  return false;
}

//Function to count how many friends this person has
bool count_in_friend_list(FriendNode *head)
{
    int i = 0;
    for (FriendNode *cur = head; cur != NULL; cur = cur->next)//Go through the LL untils its null and count i
    {
        i=i+1;
    }
    return i; //Return the count
}

// Count how many brands user has
int count_in_brand_list(BrandNode *head)
{
    int i = 0;
    for (BrandNode *cur = head; cur != NULL; cur = cur->next) //Go through LL untils its null
    {
        i=i+1;
    }
  return i; // retunr total count
}
/**
 * Inserts a User into a F\\ If the user
 * already exists, nothing is done. Returns the new head of the LL.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node) {
  if (node == NULL) return head;

  if (in_friend_list(head, node)) {
    printf("User already in list\n");
    return head;
  }
  FriendNode *fn = calloc(1, sizeof(FriendNode));
  fn->user = node;

  if (head == NULL)
    return fn;
if (strcasecmp(head->user->name,fn->user->name)>0) // Added one extra case of ordering root alphabetical
{
    fn->next = head;
    return fn;
}

  FriendNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
       cur = cur->next)
    ;
  fn->next = cur->next;
  cur->next = fn;
  return head;
}

/**
 * Inserts a brand into a BrandNode LL in sorted position. If the brand 
 * already exists, nothing is done. Returns the new head of the LL.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node) {
  if (node == NULL) return head;

  if (in_brand_list(head, node)) {
    printf("Brand already in list\n");
    return head;
  }
  BrandNode *fn = calloc(1, sizeof(BrandNode));
  strcpy(fn->brand_name, node);
  // fn->user = node;

  if (head == NULL)
    return fn;
    if (strcasecmp(head->brand_name,fn->brand_name)>0) // Added one extra case of ordering root alphabetical
    {
        fn->next = head;
        return fn;
    }
  BrandNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
       cur = cur->next)
    ;
  fn->next = cur->next;
  cur->next = fn;
  return head;
}

/**
 * Deletes a User from FriendNode LL. If the user doesn't exist, nothing is 
 * done. Returns the new head of the LL.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node) {
  if (node == NULL) return head;

  if (!in_friend_list(head, node)) {
    printf("User not in list\n");
    return head;
  }

  if (strcmp(head->user->name, node->name) == 0) {
    FriendNode *temp = head->next;
    free(head);
    return temp;
  }

  FriendNode *cur;
  for (cur = head; cur->next->user != node; cur = cur->next)
    ;

  FriendNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);
  return head;
}

/**
 * Deletes a brand from BrandNode LL. If the user doesn't exist, nothing is 
 * done. Returns the new head of the LL.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node) {
  if (node == NULL) return head;

  if (!in_brand_list(head, node)) {
    printf("Brand not in list\n");
    return head;
  }

  if (strcmp(head->brand_name, node) == 0) {
    BrandNode *temp = head->next;
    free(head);
    return temp;
  }

  BrandNode *cur;
  for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
    ;

  BrandNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);
  return head;
}

// Users
/**
 * Creates and returns a user. Returns NULL on failure.
 */
User* create_user(char* name)
{
    User *node = calloc(1,sizeof(User)); //Make space for the pointer
    if (node != NULL) // If it is NULL means memeory didn't allocate return the NUll
    {
        strcpy(node->name,name);
        node->friends = NULL;
        node->brands = NULL;
        node->visited = false;
        return node; // Else return the node
    }
    return NULL;
}

/**
 * Deletes a given user. Returns 0 on success, -1 on failure.
 */
int delete_user(User* user)
{
    // First Delete user's friend list and him from friends list
    while (user->friends != NULL)
    {
        user->friends->user->friends = delete_from_friend_list(user->friends->user->friends,user);
        user->friends = delete_from_friend_list(user->friends,user->friends->user);
    }
    // Delete users brands
    while (user->brands != NULL)
    {
        user->brands = delete_from_brand_list(user->brands,user->brands->brand_name);
    }
    //Free the user's space allocated
    free(user);
    user = NULL;
    if (user == NULL) // Null means it didn't free
    {
        return -1;
    }
    return 0;
}

/**
 * Create a friendship between user and friend.
 * Returns 0 on success, -1 on failure.
 */
int add_friend(User* user, User* friend)
{
    user->friends = insert_into_friend_list(user->friends,friend); // Adding friend in user's list
    friend->friends = insert_into_friend_list(friend->friends,user); // Adding user in friends's list
    //make temp varaible
    FriendNode* save_user = user->friends;
    FriendNode* save_friend = friend->friends;
    int count = 0;
    while (save_user != NULL)
    {
        if (strcmp(save_user->user->name,friend->name) == 0) //Check if friend is added in users friend list
        {
            count = count + 1;
            break;
        }
        save_user = save_user->next;
    }
    while (save_friend != NULL)
    {
        if (strcmp(save_friend->user->name,user->name) == 0) // check if user is added in friends' list
        {
            count = count + 1;
            break;
        }
        save_friend = save_friend->next;
    }
    if (count == 2) // if added then return 0
    {
        return 0;
    }
    return -1;
}

/**
 * Removes a friendship between user and friend.
 * Returns 0 on success, -1 on faliure.
 */
int remove_friend(User* user, User* friend)
{
    user->friends = delete_from_friend_list(user->friends,friend); //Remove friend from user's list
    friend->friends = delete_from_friend_list(friend->friends,user); //Remove user from friends's list
    //Make temp
    FriendNode* save_user = user->friends;
    FriendNode* save_friend = friend->friends;
    int count = 2;
    while (save_user != NULL)
    {
        if (strcmp(save_user->user->name,friend->name) == 0)//If friend is in users friend list that means it didn't work
        {
            count = count - 1;
            break;
        }
        save_user = save_user->next;
    }
    while (save_friend != NULL)
    {
        if (strcmp(save_friend->user->name,user->name) == 0) //If user is in friend list that means it didn't work
        {
            count = count - 1;
            break;
        }
        save_friend = save_friend->next;
    }
    if (count == 2)// If it is deleted from both then good return 0 else -1
    {
        return 0;
    }
    return -1;
}

/**
 * Creates a follow relationship, the user follows the brand.
 * Returns 0 on success, -1 on faliure.
 */
int follow_brand(User* user, char* brand_name)
{
    user->brands = insert_into_brand_list(user->brands,brand_name); // Add brands name to user's list
    //Make temp to save orginal node
    BrandNode *BrandsNodes = user->brands;
    while (BrandsNodes != NULL)
    {
        if (strcmp(BrandsNodes->brand_name,brand_name) == 0) //if brand is in it then we good return
        {
            return 0;
        }
        BrandsNodes = BrandsNodes->next;
    }
    return -1; //else its not return -1
}

/**
 * Removes a follow relationship, the user unfollows the brand.
 * Returns 0 on success, -1 on faliure.
 */
int unfollow_brand(User* user, char* brand_name)
{
    user->brands = delete_from_brand_list(user->brands,brand_name); //delete the brand of users list
    //make a temp
    BrandNode *BrandsNodes = user->brands;
    while (BrandsNodes != NULL)
    {
        if (strcmp(BrandsNodes->brand_name,brand_name) == 0) //if brand is still in it return -1
        {
            return -1;
        }
        BrandsNodes = BrandsNodes->next;
    }
    return 0; // else we good return 0
}

/**
 * A degree of connection is the number of steps it takes to get from one user
 * to another.
 * 
 * For example, if A & B are friends, then we expect to recieve 1 when calling
 * this on (A,B). Continuing on, if B & C are friends, then we expect to
 * recieve 2 when calling this on (A,C).
 * 
 * Returns a non-negative integer representing the degrees of connection
 * between two users, -1 on failure.
 */
int counter(User* a, User* b, int count)
{
    //base case if it is visited return 0;
    if (a->visited == true)
    {
        return 0;
    }
    //base case if it is in the count return the total count
    if (in_friend_list(a->friends,b))
    {
        return count;
    }
    else
    {
        a->visited = true; // mark visited as true
        for(FriendNode *p = a->friends; p!=NULL; p=p->next) //for each friend in user
        {
            for(FriendNode *p = a->friends; p!=NULL; p=p->next)//we need lease distance so check if friend is already in it
            {
                if (in_friend_list(p->user->friends,b)) //check the person we looking for is in other users fi\riend
                {
                    count = count + 1; //count 1
                    return count; //and return
                }
            }
            if (p->user->visited)
            {
                counter(p->user,b,count); //if user is already viisted we don't need to add count
            }
            else
            {
                count = count + 1;
                return counter(p->user,b,count); //if user is not viisted we need to add counter
            }
        }
    }
    return -1; //if we can't find the user jusr return -1
}
int get_degrees_of_connection(User* a, User* b)
{
    if (strcmp(a->name,b->name) == 0) // if same name is going to same then return 0
    {
        return 0;
    }
    else
    {
        return counter(a,b,1); //return the num
    }
}

/**
 * Prints out the user data.
 */
void print_user_data(User* user)
{
    printf("User: %s\n",user->name); //print the name
    FriendNode *p = user->friends; //temp node
    BrandNode *g = user->brands; //temp node
    while (p != NULL)
    {
        printf("Friend: %s\n",p->user->name); //print all of the friends
        p = p -> next;
    }
    while (g != NULL)
    {
        printf("Follows: %s\n",g->brand_name); //print all of the brands
        g = g -> next;
    }
}

// Brands
/**
 * Read from a given file and populate a brand matrix.
 * 
 */
void populate_brand_matrix(char* file_name) {
    // A buffer to hold the contents of a line (row) from the file.
    char buff[MAX_STR_LEN];
    // Opens a file f for reading.
    FILE* f = fopen(file_name, "r"); 
    // When this is called, it will load the next line of the file into buff
    for (int i=0; i<MAT_SIZE; i=i+1)
    {
        fscanf(f, "%s", buff);
        strcpy(brand_names[i],buff); //save each name in brandsnames from buff
    }
    for (int i=0; i<MAT_SIZE; i=i+1)
    {
        for (int j=0; j<MAT_SIZE; j=j+1)
        {
            fscanf(f, "%s", buff); // scan if it is 0 or 1
            brandAdjacencyMatrix[i][j] = atoi(buff); //save each 0/1 in brandAdjacencyMatrix as a int from string
        }
    }
}

/**
 * Marks two brands as similar.
 */
void connect_similar_brands(char* brandNameA, char* brandNameB)
{
    //traverse throguh the while MAT_SIZE
    for (int i=0; i<MAT_SIZE; i=i+1)
    {
        for(int j=0;j<MAT_SIZE;j=j+1)
        {
            if (strcmp(brand_names[i],brandNameA)==0 && strcmp(brand_names[j],brandNameB)==0)
            {
                brandAdjacencyMatrix[i][j] = 1; //find the name save it as 1 because we need to make them similar
            }
            if (strcmp(brand_names[i],brandNameB) ==0 && strcmp(brand_names[j],brandNameA) ==0)
            {
                brandAdjacencyMatrix[i][j] = 1; //find the name save it as 1 because we need to make them similar
            }
        }
    }
}

/**
 * Marks two brands as not similar.
 */
void remove_similar_brands(char* brandNameA, char* brandNameB)
{
    //traverse throguh the while MAT_SIZE
    for (int i=0; i<MAT_SIZE; i=i+1)
    {
        for(int j=0;j<MAT_SIZE;j=j+1)
        {
            if (strcmp(brand_names[i],brandNameA)==0 && strcmp(brand_names[j],brandNameB)==0)
            {
                brandAdjacencyMatrix[i][j] = 0; //find the name save it as 0 because we need to make them not similar
            }
            if (strcmp(brand_names[i],brandNameB) ==0 && strcmp(brand_names[j],brandNameA) ==0)
            {
                brandAdjacencyMatrix[i][j] = 0; //find the name save it as 0 because we need to make them not similar
            }
        }
    }
}

/**
 * Prints out the brand data.
 */
void print_brand_data(char* brand_name)
{
    printf("Brand: %s\n",brand_name); //print data name
    for (int i=0; i<MAT_SIZE; i=i+1)
    {
        if (strcmp(brand_names[i],brand_name)==0)
        {
            for(int j=0;j<MAT_SIZE;j=j+1)
            {
                if (brandAdjacencyMatrix[i][j] ==1)
                {
                    printf("Similar: %s\n",brand_names[j]); // If they are similar then print it
                }
            }
        }
    }
}

/**
 * Returns a suggested friend for the given user, returns NULL on failure.
 */

void visited(User* user) //Goes over the whole tree and make visited false
{
    if (user->visited == false) //base case of traverse
    {
        return;
    }
    user->visited = false; //make first = false
    for(FriendNode *p = user->friends; p!=NULL; p=p->next) //go through the whole frieends
    {
        visited(p->user); //recurrsive
    }
    return; //done
}
User* brands_make_friends(User* user,User* userr) //find a perfect fit for brands that will make it work
{
    if (user->visited == true) //base case
    {
        return user;
    }
    if (!in_friend_list(userr->friends,user) && strcmp(user->name,userr->name)!=0) //if user not in the list and its not the same name
    {
        BrandNode* temp = user->brands;
        BrandNode* temp2 = userr->brands;
        int j = 0;
        while (temp2 != NULL)
        {
            if (in_brand_list(temp,temp2->brand_name)) //count j = 1
            {
                j = j + 1;
            }
            temp2 = temp2->next; //go to next one
        }
        if (j>savedcount) //if j is less than count then make suggested firend  = user
        {
            saveduser = user;
            savedcount = j;
        }
        else if (j == savedcount && j!=0) //if there is a tie make saveduser same as input user
        {
            saveduser = userr;
        }
    }
    user->visited = true;
    for(FriendNode *p = user->friends; p!=NULL; p=p->next) //traverse
    {
        user = brands_make_friends(p->user,userr);
    }
    return saveduser;
}
User* friends_make_friends(User* user,User* userr)
{
    if (user->visited == true) //base case
    {
        return user;
    }
    if (!in_friend_list(userr->friends,user) && strcmp(user->name,userr->name)!=0) //check user is not userr firendlist and its not the same nane
    {
        FriendNode* temp = userr->friends;
        int j = 0;
        while (temp != NULL)
        {
            if (in_friend_list(user->friends,temp->user))
            {
                j = j + 1; //count j + 1
            }
            temp = temp->next;
        }
        if (j>savedcount) //if there is no tie save the user as suggested friend
        {
            saveduser = user;
            savedcount = j;
        }
        else if (j == savedcount && j!=0) // else reutnr same name
        {
            saveduser = userr;
        }
    }
    user->visited = true;
    for(FriendNode *p = user->friends; p!=NULL; p=p->next) //traverse thrugh the whole thing
    {
        user = friends_make_friends(p->user,userr);
    }
    return saveduser;
}
User* friends_find_friends(User* user,User* userr)
{
    if (user->visited == true) //base case
    {
        return user;
    }
    if (!in_friend_list(userr->friends,user) && strcmp(user->name,userr->name)!=0)
    {
        if (strcasecmp(user->name, saveduser->name)>0) //finding the last name ans saving it
        {
            saveduser = user;
        }
    }
    user->visited = true;
    for(FriendNode *p = user->friends; p!=NULL; p=p->next)
    {
        user = friends_find_friends(p->user,userr);
    }
    return saveduser; //returning the user
}
User* get_suggested_friend(User* user)
{
    saveduser = user;
    savedcount = 0;
    //making tenos
    User* p1 = user;
    User* p2 = user;
    User* p3 = user;
    visited(p1); //making whole node vsiited as false
    User* chosen_one = brands_make_friends(p1,p1);
    if(strcmp(chosen_one->name,user->name)!=0) //if brand is found
    {
        return chosen_one;
    }
    visited(p2); //making whole node vsiited as false
    chosen_one = friends_make_friends(p2,p2); //if friend if found from the whole thing
    if (strcmp(chosen_one->name,user->name)!=0)
    {
        return chosen_one;
    }
    visited(p3); //making whole node vsiited as false
    chosen_one = friends_find_friends(p3,p3);
    if (strcmp(chosen_one->name,user->name)!=0) //find somone with last name
    {
        return chosen_one;
    }
    visited(user); //making whole node as visited as false
    return NULL; //return null if found nothing
}

/**
 * Friends n suggested friends for the given user.. Returns 0 on success, -1 on failure.
 */
int add_suggested_friends(User* user, int n)
{
    int beforefriends = count_in_friend_list(user->friends); //save how many firends before
    int i = n;
    while (i!=0) //while i is not 0
    {
        FriendNode *node = insert_into_friend_list(user->friends,get_suggested_friend(user));
        if (node != NULL) //keep searching for friends and affing them
        {
            user->friends = node;
        }
        i = i-1;
    }
    if(count_in_friend_list(user->friends) > beforefriends) //if there are more friends we good
    {
        return 0;
    }
    return -1;
}

/**
 * Follows n suggested brands for the given user.  Returns 0 on success, -1 on failure.
 */
int follow_suggested_brands(User* user, int n)
{
    int beforefriends = count_in_brand_list(user->brands);
    int i = n;
    while (i!=0)
    {
        int count = 0;
        char savedfriend[MAX_STR_LEN];
        for (int i=0; i<MAT_SIZE; i=i+1)
        {
            if (in_brand_list(user->brands,brand_names[i])) //if brand is it
            {
                for (int j=0; j<MAT_SIZE; j=j+1)
                {
                    if (brandAdjacencyMatrix[i][j] == 1)
                    {
                        strcpy(savedfriend,brand_names[j]); //copy the whole name to savedfriend
                        count = count + 1;
                    }
                }
            }
        }
        if (count == 1) //if there no tie and only 1 brands we good
        {
            user->brands = insert_into_brand_list(user->brands,savedfriend);
        }
        else //else find with highest last name
        {
            strcpy(savedfriend,"NULL\0");
            for (int i=0; i<MAT_SIZE; i=i+1) //choose one brand
            {
                 if (!in_brand_list(user->brands,brand_names[i]))
                 {
                     strcpy(savedfriend,brand_names[i]);
                 }
            }
            for (int i=0; i<MAT_SIZE; i=i+1) //find any other brand
            {
                 if (!in_brand_list(user->brands,brand_names[i]) && strcasecmp(brand_names[i],savedfriend)>0)
                 {
                     strcpy(savedfriend,brand_names[i]);
                 }
            }
            if (strcmp("NULL", savedfriend) != 0) //if it is not null then we good
            {
                user->brands = insert_into_brand_list(user->brands,savedfriend);
            }
        }
        i = i-1;
    }
    if(count_in_brand_list(user->brands) > beforefriends) //if there are more brands than before we good
    {
        return 0;
    }
    return -1;
}
