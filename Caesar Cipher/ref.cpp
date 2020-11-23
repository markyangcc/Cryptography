
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/********************************  FUNCTION PROTOTYPES
 * ******************************/
char encrypt(char c, int key);
char decrypt(char c, int key);
void menu();
void choice(int pick);
void manipulateString();
void outputEncryption();
void outputDecryption();
void harderToCrack(string &str);

/**********************************  GLOBAL VARIABLES
 * *******************************/
string str;
int key, size;
char chars[1000];

/********************************      MAIN METHOD
 * ******************************/
int main() {
  cout << "Please enter a sentence to encrypt or decrypt:" << endl;

  getline(cin, str);  // user sentence input

  size = str.size();  // number of characters in the user's sentence

  endl(cout);

  do  // get the shift key
  {
    cout << "Please enter an integer between -25 and 25 for the shift key: ";

    cin >> key;
  } while (key < -25 || key > 25);

  endl(cout);

  menu(); /* call the menu function */

  endl(cout);
  endl(cout);
  cout << "Please press any key to EXIT!" << endl;
  getchar();

  return 0;
}  // END MAIN

/*******************************  Menu Function
 * **************************************/
void menu() {
  int x;
  cout << "Please choose a number from the following menu:" << endl;
  endl(cout);
  cout << "1. Encrypt my sentence." << endl;
  cout << "2. Encrypt and remove all white spaces\n"
       << "           and make it all lower case." << endl;
  cout << "3. Decrypt my sentence." << endl;

  cin >> x;
  choice(x);  // call choice function
}  // end menu function

/************************** Manipulate String Function
 * *******************************/
void manipulateString() {
  int size = str.size();

  for (int a = 0; a <= size; a++) {
    chars[a] = str[a]; /** convert the string into a character array*/
  }
}  // end manipulateString function

/************************** Output Encryption Function
 * *******************************/
void outputEncryption() {
  cout << "\nEncrypted: ";

  for (int i = 0; i < size; i++) {
    char c = chars[i];
    char encrypted = encrypt(c, key);

    cout << encrypted;
  }
}  // end outputEncryption function

/************************** Output Decryption Function
 * *******************************/
void outputDecryption() {
  cout << "\nDecrypted: ";

  for (int i = 0; i < size; i++) {
    char c = chars[i];
    char decrypted = decrypt(c, key);

    cout << decrypted;
  }
}  // end outputDecryption function

/*******************************  Choice Function
 * ***********************************/
void choice(int pick) {
  if (pick == 1) {
    manipulateString();
    outputEncryption();
  } else if (pick == 2) {
    harderToCrack(str);
    manipulateString();
    outputEncryption();
  } else if (pick == 3) {
    manipulateString();
    outputDecryption();
  } else {
    cout << "I'm sorry, that is not a valid choice." << endl;
  }
}  // end choice function

/******************************* Encryption Function
 * *********************************/
char encrypt(char c, int key) {
  char alphabet[26];
  int i = 0;

  for (char ch = 'a'; ch <= 'z';
       ++ch) /* fills alphabet array with the alphabet     */
  {
    alphabet[ch - 'a'] = ch;
  }

  /*                          BELOW while loop FROM:
                   http://www.cs.utsa.edu/~wagner/laws/Acaesar.html */

  while (i < 26) {
    if (c == alphabet[i]) return alphabet[(i + key + 26) % 26];
    i++;
  }
  return c;
}  // end encryption function

/******************************* Decryption Function
 * *********************************/
char decrypt(char c, int key) {
  char alphabet[26];
  int i = 0;

  for (char ch = 'a'; ch <= 'z';
       ++ch) /* fills alphabet array with the alphabet     */
  {
    alphabet[ch - 'a'] = ch;
  }

  /*                               BELOW while loop FROM:
                   http://www.cs.utsa.edu/~wagner/laws/Acaesar.html */

  while (i < 26) {
    if (c == alphabet[i]) return alphabet[(i - key + 26) % 26];
    i++;
  }
  return c;
}  // end decryption function

/******************************* harderToCrack Function
 * ******************************/
void harderToCrack(string &str)  // must use a reference variable here
{
  for (int i = 0; i < size; i++) /* this for loop removes all white spaces, */
  {
    if (str[i] == ' ' || str[i] == '.' || str[i] == '?') {
      str.erase(i, 1);
      i--;
    }
  }

  for (int y = 0; y < size;
       y++) /* this for loop makes everything lower case        */
  {
    str[y] = tolower(str[y]);
  }

}  // end harderToCrack function

// END OF CODE