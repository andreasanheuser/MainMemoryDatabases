#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include <string>
#include <iostream>
#include "tableSchema.h"

class SimpleCharContainer;

namespace datastore {

  /*
   * Base class for columns of all types
   */
  class ColumnBase {
    public:
      explicit ColumnBase(const std::string& aColumnName);
      virtual ~ColumnBase();

    private:
      ColumnBase(const ColumnBase&) = delete;
      ColumnBase& operator=(const ColumnBase&) = delete;

    public:
      // inserts value at end of column and converts char* to specific column type up to delimeter |
      // end points to char one behind last converted char
      virtual bool insertValue(char* str, char*& endptr) = 0;

      // returns the number of elements in this column
      virtual int size() const = 0;

      // prints column to standard out
      virtual void print(std::ostream& aOutputStream) const = 0;

      // returns the type of this column
      virtual ColumnDef::ColumnType getColumnType() const = 0;

    protected:
      std::string _columnName;
  };

  std::ostream& operator<< (std::ostream& aOutputStream, const ColumnBase& aColumnBase);

  /*
   * Implementation for columns of specific types 
   */
  template <typename T>
  class Column : public virtual ColumnBase {
    public:
      explicit Column(const std::string& aColumnName, const ColumnDef::ColumnType& aColumnType);
      ~Column();

      bool insertValue(char* str, char*& endptr) override;

      int size() const override { return _attrValues.size(); }
      ColumnDef::ColumnType getColumnType() const override { return _columnType; }

      void print(std::ostream& aOutputStream) const override;

      T operator[](const int aIndex) const { return _attrValues[aIndex]; }

    private:
      // converts string to type of specific column
      static T convertToColumnType(char* str, char*& endptr);

    protected:
      std::vector<T> _attrValues;
      ColumnDef::ColumnType _columnType;
  };

  /*
   * Text columns store their data in a char container
   */
  class TextColumn : public Column<const char *> {
    public:
      explicit TextColumn(const std::string& aColumnName, unsigned aChunkSize);
      ~TextColumn();

      bool insertValue(char* str, char*& endptr) override;

    private:
      SimpleCharContainer* _textStorage;
  };
}

#endif
