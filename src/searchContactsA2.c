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

int searchContacts(char *fileName, int keyId) {
    FILE *file = fopen(fileName, "rb"); // open the file
    
    if (!file) { // check if the file was opened
        printf("failed to open file\n");
        exit(EXIT_FAILURE);
    }

    int found = 0; // flag to see if found
    struct contact c;

    while (fread(&c, sizeof(struct contact), 1, file) == 1) { // loop through contacts
        int empId;
        fseek(file, c.empIdPosn, SEEK_SET); // go to the position of the id
        fread(&empId, sizeof(empId), 1, file);

        if (empId == keyId) { // check if they match
            found = 1; // mark found if matched

            printf("employee id: %d\n", empId);

            char buffer[101]; // buffer for reading strings

            // read and print first name if exists
            if (c.firstNamePosn > 0) {
                fseek(file, c.firstNamePosn, SEEK_SET);
                fgets(buffer, 101, file);
                printf("first name: %s\n", buffer);
            } 
            else {
                printf("first name not given\n");
            }

            // read and print last name if exists
            if (c.lastNamePosn > 0) {
                fseek(file, c.lastNamePosn, SEEK_SET);
                fgets(buffer, 101, file);
                printf("last name %s\n", buffer);
            } 
            else {
                printf("last name not given\n");
            }

            // read and print email if exists
            if (c.emailPosn > 0) {
                fseek(file, c.emailPosn, SEEK_SET);
                fgets(buffer, 101, file);
                printf("email: %s\n", buffer);
            } 
            else {
                printf("email not given\n");
            }

            break; // break when done
        }

        // move to next contact
        if (c.next > 0) {
            fseek(file, c.next, SEEK_SET); 
        }
        else {
            break; // break if no more contacts
        }
    }

    if (!found) { //if not found print message
        printf("No match found.\n");
    }

    fclose(file); 
    return found; // return 1 if found 0 if not
}
