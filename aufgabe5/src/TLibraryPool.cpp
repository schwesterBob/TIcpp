#include <iostream>
#include <fstream>
#include<vector>
#include "TLibraryPool.h"
using namespace std;


TLibraryPool::TLibraryPool(string Name, TEmployee *Chairman)
{
    this->Chairman=Chairman;
    this->Name=Name;
}

string TLibraryPool::parseLine(string line, pos *position)
{
    string value;
    position->startpos=line.find("<");
    position->endpos=line.find(">");
    value=line.substr(position->startpos+1,position->endpos-position->startpos-1);
    position->startpos=line.find(value);
    position->endpos=line.find(value,  position->startpos+1);
    return value;
}

TLibraryPool::TLibraryPool(char *filename)
{
    ifstream myfile (filename);
    string line;
    string value;
    pos position;
    string tag;

    if (myfile.is_open())
    {
        cout << "Datei geoeffnet ..." << endl;
        getline (myfile,line);
        getline (myfile,line);
        tag = parseLine(line, &position);
        this->Name=line.substr(position.startpos+tag.size()+1,position.endpos-position.startpos-tag.size()-3);
        getline (myfile,line);
        tag= parseLine(line, &position);

        if(!tag.compare("Chairman"))
        {
              getline (myfile,line);
              Chairman = new TEmployee();
              Chairman->load(myfile);
              getline (myfile,line);
              //cout <<line<<"CHAIRMAN???"<<endl; // </chairman>
        }
        getline (myfile,line);
        tag= parseLine(line, &position);

        if(!tag.compare("Library"))
        {
             while ( !tag.compare("Library") )
             {
               //  cout<<tag<<"=Library?"<<endl;
                 TLibrary * library= new TLibrary();
                 library->load(myfile);
                 LibraryList.push_back(library);
                 getline (myfile,line);
                 tag= parseLine(line, &position);
             }
        }
        if(!tag.compare("Employee"))
        {
            getline (myfile,line);
            while ( !tag.compare("Employee") )
            {
                   TEmployee *person = new TEmployee();
                   person->load(myfile);
                   Customers.push_back(person);
                   getline (myfile,line);
                   getline (myfile,line);
                   tag= parseLine(line, &position);
                   getline (myfile,line);
            }
        }
        else if(!tag.compare("Customer"))
        {
           // getline (myfile,line);
            while ( !tag.compare("Customer") )
            {
                   TCustomer *person = new TCustomer();
                   person->load(myfile);
                   Customers.push_back(person);
                   getline (myfile,line);
                   getline (myfile,line);
                   tag= parseLine(line, &position);
                   getline (myfile,line);
            }
        }
    }
    else {
            cout << "Unable to open file";
            myfile.close();
    }
}

void TLibraryPool::add(TCustomer *Customer)
{
    Customers.push_back(Customer);
}

void TLibraryPool::add(TLibrary *Library)
{
    LibraryList.push_back((Library));
}

TEmployee * TLibraryPool::get_Chairman()
{
    return this->Chairman;
}

void  TLibraryPool::set_Chairman(TEmployee Chairman)
{
    *(this->Chairman)=Chairman;

}

vector<TCustomer*> TLibraryPool::get_Customers()
{
    return Customers;
}

void TLibraryPool::print()
{
    cout<< "\n" << this->Name <<endl;
    cout<<"Leitung "<< this->Chairman->getName() << endl;
    this->Chairman->getAddress().print();
    printf("Zum Buechereiverband gehoeren %d Filialen:\n", LibraryList.size() );
    for ( int i=0;i<LibraryList.size();i++ ){
        printf("\n");
        LibraryList.at(i)->print();
    }
    printf("\nDer Buechereiverband hat %d Kunden:\n",Customers.size());
     for ( int i=0;i<Customers.size();i++ ){
        printf("\n");
        (Customers.at(i))->print();
    }
}

TLibraryPool::~TLibraryPool()
{
    for(lib : LibraryList)
    {
        cout << "delete Buecherei " << lib->getName() << endl;
        delete lib;
    }
    for(customer : Customers)
    {
        delete customer;
    }
    for(loan : LoanList)
    {
        cout << "delete loan " << endl;
        delete loan;
    }
        delete Chairman;
}
