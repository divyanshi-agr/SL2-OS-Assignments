#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>
using namespace std; 

bool palindrome(char str[]) {
    int l = 0; 
    int h = strlen(str) - 1; 
   
    while (h > l) 
    { 
        if (str[l++] != str[h--]) 
        { 
            return false; 
        } 
    } 
   return true;
}
  
int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_EXCL); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,NULL,0); 
  
    printf("Data read from memory: %s\n",str); 
    bool isPalindrome = palindrome(str);

    if(isPalindrome) {
        cout<<"The entered string IS a palindrome!"<<endl;
    }
    else {
        cout<<"The entered string is NOT a palindrome!"<<endl;
    }
      
    //detach from shared memory  
    shmdt(str); 
    
    // destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL); 
     
    return 0; 
}