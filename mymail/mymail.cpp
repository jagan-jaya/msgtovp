#include <iostream>
#include <fstream>
#include<direct.h>  
#include<string>
#include<sstream>
#include<vector>
#include<ctime>
using namespace std;
string to_string(int i){
	stringstream ss;
	ss<<i;
	return ss.str();
}
string gettime(){
	time_t t = time(0);   
    struct tm * now = localtime( & t );
    string s="";
    s+=to_string(now->tm_year + 1900) +'-' +to_string(now->tm_mon + 1)+ '-'+to_string(now->tm_mday)+'_'+to_string(now->tm_hour)+':'+to_string(now->tm_min)+':'+to_string(now->tm_sec);
    return s;
}
string removetokens(string s){
	string ss="";
	int n=s.size();
	for(int i=0;i<n;i++) if(s[i]>='0'&&s[i]<='9') ss+=s[i];
	return ss;
}
void createfile(string path,string message){
	ofstream newfile(path.c_str(),fstream::out);
	newfile<<message<<endl;
	newfile.close();
}
void appendfile(string path,string message){
	ofstream newfile(path.c_str(),fstream::app);
	newfile<<message<<endl;
	newfile.close();
}
vector<string> split(string s){
	std::istringstream iss(s);
	vector<string> ss;
	string tok;
	while(iss&&getline(iss,tok,' '))
	ss.push_back(tok);	
	return ss;
}
bool checkUser(string newname,string option){
	fstream checkfile("users.txt");
	string detail;
	while(getline(checkfile,detail)){
			vector<string> name=split(detail);
			if(name[0].compare(newname)==0){
				checkfile.close();
				if(option.compare("checkuser")!=0){
					if(name[1].compare(option)==0) return true;
					else return false;
				}
				
			 return true;
		}
	}
	checkfile.close();
	return false;
	
}

bool registerUser(string name,string password){
	if(checkUser(name,"checkuser")) return false;
	string inboxname=name+"//"+"inbox",sentname=name+"//"+"sent";
	mkdir(name.c_str());
	mkdir(inboxname.c_str());
	mkdir(sentname.c_str());
	appendfile("users.txt",name+" "+password);
	createfile(name+"//inbox//inbox.txt","welcome "+gettime());
	createfile(name+"//sent//sent.txt","Hello World "+gettime());
	return true;
}
bool Register(){
string username,password;
cout<<"Enter username:";
cin>>username;
cout<<"Enter Password:";
cin>>password;
return registerUser(username,password);
}
void showDetails(string path){
	fstream details(path.c_str());
	string msg;
	int count=1;
	for(int i=0;i<50;i++) cout<<"-";
	cout<<endl;
	while(getline(details,msg)){
		cout<<"|\t"<<count++<<" "<<msg<<"\t|"<<endl;
	}
	for(int i=0;i<50;i++) cout<<"-";
	cout<<endl;
}
string showmsg(string path,int n){
	fstream details(path.c_str());
	string msg;
	int count=1;
	while(getline(details,msg)){
		if(count==n){
			vector<string> msgfile=split(msg);
			return msgfile[0]+removetokens(msgfile[1]);
		}count++;
	}
}
void removeline(string path,string time){
	fstream ss(path.c_str());
	ofstream temp("temp.txt");
	string line;
	 while(getline(ss,line)){
	 	if(line.find(time.c_str())<line.length()) continue;
		 else temp<<line<<endl; 
}
temp.close();
ss.close();
remove(path.c_str());
rename("temp.txt",path.c_str());
}
void sendMail(string sender,string receiver,string message){
	string time=gettime();
	appendfile(sender+"//sent//sent.txt",receiver+" "+time);
	appendfile(receiver+"//inbox//inbox.txt",sender+" "+time);
	createfile(sender+"//sent//"+receiver+removetokens(time)+".txt",message);
	createfile(receiver+"//inbox//"+sender+removetokens(time)+".txt",message);
}
void getMailDetails(string username){
	cout<<"Enter recipient:";
	string recipient;
	cin>>recipient;
	if(checkUser(recipient,"checkuser")){
		string message;
		cout<<"Enter Message";
		cin.ignore(1,'\n');
		getline(cin,message);
		sendMail(username,recipient,message);
		cout<<"\nYour Message has been Successfully Sent!!\n";
		}
}
void showMsg(string username,string option){
	showDetails(username+"//"+option+"//"+option+".txt");
				while(1){
				int msgno;
				cout<<"Press 0 to Exit\nEnter the Message No to view Message:";
				cin>>msgno;
				if(msgno==0) break;
				showDetails(username+"//"+option+"//"+showmsg(username+"//"+option+"//"+option+".txt",msgno)+".txt");
			}
}
int main(){
	cout<<"1.Login\n2.Register\n";
	int choice;
	cin>>choice;
	if(choice-1){                 
		  while(1){
		  	if(Register()){
		   	cout<<"registration successful\n";
		   	break;
			}
		   else cout<<"registration failed!\nusername already exists!\nTry another username!\n\n\n";
		}
	}
	else{
		string username,password;
		cout<<"Enter username:";
		cin>>username;
		cout<<"Enter Password:";
		cin>>password;
		if(checkUser(username,password)){
			cout<<"Login Success";
			while(1){
			cout<<endl<<"1.Inbox\n2.Sent Mail\n3.Compose\n4.Exit";
			cin>>choice;
			if(choice==1){
				showMsg(username,"inbox");
			}else if(choice==2){
				showMsg(username,"sent");
			}else if(choice==3){
				getMailDetails(username);
			}else break;
		}
		}
		else cout<<"Invalid Username or Password";
	}
return 0;
}
