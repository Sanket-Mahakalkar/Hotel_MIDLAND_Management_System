#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>

using namespace std;

//Start of class 

class Hotel_MidLand
{
	int room_No;
	char name[25];
	char address[60];
	char phone_no[10];
	int days;
	
	public:
		 getDetails()                  // It gets the details of customer
		{
			cout<<"Name : ";
			cin.getline(name,24);     
			cout<<"Address : ";
			cin.getline(address,59);
			cout<<"Phone No : ";
			cin>>phone_no;
			cout<<"How many days you will be staying in a Hotel : ";
			cin>>days;
		}
		
		
		void hostel_menu();               // It display main menu of hostel
		void BookRoom();                  // It book the room for customer
		void SearchRecord();              // It display the particular guest details
		void ViewAllRooms();                 // It display alloted rooms in hotel
		void edit();                      // It edit the customer record
		bool check(int);                  // It check the status of room
		void update(int);                 // It modify the customer's record
		void delete_rec(int);                 // It deletes the customer record
		void bill(int);                   // It calculate the bill of customer          
		
};

// END of class definition







//FUNCTION for Booking a Room

void Hotel_MidLand::BookRoom()
{
	system("cls");
	ofstream fout("list.dat",ios::app|ios::binary);
	int R;
	bool flag;
	
	cout<<"Enter the Customer details :-";
	cout<<"\n-------------------------------\n";
	cout<<"\nTotal no of Rooms : 100";
	cout<<"\nSingle bed Rooms from 1 to 40";
	cout<<"\nDouble bed Rooms from 41 to 80";
	cout<<"\nMeeting Rooms from 81 to 100";
	cout<<"\n\nEnter the Room no you want to stay in : ";
	cin>>R;
	
	flag=check(R);                                              //If room is available check() will return true
	if(flag)
	{
		cin.ignore();
		getDetails();
		room_No=R;
		fout.write((char*)this,sizeof(*this));
		cout<<"\n\tRoom has been booked successfully..!!";
	}
	else
	{
		cout<<"\n\tSorry, Room is already booked. Please try some other Room !!";
	}
	
	fout.close();
}

//END of Booking function






//FUNCTION for displaying particular guest details

void Hotel_MidLand::SearchRecord()
{
	system("cls");
	char person[25];
	bool flag=false;
	ifstream fin("list.dat",ios::in|ios::binary);
	cout<<"\nEnter the name of the person you are looking for : ";
	cin.ignore();
	cin.getline(person,24);
	fin.read((char*)this,sizeof(*this));
	while(!fin.eof())
	{
		if(!strcmp(person,name))
		{
			system("cls");
			cout<<"Guest Details :-";
			cout<<"\n-----------------\n";
			cout<<"\nRoom no : "<<room_No;
			cout<<"\nName : "<<name;
			cout<<"\nAddress : "<<address;
			cout<<"\nPhone no : "<<phone_no;
			cout<<"\nNo of days he/she will be staying in hotel : "<<days;
			flag=true;
			break;
		}
		fin.read((char*)this,sizeof(*this));
	}
	if(!flag)
	 cout<<"\nSorry, the person you are looking for has not booked a room in this hotel !!";
	 
	fin.close(); 
}

//END of display Function





// FUNCTION for displaying all the alloted rooms

void Hotel_MidLand::ViewAllRooms()
{
	system("cls");
	ifstream fin("list.dat",ios::in|ios::binary);
	cout<<"\n\t\t\t   List Of Rooms Alloted";
	cout<<"\n\t\t\t   ---------------------";
	cout<<"\n\nRoom_No\t\tName\t\t\tAddress\t\tPhone No\tDays";
	fin.read((char*)this,sizeof(*this));
	while(!fin.eof())
	{
		cout<<"\n\n"<<room_No<<"\t\t";
		cout<<name<<"    \t";
		cout<<address<<"   \t";
		cout<<phone_no<<"\t";
		cout<<days;
		
		fin.read((char*)this,sizeof(*this));
	}
	fin.close();
}

//END of ViewAllRooms Function






//FUNCTION for editing record and printing Bill

void Hotel_MidLand::edit()
{
	system("cls");
	int choice,R;
	cout<<"\n\tEDIT MENU";
	cout<<"\n\t---------";
	cout<<"\n\n1. Modify Customer Record";
	cout<<"\n2. Delete Customer Record";
	cout<<"\n3. Bill of Customer";
	
	cout<<"\n\nEnter your choice : ";
	cin>>choice;
	
	if(choice==1 || choice==2 || choice==3)
	{
		system("cls");
		cout<<"\nEnter the Room no : ";
		cin>>R;
	}
	
	switch(choice)
	{
		case 1:
			update(R);
			break;
		
		case 2:
			delete_rec(R);
			break;
			
		case 3:
			bill(R);
			break;
			
		default:
		cout<<"Invalid Choice!!";
					
	}
}

//END of Edit Function





// Modifing the customer details

void Hotel_MidLand::update(int R)
{
	fstream file("list.dat",ios::in|ios::out|ios::ate|ios::binary);
	bool flag=false;
	
	if(!file)
	 cout<<"File not found";
	else
	{
		file.seekg(0);
		file.read((char*)this,sizeof(*this));
		while(!file.eof())
		{
			if(room_No==R)
			{
				cin.ignore();
				cout<<"\n\nEnter new details : ";
				cout<<"\n---------------------\n";
				getDetails();
				file.seekg(file.tellg()-sizeof(*this));
				file.write((char*)this,sizeof(*this));
				flag=true;
				cout<<"\nRecord has been modified successfully..!!";
				break;
			}
			file.read((char*)this,sizeof(*this));
		}
	 }
	 
	 file.close();
	 
	 if(!flag)
	  cout<<"\nSorry, Room no not found or is vacant"; 
}

//END of modify Function






//FUNCTION for deleting a record

void Hotel_MidLand::delete_rec(int R)
{
	ifstream fin;
	ofstream fout;
	bool flag=false;
	
	fin.open("list.dat",ios::in|ios::binary);
	if(!fin)
	 cout<<"\nFile not Found";
	else
	{
		fout.open("tempfile.dat",ios::out|ios::binary);
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof())
		{
			if(room_No!=R)  
			{
				fout.write((char*)this,sizeof(*this));
			}
			else
			{
				flag=true;
				cout<<"\nName : "<<name;
				cout<<"\nAddress : "<<address;
				cout<<"\nPhone No : "<<phone_no;
				cout<<"\n\nDo you really want to delete this record ? (y/n)";
				char ch;
				cin>>ch;
				if(ch=='n')
				  fout.write((char*)this,sizeof(*this));
				else
				 cout<<"\nRecord has been successfully deleted";  
			}
			fin.read((char*)this,sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("list.dat");
		rename("tempfile.dat","list.dat");
		if(!flag)
		 cout<<"\n Sorry, the record you want to delete is not available..!!";
		  
	 } 
}

//END of delete record Function





// FUNCTION for calculating Bill of customer

void Hotel_MidLand::bill(int R)
{
	ifstream fin("list.dat",ios::in|ios::binary);
	bool flag=false;
	
	if(!fin)
	 cout<<"File not found";
	else
	{
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof())
		{
			if(room_No==R)
			{
				flag=true;
				if(room_No >=1 && room_No<=40)
				 cout<<"\n\tBill is : "<<3000*days;
				 
				else if(room_No >= 41 && room_No <= 80)
				 cout<<"\n\tBill is : "<<6000*days; 
				 
				else
				 cout<<"\n\tBill is : "<<8000*days; 
			}
			
			fin.read((char*)this,sizeof(*this));
		}
		fin.close();
		if(!flag)
		 cout<<"\nRoom not found !!";
	}
	
}

//END of Bill Function







// FUNCTION that checks the availability of room

bool Hotel_MidLand::check(int R)
{
	ifstream fin("list.dat",ios::in|ios::binary);
	fin.read((char*)this,sizeof(*this));
	
	while(!fin.eof())
	{
		if(room_No==R)
		  return false;
		  
		fin.read((char*)this,sizeof(*this));  
	}
	return true;
}

//END of check Function





// FUNCTION of Main menu

void Hotel_MidLand::hostel_menu()
{
	int choice;
	while(1)
	{
		system("cls");
		
		cout<<"\n\t\t\t\t**************************";
		cout<<"\n\t\t\t\t HOTEL MIDLAND MANAGEMENT";
		cout<<"\n\n\t\t\t\t   !!   HOTEL MENU   !!       ";
		cout<<"\n\t\t\t\t**************************";
		cout<<"\n\n\n\t\t\t1. Book a Room";
		cout<<"\n\t\t\t2. Guest Records";
		cout<<"\n\t\t\t3. Rooms Alloted";
		cout<<"\n\t\t\t4. Edit Records";
		cout<<"\n\t\t\t5. Exit";
		cout<<"\n\nE\t\t\t\tEnter your choice : ";
		cin>>choice;
		
		switch(choice)
		{
			case 1:
				BookRoom();
				break;
			
			case 2:
				SearchRecord();
				break;
				
			case 3:
				ViewAllRooms();
				break;
				
			case 4:
				edit();
				break;
			
			case 5:
				cout<<"\n\n\t\tThank you for using the application !!";
				exit(0);		 	
			
			default:
				cout<<"\n\n\t\t\tInvalid Choice !!";		
		}
		cout<<"\n\n\t\t\tPress any key to continue..!!";
		getch();
	}
}
int main()
{
	Hotel_MidLand h;
	system("cls");
	cout<<"\n\t\t\t***********************************";
	cout<<"\n\t\t\t !!  WELCOME TO HOTEL MIDLAND   !!";
	cout<<"\n\t\t\t***********************************";
	cout<<"\n\n\n\n\n\t\t\t\t\tPress any key to continue....!!";
	getch();
	h.hostel_menu();
	return 0;
}
