#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
	ifstream source(filename.c_str());
	string x;
	char format[] = "%[^:]: %f %f %f";
	float y;
	float z;
	float a;
	float sum = 0;
	char name[100];	
	while (getline(source,x)){
		sscanf(x.c_str(),format,name,&y,&z,&a);
		sum = y+z+a;
		scores.push_back(sum);
		names.push_back(name);
		grades.push_back(score2grade(sum));
	}	
	source.close();
}
	
void getCommand(string &command,string &key){
	char format[] = "%s %[^\n]";
	char x[100];
	char y[100];
	cout << "Please input your command: ";
	string a;
	getline(cin,a);
	sscanf(a.c_str(),format,x,y);
	command = x;
	key = y;
}

void searchName(vector<string> &names,vector<int> scores,vector<char> grades,string key){
	int count = 0;
	cout << "---------------------------------\n";
	for(unsigned int i = 0;i < names.size();i++){
		if(toUpperStr(key)== toUpperStr(names[i])){
			cout << names[i] << "'s score = " << scores[i] << "\n";
			cout << names[i] << "'s grade = " << grades[i] << "\n";
			count++;
		}
	}
	if(count == 0){
		cout << "Cannot found.\n";
	}
	cout << "---------------------------------\n";
}


void searchGrade(vector<string> &names,vector<int> scores,vector<char> grades,string  key){ 
	int count = 0;
	cout << "---------------------------------\n";
	for(unsigned int i = 0;i < names.size();i++){
		if(key[0] == grades[i]){
			cout << names[i] << " (" << scores[i] << ")\n";
			count++;
		}
	}
	if(count == 0){
		cout << "Cannot found.\n";
	}
	cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
