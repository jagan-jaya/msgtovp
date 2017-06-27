#include <iostream>
#include <fstream>
#include<direct.h>  
#include<stdlib.h>
#include<conio.h>
#include<string>
#include<sstream>
#include<vector>
#include<ctime>
using namespace std;
template<class T>
string to_string(T i){
	stringstream ss;
	ss<<i;
	return ss.str();
}
string gettime(){
	time_t t = time(0);   
    struct tm * now = localtime( & t );
    string s="";
    s+=to_string(now->tm_mday)+'/'+to_string(now->tm_mon + 1)+'/'+to_string(now->tm_year + 1900) + '_'+to_string(now->tm_hour)+':'+to_string(now->tm_min)+':'+to_string(now->tm_sec);
    return s;
}
string getpass(const char *prompt, bool show_asterisk=true)
{
  const char BACKSPACE=8;
  const char RETURN=13;
  string password;
  unsigned char ch=0;

  cout <<prompt<<endl;

  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else if(ch==0 || ch==224) // handle escape sequences
         {
             getch(); // ignore non printable chars
             continue;
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}

string removetokens(string s){
	string ss="";
	int n=s.size();
	for(int i=0;i<n;i++) if(s[i]>='0'&&s[i]<='9') ss+=s[i];
	return ss;
}
void createfile(string path,string message){
	ofstream newfile(path.c_str(),fstream::out);
	if(message.size()>0) newfile<<message<<endl;
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
	createfile(name+"//inbox//inbox.txt","");
	createfile(name+"//sent//sent.txt","");
	return true;
}
bool Register(){
string username,password;
cout<<"Enter username:";
cin>>username;
password=getpass("Enter Password:",true);
return registerUser(username,password);
}
int showDetails(string path,int opt){
	fstream details(path.c_str());
	string msg;
	int count=1;
	for(int i=0;i<80;i++) cout<<"-";
	cout<<endl;
	while(getline(details,msg)){
		if(opt) cout<<"|\t"<<count++<<" "<<msg<<"\t|"<<endl;
		else cout<<msg<<endl;
	}
	if(opt&&count==1) cout<<"|\tNo messages to View\t|\n";
	for(int i=0;i<80;i++) cout<<"-";
	cout<<endl;
	return count-1;
}
vector<string> showmsg(string path,int n){
	fstream details(path.c_str());
	string msg;
	int count=1;
	while(getline(details,msg)){
		if(count==n){
			return split(msg);
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
string getinputmessage(){
	cout<<"Enter Message:";
		cin.ignore(1,'\n');
		char * msg=new char[100000];
		scanf("%[^\t]s",msg);
		return to_string(msg);
}
void getMailDetails(string username){
	system("cls");
	cout<<"Enter recipient:";
	string recipient;
	cin>>recipient;
	if(checkUser(recipient,"checkuser")){		
		sendMail(username,recipient,getinputmessage());
		cout<<"\nYour Message has been Successfully Sent!!\n";
		}
}
void forwardMail(string username,string message){
	system("cls");
	cout<<"Enter recipient:";
	string recipient;
	cin>>recipient;
	if(checkUser(recipient,"checkuser")){		
		sendMail(username,recipient,message);
		cout<<"\nYour Message has been Successfully Forwarded!!\n";
		}
}
string getMessageContent(string path){
	fstream fc(path.c_str());
	string content="",temp;
	while(getline(fc,temp)) content+=temp+"\n";
	fc.close();
	return content;
}
void showMsg(string username,string option){

				while(1){
				system("cls");
				cout<<username<<"/"<<option<<endl;
				int tot=showDetails(username+"//"+option+"//"+option+".txt",1);
				int msgno;
				cout<<"Press 0 to Go Home\nEnter the Message No to view Message:";
				cin>>msgno;
				if(msgno==0){
				system("cls"); break;
				}else if(msgno>tot){
					cout<<"Invalid Input\n try Valid input";
					continue;
				}
				while(1){
					string sender=username,receiver,timenow;
					vector<string> details=showmsg(username+"//"+option+"//"+option+".txt",msgno);
					receiver=details[0];
					timenow=removetokens(details[1]);
					system("cls");
					if(option.compare("inbox")==0) cout<<"Message from ";
					else cout<<"Mailed to ";
					cout<<receiver<<" on "<<details[1]<<endl;					
					showDetails(username+"//"+option+"//"+receiver+timenow+".txt",0);
					int choice;
					cout<<"1.Reply\n2.forward\n3.Delete\n4.Back\n";
					cin>>choice;
					if(choice==1){
						sendMail(sender,receiver,getinputmessage()); break;
					}else if(choice==2){
						forwardMail(sender,getMessageContent(username+"//"+option+"//"+receiver+timenow+".txt")); break;
					}else if(choice==3){
						remove((username+"//"+option+"//"+receiver+timenow+".txt").c_str());
						removeline(username+"//"+option+"//"+option+".txt",details[1]);
						cout<<"Message Deleted\n";
						break;
					}else break;
				}
			}
}
int main(){
	cout<<"1.Login\n2.Register\n";
	int choice;
	cin>>choice;
	system("cls");
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
		password=getpass("Enter Password:",true);
		if(checkUser(username,password)){
			cout<<"Login Success";
			system("cls");
			while(1){
			cout<<endl<<"Welcome "<<username<<"\n1.Inbox\n2.Sent Mail\n3.Compose\n4.Logout";
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
