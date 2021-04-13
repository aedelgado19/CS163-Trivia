/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   trivia_ds.cpp contains member functions for the class trivia
 */

#include <iostream>
#include "trivia_ds.h"
#include <cstring>

/* constructor for trivia node */
trivia_node::trivia_node(){
  next = NULL;
  is_used = false;
}

/* constructor for category node */
category_node::category_node(){
  next = NULL;
  trivia_head = NULL;
}

/* task 1: constructor */
trivia::trivia(){
  head = NULL;
}

/* task 2: destructor */
trivia::~trivia(){
  category_node* current_cat = head;
  while (current_cat != NULL){ //traverse category list
    category_node* next_cat = current_cat->next;
    trivia_node* current_triv = current_cat->trivia_head; //find any attached trivia nodes
    while(current_triv != NULL){ //traverse trivia list and delete trivia ndoes
      trivia_node* next_triv = current_triv->next;
      delete current_triv;
      current_triv = next_triv;
    }
    delete current_cat; //delete category node
    current_cat = next_cat; //update category node to its next to keep traversing
  }
  head = NULL;
}

/* task 3: add a trivia question */
int trivia::add_trivia(char* category_name, char* question, char* answer){
  category_node* current_cat = head;
  trivia_node* current_triv = NULL;

  //make new category node
  category_node* new_category = new category_node(); //make a new category
  new_category->category_name = new char[strlen(category_name) + 1];
  
  //make new trivia node
  trivia_node* new_trivia = new trivia_node();
  new_trivia->question = new char[strlen(question) + 1];
  new_trivia->answer = new char[strlen(answer) + 1];
  strcpy(new_trivia->question, question);
  strcpy(new_trivia->answer, answer);
  new_trivia->next = NULL;
  new_trivia->is_used = false;

  //if head is null, set head to the new category (nothing currently in list)
  if(head == NULL){ 
    head = new_category;
    strcpy(new_category->category_name, category_name);
    new_category->next = NULL;
    new_category->trivia_head = new_trivia; //link up category node to trivia node
    return 1; //success!
  }

  // if the head is NOT null, there are 2 cases:
  // 1) the category exists already (traverse categories, find match, add trivia)
  // 2) the category does not exist (traverse categories, make new category, add trivia)
  else {
    //check if the head is the match (because the while loop below won't fire if
    //there is only one category
    if(strcmp(current_cat->category_name, category_name) == 0){ //check head category
	current_triv = current_cat->trivia_head;
	while(current_triv->next != NULL){
	  current_triv = current_triv->next;
	}
	//out of while loop, found end of trivia nodes
	current_triv->next = new_trivia;
	return 1;
    }    
    //first traverse list to see if category already exists
    while(current_cat->next != NULL){  
      current_cat = current_cat->next;
      if(strcmp(current_cat->category_name, category_name) == 0){ //CASE 1: found a match	
	//traverse trivia nodes to add to end
	current_triv = current_cat->trivia_head;
	while(current_triv->next != NULL){
	  current_triv = current_triv->next;
	}
	//out of while loop, found end of trivia nodes
	current_triv->next = new_trivia;
	return 1; //success!
      }
    }

    //CASE 2 (did not find a matching category in the traversal)
    //first, if the head is the only existing category so far, set to head's next
    if(head->next == NULL){
      head->next = new_category; //link up chain
      strcpy(new_category->category_name, category_name);
      new_category->next = NULL;
      new_category->trivia_head = new_trivia;
      return 1; //success!    
    }
    while(current_cat->next != NULL && (strcmp(current_cat->category_name, category_name) != 0)){ 
      current_cat = current_cat->next;
    }
    current_cat->next = new_category; //link up chain
    strcpy(new_category->category_name, category_name);
    new_category->next = NULL;
    new_category->trivia_head = new_trivia; //attach it to its category
    return 1; //success!    
  }
  return 0; //function failure
}

/* task 4: display questions from a particular category */
int trivia::display_category(char* category_name){
  category_node* current = head;
  trivia_node* current_triv = NULL;
  int question_count = 1;
  bool found = false;  

  //check head first (if the head is the only node, the following while loop won't fire)
  //so we check it here
  if(strcmp(current->category_name, category_name) == 0){ //found a match
    current_triv = current->trivia_head;
    found = true;
  }
  //traverse category nodes
  while(current->next != NULL){
    if(strcmp(current->category_name, category_name) == 0){ //found a match
      current_triv = current->trivia_head;
      found = true;
    }
    current = current->next;
  }
  //outside of the while loop, so check the last node too
  if(strcmp(current->category_name, category_name) == 0){ //found a match
    current_triv = current->trivia_head;
    found = true;
  }
  //if you did not find a match...
  if(found == false){
    std::cout << "No categories were found matching that name." << std::endl;
    return 1; //function still successful, just didn't find a matching category
  } else { //did find a match, so print out all questions and their answers
    std::cout << "Trivia questions for category: " << category_name << std::endl;
    while(current_triv->next != NULL){ //traverse the trivia list
      std::cout << "Question #" << question_count << ": " << current_triv->question << std::endl;
      std::cout << "Answer for question " << question_count << ": " << current_triv->answer << std::endl;
      current_triv = current_triv->next;
      question_count++;
    }
    //get the last node too (while loop above stops at second to last node)
    std::cout << "Question #" << question_count << ": " << current_triv->question << std::endl;
    std::cout << "Answer for question " << question_count << ": " << current_triv->answer << std::endl;
    return 1; //success!
  }
  return 0; //function failure
}

/* task 5: display ALL questions */            
int trivia::display_all(){
  category_node* current = head;
  trivia_node* cur = NULL;
  
  if(head == NULL){
    return 1; //function still successful, there's just nothing to display
  }
  if(head != NULL && head->next == NULL){ //print out head if it is the only category node
    std::cout << "Trivia questions for category " << head->category_name << ": " << std::endl;
    cur = head->trivia_head;
    while(cur->next != NULL){
      std::cout << "     Question: " << head->trivia_head->question << std::endl;
      std::cout << "     Answer: " << head->trivia_head->answer << std::endl;
      if(cur->is_used == true){
	std::cout << "     Used: yes" << std::endl;
      } else {
	std::cout << "     Used: no" << std::endl;
      }
      cur = cur->next;
    }
    return 1;
  }
  //the following while loop knows that head exists and it is not the only node
  while(current->next != NULL){
    std::cout << "Trivia questions for category " << current->category_name << ": " << std::endl;
    cur = current->trivia_head;
    while(cur->next != NULL){
      std::cout << "     Question: " << cur->question << std::endl;
      std::cout << "     Answer: " << cur->answer << std::endl;
      if(cur->is_used == true){
	std::cout << "     Used: yes" << std::endl;
      } else {
	std::cout << "     Used: no" << std::endl;
      }
      cur = cur->next;
    }
    //print out the last trivia node
    std::cout << "     Question: " << cur->question << std::endl;
    std::cout << "     Answer: " << cur->answer << std::endl;
    if(cur->is_used == true){
      std::cout << "     Used: yes" << std::endl;
    } else {
      std::cout << "     Used: no" << std::endl;
    }
    current = current->next;
  }
  //print out the last category node
  std::cout << "Trivia questions for category " << current->category_name << ": " << std::endl;
  cur = current->trivia_head;
  while(cur->next != NULL){ //traverse trivia nodes
    std::cout << "     Question: " << cur->question << std::endl;
    std::cout << "     Answer: " << cur->answer << std::endl;
    if(cur->is_used == true){
      std::cout << "     Used: yes" << std::endl;
    } else {
      std::cout << "     Used: no" << std::endl;
    }
    cur = cur->next;
  }
  //print out the last trivia node
  std::cout << "     Question: " << cur->question << std::endl;
  std::cout << "     Answer: " << cur->answer << std::endl;
  if(cur->is_used == true){
    std::cout << "     Used: yes" << std::endl;
  } else {
    std::cout << "     Used: no" << std::endl;
  }
  return 1;
}

/* task 6: remove a category of questions */
int trivia::remove_category(char* category_name){


  
  return 0;
}

/*task 7: select a trivia question */                          
int trivia::select_question(char* category_name){
  //make sure to call display_category

  return 0;
}


/* task 8: check answer (return true if correct, false otherwise) */
bool trivia::check_answer(char* user_question, char* user_answer){

  return true;
}
