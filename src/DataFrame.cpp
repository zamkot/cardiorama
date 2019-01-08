#include <DataFrame.hpp>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static std::string expandHomePath(std::string path) {
    if (path[0] == '~') {
        path.erase(0, 2);
        
        auto pw = getpwuid(getuid());
        auto homedir = pw->pw_dir;

        std::stringstream ss;
        ss << homedir << '/' << path;

        path = ss.str();
    }

    return path;
}

Column::Column(std::string name, std::function<std::vector<std::string>()> getData) : 
    name{name}, data{getData()} {}

Column::Column(std::string name, std::vector<std::string> data) : name(name), data(data) {}

std::string Column::represent() const {
    std::stringstream ss;
    ss << name << ": [";
    for (const auto& element : data)
        ss << element << ", ";
    ss << "\b\b]";
    return ss.str();
}

size_t Column::length() const {
    return data.size();
}


DataFrame::DataFrame(std::string path) {
    std::ifstream file(expandHomePath(path));
    while(file) {
        readNextRow(file);
    }
}


void DataFrame::readNextRow(std::istream& str)
{
    std::string line;
    std::getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;
    std::vector<std::string> data;

    std::getline(lineStream, cell, ',');
    std::string name = cell;

    while(std::getline(lineStream, cell, ','))
    {
        data.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        data.push_back("");
    }

    if(!name.empty())
        addColumn(Column(name, data));
}


void DataFrame::addColumn(Column column) {
    columns.push_back(column);
}


std::string DataFrame::represent() const{
    std::stringstream ss;
    for (const auto& column : columns)
        ss << column.represent() << std::endl;
    return ss.str();
}


size_t DataFrame::length() const{
    size_t max = 0;
    for (auto& column : columns) {
        if (column.length() > max)
            max = column.length();
    }
    return max;
}

// FIXME: Might break when df contains empty columns
void DataFrame::toCsv(std::string path) const{
    std::stringstream ss;
    auto width = length();

    for (auto& column : columns) {
        ss << column.name << ',';
        auto fieldsToFill = width;
        for (auto& element : column.data) {
            ss << element << ',';
            fieldsToFill--;
        }

        while (fieldsToFill--) { ss << ','; }
        
        ss.seekp(-1, ss.cur);
        ss << std::endl;
    }

    writeFile(path, ss.str());
}

// FIXME: Might break when df contains empty columns
void DataFrame::toCsvAsColumns(std::string path) const{
    std::stringstream ss;

    for (auto& column : columns)
        ss << column.name << ',';
    ss.seekp(-1, ss.cur);
    ss << std::endl;

    for (int i = 0; i < length(); i++) {
        for (auto& column : columns) {
            if (i < column.length())
                ss << column.data[i];
            ss << ',';
        }
        ss.seekp(-1, ss.cur);
        ss << std::endl;
    }

    writeFile(path, ss.str());
}


std::ostream& operator<<(std::ostream& os, const DataFrame& df)
{
    std::string s = df.represent();
    os << s;
    return os;
}

void writeFile(std::string path, const std::string& buffer) {
    std::ofstream file(expandHomePath(path), std::ofstream::out | std::ofstream::trunc);
    file << buffer;
}
