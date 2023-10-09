#include "RecordStore.h"

#include <cstddef>
#include <iterator>
#include <filesystem>
#include <fstream>

#include <iostream>

namespace j2me {

RecordStore::RecordStore(const std::string& recordStoreName, bool createIfNecessary) {
  std::filesystem::path fname{recordStoreName + ".dat"};
  if (!createIfNecessary && !std::filesystem::exists(fname)) {
    throw RecordStoreException{"RecordStore does not exist: " + fname.string()};
  }
  std::cerr << "Opened record: " << fname << "\n";
  // TODO: Error handling
  std::ifstream ifs{fname, std::ios::binary};
  while (ifs) {
    size_t size = 0;
    ifs >> size;
    int id = 0;
    ifs >> id;
    std::string data(size, '\0');
    ifs.read(data.data(), size);
    records_.insert({id, data});
  }
}

RecordStore RecordStore::openRecordStore(const std::string& recordStoreName, bool createIfNecessary) {
  return RecordStore{recordStoreName, createIfNecessary};
}

int RecordStore::getNumRecords() const {
  return static_cast<int>(records_.size());
}

std::string RecordStore::getRecord(int /*recordId*/) {
  return {};
}

int RecordStore::addRecord(const std::string& /*data*/, int /*offset*/, int /*numBytes*/) {
  return 0;
}

void RecordStore::setRecord(int /*recordId*/, const std::string& /*newData*/, int /*offset*/, int /*numBytes*/) {
  abort();
}

} // namespace j2me
