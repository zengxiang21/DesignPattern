#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class Car
{
public:
    virtual void createCar()=0;
};
class CarA:public Car
{
public:
    void createCar()
    {
        cout<<"CarA is created"<<endl;
    }
};
class CarB:public Car
{
public:
    void createCar()
    {
        cout<<"CarB is created"<<endl;
    }
};
class Factory
{
public:
    static Car* FactoryCreateCar(char name)
    {
        if(name=='A')
        {
            return new CarA();
        }
        if(name=='B')
        {
            return new CarB();
        }
    }
};
int main()
{
    Car* car=Factory::FactoryCreateCar('B');
    car->createCar();
    return 0;
}