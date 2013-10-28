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
      ColumnBase(const std::string& aColumnName);
      virtual ~ColumnBase();

      // inserts value at end of column
      // converts string to type of specific column
      virtual bool insertValue(const std::string& aValue) = 0;

      // returns the number of elements in this column
      virtual int size() const = 0;

      // prints column to standard out
      virtual void print(std::ostream& aOutputStream) const = 0;

      // returns the type of this column
      virtual ColumnDef::ColumnType getColumnType() const = 0;

    protected:
      std::string _columnName;

      ColumnBase(const ColumnBase&) = delete;
      ColumnBase& operator=(const ColumnBase&) = delete;
  };

  std::ostream& operator<< (std::ostream& aOutputStream, const ColumnBase& aColumnBase);

  /*
   * Implementation for columns of specific types 
   */
  template <typename T>
  class Column : public virtual ColumnBase {
    public:
      Column(const std::string& aColumnName, const ColumnDef::ColumnType& aColumnType);
      ~Column();

      virtual bool insertValue(const std::string& aValue) override;
      int size() const override { return _attrValues.size(); }
      ColumnDef::ColumnType getColumnType() const override { return _columnType; }

      void print(std::ostream& aOutputStream) const override;

      T operator[](const int aIndex) const { return _attrValues[aIndex]; }

    private:
      // converts string to type of specific column
      static T convertToColumnType(const std::string& aToken);

    protected:
      std::vector<T> _attrValues;
      ColumnDef::ColumnType _columnType;
  };

  /*
   * Text columns store their data in a char container
   */
  class TextColumn : public Column<const char *> {
    public:
      TextColumn(const std::string& aColumnName, const ColumnDef::ColumnType& aColumnType, unsigned aChunkSize);
      ~TextColumn();

      bool insertValue(const std::string& aValue) override;

    private:
      SimpleCharContainer* _textStorage;
  };
}

#endif
