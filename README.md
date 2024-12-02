# Passkey Management System 

The Passkey Management System is a command-line program designed to provide users
with a secure way to generate, store, search, modify, and delete passkeys for
different websites or accounts. It employs a combination of randomly generated
characters, including letters (both uppercase and lowercase), numbers, and
symbols, to create strong and secure passkeys.

---

### Features:

1.  **Add a Passkey:**
    - Allows users to add a new passkey by entering their username, email address,
      and the website associated with the passkey.
    - Generates a secure passkey and displays it to the user.
    - Appends the user's information along with the passkey to the records file.

2.  **Search for a Passkey:**
    - Enables users to search for a previously stored passkey using their email
      address and the associated website.
    - Displays the found user data, including the username, email address,
      website, and passkey.

3.  **Modify a Passkey:**
    - Permits users to modify an existing passkey by entering their email address
      and the associated website.
    - Provides options to generate a new passkey or enter a custom passkey.
    - Updates the records file with the modified passkey.
    - Displays a message if the data is not available.

4.  **Delete a Passkey:**
    - Allows users to delete a stored passkey by entering their email address and
      the associated website.
    - Clears the specified user data from the records file.
    - Displays a message if the data is not available.

5.  **Display All Records:**
    - Displays all user data stored in the "records.txt" file.
    - Provides an option to return to the main menu.

6.  **Exit:**
    - Exits the program.

### Functions:
 * `randomNum`: Generates a random number between specified min and max values.
 * `shuffle`: Implements the Fisher-Yates shuffle algorithm for shuffling characters in a key.
 * `setKey`: Generates a passkey and shuffles it based on specified criteria.
 * `appendData`: Appends user data to the file.
 * `searchData`: Searches for user data in the file based on email ID and website.
 * `modifyData`: Modifies user data in the file, allowing users to change passkeys.
 * `clearData`: Clears user data from the file based on email ID and website.
 * `clearFile`: Clears the entire content of the file.
 * `isEmpty`: Checks if the file is empty.
 * `displayData`: Displays all user data from the file.
 * `toLower`: Converts a string to lowercase.
 * `clearConsole`: Clears the console screen.

### Implementation Details:
- Passkeys are generated using a mix of lowercase and uppercase letters, 
  numbers, and symbols for enhanced security.
- Passkeys are shuffled using the Fisher-Yates shuffle algorithm.
- User data, including usernames, email addresses, websites, and passkeys, 
  is stored in a text file ("records.txt").
- The program utilizes dynamic memory allocation for storing and manipulating 
  user data.
- To ensure data integrity, modifications and deletions are performed using 
  temporary files.

### Usage Instructions:
1. Run the program, and a menu will be displayed with options to perform 
   various tasks.
2. Follow on-screen prompts to add, search, modify, delete, or display passkeys.
3. Exit the program when done.


---