#include <string>

class SingleWildcardFilePattern
{
/* Encapsulates filename wildcard matching and substitution */

public:
    SingleWildcardFilePattern(const std::string& filePattern);
    
    bool TryGetWildcardSubstitution(const std::string &fileName,
        std::string& wildcardSubstitutionText) const;
        
    std::string DoSubstitution(const std::string& substitutionText) const;

private:
    std::string m_beforeWildcardPart, m_afterWildcardPart;
};
