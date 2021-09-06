#ifndef ILRD_RD102_FS_COMPONENT_HPP
#define ILRD_RD102_FS_COMPONENT_HPP

#include <vector> //vector
class Directory;
class FS_Component
{
public:
    explicit FS_Component(std::string file_name = "no_name");

    virtual ~FS_Component();

    virtual void Copy(Directory *other) const = 0;
    virtual void Delete() = 0;

    void SetFileName(const std::string &file_name);
    std::string GetFileName() const;

private:
    FS_Component(const FS_Component& other);
    FS_Component& operator=(const FS_Component& other);

    std::string m_file_name;
};

class File: public FS_Component
{
public:
    explicit File(std::string file_name = "no_name");

    virtual ~File();

    virtual void Copy(Directory *other) const;
    virtual void Delete();

    std::string Read(size_t num_of_bytes);
    void Write(std::string str_to_write);
    size_t GetSize() const;

private:

    char *m_initial_byte;
    size_t m_size;
};


class Directory: public FS_Component
{
public:
    explicit Directory(std::string file_name = "no_name");
    virtual ~Directory();

    void AddFile(FS_Component *file);
    virtual void Copy(Directory *other) const;
    virtual void Delete();

private:

    std::vector<FS_Component *> m_files;
};

#endif //ILRD_RD102_FS_COMPONENT_HPP
