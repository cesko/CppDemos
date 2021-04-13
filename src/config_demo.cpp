#include <iostream>
#include <fstream>
#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

main (int argc, char* argv[])
{
    std::string                 config_file;

    std::vector<std::string>    arg_positionals;

    bool                        arg_flag   = false;
    int                         arg_int    = 0;
    double                      arg_double = std::nan("");
    std::string                 arg_string = "Hello World";
    std::vector<std::string>    arg_list;


    try {

        // Options that will be allowed only on command line
        po::options_description generic("Generic options");
        generic.add_options()
            ("help",
                "produce help message")
            ("config,c",
                po::value<std::string>(&config_file), 
                "name of a file of a configuration.")
        ;

        // Options that will be allowed both on command line and in config file
        po::options_description config("Configuration");
        config.add_options()
            ("int,i",
                po::value<int>(&arg_int), 
                "An integer argument")
            ("double,d",
                po::value<double>(&arg_double),
                "A real number (double) argument")
            ("string,s",
                po::value<std::string>(&arg_string), 
                "A string argument")
            ("flag,f",
                po::bool_switch(&arg_flag),
                "A flag argument (without aprameter)")
            ("list,l",
                po::value< std::vector<std::string> >(&arg_list)->composing(),
                "A combined list of strings")
        ;

        // Hidden options, will be allowed both on command line and
        // in config file, but will not be shown to the user.
        po::options_description hidden("Hidden options");
        hidden.add_options()
            ("positionals",
                po::value< std::vector<std::string> >(&arg_positionals),
                "positionals" )
            ;

        
        po::options_description cmdline_options;
        cmdline_options.add(generic).add(config).add(hidden);

        po::options_description config_file_options;
        config_file_options.add(config).add(hidden);

        po::options_description visible("Allowed options");
        visible.add(generic).add(config);
        
        po::positional_options_description p;
        p.add("positionals", -1);

        po::variables_map vm;
        store(po::command_line_parser(argc, argv).
              options(cmdline_options).positional(p).run(), vm);
        notify(vm);
        
        std::ifstream ifs(config_file.c_str());
        if (!ifs)
        {
            std::cout << "can not open config file: " << config_file << "\n";
            // return 0;
        }
        else
        {
            store(parse_config_file(ifs, config_file_options), vm);
            notify(vm);
        }
    
        if (vm.count("help")) {
            std::cout << visible << "\n";
            return 0;
        }

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    } 

    std::cout << "Positionals: (" << arg_positionals.size() << ')';
    if (arg_positionals.size() > 0)
    {
        std::cout << " [";
        for (auto p: arg_positionals )
            std::cout << p << ',';
        std::cout << "\b]";
    }
    std::cout << '\n';

    std::cout << "Flag: " << (arg_flag ? "true" : "false") << '\n';

    std::cout << "Int: " << arg_int << '\n';

    std::cout << "Double: " << arg_double << '\n';
    
    std::cout << "String: " << arg_string << '\n';

    std::cout << "List: (" << arg_list.size() << ')';
    if (arg_list.size() > 0)
    {
        std::cout << " [";
        for (auto p: arg_list )
            std::cout << p << ',';
        std::cout << "\b]";
    }
    std::cout << '\n';

}