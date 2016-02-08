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
#include <boost/shared_ptr.hpp>
#include <vector>

using namespace std;


void fileOpen(boost::shared_ptr<std::string> arr,string filepath){

		static boost::mutex ioMutex;
		boost::mutex::scoped_lock l(ioMutex);
	    std::string str((std::istreambuf_iterator<char>(*(std::auto_ptr<std::ifstream>(new std::ifstream(filepath.c_str()))).get())), std::istreambuf_iterator<char>()
	    );
	    arr->append(str.c_str());

}



void fileWrite(const char* filename, boost::shared_ptr<std::string> strings){

			vector<string> str_v;
			boost::split(str_v,*strings,boost::is_any_of("||"));
			ofstream fout(filename,std::ios::app);
			for(size_t i=0;i<str_v.size();i++){
				fout<<str_v.at(i)<<"\n";
			}
			fout.close();

}

int main(int argc, char* argv[]) {

vector<string> filepath;
string fileOut;

	if(argc > 1){
			if((strcmp(argv[1],"-I")==0)){
				for(int i=1;i<argc-1;i++){
						if((strcmp(argv[i],"-O")==0)){
							fileOut=argv[i+1];

						}else{
							try{
								string str(argv[i+1]);
								filepath.push_back(str);

							}catch(...){
								cout<<"123"<<endl;
							}
				}
			}
		}

			boost::thread_group g;
			boost::shared_ptr<std::string> str(new string(""));
			for(size_t i=0;i<filepath.size()-1;i++){
				string path=filepath.at(i);
				g.create_thread(boost::bind(fileOpen,str,path));
		}
				g.join_all();
				fileWrite(fileOut.c_str(),str);

	}else{
		cout<<"arguments is null"<<endl;
		cout<<"for parse files please input arguments like this template :\n-I [input files path] -O [output file path]"<<endl;
	}


	return 0;
}
