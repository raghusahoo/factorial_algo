
//program to print the product of two numbers
//using recursion
//there is no conditions in getting input form the user

//header files
#include <iostream>
#include<vector> 
#include<cmath>

//predefined command to use cout/cin 
using namespace std;  

//marco to define the size of different arrays
#define size 1000  

//container to store the prime factorisation 
int store_prime_factorisation[size];   
int store_prime_num[size];

//prime count
int prime_count = 0;

int arr[size];
int r=0,s=0;

//container to store the result of the product-sum
int result[size] = {0};

//container to store the result of product
int perfect[size] = {0};

//container to store one of the two number which need to be multiplied
int mul[size] = {0};

//size of resultant and initial array 
int index_size = 0,index=0;

//recursive function to add two of digits passed by the product function 
//like    67458
 //      59466
 //   =  662118

void add_to_result(int i,int j,int t,int temp){
    if(i == j){
        if(temp){
            result[j+t] = temp;
            index_size = j++;
        }
        index_size = j-1+t;
        return;
    }
    else{
        temp += result[i+t] + perfect[i];
        result[i+t] = temp % 10;
        temp/=10;
        add_to_result(i+1,j,t,temp);
    }
}

//recursive function to find proudct of two numbers
void product(int a, int i, int temp,int t){
    if(i == index){
        index_size = 0;
        if(temp)perfect[i++] = temp;
        add_to_result(0,i,t,0);
        return;
    }
    else{
        temp += mul[i] * a;
        perfect[i] = temp % 10;
        temp/=10;
        product(a, i+1, temp,t);
    }
}

//iterate each digits of the next number to find         
void iterate_digits_of_num(int a,int t){
    if(a == 0)return;
    else{
        product(a % 10, 0, 0,t);
        iterate_digits_of_num(a/10,t+1);
    }
}

//funtion to find the number of digits it should have 
int find_number_digits(int a){

    return 8 * (log2(10) / log2(a));
}

//recursive function to find the prime factorisation of any number 
void find_prime_factorisation(int a, int store_a, int i, int count){  
    if(i > store_a/2){
        if(a == store_a){
            if(store_prime_factorisation[store_a] != 0)store_prime_factorisation[a]++;
            else{
                store_prime_num[prime_count] = a;
                prime_count++;
            }
        }
        if(count)store_prime_factorisation[a] += count;
        return;
    }
    else{
        if(a % i == 0){
            a = a/i;
            count++;
        }
        else{
            store_prime_factorisation[i] += count;
            i++; count = 0;
        }
        find_prime_factorisation(a, store_a, i, count);
    }
}

//function to interate the number right from 1 to extreme
void iterate_num(int num){
    if(num == 1)return;
    else
        find_prime_factorisation(num, num, 2, 0);

    iterate_num(num-1);
}   

int main(){

    //taking input form the user
    int num, j=0, temp, temp1, temp2, k=0, store_product[100], i=0,z=1;
    cout<<"enter your number to find factorial:";
    cin>>num;

    //calling the function
    iterate_num(num);

    //seperating the like prime factors
    for(i = 0; i<=num/2; i++){
        if(store_prime_factorisation[i] != 0){
            temp = find_number_digits(i);
            temp1 = store_prime_factorisation[i]/temp;
            temp2 = store_prime_factorisation[i] % temp;

            for(j=0; j<temp1; j++){
                arr[k] = pow(i,temp);
                k++;
            }
            if(temp2){
                arr[k] = pow(i,temp2);
                k++; 
            }
        }
    }

    //storing the first number into an array
    int t = arr[0];
    while(t){
        mul[index] = t%10;
        index++;
        t/=10;
    }

    while(z != k){
        int t=0;
        iterate_digits_of_num(arr[z],t); 

    //for the next multiplier, multiplicant will be the previous product
    //so we have product the two numbers
       
        //copying the result of two product in the first number 
        //and again initilizing the value with 0 in the resultant array
        for(i = 0; i<=index_size; i++){
            mul[i] = result[i];
            result[i] = 0;
        }
        index = index_size + 1;
        index_size = 0;
        z++;
    }
    t=0,z=0;

    //iterating the pairs which is stored in array(arr) to find factorial
    while(z != prime_count){
        int t=0;
        iterate_digits_of_num(store_prime_num[z],t); 

    //for the next multiplier, multiplicant will be the previous product
    //so we have product the two numbers
        for(i = 0; i<=index_size; i++){
            mul[i] = result[i];
            result[i] = 0;
        }
        index = index_size + 1;
        index_size = 0;
        z++;
    }
    
    //output part
    int sum = 0;
    //printing the result of factorial of a number
    for(i=index-1; i>=0;i--){
        cout<<mul[i]<<" ";
        sum += mul[i];
    }
    cout<<endl<<sum;
return 0;
}
