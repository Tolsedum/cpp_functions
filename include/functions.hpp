#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <ctime>
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
 * @version 1.0
*/
namespace ufn{
    /**
     * Check upper register in string
     * @author Tolsedum
     * @version 1.0
    */
   bool is_upper_register(std::string line);
   std::string toLower(const std::string &s);

    /**
     * Delete pattern by both sides
     * @author Tolsedum
     * @version 1.0
    */
    std::string trim(std::string patient, char pattern = ' ');
    std::string trim(std::string patient, std::vector<char> pattern);

    /**
     * String to int
     * @author Tolsedum
     * @version 1.0
    */
    int toInt(const std::string &number);
    inline std::string error_in_int_function = "";
    inline bool has_error_in_int_function = false;

    /**
     * exploed string to vector conteiner
     * @author Tolsedum
     * @version 1.0
    */
    std::vector<std::string> exploed(
        const std::string &line,
        const std::string &delimiter
    );

    /**
     * Get file content from file pointer
     * @author Tolsedum
     * @version 1.0
    */
    std::string getFileContent(std::ifstream &file);

    /**
     * Get file content by file name
     * @author Tolsedum
     * @version 1.0
    */
    std::string getFileContent(const std::string fileName);
    /**
     * Delete commtnts
     * @author Tolsedum
     * @version 1.0
    */
    std::string deleteComment(const std::string &str);
    /**
     * Hash function md5
     * @author Tolsedum
     * @version 1.0
    */
    std::string md5 (std::string in);

    /**
     * Get the currant date using the format
     * @author Tolsedum
     * @version 1.0
    */
    std::string currentDateTime(std::string format = "%d-%m-%Y %X");

    /**
     * implode Template
     *  @author FGTS45
     * @version 1.0
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
     * @version 1.0
    */
    template<class TConteiner, class TValue>
    bool inArray (TConteiner array, TValue value){
        return std::find(array.begin(), array.end(), value) != array.end();
    }
 };
#endif // !FUNCTION_HPP
