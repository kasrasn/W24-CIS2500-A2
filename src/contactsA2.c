/*
Student Name: Kasra Sina
Student ID: 1266859
Due Date: March 8, 2024
Course: CIS*2500
I have exclusive control over this submission via my password.
By including this header comment, I certify that:
1) I have read and understood the policy on academic integrity.
2) I have completed Moodle's module on academic integrity.
3) I have achieved at least 80% on the academic integrity quiz
I assert that this work is my own. I have appropriate acknowledged
any and all material that I have used, be it directly quoted or
paraphrased. Furthermore, I certify that this assignment was written
by me in its entirety.
*/

#include "../include/givenA2.h"

int main(int argc, char *argv[]){ //get argument from command line
    if (argc != 2)// check for two arguments
    {
        printf("fault in arguments\n");
        return 1;
    }
    
    // ask user for new contact
    while (1)
    {
        printf("Do you wish to enter a new contact? (Yes or No)\n");

        // allocate memory for the answer
        char * answer = malloc(sizeof(char)*10);
        scanf("%s", answer);

        //check if the user wants to enter a new contact and validate the input
        if (strcmp(answer, "Yes") == 0) // if yes call createContacts
        {
            createContacts(argv[1]);
        }
        else if (strcmp(answer, "No") == 0) // if no break 
        {
            break;
        }
        else // if invalid input
        {
            printf("invalid input, try again('Yes' or 'No')\n");
        }
    }

    // the menu
    while (1)
    {   // print the menu
        printf("choose one option:\n");
        printf(" 1 to read all contacts and print them in the same sequence they were created\n");
        printf(" 2 to search the file for a given employee id\n");
        printf(" 3 to add more contacts\n");
        printf("-1 to exit\n");

        // get the user's choice
        int option;
        scanf("%d", &option);

        // perform the action based on the user's choice
        switch (option)
        {
        case 1:// read all contacts
            readContacts(argv[1]); // call readContacts
            break;

        case 2: // search for a contact
            int id;

            while (1) // validate the input
            {
                printf("enter the employee id you want to search for(1 to 9999): ");
                scanf("%d", &id);
                if (id <= 9999 && id >= 1)
                    break;
            }
            searchContacts(argv[1], id); // call searchContacts
            break;

        case 3: // add more contacts
            createContacts(argv[1]); // call createContacts
            break;

        case -1: // exit
            return 0;

        default: // invalid input
            printf("invalid input, try again\n");
        }
    }

    return 0;
}