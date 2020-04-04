#define RELEASE

#ifdef DEBUG
int assert(int a){
	return a? 1 : 0;
}
#endif

#ifdef RELEASE
#define assert(a) 
#endif

int main(){
	assert(6);
	return 0;
}
