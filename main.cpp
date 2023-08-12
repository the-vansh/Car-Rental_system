#include<iostream>
#include<string>
#include <fstream>
using namespace std;

// To store the car Information in the system
class Car{
   public:
    string Name;
    string Modal;
    string Car_number;
    int Rent_price;

    void Addcar();
    
};

void Car :: Addcar(){
    string name,modal,car_number;
    int rent;
    cout<<"Enter the Name of the car = ";
    cin>>name;
    cout<<"Enter the Modal of the car = ";
    cin>>modal;

    cout<<"Enter the car number = ";
    cin>>car_number;

    cout<<"Enter the Rent price of the car = ";
    cin>>rent;

    Name = name;
    Modal = modal;
    Car_number = car_number;
    Rent_price=rent;
}
//To store the user information in the system;
class User: public Car{
    public:

    string customar_Name;
    int days;
    int amount;
    int advance;
   bool Adduser(Car);
   void Bookuser(Car);
};

// To check the available car
Car to_check(Car c,string type){
  ifstream filecheck;
  filecheck.open("filename.txt");

  filecheck.read((char*)&c,sizeof(c));
  while(!filecheck.eof()){
    if(c.Modal==type){
        return c;
    }
    filecheck.read((char*)&c,sizeof(c));
  }
  Car temp;
  temp.Name="Notfound";
  return temp;
  
}

void User :: Bookuser(Car b){
    string customar_Name;
    int days;
    int advance;
   cout<<"Enter the name of the customer = ";
   cin>>customar_Name;
   cout<<"Enter the days = ";
   cin>>days;
   cout<<"Enter the amount paid in advance = ";
   cin>>advance;


   this->customar_Name=customar_Name;
   this->days=days;
   this->advance = advance;
   this->Car_number = b.Car_number;
   this->Modal=b.Modal;
   this->Name=b.Name;
   this->amount = b.Rent_price*days; 
}



// To store the user information

bool User :: Adduser(Car c){
    cout<<"Press 1 for SUV"<<endl;
    cout<<"Press 2 for Sedan"<<endl;

    int n;
    cin>>n;

    if(n==1){
        Car b = to_check(c,"SUV");
        if(b.Name!="Notfound"){
          Bookuser(b);
          return true;
        }
    }else if(n==2){
       Car b = to_check(c,"sedan");
        if(b.Name!="Notfound"){
          Bookuser(b);
          return true;
        }
    }
    return false;
}


int main(){
  int choice;
  cout<<"Add Car press 1"<<endl;
  cout<<"Available car press 2"<<endl;
  Car c;
  cin>>choice;
  if(choice==1){
    c.Addcar();
    ofstream myfile;
    myfile.open("filename.txt" ,ios::app);
    myfile.write((char*)&c, sizeof(c));
  }
  else if(choice==2){
    ifstream file_obj;
 
    file_obj.open("filename.txt", ios::in);
    file_obj.read((char*)&c, sizeof(c));

    cout<<"Car Name           "<<"Car Modal          "<<"Car_Number          "<<"Rent_price            "<<endl;
    while (!file_obj.eof()) {
       
      cout<<c.Name<<"           ";
      cout<<c.Modal<<"          ";
      cout<<c.Car_number<<"     ";
      cout<<c.Rent_price<<"     ";
      cout<<endl;
      
      file_obj.read((char*)&c, sizeof(c));
    }
    }

    User us;
    bool temp = us.Adduser(c);
    if(temp){
      ofstream userinof;
      userinof.open("user.txt",ios::app);
      userinof.write((char*)&us,sizeof(us));
      cout<<"Successfully booked your car"<<endl;
    }
    
}