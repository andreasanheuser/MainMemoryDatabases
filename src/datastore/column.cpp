#include <stdexcept>
#include <cstdlib>
#include <algorithm>

#include "column.h"
#include "simplecharcontainer.h"
#include "datejd.h"
#include "../tools/stringExtensions.h"

namespace datastore {

  /*
   * Implementation class ColumnBase
   */
  ColumnBase::ColumnBase(const std::string& aColumnName)  
    : _columnName(aColumnName)
  {
  }

  ColumnBase::~ColumnBase()
  {
  }

  /*
   * Implementation class Column
   */
  template <typename T>
  Column<T>::Column(const std::string& aColumnName, const ColumnDef::ColumnType& aColumnType) 
    : ColumnBase(aColumnName), _columnType(aColumnType)
  {
  }

  template <typename T>
  Column<T>::~Column()
  {
  }

  template <typename T>
  bool Column<T>::insertValue(char* str, char*& endptr)
  {
    try {
      _attrValues.push_back(convertToColumnType(str, endptr));
    }
    catch (const std::invalid_argument& ia) {
      return false;
    }
    return true;
  }

  // template specifications to avoid runtime type checking
  template <>
  int Column<int>::convertToColumnType(char* str, char*& endptr)
  {
    return std::strtol(str, &endptr, 10);
  }

  template <>
  double Column<double>::convertToColumnType(char* str, char*& endptr)
  {
    return std::strtod(str, &endptr);
  }

  template <>
  char Column<char>::convertToColumnType(char* str, char*& endptr)
  {
    endptr = &str[1];
    return str[0];
  }

  template <>
  DateJd Column<DateJd>::convertToColumnType(char* str, char*& endptr)
  {
    return DateJd{str, endptr};
  }

  template <>
  const char* Column<const char*>::convertToColumnType(char* str, char*& endptr)
  {
    // this never gets called  - just needed for sucessfull compilation
    return nullptr;
  }
  // end template specifications

  template <typename T>
  void Column<T>::print(std::ostream& aOutputStream) const
  {
    std::cout << "Column: " << _columnName << std::endl;
    for (auto a : _attrValues)
      aOutputStream << a << "\n"; 

    aOutputStream << std::endl;
  }

  std::ostream& operator<< (std::ostream& aOutputStream, const ColumnBase& aColumnBase)
  {
    aColumnBase.print(aOutputStream);
    return aOutputStream;
  }

  /*
   * Implementation class TextColumn
   */

  TextColumn::TextColumn(const std::string& aColumnName, unsigned aChunkSize) 
    : ColumnBase(aColumnName),
      Column<const char*>(aColumnName, ColumnDef::ColumnType::TEXT),
      _textStorage(new SimpleCharContainer(aChunkSize))
  {
  }

  TextColumn::~TextColumn()
  {
    delete _textStorage;
  }

  bool TextColumn::insertValue(char* str, char*& endptr)
  {
    // TODO: fix search range
    endptr = std::find(str, str + 1000, '|');
    _attrValues.push_back(_textStorage->insert(str, endptr));
    return true;
  }

  // explicit template instantiation to avoid linking errors
  template class Column<int>;
  template class Column<double>;
  template class Column<char>;
  template class Column<DateJd>;
}
