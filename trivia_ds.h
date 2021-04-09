/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   trivia.h contains the structures needed for nodes and their data
   in this data structure
 */
#include <iostream>

//trivia is the data for the trivia_node
struct trivia_data {
  char* question;
  char* answer;
  bool is_used;
};

//a trivia node points to another trivia node of the SAME category
struct trivia_node {
  trivia_data details;
  trivia_node* next;  
};

//a category node points to another category node of a different category
//ex: history points to art
struct category_node {
  char* category_name;
  category_node* next;
  trivia_node* head;
};


//all int return type functions return 1 if successful, 0 if not
class trivia {
 public:
  trivia(); //task 1: constructor
  ~trivia(); //task 2: destructor

  //task 3: add a trivia question
  int add_trivia(char* category_name, char* question, char* answer);
  
  //task 4: display questions from a particular category
  int display_category(category_node* head);

  //task 5: display ALL questions
  int display_all(category_node* head);

  //task 6: remove a category of questions
  int remove_category(char* category_name, category_node* head);

  //task 7: select a trivia question
  int select_question(char* category_name); //also displays question
  int set_used(bool is_used);
  
  //task 8: check answer (return true if correct, false otherwise)
  bool check_answer(trivia_node* current_question, char* user_answer);

  //these are functions to create the linked lists
  int set_next_category(category_node* next);
  int set_next_trivia(trivia_node* next);
    
 private:
  category_node* head;

};
