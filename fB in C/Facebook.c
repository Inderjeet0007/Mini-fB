#include<stdio.h>
#include<conio.h>

struct user
{
    int roll,friendcount;
    char name[30],password[20],question[20],answer[20];
    struct user * nextuser;
    struct friends * friendlist;
};

struct friends
{
    struct friends * nextfrnd;
    struct user * frnd;
};

struct user *first,*temp;

void login();
struct user * searchbyroll(int);
void registration();
void loggedin(struct user *);
void editprofile(struct user *);
void resetpassword(struct user *);
void searchusers(struct user *);
void friends(struct user *);
void addfriend(struct user *, struct user *);
void removefriend(struct user *,struct friends *);
struct friends * searchfriend(struct user *,struct user *);

void main()
{
    int choice;
    while(1)
    {
        system("cls");
        printf("Welcome to Facebook");
        printf("\n\n\n");
        printf("1.Login");
        printf("\n");
        printf("2.Register");
        printf("\n");
        printf("3.Exit");
        printf("\n\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        system("cls");
        switch(choice)
        {
            case 1:
                login();
                break;
            case 2:
                registration();
                break;
            case 3:
                return;
            default:
                printf("Invalid Input");
                getch();
        }
    }
}

void registration()
{
    struct user * ptr,* prev;
    int rollno;
    char choice;
    printf("Enter your unique Roll Number: ");
    scanf("%d",&rollno);
    if(searchbyroll(rollno)!=NULL)
    {
        printf("Roll Number %d already exists",rollno);
        return;
    }
    temp=(struct user *)malloc(sizeof(struct user));
    temp->roll=rollno;
    temp->nextuser=NULL;
    temp->friendlist=NULL;
    temp->friendcount=0;
    printf("Enter your password: ");
    scanf("%s",temp->password);
    fflush(stdin);
    printf("Enter your Name: ");
    fflush(stdin);
    scanf("%[^\n]",temp->name);
    printf("Enter a security question: ");
    fflush(stdin);
    scanf("%[^\n]",temp->question);
    printf("Enter security answer: ");
    fflush(stdin);
    scanf("%[^\n]",temp->answer);
    if(first!=NULL)
    {
        if(first->roll>rollno)
        {
            temp->nextuser=first->nextuser;
            first->nextuser=temp;
        }
        else
        {
            ptr=first;
            if(ptr->nextuser==NULL)
            {
                ptr->nextuser=temp;
                temp->nextuser=NULL;
            }
            else
            {
                while(ptr->nextuser!=NULL && ptr->roll<rollno)
                {
                    prev=ptr;
                    ptr=ptr->nextuser;
                }
                temp->nextuser=ptr;
                prev->nextuser=temp;
            }
        }
    }
    else
        first=temp;
    system("cls");
    printf("Registration Successful");
    printf("\n\n");
    printf("Do you want to Login now? (Y/N): ");
    fflush(stdin);
    scanf("%c",&choice);
    if(choice=='y' || choice=='Y')
        login();
}

void login()
{
    int rollno;
    char password[30],ch;
    system("cls");
    printf("Enter your Roll Number: ");
    scanf("%d",&rollno);
    if(first==NULL)
    {
        printf("User does not exists");
        return;
    }
    system("cls");
    temp=searchbyroll(rollno);
    if(temp!=NULL)
    {
        printf("Welcome %s",temp->name);
        printf("\n\n");
        printf("Enter your Password: ");
        scanf("%s",password);
        if(strcmp(password,temp->password)==0)
        {
            loggedin(temp);
        }
        else
        {
            printf("Incorrect Password");
            printf("\n\n");
            printf("Forgot Password? (Y/N): ");
            fflush(stdin);
            scanf("%c",&ch);
            if(ch=='y' || ch=='Y')
                resetpassword(temp);
        }
    }
    else
    {
        printf("User does not exists");
        return;
    }
}

void resetpassword(struct user *ptr)
{
    char answer[20];
    system("cls");
    printf("Security question: ");
    printf("\n\n");
    printf("%s",ptr->question);
    printf("\n");
    printf("Enter your Answer: ");
    fflush(stdin);
    scanf("%[^\n]",answer);
    if(strcmp(answer,ptr->answer)==0)
    {
        printf("Enter new Password: ");
        fflush(stdin);
        scanf("%[^\n]",ptr->password);
        system("cls");
        printf("Password changed successfully");
    }
    else
        printf("Incorrect Answer");
}

void loggedin(struct user *ptr)
{
    int ch;
    system("cls");
    printf("%s's Profile",ptr->name);
    printf("\n\n");
    while(1)
    {
        system("cls");
        printf("1.Edit Profile");
        printf("\n");
        printf("2.Friends (%d)",ptr->friendcount);
        printf("\n");
        printf("3.Search other users");
        printf("\n");
        printf("4.Logout");
        printf("\n");
        printf("5.Print all details");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        system("cls");
        switch(ch)
        {
            case 1:
                editprofile(ptr);
                break;
            case 2:
                friends(ptr);
                break;
            case 3:
                searchusers(ptr);
                break;
            case 4:
                return;
            case 5:
                printf("Roll Number: %d \n",ptr->roll);
                printf("Name: %s \n",ptr->name);
                printf("Password: %s \n",ptr->password);
                printf("Security Question : %s \n",ptr->question);
                printf("Security Answer: %s \n",ptr->answer);
                printf("Friend Count: %d ",ptr->friendcount);
                break;
            default:
                printf("Invalid Input");
        }
        getch();
    }
}

void editprofile(struct user * ptr)
{
    int ch;
    while(1)
    {
        printf("1.Edit Name");
        printf("\n");
        printf("2.Change Password");
        printf("\n");
        printf("3.Change Security question and answer");
        printf("\n");
        printf("4.Back");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("Enter new Name: ");
                scanf("%[^\n]",ptr->name);
                break;
            case 2:
                printf("Enter new Password: ");
                scanf("%[^\n]",ptr->password);
                break;
            case 3:
                printf("Enter your new security question: ");
                scanf("%[^\n]",ptr->question);
                printf("Enter your new security answer: ");
                scanf("%[^\n]",ptr->answer);
                break;
            case 4:
                return;
            default:
                printf("Invalid Input");
        }
        system("cls");
        if(ch==1 || ch ==2 || ch==3)
            printf("Data Updated Successfully");
        getch();
    }
}

void searchusers(struct user * ptr)
{
    char ch;
    int rollno;
    struct friends * tmp;
    struct user *tempuser;
    printf("Enter the roll number of the person to be searched: ");
    scanf("%d",&rollno);
    if(ptr->roll==rollno)
    {
        return;
    }
    tempuser=searchbyroll(rollno);
    system("cls");
    if(tempuser==NULL)
    {
        printf("Roll no %d does not exists",rollno);
        return;
    }
    while(1)
    {
        system("cls");
        printf("%s's Profile",tempuser->name);
        printf("\n\n");
        printf("Roll Number: %d",tempuser->roll);
        printf("\n");
        printf("Name: %s",tempuser->name);
        printf("\n");
        tmp=searchfriend(tempuser,ptr);
        if(tmp==NULL)
        {
            printf("Add Friend? (Y/N): ");
            fflush(stdin);
            scanf("%c",&ch);
            if(ch=='y' || ch=='Y')
            {
                addfriend(ptr,tempuser);
                system("cls");
                ptr->friendcount++;
                printf("%s Added to Friend List Successfully",tempuser->name);
                getch();
            }
            else
                return;
        }
        else
        {
            printf("Remove Friend? (Y/N): ");
            fflush(stdin);
            scanf("%c",&ch);
            if(ch=='y' || ch=='Y')
            {
                removefriend(ptr,tmp);
                ptr->friendcount--;
                system("cls");
                printf("%s Removed from Friend List Successfully",tempuser->name);
                getch();
            }
            else
                return;
        }
    }
}

void addfriend(struct user *ptr, struct user *tmp)
{
    struct friends * tempfrnd,* temp2,* prevfrnd;
    tempfrnd=ptr->friendlist;
    if(tempfrnd==NULL)
    {
        ptr->friendlist=(struct friends *)malloc(sizeof(struct friends));
        ptr->friendlist->nextfrnd=NULL;
        ptr->friendlist->frnd=tmp;
    }
    else
    {
        temp2=(struct friends *)malloc(sizeof(struct friends));
        temp2->frnd=tmp;
        if(tempfrnd->frnd->roll>temp2->frnd->roll)
        {
            temp2->nextfrnd=tempfrnd->nextfrnd;
            ptr->friendlist=temp2;
        }
        else
        {
            while(tempfrnd->nextfrnd!=NULL && tempfrnd->frnd->roll<tmp->roll)
            {
                prevfrnd=tempfrnd;
                tempfrnd=tempfrnd->nextfrnd;
            }
            temp2->nextfrnd=tempfrnd;
            prevfrnd->nextfrnd=temp2;
        }
    }
}

void removefriend(struct user *ptr, struct friends *tmp)
{
    struct friends *tmp2;
    if(ptr->friendlist->nextfrnd==NULL)
    {
        ptr->friendlist=NULL;
        free(tmp);
        return;
    }
    tmp2=ptr->friendlist;
    while(tmp2->nextfrnd!=tmp)
        tmp2=tmp2->nextfrnd;
    tmp2->nextfrnd=tmp->nextfrnd;
    tmp->nextfrnd=NULL;
    tmp->frnd=NULL;
    free(tmp);
}

void friends(struct user * ptr)
{
    int choice;
    struct friends * tmp;
    int i=0,count=1;
    if(ptr->friendlist==NULL)
    {
        printf("No Friends");
        return;
    }
    tmp=ptr->friendlist;
    while(tmp!=NULL)
    {
        i++;
        printf("\n");
        printf("%d. (%d) %s",i,tmp->frnd->roll,tmp->frnd->name);
        tmp=tmp->nextfrnd;
    }
    getch();
}

struct friends * searchfriend(struct user * tempuser,struct user *ptr)
{
    struct friends *tmp;
    tmp=ptr->friendlist;
    if(tmp==NULL)
        return NULL;
    while(tmp->nextfrnd!=NULL && tmp->frnd!=tempuser)
        tmp=tmp->nextfrnd;
    if(tmp->frnd==tempuser)
        return tmp;
    return NULL;
}

struct user * searchbyroll(int x)
{
    struct user *tmp;
    if(first==NULL)
        return NULL;
    tmp=first;
    while(tmp->nextuser!=NULL && x!=tmp->roll)
        tmp=tmp->nextuser;
    if(x==tmp->roll)
        return tmp;
    return NULL;
}
