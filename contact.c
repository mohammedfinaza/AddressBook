#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


//Function Declarations

void namecreate(AddressBook *addressBook,int count);
void numbercreate(AddressBook *addressBook,int count);
void mailcreate(AddressBook *addressBook,int count);

void namesearch(AddressBook *addressBook);
void numbersearch(AddressBook *addressBook);
void mailsearch(AddressBook *addressBook);

int namevalidate(char temp[]);
int numbervalidate(AddressBook *addressBook,char number[],int count);
int mailvalidate(AddressBook *addressBook,char mail[],int count);

int z=0;//global variable to pass the structure array index b/w various functions.


//MAIN FUNCTIONS


void listContacts(AddressBook *addressBook) //functions to print all the existing contacts in the FILE.
{
    int count=addressBook -> contactCount;
    printf("Name\t\t\tPhone\t\t\tMailaddress\n");
    for(int i=0;i < count;i++)
    {
      if(strlen(addressBook -> contacts[i].name)<=7)
      {
        printf("%s\t\t\t%s\t\t%s\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
      }
      else
      {
       printf("%s\t\t%s\t\t%s\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
          
      } 
    }
    
}




void initialize(AddressBook *addressBook)
{
  addressBook->contactCount = 0;
  //populateAddressBook(addressBook);
    
  // Load contacts from file during initialization
  loadContactsFromFile(addressBook);
}




void saveAndExit(AddressBook *addressBook)
{
  saveContactsToFile(addressBook); // Save contacts to file
  exit(EXIT_SUCCESS); // Exit the program
}





void createContact(AddressBook *addressBook)//function to create contact
{
    
    int count=addressBook -> contactCount;
    namecreate(addressBook,count);//function to create name
    numbercreate(addressBook,count);//func to create phone number
    mailcreate(addressBook,count);//func to create mail
    addressBook -> contactCount++;//incrementing contact count after creating the contact
    printf("\n\nCONTACT CREATED!!!\n");
}

void searchContact(AddressBook *addressBook) //search contact func
{
  int choice;
  
  //menu to choose by which option you want to search the contact
  do
  {
    printf("\nEnter by which option you want to access the contact:\n");
    printf("1.Name\n");
    printf("2.Phone no.\n");
    printf("3.Email\n");
    printf("Enter the choice: ");
    scanf("%d",&choice);
    getchar();

    switch(choice)
    {
      case 1:namesearch(addressBook);
      break;
      case 2:numbersearch(addressBook);
      break;
      case 3:mailsearch(addressBook);
      break;
      default:
      printf("Invalid choice.Try again!!!\n");       

    }

    
  } while (choice!=1 && choice!=2 && choice!=3 );

  
}





void editContact(AddressBook *addressBook)//edit contact func.
{
	int choice,choice1;
  
  do
  {
    printf("\nEnter by which option you want to access the contact :\n");
    printf("1.Name\n");
    printf("2.Phone no.\n");
    printf("3.Email\n");
    printf("Enter the choice: ");
    scanf("%d",&choice);
    getchar();


    switch(choice)
    {
      case 1:
      namesearch(addressBook);
      break;
      case 2:
      numbersearch(addressBook);
      break;
      case 3:
      mailsearch(addressBook);
      break;
      default:
      printf("Invalid option!!!");
    }
  } while (choice!=1 && choice!=2 && choice!=3);



  do
  {
    printf("\nEnter which option you want to edit :\n");
    printf("1.Name\n");
    printf("2.Phone no.\n");
    printf("3.Email\n");
    printf("Enter the choice: ");
    scanf("%d",&choice1);
    getchar();

    switch(choice1)
    {
      case 1:
      namecreate(addressBook,z);
      break;
      case 2:
      numbercreate(addressBook,z);
      break;
      case 3:
      mailcreate(addressBook,z);
      break;
      default:
      printf("Invalid option!!!");
    }
  } while (choice1!=1 && choice1!=2 && choice1!=3);

  printf("\nCONTACT EDITED SUCCESSFULLY!!!\n");

    
}



void deleteContact(AddressBook *addressBook)//delete contact func.
{
	printf("\nFor deleting the contact");
  searchContact(addressBook);
  int index=z;
  int count=addressBook -> contactCount;
  for (int i = index; i < count; i++) 
  {
    strcpy(addressBook->contacts[i].name, addressBook->contacts[i+1].name);
    strcpy(addressBook->contacts[i].phone, addressBook->contacts[i+1].phone);
    strcpy(addressBook->contacts[i].email, addressBook->contacts[i+1].email);
  }
  addressBook -> contactCount--;
  printf("\nContact Deleted!!!\n");
}





//VALIDATION FUNCTIONS

int namevalidate(char temp[])
{
  int len=strlen(temp);
  

  while(*temp!='\0')
  {
     if( (*temp >='a' && *temp<='z') || (*temp>='A' && *temp<='Z') || (*temp==' '))
     {
       temp++;
     }
     else
     {
       return 0;
     }
  }

  return 1;

}


int numbervalidate(AddressBook *addressBook,char number[],int count)
{
    int len=strlen(number);
    int i=0;

    
    while(*number!='\0')
    {
        if((*number>='0') && (*number<='9'))
        {
          
        }
        else
        {
          printf("Phone number should contain only digits!!!\n");
          return 0;
        }
      number++;
    }
    if(len<10)
    {
      printf("The phone number should contain 10 digits!!!\n");
      return 0;
    }
    else if(len>10)
    {
      printf("The phone number should not contain more 10 digits\n");
      return 0;
    }

    number=number-len;

    for(i=0;i<count;i++)
    {
      if(strcmp(number,addressBook -> contacts[i].phone)==0)
      {
        return 2;
      }
    }
    return 1;
}


int mailvalidate(AddressBook *addressBook,char mail[],int count)
{
    int count1=0;
    int count2=0;
    int len=strlen(mail);

    if( (*mail >='a' && *mail<='z') || (*mail>='A' && *mail<='Z') || (*mail>='0' && *mail<='9'))
    {
        mail++;
       while(*mail!='\0')
       { 
          if(*mail=='@')
          {
            mail++;
            if( (*mail >='a' && *mail<='z') || (*mail>='A' && *mail<='Z') || (*mail>='0' && *mail<='9'))
            {
              mail--;
              count1++;
            }
            else
            {
              return 0;
            }
          } 

          if(*mail=='.')
          {
            if(*(mail+1)=='c' && *(mail+2)=='o' && *(mail+3)=='m' && *(mail+4)=='\0')
            {
                count2++;
            }
            
          } 
          mail++;
       }

    mail=mail-len;
    for(int i=0;i<count;i++)
    {
      if(strcmp(mail,addressBook -> contacts[i].email)==0)
      {
        return 2;
      }
    }

    if(count1==1 && count2==1)
    {
       return 1;
    }
    else
    {
       return 0;
    }
    }
  else
  { 
      return 0;
  }

    
}





//CREATE FUNCTIONS


void namecreate(AddressBook *addressBook,int count)
{
   char temp[50];
   while (1)
    {
      printf("Enter the name to save: ");
      scanf(" %[^\n]",temp);

       if(namevalidate(temp)==1)
      {
        strcpy(addressBook -> contacts[count].name,temp);
        break;
      }
      else
      {
        printf("Enter a valid name!!!\n");
      }    
    }
	  
}



void numbercreate(AddressBook *addressBook,int count)
{
    char temp[50];
    while(1)
    {
       printf("Enter the phone number to save:");
       scanf("%s",temp);
       int a=numbervalidate(addressBook,temp,count);
    
       if(a==1)
      {
        strcpy(addressBook -> contacts[count].phone,temp);
        break;
      }
      else if(a==2)
      {
        printf("Number already exists!!!\n");
      }
      else
      {
        printf("Invalid Number!!!\n"); 
      }
    }
    
 }
    


void mailcreate(AddressBook *addressBook,int count)
{
  char temp[50];
  while(1)
  {
    printf("Enter the mailid to save: ");
    scanf(" %[^\n]",temp);
    int a=mailvalidate(addressBook,temp,count);
  
     if(a==1)
    {
      strcpy(addressBook -> contacts[count].email,temp);
      break;
    }
    else if(a==2)
    {
      printf("Mail already exists!!!\n");
    }
    else
    {
    printf("Invalid Mail id!!!\n");
    } 
    
  }
  
} 



//SEARCH FUNCTIONS

void namesearch(AddressBook *addressBook)
{


    char temp[50],no[50];
    int i,namecount=0,choice;
    
    int count=addressBook -> contactCount;
    while(namecount<1)
    {
       printf("Enter the name to search :");
       scanf(" %[^\n]",temp);
       
       if(namevalidate(temp)==1)
       {
          for(i=0;i<count;i++)
          {
          if(strcmp(temp,addressBook -> contacts[i].name)==0)
          {
            z=i;
            namecount++;
          }
          }
          
          if(namecount==0)
          {
            printf("Name doesn't exists!!!\n");
            return;
          }
       }
       else
       {
          printf("Please enter a valid name!!!\n");
       }
       
    }
    
      

    if(namecount>1)
    {
      printf("\nMultiple contact with same name exists.Please enter emailid or phone number also to access the contact\n");
      do
      {

        printf("\nEnter by which option you want to access the contact:\n");
        printf("1.Phone no.\n");
        printf("2.Email\n");
        printf("Enter the choice: ");
        scanf("%d",&choice);

       switch(choice)
      {
        
        case 1:numbersearch(addressBook);
        break;
        case 2:mailsearch(addressBook);
        break;
        default:
        printf("Invalid choice.Try again!!!\n");       

      } 
        
      } while (choice!=1 && choice!=2 );
      
    }
    else
    {
      printf("\nName\t\t\tPhone\t\t\tMailaddress\n");
      if(strlen(addressBook -> contacts[z].name)<=7)
      {
        printf("\n%s\t\t\t%s\t\t%s\n",addressBook -> contacts[z].name,addressBook -> contacts[z].phone,addressBook -> contacts[z].email);
      }
      else
      {
       printf("\n%s\t\t%s\t\t%s\n",addressBook -> contacts[z].name,addressBook -> contacts[z].phone,addressBook -> contacts[z].email);
          
      } 

    }

  

}


void numbersearch(AddressBook *addressBook)
{

    char temp[50],no[50];
    int i,phonecount=0;
    int index;
    int count=addressBook -> contactCount;
    while(phonecount<1)
    {
       printf("Enter the phone number to search :");
       scanf(" %[^\n]",temp);

      if(numbervalidate(addressBook,temp,count))
      {
        for(i=0;i<count;i++)
       {
          if(strcmp(temp,addressBook -> contacts[i].phone)==0)
          {
            index=i;
            phonecount++;
          }

       }
       if(phonecount==0)
       {
        printf("Number doesn't exist!!!!\n");
       }
       else
       {
         printf("\nName\t\t\tPhone\t\t\tMailaddress\n");
         if(strlen(addressBook -> contacts[index].name)<=7)
         {
           printf("\n%s\t\t\t%s\t\t%s\n",addressBook -> contacts[index].name,addressBook -> contacts[index].phone,addressBook -> contacts[index].email);
         }
         else
         {
           printf("\n%s\t\t%s\t\t%s\n",addressBook -> contacts[index].name,addressBook -> contacts[index].phone,addressBook -> contacts[index].email);
         }
         break;
       }

      }
       
    }
      
  z=index;    

}


void mailsearch(AddressBook *addressBook)
{

   char temp[50],no[50];
    int i,emailcount=0;
    int index;
    int count=addressBook -> contactCount;

    while(1)
    {
       printf("Enter the emailid :");
       scanf(" %[^\n]",temp);

       if(mailvalidate(addressBook,temp,count))
       {
       for(i=0;i<count;i++)
       {
          if(strcmp(temp,addressBook -> contacts[i].email)==0)
          {
            index=i;
            emailcount++;
          }

       }
       if(emailcount==0)
       {
        printf("Email Not Found\n");
        break;
       }
       else
       {
         printf("\nName\t\t\tPhone\t\t\tMailaddress\n");
         if(strlen(addressBook -> contacts[index].name)<=7)
         {
           printf("\n%s\t\t\t%s\t\t%s\n",addressBook -> contacts[index].name,addressBook -> contacts[index].phone,addressBook -> contacts[index].email);
         }
         else
         {
           printf("\n%s\t\t%s\t\t%s\n",addressBook -> contacts[index].name,addressBook -> contacts[index].phone,addressBook -> contacts[index].email);
         }
         break;

       }
       }
       else
       {
          printf("Invalid email.Enter valid emailid.\n");
       }

    }

    z=index;
      

}
