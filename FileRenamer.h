#include <string>
#include <SingleWildcardFilePattern.h>

class FileRenamer
{
public:
    FileRenamer(const std::string& srcFilePattern,
                const std::string& destFilePattern,
                bool recursive = false) :
                    m_srcWildcardFilePattern(srcFilePattern),
                    m_destWildcardFilePattern(destFilePattern),
                    m_recursive(recursive) {}

	int RenameMatchingFilesInDirectory(std::string directoryName) const;

private:
    const bool m_recursive;
    const SingleWildcardFilePattern m_srcWildcardFilePattern, m_destWildcardFilePattern;
};
