/*Documentation
Name:Mohammed Finaz A
Date:18/10/24
DES:Address Book
*/

#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialising the address book to get the existing contacts from the FILE.
    
    //Displaying the menu and calling the function according to the user i/p.
    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                return 0;
            case 7:
                return 0;    
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
