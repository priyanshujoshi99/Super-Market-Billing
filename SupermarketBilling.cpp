#include<iomanip>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

using namespace std;

fstream file;
//**************Global Functions**************//
void time()
{
    time_t tim;  //create variable
    time(&tim);  //pass variable to time function
    cout<<ctime(&tim);
}

void printstars() //for printing the stars as shown
{
    cout<<"\n********************************************************************************\n"<<endl;

}

void display_nce()
{
    cout<<setw(50)<<"_____________________"<<endl;
    cout<<setw(51)<<"|***NCE SUPERMARKET***|"<<endl;
    cout<<setw(51)<<"|_____________________|"<<endl;
    printstars();
}

//**********************************************************//

//**************Class User**************//
class user
{
  private:
    char username[20];
    char password[20];
public:
    void add_user()
    {
        cout<<"\n\n\t\t\tADD USER\n\n";
        cout<<"\n\t\tEnter the username and password\n";
        cout<<"\tUsername  :  ";
        cin>>username;
        cout<<"\tPassword  :  ";
        cin>>password;
        file.open("user.txt",ios::app|ios::out);
        file.write(reinterpret_cast<char*>(this),sizeof(*this));
        file.close();
    }

    int verify()
    {
        display_nce();
        char u[20];
        char pw[20];
        int count;
        cout<<"\n\t\tPlease Enter the username and password\n";
        cout<<"\tUsername  :  ";
        cin>>u;
        cout<<"\tPassword  :  ";
        cin>>pw;
        file.open("user.txt",ios::in);
        file.seekg(0);
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
        while(!file.eof())
        {
            if(strcmp(username,u)==0)
            {
                if(strcmp(password,pw)==0)
                {
                    count=1;
                }
            }
            file.read(reinterpret_cast<char*>(this),sizeof(*this));

        }
        file.close();
        return(count);
        }


};
//*************Class Customer**********//
class customer
{
    private:
        char fname[20],lname[20];
        char add[25];
        char cn[10];

    public:
        void c_read();
        void c_display();

};

void customer::c_read()
        {
            display_nce();
            cout<<"Enter full name of the customer   :    ";
            cin>>fname;
            cin>>lname;
            cout<<"Enter address of the customer     :    ";
            cin>>add;
            cout<<"Enter contact no. of the customer :    ";
            cin>>cn;
        }

void customer::c_display()
        {
            cout<<"Customer Name     :  "<<fname<<" "<<lname<<endl;
            cout<<"Customer Address  :  "<<add<<endl;
            cout<<"Contact no.       :  "<<cn<<endl;

        }
//*************************************************************************//

//****************Class Product***********************//

class product : public user
{
    protected:
    unsigned int id;
    char name[50];
    float rate;
    float dis;
 public:
	void create_product();
    void show_product();
    void display_all();
    void display_sp();
    void price_list();
    void modify_product();
    void delete_product();
    void fread()
    {
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
    }
    void admin_menu();
};


void product::create_product()
{
    cout<<"\nEnter the product ID of the product : ";
    cin>>id;
    cout<<"\nEnter the Name of the product       : ";
    cin>>name;
    cout<<"\nEnter the Rate of the product      : ";
    cin>>rate;
    cout<<"\nEnter the Discount (%)              : ";
    cin>>dis;
    file.open("product.dat",ios::app|ios::out);
    file.write(reinterpret_cast<char*>(this),sizeof(*this));
    file.close();
    cout<<"\n\nThe Product Has Been Created.";
    }

void product::show_product()
{
    cout<<"*****************************";
    cout<<"\nProduct ID : "<<id;
    cout<<"\nName       : "<<name;
    cout<<"\nRate       : "<<"Rs. "<<rate;
    cout<<"\nDiscount   : "<<dis<<"%";
    cout<<"\n*****************************";
    }

void product::display_all()
{
    cout<<"\n\n\n\t\tDISPLAYING ALL RECORD\n\n";
    file.open("product.dat",ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(this),sizeof(*this));
    while(!file.eof())
	{
        show_product();
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
        cout<<"\n\n====================================\n\n";

	 }
	 file.close();
    getch();
}

void product::display_sp()
{
    int n,flag=0;
    cout<<"Enter the product id of the product to be displayed : ";
    cin>>n;
    file.open("product.dat",ios::in);
    file.seekg(0);
    while(!file.eof())
	{
	    file.read(reinterpret_cast<char*>(this),sizeof(*this));
	    if(id==n)
		{
		 system("cls");
		 show_product();
		 flag=1;
		}
	}
	file.close();
    if(flag==0)
    cout<<"\n\nRecord doesnot exist";
    getch();
}

void product::price_list()
{
    file.open("product.dat",ios::in);
    cout<<"====================================================\n";
    cout<<"\t\t\t\tProduct MENU\n";
    cout<<"====================================================\n";
    cout<<"Product ID\t\tNAME\t\tPRICE\n";
    file.seekg(0);
    file.read(reinterpret_cast<char*>(this),sizeof(*this));
    while(!file.eof())
    {
        cout<<id<<"\t\t\t"<<name<<"\t\t"<<rate<<endl;
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
    }
    file.close();
    getch();

}

void product::modify_product()
{
    int n,pos,flag=0;
    cout<<"\n\nEnter the product ID of the product to modify : ";
    cin>>n;
    file.open("product.dat",ios::in|ios::out);
    while(!file.eof())
	{
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(id==n)
        {
            show_product();
            pos=-1*sizeof(*this);
            file.seekp(pos,ios::cur);
            cout<<"\nEnter the product ID of the product : ";
            cin>>id;
            cout<<"\nEnter the Name of the product       : ";
            cin>>name;
            cout<<"\nEnter the Rate of the product      : ";
            cin>>rate;
            cout<<"\nEnter the Discount (%)              : ";
            cin>>dis;
            file.write(reinterpret_cast<char*>(this),sizeof(*this));
            cout<<"\n\n\t Record Updated";
            flag=1;
         }
    }
    file.close();
    if(flag==0)
    cout<<"\n\nSorry!!! Record Not Found ";
    getch();
}

void product::admin_menu()
{
  char ch;
  while(1)
  {
    system("cls");
    cout<<"\n\n\t1.CREATE PRODUCT";
    cout<<"\n\t2.DISPLAY ALL PRODUCTS";
    cout<<"\n\t3.DISPALY SPECIFIC PRODUCT";
    cout<<"\n\t4.MODIFY PRODUCT";
    cout<<"\n\t5.DELETE PRODUCT";
    cout<<"\n\t6.DISPLAY PRICE LIST";
    cout<<"\n\t7.ADD USER";
    cout<<"\n\t8.BACK TO MAIN MENU";
    cout<<"\n\n\n\tEnter Your Choice :\t ";
    cin>>ch;
    switch(ch)
    {
        case '1':
            system("cls");
            display_nce();
            create_product();
            break;
        case '2':
            system("cls");
            display_nce();
            display_all();
            break;
        case '3':
            system("cls");
            display_nce();
            display_sp();
            break;
        case '4':
            system("cls");
            display_nce();
            modify_product();
            break;
        case '5':
            system("cls");
            display_nce();
            delete_product();
            break;
        case '6':
            system("cls");
            display_nce();
            price_list();
            break;
        case '7':
            system("cls");
            display_nce();
            user::add_user();
            break;
        case '8':
            goto leave;
            break;
        default:cout<<"Invalid Choice";
       }
  }
  leave:
  cout<<" ";
}

void product::delete_product()
{
    int n,flag=0;
    fstream file2;
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nEnter the Product id of the Product to Delete  :  ";
    cin>>n;
    file.open("product.dat",ios::in);
    file2.open("Temp.dat",ios::out);
    file.seekg(0);
    while(!file.eof())
	{
	    file.read(reinterpret_cast<char*>(this),sizeof(*this));
	    if(id!=n)
		{
		 file2.write(reinterpret_cast<char*>(this),sizeof(*this));
		 flag++;
		 }
	 }
    file2.close();
    file2.open("Temp.dat",ios::in);
    file2.seekg(0);
    file.open("product.dat",ios::out|ios::trunc);
    while(!file2.eof())
	{
		 file2.read(reinterpret_cast<char*>(this),sizeof(*this));
		 file.write(reinterpret_cast<char*>(this),sizeof(*this));

	 }
	 file.close();
	 file2.close();
	 if(flag==0)
	 cout<<"\n\nSorry!!! Record Not Found ";
    getch();
}

//********************************************************//

//***************Class  BILL******************//

class bill : public product , public customer
{
  private :
    int  order_arr[50],quan[50];
    float amt,damt,total;
  public :
    void place_order()
    {
        int n,count=0;
        system("cls");
        customer::c_read();
        system("cls");
        display_nce();
        cout<<"\n\tHow many items are there?   ";
        cin>>n;
        printstars();
        total=0;
        for(int i=0;i<n;i++)
        {
            cout<<"\n\nEnter the Product ID of the Product "<<i+1<<"  :  ";
            cin>>order_arr[i];
            cout<<"\nEnter the quantity of Product "<<i+1<<"  :  ";
            cin>>quan[i];
        }
        system("cls");
        display_nce();
        cout<<"\n\n***********************************INVOICE**************************************\n\n";
        cout<<setw(80);
        time();
        customer::c_display();
        cout<<"\n\n\n";
        cout<<"\nPr ID\tPr Name\t\tQuantity \tPrice \tAmount \tAmount after discount\n";
        for(int x=0;x<n;x++)
        {
            file.open("product.dat",ios::in);
            file.seekg(0);
            product::fread();
            while(!file.eof())
            {
                if(id==order_arr[x])
                {
                    amt=rate*quan[x];
                    damt=amt-((amt*dis)/100);
                    cout<<"\n"<<order_arr[x]<<"\t"<<name<<"\t"<<quan[x]<<"\t\t"<<rate<<"\t"<<amt<<"\t\t"<<damt;
                    total+=damt;
                }
                product::fread();

            }
            file.close();
        }
        cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
        getch();
        }




};
//****************************************************//
void display_main()
{
    display_nce();
    cout<<"\t\t _______________________________"<<endl;
    cout<<"\t\t|**********MAIN   MENU**********|"<<endl;
    cout<<"\t\t|_______________________________|"<<endl;
    cout<<"\n\n\n";
    cout<<"\n\t\t<1>Place Order"<<
          "\n\t\t<2>Admin Panel"<<
          "\n\t\t<3>Log out"<<
          "\n\t\t<4>Exit"<<endl;

}

void start_screen()
{
    string str1,str2,str3,str4,str5;
    str1=" A PROJECT ON";
    str2=" SUPER MARKET BILLING SYSTEM";
    cout<<"\n\n\n\n\t\t\t\t";
    for(int i=0;i<13;i++)
    {
        cout<<str1[i];
        Sleep(200);

    }
    cout<<"\n\n\t\t\t";
    for(int i=0;i<28;i++)
    {
        cout<<str2[i];
        Sleep(200);

    }
    system("cls");
    cout<<"\n\n\n\t\t\t*****************************"<<
          "\n\t\t\t*\tA PROJECT ON        *"<<
          "\n\t\t\t*                           *"
          "\n\t\t\t*SUPER MARKET BILLING SYSTEM*"<<
          "\n\t\t\t*****************************\n";
    cout<<"\n\n\t\t\t\t\t-";
    for(int i=0;i<15;i++)
    {
        cout<<str3[i];
        Sleep(200);

    }
    cout<<"\n\n\t\t\t\t\t";
    for(int i=0;i<17;i++)
    {
        cout<<str4[i];
        Sleep(200);

    }
    cout<<"\n\n\t\t\t\t\t";
    for(int i=0;i<21;i++)
    {
        cout<<str5[i];
        Sleep(200);

    }
 }
//****************MAIN PROGRAM****************//

int main()
{

    int choice,ch,v;
    user ur;
    product pr;
    bill bi;
    system("COLOR b0");
    start_screen();
    system("cls");
    main:
    for(int c=1;c<=3;c++)
    {
        v=ur.verify();
        if(v==1)
        {

        while(1)
        {
            system("cls");
            display_main();
            cout<<"\n\t\tEnter your choice  :  ";
            cin>>choice;
            switch(choice)
            {
                case 1:
                    system("cls");
                    bi.place_order();
                    break;

                case 2:
                    system("cls");
                    display_nce();
                    pr.admin_menu();
                    break;

                case 3:
                    system("cls");
                    goto main;
                    break;
                case 4:
                    exit(0);
                    break;

                default :
                    cout<<"Invalid choice";
                }
            }

        }
        else
        {
            cout<<"\n\n\tWrong username or password.\n\n"<<endl;
            printstars();
            cout<<"\n\n\t You have "<<3-c<<" chances left.";
            getch();
            system("cls");
        }
    }
    return 0;
}
