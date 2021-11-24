#include"dir_reader.h"
dir_reader::dir_reader(){
    this->URI_="";
}
dir_reader::dir_reader(std::string URI){
    this->URI_=URI;
}

std::string dir_reader::get_URI(){
    return this->URI_;
}