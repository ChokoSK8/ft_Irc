#include "Command.hpp"

Command::Command(void)
{
	std::cout << "Command default constructor called" << std::endl;
	_cmdMap["join"] = &Command::join;
	_cmdMap["part"] = &Command::part;
	_cmdMap["msg"] = &Command::msg;
	_cmdMap["query"] = &Command::query;
	_cmdMap["quit"] = &Command::quit;
}

Command::~Command(void)
{
	std::cout << "Command destructor called" << std::endl;
}

void	Command::CheckCmd(std::string line)
{
	size_t	nOpt = countOccurrences(" ", line) + 1;
	void	(Command::*fct) (void);
	std::string	str;

	if (!nOpt)
		throw std::invalid_argument("You've entered a empty line");
	BuildCmd(nOpt, line);
	str = _cmd.front();
	std::cout << str << std::endl;
	for (std::map<std::string, void (Command::*) ()>::iterator it = _cmdMap.begin();
		it != _cmdMap.end(); it++)
	{
		std::cout << it->first << std::endl;
		if (!(str.compare(it->first)))
		{
			fct = it->second;
			(this->*fct) ();
		}
	}
	throw std::invalid_argument("You've entered a invalid command");
}

void	Command::BuildCmd(size_t nOpt, std::string line)
{
	int	tmp = -1;
	size_t	pos;

	while (nOpt--)
	{
		pos = line.find_first_of(" ", tmp + 1);
		if (nOpt)
		{
			_cmd.push_back(line.substr(tmp + 1, pos));
			tmp = pos;
		}
	}
	_cmd.push_back(line.substr(tmp + 1));
}

void	Command::join(void)
{
	if (_cmd.size() != 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /join <channel>");
}

void	Command::part(void)
{
	if (_cmd.size() > 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /part [channel] [msg]");
}

void	Command::msg(void)
{
	if (_cmd.size() != 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /msg <nickname> <msg>");
}

void	Command::query(void)
{
	if (_cmd.size() < 2 || _cmd.size() > 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /query <nickname> [msg]");
}

void	Command::quit(void)
{
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /quit [msg]");
}

size_t	countOccurrences(std::string charset, std::string str)
{
	size_t	count = 0;
	size_t	pos = 0;

	while ((pos = str.find_first_of(charset, pos + 1)) != std::string::npos)
		count++;
	return (count);
}
