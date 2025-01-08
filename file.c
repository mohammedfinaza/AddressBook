#include <stdio.h>
#include <string.h>
#include "file.h"

FILE *fp;

void saveContactsToFile(AddressBook *addressBook) //function to save the contants from the structure to the file
{
  fp=fopen("contacts.csv","w");
  if(fp==NULL)
  {
    perror("ERROR");
    return;
  }
  int count=addressBook->contactCount;
  fprintf(fp,"%d",count);
  fprintf(fp,"\n");

  for(int i=0;i<count;i++)
  {
    fprintf(fp,"%s",addressBook -> contacts[i].name);
    fprintf(fp,",");
    fprintf(fp,"%s",addressBook -> contacts[i].phone);
    fprintf(fp,",");
    fprintf(fp,"%s",addressBook -> contacts[i].email);
    fprintf(fp,"\n");
  }
  fclose(fp);
  
}



void loadContactsFromFile(AddressBook *addressBook)//function to load the contacts save in the file to the structure on program execution
{
  fp=fopen("contacts.csv","r");
  if(fp==NULL)
  {
    perror("ERROR");
    return;
  }
  
  fscanf(fp,"%d",&(addressBook->contactCount));
  
  for(int i=0;i<addressBook->contactCount;i++)
  {
    fscanf(fp," %[^,],",addressBook -> contacts[i].name);
    fscanf(fp," %[^,],",addressBook -> contacts[i].phone);
    fscanf(fp," %[^\n]\n",addressBook -> contacts[i].email);
  }
  
  fclose(fp);
}
 


