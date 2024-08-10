#include "functions.hpp"

namespace hashes{
    static unsigned func0(unsigned abcd[]){
        return (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
    }
    static unsigned func1(unsigned abcd[]){
        return (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
    }

    static unsigned func2(unsigned abcd[]){
        return  abcd[1] ^ abcd[2] ^ abcd[3];
    }

    static unsigned func3(unsigned abcd[]){
        return abcd[2] ^ (abcd[1] | ~abcd[3]);
    }

    static unsigned *calctable(unsigned *k){
        double s, pwr;
        int i;

        pwr = std::pow(2.0, 32);
        for (i = 0; i<64; i++) {
            s = std::fabs(sin(1.0 + i));
            k[i] = (unsigned)(s * pwr);
        }
        return k;
    }
    static unsigned rol(unsigned r, short N){
        unsigned  mask1 = (1 << N) - 1;
        return ((r >> (32 - N)) & mask1) | ((r << N) & ~mask1);
    }

    static unsigned* MD5Hash(std::string msg){
        int mlen = msg.length();
        static DigestArray h0 = {
            0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476
        };
        static DgstFctn ff[] = { &func0, &func1, &func2, &func3 };
        static short M[] = { 1, 5, 3, 7 };
        static short O[] = { 0, 1, 5, 0 };
        static short rot0[] = { 7, 12, 17, 22 };
        static short rot1[] = { 5, 9, 14, 20 };
        static short rot2[] = { 4, 11, 16, 23 };
        static short rot3[] = { 6, 10, 15, 21 };
        static short *rots[] = { rot0, rot1, rot2, rot3 };
        static unsigned kspace[64];
        static unsigned *k;

        static DigestArray h;
        DigestArray abcd;
        DgstFctn fctn;
        short m, o, g;
        unsigned f;
        short *rotn;
        union {
            unsigned w[16];
            char     b[64];
        }mm;
        int os = 0;
        int grp, grps, q, p;
        unsigned char *msg2;

        if (k == NULL) k = calctable(kspace);

        for (q = 0; q<4; q++)
            h[q] = h0[q];

        {
            grps = 1 + (mlen + 8) / 64;
            msg2 = (unsigned char*)malloc(64 * grps);
            std::memcpy(msg2, msg.c_str(), mlen);
            msg2[mlen] = (unsigned char)0x80;
            q = mlen + 1;
            while (q < 64 * grps){ msg2[q] = 0; q++; }
            {
                MD5union u;
                u.w = 8 * mlen;
                q -= 8;
                std::memcpy(msg2 + q, &u.w, 4);
            }
        }

        for (grp = 0; grp<grps; grp++){
            std::memcpy(mm.b, msg2 + os, 64);
            for (q = 0; q<4; q++) abcd[q] = h[q];
            for (p = 0; p<4; p++) {
                fctn = ff[p];
                rotn = rots[p];
                m = M[p]; o = O[p];
                for (q = 0; q<16; q++) {
                    g = (m*q + o) % 16;
                    f = abcd[1]
                        + rol(
                            abcd[0]
                                + fctn(abcd)
                                + k[q + 16 * p]
                                + mm.w[g],
                            rotn[q % 4]
                        );

                    abcd[0] = abcd[3];
                    abcd[3] = abcd[2];
                    abcd[2] = abcd[1];
                    abcd[1] = f;
                }
            }
            for (p = 0; p<4; p++)
                h[p] += abcd[p];
            os += 64;
        }
        return h;
    }

    std::string getMD5String(std::string msg) {
        std::string str;
        int j;
        unsigned *d = MD5Hash(msg);
        MD5union u;
        for (j = 0; j<4; j++){
            u.w = d[j];
            char s[9];
            sprintf(
                s,
                "%02x%02x%02x%02x",
                u.b[0],
                u.b[1],
                u.b[2],
                u.b[3]
            );
            str += s;
        }

        return str;
    }
}

namespace ufn{

    /**
     * Check upper register in string
    */
    bool createFileAndDirrs(
        std::string file_path,
        std::string content
    ){
        error_in_function_create_file_and_dir =
            std::runtime_error("");
        bool file_exists = true;
        try{
            if(!std::filesystem::exists(file_path)){
                std::filesystem::path path{file_path};
                std::string parent_path = path.parent_path();
                if(!parent_path.empty()
                    && !std::filesystem::exists(parent_path)
                ){
                    std::filesystem::create_directories(parent_path);
                }
                if(!std::filesystem::is_regular_file(path)){
                    std::ofstream ofs(path);
                    if(ofs.is_open()){
                        if(!content.empty()){
                            ofs << content;
                        }
                        ofs.close();

                    }else{
                        file_exists = false;
                        error_in_function_create_file_and_dir =
                            std::runtime_error("Can`t open file");
                    }
                }
            }
        }catch(const std::exception& e){
            error_in_function_create_file_and_dir =
                std::runtime_error(e.what());
            file_exists = false;
        }
        return file_exists;
    }

    std::string getNumericType(std::string numeric){
        std::string type;
        short count = 0;

        for(int i = numeric.size() - 1; i != 0; i--){
            if(
                count > 3 || (
                    numeric[i] != 'U'
                    && numeric[i] != 'L'
                    && numeric[i] != 'I'
                    && numeric[i] != 'F'
                    && numeric[i] != 'D'
                )
            ){
                break;
            }else{
                count++;
                type = numeric[i] + type;
            }
        }
        if(
            count > 3
            || (
                type != "U"
                && type != "UL"
                && type != "ULL"
                && type != "LL"
                && type != "L"
                && type != "I"
                && type != "F"
                && type != "D"
            )
        ){
            type.clear();
        }
        return type;
    }

    bool isNumeric(std::string str){
        short count_dot = 0;
        std::string type = getNumericType(str);
        if(!type.empty()){
            str.erase(str.size() - type.size());
        }

        return !str.empty()
            && std::find_if(
                str.begin(),
                str.end(),
                [&count_dot](unsigned char c){
                    if(c == '.'){
                        count_dot++;
                        if(count_dot > 1){
                            return true;
                        }
                    }
                    return !(std::isdigit(c) || c == '.' || c == '-');
                }
            ) == str.end();
    }

    template <> Converter::operator int() {
        return std::stoi(x);
    }
    template <> Converter::operator double() {
        return std::stod(x);
    }
    template <> Converter::operator float() {
        return std::stof(x);
    }
    template <> Converter::operator long() {
        return std::stol(x);
    }
    template <> Converter::operator unsigned int () {
        unsigned long ul = std::stoul(x);
        return static_cast<unsigned int>(ul);
    }
    template <> Converter::operator long double() {
        return std::stold(x);
    }
    template <> Converter::operator long long() {
        return std::stoll(x);
    }
    template <> Converter::operator unsigned long() {
        return std::stoul(x);
    }
    template <> Converter::operator unsigned long long() {
        return std::stoull(x);
    }
    inline Converter stringTo(const std::string& x) {
        return {x};
    }

    template<typename Numeric>
    Numeric strToNumeric(const std::string &numeric){
        has_error_in_converter_function = 0;
        error_in_converter_function = "";
        Numeric num = 0;
        try{
            num = stringTo(numeric);
        }catch(const std::invalid_argument &e){
            has_error_in_converter_function = 1;
            error_in_converter_function.append("Invalid argument: ");
            error_in_converter_function.append(e.what());
        }catch(const std::out_of_range &e){
            has_error_in_converter_function = 2;
            error_in_converter_function.append("Out of range: ");
            error_in_converter_function.append(e.what());
        }catch(...){
            has_error_in_converter_function = 3;
            error_in_converter_function = "Unexpected error";
        }
        return num;
    }

    int strToInt(const std::string &number){
        return strToNumeric<int>(number);
    }
    double strToDouble(const std::string &number){
        return strToNumeric<double>(number);
    }
    float strToFloat(const std::string &number){
        return strToNumeric<float>(number);
    }
    unsigned strToUnsigned(const std::string &number){
        return strToNumeric<unsigned>(number);
    }
    long strToLong(const std::string &number){
        return strToNumeric<long>(number);
    }
    long double strToLongDouble(const std::string &number){
        return strToNumeric<long double>(number);
    }
    long long strToLongLong(const std::string &number){
        return strToNumeric<long long>(number);
    }
    unsigned long strToUnsignedLong(const std::string &number){
        return strToNumeric<unsigned long>(number);
    }
    unsigned long long strToUnsignedLongLong(
        const std::string &number
    ){
        return strToNumeric<unsigned long long>(number);
    }

    std::string deleteComment(
        const std::string &str
    ){
        std::string ret_value;
        if(size_t pos = str.find('#') != std::string::npos){
            ret_value = str.substr(0, pos - 1);
        }else ret_value = str;
        return ret_value;
    }

    bool hasUpperRegister(std::string line){
        for (auto const &var : line){
            if (std::isupper(var))
                return true;
        }
        return false;
    }

    std::string toLower(const std::string &s){
            std::string new_s;
            for(auto const& var : s){
                new_s.append(1, std::tolower(var));
            }
            return new_s;
    }

    std::vector<std::string> exploed(
        const std::string &line,
        const std::string &delimiter
    ){
        std::vector<std::string> ret_value;
        size_t pos = 0;
        std::string token;
        std::string line_copy = line;
        while (
            (pos = line_copy.find(delimiter)) != std::string::npos
        ){
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

    std::string trim(std::string patient, char pattern){
        boost::trim_if(patient, [pattern](char &c){
            return c == pattern;
        });
        return patient;
    }

    std::string trim(std::string patient, std::vector<char> pattern){
        for(auto var : pattern){
            boost::trim_if(patient, [var](char &c){
                return c == var;
            });
        }
        return patient;
    }

    std::string getFileContent(std::ifstream &file){
        std::string ret_value;
        if(file.is_open()){
            file.seekg(0, std::ios::end);
            size_t size = file.tellg();
            file.seekg(0);
            ret_value = std::string(size, ' ');
            file.read(&ret_value[0], size);
        }

        return ret_value;
    }

    std::string getFileContent(const std::string file_name){
        std::string ret_value;
        if(std::filesystem::exists(file_name)){
            std::ifstream i_file(file_name);
            ret_value = getFileContent(i_file);
            i_file.close();
        }
        return ret_value;
    }

    std::string md5(std::string in){
        return hashes::getMD5String(in);
    }

    std::string currentDateTime(std::string format) {
        time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        char buffer[128];
        strftime(buffer, sizeof(buffer), format.c_str(), now);
        return buffer;
    }

    unsigned long getFileCreationDate(const std::string &file_name){
        struct stat t_stat;
        stat(file_name.c_str(), &t_stat);
        return t_stat.st_mtime;
    }

    std::string convertTimestampDateToString(
        unsigned long &timestamp,
        std::string format
    ){
        std::time_t temp = timestamp;
        std::tm* t = std::localtime(&temp);
        std::stringstream ss;
        ss << std::put_time(t, format.c_str());
        return ss.str();
    }

    unsigned long convertStringDateToTimestamp(
        const std::string &date,
        std::string format
    ){
        std::tm t{};
        std::istringstream s_stream(date);
        s_stream >> std::get_time(&t, format.c_str());
        if (s_stream.fail()) {
            throw std::runtime_error{"Failed to parse time string"};
        }
        return mktime(&t);
    }

    std::string getParentDir(const std::string_view dir){
        std::string path{dir};
        path = trim(path, '/');
        path = path.substr(0, path.find_last_of("/"));
        return path;
    }
} // namespace ufn
