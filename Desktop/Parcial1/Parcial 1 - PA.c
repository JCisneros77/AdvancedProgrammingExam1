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
	int levels;
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
	int levels;
	char * date;
	int period;
	int engineerID;
	Diameter * diameters; //1 for each level
}Tower;

typedef struct{
	int modals;
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

//Helper Functions
int getLength(char *);
int inRange(char*,char*,char*);

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

//Buildings
int buildings_size;
Building * buildings;
void printBuilding(Building *);

//Towers
int towers_size;
Tower * towers;
void printTower(Tower *);

//Houses
int houses_size;
House * houses;
void printHouse(House *);

void printHRReport();

int main(void) {
	id_engineers = 0;
	engineers_size = 0;
	engineers = (Engineer *) malloc(sizeof(Engineer));

	buildings_size = 0;
	buildings = (Building *) malloc(sizeof(Building));

	towers_size = 0;
	towers = (Tower *) malloc(sizeof(Tower));

	houses_size = 0;
	houses = (House *) malloc(sizeof(House));

	int option = -1;

	while (option != 0){
	printf("1)Add Engineer\n2)Edit Engineer\n3)Delete Engineer\n4)Add Structure\n5)Show Structures per date\n6)HR Report\n0)Exit\n");
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
	case 4:
		addStructure();
		break;
	case 5:
		showStructures();
		break;
	case 6:
		printHRReport();
		break;
	case 0: printf("Bye\n");
		break;
	default:printf("Invalid option\n");
		break;

	}
	}

	//FREE

	// Free Memory
	Building * bIndex;
	Building * bEnd = buildings + (buildings_size - 1);
	for(bIndex = buildings; bIndex <= bEnd; ++bIndex){
		free(bIndex->modals);
	}
	Tower * tIndex;
	Tower * tEnd = towers + (towers_size - 1);
	for(tIndex = towers; tIndex <= tEnd; ++tIndex){
		free(tIndex->modals);
		free(tIndex->diameters);
	}
	free(engineers);
	free(buildings);
	free(towers);
	free(houses);

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

	if (engineers_size == 1){
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
	char * newValue[100];
	printf("Choose an Engineer: \n");
	eng = printEngineers();
	printf("Choose what you want to edit:\n1)Name\n2)Surname\n3)DOB\n4)Starting Date\n5)Salary\n6)Position\n");
	scanf("%d",&edit);
	printf("Enter new value: \n");
	scanf("%s",newValue);
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
	case 1:{ // Building
		Building b;
		Building * bIndex;
		int levels = 5;
		int * modals = (int *) malloc (levels * sizeof(int));
		int * modalsIndex;
		int * modalsEnd = modals + (levels - 1);
		for(modalsIndex = modals; modalsIndex <=modalsEnd; ++modalsIndex)
			*modalsIndex = 1;
		char * date = "01/01/2010";
		int symmetric = 1;
		int period = 2;
		int engineerID;
		printf("Enter Engineer ID:\n");
		scanf("%d",&engineerID);
		b.levels = levels;
		b.modals = modals;
		b.date = date;
		b.symmetric = symmetric;
		b.period = period;
		b.engineerID = engineerID;

		buildings_size++;
		if (buildings_size == 1){
			bIndex = buildings;
		}
		else{
			buildings = (Building *) realloc(buildings,buildings_size * sizeof(Building));
			bIndex = buildings + (buildings_size - 1);
		}
		*bIndex = b;


		break;
	}
	case 2:{ // Tower
		Tower t;
		Tower * tIndex;
		int engineerID;
		int period = 3;
		int levels = 5;
		int * modals = (int *) malloc (levels * sizeof(int));
		int * modalsIndex;
		int * modalsEnd = modals + (levels - 1);
		for(modalsIndex = modals; modalsIndex <=modalsEnd; ++modalsIndex)
			*modalsIndex = 1;

		char * date = "01/01/2010";
		printf("Enter Engineer ID:\n");
		scanf("%d",&engineerID);
		Diameter * diameters = (Diameter *) malloc (levels * sizeof(Diameter));
		int i;
		for(i = 0; i < levels; ++i){
			Diameter d;
			d.inferior = 2;
			d.superior = 3;
			*(diameters + i) = d;
		}
		t.levels = levels;
		t.date = date;
		t.diameters = diameters;
		t.engineerID = engineerID;
		t.period = period;
		t.modals = modals;

		towers_size++;
		if (buildings_size == 1){
			tIndex = towers;
		}
		else{
			towers = (Tower *) realloc(towers,towers_size * sizeof(Tower));
			tIndex = towers + (towers_size - 1);
		}
		*tIndex = t;
		break;
	}
	case 3:{
		House h;
		House * hIndex;
		int modals = 2;
		char * date = "01/01/2010";
		int period = 5;
		char * roof = "Roof";
		int engineerID;
		printf("Enter Engineer ID:\n");
		scanf("%d",&engineerID);

		h.date = date;
		h.engineerID = engineerID;
		h.modals = modals;
		h.period = period;
		h.roof = roof;

		houses_size++;
		if (houses_size == 1){
			hIndex = houses;
		}
		else{
			houses = (House *) realloc(houses,houses_size * sizeof(House));
			hIndex = houses + (houses_size - 1);
		}
		*hIndex = h;
		break;
	}

	}
	printf("Modeling structure. \n");
	printf("Structure added. \n");
}

void showStructures(){
	char * date;
	char * temp;
	int id;
	Tower * tIndex;
	Tower * tEnd = towers + (towers_size - 1);
	Building * bIndex;
	Building * bEnd = buildings + (buildings_size - 1);
	House * hIndex;
	House * hEnd = houses + (houses_size - 1);

	pid_t childpid;



	printf("Enter engineer's id:\n");
	scanf("%d",&id);

	printf("Enter the date: (dd/mm/yyyy) \n");
	scanf("%ms",&temp);
		date = (char *) malloc(getLength(temp) * sizeof(char));
		strcpy(date,temp);
		free(temp);

		childpid = fork();
		if (childpid == 0){
	for(bIndex = buildings; bIndex <= bEnd; ++bIndex){
		if(bIndex->engineerID == id){
			if(strcmp(bIndex->date,date) == 0){
				printBuilding(bIndex);
			}
		}
	}
	for(tIndex = towers; tIndex <= tEnd; ++tIndex){
		if(tIndex->engineerID == id){
			if(strcmp(tIndex->date,date) == 0){
				printTower(tIndex);
			}
		}
	}
	for(hIndex = houses; hIndex <= hEnd; ++hIndex){
		if(hIndex->engineerID == id){
			if(strcmp(hIndex->date,date) == 0){
				printHouse(hIndex);
			}
		}
	}
	}
	free(date);
}

void printBuilding(Building * b){
	printf("--- BUILDING --- \n Modals: \n");
	int * modals;
	int * modalsEnd = b->modals + (b->levels - 1);

	for(modals = b->modals; modals <= modalsEnd; ++modals)
		printf("%d  ",*modals);

	printf("\nLevels: %d\n",b->levels);
	printf("Date of creation: %s\n",b->date);
	printf("Symmetric: %d\n",b->symmetric);
	printf("Period: %d\n",b->period);
}

void printTower(Tower * t){
	printf("--- Tower --- \n Modals: \n");
	int * modals;
	int * modalsEnd = t->modals + (t->levels - 1);

	for(modals = t->modals; modals <= modalsEnd; ++modals)
			printf("%d  ",*modals);

	printf("\nDiameters: \n");
	Diameter * diameterIndex;
	Diameter * diameterEnd = t->diameters + (t->levels - 1);
	int i = 1;
	for(diameterIndex = t->diameters; diameterIndex <= diameterEnd; ++diameterIndex){
		printf("\t Level %d:\n\tSuperior: %d  Inferior: %d\n",i,diameterIndex->superior,diameterIndex->inferior);
		++i;
	}

	printf("\nLevels: %d\n",t->levels);
	printf("Diameters: \n");

	printf("Date of creation: %s\n",t->date);
	printf("Period: %d\n",t->period);
}

void printHouse(House * h){
	printf("--- House --- \nModal: %d\n",h->modals);
	printf("Date of creation: %s\n",h->date);
	printf("Period: %d\n",h->period);
	printf("Roof: %s\n",h->roof);
}

void printHRReport(){
	char * startDate;
	char * temp;
	char * endDate;
	Engineer * eIndex;
	Engineer * eEnd = engineers + (engineers_size - 1);
	Building * bIndex;
	Building * bEnd = buildings + (buildings_size - 1);
	Tower * tIndex;
	Tower * tEnd = towers + (towers_size - 1);
	House * hIndex;
	House * hEnd = houses + (houses_size - 1);

	printf("Enter starting date: (dd/mm/yyyy) \n");
		scanf("%ms",&temp);
			startDate = (char *) malloc(getLength(temp) * sizeof(char));
			strcpy(startDate,temp);
			free(temp);

	printf("Enter end date: (dd/mm/yyyy) \n");
		scanf("%ms",&temp);
			endDate = (char *) malloc(getLength(temp) * sizeof(char));
			strcpy(endDate,temp);
			free(temp);

	for(eIndex = engineers; eIndex <= eEnd; ++eIndex){
		int cont = 0;

		printf("--- Engineer %s %s ---\n",eIndex->name,eIndex->surname);
		printf("Date of Birth: %s \n",eIndex->dob);
		printf("Starting Date: %s \n",eIndex->startingDate);
		printf("Salary: %d \n", eIndex->salary);
		printf("Position: %s \n", eIndex->position);

		for(bIndex = buildings; bIndex <= bEnd; ++bIndex){
			if(bIndex->engineerID == eIndex->id){
				if(inRange(startDate,endDate,bIndex->date)){
					printBuilding(bIndex);
					cont++;
				}
			}
		}

		for(tIndex = towers; tIndex <= tEnd; ++tIndex){
			if(tIndex->engineerID == eIndex->id){
				if(inRange(startDate,endDate,tIndex->date)){
					printTower(tIndex);
					cont++;
				}
			}
		}

		for(hIndex = houses; hIndex <= hEnd; ++hIndex){
			if(hIndex->engineerID == eIndex->id){
				if(inRange(startDate,endDate,hIndex->date)){
					printHouse(hIndex);
					cont++;
				}
			}
		}
		printf("Total structures from %s and %s : %d\n\n",startDate,endDate,cont);
	}
	free(startDate);
	free(endDate);
}

int inRange(char * start, char * end, char * date){
	char * startDay = (char *) malloc(3 * sizeof(char));
	char * startMonth = (char *) malloc(3 * sizeof(char));
	char * startYear = (char *) malloc(3 * sizeof(char));

	char * endDay = (char *) malloc(3 * sizeof(char));
	char * endMonth = (char *) malloc(3 * sizeof(char));
	char * endYear = (char *) malloc(3 * sizeof(char));

	char * dateDay = (char *) malloc(3 * sizeof(char));
	char * dateMonth = (char *) malloc(3 * sizeof(char));
	char * dateYear = (char *) malloc(3 * sizeof(char));

	strncpy(startDay, start, 2);
	strncpy(startMonth, start + 3, 2);
	strncpy(startYear, start + 5, 2);

	strncpy(endDay, end, 2);
	strncpy(endMonth, end + 3, 2);
	strncpy(endYear, end + 5, 2);

	strncpy(dateDay, date, 2);
	strncpy(dateMonth, date + 3, 2);
	strncpy(dateYear, date + 5, 2);

	if(atoi(dateYear) >= atoi(startYear) && atoi(dateYear) <= atoi(endYear)){
		if(atoi(dateYear) == atoi(startYear) && atoi(dateYear) == atoi(endYear)){
			if(atoi(dateMonth) >= atoi(startMonth) && atoi(dateMonth) <= atoi(endMonth)){
				if(atoi(dateMonth) == atoi(startMonth) && atoi(dateMonth) == atoi(endMonth)){
					if(atoi(dateDay) >= atoi(startDay) && atoi(dateDay) <= atoi(endDay)){
						free(startDay);
						free(startMonth);
						free(startYear);
						free(endDay);
						free(endMonth);
						free(endYear);
						free(dateDay);
						free(dateMonth);
						free(dateYear);
						return 1;
					}
			}
				else{
					free(startDay);
					free(startMonth);
					free(startYear);
					free(endDay);
					free(endMonth);
					free(endYear);
					free(dateDay);
					free(dateMonth);
					free(dateYear);
					return 1;
				}
		}
		}
		else{
			free(startDay);
			free(startMonth);
			free(startYear);
			free(endDay);
			free(endMonth);
			free(endYear);
			free(dateDay);
			free(dateMonth);
			free(dateYear);
			return 1;
		}
	}

	free(startDay);
	free(startMonth);
	free(startYear);
	free(endDay);
	free(endMonth);
	free(endYear);
	free(dateDay);
	free(dateMonth);
	free(dateYear);


return 0;
}
