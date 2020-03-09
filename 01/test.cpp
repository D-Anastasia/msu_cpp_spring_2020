#include <cstdio>
#include <iostream>
#include <cstring>
#include "allocator.hpp"
using namespace std;
int main(void){
	Allocator A;
	A.makeAllocator(20);

	char* p = A.alloc(10);
	if (p==NULL) cout<<"ERR: p=NULL"<<endl;
	p = A.alloc(9);
	if (p==NULL) cout<<"ERR: p=NULL"<<endl;

	p = A.alloc(1);
	if (p==NULL) cout<<"ERR: p=NULL"<<endl;

	p = A.alloc(1);
	if (p!=NULL) cout<<"ERR: p!=NULL"<<endl;

	A.reset();

	p = A.alloc(10);
	if (p==NULL) cout<<"ERR: p=NULL"<<endl;

	p = A.alloc(10);
	if (p==NULL) cout<<"ERR: p=NULL"<<endl;

	p = A.alloc(1);
	if (p!=NULL) cout<<"ERR: p!=NULL"<<endl;

	return 0;
}