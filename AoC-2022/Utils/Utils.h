
namespace Utils
{
	// convert 2D vector of vector of strings to vector of vector of ints
	template <typename Int = int, template <typename...> typename Cont2 = std::vector, template <typename...> typename Cont1 = std::vector>
	Cont1<Cont2<Int>> input_to_int_2D(const Cont1<Cont2<std::string, std::allocator<std::string>>, std::allocator<std::vector<std::string, std::allocator<std::string>>>>& input) {

		const size_t& size = input.size();
		Cont1<Cont2<Int>> output(size);

		for (size_t i = 0; i < size; i++) {

			Int value;
			output[i].reserve(input[i].size());

			for (const std::string& word : input[i]) {
				auto result = std::from_chars(word.data(), word.data() + word.size(), value);

				if (result.ec == std::errc::invalid_argument) {
					std::cerr << "Non-integer value in input_to_int\n";
					std::exit(EXIT_FAILURE);
				}
				else if (result.ec == std::errc::result_out_of_range) {
					std::cerr << "Integer type too small in input_to_int\n";
					std::exit(EXIT_FAILURE);
				}
				output[i].push_back(value);
			}
		}

		return output;
	}

	// Function to read input file "file_name" containing lines split by multiple delimiters
	// and output a Cont1(vector) of Cont2(vector) of strings called "input"
	template <template <typename...> typename Cont2 = std::vector, template <typename...> typename Cont1 = std::vector >
	Cont1<Cont2<std::string>> read_input_2D(std::string file_name, std::vector<std::string> delimiters) {

		if (delimiters.empty()) {
			std::cout << "No delimiters provided. Use read_input instead of read_input_2D" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		// output vector of strings
		Cont1<Cont2<std::string>> input;

		// read input into "line"
		std::string line;
		std::ifstream input_file(file_name);

		// check that file exists
		if (!input_file.is_open()) {
			std::cout << "Could not open file " << file_name << std::endl;
			std::exit(EXIT_FAILURE);
		}

		size_t line_length;
		size_t delims = delimiters.size();
		std::string temp_val;
		Cont2<std::string> temp_vector;
		while (getline(input_file, line)) {

			line_length = line.size();

			// loop through contents of line
			for (size_t read_pos = 0; read_pos < line_length; read_pos++) {

				for (size_t i = 0; i < delims; i++) {
					// if next characters match possible delimiters, skip delimiter and add to temp_vector
					if (line.substr(read_pos, delimiters[i].size()) == delimiters[i]) {
						read_pos += delimiters[i].size() - 1;
						// in case delimiters follow each other
						if (!temp_val.empty()) { temp_vector.push_back(temp_val); }
						temp_val.clear();
						break;
					}
					// if next character does not match any delimiter, add to temp_val
					else {
						if (i == delimiters.size() - 1) {
							temp_val.push_back(line[read_pos]);
						}
					}
				}
			}
			// push_back last value (if not empty)
			if (!temp_val.empty()) { temp_vector.push_back(temp_val); }

			// add vector to input
			input.push_back(temp_vector);
			temp_vector.clear();
			temp_val.clear();
		}

		input_file.close();

		return input;
	}

	// Function to read input file "file_name" containing values separated by
	// "separator" and output a Cont(vector) of strings called "input"
	template <template <typename...> typename Cont = std::vector>
	Cont<std::string> read_input(std::string file_name, std::vector<std::string> delimiters = {}) {

		// output vector of strings
		Cont<std::string> input;

		// read input into "line"
		std::string line;
		std::ifstream input_file(file_name);

		// check that file exists
		if (!(input_file.is_open())) {
			std::cout << "Could not open file " << file_name << std::endl;
			std::exit(EXIT_FAILURE);
		}

		size_t line_length;
		std::string temp_val;
		size_t delims = delimiters.size();

		while (getline(input_file, line)) {

			line_length = line.size();

			if (delimiters.empty()) { input.push_back(line); }
			else {
				// loop through contents of line
				for (size_t read_pos = 0; read_pos < line_length; read_pos++) {

					for (size_t i = 0; i < delims; i++) {

						// if next characters != any delimiter, add next char to temp_val
						if (line.substr(read_pos, delimiters[i].size()) == delimiters[i]) {
							read_pos += delimiters[i].size() - 1;
							// in case delimiters follow each other
							if (!temp_val.empty()) { input.push_back(temp_val); }
							temp_val.clear();
							break;
						}
						else {
							if (i == delimiters.size() - 1) {
								temp_val.push_back(line[read_pos]);
							}
						}
					}
				}
				// push_back last value
				if (!temp_val.empty()) { input.push_back(temp_val); }
				temp_val.clear();
			}
		}

		input_file.close();

		return input;
	}



	inline std::vector<std::string> split_string(std::string str, char delimiter)
	{
		std::string token;
		std::vector<std::string> tokens;

		std::stringstream ss(str);
		while (getline(ss, token, delimiter))
			tokens.push_back(token);

		return tokens;
	}
}