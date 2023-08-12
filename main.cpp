#include<iostream>
#include<string>
#include <fstream>
using namespace std;
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


int main(){
  int user;
  cout<<"Add Car press 1"<<endl;
  cout<<"Available car press 2"<<endl;
  Car c;
  cin>>user;
  if(user==1){
    c.Addcar();
    ofstream myfile;
    myfile.open("filename.txt" ,ios::app);
    myfile.write((char*)&c, sizeof(c));
  }
  else if(user==2){
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
}