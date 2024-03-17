/*
> Normal queue - single ended - push at back, pop from front
> Version number - with each push AND pop, version number(int) is incremented
> Corresponding to a particular version number, we need a start_index and an end_index. We are going to use an array of objects that store this.
> NO STL CONTAINERS/ALGORITHMS: No queues, vectors, maps or even pairs used.

Assumptions:
> Version number is an integer. That is what it looks like from the question, it makes the mapping of version number to start/end indices much easier 
> Initialiser list is currently not supported.
*/


#ifndef VERSION_H_
#define VERSION_H_
#include <iostream>
#include <assert.h>
#include <cstring>

//Define the constants:
#define INITIAL_SIZE 4096 //Power of 2
#define RESCALE_FACTOR 2 //1.5 might be better for some applications


template <class T>
class version_queue
{
    private:
        //Helper struct:
        struct version_details
        {
            int start_index;
            int end_index;
        };

        //Actual container:
        T* q;

        //Helper object:
        version_details* version;       

        //Current Max Size of queue:
        size_t current_max_size;        

        //Current Version:
        int current_version;

        //Pointers to front and back for current version
        int start_index;
        int end_index;

        void resize(size_t new_size=RESCALE_FACTOR*INITIAL_SIZE);       

    public:
        //a C pointer is a valid iterator
        typedef T* iterator;

        //Default constructor override:
        explicit version_queue();

        //Parameterised constructor:
        explicit version_queue(size_t s);

        //Copy assignment operator
        version_queue& operator=(version_queue& v);

        //Copy constructor
        explicit version_queue(version_queue& other);

        //Destructor:
        ~version_queue();

        //Enqueue(push):
        void enqueue(const T& f);

        //Dequeue(pop)
        T dequeue();

        //Print(version): Prints the state of the queue for a particular version:
        const void print(int version_number);

        //Some helper functions (similar to what STL containers have):
        const int getVersion();
        const int size();

        iterator front();
        iterator begin();//Same as front but enables some c++11-17 features and algorithms that only work with a .begin() and .end() method

        iterator back();
        iterator end();//Same as front but enables some c++11-17 features and algorithms that only work with a .begin() and .end() method

        const bool empty();
};


//Default constructor override:
template <class T>
version_queue<T>::version_queue()
{
    this->q = new T[INITIAL_SIZE];
    this->version = new version_details[2*INITIAL_SIZE];
    this->current_max_size = INITIAL_SIZE;
    this->current_version = 0;
    this->start_index = 0;
    this->end_index = 0;
    this->version[0].start_index = 0;
    this->version[0].end_index = 0;
}

//Parameterised constructor, parameter is the size
template <class T>
version_queue<T>::version_queue(size_t s)
{
    this->q = new T[s];    
    this->version = new version_details[2*s];
    this->current_version = 0;
    this->current_max_size = s;
    this->start_index = 0;
    this->end_index = 0;
    this->version[0].start_index = 0;
    this->version[0].end_index = 0;
}

//Copy assignment
template <class T>
version_queue<T>& version_queue<T>::operator=(version_queue<T>& other)
{
    version_queue(other.current_max_size);
    this->q = other.q;
    this->version = other.version;
    this->current_max_size = other.current_max_size;
    this->current_version = other.version;
    this->start_index = other.start_index;
    this->end_index = other.end_index;
}


//Copy constructor
template <class T>
version_queue<T>::version_queue(version_queue<T>& other)
{
    version_queue(other.current_max_size);
    this->q = other.q;
    this->version = other.version;
    this->current_max_size = other.current_max_size;
    this->current_version = other.current_version;
    this->start_index = other.start_index;
    this->end_index = other.end_index;
}

template <class T>
version_queue<T>::~version_queue()
{
    delete[] q;
    delete[] version;
}


template <class T>
void version_queue<T>::resize(size_t new_size)
{
    q = (T*)realloc(q, new_size*sizeof(T));    
    version = (version_details*)realloc(version, 2*new_size*sizeof(version_details));
   
    current_max_size = new_size;
    //std::cout<<"resized to "<<current_max_size<<std::endl;
}

//Enqueue(push):
template <class T>
void version_queue<T>::enqueue(const T& f)
{
    if(end_index+1 == current_max_size)
    {
        resize(RESCALE_FACTOR*current_max_size);
    }

    //Add the element to the end:
    q[end_index] = f;

    current_version += 1;
    version[current_version].start_index = start_index;
    version[current_version].end_index = end_index+1;

    end_index++;
}

//Dequeue(pop)
template <class T>
T version_queue<T>::dequeue() 
{
    assert(start_index < end_index);//Check overflow

    T dequeued = *front();        

    current_version +=1;
    version[current_version].start_index = start_index+1;
    version[current_version].end_index = end_index;

    start_index++;

    return dequeued;
}

//Print(version): Prints the state of the queue for a particular version:
template <class T>
const void version_queue<T>::print(int version_number)
{
    if(version_number<=current_version && version_number>0)
    {
        if(version[version_number].start_index<version[version_number].end_index)
        {
            std::cout<<"Printing in order: first entry on the left"<<std::endl;
            for(auto i=version[version_number].start_index; i<version[version_number].end_index; i++)
            {
                std::cout<<q[i]<<" ";
            }
            std::cout<<std::endl;
        }
        else 
        {
            std::cout<<"Queue is empty..."<<std::endl;
        }        
    }
    else
    {
        std::cout<<"Please enter a valid version number"<<std::endl;
    }         
}

//Some helper functions:
template <class T>
const int version_queue<T>::getVersion()
{
    return current_version;
}

template <class T>
const int version_queue<T>::size()
{
    return (end_index-start_index);
}

template <class T>
typename version_queue<T>::iterator version_queue<T>::back()
{
    assert(end_index<current_max_size);//Check overflow
    
    return &q[end_index];    
}

template <class T>
typename version_queue<T>::iterator version_queue<T>::end()
{
    assert(end_index<current_max_size);//Check overflow
    
    return &q[end_index];    
}

template <class T>
typename version_queue<T>::iterator version_queue<T>::front()
{
    assert(start_index<current_max_size && start_index<end_index);//Check underflow

    return &q[start_index];    
}

template <class T>
typename version_queue<T>::iterator version_queue<T>::begin()
{
    assert(start_index<current_max_size && start_index<end_index);//Check underflow

    return &q[start_index];    
}

template <class T>
const bool version_queue<T>::empty()
{
    return end_index-start_index == 0? true:false;
}

#endif