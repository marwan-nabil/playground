#include "std_lib_facilities.h"
using namespace std;

int printvec(vector<int> myvec,int index)
{ 
    if(index < myvec.size())
        cout << myvec[index] << printvec(myvec,index+1);
    cout << endl;
}

int main(int argc,char **argv)
{
    
    vector<int> vec1({4,5,7,8,9,4,2,3});
    printvec(vec1,0); //(int) *argv[1]);
    return 0;
}
