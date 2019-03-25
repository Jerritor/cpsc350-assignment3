#include <iostream>

using namespace std;

//Template Class Declaration
template <class T>
class GenStack
{
	public:
		GenStack(); //constructor
		GenStack(int maxSize); //overloaded constructor
		~GenStack(); //destructor

		void push(T d); //add to top of stack
		T pop();  //remove and return top of stack
		T peek(); //also top() - returns top of stack

		int getSize();	//size of stack
		bool isEmpty();
		bool isFull();

		int size; //current size of stack
		int top; //top index of stack
	private:
		//dynamic memory allocation - size will be initialized at instantiation
		T *myArray;
};

//Template Definition
template <class T>
GenStack<T>::GenStack() //default constructor
{
	//initialize variables to default values
	//'new' allocates to heap. memory is deallocated in destructor
	size = 100; //100 is my default constructor size
	myArray = new T[size];
	top = -1;
}

template <class T>
GenStack<T>::GenStack(int maxSize) //overloaded constructor
{
	myArray = new T[maxSize];
	size = maxSize;
	top = -1;
}

template <class T>
GenStack<T>::~GenStack() //default constructor
{
	delete myArray; //deallocates myArray from heap memory
}

template <class T>
void GenStack<T>::push(T d)
{
	if (size-1 == top) //if stack is full, resize
	{
		int newsize = size+50; //increase size by this amount

		T *newArray = new T[newsize];
		//myArray = new T[newsize];

		for(int i = 0; i < newsize; i++)
		{
			if (!isEmpty()) newArray[i] = pop();
			else
			{
				top = i;
				break;
			}
		}
		size = newsize;
		T* oldArray = myArray;
		myArray = newArray;

		delete oldArray;
	}

	//check if stack is not empty
	if (size > 0)
	{
		myArray[++top] = d; //top is pre-incremented to start at 0
	}
}

template <class T>
T GenStack<T>::pop()
{
	if (!isEmpty()) //check if empty
	{
		T temp = myArray[top--];
		return temp;
	}
	else
	{
		throw "Stack Empty Exception";
		return 0;
	}

	//OTHER VERSION
	if (!isEmpty())
		return myArray[top--];
}

template <class T>
T GenStack<T>::peek()
{
	return myArray[top];
}

template <class T>
bool GenStack<T>::isFull()
{
	return (top == size-1);
}

template <class T>
bool GenStack<T>::isEmpty()
{
	return (top == -1);
}

template <class T>
int GenStack<T>::getSize()
{
	return top+1; //+1 bc top initialized as -1
}
