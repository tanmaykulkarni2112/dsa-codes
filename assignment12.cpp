#include<iostream>
#include<fstream>
using namespace std;

class student
{
public:
int roll;
char name[50];
char div[2];
char add[100];
void setdata()
{
cout<<"enter roll no:"<<endl;
cin>>roll;
cout<<"enter name:"<<endl;
cin>>name;
cout<<"Enter division:"<<endl;
cin>>div;
cout<<"enter address"<<endl;
cin>>add;

}

void showdata(){
cout<<"rollno:"<<roll<<endl;
cout<<"name:"<<name<<endl;
cout<<"division of stud:"<<div<<endl;
cout<<"address of stud:"<<add<<endl;
}

};

void writedata(){
ofstream outfile;
outfile.open("student.dat",ios::binary |ios::app);
student obj;
obj.setdata();
outfile.write((char*)&obj,sizeof(obj));
outfile.close();
}

void display(){
ifstream infile;
infile.open("student.dat",ios::binary);
student obj;
while(infile.read((char*)&obj,sizeof(obj))){
obj.showdata();

}
infile.close();
}

int search(int n){
ifstream infile;
bool flag=false;
infile.open("student.dat",ios::binary);
student obj;
while(infile.read((char*)&obj,sizeof(obj))){
if(obj.roll==n){
flag=true;
obj.showdata();
return 1;
break;
}
}
if(flag==false){
cout<<"record of roll no"<<n<<"not found in file"<<endl;
return 0;
}
infile.close();
}
void delete_data(int n){
student obj;
ifstream infile;
infile.open("student.dat",ios::in);
ofstream outfile;
outfile.open("temp.dat",ios::out| ios::out);
int a=search(n);
if(a==1){
while(infile.read((char*)&obj,sizeof(obj))){
if(obj.roll!=n){
outfile.write((char*)&obj,sizeof(obj));
}
}
cout<<"Record Deleted";
infile.close();
outfile.close();
remove("student.dat");
rename("temp.dat","student.dat");

}
else{
cout<<"Entered student is not present"<<endl;
}
}
int main(){
int choice;
do{
int ch;
cout<<"1.Add data"<<endl;
cout<<"2.Show data"<<endl;
cout<<"3.Search data"<<endl;
cout<<"4.delete data"<<endl;

cout<<"\nEnter your choice";
cin>>ch;
switch(ch){
case 1:cout<<"Enter no of records:";
int n;
cin>>n;
for(int i=0;i<n;i++){
writedata();
}
break;
case 2:
cout<<"\nList of records";
display();
break;

case 3:
cout<<"Enter roll no to search "<<endl;
int j;
cin>>j;
search(j);
break;


case 4:
cout<<"Enter noto delete";
int k;
cin>>k;

delete_data(k);
break;
}
cout<<"\nDo you want to continue?(1/0)";
cin>>choice;
}while(choice!=0);
return 0;
}
