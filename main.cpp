
static bool parseInt(const std::string& s, int& out) {
	std::istringstream iss(s);
	iss >> out;
	return iss.eof() && !iss.fail();
}

int main(int argc, char **argv)
{
    if (argc == 1)
		return (1);

	std::vector<int> vec;
	for (int i = 1; i < argc; ++i) {
		int n;
		if (!parseInt(argv[i], n) || n < 0 || n > std::numeric_limits<int>::max())
		{
			std::cerr << "Error: invalid number: " << argv[i] << std::endl;
			return (1);
		}
		vec.push_back(n);
	}
	std::cout << "Before: ";
	putVector(vec);
	fordJohnsonVector(vec);
	std::deque<int>	dec(vec.begin(), vec.end());
	fordJohnsonDeque(dec);
	
	return (0);
}
