#include <iostream>
#include <cstdlib>
using namespace std;

// The class that will be hijacked
// Since it has a virtual function, at the very beginning of the memory of it instance,
// a pointer, namely vpointer, to its vtable will be stored
// In this program, I attempt to hijack the vtable of this class,
// by creating a fake vtable and replacing the vpointer to point to this fake vtable

class Greeter{
    public:
    Greeter(){}
    virtual void greet(){
        cout<<"Hello World!\n";
    }
};

void imposter_greet(){
    cout<<"The vtable has been hijacked successfully!\n";
}


int main() {    
    // First make the fake vtable
    // The fake vtable is a chunk in heap of arbitrary size (16)
    long long *fake_vtable;
    fake_vtable=(long long *)malloc(16);
    
    // Create an instance of the class to be hijacked
    // Creating an instance in this way will create the object in heap
    Greeter* greeter = new Greeter();
    
    // Call the greet function to show its initial behaviour
    cout << "Initial call to the member function:\n";
    greeter->greet();

    // The address of the fake_vtable
    cout<<"Address of fake vtable: "<<((long long)fake_vtable)<<"\n";

    // The address of the true vtable
    cout<<"Address of true vtable: "<<((long long*)greeter)[0]<<"\n";

    // An array containing data that needs to be filled in the chunk
    // The array size is evidently more than chunk size
    // Hence, it will overflow to the next object
    long long arr[] = {(long long)&imposter_greet,0,0,0,(long long) fake_vtable};

    // Loop over the elements of the array and put it in the chunk
    // The start of the chunk is filled with imposter function address
    // As this chunk is treated as vtable, the imposter function address
    // will be used when a call to the member function is made
    for (int i=0; i < end(arr) - begin(arr); i++){
        // Convert the addresses of memory to long long
        // At each address corresponding array item is placed
        // As the last element is over the bounds, it overflows to the next object
        // Hnce, the vpointer is repleced
        long long * j = (long long *)((long long)&fake_vtable[i]);
        *j=arr[i];
    }
    
    // Address of the vtable after hijacking, it will be same as fake_vtable
    cout<<"Address of true vtable after hijacking: "<<((long long*)greeter)[0]<<"\n";

    // Call the greet function again
    // The behaviour will be different this time as vtable has been hijacked
    cout<<"Final call to the member function:\n";
    greeter->greet();

    // In this way the vtable can be hijacked by a buffer overflow on the heap
    // and the program flow can be diverted to any function whose address is in fake v_table    
}