/*
 ============================================================================
 Name        : Parcial.c
 Author      : Jose Cisneros
 Version     :
 Copyright   : Copyright Jose Cisneros 2014
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int * modals; //1 for each level
	char * date;
	int symmetric;
	int period;
	int engineerID;
}Building;

typedef struct{
	int superior;
	int inferior;
}Diameter;

typedef struct{
	int * modals; //1 for each level
	char * date;
	int symmetric;
	int period;
	int engineerID;
	Diameter * diameters; //1 for each level
}Tower;

typedef struct{
	int * modals;
	char * date;
	int period;
	char * roof;
	int engineerID;
}House;

typedef struct{
	int id;
	char * name;
	char * surname;
	char * dob;
	char * startingDate;
	int salary;
	char * position;
}Engineer;

int getLength(char *);
// Engineers
int id_engineers;
int engineers_size;
Engineer * engineers;
void addEngineer();
void editEngineer();
void deleteEngineer();
int printEngineers();
void updateInfo(int,int,char *);
Engineer * findEngineer(int);

// Structures
void addStructure();
void showStructures();


int main(void) {
	id_engineers = 0;
	engineers_size = 0;
	engineers = (Engineer *) malloc(sizeof(Engineer));

	int option = -1;

	while (option != 4){
	printf("1)Add Engineer\n2)Edit Engineer\n3)Delete Engineer\n4)Exit\n");
	scanf("%d",&option);

	switch(option){
	case 1:
		addEngineer();
		break;
	case 2:
		editEngineer();
		break;
	case 3:
		deleteEngineer();
		break;
	case 4: printf("Bye\n");
		break;
	default:printf("Invalid option\n");
		break;

	}
	}


	return 0;
}

int getLength(char * word){

	char * end = word;
	char * start = word;
	int i = 0;

	while (*end != '\0'){
		end = word;
		word++;
	}
	i = end - start;

	return i;
}

void addEngineer(){
	printf("Entre");
	char * name = "Name here";
	char * surname = "Surname here";
	char * dob = "01/01/1990";
	char * startingDate = "02/02/2000";
	int salary = 5000;
	char * position = "Position here";
	Engineer e;
	Engineer * eIndex;

	e.name = name;
	e.surname = surname;
	e.dob = dob;
	e.startingDate = startingDate;
	e.salary = salary;
	e.position = position;

	id_engineers++;
	engineers_size++;
	e.id = id_engineers;

	if (id_engineers == 1){
		eIndex = engineers;
	}
	else{
		engineers = (Engineer *) realloc(engineers,engineers_size * sizeof(Engineer));
		eIndex = engineers + (engineers_size - 1);
	}

	*eIndex = e;
	printf("Engineer added succesfully.\n");

}

void editEngineer(){
	int eng,edit;
	char * newValue;
	char * temp;
	printf("Choose an Engineer: \n");
	eng = printEngineers();
	printf("Choose what you want to edit:\n1)Name\n2)Surname\n3)DOB\n4)Starting Date\n5)Salary\n6)Position\n");
	scanf("%d",&edit);
	printf("Enter new value: \n");
	scanf("%ms",&temp);
	newValue = (char *) malloc(getLength(temp) * sizeof(char));
	strcpy(newValue,temp);
	free(temp);
	updateInfo(eng,edit,newValue);
}

void deleteEngineer(){
	int eng;
	Engineer * eEnd = engineers + (engineers_size - 1);
	printf("Choose an Engineer: \n");
	eng = printEngineers();
	Engineer * eIndex = findEngineer(eng);

	if (eng != id_engineers)
	memmove(eIndex, eIndex+1, (eEnd - eIndex) * sizeof(Engineer));

	engineers = (Engineer *) realloc(engineers,(engineers_size - 1) * sizeof(Engineer));
	engineers_size--;

}

int printEngineers(){
	int e;
	Engineer * eIndex;
	Engineer * eEnd = engineers + (engineers_size - 1);

	for(eIndex = engineers; eIndex <= eEnd; eIndex++){
		printf("%d - %s %s (%s) \n",eIndex->id,eIndex->name,eIndex->surname,eIndex->position);
	}
		scanf("%d",&e);

	return e;
}

void updateInfo(int id,int index,char * newValue){
	Engineer * eIndex = findEngineer(id);
	int salary = 0;

	if (index == 5)
		salary = atoi(newValue);

	switch(index){
	case 1: eIndex->name = newValue;
		break;
	case 2: eIndex->surname = newValue;
		break;
	case 3: eIndex->dob = newValue;
		break;
	case 4: eIndex->startingDate = newValue;
		break;
	case 5: eIndex->salary = salary;
		break;
	case 6: eIndex->position = newValue;
		break;

	}
}

Engineer * findEngineer(int id){
	Engineer * eIndex;
	Engineer * eEnd = engineers + (engineers_size - 1);
		for(eIndex = engineers; eIndex <= eEnd; eIndex++){
			if(eIndex->id == id)
				break;
		}
	return eIndex;
}

void addStructure(){
	int type;
	printf("Choose type of structure:\n1)Building\n2)Tower\n3)House\n");
	scanf("%d",&type);

	switch(type){
	case 1:{

		break;
	}
	case 2:{

		break;
	}
	case 3:{

		break;
	}

	}
}
void showStructures(){

}
