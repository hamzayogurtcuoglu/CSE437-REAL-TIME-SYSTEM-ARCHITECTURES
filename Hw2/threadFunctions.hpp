
#include "gtu.hpp"

gtu::mutex m1;
gtu::mutex m2;

int resourceValue = 0;

void oneIncreament() {
    m1.registerThread();
    m2.registerThread();
    
    for (size_t i = 0; i < 10; i++)
    {        
        std::lock_guard<gtu::mutex> lock1(m1);
        std::lock_guard<gtu::mutex> lock2(m2);       
        cout<<"oneIncrement : "<<++resourceValue<<endl;
    }   
}
void twoIncreament(){   
    m1.registerThread();
    m2.registerThread();
       

    for (size_t i = 0; i < 10; i++)
    {
        std::lock_guard<gtu::mutex> lock2(m2);
        std::lock_guard<gtu::mutex> lock1(m1);                
        resourceValue=resourceValue+2;
        cout<<"twoIncrement : "<<resourceValue<<endl;
    } 
}
void oneDecreament(){
    m1.registerThread();
    m2.registerThread();
 
    for (size_t i = 0; i < 10; i++)
    {
        std::lock_guard<gtu::mutex> lock1(m1);
        std::lock_guard<gtu::mutex> lock2(m2); 
        cout<<"oneDecreament : "<<--resourceValue<<endl;
    }
}

void twoDecreament(){
    m1.registerThread();
    m2.registerThread();

    
    for (size_t i = 0; i < 10; i++)
    {
        std::lock_guard<gtu::mutex> lock2(m2);
        std::lock_guard<gtu::mutex> lock1(m1);   
        resourceValue=resourceValue-2;
        cout<<"twoDecreament : "<<resourceValue<<endl;
    }
}

void fourIncreament() {

    m1.registerThread();
    m2.registerThread();

    for (size_t i = 0; i < 10; i++)
    {   
        std::lock_guard<gtu::mutex> lock1(m1);
        std::lock_guard<gtu::mutex> lock2(m2);       
        resourceValue=resourceValue+4;
        cout<<"fourIncrement : "<<resourceValue<<endl;
    }   
}
void threeIncreament(){   
    m1.registerThread();
    m2.registerThread();
 
    
    for (size_t i = 0; i < 10; i++)
    {
        std::lock_guard<gtu::mutex> lock2(m2);
        std::lock_guard<gtu::mutex> lock1(m1);  
        resourceValue=resourceValue+3;
        cout<<"threeIncrement : "<<resourceValue<<endl;
    } 
}
void fourDecreament(){
    
    m1.registerThread();
    m2.registerThread();
    for (size_t i = 0; i < 10; i++)
    {
        std::lock_guard<gtu::mutex> lock1(m1);
        std::lock_guard<gtu::mutex> lock2(m2);
        resourceValue=resourceValue-4;
        cout<<"fourDecreament : "<<resourceValue<<endl;
    }
}

void threeDecreament(){
    
    m1.registerThread();
    m2.registerThread();
    for (size_t i = 0; i < 10; i++)
    {
        std::lock_guard<gtu::mutex> lock2(m2);
        std::lock_guard<gtu::mutex> lock1(m1);
        resourceValue=resourceValue-3;
        cout<<"threeDecreament : "<<resourceValue<<endl;
    }
}
