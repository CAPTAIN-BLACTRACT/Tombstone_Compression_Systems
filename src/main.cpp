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

  BMPInfoHeader infoHeader;

  file.read(reinterpret_cast<char*>(&fileHeader),sizeof(fileHeader));
  
  file.read(reinterpret_cast<char*>(&infoHeader),sizeof(infoHeader));

  //validation
  if(fileHeader.file_type!=0x4D42){
    cerr<<"Error. File not a BMP. (magic number mismatch)"<<endl;
    return 1;
  }

  if(infoHeader.bit_count!=24){
    cerr<<"Error: TCS currently supports only 24-bit BMPs"<<endl;
    return 1;
  }

  //preparing for pixel Data
  int width = infoHeader.width;
  int height = infoHeader.height;

  //calculating padding
  int padding = (4-(width*3)%4)%4;
  
  cout<<"Reading Image: "<<width<<"x"<<"height"<<endl;
  cout<<"Padding per row :"<<padding<<" bytes"<<endl;

  //moving cursor or pointer to start of pixel data
  file.seekg(fileHeader.offset_data,file.beg);

  vector<Pixel> pixelData(width*height);

  //sara pixel data ko capture karen janab
  for(int y=0;y<height;y++){
    for(int x=0;x<width;x++){
        file.read(reinterpret_cast<char*>(&pixelData[y*width +x]),3);
    }
    file.seekg(padding,ios::cur);
  }
  file.close();

  cout<<"Image Loaded Successfully"<<endl;
  
  //these are now testing methods
  ofstream outFile("test_copy.bmp",ios::binary);

  outFile.write(reinterpret_cast<const char*>(&fileHeader),sizeof(fileHeader));
  outFile.write(reinterpret_cast<const char*>(&infoHeader),sizeof(infoHeader));

  //pixel aur padding dalen
  for(int y=0;y<height;y++){
    for(int x=0;x<width;x++){
      outFile.write(reinterpret_cast<const char*>(&pixelData[y*width+x]),3);
    }

    char pad[3] = {0,0,0};
    outFile.write(pad,padding);
  }

  outFile.close();
  cout<<"Success ! Wrote 'test_copy.bmp'"<<endl;
  return 0;
}
