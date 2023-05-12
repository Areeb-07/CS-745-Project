#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
    
    // Allocating two blocks adjacent to each other
    long long* a = (long long*) malloc(1600);
    long long* b = (long long*) malloc(1600);

    // The size of chunk is 33, 16 the allocated size,
    // 8 + 8 for metadata (size + prev_size),
    // 1, the least significant digit showing previous block is not free
    // Previous size will be 0 as size of previous chunk doesn't matter when not free
    cout << "Before overflow\n";
    cout << "Size of chunk b: " << *(b-1) << "\n";
    cout << "Size of chunk precious to b: " << *(b-2) << "\n";
    cout << "Address of chunk b: " << (long long)b << "\n";

    // Data to be filled in a, more than it can hold
    // 10000 will be set as prev_size of next chunk
    // 1616 will be set as the size of the chunk
    long long arr[] = {10000,1616};
    // Filling data in the chunk a more than it can hold, causing buffer overflow to b
    // which will corrupt its metadata
    for (int i=0; i < 202; i++){
        long long* c = (long long *)((long long)&a[i]);
        if (i <= 200) *c = 0;
        else *c = arr[i-200];
    }

    // With the least significant bit 0, it will appear as if previous chunk is free
    // When the chunk is freed, it will be merged with the supposed free previous chunk
    // Thus, the next malloc will happen at the start of this merged chunk
    cout << "After overflow\n";
    cout << "New size of chunk b: " << *(b-1) << "\n";
    cout << "New previous size of chunk b: " << *(b-2)<<"\n";

    // Free the chunk
    free(b);

    // A new malloc
    long long* d = (long long*) malloc(16);

    // The address of this chunk is far away
    // It is also possible to reach the stack in this way, if its location can be known
    cout << "Address of newly allocated chunk: " << (long long)(d);
    return 0;
    
    // When free is called, the program exits as the corrupted metadata is detected
    // Nevertheless, the following conclusions can still be drawn
    // Thus a buffer overflow in a chunk can corrupt metadata of a neighbouring chunk
    // This can result in a subsequent malloc at an arbitrary location

}