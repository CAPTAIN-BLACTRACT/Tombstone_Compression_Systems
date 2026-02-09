#include <iostream>
#include <fstream>
#include "tcs_bmp.h"

int main(int argc, char* argv[]){
  if(argc<2){
    std::cerr<<"Usage ./build/tombstone <input_file.bmp>"<<std::endl;
    return 1;
  }
  std::string filename = argv[1];
  std::cout<<"Tombstone Compression Systems"<<std::endl;
  std::cout<<"Target File: "<<filename<<std::endl;

  std::ifstream file(filename, std::ios::binary);

  if(!file){
    std::cerr<<"Error couldn't open file "<<filename<<std::endl;
    return 1;
  }

  //TODO: read the bmp file
  BMPFileHeader fileheader;

  std::cout<<"File opened successfully. Ready to parse"<<std::endl;

  return 0;
}
