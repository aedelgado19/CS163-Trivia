/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   trivia_ds.cpp contains member functions for the class trivia
 */

#include <iostream>
#include "trivia_ds.h"
#include <cstring>
#include <cstdlib>
#include <ctime>

/* constructor for trivia node */
trivia_node::trivia_node(){
  next = NULL;
  is_used = false;
}

/* constructor for category node */
category_node::category_node(){
  next = NULL;
  trivia_head = NULL;
  count = 0;
}

/* task 1: constructor */
trivia::trivia(){
  head = NULL;
  question_asked = NULL;
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

  //make question lowercase (for checking question later)
  for(int i = 0; i < strlen(question); i++){
    question[i] = std::tolower(question[i]);
  }

  //make answer lowercase (for checking too)
  for(int j = 0; j < strlen(answer); j++){
    answer[j] = std::tolower(answer[j]);
  }
  
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
    new_category->count += 1;
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
	current_cat->count += 1;
	return 1;
    }    
    //first traverse list to see if category already exists
    while(current_cat != NULL){  
      if(strcmp(current_cat->category_name, category_name) == 0){ //CASE 1: found a match	
	//traverse trivia nodes to add to end
	current_triv = current_cat->trivia_head;
	while(current_triv->next != NULL){
	  current_triv = current_triv->next;
	}
	//out of while loop, found end of trivia nodes
	current_triv->next = new_trivia;
	current_cat->count += 1;
	return 1; //success!
      }
      current_cat = current_cat->next;
    }

    //CASE 2 (did not find a matching category in the traversal)
    //first, if the head is the only existing category so far, set to head's next
    if(head->next == NULL){
      head->next = new_category; //link up chain
      strcpy(new_category->category_name, category_name);
      new_category->next = NULL;
      new_category->trivia_head = new_trivia;
      new_category->count += 1;
      return 1; //success!    
    }
    //while next isn't null and it is not a matching name...
    while(current_cat->next != NULL && (strcmp(current_cat->category_name, category_name) != 0)){ 
      current_cat = current_cat->next;
    }
    current_cat->next = new_category; //link up chain
    strcpy(new_category->category_name, category_name);
    new_category->next = NULL;
    new_category->trivia_head = new_trivia; //attach it to its category
    new_category->count += 1;
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
  if(head == NULL){
    return 1; //still successful, just an empty list (doesn't mean failure)
  }

  //check head first (if the head is the only node, the following while loop won't fire)
  //so we check it here
  if(strcmp(current->category_name, category_name) == 0){ //found a match
    current_triv = current->trivia_head;
    found = true;
  }

  //traverse category nodes
  while(current != NULL){
    if(strcmp(current->category_name, category_name) == 0){ //found a match
      current_triv = current->trivia_head;
      found = true;
    }
    current = current->next;
  }

  //if you did not find a match...
  if(found == false){
    return 2; //function still successful, just didn't find a matching category
  } else { //did find a match, so print out all questions and their answers
    std::cout << "     Trivia questions for category: " << category_name << std::endl;
    while(current_triv != NULL){ //traverse the trivia list
      std::cout << "     Question #" << question_count << ": " << current_triv->question << std::endl;
      std::cout << "     Answer for question " << question_count << ": " << current_triv->answer << std::endl;
      current_triv = current_triv->next;
      question_count++;
    }
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
  
  while(current != NULL){ //traverse list
    std::cout << "Trivia questions for category " << current->category_name << ": " << std::endl;
    cur = current->trivia_head;
    while(cur != NULL){
      std::cout << "     Question: " << cur->question << std::endl;
      std::cout << "     Answer: " << cur->answer << std::endl;
      if(cur->is_used == true){
	std::cout << "     Used: yes" << std::endl;
      } else {
	std::cout << "     Used: no" << std::endl;
      }
      cur = cur->next;
    }
    current = current->next;
  }
  return 1;
}

/* task 6: remove a category of questions */
int trivia::remove_category(char* category_name){
  category_node* current_cat = head;
  category_node* prev_cat = NULL;
  trivia_node* current_triv = NULL;
  bool found = false;
  
  //special case: check if the head is the one to delete
  if(strcmp(head->category_name, category_name) == 0){
    found = true;
    current_triv = head->trivia_head;
    while(current_triv->next != NULL){ //traverse trivia nodes
      trivia_node* t_temp = current_triv;
      current_triv = current_triv->next;
      delete t_temp;
    }
    delete current_triv; //delete final node
    current_cat->trivia_head = NULL; 
    category_node* c_temp = head; //delete original head now
    head = head->next;
    delete c_temp;
    return 1;
  }

  //otherwise, just traverse the list to find the match
  while(current_cat->next != NULL){
    prev_cat = current_cat;
    current_cat = current_cat->next;
    if(strcmp(current_cat->category_name, category_name) == 0){
      found = true;
      prev_cat->next = current_cat->next; //unlink current category
      //traverse trivia list of the node to delete
      current_triv = current_cat->trivia_head;
      while(current_triv->next != NULL){
	trivia_node* t_temp = current_triv;
	current_triv = current_triv->next;
	delete t_temp;
      }
      //delete the last trivia node too
      delete current_triv;
      current_cat->trivia_head = NULL;
      //now delete the category
      delete current_cat;
      return 1;
    }
  }
  if(found == false){ //if the user tries to remove a nonexistent node
    return 2; //special case, didn't find anything
  }  
  return 0;
}

/* task 7: select a trivia question */                          
int trivia::select_question(char* category_name){
  srand(time(0));
  category_node* current = head;
  int visited = 0; //keeps track of how many nodes you've visited
  
  //check head first to see if it is the match
  if(strcmp(head->category_name, category_name) == 0){
    int rand_num = rand() % head->count;
    trivia_node* cur = head->trivia_head;
    while(visited < rand_num){ //find randomly selected node
      visited++;
      cur = cur->next;
    }
    //out of while loop, found the randomly selected node
    std::cout << "Here is your question: " << std::endl;
    std::cout << cur->question << std::endl;
    question_asked = cur;
    return 1;
  }

  //if it's not the head...
  while(current != NULL){ //traverse list until you find it
    if(strcmp(current->category_name, category_name) == 0){ //found a match
      int rand_num = rand() % current->count;
      trivia_node* cur = current->trivia_head;
      while(visited < rand_num){ //find randomly selected node
	visited++;
	cur = cur->next;
      }
      //out of while loop, found the randomly selected node
      std::cout << "Here is your question: " << std::endl;
      std::cout << cur->question << std::endl;
      question_asked = cur;
      return 1;
    }
    current = current->next;
  }
  return 0;
}


/* task 8: check answer (return true if correct, false otherwise) */
bool trivia::check_answer(char* user_answer){
  char* correct_answer = NULL;
  
  if(question_asked == NULL){ //if the user has not typed "select"...
    return false;
  } else { //otherwise set correct_answer to the question
    correct_answer = question_asked->answer;
  }
  for(int i = 0; i < strlen(user_answer); i++){ //convert to lowercase
    user_answer[i] = std::tolower(user_answer[i]);
  }
  if(strcmp(correct_answer, user_answer) == 0){ //check match
    question_asked->is_used = true;
    return true;
  }
  return false;
}
