#include "Command.hpp"

Command::Command(std::string type) : _type(type)
{
	std::cout << "Command default constructor called" << std::endl;
	_cmdMap["join"] = &Command::join;
	_cmdMap["part"] = &Command::part;
	_cmdMap["msg"] = &Command::msg;
	_cmdMap["query"] = &Command::query;
	_cmdMap["quit"] = &Command::quit;
	_cmdMap["kick"] = &Command::kick;
	_cmdMap["mode"] = &Command::mode;
	_cmdMap["invite"] = &Command::invite;
	_cmdMap["topic"] = &Command::topic;
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
	for (mapper::iterator it = _cmdMap.begin();
		it != _cmdMap.end(); it++)
	{
		if (!(str.compare(it->first)))
		{
			fct = it->second;
			return ((this->*fct) ());
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
	// User.Execute(this)
}

void	Command::part(void)
{
	if (_cmd.size() > 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /part [channel] [msg]");
	// User.Execute(this)
}

void	Command::msg(void)
{
	if (_cmd.size() != 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /msg <nickname> <msg>");
	// User.Execute(this)
}

void	Command::query(void)
{
	if (_cmd.size() < 2 || _cmd.size() > 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /query <nickname> [msg]");
	// User.Execute(this)
}

void	Command::quit(void)
{
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /quit [msg]");
	// User.Execute(this)
}

void	Command::kick(void)
{
	if (_type.compare("operator"))
		throw std::domain_error("You're not allowed to use this command");
	if (_cmd.size() != 3)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /kick <nickname> <channel>");
	// User.Execute(this)
}

void	Command::mode(void)
{
	if (_type.compare("operator"))
		throw std::domain_error("You're not allowed to use this command");
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /mode [msg]");
	// User.Execute(this)
}

void	Command::invite(void)
{
	if (_type.compare("operator"))
		throw std::domain_error("You're not allowed to use this command");
	// check channel mode
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /invite <nickname>");
	// User.Execute(this)
}

void	Command::topic(void)
{
	if (_type.compare("operator"))
		throw std::domain_error("You're not allowed to user this command");
	// check channel mode
	if (_cmd.size() > 2)
		throw std::invalid_argument("Command parts in <> are mandatory and in [] are optional\nHow to use: /topic [msg]");
	// User.Execute(this)
}

size_t	countOccurrences(std::string charset, std::string str)
{
	size_t	count = 0;
	size_t	pos = 0;

	while ((pos = str.find_first_of(charset, pos + 1)) != std::string::npos)
		count++;
	return (count);
}
