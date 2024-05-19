#include <iostream>
#include "functions.hpp"

/** Create .so lib */
int main(){
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
    std::cout<< "md5 of 'php': " << result <<std::endl;
    std::cout<< "md5 of 'ufn': " << ufn::md5(str) << std::endl;


    std::cout<<
        "num " << ufn::toInt("99999999999999999999999999999999999999999999999")
    << std::endl;
    if(ufn::has_error_in_int_function){
        std::cout<<
            "has_error_in_int_function: "<< ufn::has_error_in_int_function
            << std::endl <<
            "error_in_int_function: " << ufn::error_in_int_function
        << std::endl;
    }

}
