#include "version_queue.h"
#include <iostream>
#include <exception>
#include <chrono>

//Parameterised Construcor
version_queue<int> v(10000000);

int main()
{
    
    int test_size = 10000000;

    /*
    This section tests the time taken to perform 40,000 enqueue operations in milliseconds
    */
    auto startTime = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<test_size; i++)
    {
        v.enqueue(i);
    }
    auto endTime = std::chrono::high_resolution_clock::now(); 
    std::cout<<"Time taken for enqueing "<<test_size<<" elements is: "<<std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count()<<" milliseconds"<<std::endl;   

    /*
    This section tests the time taken to perform 40,000 dequeue operations in milliseconds
    */
    int deqd = 0;
    startTime = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<test_size; i++)
    {
        deqd = v.dequeue();
    }
    endTime = std::chrono::high_resolution_clock::now();
    std::cout<<"Time taken for dequeing "<<test_size<<" elements is: "<<std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count()<<" milliseconds"<<std::endl;   

    //Copy constructors:
    version_queue<int> v2(v);
    version_queue<int> v3 = v;

    //Sample print function:
    std::cout<<"Sample print function at version# 1000: "<<std::endl;
    v.print(1000);

    int option = 1;
    float input = 0;
    float output = 0;
    int ver = 0;


    /*
    This section can take user input to perform different operations on the queue
    */
    while(option!=6)
    {
        std::cout<<"Enter your choice:\n";
        std::cout<<"1. Enqueue\n";
        std::cout<<"2. Dequeue\n";
        std::cout<<"3. Print\n";
        std::cout<<"4. Get current version number\n";
        std::cout<<"5. Get current size of queue\n";
        std::cout<<"6. Exit\n";
        std::cin>>option;

        switch (option)
        {
            case 1:
                std::cout<<"Enter a number to enqueue"<<std::endl;
                std::cin>>input;
                v.enqueue(input);
                break;

            case 2:
                try
                {
                    output = v.dequeue();
                }
                catch(underflow uf)
                {
                    std::cout<<uf.what();
                    break;
                }
                std::cout<<"First element deqeueued, the element is: "<<output<<std::endl;
                break;

            case 3:
                std::cout<<"Enter a version number: "<<std::endl;
                std::cin>>ver;
                v.print(ver);
                break;
            case 4:
                std::cout<<"Current version number is: "<<v.getVersion()<<std::endl;
                break;
            case 5:
                std::cout<<"Current size of queue is: "<<v.size()<<std::endl;
                break;
            case 6:
                std::cout<<"Closing user interface"<<std::endl;
                break;
            default:
                std::cout<<"Invalid choice!"<<std::endl;
                break;
        }
    }

    std::cout<<"Closing..."<<std::endl;
    return 0;
}
