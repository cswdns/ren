#include <CommandLineProcessor.h>
#include <FileRenamer.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char* argv[])
{
    CommandLineProcessor cmdLineProc(argc, argv);

    if (!cmdLineProc.IsValid())
    {
        std::cout << cmdLineProc.GetErrorString() << std::endl;
    }

    if (cmdLineProc.UsageRequired())
    {
        std::cout << cmdLineProc.GetUsage() << std::endl;
        return 1;
    }

	char buf[BUFSIZ];
	char *cwd = getcwd(buf, sizeof(buf));

    if (cwd == NULL)
    {
        std::cout << "Error retrieving current working directory" << std::endl;
        return 1;
    }
    
    try
    {
        FileRenamer fileRenamer(cmdLineProc.GetSrcFilePattern(),
                                cmdLineProc.GetDestFilePattern(),
                                cmdLineProc.IsRecursive());

        fileRenamer.RenameMatchingFilesInDirectory(cwd);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "Unkonwn error encountered." << std::endl;
        return 1;
    }

    return 0;
}
