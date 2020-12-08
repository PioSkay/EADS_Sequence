//
//  EADS Lab1
//
//  Created by Piotr Skibinski on 18/11/2020.
//


#include "Lab1.h"
template<typename Key,typename Info>
void split(const Sequence<Key,Info> &source, const Key& keyStart, int keyOccurance, int total,
           Sequence<Key,Info> &target1, int length1,
           Sequence<Key,Info> &target2, int length2)
{
    if(total < 0 or length1 < 0 or length2 < 0){
        throw "Error. total, length1 and length2 needs to be grater than zero.";
    }
    //if lenght1 and lenght2 is 0 we have nothing to do but out method is correct.
    if(length1 == 0 and length2 == 0){
    	return;
	}
	
	auto it = source.find(keyStart, keyOccurance);
    if(it == source.end()){
    	throw "Could not find the element!";
	}
    //Now we do need to gain access to the target1 and target2
    target1.clear();
    target2.clear();
    auto it_t1 = target1.begin();
    auto it_t2 = target2.begin();
    int i = 0;
    //Now lets create a loop to copy a number of elements *total*
    //We of course need to keep track of a curr because
    //number of elements to copy can be grater than number of avalible elements.
    while(i < total and it != source.end()){
        //Lets copy elements to the target1.
        //Like before we need to keep track of a curr and i.
        for(int j = 0; j < length1 and i < total and it != source.end(); j++){
            if(target1.empty()){
            	target1.push_front(it);
            	it_t1 = target1.begin();
			} else {
				it_t1 = it_t1.insert_after(it.getKey(), it.getInfo());
			}
			i++;
			it++;
        }
        //Now lets do the same to the target2.
        for(int j = 0; j < length2 and i < total and it != source.end(); j++){
            if(target2.empty()){
            	target2.push_front(it);
            	it_t2 = target2.begin();
			} else {
				it_t2 = it_t2.insert_after(it.getKey(), it.getInfo());
			}
			i++;
			it++;
        }
    }
    if(i < total)
        throw "Error. Total number of elements to copy is grater than the number of elements that are avalible to copy.";
}

int main() {
    {
        std::cout<<"Test 1: First of all example from the lecture."<<std::endl;
        Sequence<int , int> seq, a, b;
        seq.push_front(13, 0);
        seq.push_front(12, 0);
        seq.push_front(11, 0);
        seq.push_front(10, 0);
        seq.push_front(9, 0);
        seq.push_front(8, 0);
        seq.push_front(7, 0);
        seq.push_front(6, 0);
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        seq.push_front(3, 0);
        seq.push_front(2, 0);
        seq.push_front(1, 2);
        seq.push_front(11, 0);
        seq.push_front(6, 0);
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        seq.push_front(3, 0);
        seq.push_front(2, 0);
        seq.push_front(1, 5);
        split<int, int>(seq, 1, 2, 11, a, 3, b, 2);
        std::cout<<"target1: "<<std::endl<<a<<std::endl;
        std::cout<<"target2: "<<std::endl<<b<<std::endl;
    }
    {
        Sequence<int , int> seq, a, b;
        std::cout<<"Test 2: Empty main sequence."<<std::endl;
        //Our method is capable of throwing an exceptions with brief descriptions of an error.
        try{
            split<int, int>(seq, 1, 2, 11, a, 3, b, 2);
        } catch(const char* error){
            std::cout<<"Method generated an error: "<<error<<std::endl;
        }
        //Element could not been found beacuse seq is empty.
    }
    {
        std::cout<<"Test 3: The number of elements to copy is smaller than the amount of elements avaliable after finding a key."<<std::endl;
        Sequence<int , int> seq, a, b;
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        seq.push_front(3, 0);
        seq.push_front(2, 0);
        seq.push_front(1, 0);
        seq.push_front(11, 0);
        seq.push_front(6, 0);
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        try{
            split<int, int>(seq, 1, 1, 11, a, 3, b, 2);
        } catch(const char* error){
            std::cout<<"Method generated an error: "<<error<<std::endl;
            //method is throwing an exception but u can access the elements that were possible to be copied.
            std::cout<<"We can have access to the elements:"<<std::endl;
            std::cout<<a;
        }
    }
    {
        std::cout<<"Test 4: What about the incorrect parameters."<<std::endl;
        Sequence<int , int> seq, a, b;
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        seq.push_front(3, 0);
        seq.push_front(2, 0);
        seq.push_front(1, 0);
        seq.push_front(11, 0);
        seq.push_front(6, 0);
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        try{
            split<int, int>(seq, 1, 1, 11, a, -3, b, 2);
        } catch(const char* error){
            std::cout<<"Method generated an error: "<<error<<std::endl;
            //method is throwing an exception but u can access the elements that were possible to be copied.
        }
    }
    {
        std::cout<<"Test 5: What in the case of 0 and *total* lower than a *length2*."<<std::endl;
        Sequence<int , int> seq, a, b;
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        seq.push_front(3, 0);
        seq.push_front(2, 0);
        seq.push_front(1, 0);
        seq.push_front(11, 0);
        seq.push_front(6, 0);
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        try{
            split<int, int>(seq, 1, 1, 1, a, 0, b, 2);
        } catch(const char* error){
            std::cout<<"Method generated an error: "<<error<<std::endl;
            //method is throwing an exception but u can access the elements that were possible to be copied.
        }
        //Method did not throw an exception because aforementioned case is correct.
        //we get:
        std::cout<<b<<std::endl;
    }
	{
        std::cout<<"Test 6: Non-empty sequence b."<<std::endl;
        Sequence<int , int> seq, a, b;
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        seq.push_front(3, 0);
        seq.push_front(2, 0);
        seq.push_front(1, 0);
        seq.push_front(11, 0);
        seq.push_front(6, 0);
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        b.push_front(3, 3);
        try{
            split<int, int>(seq, 1, 1, 1, a, 0, b, 2);
        } catch(const char* error){
            std::cout<<"Method generated an error: "<<error<<std::endl;
            //method is throwing an exception but u can access the elements that were possible to be copied.
        }
        //Method did not throw an exception because aforementioned case is correct.
        //We just delete all elements.
        //we get:
        std::cout<<b<<std::endl;
    }
    {
        std::cout<<"Test 7: lenght1 and lenght2 == 0"<<std::endl;
        Sequence<int , int> seq, a, b;
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        seq.push_front(3, 0);
        seq.push_front(2, 0);
        seq.push_front(1, 0);
        seq.push_front(11, 0);
        seq.push_front(6, 0);
        seq.push_front(5, 0);
        seq.push_front(4, 0);
        b.push_front(3, 3);
        try{
            split<int, int>(seq, 1, 1, 1, a, 0, b, 0);
        } catch(const char* error){
            std::cout<<"Method generated an error: "<<error<<std::endl;
        }
    }
}
