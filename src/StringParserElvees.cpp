//============================================================================
// Name        : StringParserElvees.cpp
// Author      : Alexey Khotchenkov
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>


using namespace std;

void split(){
	string line("test-test2-test3");
	vector<string> strs;
	boost::split(strs,line,boost::is_any_of("-"));

	cout << "* size of the vector: " << strs.size() << endl;
	for (size_t i = 0; i < strs.size(); i++)
	    cout << strs[i] << endl;
}

void file(string filepath){
	fstream file(filepath.c_str());

}

int main(int argc, char* argv[]) {

//	boost::thread thr(print,10);
//	boost::thread thr1(print,11);
//	boost::thread thr2(print,12);
//
//	thr.join();
//	thr1.join();
//	thr2.join();

	if(argc>1){
		for(int i=0;i<2;i++){
			cout<<argv[i]<<endl;
		}
	}else{
		split();
	}


	return 0;
}
