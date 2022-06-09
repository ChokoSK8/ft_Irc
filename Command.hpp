#ifndef COMMAND_HPP
# define COMMAND_HPP
# include <string>
# include <iostream>
# include <string>
# include <map>
# include <deque>

class	Command;

typedef	std::map<std::string, void (Command::*) ()>	mapper;

class	Command
{
	private:
		std::string	_type;
		mapper	_cmdMap;
		std::deque<std::string>	_cmd;
		void	join(void);
		void	part(void);
		void	msg(void);
		void	query(void);
		void	quit(void);
		void	kick(void);
		void	mode(void);
		void	invite(void);
		void	topic(void);

	public:
		Command(std::string);
		~Command(void);
		void	BuildCmd(size_t, std::string);
		void	CheckCmd(std::string);
		void	CheckType(std::string);
};

size_t	countOccurrences(std::string, std::string);
std::ostream& operator<<(std::ostream&, const Command&);
#endif
