#include <iostream>
#include "functions.hpp"

void trim_and_md5_test(){
    std::string str(" grape ");
    str = ufn::trim(str);

    std::string cmd("php test.php -str " + str);

    FILE *fp = NULL;
    std::string result;
    char buf[1024];
    if( (fp = popen(cmd.c_str(), "r")) != NULL){
        while(fgets(buf, 1024, fp) != NULL){
            result.append(buf);
        }
        pclose(fp);
        fp = NULL;
    }
    std::cout<< "is rite: " << (result == ufn::md5(str)) <<std::endl;


    std::cout<<
        "num " << ufn::strToInt("-9") << std::endl<<
            ufn::strToDouble("-9")
    << std::endl;
    if(ufn::has_error_in_converter_function){
        std::cout<<
            "has_error_in_converter_function: "<< ufn::has_error_in_converter_function
            << std::endl <<
            "error_in_converter_function: " << ufn::error_in_converter_function
        << std::endl;
    }
}

/** Create .so lib */
int main(){
    // if(!ufn::createFileAndDirrs("test.test", "content")){
    //     std::cout<< "error_in_function_create_file_and_dir: " << ufn::error_in_function_create_file_and_dir.what() << std::endl;
    // }

    bool first = ufn::isNumeric("1.2.25");
    std::cout<< "1.2.25: "<< first  <<std::endl;
    bool second = ufn::isNumeric("12.25");
    std::cout<< "12.25: " << second <<std::endl;
    bool last = ufn::isNumeric("12.25 ");
    std::cout<< "12.25 : "<< last <<std::endl;
    return 0;
}
