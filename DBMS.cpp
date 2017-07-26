#include <bits/stdc++.h>
#include <exception>
using namespace std;

string command;
#define coutWidth 15

template <class T>
class cell
{
protected:
	T value;
public:
	cell()
	{
	}
	cell(T x)
	{
		value = x;
	}
	void addValue(T x)
	{
		value = x;
	}
	T getValue()
	{
		return value;
	}
};

template <class T>
class column
{
protected:
	int noOfCells;
	string fieldName;
	vector< cell<T> > v;
	T temp;
	cell<T> tempCell;
public:
	column()
	{
		noOfCells=0;
	}
	column(string a,int b,T value)
	{
		fieldName = a;
		noOfCells=b;
		for (int i = 0; i < b; ++i)
		{
			cell<T> t;
			t.addValue(value);
			v.push_back(t);
		}
	}

	string getFieldName()
	{
		return fieldName;
	}

	void setFieldname(string s)
	{
		fieldName=s;
	}


	void addCell(T value)
	{
		noOfCells++;
		tempCell.addValue(value);
		v.push_back(tempCell);
	}

	void setCell(int y)
	{
		cin>>temp;
		getchar();
		v[y].addValue(temp);
	}

	T getData(int x)
	{
		return v[x].getValue();
	}

	void displayColumn()
	{
		cout<<endl;
		for (int i = 0; i < noOfCells; ++i)
		{
			cout<<v[i].getValue()<<endl;
		}
	}

	void deleteCell(int y)
	{
		v.erase(v.begin()+y-1);
		noOfCells--;
	}

};

class table
{
	int noOfColumn,pos,noOfCells;
	vector<string> name;
	vector<string>::iterator it;
	vector<int> dataType;	//0 - int , 1 - float , 2 - string
	vector< column<int> > v1;
	vector< column<float> > v2;
	vector< column<string> > v3;
	string tableName;
public:
	table()
	{
		noOfColumn=0;
		noOfCells=0;
	}
	table(string a)
	{
		tableName=a;
		noOfColumn=0;
		noOfCells=0;
	}

	int findTotalPos(string s)
	{
		int pos;
		it=find(name.begin(),name.end(),s);
	    if(it!=name.end())
	    {
    	    pos = (it - name.begin());
    	    return pos;
    	}
    	else
    	{
    		return -1;
    	}
	}

	int findPos(string s)
	{
		int temp,temp1;
		it=find(name.begin(),name.end(),s);
	    if(it!=name.end())
	    {
    	    pos = it - name.begin();
    	    temp = dataType[pos];
    	    temp1=0;
    	    for (int i = 0; i < pos; ++i)
    	    {
    	    	if(dataType[i]==temp)
    	    		temp1++;
    	    }
    	    return temp1;
    	}
    	else
    	{
    		return -1;
    	}
	}

	void addColumn(string s,int y)
	{
		int flag = 0;
		for(vector<string>::iterator it = name.begin();it!=name.end();++it){
			if(*it == s){
				flag = 1;
				throw "Column already exists by that name\n";
			}
		}

		if(!flag){
		name.push_back(s);
		dataType.push_back(y);
		noOfColumn++;
		if(y==0)
		{
			column<int> t(s,noOfCells,0);
			v1.push_back(t);
		}
		else if(y==1)
		{
			column<float> t(s,noOfCells,0);
			v2.push_back(t);
		}
		else if(y==2)
		{
			column<string> t(s,noOfCells,"");
			v3.push_back(t);
		}
		}
	}

	void addCell()
	{
		int temp,temp1;
		string s;
		for (int i = 0; i < noOfColumn; ++i)
		{
			s=name[i];
			temp=findTotalPos(s);
			if(findPos(s)!=-1)
			{
				temp1=findPos(s);
    		    if(dataType[temp]==0)
    		    {
    		    	v1[temp1].addCell(0);
    		    }
    		    else if(dataType[temp]==1)
    		    {
    		    	v2[temp1].addCell(0);
    		    }
    		    else if (dataType[temp]==2)
    		    {
    		    	v3[temp1].addCell("");
    		    }
    		}
    		else
    		{
        		cout<<"NOT FOUND"<<endl;
    		}
    	}
    	noOfCells++;
	}

	void setCellValue(string s, int y)
	{
		int temp,temp1;
		temp=findTotalPos(s);
		temp1=findPos(s);
		cout<<endl<<"Enter value for column "<<s<<" record "<<y+1<<endl;
		if(temp!=-1)
		{
    	    if(dataType[temp]==0)
    	    {
    	    	v1[temp1].setCell(y);
    	    }
    	    else if(dataType[temp]==1)
    	    {
    	    	v2[temp1].setCell(y);
    	    }
    	    else if (dataType[temp]==2)
    	    {
    	    	v3[temp1].setCell(y);
    	    }
    	}
    	else
    	{
        	cout<<"NOT FOUND"<<endl;
    	}
	}

	void deleteColumn(string s)
	{
		int temp,temp1;
		temp=findTotalPos(s);
		temp1=findPos(s);
		if(temp!=-1)
		{
			if(dataType[temp]==0)
			{
				v1.erase(v1.begin() + temp1);
			}
			else if(dataType[temp]==1)
			{
				v2.erase(v2.begin() + temp1);
			}
			else if(dataType[temp]==2)
			{
				v3.erase(v3.begin() + temp1);
			}
			name.erase(name.begin() + temp);
			dataType.erase(dataType.begin() + temp);
		}
		else
		{
			cout<<"NOT FOUND"<<endl;
		}
		noOfColumn--;
	}

	void deleteRecord(int y)
	{
		if(y<noOfCells)
		{
			string s;
			int temp,temp1;
			for (int i = 0; i < noOfColumn; ++i)
			{
				s=name[i];
				temp=findTotalPos(s);
				temp1=findPos(s);
				if(temp!=-1)
				{
					if(dataType[temp]==0)
					{
						v1[temp1].deleteCell(y);
					}
					else if(dataType[temp]==1)
					{
						v2[temp1].deleteCell(y);
					}
					else if(dataType[temp]==2)
					{
						v3[temp1].deleteCell(y);
					}
				}
				else
				{
					cout<<"NOT FOUND"<<endl;
				}
			}
			noOfCells--;
		}
		else
		{
			cout<<"Record not added"<<endl;
		}
	}

	void addRecord()
	{
		addCell();
		string s;
		for (int i = 0; i < noOfColumn; ++i)
		{
			s=name[i];
			setCellValue(s,noOfCells-1);
		}
	}

	void displayColumn(string s)
	{
		int temp,temp1;
		temp=findTotalPos(s);
		temp1=findPos(s);
		if(temp!=-1)
		{
			if(dataType[temp]==0)
			{
				v1[temp1].displayColumn();
			}
			else if(dataType[temp]==1)
			{
				v2[temp1].displayColumn();
			}
			else if(dataType[temp]==2)
			{
				v3[temp1].displayColumn();
			}
		}
		else
		{
			cout<<"NOT FOUND"<<endl;
		}
	}

	void displayRecord(int y)
	{
		int temp,temp1;
		for (int i = 0; i < noOfColumn; ++i)
		{
			string s;
			s=name[i];
			temp=findTotalPos(s);
			temp1=findPos(s);
			if(temp!=-1)
			{
				if(dataType[temp]==0)
				{
					cout<<"| ";
					cout.width(coutWidth-2);
					cout<<left<<v1[temp1].getData(y);
				}
				else if(dataType[temp]==1)
				{
					cout<<"| ";
					cout.width(coutWidth-2);
					cout<<left<<v2[temp1].getData(y);
				}
				else if(dataType[temp]==2)
				{
					cout.width(coutWidth);
					cout<<left<<"| "+v3[temp1].getData(y);
				}
			}
			else
			{
				cout<<"NOT FOUND"<<endl;
			}
		}
		cout<<"|"<<endl;
	}

	void displayTable()
	{
		if(noOfCells>0)
		{
			for (int i = 0; i < ((noOfColumn+1)*coutWidth+1); ++i)
			{
				cout<<"-";
			}
			cout<<endl;
			cout.width(coutWidth);
			cout<<left<<"| RecordNo";
			for (int i = 0; i < noOfColumn; ++i)
			{
				cout.width(coutWidth);
				cout<<left<<"| "+name[i];
			}
			cout<<"|"<<endl;
			for (int i = 0; i < ((noOfColumn+1)*coutWidth+1); ++i)
			{
				cout<<"-";
			}
			cout<<endl;
			for (int i = 0; i < noOfCells; ++i)
			{
				cout<<"| ";
				cout.width(coutWidth-2);
				cout<<left<<i+1;
				displayRecord(i);
			}
			for (int i = 0; i < ((noOfColumn+1)*coutWidth+1); ++i)
			{
				cout<<"-";
			}
			cout<<endl;
		}
	}


	string getTableName(){
		return tableName;
	}

};

class Database{
	string databaseName;
	vector<table> tables;
	vector<string> tableNames;
	vector<string>::iterator it;
	int noOfTables;
	char lastEditedBy[50];
	char author[50];
public:

	Database()
	{

	}

	Database(string s)
	{
		databaseName=s;
		noOfTables=0;
	}

	void setLastEditedBy(char name[]){
		strcpy(lastEditedBy,name);
	}

	char* getLastEditedBy(){
		return lastEditedBy;
	}

	void setAuthor(char name[]){
		strcpy(author,name);
	}

	char* getAuthor(){
		return author;
	}

  bool isNull(){
		if(databaseName == ""){
			return true;
		}else return false;
	}

	string getName(){
		return databaseName;
	}

	int findTableIndex(string s)
	{
		int pos;
		it=find(tableNames.begin(),tableNames.end(),s);
	    if(it!=tableNames.end())
	    {
    	    pos = (it - tableNames.begin());
    	    return pos;
    	}
    	else
    	{
    		return -1;
    	}
	}

	void createTable(string s)
	{
		table temp(s);
		int tempNo = findTableIndex(s);
		if(tempNo == -1){
			tables.push_back(temp);
			tableNames.push_back(s);
			noOfTables++;
		}else{
			throw "Table already exists by that name\n";
		}
	}

	void addColumn(string tname,string cname,int dataType)
	{
		int temp;
		temp=findTableIndex(tname);
		if(temp != -1){
			tables[temp].addColumn(cname,dataType);
		}else{
			throw "Table not found\n";
		}
	}

	void addRecordTable(string tname)
	{
		int temp;
		temp=findTableIndex(tname);
		if(temp != -1){
			tables[temp].addRecord();
		}else{
			throw "Table Not Found\n";
		}
	}

	void setCellTable(string tname,string cname,int y)
	{
		int temp;
		temp=findTableIndex(tname);
		tables[temp].setCellValue(cname,y);
	}

	void addEmptyCellTable(string tname)
	{
		int temp;
		temp=findTableIndex(tname);
		tables[temp].addCell();
	}

	void deleteTable(string tname)
	{
		int temp=findTableIndex(tname);
		if(temp != -1){
			tables.erase(tables.begin()+temp);
			tableNames.erase(tableNames.begin()+temp);
		}else{
			throw "Table Not Found\n";
		}
	}

	void deleteColumnTable(string tname,string cname)
	{
		int temp=findTableIndex(tname);
		if(temp != -1){
			tables[temp].deleteColumn(cname);
		}else{
			throw "Table Not Found\n";
		}
	}

	void deleteRecordTable(string tname,int y)
	{
		int temp=findTableIndex(tname);
		if(temp != -1){
			tables[temp].deleteRecord(y);
		}else{
			throw "Record not found\n";
		}
	}

	void display()
	{
		string s;
		cout<<endl<<"Database "<<databaseName<<"\n";
		cout<<"Author: "<<getAuthor()<<endl;
		cout<<"Last Edited By: "<<getLastEditedBy()<<endl;
		for (int i = 0; i < noOfTables; ++i)
		{
			s=tableNames[i];
			cout<<endl<<"Table "<<s<<endl<<endl;
			tables[i].displayTable();
		}
	}

	void display(string tname)
	{
		int temp=findTableIndex(tname);
		if(temp!=-1)
		{
			cout<<endl<<"Table "<<tname<<endl<<endl;
			tables[temp].displayTable();
		}
		else
		{
			throw "Table not found\n";
		}
	}

	void showTables(){
		cout<<"Tables:"<<endl<<endl;
		int flag = 0;
		for(vector<string>::iterator it = tableNames.begin(); it!=tableNames.end();++it){
			cout<<*it<<endl;
			flag = 1;
		}
		if(!flag){
			cout<<"No tables created\n";
		}
	}

};

int databaseNo=0,it1;
std::vector<Database> collection;
Database db;

void writeToFile(Database &db){
	int flag = 0;
	for(std::vector<Database>::iterator it = collection.begin() ; it != collection.end(); ++it){
		if(it->getName() == db.getName()){
			flag = 1;
			throw "Database already exists by that name\n";
		}
	}
	if(!flag){
		collection.push_back(db);
		it1 = collection.size()-1;
	}
}


void findDatabase(string name){
	int x=0,flag=0;
	for(std::vector<Database>::iterator it = collection.begin() ; it != collection.end(); ++it)
	{
		if(it->getName() == name){
			it1=x;
			flag=1;
			break;
		}
		x++;
	}
	if(flag==0)
	{
		throw "Database not found\n";
	}
}

void showDatabases(){
	cout<<"Databases"<<endl<<endl;
	for(std::vector<Database>::iterator it = collection.begin() ; it != collection.end(); ++it){
		cout<<it->getName()<<endl;
	}
}

bool db_selected(){
  if(collection[it1].isNull() == true){
    cout<<"Database Hasn't been selected\n";
    return false;
  }else return true;
}

void listCommands(){
	 //HARDCODE SOME COMMAND LIST HERE
}

void getCommand(string name){
  ifstream infile;
  infile.open(name.c_str());

	if(!infile.is_open()){
		throw "Invalid Command";
	}

  char ch;
  string str;
  while(getline(infile,str,'\0')){
    cout<<str;
  }
  infile.close();
}


//USERS PART STARTS HERE

class Users{
	int id;
	char username[50];
	char password[50];
public:
	Users(){
		strcpy(username,"");
		strcpy(password,"");
	}

	Users(char username[],char password[]){
		id = 1; 
		strcpy(this->username,username);
		strcpy(this->password,password);
	}

	virtual bool writeAccess(){
		return false;
	}

	char* getUsername(){
		return username;
	}

	bool isNull(){
		if(!strcmp(this->username,"")){
			return true;
		}else return false;
	}

	bool authenticate(char username[],char password[]){
		if(!strcmp(this->username,username) && !strcmp(this->password,password)){
			return true;
		}else return false;
	}
};

class Admin:public Users{
public:
	Admin(){

	}

	Admin(char username[],char password[]):Users(username,password){

	}
	bool writeAccess(){
		return true;
	}
};

class Public: public Users{
public:
	Public(){

	}

	Public(char username[],char password[]):Users(username,password){

	}
	bool writeAccess(){
		return false;
	}
};

Users *U;

bool login(char username[],char password[]){
	ifstream infile;
	infile.open("admin.dat");
	Admin A;
	while(infile.read((char*)&A,sizeof(Admin))){
		if(A.authenticate(username,password)){
			Admin* temp = new Admin(A);
			U = temp;
			return true;
		}
	}
	infile.close();
	infile.open("public.dat");
	Public P;
	while(infile.read((char*)&P,sizeof(Public))){
		if(P.authenticate(username,password)){
			Public* temp = new Public(P);
			U = temp;
			return true;
		}
	}
	cout<<"Invalid Username or Password\n";
	infile.close();
	return false;
}

void createAccount(){
	char username[50],password[50];
	int flag = 0;
	do{
		flag = 0;
		cout<<"Choose Username: ";
		cin>>username;
		Admin A;
		ifstream infile;
		infile.open("admin.dat");
		while(infile.read((char*)&A,sizeof(Admin))){
			if(!strcmp(A.getUsername(),username)){
				flag = 1;
				cout<<"Username has already been taken\n"<<endl;
				break;
			}
		}
		infile.close();
		if(flag == 0){
			Public P;
			infile.open("public.dat");
			while(infile.read((char*)&P,sizeof(Public))){
				if(!strcmp(P.getUsername(),username)){
					flag = 1;
					cout<<"Username has already been taken\n"<<endl;
					break;
				}
			}
			infile.close();
		}
	}while(flag);
	cout<<"Choose Password: ";
	cin>>password;
	string secure_key = "6789";
	string key;
	cout<<"Enter Security Key (Enter 0 if not Admin): ";
	cin>>key;
	int ch;
	if(key == secure_key){
		ch = 1;
	}else{
		ch = 2;
	}
	switch(ch){
		case 1:
		{
			Admin A(username,password);
			ofstream outfile;
			outfile.open("admin.dat",ios::app);
			outfile.write((char*)&A,sizeof(Admin));
			outfile.close();
			cout<<"Admin Account Successfully Created\n";
		}
		break;
		case 2:
		{
			Public P(username,password);
			ofstream outfile;
			outfile.open("public.dat",ios::app);
			outfile.write((char*)&P,sizeof(Public));
			outfile.close();
			cout<<"Public Account Successfully Created\n";
		}
		break;
	}
}

//END OF USERS PART

int main(int argc, char const *argv[])
{

  string command;
	bool logged_in = false;
	do{

		system("clear");

	while(!logged_in){
		int ch;
		cout<<"1.Login\n2.Create Account\n3.Exit\nEnter choice: ";
		cin>>ch;
		switch(ch){
			case 1:
			{
				char username[50],password[50];
				cout<<"Username: ";
				cin>>username;
				cout<<"Password: ";
				cin>>password;
				cin.ignore(1);
				if(login(username,password) == true){
					cout<<"-----------------------------\n";
					cout<<"DolphinDB v.1.0.1\n";
					cout<<"Logged in as "<<U->getUsername()<<endl;
					if(U->writeAccess()){
						cout<<"Auth Level: Admin\n";
					}else{
						cout<<"Auth Level: Public\n";
					}
					cout<<"-----------------------------\n";
					logged_in = true;
				}
			}
			break;
			case 2:
			{
				createAccount();
			}
			break;
			case 3:
			{
				exit(0);
			}
			break;
		}
	}

  do{
		cout<<">>>";
    getline(cin, command);

		try{
		  if(command.substr(0,6) == "create"){
				if(!U->writeAccess()){
					cout<<"ERR: NOT PERMITTED\n";
					continue;
				}
		    command = command.substr(7,command.length());

		    if(command.substr(0,8) == "database"){
					//create database <database-name>
		      command = command.substr(9,command.length());
		      string name = command;
		      Database db_temp(name);
		      //db = db_temp;
					try{
						writeToFile(db_temp);
						cout<<"Creating new database...\nDatabase Created..\n";
						collection[it1].setAuthor(U->getUsername());
						collection[it1].setLastEditedBy(U->getUsername());
					}catch(const char* str){
						cout<<"ERR: "<<str;
					}
		    }else if(command.substr(0,5) == "table"){
					//create table <table-name>
		      command = command.substr(6,command.length());
		      if(db_selected()){
		        string name = command;
						try{
		        				collection[it1].createTable(name);
							cout<<"Creating Table...\nTable Created Successfully\n";
							collection[it1].setLastEditedBy(U->getUsername());
						}catch(const char* str){
							cout<<str;
						}
		      }
		    }else{
		    	cout<<"ERR: Wrong command"<<endl;
		    }
		  }else if(command.substr(0,3) == "use"){
				//use <database-name>
		    command = command.substr(4,command.length());
		    string name = command;
				try{
						findDatabase(name);
						if(db_selected()){
						cout<<"Switched to database "<<name<<endl;
					}
				}catch(const char* str){
					cout<<"ERR: "<<str;
				}
		    //FIND A DATABASE FROM THE FILE AND ATTACH IT TO DB
		  }else if(command.substr(0,6) == "insert"){
				if(!U->writeAccess()){
					cout<<"ERR: NOT PERMITTED\n";
					continue;
				}
		    //insert column <table_name> <type(int,float,string)> <column_name>
		    command = command.substr(7,command.length());

		    if(command.substr(0,6) == "column"){
		      command = command.substr(7,command.length());

		      int pos = command.find(" ");
					if(pos == string::npos){
						throw "Invalid Command";
					}

		      string tname = command.substr(0,pos);
		      command = command.substr(pos+1,command.length());

		      pos = command.find(" ");
					if(pos == string::npos){
						throw "Invalid Command Format\n";
					}
		      string type = command.substr(0,pos);
		      command = command.substr(pos+1,command.length());
		      string name = command;

					if(name.find(" ") != string::npos || name == ""){
						throw "Invalid Column name\nNo spaces allowed and Column Name can't be empty.\n";
					}

		      int type_int = -1;

		      if(type == "int"){
		        type_int = 0;
		      }else if(type == "float"){
		        type_int = 1;
		      }else if(type == "string"){
		        type_int = 2;
		      }

		      if(db_selected()){
						try{
		        				collection[it1].addColumn(tname,name,type_int);
		        				cout<<"Generating column...\nColumn created Successfully\n";
							collection[it1].setLastEditedBy(U->getUsername());
						}catch(const char* str){
							cout<<"ERR: "<<str;
						}
		      }
				}else{

				}
			}else if(command.substr(0,10) == "add record"){
					//add record <table-name> [null]
					command = command.substr(11,command.length());
					cout<<"Trying to add...\n";
					size_t pos = command.find(" ");
					string name;
					if(pos!=string::npos){
						//DEBUG HERE
						name = command.substr(0,pos);
						command = command.substr(pos+1,command.length());
						if(command == "null"){
							collection[it1].addEmptyCellTable(name);
							cout<<"Added New Record...\nSet to NULL\n";
							collection[it1].setLastEditedBy(U->getUsername());
						}
					}else {
						name = command;
						try{
							collection[it1].addRecordTable(name);
							cout<<"Added New Record\n";
							collection[it1].setLastEditedBy(U->getUsername());
						}catch(const char* str){
							cout<<"ERR: "<<str;
						}
					}
			}else if(command.substr(0,6) == "delete"){
				command = command.substr(7,command.length());
				if(command.substr(0,6) == "record"){
					//delete record <table-name>
					command = command.substr(7,command.length());
					string name = command;
					int x;
					cout<<"Enter the ID of the record: ";
					cin>>x;
					getchar();
					try{
						collection[it1].deleteRecordTable(name,x);
						collection[it1].setLastEditedBy(U->getUsername());
					}catch(const char* str){
						cout<<"ERR: "<<str;
					}
				}else if(command.substr(0,6) == "column"){
					if(!U->writeAccess()){
						cout<<"ERR: NOT PERMITTED\n";
						continue;
					}
					//delete column <table-name> <column-name>
					command = command.substr(7,command.length());
					size_t pos = command.find(" ");
					string tname = command.substr(0,pos);
					string cname = command.substr(pos+1,command.length());
					try{
						collection[it1].deleteColumnTable(tname,cname);
						cout<<"Column "<<cname<<" successfully deleted\n";
						collection[it1].setLastEditedBy(U->getUsername());
					}catch(const char* str){
						cout<<"ERR: "<<str;
					}
				}else if(command.length() != 0){
					if(!U->writeAccess()){
						cout<<"ERR: NOT PERMITTED\n";
						continue;
					}
					//delete <table-name>
					string name = command;
					try{
						collection[it1].deleteTable(name);
						cout<<"Table has been deleted...\n";
						collection[it1].setLastEditedBy(U->getUsername());
					}catch(const char* str){
						cout<<"ERR: "<<str<<endl;
					}
				}
			}else if(command.substr(0,4) == "show"){
				if(command.length() == 4){
					collection[it1].display();
				}else{
					command = command.substr(5,command.length());
					if(command.substr(0,9) == "databases"){
						//show databases
						showDatabases();
					}else if(command.substr(0,6) == "tables"){
						collection[it1].showTables();
					}else if(command.substr(0,5) == "table"){
						//show <table-name>
						command = command.substr(6,command.length());
						string tname = command;
						try{
							collection[it1].display(tname);
						}catch(const char* str){
							cout<<"ERR: "<<str;
						}
					}
				}
			}else if(command.substr(0,4) == "help"){
				if(command.length() == 4){
					getCommand(command);
				}else{
					command = command.substr(5,command.length());
					string name = command;
					try{
						getCommand(name);
					}catch(const char* str){
						cout<<"ERR: "<<str<<endl;
					}
				}
			}else if(command.substr(0,4) == "exit"){
				// rewriteToFile(db);
				logged_in = false;
			}
			else
			{
				cout<<"ERR: Incomplete/Invalid command"<<endl;
			}
		}catch(exception &e){
			cout<<"ERR: Incomplete/Invalid Command\n";
		}
		catch(const char* str){
			cout<<str;
		}
	}while(logged_in);
}while(1);
	return 0;
}
