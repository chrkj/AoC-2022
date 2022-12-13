using namespace std;

namespace Utils
{
	// convert 2D vector of vector of strings to vector of vector of ints
	template <typename Int = int, template <typename...> typename Cont2 = vector, template <typename...> typename Cont1 = vector>
	Cont1<Cont2<Int>> InputToInt2D(const Cont1<Cont2<string, allocator<string>>, allocator<vector<string, allocator<string>>>>& input) {

		const size_t& size = input.size();
		Cont1<Cont2<Int>> output(size);

		for (size_t i = 0; i < size; i++) {

			Int value;
			output[i].reserve(input[i].size());

			for (const string& word : input[i]) {
				auto result = from_chars(word.data(), word.data() + word.size(), value);

				if (result.ec == errc::invalid_argument) {
					cerr << "Non-integer value in input_to_int\n";
					exit(EXIT_FAILURE);
				}
				else if (result.ec == errc::result_out_of_range) {
					cerr << "Integer type too small in input_to_int\n";
					exit(EXIT_FAILURE);
				}
				output[i].push_back(value);
			}
		}

		return output;
	}

	// Function to read input file "file_name" containing lines split by multiple delimiters
	// and output a Cont1(vector) of Cont2(vector) of strings called "input"
	template <template <typename...> typename Cont2 = vector, template <typename...> typename Cont1 = vector >
	Cont1<Cont2<string>> ReadInput2D(string file_name, vector<string> delimiters) {

		if (delimiters.empty()) {
			cout << "No delimiters provided. Use read_input instead of read_input_2D" << endl;
			exit(EXIT_FAILURE);
		}

		// output vector of strings
		Cont1<Cont2<string>> input;

		// read input into "line"
		string line;
		ifstream input_file(file_name);

		// check that file exists
		if (!input_file.is_open()) {
			cout << "Could not open file " << file_name << endl;
			exit(EXIT_FAILURE);
		}

		size_t line_length;
		size_t delims = delimiters.size();
		string temp_val;
		Cont2<string> temp_vector;
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
	template <template <typename...> typename Cont = vector>
	Cont<string> ReadInput(string file_name, vector<string> delimiters = {}) {

		// output vector of strings
		Cont<string> input;

		// read input into "line"
		string line;
		ifstream input_file(file_name);

		// check that file exists
		if (!(input_file.is_open())) 
		{
			cout << "Could not open file " << file_name << endl;
			exit(EXIT_FAILURE);
		}

		size_t line_length;
		string temp_val;
		size_t delims = delimiters.size();

		while (getline(input_file, line)) 
		{
			line_length = line.size();
			if (delimiters.empty()) 
			{ 
				input.push_back(line); 
			}
			else 
			{
				// loop through contents of line
				for (size_t read_pos = 0; read_pos < line_length; read_pos++) 
				{
					for (size_t i = 0; i < delims; i++) 
					{
						// if next characters != any delimiter, add next char to temp_val
						if (line.substr(read_pos, delimiters[i].size()) == delimiters[i]) 
						{
							read_pos += delimiters[i].size() - 1;
							// in case delimiters follow each other
							if (!temp_val.empty()) { input.push_back(temp_val); }
							temp_val.clear();
							break;
						}
						else 
						{
							if (i == delimiters.size() - 1)
								temp_val.push_back(line[read_pos]);
						}
					}
				}
				// push_back last value
				if (!temp_val.empty())
					input.push_back(temp_val);
				temp_val.clear();
			}
		}
		input_file.close();
		return input;
	}


	template <typename T>
	vector<T> SplitString(const string& str, const string& delimiters) 
	{
		vector<T> tokens;
		string token;
		stringstream ss(str);

		while (getline(ss, token, delimiters[0])) 
		{
			for (size_t i = 1; i < delimiters.length(); ++i) 
			{
				string::size_type pos = 0;
				while ((pos = token.find(delimiters[i], pos)) != string::npos)
					token.replace(pos, 1, " ");
			}
			tokens.push_back(token);
		}
		return tokens;
	}


	template<typename T>
	inline void PrintVector(const T& t)
	{
		copy(t.cbegin(), t.cend(), ostream_iterator<typename T::value_type>(cout, ", "));
	}


	inline vector<int> StringToVectorOfInts(const string& str)
	{
		vector<int> result;
		for (char c : str) 
		{
			if (c >= '0' && c <= '9')
				result.push_back(c - '0');
		}
		return result;
	}

	inline vector<vector<int>> StringToVectorOfInts(const vector<string>& strs) 
	{
		vector<vector<int>> result;
		for (const auto& str : strs) 
		{
			vector<int> digits;
			for (const auto& c : str) 
			{
				if (c >= '0' && c <= '9')
					digits.push_back(c - '0');
			}
			result.push_back(digits);
		}
		return result;
	}

	template <typename T, typename U>
	std::vector<std::pair<T, U>> StringToPair(const std::vector<std::string>& input)
	{
		std::vector<std::pair<T, U>> pairs;
		for (const std::string& elem : input)
		{
			// extract the character and integer from the input element
			T c = elem[0];
			U i = std::stoi(elem.substr(2));

			// create a pair with the character and integer and add it to the vector
			pairs.push_back(std::make_pair(c, i));
		}

		return pairs;
	}

	inline std::vector<int> GetIntegersFromString(const std::string& str)
	{
		std::vector<int> integers;
		std::string current_number;

		for (char c : str)
		{
			if (std::isdigit(c))
			{
				current_number += c;
			}
			else
			{
				if (!current_number.empty())
				{
					integers.push_back(std::stoi(current_number));
					current_number.clear();
				}
			}
		}

		if (!current_number.empty())
		{
			integers.push_back(std::stoi(current_number));
		}

		return integers;
	}
}