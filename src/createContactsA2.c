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

// function to create a new contact
void createContacts(char *fileName) {
    FILE *file = fopen(fileName, "rb+");// open the file

    if (!file) {
        file = fopen(fileName, "wb+"); // create the file if it doesnt exist
        if (!file) {
            printf("failed to open or create file\n");
            exit(EXIT_FAILURE);
        }
    }

    //allocate memory
    char *firstName = malloc(101 * sizeof(char));
    char *lastName = malloc(101 * sizeof(char));
    char *email = malloc(101 * sizeof(char));
    
    int empId;
    struct contact newContact = {0, 0, 0, 0, 0};

    //get id
    printf("employee id: ");
    scanf("%d", &empId);
    while (getchar() != '\n');

    //get first name
    printf("first Name: ");
    fgets(firstName, 101, stdin);
    firstName[strcspn(firstName, "\n")] = 0;

    //get last name
    printf("last Name: ");
    fgets(lastName, 101, stdin);
    lastName[strcspn(lastName, "\n")] = 0;

    //get email
    printf("email: ");
    fgets(email, 101, stdin);
    email[strcspn(email, "\n")] = 0;

    //get the position of the new contact
    fseek(file, 0, SEEK_END);
    long newContactPos = ftell(file);

    //---------

    // writing placeholder for new contact
    fwrite(&newContact, sizeof(newContact), 1, file);

    //write the id and update position
    newContact.empIdPosn = ftell(file);
    fwrite(&empId, sizeof(empId), 1, file);

    //write the first name and update position
    newContact.firstNamePosn = ftell(file);
    fwrite(firstName, strlen(firstName) + 1, 1, file);

    //write the last name and update position
    newContact.lastNamePosn = ftell(file);
    fwrite(lastName, strlen(lastName) + 1, 1, file);

    //write the email and update position
    newContact.emailPosn = ftell(file);
    fwrite(email, strlen(email) + 1, 1, file);

    // go back and update the new contact
    fseek(file, newContactPos, SEEK_SET);
    fwrite(&newContact, sizeof(newContact), 1, file);

    fseek(file, 0, SEEK_SET); 
    struct contact temp; // temp to update last contact
    long lastContactPos = -1;

    // loop through the contacts
    while (fread(&temp, sizeof(temp), 1, file) == 1) {
        if (temp.next == 0) { // see if we r at the end of the file

            lastContactPos = ftell(file) - sizeof(temp);
            break;

        } 
        else { // move to the next contact

            fseek(file, temp.next, SEEK_SET);
        }
    }

    if (lastContactPos != -1) { // update the last contact

        fseek(file, lastContactPos, SEEK_SET);
        fread(&temp, sizeof(temp), 1, file);
        temp.next = newContactPos;
        fseek(file, lastContactPos, SEEK_SET);
        fwrite(&temp, sizeof(temp), 1, file);
    }

    fclose(file);
}
