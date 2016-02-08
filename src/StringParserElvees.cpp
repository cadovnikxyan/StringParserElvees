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
#include <boost/filesystem.hpp>
#include <vector>

using namespace std;


void fileOpen(boost::shared_ptr<std::string> stringForParse,boost::shared_ptr<std::string> splitString,string filepath){

		static boost::mutex ioMutex;
		boost::mutex::scoped_lock l(ioMutex);
		vector<string> str_v;
	    std::string str((std::istreambuf_iterator<char>(*(std::auto_ptr<std::ifstream>(new std::ifstream(filepath.c_str()))).get())), std::istreambuf_iterator<char>()
	    );
	    boost::split(str_v,str,boost::is_any_of("\n"));
	    string buf=str_v.at(0);
	    stringForParse->append(buf.c_str());
	    for(size_t i=1;i<str_v.size();i++){
	    	splitString->append("||");
			splitString->append(str_v.at(i).c_str());

	    }

}



void fileWrite(const char* filename, boost::shared_ptr<std::string> strings,boost::shared_ptr<std::string> splitString){

			vector<string> str_Sp;
			boost::split(str_Sp,*splitString,boost::is_any_of("||"));
			for(size_t j=0;j<str_Sp.size();j++){
				vector<string> str_v;
				boost::split(str_v,*strings,boost::is_any_of(str_Sp.at(j).c_str()));
				ofstream fout(filename,std::ios::app);
				for(size_t i=0;i<str_v.size();i++){
					fout<<str_v.at(i)<<"\n";
				}

				fout.close();
			}

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
								boost::filesystem::path p(str.c_str());
								for(auto i= boost::filesystem::directory_iterator(p); i!=boost::filesystem::directory_iterator();i++){
									if(!boost::filesystem::is_directory(i->path())){
										filepath.push_back(i->path().filename().string());
									}
								}
							}catch(...){
								cout<<"123"<<endl;
							}
				}
			}
		}

			boost::thread_group g;
			boost::shared_ptr<std::string> str(new string(""));
			boost::shared_ptr<std::string> strSplit(new string(""));
			for(size_t i=0;i<filepath.size()-1;i++){
				string path=filepath.at(i);
				g.create_thread(boost::bind(fileOpen,str,strSplit,path));
		}
				g.join_all();
				fileWrite(fileOut.c_str(),str,strSplit);

	}else{
		cout<<"arguments is null"<<endl;
		cout<<"for parse files please input arguments like this template :\n-I [input files path] -O [output file path]"<<endl;
	}


	return 0;
}
