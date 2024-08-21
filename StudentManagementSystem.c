/*
 * StudentManagementSystem.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Aziza Abdul Rahman Zamel
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOUND 1
#define NOT_FOUND 0

typedef struct student {
	int id;
	float gpa;
	char name[50];
	int age;
} student;

typedef struct node {
	student data;
	struct node *next;
} node;

node *head = NULL;
// pointers used in functions to loop in linked list
node *current = NULL;
node *previous = NULL;

/**********************         function prototypes         **********************/

// function returns 1 if Id found and 0 if not found
int isFound(int studentID);

// function adds student to the student linked list
void addStudent(const struct student *const ptr);

// function displays the details of all students currently in the system
void displayStudents(void);

// function searches for a student by their ID and displays their details if found
void searchStudentByID(int id);

// function updates the details of a student with the given ID
void updateStudent(int id);

// function calculates and returns the average GPA of all students
float calculateAverageGPA(void);

// function finds and displays the student with the highest GPA.
void searchHighestGPA(void);

// function deletes a student from the linked list by their ID
void deleteStudent(int id);

/***********************************************************************************/

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	int choice, id;
	while (1) {
		// menu
		printf("-------------------------------------------------------\n");
		printf("1. Add Student\n");
		printf("2. Display Students\n");
		printf("3. Search Student by ID\n");
		printf("4. Update Student Information\n");
		printf("5. Delete Student\n");
		printf("6. Calculate Average GPA\n");
		printf("7. Search for Student with Highest GPA\n");
		printf("8. Exit\n");
		printf("Enter choice: ");
		scanf(" %d", &choice);

		switch (choice) {
		case 1:
			printf("-------------------------------------------------------\n");
			student s;
			printf("Enter Student ID: ");
			scanf(" %d", &(s.id));
			printf("Enter name: ");
			scanf(" %s", s.name);
			printf("Enter age: ");
			scanf(" %d", &(s.age));
			printf("Enter GPA: ");
			scanf(" %f", &(s.gpa));
			addStudent(&s);
			break;
		case 2:
			printf("-------------------------------------------------------\n");
			displayStudents();
			break;
		case 3:
			printf("Enter Student ID to search: ");
			scanf(" %d", &id);
			printf("-------------------------------------------------------\n");
			searchStudentByID(id);
			break;
		case 4:
			printf("Enter Student ID to update it's information: ");
			scanf(" %d", &id);
			printf("-------------------------------------------------------\n");
			updateStudent(id);
			break;
		case 5:
			printf("Enter Student ID to Delete it's Data: ");
			scanf(" %d", &id);
			printf("-------------------------------------------------------\n");
			deleteStudent(id);
			break;
		case 6:
			printf("-------------------------------------------------------\n");
			printf("Average GPA= %f\n", calculateAverageGPA());
			break;
		case 7:
			printf("-------------------------------------------------------\n");
			searchHighestGPA();
			break;
		case 8:
			printf("Exiting...\n");
			return 0;
		}
	}
	return 0;
}

int isFound(int studentID) {
	// start checking from the first student
	current = head;
	while (current != NULL) {

		// if ID found, current pointer will point to the student with this ID
		// if the student with this ID is not the first student in the list, previous pointer will point to the student before this student
		if ((current->data.id) == studentID) {
			return FOUND;
		}

		previous = current;
		current = current->next;
	}
	// ID not found
	return NOT_FOUND;
}

void addStudent(const struct student *const ptr) {
	//check if ID is already reserved
	if (isFound(ptr->id)) {
		printf("-------------------------------------------------------\n");
		printf("This ID is already reserved\n");
		return;
	}

	// Allocate memory for new node
	node *newStudent = (node*) malloc(sizeof(node));

	// check If memory allocation fails
	if (newStudent == NULL) {
		printf("ERROR, failed to add new student\n");
		return;
	}

	// copy student data
	newStudent->data.age = ptr->age;
	newStudent->data.gpa = ptr->gpa;
	newStudent->data.id = ptr->id;
	strcpy(newStudent->data.name, ptr->name);
	// student will be added to the end of the list
	newStudent->next = NULL;

	// if head is empty, create list
	if (head == NULL) {
		head = newStudent;
		return;
	}
	// loop until reach the last node in the list
	current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	// Make the last node in the old list point to new node
	current->next = newStudent;
}

void displayStudents(void) {
	//check if the list is empty
	if (head == NULL) {
		printf("No students are present.\n");
		return;
	}

	// loop until the end of list printing information of each student
	current = head;
	while (current != NULL) {
		printf("[ ID: %d, Name: %s, Age: %d, GPA: %.2f ]\n", current->data.id,
				current->data.name, current->data.age, current->data.gpa);
		current = current->next;
	}
}

void searchStudentByID(int id) {
	// if ID found print student information
	if (isFound(id)) {
		printf("Student found:\n");
		printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n", current->data.id,
				current->data.name, current->data.age, current->data.gpa);
	} else {
		// ID not found
		printf("Student with ID %d not found.\n", id);
	}
}

void updateStudent(int id) {
	// if ID found update student information
	if (isFound(id)) {
		printf("Enter new details for the student with ID %d\n", id);
		printf("Enter new name: ");
		scanf(" %s", current->data.name);
		printf("Enter new age: ");
		scanf(" %d", &(current->data.age));
		printf("Enter new GPA: ");
		scanf(" %f", &(current->data.gpa));

		printf("Student details updated successfully\n");
	} else {
		// ID not found
		printf("Student with ID %d not found.\n", id);
	}
}

float calculateAverageGPA(void) {
	// check if the list is empty
	if (head == NULL) {
		return 0;
	}
	float sum = 0;
	int count = 0;

	// loop until the end of the list adding GPA of each student and count the number of students
	current = head;
	while (current != NULL) {
		sum += current->data.gpa;
		count++;
		current = current->next;
	}
	// return the average
	return sum / count;
}

void searchHighestGPA(void) {
	// check if the list is empty
	if (head == NULL) {
		printf("There are no students.\n");
		return;
	}

	// assume the first student in the list have highest GPA
	node *highestStudent = head;

	// start checking from the second student in the list
	current = head->next;
	while (current != NULL) {
		if ((current->data.gpa) > highestStudent->data.gpa) {
			highestStudent = current;
		}
		current = current->next;
	}

	// print student information
	printf("Student with the highest GPA:\n");
	printf("[ ID: %d, Name: %s, Age: %d, GPA: %.2f ]\n",
			highestStudent->data.id, highestStudent->data.name,
			highestStudent->data.age, highestStudent->data.gpa);

}

void deleteStudent(int id) {
	// if ID found delete student
	if (isFound(id)) {
		// if the ID found for the first student in the list, move head to next student
		if (current == head) {
			head = head->next;
		} else {
			previous->next = current->next;
		}
		// delete student
		free(current);
		printf("Student with ID %d deleted successfully.\n", id);
	} else {
		// ID not found
		printf("Student with ID %d not found.\n", id);
	}
}

