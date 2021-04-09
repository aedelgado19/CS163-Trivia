/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   main.cpp acts as a user interface to test the ADT

 */
#include <iostream>
#include "trivia_ds.h"
#include <cstring>
using namespace std;

bool check_valid(char input[]);

int main(){
  char input[20];
  char category[20];
  char question[40];
  char answer[40];
  cout << "Welcome to Trivia Questions!" << endl;
  cout << "Type 'help' anytime to see possible commands." << endl;

  while(strcmp(input, "q") != 0){
    cout << "> ";
    cin.get(input, 20);
    cin.get();

    for(int i = 0; i < strlen(input); i++){ //change input to lowercase
      input[i] = tolower(input[i]);
    }

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
      trivia->add_trivia(category, question, answer);
    }
    
    if(strcmp(input, "dcat") == 0){

    }

    if(strcmp(input, "dall") == 0){

    }

    if(strcmp(input, "rm") == 0){

    }

    if(strcmp(input, "select") == 0){

    }

    if(strcmp(input, "check") == 0){

    }
  }
  cout << "Thanks for playing. Goodbye!" << endl;
  
  return 0;
}

  
