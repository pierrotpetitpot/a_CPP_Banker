//
//  Account.hpp
//  banker
//
//  Created by Pierre  Tran  on 2018-05-05.
//  Copyright © 2018 Pierre  Tran . All rights reserved.
//

#ifndef Account_hpp
#define Account_hpp

#include <stdio.h>
class account
{
    int ID;
    char name[50];
    double deposit;
    char type;
public:
    void create_account();    //function to get data from user
    void show_account() const;    //function to show data on screen
    void modify();    //function to modify data
    void dep(double);    //function to accept amount and add to balance amount
    void draw(double);    //function to accept amount and subtract from balance amount
    void report() const;    //function to show data in tabular format
    double getID() const;    //function to return account ID
    double getDeposit() const;    //function to return balance amount
    char getType() const;    //function to return type of account
};         //cl
#endif /* Account_hpp */
