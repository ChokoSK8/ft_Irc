#ifndef COMMAND_HPP
# define COMMAND_HPP
# include <string>
# include <iostream>
# include <string>
# include <map>
# include <deque>

class	Command
{
	private:
		std::map<std::string, void (Command::*) ()>	_cmdMap;
		std::deque<std::string>	_cmd;
		void	join(void);
		void	part(void);
		void	msg(void);
		void	query(void);
		void	quit(void);

	public:
		Command(void);
		~Command(void);
		void	BuildCmd(size_t, std::string);
		void	CheckCmd(std::string);
};

size_t	countOccurrences(std::string, std::string);
std::ostream& operator<<(std::ostream&, const Command&);
#endif
