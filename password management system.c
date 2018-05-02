#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>
struct tree
{
char web[500];
char userid[500];
char password[100];
struct tree *left;
struct tree *right;
}*root=NULL;

struct stat{
 int data;
 char web[500];
 struct stat *next;
}*head=NULL;
int key;
int count=0;
int number=0;
int delNum=0;

void display_stat(struct stat *head)
{
 while(head->next!=NULL)
 {
     printf("\nYou have %d ID of %s\n",head->data,head->web);
     head=head->next;

 }
  printf("\nYou have %d ID of %s\n",head->data,head->web);
}
void statistic_linklist(struct tree *root,struct stat **head)
{
   int found=0;
   struct stat *temp=NULL;

   struct stat *newnode=(struct stat*)malloc(sizeof(struct stat));
   strcpy(newnode->web,root->web);
   newnode->data=1;
   newnode->next=NULL;

    if(*head==NULL)
    {
        *head=newnode;
    }

    else
    {
        temp=*head;
        while(temp->next!=NULL)
        {
            if(strcmp(root->web,temp->web)==0)
            {
                temp->data=temp->data+1;
                found=1;

                break;
            }
            else{
                temp=temp->next;
            }
        }
        if(strcmp(root->web,temp->web)==0)
            {
                temp->data=temp->data+1;
                found=1;

            }
        if(temp->next==NULL && found==0)
        {
            temp->next=newnode;

        }

    }
}
void statistic_binary(struct tree *root)
{
    if(root!=NULL)
    {

        statistic_binary(root->left);
        printf("\n%s\n",root->web);
        statistic_linklist(root,&head);
        statistic_binary(root->right);

    }
}
void insert(struct tree **root,char web[],char userid[],char password[])
{
    struct tree *newnode=(struct tree*)malloc(sizeof(struct tree));
    strlwr(web);
    strcpy(newnode->web,web);
    strcpy(newnode->userid,userid);
    strcpy(newnode->password,password);
    newnode->left=NULL;
    newnode->right=NULL;
    if(*root==NULL)
       {

       *root=newnode;
       }
     else
     {
         if (strcmp((*root)->web,newnode->web)>0)
                insert(&(*root)->left,web,userid,password);
    else if (strcmp((*root)->web,newnode->web)<=0)
         insert(&(*root)->right,web,userid,password);
     }



}
void count_data(struct tree *root)
{
    if(root!=NULL)
    {
    count_data(root->left);
    number=number+1;
    count_data(root->right);
    }
}
void update(struct tree *root,char web[500],char userid[500],char password1[100])
{
 struct tree x;
 int n,i;
 char duplicate[100];
 FILE *new1;
    if (root != NULL)
    {
        update(root->left,web,userid,password1);
        new1=fopen("new","ab");

        strcpy(x.web,root->web);
        strcpy(x.userid,root->userid);
        x.left=root->left;
        x.right=root->right;
        if(strcmp(root->web,web)==0 && strcmp(root->userid,userid)==0)
         {
             n=strlen(password1);
             for(i=0;i<n;i++)
             {
                 password1[i]=password1[i]+key;
             }
             strcpy(x.password,password1);
             fwrite(&x,sizeof(x),1,new1);
             printf("\nPassword Updated !!");
        fclose(new1);
         }
         else
         {
             n=strlen(root->password);
             strcpy(duplicate,root->password);
             for(i=0;i<n;i++)
             {
                 duplicate[i]=duplicate[i]+key;
             }
             strcpy(x.password,duplicate);
             fwrite(&x,sizeof(x),1,new1);
             fclose(new1);
         }

        update(root->right,web,userid,password1);
    }

}


void delete_entry(struct tree *root,char web[500],char userid[500])
{
     char duplicate[100];
     int n,i;
     struct tree x;

    FILE *new1;
    if (root != NULL)
    {
        delete_entry(root->left,web,userid);
        if(strcmp(root->web,web)!=0 || strcmp(root->userid,userid)!=0)
        {

        new1=fopen("new","ab");
        strcpy(x.web,root->web);
        strcpy(x.userid,root->userid);
        n=strlen(root->password);
        strcpy(duplicate,root->password);
        for(i=0;i<n;i++)
        {
            duplicate[i]=duplicate[i]+key;

        }
        strcpy(x.password,duplicate);
        x.left=root->left;
        x.right=root->right;
       // printf(" YY  %s",root->web);
        fwrite(&x,sizeof(x),1,new1);
        fclose(new1);
        delNum=delNum+1;
        }
        else if(strcmp(root->web,web)==0 && strcmp(root->userid,userid)==0)
        {
            printf("\n!!!Entry successfully deleted!!!");
            delNum=-1;
        }
        delete_entry(root->right,web,userid);
    }


}

void search_entry(struct tree *root,char web[500],char userid[500])
{
     //FILE *new1;
    if (root != NULL)
    {
        search_entry(root->left,web,userid);
        delNum=delNum+1;
        if(strcmp(root->web,web)==0 && strcmp(root->userid,userid)==0)
        {
            printf("Your password is %s",root->password);
            count++;
            delNum=-1;
        }
        search_entry(root->right,web,userid);
    }
}

void inorder(struct tree *root)
{   int n,i;
     struct tree x;

   char duplicate[100]; //To store encrypted password
    FILE *new1;
    if (root != NULL)
    {
        inorder(root->left);
        new1=fopen("new","ab");
        n=strlen(root->password);
        strcpy(duplicate,root->password);
        for(i=0;i<n;i++)
        {
            duplicate[i]=duplicate[i]+key;         // Encryption

        }
       // printf("%s \n",duplicate);
        strcpy(x.web,root->web);
        //printf("%s \n",x.web);
        strcpy(x.userid,root->userid);
        strcpy(x.password,duplicate);
        x.left=root->left;
        x.right=root->right;
        fwrite(&x,sizeof(x),1,new1);
        fclose(new1);
        inorder(root->right);
    }
}

void getdata()
{
    struct tree x;
    char password1[100];
    int len,i;
    FILE *p;
    p=fopen("new","rb");
    if(p==NULL)
    {

     return;
    }
    else
    {
        while(fread(&x,sizeof(x),1,p)>0)
        {

            len=strlen(x.password);
            strcpy(password1,x.password);
            for(i=0;i<len;i++)
            {
               password1[i]=password1[i]-key;  //Decryption
            }
            //printf("%s %s %s \n",x.web,x.userid,password1);
           insert(&root,x.web,x.userid,password1);
        }

    }
    fclose(p);
}


void initialise_insert()
{
int i,n ;
FILE *p;
char web[100];
char userid[500];
char password[100];
    printf("\n Please enter the number of data that you wish to input - ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("\n Enter website name , userID, Password respectively !- ");
        scanf("%s %s %s",&web,&userid,&password);
        strlwr(web);
        search_entry(root , web ,password);
        if(count==1)
        {
            count=0;
            printf("\n Account with the same UserID in the website already exists \n Update the details:- ");
            printf("\n Enter website name , userID, Password respectively !- ");
            scanf("%s %s %s",&web,&userid,&password);
            strlwr(web);
        }
        insert(&root,web,userid,password);
        printf("One data successfully added !!\n");
    }
    p=fopen("new","wb");
    fclose(p);
    inorder(root);
    printf("All your data successfully added!!\n");


}



int main()
{
    FILE *p;
char web[100];
char userid[500];
char password[100];
FILE *fp;  //Password
int pin,pin1,n1,o=1 , ctr=1;
fp=fopen("pass","rb");
if(fp==NULL)
{
    printf("\n!!!               Welcome to PSAFE ,a platform where you can save and protect your website passwords       !!!!");
    printf("\n\nPlease enter the 4 digit NUMERIC pin for the software - ");
    while(1)
    {

    scanf("%d",&pin);
    if((pin/10000)>0)
    {
        printf("\nPlease enter the 4 NUMERIC digit pin - ");
    }
    else
    {

    printf(" \n!!!Password saved successfully!!!\n");
    fclose(fp);
    fp=fopen("pass","wb");
    fwrite(&pin,sizeof(pin),1,fp);
    fclose(fp);
    break;
    }
    }
}
    fp = fopen("pass","rb");
    system("cls");
    printf("\nPlease enter the PIN \n");//Valid Pin Check
    scanf("%d",&pin);
    fp=fopen("pass","rb");
    fread(&pin1,sizeof(pin1),1,fp);
    ctr++;
    while(ctr<=3)
    {
       if(pin!=pin1)
       {
         printf("\n You have entered the wrong pin, Re-Enter the pin:- ");
         scanf("%d",&pin);
          ctr++;
       }
       else
         break;
      }



    if(pin==pin1)
        {
            fclose(fp);
            system("cls");
            printf("                                 Welcome To your Account User   !!!   \n \n          ");
            key=(pin%100); //Key For Encryption

           while(o==1) //To Continue
           {
              printf("\n\n1. For insertion new entries \n2. For deletion of an entry \n3. To update an entry \n4. To search a password \n5. To See the statistics of accounts you have\n6.To EXIT the program\n");
              printf("Please enter the number accordingly \n");
              scanf("%d",&n1);
              switch(n1)
              {
                  case 1:
                 if(root==NULL)
                 {
                     getdata();
                 }
                 initialise_insert();
                  break;
                 case 3:
                     system("cls");
                      if(root==NULL)
                      {
                        getdata();
                      }

                    p=fopen("new","wb");
                    fclose(p);
                      printf("\nEnter the website name , userID  and New Password respectively !!!");
                      scanf("%s %s %s",&web,&userid,&password);
                      strlwr(web);
                      update(root,web,userid,password);
                      root=NULL;
                      getdata();

                  break;
                  case 2:
                  system("cls");
                  if(root==NULL)
                  {
                      getdata();
                  }

                  p=fopen("new","wb");
                  fclose(p);
                  printf("\nEnter the website name and userID respectively!!");
                  scanf("%s %s",&web,&userid);
                  strlwr(web);
                  delNum=number=0;
                  count_data(root);
                  delete_entry(root,web,userid);
                  if(delNum==number)
                  {
                      printf("\n!!!NO data found to be deleted!!!\n");
                  }
                  root=NULL;
                  getdata();
                  break;
                  case 4:
                  system("cls");
                  //count=0;
                  if(root==NULL)
                  {
                      getdata();
                  }
                  printf("\nEnter the website name and userID respectively!!");
                  scanf("%s %s",&web,&userid);
                  strlwr(web);
                  delNum=number=0;
                  count_data(root);
                  search_entry(root,web,userid);
                  if(delNum==number)
                  {
                      printf("\n!!!NO data found!!!\n");
                  }
                  break;
                  case 5:
                      if(root==NULL)
                  {
                      getdata();
                  }
                  if(root==NULL)
                  {
                      printf("\nPlease enter some data to view Stats\n");
                  }
                  else
                  {

                  head=NULL;
                  statistic_binary(root);
                  display_stat(head);
                  }
                  break;
                  case 6:o=0;
                  printf("\nWe will meet soon !!!\n");
                  exit(0);
                  break;
                  default:printf("\nOOPS !! Please enter a valid argument!!\n");

              }
           }

        }
        }

