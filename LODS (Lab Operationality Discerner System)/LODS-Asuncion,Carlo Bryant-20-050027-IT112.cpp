#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
using namespace std;
//Lab Operationality Discerner System
//Carlo Bryant Asuncion BSIT 1B

struct User{
	string id;
	unsigned char mouse, cable, kybrd, mnitr;
};

enum Menu{
	NEW_DATA=1, LOAD_DATA, EXT_PROGRAM 
};

//ID input function and error trapping
void idEnter(char id[], bool& errInput){
bool withDash=false;
	for(int i=0;i<10 && !errInput;i++){
		id[i]=cin.get();
		
		//Input stops when user enters newline
		if(id[i]=='\n'){
			id[i]='\0';
			break;
		}
		if(id[2]==' ' || id[2]=='-') withDash=true;

		//Error trapping if user inputs non-numeric characters
		//That aren't newline nor dash/space at index 2
		else if(cin.fail() || 
		((id[i]<'0'||id[i]>'9')&&id[i]!='\n')){
			errInput=true;
			cin.clear();
			cin.ignore(1000,'\n');
			cout<<"Please enter a valid student number\n"<<endl;
			for(int j=0;j<10;j++) id[i]='\0';
		}
	}
	//When '0' alone is entered, it will labeled as "UNUSED_PC"
	if(id[0]=='0'&&id[1]=='\0'){
		char none[]="UNUSED_PC";
		strcpy_s(id, sizeof(id), none);
	} else if(((strlen(id)>8||strlen(id)<8)&&!withDash&&!errInput)||
	((strlen(id)>9||strlen(id)<9)&&withDash&&!errInput)){
			errInput=true;
			if(strlen(id)>8)cin.ignore(1000,'\n');
			cout<<"Please enter a valid student number\n"<<endl;
	} //Error trapping when input exceeds or is less than the character limit

}
void idFormat(char id[]){

	//A space in index 2/third element will be overwritten with a dash
	if(id[2]==' ') id[2]='-';

	//If user does not input space/dash, this for loop will do it
	else if(id[2]!='-'&&id[2]!='U'){
		for(int j=10;j>2;j--){
			*(id+j)=*(id+j-1);
		} id[2]='-';
	}
}

//Hardware data input function and error trapping
void hardwareErr(char u[], bool& errChar){
	//If user enters more than one character
	if(strlen(u)>1){
		errChar=true;
		cout<<"Please input a valid character\t\t\t\t  ";
	} else {
		//Takes the value of the first character in the array
		switch(*u){
			case 'O':
			case 'o':
				*u='O';
				break;
			case 'X':
			case 'x':
				*u='X';
				break;
			case 'M':
			case 'm':
				*u='M';
				break;
			default:
				errChar=true;
				cout<<"Please input a valid character\t\t\t\t  ";
				//Error trapping when character is none of the above
		}
	}
}
void hardwareEnter(User u[], int i){
	bool errChar=false;
	                    
	for(int j=0;j<4;j++){
		do{	//A character array is dynamically allocated to trap
			//Errors when user enters more than one character
			char *charOpt=new char[10];
			errChar=false;
			
			if(j==0) cout<<"PC ["<<i+1<<"] Mouse status    : ";
			if(j==1) cout<<"PC ["<<i+1<<"] Cable status    : ";
			if(j==2) cout<<"PC ["<<i+1<<"] Keyboard status : ";
			if(j==3) cout<<"PC ["<<i+1<<"] Monitor status  : ";
			
			cin.getline(charOpt, 10);
			
			//Error trapping when user enters beyond the limit
			if(cin.fail()){
				cin.clear();
				cin.ignore(1000, '\n');
				errChar=true;
				cout<<"Please input a valid character\t\t\t\t  ";
			} else hardwareErr(charOpt, errChar);
			
			if((*charOpt=='O' || *charOpt=='X' || *charOpt=='M')&&j<3) 
				cout<<"\t\t\t\t\t\t\t  ";
			
			if(j==0) u[i].mouse=*charOpt;
			if(j==1) u[i].cable=*charOpt;
			if(j==2) u[i].kybrd=*charOpt;
			if(j==3) u[i].mnitr=*charOpt; 	
			
			delete[] charOpt;
		} while(errChar);
	} 									   
}

//Other input functions
void selection1to3(int* option){
	bool errOption=false;
		
	do{	
		if(errOption){
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"  Invalid input :(\t";
		}
		errOption=false;
		cout<<"Indicate your option: ";
		cin>>*option;
		if(cin.fail() || 
		(cin.peek()<'1'||cin.peek()>'3')&&(cin.peek()!='\n') ||
		(*option!=1&&*option!=2&&*option!=3))
		//Error trapping when input is neither 1, 2, or 3
		errOption=true;

	} while(errOption);
}
void filenameInput(char filename[]){
	do{ //Error trapping for file name input
		if(strlen(filename)>24){
			cin.clear();
			cin.ignore(10000, '\n');
			cout<<"\n\tThe character limit is only 24. Please try again.";
		} else if(*filename=='\n') cin.ignore(1); //Prevents input buffering
		cout<<"\n\tEnter the file name: ";
		for(int i=0;i<25;i++){
			filename[i]=cin.get();
			//Stops input when newline is entered by the user
			if(filename[i]=='\n'){
				filename[i]='\0'; 
			break;
				}
			}
	} while(strlen(filename)>24);
	//File extension is concatenated by the program
	char ext[]=".txt";
	strcat_s(filename, sizeof(filename), ext);
}	
void outputMenu(bool& backToMain, int pcQtty, User u[]){
	cout<<"\n\t\t\t\t\tWhat's next?"<<endl;
	cout<<"\t\t\t\t\t[1] SAVE DATA"<<endl;
	cout<<"\t\t\t\t\t[2] BACK TO MAIN MENU"<<endl;
	cout<<"\t\t\t\t\t[3] EXIT PROGRAM"<<endl;
	cout<<"\n\t\t\t";
	int* option=new int;
	selection1to3(option);
	switch(*option){

		case 1:{
		ofstream fout;
		cout<<"\n\t(Recommended file format ";
		cout<<"\"MMDDYY-[TIME IN]-[TIMEOUT]\", e.g.";
		cout<<" 123122-11-2)"; 
		char *filename=new char[25];
		if(cin.peek()=='\n') cin.ignore(1,'\n');
		filenameInput(filename);
		fout.open(filename);
	
		if(fout.is_open()){
			cout<<"\n\tCreating "<<filename<<" file..."<<endl;
			for(int i=0;i<pcQtty;i++){
				fout<<u[i].id<<" "<<u[i].mouse<<" "
				<<u[i].cable<<" "<<u[i].kybrd<<" "<<u[i].mnitr<<endl;
			}
			fout.close();
			cout<<"\tData has been saved! Please restart the program ";
			cout<<"and load the data to check."<<endl;
		} else cout<<"\tSaving failed! Sorry :("<<endl;
		delete[] filename;
		break;
		}

		case 2: backToMain=true; 
		break;
		
		case 3: 
		break;
	} 	delete option;
}
void inputMenu(bool& backToMain, bool& backToLoad){
	cout<<"\n\t\t\t\t\tWhat's next?"<<endl;
	cout<<"\t\t\t\t\t[1] LOAD OTHER DATA"<<endl;
	cout<<"\t\t\t\t\t[2] BACK TO MAIN MENU"<<endl;
	cout<<"\t\t\t\t\t[3] EXIT PROGRAM"<<endl;
	cout<<"\n\t\t\t";
	int* option=new int;
	selection1to3(option);
	switch(*option){
		case 1:{
		backToLoad=true;
		system("cls");
		break;
		}
	
		case 2: backToMain=true; 
		break;
		
		case 3:
		break;
	} delete option;
}

//Text Art function declaration
void mainMenu();
void diagram(User u[]);
void diagramNull();

int main(){
	//PC Quantity
	const unsigned int pcQtty=24; 
	User user[pcQtty];
	
	//Error trapping bool variable
	bool errInput=false;
	//Main menu bool variable
	bool backToMain=false;

	do{
		backToMain=false;
		system("cls"); 
		//Program start
		int* option=new int;
			mainMenu();
			selection1to3(option);
			
		//The value of option is converted to it's respective enum member
		Menu selected=static_cast<Menu>(*option);	
		delete option;
		switch(selected){
			
			case NEW_DATA:{
				cout<<"\t\t\tENTER NEW LAB ROOM DATA"<<endl;
				
				diagramNull();
				char *id=new char[10];
				if(cin.peek()=='\n') cin.ignore(1);
				//Prevents newline input buffering
				for(int i=0;i<pcQtty;i++){
					do{ 
					errInput=false;
					cout<<"Enter Student Number of user in PC ["<<i+1<<"]: ";
					idEnter(id, errInput);
					} while(errInput);
		
					idFormat(id);
					user[i].id=id;

					cout<<"\t\t\t\t\t"<<user[i].id<<"\t  ";
					hardwareEnter(user, i);		
				} delete[] id;

				//Visual diagram of data
				system("cls");
				diagram(user);
				outputMenu(backToMain, pcQtty, user);
			break;
			}	
			
			case LOAD_DATA:{	
				bool backToLoad=false;
				do{	
					backToLoad=false;
					cout<<"\t\t\tLOAD COMPUTER LAB ROOM DATA"<<endl;
					ifstream fin;
					char *filename=new char[25];
					
					for(int k=0;!fin.is_open();k++){
					if(k==0 && cin.peek()=='\n') cin.ignore(1,'\n');
					//Prevents newline input buffering of the first loop

					cout<<"\n\t(Make sure the file is in the same directory as";
					cout<<" the program)";
					filenameInput(filename);
					
					fin.open(filename);
					if(fin.is_open()){
						cout<<"Loading "<<filename<<"...";
						for(int i=0;i<pcQtty;i++){
							fin>>user[i].id>>user[i].mouse>>user[i].cable;
							fin>>user[i].kybrd>>user[i].mnitr;	
						}
					} else cout<<"\tUnable to open "<<filename<<", please check";
							cout<<" properly."<<endl;
					} delete[] filename;
					fin.close();

					//Visual diagram of data
					system("cls");
					diagram(user);
					inputMenu(backToMain, backToLoad);
				} while(backToLoad);
			break;
			}
		
			case EXT_PROGRAM: 
				cout<<"\t\t\tGOODBYE LODS :D"<<endl;
			break;
			}
	} while(backToMain);
	
	return 0;
} 

//Text Art
void mainMenu(){
cout<<"\t\x1b[31m  W E L C O M E\x1b[0m"<<endl; 	
cout<<"...................................."<<endl; 
cout<<"888       ,88~-_   888~-_   ,d88~~\\\tSelect an Option"<<endl; 
cout<<"888      d888   \\  888   \\  8888    "<<endl;
cout<<"888     88888    | 888    | `Y88b   \t[";
cout<<static_cast<int>(NEW_DATA)<<"] NEW DATA"<<endl;
cout<<"888     88888    | 888    |  `Y88b, \t[";
cout<<static_cast<int>(LOAD_DATA)<<"] LOAD DATA"<<endl;
cout<<"888      Y888   /  888   /     8888 \t[";
cout<<static_cast<int>(EXT_PROGRAM)<<"] EXIT PROGRAM"<<endl;
cout<<"888____   `88_-~   888_-~   \\__88P' \n"<<endl;
cout<<"\t\t\t";
}
void diagramNull(){
 cout<<".____________________________________________.            .____________________________________________.\n"; 
 cout<<"|  <_____>    <_____>    <_____>    <_____>  |            |  <_____>    <_____>    <_____>    <_____>  |\n"; 
 cout<<"| :=======:  :=======:  :=======:  :=======: |            | :=======:  :=======:  :=======:  :=======: |\n"; 
 cout<<"|    [1]        [2]        [3]        [4]    |            |    [5]        [6]        [7]        [8]    |\n"; 
 cout<<"|____________________________________________|            |____________________________________________|\n"; 
 cout<<"\n\n\n";
 cout<<".____________________________________________.            .____________________________________________.\n"; 
 cout<<"|  <_____>    <_____>    <_____>    <_____>  |            |  <_____>    <_____>    <_____>    <_____>  |\n";  
 cout<<"| :=======:  :=======:  :=======:  :=======: |            | :=======:  :=======:  :=======:  :=======: |\n";
 cout<<"|    [9]       [10]       [11]       [12]    |            |   [13]       [14]       [15]       [16]    |\n"; 
 cout<<"|____________________________________________|            |____________________________________________|\n"; 
 cout<<"\n\n\n"; 
 cout<<".____________________________________________.            .____________________________________________.\n"; 
 cout<<"|  <_____>    <_____>    <_____>    <_____>  |            |  <_____>    <_____>    <_____>    <_____>  |\n";  
 cout<<"| :=======:  :=======:  :=======:  :=======: |            | :=======:  :=======:  :=======:  :=======: |\n";  
 cout<<"|   [17]       [18]       [19]       [20]    |            |   [21]       [22]       [23]       [24]    |\n"; 
 cout<<"|____________________________________________|            |____________________________________________|\n";
 cout<<"\n\t\t\t\t | Mouse | Cable | Keyboard | Monitor |\n";
 cout<<"\t\t\t     O: Operational,   M: Missing,   X: Malfunction\n";
 cout<<"\n\n"; 
}
void diagram(User u[]){
 cout<<".____________________________________________.            .____________________________________________.\n"; 
 cout<<"|  <_____>    <_____>    <_____>    <_____>  |            |  <_____>    <_____>    <_____>    <_____>  |\n"; 
 cout<<"| :=======:  :=======:  :=======:  :=======: |            | :=======:  :=======:  :=======:  :=======: |\n"; 
 cout<<"|    [1]        [2]        [3]        [4]    |            |    [5]        [6]        [7]        [8]    |\n"; 
 cout<<"|____________________________________________|            |____________________________________________|\n"; 
 cout<<"  "<<u[0].id<<"  "<<u[1].id<<"  "<<u[2].id<<"  "<<u[3].id<<"                "<<u[4].id<<"  "<<u[5].id<<"  "<<u[6].id<<"  "<<u[7].id<<"  \n"; 
 cout<<"  |"<<u[0].mouse<<"|"<<u[0].cable<<"|"<<u[0].kybrd<<"|"<<u[0].mnitr<<"|  ";
 cout<<"|"<<u[1].mouse<<"|"<<u[1].cable<<"|"<<u[1].kybrd<<"|"<<u[1].mnitr<<"|  |"<<u[2].mouse<<"|"<<u[2].cable<<"|"<<u[2].kybrd<<"|"<<u[2].mnitr<<"|";
 cout<<"  |"<<u[3].mouse<<"|"<<u[3].cable<<"|"<<u[3].kybrd<<"|"<<u[3].mnitr<<"|                |"<<u[4].mouse<<"|"<<u[4].cable<<"|"<<u[4].kybrd<<"|"<<u[4].mnitr<<"|";
 cout<<"  |"<<u[5].mouse<<"|"<<u[5].cable<<"|"<<u[5].kybrd<<"|"<<u[5].mnitr<<"|  |"<<u[6].mouse<<"|"<<u[6].cable<<"|"<<u[6].kybrd<<"|"<<u[6].mnitr<<"|";
 cout<<"  |"<<u[7].mouse<<"|"<<u[7].cable<<"|"<<u[7].kybrd<<"|"<<u[7].mnitr<<"|  \n";
 cout<<"                                                                                                        \n"; 
 cout<<".____________________________________________.            .____________________________________________.\n"; 
 cout<<"|  <_____>    <_____>    <_____>    <_____>  |            |  <_____>    <_____>    <_____>    <_____>  |\n";  
 cout<<"| :=======:  :=======:  :=======:  :=======: |            | :=======:  :=======:  :=======:  :=======: |\n";
 cout<<"|    [9]       [10]       [11]       [12]    |            |   [13]       [14]       [15]       [16]    |\n"; 
 cout<<"|____________________________________________|            |____________________________________________|\n"; 
 cout<<"  "<<u[8].id<<"  "<<u[9].id<<"  "<<u[10].id<<"  "<<u[11].id<<"                "<<u[12].id<<"  "<<u[13].id<<"  "<<u[14].id<<"  "<<u[15].id<<"  \n";   
 cout<<"  |"<<u[8].mouse<<"|"<<u[8].cable<<"|"<<u[8].kybrd<<"|"<<u[8].mnitr<<"|  ";
 cout<<"|"<<u[9].mouse<<"|"<<u[9].cable<<"|"<<u[9].kybrd<<"|"<<u[9].mnitr<<"|  |"<<u[10].mouse<<"|"<<u[10].cable<<"|"<<u[10].kybrd<<"|"<<u[10].mnitr<<"|";
 cout<<"  |"<<u[11].mouse<<"|"<<u[11].cable<<"|"<<u[11].kybrd<<"|"<<u[11].mnitr<<"|                |"<<u[12].mouse<<"|"<<u[12].cable<<"|"<<u[12].kybrd<<"|"<<u[12].mnitr<<"|";
 cout<<"  |"<<u[13].mouse<<"|"<<u[13].cable<<"|"<<u[13].kybrd<<"|"<<u[13].mnitr<<"|  |"<<u[14].mouse<<"|"<<u[14].cable<<"|"<<u[14].kybrd<<"|"<<u[14].mnitr<<"|";
 cout<<"  |"<<u[15].mouse<<"|"<<u[15].cable<<"|"<<u[15].kybrd<<"|"<<u[15].mnitr<<"|  \n";
 cout<<"                                                                                                        \n"; 
 cout<<".____________________________________________.            .____________________________________________.\n"; 
 cout<<"|  <_____>    <_____>    <_____>    <_____>  |            |  <_____>    <_____>    <_____>    <_____>  |\n";  
 cout<<"| :=======:  :=======:  :=======:  :=======: |            | :=======:  :=======:  :=======:  :=======: |\n";  
 cout<<"|   [17]       [18]       [19]       [20]    |            |   [21]       [22]       [23]       [24]    |\n"; 
 cout<<"|____________________________________________|            |____________________________________________|\n";
 cout<<"  "<<u[16].id<<"  "<<u[17].id<<"  "<<u[18].id<<"  "<<u[19].id<<"                "<<u[20].id<<"  "<<u[21].id<<"  "<<u[22].id<<"  "<<u[23].id<<"  \n";
  cout<<"  |"<<u[16].mouse<<"|"<<u[16].cable<<"|"<<u[16].kybrd<<"|"<<u[16].mnitr<<"|  ";
 cout<<"|"<<u[17].mouse<<"|"<<u[17].cable<<"|"<<u[17].kybrd<<"|"<<u[17].mnitr<<"|  |"<<u[18].mouse<<"|"<<u[18].cable<<"|"<<u[18].kybrd<<"|"<<u[18].mnitr<<"|";
 cout<<"  |"<<u[19].mouse<<"|"<<u[19].cable<<"|"<<u[19].kybrd<<"|"<<u[19].mnitr<<"|                |"<<u[20].mouse<<"|"<<u[20].cable<<"|"<<u[20].kybrd<<"|"<<u[20].mnitr<<"|";
 cout<<"  |"<<u[21].mouse<<"|"<<u[21].cable<<"|"<<u[21].kybrd<<"|"<<u[21].mnitr<<"|  |"<<u[22].mouse<<"|"<<u[22].cable<<"|"<<u[22].kybrd<<"|"<<u[22].mnitr<<"|";
 cout<<"  |"<<u[23].mouse<<"|"<<u[23].cable<<"|"<<u[23].kybrd<<"|"<<u[23].mnitr<<"|  \n";
  cout<<"\n\t\t\t\t | Mouse | Cable | Keyboard | Monitor |\n";
 cout<<"\t\t\t     O: Operational,   M: Missing,   X: Malfunction\n";
}

