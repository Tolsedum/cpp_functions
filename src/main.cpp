#include <iostream>
#include "functions.hpp"



// struct converter {
//     const std::string& x;
//     template <typename T> operator T() { return 0;}
// };

// template <> converter::operator int() { return stoi(x); }
// template <> converter::operator double() { return stod(x); }
// converter stringTo(const std::string& x) { return {x}; }


/** Create .so lib */
int main(){

    // std::string s{"1.23"};
    // int x = stringTo(s);
    // double y = stringTo(s);
    // std::cout << x << " " << y << std::endl;



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
        "num " << ufn::strToUnsignedLongLong("9999999999999999999999999999999")
    << std::endl;
    if(ufn::has_error_in_int_function){
        std::cout<<
            "has_error_in_int_function: "<< ufn::has_error_in_int_function
            << std::endl <<
            "error_in_int_function: " << ufn::error_in_int_function
        << std::endl;
    }

}
