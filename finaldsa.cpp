#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>

using namespace std;

void mainPage(string);
void homePage(string);
void searchContact();
void deleteContact();
int getCount();
void updateContact();

struct contact{
  string contactName;
  string mobileNumber;
  int month;
  int year;
};

string welcomeName="";

enum doesPasswordMatch {YES, NO, NILL};
doesPasswordMatch dpm = NILL;

void header(string generalmsg){
  cout<<"------------------------------------";
  cout<<"\n\t PHONE BOOK PROGRAM";
  cout<<"\n------------------------------------";
  cout<<"\n\n"<<generalmsg;
}

int doesUserExists(string userid,string password){
  string fusername;
  string fuserid;
  string fpswd;
  fstream userStream;
  userStream.open("users.txt",ios::in);
  while(1){
    userStream>>fusername>>fuserid>>fpswd;
    if(userStream.eof()){
      break;
    }
    if(fuserid == userid){
      if(password == fpswd){
        dpm = YES;
      }else{
        dpm = NO;
      }
      welcomeName = fusername;
      userStream.close();
      return 0;
    }
  }
  userStream.close();
  return 1;
}

int doesContactExists(int id, string name, string number){
  fstream userStream;
  userStream.open(welcomeName+".txt",ios::in | ios::out | ios::app);
  int i=0;
  int totalContacts = getCount();
  contact c[totalContacts];
  while(1){
    userStream>>c[i].contactName>>c[i].mobileNumber>>c[i].month>>c[i].year;
    if(userStream.eof()){
      break;
    }
    i++;
  }
  userStream.close();
  if(id==1){
    for(int j=0;j<totalContacts;j++){
      if(c[j].contactName == name){
        return j;
      }
    }
  }else{
    for(int j=0;j<totalContacts;j++){
      if(c[j].mobileNumber == number){
        return j;
      }
    }
  }
  return -1;
}


int getYear(){
  time_t now = time(0);
  tm *ltm = localtime(&now);
  return 1900 + ltm->tm_year;
}

int getMonth(){
  time_t now = time(0);
  tm *ltm = localtime(&now);
  return 1 + ltm->tm_mon;
}

void addContact(){
  int status;
  system("cls");
  contact c;
  string fileName = welcomeName+".txt";
  header("\tAdd a new contact \n");
  cout<<"\n\n ENTER THE NAME : ";
  cin>>c.contactName;
  cout<<"\nENTER THE MOBILE NUMBER : ";
  cin>>c.mobileNumber;
  status = doesContactExists(2, "", c.mobileNumber);
  if(status != -1){
    homePage("\t**SORRY THE NUMBER IS ALREADY SAVED**");
  }else{
    c.month = getMonth();
    c.year = getYear();
    fstream userStream;
    userStream.open(fileName, ios::out | ios::in | ios::app);
    if(!userStream){
      cout<<"\nERROR CREATING FILE";
    }
    userStream<<c.contactName<<"\t"<<c.mobileNumber<<"\t"<<c.month<<"\t"<<c.year<<"\n";
    userStream.close();
    homePage("\tContact Added successfully !");
  }

}
void deleteUser(int id){
  fstream userStream,userStream1;
  userStream.open(welcomeName+".txt",ios::in);
  int i=0;
  int totalContacts = getCount();
  contact c[totalContacts];
  while(1){
      userStream>>c[i].contactName>>c[i].mobileNumber>>c[i].month>>c[i].year;
      if(userStream.eof()){
        break;
      }
      i++;
  }
  userStream.close();
  ifstream File;
  File.open(welcomeName+".txt", ifstream::out | ifstream::trunc );
  File.close();

  userStream1.open(welcomeName+".txt", ios::app);
  for(int i=0;i<totalContacts;i++){
    if(i!=id){
      userStream1<<c[i].contactName<<"\t"<<c[i].mobileNumber<<"\t"<<c[i].month<<"\t"<<c[i].year<<"\n";
    }
  }
  userStream1.close();
}

void deleteByName(){
  string any,userName;
  system("cls");
  header("DELETE BY NAME :)\n");
  cout<<"\nENTER NAME : ";
  cin>>userName;
  int status = doesContactExists(1, userName, "");
  if(status == -1){
    cout<<"\nNO SUCH USER EXISTS";
  }else{
  deleteUser(status);
    cout<<"\nDELETED SUCCESSFULLY";
  }
  cout<<"\n\nPRESS ANY KEY TO GO BACK : ";
  cin>>any;
  deleteContact();
}

void deleteByNumber(){
  string any,mobile;
  system("cls");
  header("DELETE BY MOBILE :)\n");
  cout<<"\nENTER MOBILE : ";
  cin>>mobile;
  int status = doesContactExists(2, "", mobile);
  if(status == -1){
    cout<<"\nNO SUCH USER EXISTS";
  }else{
      deleteUser(status);
      cout<<"\nDELETED SUCCESSFULLY";
  }
  cout<<"\n\nPRESS ANY KEY TO GO BACK : ";
  cin>>any;
  deleteContact();
}

void deleteContact(){
  int userChoice;
  system("cls");
  header("Wishing you a successful Deletion :)\n");
  cout<<"\n1. DELETE BY NAME : ";
  cout<<"\n2. DELETE BY NUMBER : ";
  cout<<"\n3. HOME PAGE";
  cout<<"\n\nENTER CHOICE : ";
  cin>>userChoice;
  switch (userChoice) {
    case 1:
    deleteByName();
    break;
    case 2:
    deleteByNumber();
    break;
    case 3:
    homePage("\tDeleted Your Contact ?");
    break;
    default:
    deleteContact();
  }

}

int getCount(){
  int count = 0;
  fstream userStream;
  contact c;
  userStream.open(welcomeName+".txt",ios::in);
  while(1){
    userStream>>c.contactName>>c.mobileNumber>>c.month>>c.year;
    if(userStream.eof()){
      break;
    }
    count++;
  }
  userStream.close();
  return count;

}
void displayContacts(){
  fstream userStream;
  system("cls");
  header("\tALL CONTACTS LIST\n");
  userStream.open(welcomeName+".txt",ios::in);
  int i=0,flag=0;
  int totalContacts = getCount();
  contact c[totalContacts];
  while(1){
    userStream>>c[i].contactName>>c[i].mobileNumber>>c[i].month>>c[i].year;
    if(userStream.eof()){
      break;
    }
    i++;
  }
  userStream.close();
  if(totalContacts == 0){
    cout<<"\n\t** THERE ARE NO CONTACTS **\n";
  }else{
    cout<<"\n\tLIST OF ALL CONTACTS\n\n";
    for(int j=0;j<totalContacts;j++){
      cout<<"\t"<<j+1<<". "<<c[j].contactName<<"\t"<<c[j].mobileNumber<<"\n";
    }
  }
  cout<<"\n\nPRESS ANY KEY TO GO BACK : ";
  string any;
  cin>>any;
  homePage("Did you see all of your contacts ?");
}
void updateUser(int id, int status, string newName, string newNumber){

  fstream userStream,userStream1;
  userStream.open(welcomeName+".txt",ios::in);
  int i=0;
  int totalContacts = getCount();
  contact c[totalContacts];
  while(1){
      userStream>>c[i].contactName>>c[i].mobileNumber>>c[i].month>>c[i].year;
      if(userStream.eof()){
        break;
      }
      i++;
  }

  userStream.close();
  ifstream File;
  File.open(welcomeName+".txt", ifstream::out | ifstream::trunc );
  File.close();
  userStream1.open(welcomeName+".txt", ios::app);

  if(id==1){
    for(int i=0;i<totalContacts;i++){
      if(i==status){
        c[i].contactName = newName;
      }
        userStream1<<c[i].contactName<<"\t"<<c[i].mobileNumber<<"\t"<<c[i].month<<"\t"<<c[i].year<<"\n";

    }
  }
  else if(id==2){
    for(int i=0;i<totalContacts;i++){
      if(i==status){
        c[i].mobileNumber = newNumber;
      }
        userStream1<<c[i].contactName<<"\t"<<c[i].mobileNumber<<"\t"<<c[i].month<<"\t"<<c[i].year<<"\n";
  }}
  else{
    for(int i=0;i<totalContacts;i++){
      if(i==status){
        c[i].contactName = newName;
        c[i].mobileNumber = newNumber;
      }
        userStream1<<c[i].contactName<<"\t"<<c[i].mobileNumber<<"\t"<<c[i].month<<"\t"<<c[i].year<<"\n";
  }

}
userStream1.close();
}

void updateByName(){
  string any,userName,newName, newNumber;
  int c;
  system("cls");
  header("UPDATE BY NAME :)\n");
  cout<<"\nENTER NAME : ";
  cin>>userName;
  int status = doesContactExists(1, userName, "");
  if(status == -1){
    cout<<"\nNO SUCH USER EXISTS";
  }else{
    cout<<"\n1. CHANGE NAME";
    cout<<"\n2. CHANGE NUMBER";
    cout<<"\n3. CHANGE BOTH";
    cout<<"\n\nENTER CHOICE : ";
    cin>>c;
    switch (c) {
      case 1:
      cout<<"\nENTER NEW NAME : ";
      cin>>newName;
      updateUser(1, status, newName, "");
      break;
      case 2:
      cout<<"\nENTER NEW NUMBER : ";
      cin>>newNumber;
      updateUser(2, status, "", newNumber);
      break;
      case 3:

      cout<<"\nENTER NEW NAME : ";
      cin>>newName;
      cout<<"\nENTER NEW NUMBER : ";
      cin>>newNumber;
      updateUser(3, status, newName, newNumber);
      break;
    }
    cout<<"\nUPDATED SUCCESSFULLY";
  }
  cout<<"\n\nPRESS ANY KEY TO GO BACK : ";
  cin>>any;
  updateContact();
}

void updateByNumber(){
  string any,mobile,newName,newNumber;
  int c;
  system("cls");
  header("UPDATE BY NUMBER :)\n");
  cout<<"\nENTER NUMBER : ";
  cin>>mobile;
  int status = doesContactExists(2, "", mobile);
  if(status == -1){
    cout<<"\nNO SUCH USER EXISTS";
  }else{
    cout<<"\n1. CHANGE NAME";
    cout<<"\n2. CHANGE NUMBER";
    cout<<"\n3. CHANGE BOTH";
    cout<<"\n\nENTER CHOICE : ";
    cin>>c;
    switch (c) {
      case 1:
      cout<<"\nENTER NEW NAME : ";
      cin>>newName;
      updateUser(1, status, newName, "");
      break;
      case 2:
      cout<<"\nENTER NEW NUMBER : ";
      cin>>newNumber;
      updateUser(2, status, "", newNumber);
      break;
      case 3:
      cout<<"\nENTER NEW NAME : ";
      cin>>newName;
      cout<<"\nENTER NEW NUMBER : ";
      cin>>newNumber;
      updateUser(3, status, newName, newNumber);
      break;
    }
    cout<<"\nUPDATED SUCCESSFULLY";
  }
  cout<<"\n\nPRESS ANY KEY TO GO BACK : ";
  cin>>any;
  updateContact();
}

void updateContact(){
  int userChoice;
  system("cls");
  header("Wishing you a successful Updation :)\n");
  cout<<"\n1. UPDATE BY NAME : ";
  cout<<"\n2. UPDATE BY NUMBER : ";
  cout<<"\n3. HOME PAGE";
  cout<<"\n\nENTER CHOICE : ";
  cin>>userChoice;
  switch (userChoice) {
    case 1:
    updateByName();
    break;
    case 2:
    updateByNumber();
    break;
    case 3:
    homePage("\nUpdated Your Contact ?");
    break;
    default:
    deleteContact();
  }
}

void linearSearch(int id){
  int flag = 0;
  system("cls");
  fstream userStream;
  string inputName,inputNumber;
  int mon, yr;
  userStream.open(welcomeName+".txt", ios::in);
  int i=0,totalContacts = getCount();
  contact c[totalContacts];
  while(1){
    userStream>>c[i].contactName>>c[i].mobileNumber>>c[i].month>>c[i].year;
    if(userStream.eof()){
      break;
    }
    i++;
  }
  userStream.close();

  if(id==1){
    header("Search by Name or Half Name :)\n");
    cout<<"\nENTER THE NAME : ";
    cin>>inputName;
    cout<<endl;
    for(int j=0;j<totalContacts;j++){
      if(c[j].contactName == inputName || strstr(c[j].contactName.c_str(), inputName.c_str())){
        flag = 1;
        cout<<c[j].contactName<<"\t"<<c[j].mobileNumber<<"\n";
      }
    }
    if(flag == 0){
      cout<<"\n\t**SORRY! We didn't Find any contacts in that Name**\n";
    }
  }

  if(id==2){
    header("Search by Number or Half Number :)\n");
    cout<<"\nENTER YOUR NUMBER : ";
    cin>>inputNumber;
    cout<<endl;
    for(int j=0;j<totalContacts;j++){
      if(c[j].mobileNumber == inputNumber || strstr(c[j].mobileNumber.c_str(), inputNumber.c_str())){
        flag = 1;
        cout<<c[j].contactName<<"\t"<<c[j].mobileNumber<<"\n";
      }
    }
    if(flag == 0){
      cout<<"\n\t**SORRY! We didn't Find any contacts in that Number**\n";
    }
  }

  if(id==3){
    header("Search by Month of Saving the Contact :)\n");
    cout<<"\nENTER MONTH (give 0 if not sure): ";
    cin>>mon;
    cout<<"\nENTER YEAR (give 0 if not sure): ";
    cin>>yr;
    cout<<endl;
    for(int j=0;j<totalContacts;j++){
      if(mon == 0 || yr == 0){
        if(c[j].month == mon || c[j].year == yr){
          flag = 1;
          cout<<c[j].contactName<<"\t"<<c[j].mobileNumber<<"\n";
        }else if(mon == 0 && yr == 0){
          flag = 1;
          cout<<c[j].contactName<<"\t"<<c[j].mobileNumber<<"\n";
        }else{
          if(c[j].month == mon && c[j].year == yr){
            flag = 1;
            cout<<c[j].contactName<<"\t"<<c[j].mobileNumber<<"\n";
          }
        }
      }
    }
    if(flag == 0){
      cout<<"\n\t**SORRY! We didn't Find any contacts in that Month | Year**\n";
    }

  }

  string any;
  cout<<"\nPRESS ANY KEY TO RETURN : ";
  cin>>any;
  searchContact();

}

void searchContact(){
  int userChoice;
  system("cls");
  header("Wishing you a successful search :)\n");
  cout<<"\n1. SEARCH BY NAME  ";
  cout<<"\n2. SEARCH BY NUMBER  ";
  cout<<"\n3. SEARCH BY DATE OF SAVING  ";
  cout<<"\n4. HOME PAGE ";
  cout<<"\n\nENTER CHOICE : ";
  cin>>userChoice;
  switch (userChoice) {
    case 1:
    linearSearch(1);
    break;
    case 2:
    linearSearch(2);
    break;
    case 3:
    linearSearch(3);
    break;
    case 4:
    homePage("\tSearched Your Contact ?");
    default:
    searchContact();
  }

}

void homePage(string homeMessage)
{
  int userChoice;
  system("cls");
  header(homeMessage);
  cout<<"\n\n1. ADD A CONTACT";
  cout<<"\n2. DELETE A CONTACT";
  cout<<"\n3. UPDATE A CONTACT";
  cout<<"\n4. DISPLAY ALL CONTACTS";
  cout<<"\n5. SEARCH A PARTICULAR CONTACT";
  cout<<"\n6. LOGOUT";
  cout<<"\n\nENTER CHOICE : ";
  cin>>userChoice;
  switch (userChoice) {
    case 1:
    addContact();
    break;
    case 2:
    deleteContact();
    break;
    case 3:
    updateContact();
    break;
    case 4:
    displayContacts();
    break;
    case 5:
    searchContact();
    break;
    case 6:
    mainPage("\t** Logged out successfully !**\n");
    welcomeName="";
    break;
    default:
    homePage("\tPlease Enter a Valid Choice");
  }
}

void userLogin()
{
  system("cls");
  string userid, pswd;
  header("Please Enter Your Credentials !\n");
  cout<<"\nENTER YOUR USER ID : ";
  cin>>userid;
  cout<<"\nENTER PASSWORD : ";
  cin>>pswd;
  int status = doesUserExists(userid,pswd);
  if(status == 0 && dpm == YES){
    homePage("\tWelcome "+welcomeName);
  }else if(status == 0 && dpm == NO){
    mainPage("** Your PASSWORD is Wrong. Please Try Again.** \n");
  }else{
    mainPage("** No Such User! Please Try Again.** \n");
  }
}

void registerUser(string username, string userid, string password){
  fstream userStream;
  userStream.open("users.txt", ios::app);
  userStream<<username<<"\t"<<userid<<"\t"<<password<<"\n";
  userStream.close();
}

void userRegister(){
  system("cls");
  string username, userid, pswd, repswd;
  header("Happy to see you join us !\n");
  cout<<"\nENTER YOUR FULL NAME : ";
  cin>>username;
  cout<<"\nENTER USER ID : ";
  cin>>userid;
  cout<<"\nENTER PASSWORD : ";
  cin>>pswd;
  cout<<"\nRE-ENTER PASSWORD : ";
  cin>>repswd;
  int status = doesUserExists(userid, pswd);
  dpm = NILL;
  if(status == 0){
    mainPage("** Userid Already Exists. Try Logging in.** \n");
  }else{
    welcomeName = username;
    if(pswd == repswd){
      registerUser(username, userid, pswd);
      homePage("\tWelcome "+welcomeName);
    }else{
      mainPage("** Passwords Didn't Match. Please try Again.** \n");
    }
  }


}

void mainPage(string inputMessage){
  system("cls");
  int userChoice;
  header(inputMessage);
  cout<<"\n1. LOGIN (already have an account ?)";
  cout<<"\n2. REGISTER (new here ?)";
  cout<<"\n3. EXIT";
  cout<<"\n\nENTER CHOICE : ";
  cin>>userChoice;
  switch (userChoice) {
    case 1:
    userLogin();
    break;
    case 2:
    userRegister();
    break;
    case 3:
    exit(0);
    break;
    default:
    system("cls");
    mainPage("Please Enter a Valid Choice !\n");
  }
}

int main()
{
  mainPage("Vankkam ! Happy to see you here !!!\n");
  return 0;
}
