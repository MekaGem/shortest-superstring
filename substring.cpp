#include <iostream>
#include <cstdio>
#include <set>
#include <cassert>

typedef std::set<std::string> StringSet;

size_t getOverlap(const std::string &s, const std::string &t)
{
	size_t maxOverlap = 0;
	for (size_t overlap = 0; overlap <= s.size(); ++overlap)
	{
		if (s.compare(s.size() - overlap, overlap, t, 0, overlap) == 0)
		{	
			maxOverlap = overlap;
		}
	}
	return maxOverlap;
}

std::string mergeStrings(const std::string &s, const std::string &t, size_t overlap)
{
	return s.substr(0, s.size() - overlap) + t;
}

void checkInput(const StringSet &stringSet)
{
	for (auto s : stringSet)
	{
		for (auto t : stringSet)
		{
			if (s != t && s.find(t) != std::string::npos)
			{
				std::cerr << "Your input sucks! (" << s << " " << t << ")" << std::endl;
				exit(-1);
			}
		}
	}
}

void reduceStringSet(StringSet &stringSet)
{
	assert(stringSet.size() > 1);

	std::string s1, s2;
	size_t maxOverlap = 0;

	for (auto s : stringSet)
	{
		for (auto t : stringSet)
		{
			if (s != t)
			{
				size_t overlap = getOverlap(s, t);
				if (overlap >= maxOverlap)
				{
					maxOverlap = overlap;
					s1 = s;
					s2 = t;
				}
			}
		}
	}

	stringSet.erase(s1);
	stringSet.erase(s2);
	s1 = mergeStrings(s1, s2, maxOverlap);

	for (auto s = stringSet.begin(); s != stringSet.end();)
	{
		auto _it = s++;
		if (s1.find(*_it) != std::string::npos)
		{
			stringSet.erase(_it);
		}
	}

	stringSet.insert(s1);
}

int main (int argc, char **argv)
{
	if (argc > 1)
	{
		if (freopen(argv[1], "r", stdin) == NULL)
		{
			std::cerr << "No such file: \"" << argv[1] << "\"" << std::endl;
			return -1;
		}

		std::cerr << "Input file: " << argv[1] << std::endl;
	}

	size_t setSize;
	StringSet stringSet;

	std::cin >> setSize;
	for (size_t index = 0; index < setSize; ++index)
	{
		std::string s;
		std::cin >> s;
		stringSet.insert(s);
	}

	checkInput(stringSet);

	while (stringSet.size() > 1)
	{
		reduceStringSet(stringSet);
	}

	std::cout << *stringSet.begin() << std::endl;
	return 0;
}