/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   main.cpp acts as a user interface to test the ADT

 */
#include <iostream>
#include "trivia_ds.h"
#include <cstring>
using namespace std;

void print_error_messages(int success, const char function_name[]);

/* main prompts the user for input
   and passes the input to public member functions.
 */
int main(){
  int success = 0;
  trivia* new_trivia = new trivia();
  char input[20];
  char category[20];
  char question[40];
  char answer[40];
  cout << " " << endl;
  cout << "********************************************* " << endl;
  cout << "Welcome to Trivia Questions!" << endl;
  cout << "Type 'help' to see possible commands." << endl;

  while(strcmp(input, "q") != 0){ //while the user hasn't commanded program to quit
    cout << "> ";
    cin.get(input, 20);
    cin.get();

    for(int i = 0; i < strlen(input); i++){ //change input to lowercase
      input[i] = tolower(input[i]);
    }
    //print out all possible commands
    if(strcmp(input, "help") == 0){
      cout << "Commands are: " << endl;
      cout << "'add' - add a new trivia question" << endl;
      cout << "'dcat' - display category" << endl;
      cout << "'dall' - display all questions" << endl;
      cout << "'rm' - remove a category of questions" << endl;
      cout << "'select' - select a trivia question" << endl;
      cout << "'check' - check answer" << endl;
      cout << "'q' - quit game" << endl;
    }
    //prompt user for trivia data, send to add_trivia function
    if(strcmp(input, "add") == 0){
      cout << "Enter the category of this trivia question." << endl;
      cout << "> ";
      cin.get(category, 20);
      cin.get();
      cout << "Enter the question." << endl;
      cout << "> ";
      cin.get(question, 40);
      cin.get();
      cout << "Enter the answer." << endl;
      cout << "> ";
      cin.get(answer, 40);
      cin.get();
      success = new_trivia->add_trivia(category, question, answer);
      print_error_messages(success, "add_trivia");
    }
    //prompt user for the name of the category and call display_category function
    if(strcmp(input, "dcat") == 0){
      cout << "Enter the name of the category you would like to display. " << endl;
      cout << "> ";
      cin.get(category, 20);
      cin.get();
      success = new_trivia->display_category(category);
      print_error_messages(success, "display_category");
    }

    //call display_all function
    if(strcmp(input, "dall") == 0){
      success = new_trivia->display_all();
      print_error_messages(success, "display_all");
    }

    if(strcmp(input, "rm") == 0){

    }

    if(strcmp(input, "select") == 0){

    }

    if(strcmp(input, "check") == 0){

    }
  }
  cout << "Thanks for playing. Goodbye!" << endl;
  delete new_trivia;
  return 0;
}

/* This function uses the integer returned from the member functions
   that determines their success. If anything but a 1 is passed in,
   it will print that there was an error in the function.

   inputs: integer success, name of function
   outputs: print error message if necessary
 */
void print_error_messages(int success, const char function_name[]){
  if(success == 1){ //1 returns a successful function
    if(strcmp(function_name, "add_trivia") == 0){
      cout << "Trivia added successfully." << endl;
      cout << " " << endl;
    }
    return;
  } else { //anything else means failure
    cout << "Error in function: " << function_name << endl;
  }
}
