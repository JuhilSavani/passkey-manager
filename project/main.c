// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "logos.c"

// Constants for formatting strings and file path
#define DUMP "%s, %s, %s, %s\n"
#define GET "%[^,], %[^,], %[^,], %[^,\n]\n"
#define PATH "records.txt"

// Structure to hold user data
typedef struct userdata{
    char name[51];
    char id[51];
    char site[51];
    char key[20];
}data;

// Function declarations
int randomNum(int min , int max);
void shuffle(char key[], int length, int times);
void setKey(char passKey[]);
void appendData(data newUser, const char path[]);
data *searchData(data newUser, const char path[]);
void modifyData(data modifiedUser, const char path[]);
void clearData(data modifiedUser, const char path[]);
void clearFile(const char path[]);
bool isEmpty(const char path[]);
void displayData(const char path[]);
void toLower(char *str);
void clearConsole();

int main(){
    // Seed the random number generator
    srand(time(NULL));
    char response ='n';
    int choice;
    fputs(logo1, stdout);
    // Display initial message and wait for user to press enter
    printf("Press Enter to continue...");
    while(getchar() != '\n'); // Until the user press enter
    clearConsole();

    // Main loop for user interaction
    do{
        fputs(logo2, stdout);
        // Display menu options
        printf("Enter the appropriate number to perform following tasks.\n\n");
        printf("1 : Add the passkey.\n2 : Search the passkey.\n3 : Modify the passkey.\n4 : Delete the passkey.\n5 : Exit.\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n'); // Until the user press enter
        clearConsole();

        // Declare variables for user data and file handling
        data newUser, *user;
        FILE *file=NULL;
        switch(choice){
            case 0:
                displayData(PATH);
                printf("\033[%dD", 16);
                printf("Press 'n' to go back to the menu: ");
                response = getchar();
                while(getchar()!='\n'); // Until the user press enter
                clearConsole();
                break;
            case 1:
                // Add a passkey
                do{
                    fputs(logo3, stdout);

                    // Get user input for new passkey
                    printf("Enter the username: ");
                    fgets(newUser.name, sizeof(newUser.name), stdin);
                    printf("Enter your email address: ");
                    fgets(newUser.id, sizeof(newUser.id), stdin);
                    toLower(newUser.id);
                    printf("Enter the website: ");
                    fgets(newUser.site, sizeof(newUser.site), stdin);
                    toLower(newUser.site);
                    setKey(newUser.key);

                    // Display and store the generated passkey
                    printf("your passkey for the website: %s\n\n", newUser.key);
                    user=searchData(newUser, PATH);
                    if(user!=NULL){
                        printf("This data has already been secured in the records.\n\nWant to modify it, then press 'y' else 'n'. ");
                        response = getchar(); // Read a single character
                        while(getchar()!='\n');  // Until the user press enter
                        if(response=='y') modifyData(newUser, PATH);
                        putchar('\n');
                    }
                    else appendData(newUser, PATH);

                    // Ask if the user wants to add another record
                    printf("Want to add another record, Then press 'y' else 'n'. ");
                    response = getchar(); // Read a single character
                    while(getchar()!='\n');  // Until the user press enter
                    clearConsole();

                } while(response == 'y' || response == 'Y');
                break;
            case 2:
                // Search for a passkey
                do{
                    fputs(logo4, stdout);

                    // Get user input for searching
                    printf("Enter the email address: ");
                    fgets(newUser.id, sizeof(newUser.id), stdin);
                    toLower(newUser.id);
                    printf("Enter the website: ");
                    fgets(newUser.site, sizeof(newUser.site), stdin);
                    toLower(newUser.site);

                    // Search for the data and display the result
                    user=searchData(newUser, PATH);
                    if(user!=NULL){
                        printf("\n\n~~~~ Data has been retrieved successfully ~~~~\n\n\tUsername: %s\n\tEmail ID: %s\n\tWebsite: %s\n\tPasskey: %s\n",
                        user->name, user->id, user->site, user->key);
                    }else printf("\n\n~~~~ Sorry! Data is not available ~~~~\n\n");

                    // Ask if the user wants to search another record
                    printf("Want to search another record, Then press 'y' else 'n'. ");
                    response = getchar();
                    while(getchar()!='\n'); // Until the user press enter
                    clearConsole();

                }while(response == 'y' || response == 'Y');
                break;
            case 3:
                // Modify a passkey
                do{
                    fputs(logo5, stdout);

                    // Get user input for modifying
                    printf("Enter user's email address: ");
                    fgets(newUser.id, sizeof(newUser.id), stdin);
                    toLower(newUser.id);
                    printf("Enter the website: ");
                    fgets(newUser.site, sizeof(newUser.site), stdin);
                    toLower(newUser.site);

                    // Search for the data to be modified
                    user=searchData(newUser, PATH);
                    if(user!=NULL){
                        // Ask the user for the modification method
                        printf("\n\nEnter the appropriate number to perform following tasks.\n\n");
                        printf("1 : Generate the new passkey.\n2 : Custom passkey.\n\n\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);
                        switch(choice){
                            case 1:
                                // Generate and display a new passkey
                                setKey(newUser.key);
                                printf("\nHere is the new passkey for this account: ");
                                fputs(newUser.key, stdout);
                                modifyData(newUser, PATH);
                                break;
                            default:
                                // Get a custom passkey from the user
                                printf("\nEnter the passkey for this account: ");
                                scanf("%s", newUser.key);
                                modifyData(newUser, PATH);
                                break;
                        }
                        printf("\n\n~~~~ The user data has been modified successfully ~~~~");
                    }else printf("\n\n~~~~ Sorry! Data is not available ~~~~");

                    // Ask if the user wants to modify another record
                    printf("\n\nWant to modify another record, Then press 'y' else 'n'. ");
                    scanf(" %c", &response);
                    while(getchar()!='\n'); // Until the user press enter
                    clearConsole();
                }while(response == 'y' || response == 'Y');
                break;
            case 4:
                // Delete a passkey
                do{
                    fputs(logo6, stdout);

                    // Get user input to clear the specfic data
                    printf("Enter user's email address: ");
                    fgets(newUser.id, sizeof(newUser.id), stdin);
                    toLower(newUser.id);
                    printf("Enter the website: ");
                    fgets(newUser.site, sizeof(newUser.site), stdin);
                    toLower(newUser.site);

                    // Search for the data to be deleted
                    user=searchData(newUser, PATH);
                    if(user!=NULL){
                        // Clear the data from the records
                        clearData(newUser, PATH);
                        printf("\n\n~~~~ The user has been cleared successfully from the records. ~~~~\n\n");
                    }else printf("\n\n~~~~ Sorry! Data is not available ~~~~\n\n");

                    // Ask if the user wants to delete another record
                    printf("Want to clear another record, Then press 'y' else 'n'. ");
                    response = getchar();
                    while(getchar()!='\n'); // Until the user press enter
                    clearConsole();
                }while(response == 'y' || response == 'Y');
                break;
            default:
                fputs(logo7, stdout);
                return 0;
        }
    }while(response=='n' || response=='N');
    return 0;
}


// Function implementations

// Generates a random number between min and max (inclusive)
int randomNum(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Fisher-Yates shuffle algorithm for shuffling characters in the key
void shuffle(char key[], int length, int times){
    while(times--){
        for (int i=length-1; i>0; i--) {
            int j = rand() % (i + 1);
            char temp=key[i];
            key[i]=key[j];
            key[j]=temp;
        }
    }
    return;
}

// Generates a passkey and shuffles it
void setKey(char passKey[]){
    char set[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$&@*";
    char key[20];
    strcpy(key, " ");
    int letters = randomNum(5, 6);
    int numbers = randomNum(2, 4);
    int symbols = randomNum(2, 4);
    int size = letters + numbers + symbols;
    int i;
    // Generate passkey with a mix of letters, numbers, and symbols
    for (i = 0; i < letters; i++) {
        key[i] = set[randomNum(0, 51)];
    }
    for (; i < letters + numbers; i++) {
        key[i] = set[randomNum(52, 61)];
    }
    for (; i < size; i++) {
        key[i] = set[randomNum(62, 67)];
    }
    key[size] = '\0';
    shuffle(key, strlen(key), 2);
    strcpy(passKey, key);
    passKey[size]='\0';
    return;
}

// Appends user data to the file
void appendData(data newUser, const char path[]){
    FILE *file = fopen(path, "a+"); // If exist it open and if not it will create
    if (file == NULL){
        perror("Error while opening the file for writing!");
        exit(EXIT_FAILURE); 
    }

    // Remove trailing newline characters from user data
    newUser.name[strcspn(newUser.name, "\n")] = '\0';
    newUser.id[strcspn(newUser.id, "\n")] = '\0';
    newUser.site[strcspn(newUser.site, "\n")] = '\0';

    // Write user data to the file
    fprintf(file, DUMP, newUser.name, newUser.id, newUser.site, newUser.key);
    fclose(file);
    return;
}

// Searches for user data in the file
data *searchData(data newUser, const char path[]) {
    data *user = malloc(sizeof(data));
    if (user == NULL) {
        perror("Memory allocation failed in search engine!\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error while opening the file for reading in search engine!");
        free(user);  // Free allocated memory before exiting
        exit(EXIT_FAILURE);
    }

    // Remove trailing newline characters from search criteria
    newUser.id[strcspn(newUser.id, "\n")] = '\0';
    newUser.site[strcspn(newUser.site, "\n")] = '\0';

    while (fscanf(file, GET, user->name, user->id, user->site, user->key) != EOF) {
        // Compare email ID and site
        if (strcmp(newUser.id, user->id) == 0 && strcmp(newUser.site, user->site) == 0) {
            fclose(file);
            return user; // Data found
        }
    }

    fclose(file);
    free(user); // Free allocated memory if data not found
    return NULL; // Data not found -> user=NULL;
}


// Modifies user data in the file
void modifyData(data modifiedUser, const char path[]){
    const char tempPath[] = "tempRecords.txt";
    FILE *tempFile = fopen(tempPath, "w");
    if (tempFile == NULL) {
        perror("Error while opening the file while writing in tempRecords.txt in modifier!");
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error while opening the file while reading records.txt in modifier!");
        exit(EXIT_FAILURE);
    }
    data *user = malloc(sizeof(data));
    if (user == NULL) {
        perror("Memory allocation failed during modification!\n");
        exit(EXIT_FAILURE);
    }

    // Remove trailing newline characters from modification criteria
    modifiedUser.id[strcspn(modifiedUser.id, "\n")] = '\0';
    modifiedUser.site[strcspn(modifiedUser.site, "\n")] = '\0';

    while(fscanf(file, GET, user->name, user->id, user->site, user->key) != EOF){
        if(strcmp(modifiedUser.id, user->id) == 0 && strcmp(modifiedUser.site, user->site) == 0){
            // Modify user data and write to temporary file
            fprintf(tempFile, DUMP, user->name, user->id, user->site, modifiedUser.key);
        }else{
            // Write unchanged data to temporary file
            fprintf(tempFile, DUMP, user->name, user->id, user->site, user->key);
        }
    }
    fclose(file);
    fclose(tempFile);
    free(user);  // Free memory allocated for user data
    remove(path);
    rename(tempPath, path);
    return;
}

// Clears user data from the file
void clearData(data modifiedUser, const char path[]){
    const char tempPath[] = "tempRecords.txt";
    FILE *tempFile = fopen(tempPath, "w");
    if (tempFile == NULL) {
        perror("Error while opening the file while writing in tempRecords.txt in modifier!");
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error while opening the file while reading records.txt in modifier!");
        exit(EXIT_FAILURE);
    }
    data *user = malloc(sizeof(data));
    if (user == NULL) {
        perror("Memory allocation failed during modification!\n");
        exit(EXIT_FAILURE);
    }

    // Remove trailing newline characters from criteria
    modifiedUser.id[strcspn(modifiedUser.id, "\n")] = '\0';
    modifiedUser.site[strcspn(modifiedUser.site, "\n")] = '\0';

    while(fscanf(file, GET, user->name, user->id, user->site, user->key) != EOF){
        if(strcmp(modifiedUser.id, user->id) != 0 || strcmp(modifiedUser.site, user->site) != 0){
            // Write unchanged data to temporary file
            fprintf(tempFile, DUMP, user->name, user->id, user->site, user->key);
        }
    }
    fclose(file);
    fclose(tempFile);
    free(user); // Free memory allocated for user data
    remove(path);
    rename(tempPath, path);
    return;
}

// Clears the entire file
void clearFile(const char path[]){
    FILE *file = fopen(path, "w");
    if (file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    return;
}

// returns true if file is empty
bool isEmpty(const char path[]){
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error while opening the file for reading in isFileEmpty!");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END); // moves the file position indicator to the end
    long size = ftell(file); //  returns the size of the file in bytes.
    fclose(file);

    return size == 0;
}

// Function to display all user data from a file
void displayData(const char path[]) {
    // Allocate memory for a single user data structure
    data *user = malloc(sizeof(data));
    if (user == NULL) {
        perror("Memory allocation failed while displaying user data");
        exit(EXIT_FAILURE);
    }
    // Open the file for reading
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening the file for reading while displaying user data");
        free(user);
        exit(EXIT_FAILURE);
    }
    if (!isEmpty(path)) {
        printf("\n\n>> Data has been retrieved successfully\n\n\n\t");
        // Read and display user data until the end of the file is reached
        while (fscanf(file, GET, user->name, user->id, user->site, user->key) != EOF) {
            // Print user information
            printf("Username: %s\n\tEmail ID: %s\n\tWebsite: %s\n\tPasskey: %s\n\n\t",
                user->name, user->id, user->site, user->key);
        }
    }else printf("\n\n~~~~ File is empty! ~~~~\n\n");
    fclose(file);
    free(user); // Free the allocated memory for user data
    return;
}

// Converts a string to lowercase
void toLower(char *str){
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

// Clears the console screen
void clearConsole(){
    system("clear");
    return;
}
