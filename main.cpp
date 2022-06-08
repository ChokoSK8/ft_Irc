# include "Command.hpp"

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Usage: ./parser <role> <command with options>" << std::endl;
		return (1);
	}

	Command	test;

	try
	{
		test.CheckCmd(std::string(av[2]));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
