#include <stdexcept>
#include "column.h"

namespace persistency {
  ColumnBase::ColumnBase(const std::string& columnName)  
    : _columnName(columnName)
  {
  }

  ColumnBase::~ColumnBase()
  {
  }

  template <typename T>
  Column<T>::Column(const std::string& columnName, const ColumnType columnType) 
    : ColumnBase(columnName), _columnType(columnType)
  {
  }

  template <typename T>
  Column<T>::~Column()
  {
  }

  template <typename T>
  bool Column<T>::insertValue(const std::string& token)
  {
    try {
      _attrValues.push_back(convertToColumnType(token));
    }
    catch (const std::invalid_argument& ia) {
      return false;
    }
    return true;
  }

  template <typename T>
  T Column<T>::convertToColumnType(const std::string& token) const
  {
    return token;
  }

  // template specialization to avoid usage of typeid
  template <>
  int Column<int>::convertToColumnType(const std::string& token) const
  {
    return std::stoi(token);
  }

  template <typename T>
  int Column<T>::size() const
  {
    return _attrValues.size();
  }

  template <typename T>
  ColumnBase::ColumnType Column<T>::getColumnType() const
  {
    return _columnType;
  }

  template <typename T>
  std::string Column<T>::operator[](int index) const
  {
    return _attrValues[index];
  }

  template <>
  std::string Column<int>::operator[](int index) const
  {
    return std::to_string(_attrValues[index]);
  }

}
