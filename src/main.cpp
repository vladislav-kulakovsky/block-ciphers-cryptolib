#include "cast6.h"
#include "utils.h"
#include "types.h"
#include "cbc.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		std::cout << "Wrong argument!" << std::endl;
		show_usage(argv[0]);
		return 1;
	}
	std::string input_file;
	std::string output_file;

	std::string cmd;
	std::string key;
	std::string iv;
	std::string pt;
	std::vector<std::string> sources;

	bool arg_key = false, arg_iv = false, arg_inp = false;

	for (size_t i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		if ((arg == "-h") || (arg == "--help"))
		{
			show_usage(argv[0]);
			return 0;
		}
		else if ((arg == "-m") || (arg == "--mode"))
		{
			if (i + 1 < argc)
			{
				cmd = argv[++i];
			}
			else
			{
				std::cout << "Wrong argument!" << std::endl;
				show_usage(argv[0]);
				return 1;
			}
		}
		else if ((arg == "-k") || (arg == "--key"))
		{
			if (i + 1 < argc)
			{
				key = argv[++i];
				arg_key = true;
			}
			else
			{
				std::cout << "Wrong argument!" << std::endl;
				show_usage(argv[0]);
				return 1;
			}
		}
		else if ((arg == "-v") || (arg == "--iv"))
		{
			if (i + 1 < argc)
			{
				iv = argv[++i];
				arg_iv = true;
			}
			else
			{
				std::cout << "Wrong argument!" << std::endl;
				show_usage(argv[0]);
				return 1;
			}
		}
		else if ((arg == "-i") || (arg == "--inp"))
		{
			if (i + 1 < argc)
			{
				input_file = argv[++i];
				arg_inp = true;
				std::ifstream input(input_file, std::ios::in | std::ios::binary);
				std::vector<uint8> tmp;
				std::copy(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), std::back_inserter(tmp));
				std::copy(tmp.begin(), tmp.begin() + tmp.size(), std::back_inserter(pt));
				input.close();
			}
			else
			{
				std::cout << "Wrong argument!" << std::endl;
				show_usage(argv[0]);
				return 1;
			}
		}
		else
		{
			sources.push_back(argv[i]);
		}
	}

	if ((arg_key || arg_iv || arg_inp) && (!arg_key || !arg_iv || !arg_inp))
	{
		std::cout << "Wrong argument!" << std::endl;
		show_usage(argv[0]);
		return 1;
	}

	if (arg_inp && (sources.size() == 1))
	{
		std::copy(sources[0].begin(), sources[0].end(), std::back_inserter(output_file));
	}
	else if (!arg_inp && (sources.size() == 2))
	{
		std::copy(sources[0].begin(), sources[0].end(), std::back_inserter(input_file));
		std::copy(sources[1].begin(), sources[1].end(), std::back_inserter(output_file));

		std::ifstream input(input_file, std::ios::in | std::ios::binary);
		if (input.is_open())
		{
			input >> key;
			input >> iv;
			input.get();
			input.get();
			std::vector<uint8> tmp;
			std::copy(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), std::back_inserter(tmp));
			std::copy(tmp.begin(), tmp.begin()+tmp.size(), std::back_inserter(pt));

		}
		input.close();
	}
	else
	{
		std::cout << "Wrong argument!" << std::endl;
		show_usage(argv[0]);
		return 1;
	}
	

	CryptoInterface * cast6 = new CAST256(key);
	CBC cbc(cast6, iv);

	
	std::ofstream output(output_file, std::ios::out| std::ios::binary);
	if (output.is_open())
	{
		if (!arg_inp)
		{
			output << key << "\r\n";
			output << iv << "\r\n";
		}
		if (cmd == "encrypt")
		{
			output << cbc.encrypt(pt);
		}
		else if (cmd == "decrypt")
		{
			output << cbc.decrypt(pt);
		}
		output.close();
	}
	else
	{
		return 10;
	}

	delete(cast6);
	return 0;
}