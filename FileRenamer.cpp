#include <FileRenamer.h>
#include <dirent.h>
#include <sys/stat.h>
#include <vector>
#include <iostream>

int FileRenamer::RenameMatchingFilesInDirectory(std::string directoryName) const
{
    std::vector<std::string> subdirectories;
    int retCode = 0;
    DIR* dir = opendir(directoryName.c_str());
    if (!dir)
    {
        std::cout << "Error occurred while opening directory " << directoryName << std::endl;
        return 1;
    }
    
    directoryName += '/';

    for (;;)
    {
        struct dirent* entry = readdir(dir); // Get next directory entry
        if (entry == NULL) // No more entries
            break;

        std::string oldFileName(entry->d_name);
        std::string oldFilePath = directoryName + oldFileName;
        struct stat filestat;
        if (stat(oldFilePath.c_str(), &filestat))
        {
            std::cout << "Error occurred while processing " << oldFilePath << std::endl;
            continue;
        }
        
        if ((S_ISDIR(filestat.st_mode)) && (m_recursive))
        {
            if ((oldFileName == ".") || (oldFileName == "..")) // skip these
                continue;
                
            // buffer directory names for later recursion
            subdirectories.push_back(oldFilePath);
        }
        
        if (!(S_ISREG(filestat.st_mode))) // only rename "regular" files
            continue;
            
        std::string substitutionText;
        if (m_srcWildcardFilePattern.TryGetWildcardSubstitution(oldFileName, substitutionText))
        {
            std::string newFileName = m_destWildcardFilePattern.DoSubstitution(substitutionText);
            std::string newFilePath = directoryName + newFileName;
            
            std::cout << "Renaming " << oldFilePath << " to " << newFilePath;
            int rc = rename(oldFilePath.c_str(), newFilePath.c_str());
            if (rc != 0)
            {
                std::cout << " - Error occurred.  Could not complete copy.";
                retCode = rc;
            }
            std::cout << std::endl;
        }
    }

    if (closedir(dir) == -1)
    {
        std::cout << "Error occurred while closing directory " << directoryName << std::endl;
        return 1;
    }
    
    for (std::vector<std::string>::const_iterator it = subdirectories.begin(); it != subdirectories.end(); it++)
    {
        // Rename the matching files in the subdirectories
        int rc = RenameMatchingFilesInDirectory(*it);
        if (rc != 0)
            retCode = rc;
    }
    
    return retCode;
}

