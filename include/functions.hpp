#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <ctime>
#include <filesystem>
#include <cmath>
#include <cstring>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/string.hpp>


namespace hashes{
	typedef union uwb {
		unsigned w;
		unsigned char b[4];
	} MD5union;

	typedef unsigned DigestArray[4];
	typedef unsigned(*DgstFctn)(unsigned a[]);
	inline std::string getMD5String(std::string msg);
}

/**
 * Universal functions
 * @author Tolsedum
*/
namespace ufn{

    /**
     * @brief Сreate a file with parent directories
     * @author Tolsedum
     * @param path
     */
    // void createFileAndDirrs(std::string path, std::string content = "");

    /**
     * Check upper register in string
     * @author Tolsedum
    */
   bool hasUpperRegister(std::string line);

    /**
     * @brief to lowercase
     * @author Tolsedum
     * @return
     */
   std::string toLower(const std::string &s);

    /**
     * Delete pattern by both sides
     * @author Tolsedum
    */
    std::string trim(std::string patient, char pattern = ' ');
    std::string trim(std::string patient, std::vector<char> pattern);


    inline std::string error_in_int_function = "";
    inline bool has_error_in_int_function = false;

    struct Converter {
        const std::string &x;
        template <typename Numeric> operator Numeric() { return 0;}
    };

    /**
     * @brief String to int, fload, double ... .
     *      If has error then in has_error_in_int_function
     *      set true and error description in hear error_in_int_function.
     *
     * @param number
     * @return int
     * @author Tolsedum
     */
    int strToInt(const std::string &number);
    double strToDouble(const std::string &number);
    float strToFloat(const std::string &number);
    long strToLong(const std::string &number);
    long double strToLongDouble(const std::string &number);
    long long strToLongLong(const std::string &number);
    unsigned long strToUnsignedLong(const std::string &number);
    unsigned long long strToUnsignedLongLong(const std::string &number);

    /**
     * exploed string to vector conteiner
     * @author Tolsedum
    */
    std::vector<std::string> exploed(
        const std::string &line,
        const std::string &delimiter
    );

    /**
     * Get file content from file pointer
     * @author Tolsedum
    */
    std::string getFileContent(std::ifstream &file);

    /**
     * Get file content by file name
     * @author Tolsedum
    */
    std::string getFileContent(const std::string fileName);
    /**
     * Delete commtnts
     * @author Tolsedum
    */
    std::string deleteComment(const std::string &str);
    /**
     * Hash function md5
     * @author Tolsedum
    */
    std::string md5 (std::string in);

    /**
     * Get the currant date using the format
     * @author Tolsedum
    */
    std::string currentDateTime(std::string format = "%d-%m-%Y %X");

    /**
     * implode Template
     *  @author FGTS45
    */
    template<typename TContainer, typename TData>
    std::string implode (TContainer array , char separator = ',')
    {
        std::string outData;
        for (TData arrData : array){
            outData+=std::to_string(arrData) + separator;
        }
        return outData;
    }

    /**
     * Search existing in array
     * @author Tolsedum
    */
    template<class TConteiner, class TValue>
    bool inArray (TConteiner array, TValue value){
        return std::find(array.begin(), array.end(), value) != array.end();
    }
 };
#endif // !FUNCTIONS_HPP
