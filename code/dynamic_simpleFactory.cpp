#include<iostream>
#include<bits/stdc++.h>
using namespace std;
//动态对象创建类
//该类包含一个map实现"NAME"->对象生成函数的反射机制
//该类使用单例模式实现，有注册名字+回调函数的接口reg
//该类有getbyname接口，通过名字"name"调用回调函数(new 对象并返回)
class ObjCreate
{
private:
    map<string,function<void*(void)>> m_map;
    ObjCreate()=default;
    ObjCreate(const ObjCreate& obj)=delete;
    ObjCreate& operator=(const ObjCreate& obj)=delete;
public:
    static ObjCreate& getObjInstance()
    {
        static ObjCreate obj;
        return obj;
    }
    void reg(string name,function<void*(void)> func)
    {
        m_map.insert({name,func});
    }
    void* getbyname(string name)
    {
        auto it=m_map.find(name);
        if(it==m_map.end())
        {
            return nullptr;
        }
        else
        {
            return it->second();
        }
    }
};
//注册行为调用类
class regAction
{
public:
    regAction(string name,function<void*(void)> func)
    {
        ObjCreate::getObjInstance().reg(name,func);
    }
};
//使用宏定义注册新"name"+回调函数，只需要REGISTER_DECLARE(name)便可以注册到map中
//宏定义中#->转化为字符串，##表示拼接
#define REGISTER_DECLARE(class_name) \
	class_name* ObjectCreator##class_name() \
	{ \
		return new class_name; \
	} \
	regAction g_Register##class_name(#class_name, (function<void*(void)>)ObjectCreator##class_name);

class Fruit
{
public:
    virtual void eat()=0;
};

class apple:public Fruit
{
public:
    virtual void eat()
    {
        cout<<"吃苹果"<<endl;
    }	
};
//将该类注册到对象创建类的map中去
REGISTER_DECLARE(apple);

class banana:public Fruit
{
public:
    virtual void eat()
    {
        cout<<"吃香蕉"<<endl;
    }
private:
};
REGISTER_DECLARE(banana);

class Factory
{
public:
	static Fruit* CreateFruitObject(const std::string& name)
	{
		return static_cast<Fruit*>(ObjCreate::getObjInstance().getbyname(name));
	}
};


int main()
{
    Fruit* fru=Factory::CreateFruitObject("apple");
    fru->eat();
    fru=Factory::CreateFruitObject("banana");
    fru->eat();
    return 0;
}