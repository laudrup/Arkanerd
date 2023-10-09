#pragma once

#include <map>
#include <stdexcept>
#include <string>

namespace j2me {
class RecordStoreException : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

class RecordStore {
public:
  static RecordStore openRecordStore(const std::string& recordStoreName, bool createIfNecessary);
  int getNumRecords() const;
  std::string getRecord(int recordId);
  int addRecord(const std::string& data, int offset, int numBytes);
  void setRecord(int recordId, const std::string& newData, int offset, int numBytes);

private:
  RecordStore(const std::string& recordStoreName, bool createIfNecessary);

  std::map<int, std::string> records_;
};

} // namespace j2me
