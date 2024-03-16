/*
> Normal queue - single ended - push at back, pop from front
> Version number - with each push AND pop, version number(int) is incremented
> Corresponding to a particular version number, we need a start and an end. We are going to use an array of objects that store this.
> NO STL CONTAINERS/ALGORITHMS: No queues, vectors, maps or even pairs used.

Assumptions:
> Version number is an integer. That is what it looks like from the question, it makes the mapping of version number to start/end indices much easier 
> Currently, not designed to work with std::iterator. If required, can implement a helper iterator class for functions such as .begin(), .end(), as well as the ability to use this data structure with STL algorithms
> Initialiser list is currently not supported, because logically, enqueue operations should be sequential. Order matters.
*/


#ifndef VERSION_H_
#define VERSION_H_
#include <iostream>
#include <exception>
#include <cstring>

//Define the initial size:
#define INITIAL_SIZE 20000 
#define RESCALE_FACTOR 2 //1.5 might be better for some applications


template <class T>
class version_queue
{
    private:
        //Helper struct:
        struct version_details
        {
            int begin;
            int end;
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
        int begin;
        int end;

        void resize(size_t new_size=RESCALE_FACTOR*INITIAL_SIZE);       

    public:
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
        void enqueue(T f);

        //Dequeue(pop)
        T dequeue();

        //Print(version): Prints the state of the queue for a particular version:
        void print(int version_number);

        //Some helper functions (similar to what STL containers have):
        int getVersion();
        int size();
        T front();
        T back();
        bool empty();
};

class underflow : public std::exception 
{
    public:
        char* what ();
};


//Default constructor override:
template <class T>
version_queue<T>::version_queue()
{
    this->q = new T[INITIAL_SIZE];
    this->version = new version_details[2*INITIAL_SIZE];
    this->current_max_size = INITIAL_SIZE;
    this->current_version = 0;
    this->begin = 0;
    this->end = 0;
    this->version[0].begin = 0;
    this->version[0].end = 0;
}

//Parameterised constructor, parameter is the size
template <class T>
version_queue<T>::version_queue(size_t s)
{
    this->q = new T[s];    
    this->version = new version_details[2*s];
    this->current_version = 0;
    this->current_max_size = s;
    this->begin = 0;
    this->end = 0;
    this->version[0].begin = 0;
    this->version[0].end = 0;
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
    this->begin = other.begin;
    this->end = other.end;
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
    this->begin = other.begin;
    this->end = other.end;
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
void version_queue<T>::enqueue(T f)
{
    if(end+1 == current_max_size)
    {
        resize(RESCALE_FACTOR*current_max_size);
    }

    //Add the element to the end:
    q[end] = f;

    current_version += 1;
    version[current_version].begin = begin;
    version[current_version].end = end+1;

    end++;
}

//Dequeue(pop)
template <class T>
T version_queue<T>::dequeue() 
{
    if(begin<end)
    {
        T dequeued = front();        

        current_version +=1;
        version[current_version].begin = begin+1;
        version[current_version].end = end;

        begin++;

        return dequeued;
    }
    else
    {
        throw(underflow());
        return 0;
    }
}

//Print(version): Prints the state of the queue for a particular version:
template <class T>
void version_queue<T>::print(int version_number)
{
    if(version_number<=current_version && version_number>0)
    {
        if(version[version_number].begin<version[version_number].end)
        {
            std::cout<<"Printing in order: first entry on the left"<<std::endl;
            for(auto i=version[version_number].begin; i<version[version_number].end; i++)
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
int version_queue<T>::getVersion()
{
    return current_version;
}

template <class T>
int version_queue<T>::size()
{
    return (end-begin);
}

template <class T>
T version_queue<T>::front()
{
    if(end<current_max_size)
    {
        return q[end];
    }
    else
    {
        throw(underflow());
        return 0;
    }
}

template <class T>
T version_queue<T>::back()
{
    if(begin<current_max_size && begin<end)
    {
        return q[begin];
    }
    else
    {
        throw(underflow());
        return 0;
    }
}
template <class T>
bool version_queue<T>::empty()
{
    if(size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char* underflow::what() 
{
    char* ret = new char[40];
    strcpy(ret, "Memory underflow, no elements in queue\n");
    return ret;
}

#endif