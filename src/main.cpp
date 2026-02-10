#include <iostream>
#include <fstream>
#include <vector>
#include "tcs_bmp.h"

using namespace std;

int main(int argc, char* argv[]){
  if(argc<2){
    std::cerr<<"Usage ./build/tombstone <input_file.bmp>"<<std::endl;
    return 1;
  }
  std::string filename = argv[1];
  std::cout<<"Tombstone Compression Systems"<<std::endl<<endl;
  std::cout<<"Target File: "<<filename<<std::endl;

  std::ifstream file(filename, std::ios::binary);

  if(!file){
    std::cerr<<"Error couldn't open file "<<filename<<std::endl;
    return 1;
  }

  //TODO: read the bmp file
  BMPFileHeader fileHeader;

  file.read(reinterpret_cast<char*>(&fileHeader),sizeof(fileHeader));
  
  if(fileHeader.file_type!=0x4D42){
    cerr<<"Error. File not a BMP. (magic number mismatch)"<<endl;
    return 1;
  }

  //read the info header 
  BMPInfoHeader infoHeader;

  file.read(reinterpret_cast<char*>(&infoHeader),sizeof(infoHeader));

  //Diagnosis printing
  cout<<"---------------------------------------"<<endl;
  cout<<"File Size: "<<fileHeader.file_size<<" bytes"<<endl;
  cout<<"Dimensions: "<<infoHeader.width<<"x"<<infoHeader.height<<endl;
  cout<<"Bit Depth: "<<infoHeader.bit_count<<"-bit"<<endl;
  cout<<"Data Offset: "<<fileHeader.offset_data<<" bytes"<<endl;
  cout<<"---------------------------------------"<<endl;
  
  //validation
  if(infoHeader.bit_count!=24){
    cerr<<"Error: TCS currently supports only 24-bit BMPs"<<endl;
    return 1;
  }

  if(infoHeader.compression !=0){
    cerr<<"Error: Compressed BPMs are not supported yet"<<endl;
    return 1;
  }
  
  cout<<"SUCCESS: valid 24-bit BMP detected "<<endl;
  file.close();
  return 0;
}
