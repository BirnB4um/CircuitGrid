#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>

class IO_DATA
{
public:
	std::string choose_open_file(int nr_file_name);
	std::string choose_save_file(int nr_file_name);
	bool save_to_file(std::string file_name, const char *output_data, const size_t data_size, bool append_data);
	bool read_from_file(std::string file_name, std::vector<char>& input_data);
};

