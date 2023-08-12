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
   void Generatebill(User);
};



// TO generate bill

void User :: Generatebill(User us){
    cout<<"Name of the customer is = "<<us.customar_Name<<endl;
    cout<<"Name of the Car is = "<<us.Name<<endl;
    cout<<"Type of the Car is = "<<us.Modal<<endl;
    cout<<"Number of the Car is = "<<us.Car_number<<endl;
    cout<<"Number of days Car ranted = "<<us.days<<endl;
    cout<<"Advanced paid money is = "<<us.advance<<endl;
    cout<<"Total amount of car Booking = "<<us.amount<<endl;
    cout<<"Total Balance  = "<<(us.amount-us.advance)<<endl;
}
// To check the available car
Car to_check(Car c,string type){
  ifstream filecheck;
  filecheck.open("filename.txt");

  filecheck.read((char*)&c,sizeof(c));
  // cout<<c.Modal<<endl;

  cout<<"Available Cars................"<<endl;
  while(!filecheck.eof()){
    if(c.Modal==type){
    cout<<c.Name<<endl;
    }
    filecheck.read((char*)&c,sizeof(c));
    
  }
  string name;
  cout<<"Choose the car from above list and for exit press -1"<<endl;
  cin>>name;
  if(name=="-1"){
    exit(0);
  }
  filecheck.close();
  filecheck.open("filename.txt");
  filecheck.read((char*)&c,sizeof(c));
  // cout<<c.Modal<<endl;
  while(!filecheck.eof()){
    if(c.Name==name){
      cout<<"Car successfiul"<<endl;
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
          fstream car1;
            fstream car2;
            Car d;
            car1.open("filename.txt");
            car2.open("newfilename.txt",ios::app);
            car1.read((char*)&d,sizeof(d));
            while(!car1.eof()){
              if(d.Car_number!=b.Car_number){
                  car2.write((char*)&d, sizeof(d));
                }
                car1.read((char*)&d, sizeof(d));
              }
              
            
              car1.close();
              car2.close();
              remove("filename.txt");
              rename("newfilename.txt","filename.txt");
          return true;
        }
    }else if(n==2){
       Car b = to_check(c,"sedan");
        if(b.Name!="Notfound"){
          Bookuser(b);
          fstream car1;
            fstream car2;
            Car d;
            car1.open("filename.txt");
            car2.open("newfilename.txt",ios::app);
            car1.read((char*)&d,sizeof(d));
            while(!car1.eof()){
              if(d.Car_number!=b.Car_number){
                  car2.write((char*)&d, sizeof(d));
                }
                car1.read((char*)&d, sizeof(d));
              }
              
            
              car1.close();
              car2.close();
              remove("filename.txt");
              rename("newfilename.txt","filename.txt");
          return true;
        }
    }
    return false;
}


int main(){
  int choice;
  cout<<"Add Car press 1"<<endl;
  cout<<"Available car press 2"<<endl;
  cout<<"Press 3 Book a Car "<<endl;
  cout<<"Press 4 to see the rented car"<<endl;
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
    }else if(choice==3){
        User us;
       bool temp = us.Adduser(c);
       if(temp){
          ofstream userinof;
          userinof.open("user.txt",ios::app);
          userinof.write((char*)&us,sizeof(us));
          cout<<"Successfully booked your car"<<endl;
          us.Generatebill(us);
       }else{
          cout<<"No Car Available"<<endl;
       }
    }else if(choice==4){
      fstream userlist;
      userlist.open("user.txt");
      User obj;
      userlist.read((char*)&obj,sizeof(obj));
      cout<<"Name       "<<"Car Number       "<<"Balance Amt     "<<"Car Name     "<<endl;

      while (!userlist.eof())
      {
          cout<<obj.customar_Name<<"     ";
          cout<<obj.Car_number<<"       ";
          cout<<(obj.amount-obj.advance)<<"       ";
          cout<<obj.Name<<endl;
          userlist.read((char*)&obj,sizeof(obj));
      }
      
    }
}