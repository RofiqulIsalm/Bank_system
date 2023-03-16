#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include<vector>
#include<map>
#include<random>
#include<time.h>
#include<sstream>
#include<vector>
#include <iomanip>
using namespace std;
// some global variable 
string suf,spf,scf,sif,sbf; 
/*suf= search user found
  spf= search password found
  scf= search category found
  sif= search id found
  sbf= search balance found
*/

// struct for user data
struct accountHolder
{
  string username;
  string password;
  string category;
  string id;
  int balance;
};
// The hidePassword function can hide the user's password when the user inputs the password

void hidePassword(string& password){
  char ch;
  password = "";
  while ((ch = _getch())!= 13)// _getch() function take input until user input Enter (13 == Enter)
  {
    if (ch == 8) // if user input Backspace (8 == backspace)
    {
      if (password.length() > 0)
      {
        password.pop_back();
        cout << "\b \b"; // (\b == backspace)
      }
    }else{
      password += ch; // if user input without enter the value will add in password;
      cout <<"#"; // and display #
    }
  }cout << endl;
  
}

void signin();

void singup();

void changePassword();

void forget();

void managmentPage();

void accountManagement();

void deposit();

void withdrawal();

void accountClosure();

int main(){
  system("cls"); // the system("cls") funciton clear the terminal
  cout << "\t\t\t__________________________________________________" << endl;
  cout << "\t\t\t       Wellcome to Account managment system       " << endl;
  cout << "\t\t\t__________________________________________________" << endl;
  cout << endl;
  cout << "\t\t\t----> 1) Login." << endl;
  cout << "\t\t\t----> 2) Registration User." << endl;
  cout << "\t\t\t----> 3) Forgot." << endl;
  cout << "\t\t\t----> 4) Exit." << endl;
  int opt;
  cout << "\t\t\tSelect you'r option\t: ";
  cin >> opt;
  switch (opt)
  {
    case 1:
      signin();
      break;
    case 2:
      singup();
      break;
    case 3:
      forget();
      break;
    case 4:
      system("cls"); // the system("cls") funciton clear the terminal
      cout << "\t\t\t__________________________________________________" << endl;
      cout << "\t\t\t           Thank's for using our service          " << endl;
      cout << "\t\t\t__________________________________________________" << endl;
      cout << endl;
      return 0;
      break;
    
    default:
      system("cls"); // the system("cls") funciton clear the terminal
      cout << "\tYou select wrong option....!" << endl;
      main();
      break;
  }
  
}

void managmentPage(){
  system("cls"); // the system("cls") funciton clear the terminal
  again: // the again function repeat the code again

  accountHolder user;
  map<string,bool>usermap; // this funciton work like array . But not array
  string name;
  ifstream file("server.txt");

  if (!file)
  {
    system("cls");
    cout << "\t\tThe file not found..!" << endl;
    return;
  }
  
  cout << "\t\t\t__________________________________________________" << endl;
  cout << "\t\t\t  Wellcome back `"<< suf << "` to Account management system  " << endl;
  cout << "\t\t\t__________________________________________________" << endl;
  cout << endl;
  cout << "\t\t\t----> 1) Account management." << endl;
  cout << "\t\t\t----> 2) Deposit Money." << endl;
  cout << "\t\t\t----> 3) withdrawal Money." << endl;
  cout << "\t\t\t----> 4) LogOut." << endl;
  cout << endl;
  int opt;
  cout << "\t\t\tSelect you'r option\t: ";
  cin >> opt;
  switch (opt)
  {
  case 1:
    accountManagement();
    break;

  case 2:
    deposit();
    break;

  case 3:
    withdrawal();
    break;

  case 4:
    system("cls");
      
      cout << "\t\t\t__________________________________________________" << endl;
      cout << "\t\t\t           Thank's for using our service          " << endl;
      cout << "\t\t\t__________________________________________________" << endl;
      cout << endl;
      cout << "LogOut successful...!" << endl;
      return;
    break;
  
  default:
    system("cls");
    cout << "You select worng option...!" << endl;
    goto again;
    break;
  }
}

void singup()
  {
  system("cls");
  again:
  accountHolder user;
  ifstream file("server.txt");
  map<string,bool>usernameMap;
  string rePassword,line;

  cout << "\t\t\t__________________________________________________" << endl;
  cout << "\t\t\t          Wellcome to Registration system         " << endl;
  cout << "\t\t\t__________________________________________________" << endl;
  cout << endl;

  cout << "\t\t\t----> Enter your name\t\t\t:";
  cin >> user.username;

  while (getline(file,line)) // this loop will try to chack is the username already taken or not
  {
    string username,password,id,category,balance;
    istringstream iss(line);
    getline(iss,username,',');
    getline(iss,password,',');
    getline(iss,balance,',');
    getline(iss,category,',');
    getline(iss,id,'\n');
    if (user.username == username)
    {
      system("cls");
      cout << "\t\tSomeone user this usename....!"<< endl;
      goto again;
    }
  }file.close();

  catopt: // to run the code again. This is the start point
  cout << "\t\t\t----> Enter account category." <<endl;
  cout << "\t\t\t\t\t-->1) Savings accounts\n\t\t\t\t\t-->2) Current accounts"<<endl;
  cout << "\t\t\t----> Select a option\t\t\t:";
  int catOpt;
  cin >> catOpt;

  switch (catOpt)
  {
  case 1:
    user.category = "Saving";
    break;
  case 2:
    user.category = "Current";
    break;
  
  default:
    cout << "\t\tWrong option select..!" <<endl;
    goto catopt;
    break;
  }
  pass: // to run the code again. This is the start point
  string rePasswrod;
  cout << "\t\t\t----> Enter your password\t\t:";
  cin >> user.password;
  cout << "\t\t\t----> Enter your re-password\t\t:";
  cin >> rePassword;

  if (user.password == rePassword) 
  {
    user.balance = 0;
    srand(time(0));
    int ran = rand()%10000; // rand function build a random number
    user.id = "BoPx" + to_string(ran);
    ofstream outFile("server.txt",ios::app);
    outFile << user.username << "," << user.password << "," << user.balance << "," << user.category << "," << user.id << endl;
    outFile.close();
    main();
  }else{
    cout << "\t\tPassword not match..!" <<endl;
    goto pass;
  } 
}

void signin(){
  system("cls");
  again: // to run the code again. This is the start point
  string username,password;
  ifstream file("server.txt");
  bool found = false;
  string line;
  accountHolder user;

  cout << "\t\t\t__________________________________________________" << endl;
  cout << "\t\t\t             Wellcome to Login system             " << endl;
  cout << "\t\t\t__________________________________________________" << endl;
  cout << endl;

  cout << "\t\t\t----> Enter you'r name\t\t\t:";
  cin >> username;
  cout << "\t\t\t----> Enter you'r password\t\t:";
  hidePassword(password);

  while (getline(file,line))
  {
    if (line.find(username) != string::npos)
    {
      if (line.find(password) != string::npos)
      {
        found = true;
        istringstream iss(line);
        getline(iss,suf,',');
        getline(iss,spf,',');
        getline(iss,sbf,',');
        getline(iss,scf,',');
        getline(iss,sif,'\n');
      }
    }
  }file.close();

  if (found)
  {
    suf = username;
    managmentPage();
  }else{
    system("cls");
    cout << "\t\tUsername and password are wrong...!"<<endl;
    goto again;
  }
}

void accountManagement(){
  system("cls");
  ifstream file("server.txt");
  accountHolder user;
  again:
  cout << "\t\t\t__________________________________________________" << endl;
  cout << "\t\t\t      Wellcome to Account management system     " << endl;
  cout << "\t\t\t__________________________________________________" << endl;
  cout << endl;
  double balance = stod(sbf);
  cout <<"\t--> Account Holder\t: " << suf ;
  cout <<"\t\t\t--> Account Balance\t\t: "<< fixed << setprecision(3) << balance << "$" << endl;
  cout <<"\n\t--> Account Category\t: " << scf;
  cout <<"\t\t--> Account Number\t\t: " << sif << endl;
  cout << "\t\t\t__________________________________________________" << endl;
  cout <<"\n\t\t -------------------------Modify Account-------------------------" << endl;

  cout <<"\t\t  --> 1) Change Password";
  cout <<"\t\t  --> 2) Delet Account" << endl;;
  cout << endl;
  char ch;
  cout << "\t\t\tDo you want Modify [Y/N] \t:";
  cin >> ch;
  if (ch =='Y' || ch == 'y')
  {
    int opt;
    cout<<"\t\t\tSelect you'r Option\t:";
    cin >> opt;
    switch (opt)
    {
    case 1:
      changePassword();
      break;
    case 2:
      accountClosure();
      break;
    
    default:
      system("cls");
      cout <<"\tYou select wrong option...!"<<endl;
      goto again;
      break;
    }
  }else{
    managmentPage();
  }
  
}

void changePassword(){
  system("cls");
  cout << "\t\t\t__________________________________________________" << endl;
  cout << "\t\t\t      So now you want to change password why     " << endl;
  cout << "\t\t\t__________________________________________________" << endl;
  cout << endl;
}

void withdrawal(){
 system("cls");
    cout << "\t\t\t__________________________________________________" << endl;
    cout << "\t\t\t     Take your money we don't need it anymore     " << endl;
    cout << "\t\t\t__________________________________________________" << endl;
    cout << endl;
    string username = suf;
    double amount;
    string filename = "server.txt";
    fstream file(filename, ios::in | ios::out);
    cout << "\t\t\t----> Enter the amount you Withdrawal\t\t:";
    cin >> amount;
    if (!file) {
      cerr << "Failed to open file" << endl;
      return;
    }
    string line;
    vector<string> lines;
    while (getline(file, line)) {
      istringstream iss(line);
      string storedUsername, password, balanceStr, category, id;
      getline(iss, storedUsername, ',');
      getline(iss, password, ',');
      getline(iss, balanceStr, ',');
      getline(iss, category, ',');
      getline(iss, id, '\n');

      if(username == storedUsername) {
        double balance = stod(balanceStr);
        balance -= amount;
        sbf = to_string(balance);
        ostringstream oss;
        oss << storedUsername << "," << password << "," << balance << "," << category << "," << id;
        lines.push_back(oss.str());
      }else {
        lines.push_back(line);
      }
    }
    file.close();
    file.open(filename, ios::out | ios::trunc);
    for (const string& line : lines) {
      file << line << endl;
    }
    file.close();
    cout << "\t\t\t________________________________________________________" << endl;
    cout << "\t\t\tDeposit of $" << amount << " was successful for user " << username << endl;
    cout << "\t\t\t________________________________________________________" << endl;
    cout << "\n\n\tpress enter key..........." <<endl;
    getchar();
    getchar();
    accountManagement();

}

void deposit() {
    system("cls");
    cout << "\t\t\t__________________________________________________" << endl;
    cout << "\t\t\t       Your money my money.My money not your      " << endl;
    cout << "\t\t\t__________________________________________________" << endl;
    cout << endl;
    string username = suf;
    double amount;
    string filename = "server.txt";
    fstream file(filename, ios::in | ios::out);
    cout << "\t\t\t----> Enter the amount you deposit\t\t:";
    cin >> amount;
    if (!file) {
      cerr << "Failed to open file" << endl;
      return;
    }
    string line;
    vector<string> lines;
    while (getline(file, line)) {
      istringstream iss(line);
      string storedUsername, password, balanceStr, category, id;
      getline(iss, storedUsername, ',');
      getline(iss, password, ',');
      getline(iss, balanceStr, ',');
      getline(iss, category, ',');
      getline(iss, id, '\n');

      if(username == storedUsername) {
        double balance = stod(balanceStr);
        balance += amount;
        sbf = to_string(balance);
        ostringstream oss;
        oss << storedUsername << "," << password << "," << balance << "," << category << "," << id;
        lines.push_back(oss.str());
      }else {
        lines.push_back(line);
      }
    }
    file.close();
    file.open(filename, ios::out | ios::trunc);
    for (const string& line : lines) {
      file << line << endl;
    }
    file.close();
    cout << "\t\t\t________________________________________________________" << endl;
    cout << "\t\t\tDeposit of $" << amount << " was successful for user " << username << endl;
    cout << "\t\t\t________________________________________________________" << endl;
    cout << "\n\n\tpress enter key..........." <<endl;
    getchar();
    getchar();
    accountManagement();
}

void accountClosure(){
  system("cls");
  again:
  ifstream file("server.txt");
  cout << "\t\t\t__________________________________________________" << endl;
  cout << "\t\t\t           Are you sure you want to delete        " << endl;
  cout << "\t\t\t__________________________________________________" << endl;
  cout << endl;
  cout << "\t\t\t----> Do you want to delete you account [Y/N]\t:";
  char ch;
  cin >> ch;
  if (ch == 'Y' || ch == 'y')
  {
    vector<string>lines;
    string line;
    while (getline(file,line))
    {
      string username = line.substr(0,line.find(","));
      if (username != suf)
      {
        lines.push_back(line);
      }
    }file.close();
    ofstream outfile("server.txt");
    for (auto& line : lines)
    {
      outfile << line << endl;
    }
    system("cls");
    cout << "\t\tAccount remove successful...!" << endl;
    signin();
  }else if(ch == 'N' || ch == 'n'){
    accountManagement();
  }
  else{
    system("cls");
    cout << "\t\t\tWrong option select...!" << endl;
    goto again;
  }
}

void forget(){
  system("cls");
  ifstream file("server.txt");
  map<string,string>userpasswordMap;
  again:
  cout << "\t\t\t__________________________________________________" << endl;
  cout << "\t\t\t     Bha you already forgot you usename/password    " << endl;
  cout << "\t\t\t__________________________________________________" << endl;
  cout << endl;

}