#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <sstream>
#include <memory>

class Column {
    std::string name;
    std::vector<std::string> data;

    friend class DataFrame;
    template<typename T, typename F> friend Column createColumn(std::string name, T data, F convert);
    template<typename T> friend Column createColumn(std::string name, T data);

public:
    Column() {};
    Column(std::string name, std::function<std::vector<std::string>()>);
    Column(std::string name, std::vector<std::string> data);
    std::string represent() const;
    size_t length() const;

    template<typename T, typename F> std::vector<T> decode(F convert) const {
        std::vector<T> result;
        for (const auto& element : data) {
            result.push_back(convert(element));
        }
        return result;
    }
};


class DataFrame {
    std::vector<Column> columns;

public:
    DataFrame() {};
    DataFrame(std::string path);

    void addColumn(Column);
    std::string represent() const;
    size_t length() const;
    void toCsv(std::string) const;
    void toCsvAsColumns(std::string) const;
    void readNextRow(std::istream& str);

    template<typename T> void addColumn(std::string name, T data) {
        addColumn(createColumn(name, data));
    };

    template<typename T, typename F> void addColumn(std::string name, T data, F convert) {
        addColumn(createColumn(name, data, convert));
    };

    template<typename T, typename F> std::vector<T> get(std::string name, F convert) const{
        for (auto& column : columns) {
            if (column.name == name) {return column.decode<T>(convert);}
        }
        return {};
    }
};

std::ostream& operator<<(std::ostream& os, const DataFrame& df);

void writeFile(std::string path, const std::string& buffer);


template<typename T> Column createColumn(std::string name, T data) {
    Column c;
    c.name = name;
    for (auto & element : data) {
        c.data.push_back(std::to_string(element));
    }
    return c;
};


template<typename T, typename F> Column createColumn(std::string name, T data, F convert) {
    Column c;
    c.name = name;
    for (auto const & element : data) {
        c.data.push_back(convert(element));
    }
    return c;
};
