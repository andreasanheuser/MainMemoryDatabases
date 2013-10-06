#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include <string>

namespace persistency {

  /*
   * Base class for columns of all types
   */
  class ColumnBase {
    public:
      ColumnBase(const std::string& columnName);
      virtual ~ColumnBase();

      // Possible types for each column
      enum class ColumnType {INTEGER, STRING};
  
      // insert value at end of column
      // converts string to type of specific column
      virtual bool insertValue(const std::string&) = 0;

      // returns the number of elements in this column
      virtual int size() const = 0;

      // access element at pos index
      virtual std::string operator[](int index) const = 0;

      // returns the type of this column
      virtual ColumnType getColumnType() const = 0;

    protected:
      std::string _columnName;

      ColumnBase(const ColumnBase&) = delete;
      ColumnBase& operator=(const ColumnBase&) = delete;
  };

  /*
   * Implementation for columns of specific types 
   */
  template <typename T>
  class Column : public virtual ColumnBase {
    public:
      Column(const std::string& columnName, const ColumnType columnType);
      ~Column();

      bool insertValue(const std::string&) override;
      int size() const override;
      ColumnType getColumnType() const override;
      std::string operator[](int index) const override;

    private:
      // converts string to type of specific column
      T convertToColumnType(const std::string& token) const;

    private:
      std::vector<T> _attrValues;
      ColumnType _columnType;
  };

}

#endif
