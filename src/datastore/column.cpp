#include <stdexcept>
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
  bool Column<T>::insertValue(const std::string& aValue)
  {
    try {
      _attrValues.push_back(convertToColumnType(aValue));
    }
    catch (const std::invalid_argument& ia) {
      return false;
    }
    return true;
  }

  template <typename T>
  bool Column<T>::insertValue(const char* begin, const char* end)
  {
    try {
      _attrValues.push_back(convertToColumnType(begin, end));
    }
    catch (const std::invalid_argument& ia) {
      return false;
    }
    return true;
  }

  template <typename T>
  T Column<T>::convertToColumnType(const std::string& aToken)
  {
    return aToken;
  }

  // template specialization to avoid usage of typeid
  template <>
  int Column<int>::convertToColumnType(const std::string& aToken)
  {
    return std::stoi(aToken);
  }

  template <>
  double Column<double>::convertToColumnType(const std::string& aToken)
  {
    return std::stod(aToken);
  }

  template <>
  char Column<char>::convertToColumnType(const std::string& aToken)
  {
    return aToken[0];
  }

  template <>
  DateJd Column<DateJd>::convertToColumnType(const std::string& aToken)
  {
    std::vector<std::string> tokens = tools::tokenize(aToken, '-');
    int lYear = std::stoi(tokens[0]);
    int lMonth = std::stoi(tokens[1]);
    int lDay = std::stoi(tokens[2]);
    return DateJd{lYear, lMonth, lDay}; 
  }

  template <>
  const char* Column<const char*>::convertToColumnType(const std::string& aToken)
  {
    return aToken.c_str();
  }
  // end of template specializations

  // mmap stuff
  template <>
  int Column<int>::convertToColumnType(const char* begin, const char* end)
  {
    return std::stoi(std::string(begin, end-begin));
  }

  template <>
  double Column<double>::convertToColumnType(const char* begin, const char* end)
  {
    return std::stod(std::string(begin, end-begin));
  }

  template <>
  char Column<char>::convertToColumnType(const char* begin, const char* end)
  {
    return begin[0];
  }

  template <>
  DateJd Column<DateJd>::convertToColumnType(const char* begin, const char* end)
  {
    return convertToColumnType(std::string(begin, end-begin));
  }

  template <>
  const char* Column<const char*>::convertToColumnType(const char* begin, const char* end)
  {
    return std::string(begin, end-begin).c_str();
  }
  // end mmap stuff

  template <typename T>
  void Column<T>::print(std::ostream& aOutputStream) const
  {
    for (auto a : _attrValues)
      aOutputStream << a << ", " << std::endl; 
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

  bool TextColumn::insertValue(const std::string& aValue)
  {
    _attrValues.push_back(_textStorage->insert(&(*aValue.begin()), &(*aValue.end())));
    return true;
  }

  bool TextColumn::insertValue(const char* begin, const char* end)
  {
    _attrValues.push_back(_textStorage->insert(begin, end));
    return true;
  }

  // explicit template instantiation to avoid linking errors
  template class Column<int>;
  template class Column<double>;
  template class Column<char>;
  template class Column<DateJd>;
}
