#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*  Author: Alp Bintuğ Uzun
    Tested on Windows 10 (x64) with Code::Blocks 17.12 using GNU GCC Compiler.
    Used data structure: Binary Tree.
    The function which fixes the structure of binary tree is not written because it requires more resources than searching on a not-full binary tree.
    Examples of corrupted binary tree:
    If user enters increasing (or decreasing) numbers as ID, binary tree structure corrupts. Researach time increases to N from LogN.
        ID Samples= {1,3,5,11,96,152,310...}, {...,78,56,43,32,11,3,1}
        Sample tree=
                    1                   |              78
                      \                 |             /
                        3               |           56
                          \             |          /
                            5           |        43
                              \         |       /
                                11...   |     32...

    If user enters IDs between two values and each ID gets closser to the other value each time user enters an ID, binary tree structure corrupts.
        ID Samples= {78,1,64,14,61,17,57...}
        Sample tree=
                                78
                               /
                              1
                                \
                                 64
                                /
                               14...

    Circumstances declared at topper senction increases the research time to N.
    */
struct user{
    int ID;
    char name[50];
    char friends[500];
    struct user *right;
    struct user *left;
};
//Finds the user who has the given ID on the given tree(or sub tree).
struct user* findUser(struct user *root,int ID){
    while(root->ID!=ID&&root!=NULL){
        if(ID>root->ID)
            root=root->right;
        else
            root=root->left;
    }
    return root;
}
//Prints out given users' info.
void printUser(struct user *root){
    if (root!=NULL)
        printf("ID: %d, User name: %s\n", root->ID, root->name);
    }
//Checks if given tree(or sub tree) consists the given user.
char* contains(struct user *root, int ID){
    if(root==NULL || root->ID==ID){
        if(root==NULL)
        printf("Can't find the user with ID:%d\n",ID);
        else
        printf("%s\n",root->name);
    }
    else if(ID>root->ID){
        printf("Comparison: %d, ID: %d, ID > Comparison, going right\n",root->ID,ID);
        printf("%s\n",contains(root->right,ID));
    }
    else{
        printf("Comparison: %d, ID: %d, ID < Comparison, going left\n",root->ID,ID);
        printf("%s\n",contains(root->left,ID));
    }
    return NULL;
}
//Returns the left-most element of the tree(or sub tree). Used in another function.
struct user* findMin(struct user *root){
    while(root->left!= NULL){
            root=root->left;}
    return root;
}
//Creates new user with given information.
struct user* newUser(int ID, char name[], char frndLst[]){
    printf("Creating new user...\n");
    struct user *p;
    p = (struct user*)malloc(sizeof(struct user));
    p->ID = ID;
    p->left= NULL;
    p->right= NULL;
    strcpy(p->friends,frndLst);
    strcpy(p->name,name);
    printf("User created.\n");
    return p;
}
/*Adds the given user to the right place of the given tree(or sub tree)
When using Input.txt to import user info, blank lines make program tries to add the same user.
But you can't add user with same ID on the tree so it gives an error.
No further solutions are developed for this.*/
struct user* insertNewUser(struct user *root, struct user *add){
    if(root == NULL)
        root=add;
    else if(add->ID>root->ID)
        root->right = insertNewUser(root->right, add);
    else if(add->ID<root->ID)
        root->left = insertNewUser(root->left,add);
    else
        //If an user already has the same ID, new user wont bee added to the tree.
        printf("Can't add the user. Given ID already exists in the tree!\n");
    return root;
}
//Deletes the user with given ID from the given tree(or sub tree).
struct user* deleteUser(struct user *root, int ID){
    if(root==NULL)
        return NULL;
    if (ID>root->ID) //Searches the user unitill it finds, or tree ends. Goes to right-subtree.
        root->right= deleteUser(root->right, ID);
    else if(ID<root->ID) //Goes to left-subtree
        root->left = deleteUser(root->left, ID);
    else  //Entering else branch means that user is found and removes the found user.
    {   //If there is no child, just freeing the root will remove the user.
        if(root->left==NULL && root->right==NULL){
            free(root);
            root=NULL;
            return NULL;
        }
        //If there is atleast one child, checks for necessary shift opertions.
        else if(root->left==NULL || root->right==NULL){
            struct user *dummy; //Declared to return the necessary value when the root is removed.
            if(root->left==NULL)
                dummy = root->right;
            else
                dummy = root->left;
            free(root);
            root=NULL;
            return dummy;
        }
        else{ //Makes one of the child go for the place of the deleted user, so the tree structure is protected.
            struct user *dummy = findMin(root->right);
            root->ID = dummy->ID;
            strcpy(root->friends,dummy->friends);
            strcpy(root->name,dummy->name);
            root->right = deleteUser(root->right, dummy->ID);
        }
    }
    return root;
}
    //Prints the tree in left-node-right order, which prints it in increasing ID order.
void printInOrder(struct user *root){
    if(root!=NULL){
        printInOrder(root->left); //Goes for the left-most element of the tree
        printUser(root); //Prints root next
        printInOrder(root->right); //Prints right last
    }
}
    //Prints the subtree of given user (User itself is not included).
void printNext(struct user *root,int ID){
    printf("Printing the subtree of the user with the ID:%d\nUser: ",ID);
    contains(root,ID);
    root=findUser(root,ID); //Finds the given user.
    printf("Left subtree:\n");
    printInOrder(root->left); //Prints the left subtree in order(left-node-right).
    printf("Right subtree:\n");
    printInOrder(root->right); //Prints the right subtree in order(left-node-right).
}
    //Returns the number of the users in the tree.
int size(struct user *root){
    int s=0; //Holds the size.
    if(root!=NULL){
        s++;
        s+=size(root->left);
        s+=size(root->right);
    }
    return s;
}
    //Prints user who has greater ID than given ID.
void printGreater(struct user *root,int ID){
    if(root!=NULL){
    if(root->ID>ID){
        printInOrder(root->right);
        printUser(root);
        printGreater(root->left,ID);
    }
    else
    printGreater(root->right,ID);
}
}
    //Prints friends of the user with given ID.
void friends(struct user *root, int ID){
    struct user *dummy;
    dummy = (struct user *)malloc(sizeof(struct user));
    dummy=findUser(root,ID); //Finds the user with given ID.
    printf("Finding the friends of the user with Name: %s, ID: %d ID\n",dummy->name,dummy->ID);
    int i=0;
    //User friendlist is kept as a string, so we have to find numbers and convert them to integer.
    while((dummy->friends[i]>=48&&dummy->friends[i]<=57)||dummy->friends[i]=='-'){//Checks if the current character have number value in ASCII table
        int j=0;
        char a[10];
        for(int q=0;q<10;q++)
            a[q]=0;
        while(dummy->friends[i]>=48&&dummy->friends[i]<=57){
            a[j]=dummy->friends[i];
            j++;
            i++;
        }
        i++;
        printf("%s\n",findUser(root,atoi(a))->name);
        /*Atoi function converts the String a to integer ID,then we find this user with its ID, and then print it.*/
    }
    printf("Friends found.\n");
}
struct user * insertUserFromFile(struct user *root, FILE *fp){
    char friends[500];
    char name[50];
    char row[560]; //Keeps the row read from the file
    char id[10];//Keeps the ID read from the file. Its converted to integer value later.
    int q; //Index variable

            /*Making sure that there is no unreadable ASCII characters in the strings which will effect our functions*/
                for (q=0;q<500;q++){
                            friends[q]=0;
                        }
                for(q=0;q<50;q++){
                            name[q]=0;
                        }
                for(q=0;q<10;q++){
                            id[q]=0;
                        }
                fscanf(fp,"%[^\n]s",&row);//Reading from the file unitill a newline character appears.
                printf("Data of the new user: %s\n",row);
                int i=0;
                int j=0;
                while(row[i]<=47||row[i]>=58){ //Skipping the unreadable ASCII characters appear in the beggining of the file.
                        i++;
                }
                while(row[i]>47&&row[i]<58){ //Copying the ID value unitill current character has a number value in ASCII table.
                        id[j]=row[i];
                        i++;
                        j++;
                }
                i++; //Skipping ','.
                j=0;
                while((row[i]!=',')&&row[i]!=NULL){ //Checks if friendlist is empty (if empty there will be no ',' char) and reads the name.
                        name[j]=row[i];
                        i++;
                        j++;
                }
                i++;
                j=0;
                while((row[i]>47&&row[i]<58)||row[i]=='-'){//Reading the friendlist.
                        friends[j]=row[i];
                        i++;
                        j++;
                }
                if(root==NULL)//If there is no existing tree, we can't use insert user function, that function requires a existing tree.
                root=newUser(atoi(id),name,friends);//Creating new tree if no tree exists
                else
                insertNewUser(root,newUser(atoi(id),name,friends));//If a tree is existing, adding the new user to that tree.
                fgetc(fp); //Skipping the newline character at the end of the line (\n).
                return root;
}
int main(){
   int exit=0;//Checks if program user wants to quit or not.
   struct user *root;
   root = (struct user*)malloc(sizeof(struct user));
   root = NULL;
   FILE *fp;
   fp=fopen("Input.txt","r");
   fseek(fp,0,SEEK_SET);
    while (exit==0){
        int process;
        //Printing out the user menu
        printf("Select a process\n1-Add user\n2-Delete user\n3-Check user\n4-Find friends\n5-Number of users\n6-Print out user subtree\n7-Print users with greater ID\n8-Print in order\n\n0-Exit\n");
        scanf("%d",&process);
        if(process==1){
                int process2;
            printf("Press 1 to add user from console, Press 2 to add user from file, make sure that you have users in \n");
            scanf("%d",&process2);
            if(process2==1){
                int no;
                char name[50];
                char friendList[500];
                printf("Enter user ID\n");
                scanf("%d",&no);
                printf("Enter user name\n");
                getchar();
                scanf("%[^\n]s",&name);
                printf("Enter friends of the user. Set friends apart with '-' symbol, Dont use space (' ').\nIf user has no friends only write '-'. Example: 11-4-5-6-15\n");
                scanf("%s",&friendList);
                if(root==NULL)
                /*Can't use insertNewUser function if there is no existing tree.
                insertNewUser is used to insert a new user to an existing, non-empty tree.
                So, we call newUser function to create a root and a tree*/
                    root=newUser(no,name,friendList);
                else
                insertNewUser(root, newUser(no,name,friendList));
            }
            else if(process2==2){
                if(fp==NULL)
                printf("Can't open Input.txt file");
                else{
                printf("Make sure that user data is correctly written in Input.txt.\nCorrect format: ID,name,friendList\nExample:17,Alp Bintug Uzun,16-1-17\nPress 1 to add all the users in the file, Press 2 to add the next user in the file\n");
                scanf("%d",&process2);
                if(process2==1){
                    while(!feof(fp)){//Calling the insertUserFromFile function unitill the end of the file.
                        root=insertUserFromFile(root,fp);
                    }
                }
                else{ //Calling insertUserFromFile function only once to add the next user.
                       root=insertUserFromFile(root,fp);
                }
                }
            }
        }
        else if(process==2){
            int no;
            printf("Enter the ID of user you wish to remove\n");
            scanf("%d",&no);
            root=deleteUser(root,no);
        }
        else if(process==3){
            int no;
            printf("Enter the ID of the user you wish to check if it exists in the tree.\n");
            scanf("%d",&no);
            contains(root,no);
        }
        else if(process==4){
            int no;
            printf("Enter the ID of the user you wish to find friends of.\n");
            scanf("%d",&no);
            friends(root,no);
        }
        else if(process==5){
            printf("There is %d users in the tree.\n",size(root));
        }
        else if(process==6){
                int no;
            printf("Enter the ID of the user you wish to print the subtree of.\n");
            scanf("%d",&no);
            printNext(root,no);
        }
        else if(process==7){
            int no;
            printf("Enter the ID to find users with greater ID than this\n");
            scanf("%d",&no);
            printGreater(root,no);
        }
        else if(process==8){
            printf("Printing in order\n");
            printInOrder(root);
            printf("Process completed\n");
        }
        else {
            exit=1;
        }
        printf("\n");
    }
    fclose(fp);
}
