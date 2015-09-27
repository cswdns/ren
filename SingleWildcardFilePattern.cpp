#include <SingleWildcardFilePattern.h>

SingleWildcardFilePattern::SingleWildcardFilePattern(const std::string& filePattern)
{
    size_t wildcardCount = std::count(filePattern.begin(), filePattern.end(), '*');
    if (wildcardCount != 1)
    {
        std::string errorString("Invalid file pattern '");
        errorString += filePattern;
        errorString += "' specified.  File patterns must contain exactly one wildcard asterisk.";
        
        throw std::runtime_error(errorString);
    }

    int wildcardPos = filePattern.find('*');
    m_beforeWildcardPart = filePattern.substr(0, wildcardPos);
    m_afterWildcardPart = filePattern.substr(wildcardPos + 1);
}

bool SingleWildcardFilePattern::TryGetWildcardSubstitution(const std::string &fileName,
        std::string& wildcardSubstitutionText) const
{
    // Check that it begins with the matching text
    if (fileName.find(m_beforeWildcardPart) != 0)
        return false;

    // And also that it ends with the matching text
    int afterWildcardPartPos = fileName.rfind(m_afterWildcardPart);
    if (afterWildcardPartPos != fileName.length() - m_afterWildcardPart.length())
        return false;
        
    // And that they don't overlap
    if (m_beforeWildcardPart.length() + m_afterWildcardPart.length() > fileName.length())
        return false;
        
    wildcardSubstitutionText = fileName.substr(m_beforeWildcardPart.length(),
        afterWildcardPartPos - m_beforeWildcardPart.length());
        
    return true;
}

std::string SingleWildcardFilePattern::DoSubstitution(const std::string& substitutionText) const
{
    return m_beforeWildcardPart + substitutionText + m_afterWildcardPart;
}
