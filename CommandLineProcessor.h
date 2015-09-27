#include <string>

class CommandLineProcessor
{
/* Simple encapsulation of command line processing */

public:
    CommandLineProcessor(int argc, char* argv[]);

    std::string GetUsage() const;

    bool IsValid() const {return m_error.empty();}
    bool UsageRequired() const {return m_usageRequested || !IsValid();}
    std::string GetErrorString() const {return m_error;}

    bool IsRecursive() const {return m_recursive;}
    std::string GetSrcFilePattern() const {return m_srcFilePattern;}
    std::string GetDestFilePattern() const {return m_destFilePattern;}

private:
    bool m_recursive;
    bool m_usageRequested;
    std::string m_error;
    std::string m_srcFilePattern;
    std::string m_destFilePattern;
};
