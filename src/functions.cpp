#include "functions.hpp"


int ufn::toInt(const std::string &number){
    int num = 0;
    try{
        num = std::stoi(number);
    }catch(const std::invalid_argument &e){
        //
    }catch(const std::out_of_range &e){
        //
    }
    return num;
}

std::string ufn::deleteComment(
    const std::string &str
){
    std::string ret_value;
    if(size_t pos = str.find('#') != std::string::npos){
        ret_value = str.substr(0, pos - 1);
    }else ret_value = str;
    return ret_value;
}

/**
     * Check upper register in string
    */
   bool ufn::is_upper_register(std::string line){
        for(auto const& var : line){
            if(std::isupper(var)) return true;
        }
        return false;
   }

   std::string ufn::to_lower(const std::string &s){
        std::string new_s;
        for(auto const& var : s){
            new_s.append(1, std::tolower(var));
        }
        return new_s;
   }

std::vector<std::string> ufn::exploed(
    const std::string &line,
    const std::string &delimiter
){
    std::vector<std::string> ret_value;
    size_t pos = 0;
    std::string token;
    std::string line_copy = line;
    while ((pos = line_copy.find(delimiter)) != std::string::npos){
        token = line_copy.substr(0, pos);
        line_copy.erase(0, pos + delimiter.length());
        ret_value.push_back(token);
    }
    ret_value.push_back(line_copy);
    return ret_value;
}

bool isSymb(char c, char p){
    return c == p;
}

void ufn::trim(std::string &patient, char pattern){
    boost::trim_if(patient, [pattern](char &c){return c == pattern;});
}

void ufn::trim(std::string &patient, std::vector<char> pattern){
    for(auto var : pattern){
        boost::trim_if(patient, [var](char &c){return c == var;});
    }
}

std::string ufn::getFileContent(std::ifstream &file){

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0);
    std::string ret_value(size, ' ');
    file.read(&ret_value[0], size);

    return ret_value;
}

std::string ufn::getFileContent(const std::string file_name){
    std::ifstream i_file(file_name);
    std::string ret_value = getFileContent(i_file);
    i_file.close();
    return ret_value;
}

std::string ufn::md5 (std::string in){
    return hashes::GetMD5String(in);
}

std::string ufn::currentDateTime(std::string format) {
    time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    char buffer[128];
    strftime(buffer, sizeof(buffer), format.c_str(), now);
    return buffer;
}
