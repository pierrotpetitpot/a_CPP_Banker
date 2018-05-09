//
//  Account.cpp
//  banker
//
//  Created by Pierre  Tran  on 2018-05-05.
//  Copyright © 2018 Pierre  Tran . All rights reserved.
//

#include<iostream>
#include <stdio.h>
#include <string.h>
#include<fstream>
#include<cctype>
#include<iomanip>
#include "Account.hpp"
using namespace std;


void account::create_account()
{
   
takenID: cout<<"\nEnter an account number :";
    cin>>ID;
    
    while(cin.fail()){      //error handling
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"\nInvalid input, please enter interger\n";
        cin>>ID;
    }
    
    account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.getID()==ID)              //to ensure that no other account has the same ID
        {
            cout<<"This ID is already in use\n\n";
            goto takenID;
        }
    }
    inFile.close();
    
    cout<<"\n\nEnter the name of the account holder : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nEnter Type of the account (C/S) : ";
    cin>>type;
    type=toupper(type);
    while(type != 'C' && type != 'S'){      //error handling
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Input, plese enter valid input.\n";
        cin >> type;
        type = toupper(type);
    }
here: cout<<"\nEnter an initial ammount : ";
    cin>>deposit;
    while(deposit < 0 || cin.fail()){     //error handling, testing goto function
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Invalid input, please enter a positive value.\n";
        goto here;
    }
    cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
    cout<<"\nAccount No. : "<<ID;
    cout<<"\nAccount Holder Name : " <<name;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance amount : "<<deposit;
}

void account::modify()
{
    cout<<"\nAccount No. : "<<ID;
    cout<<"\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify Type of Account : ";
    cin>>type;
    type=toupper(type);
}


void account::dep(double x)
{
    deposit+=x;
}

void account::draw(double x)
{
    deposit-=x;
}

void account::report() const
{
    cout<<ID<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


double account::getID() const
{
    return ID;
}

double account::getDeposit() const
{
    return deposit;
}

char account::getType() const
{
    return type;
}
