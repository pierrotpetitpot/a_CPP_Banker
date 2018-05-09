//
//  main.cpp
//  accountMain
//
//  Created by Pierre  Tran  on 2017-03-03.
//  Copyright © 2018 Pierre  Tran . All rights reserved.

#include<iostream>
#include <stdio.h>
#include <string.h>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

#include "Account.hpp"      // this is the class file



void write_account();    //function to write record into binary a file called Account1.dat
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void display(int);    //function to display account data
void displayAll();        //function to display all account data
void deleteAccount(int);    //function to delete record
void modifyAccount(int);    //function to modify record
void intro();    //intro screen


void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("Account1.dat",ios::binary|ios::app);  //opening file
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account)); //writing to file
    outFile.close();
}

void deposit_withdraw(int ID, int option)
{
    double amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("Account1.dat", ios::binary|ios::in|ios::out);
    if(!File)       //error handling if file does not exist
    {
        cout<<"File does not exist or could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.getID()==ID)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                cout<<"\n\nEnter The amount to be deposited: ";
                cin>>amt;
                while(amt < 0){     //error handling for negative value of deposit
                    cout<<"\t\nInvalid input, please enter positive value: ";
                    cin>>amt;
                }
                ac.dep(amt);
                cout<<"\n";
                ac.show_account();
            }
            if(option==2)
            {
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
            insufficienceBalance: cout<<"\n\nEnter The amount to be withdrawn: ";
                cin>>amt;
                while(amt < 0){      //error handling for negative value of withdrawal
                    cout<<"\t\nInvalid input, please enter positive value: ";
                    cin>>amt;
                }
                int bal=ac.getDeposit()-amt;
                while(bal<0){
                    cout<<"Insufficience balance\n";
                    goto insufficienceBalance;
                }
                
                ac.draw(amt);
                cout<<"\n";
                ac.show_account();
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
    File.close();   //to avoid leaking
    if(found==false)
        cout<<"\n\n Record Not Found ";
}

void display(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("Account1.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File does not exist or could not be open !! Press any Key...";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";
    
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.getID()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}

void displayAll()
{
    account ac;
    ifstream inFile;
    inFile.open("Account1.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File does not exist or could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"====================================================\n";
    cout<<"A/c no.      NAME            Type    Balance\n";
    cout<<"====================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

void deleteAccount(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("Account1.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.getID()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("Account1.dat");
    rename("Temp.dat","Account1.dat");
    cout<<"\n\n\tRecord Deleted ..";
}

void modifyAccount(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("Account1.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.getID()==n)
        {
            ac.show_account();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}

void intro()
{
    cout<<"\n\n\n\t  a Bank System";
    cout<<"\n\n\n\n\tMade by Pierre Tran";
    cin.get();
}

int main()
{
    int option;
    int numID;
    intro();
    do
    {
       
        cout<<"\n\n\n\twelcome to our service bank, how can I help you?";
        cout<<"\n\n\t1. new account";
        cout<<"\n\n\t2. deposit ";
        cout<<"\n\n\t3. withdraw";
        cout<<"\n\n\t4. account information";
        cout<<"\n\n\t5. all accounts information";
        cout<<"\n\n\t6. delete account";
        cout<<"\n\n\t7. modify account";
        cout<<"\n\n\t8. exit";
        cout<<"\n\n\tSelect Your Option (1-8) ";
        cin>>option;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"\tInvalid input, please enter a valid option\n\n";
            cin>>option;
        }
       
        switch(option)
        {
            case 1:
                write_account();
                break;
            case 2:
                cout<<"\n\n\tEnter The account No. : ";
                cin>>numID;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout<<"\tPlease enter an integer: ";
                    cin>>numID;
                }
                deposit_withdraw(numID, 1);
                break;
            case 3:
                cout<<"\n\n\tEnter The account No. : ";
                cin>>numID;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout<<"\tPlease enter an integer: ";
                    cin>>numID;
                }
                deposit_withdraw(numID, 2);
                break;
            case 4:
                cout<<"\n\n\tEnter The account No. : ";
                cin>>numID;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout<<"\tPlease enter an integer: ";
                    cin>>numID;
                }
                display(numID);
                break;
            case 5:
                displayAll();
                break;
            case 6:
                cout<<"\n\n\tEnter The account No. : ";
                cin>>numID;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout<<"\tPlease enter an integer: ";
                    cin>>numID;
                }
                deleteAccount(numID);
                break;
            case 7:
                cout<<"\n\n\tEnter The account No. : ";
                cin>>numID;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout<<"\tPlease enter an integer: ";
                    cin>>numID;
                }
                modifyAccount(numID);
                break;
            case 8:
                cout<<"\n\n\tThank you for using bank management system";
                break;
            default :cout<<"\a\t Wrong input, please enter a valid option.";
        }
        cin.ignore();
        cin.get();
    }while(option!=8);
    return 0;
}
