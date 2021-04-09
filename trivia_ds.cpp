/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   trivia_ds.cpp contains member functions for the class trivia
 */

#include <iostream>
#include "trivia_ds.h"
#include <cstring>
using namespace std;


//task 1: constructor
trivia::trivia(){


}

//task 2: deconstructor
trivia::~trivia(){

}

//task 3: add a trivia question
int trivia::add_trivia(char* category_name, char* question, char* answer){
  
  return 0;
}

//task 4: display questions from a particular category                
int trivia::display_category(category_node* head){

  return 0;
}

//task 5: display ALL questions                                       
int trivia::display_all(category_node* head){

  return 0;
}

//task 6: remove a category of questions                              
int trivia::remove_category(char* category_name, category_node* head){

  return 0;
}

//task 7: select a trivia question                                    
int trivia::select_question(char* category_name){ //also displays question

  return 0;
}

int trivia::set_used(bool is_used){

  return 0;
}

//task 8: check answer (return true if correct, false otherwise)      
bool trivia::check_answer(trivia_node* current_question, char* user_answer){

  return true;
}
