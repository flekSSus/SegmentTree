#include<iostream>
#include<vector>

std::vector<long long> arrNumbers;

struct IntervalTree
{
    std::vector<long long> binHeap;

    IntervalTree()
    {
        binHeap.resize(arrNumbers.size()*2);
        for(int i(0);i<arrNumbers.size();++i)
        {
            binHeap[arrNumbers.size()+i]=arrNumbers[i];
        }
        for(int i(arrNumbers.size()-1);i>0;--i)
        {
            binHeap[i]=binHeap[2*i+1]+binHeap[2*i];
        }
    }

    void Add(int index, long long value)
    {
        binHeap[index+arrNumbers.size()]+=value;
        index+=arrNumbers.size();
        while(index>1)
        {
            index/=2;
            binHeap[index]=binHeap[index*2]+ binHeap[index*2+1];
        }
    }
    long long RangedSum(int indexL, int indexR)
    {
        long long sum(0);
        indexL+=arrNumbers.size();
        indexR+=arrNumbers.size();
         
        while(indexL<indexR)
        {
            if(indexL%2)
            {
                sum+=binHeap[indexL];
                ++indexL;
            }
            if(indexR%2)
            {
                --indexR;
                sum+=binHeap[indexR];
            }
            indexL/=2;
            indexR/=2;
        }
        return sum;
            
    }
};

int main()
{
    int arrSize(0);
    int numOfRequests(0);
    std::cin>>arrSize;

    arrNumbers.resize(arrSize,0);
    
    for(int i(0);i<arrSize;++i)
    {
        int el(0);
        std::cin>>el;
        arrNumbers[i]=el;
    }

    std::cin>>numOfRequests; 
    
    IntervalTree a;

    for(int i(0);i<numOfRequests;++i)
    {
        std::string requestName(" ");    
        std::cin>>requestName;
        if(requestName=="Add")
        {
            int index(0);
            int value(0);
            std::cin>>index>>value;
            a.Add(index,value);
        }
        else if(requestName=="FindSum")
        {
            int indexL(0);
            int indexR(0);
            std::cin>>indexL>>indexR;
            std::cout<<a.RangedSum(indexL,indexR)<<'\n';
        }
    }
}
