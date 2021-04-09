/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   trivia.h contains the structures needed for nodes and their data
   in this data structure
 */
#include <iostream>

//a trivia node points to another trivia node of the SAME category
struct trivia_node {
  trivia_node(); //constructor for trivia node
  trivia_node* next;
  char* question;
  char* answer;
  bool is_used;

};
 
//a category node points to another category node of a different category
//ex: history points to art
struct category_node {
  category_node(); //constructor for category node
  char* category_name;
  category_node* next;
  trivia_node* trivia_head;
};


//all int return type functions return 1 if successful, 0 if not
class trivia {
 public:
  trivia(); //task 1: constructor
  ~trivia(); //task 2: destructor
  
  //task 3: add a trivia question
  int add_trivia(char* category_name, char* question, char* answer);
  
  //task 4: display questions from a particular category
  int display_category();

  //task 5: display ALL questions
  int display_all();

  //task 6: remove a category of questions
  int remove_category(char* category_name);

  //task 7: select a trivia question
  int select_question(char* category_name);
  
  //task 8: check answer (return true if correct, false otherwise)
  bool check_answer(char* user_question, char* user_answer);

 private:
  category_node* head;

};
