#include <CommandLineProcessor.h>

CommandLineProcessor::CommandLineProcessor(int argc, char* argv[])
{
    m_recursive = false;
    m_usageRequested = false;

    if (argc == 2)
    {
        // If there is only one parameter, it better be -h
        if (strcmp(argv[1], "-h") == 0)
        {
            m_usageRequested = true;
        }
        else
        {
            m_error = "Invalid option ";
            m_error += argv[1];
        }
    }
    else if (argc == 3)
    {
        m_srcFilePattern = argv[1];
        m_destFilePattern = argv[2];
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-r") == 0)
        {
            m_recursive = true;
            m_srcFilePattern = argv[2];
            m_destFilePattern = argv[3];
        }
        else
        {
            m_error = "Invalid option ";
            m_error += argv[1];
        }
    }
    else
    {
        m_error = "Invalid number of arguments";
    }
}

std::string CommandLineProcessor::GetUsage() const
{
    return "usage:  ren [-r] filePattern1 filePattern2";
}
