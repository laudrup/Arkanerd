#include "os_util.h"

#include <atlbase.h>
#include <shlobj.h>
#include <windows.h>

#include <system_error>

namespace arkanerd {

std::filesystem::path current_exe_path() {
  wchar_t p[MAX_PATH];
  if (!GetModuleFileNameW(nullptr, p, MAX_PATH)) {
    throw std::system_error(static_cast<int>(GetLastError()), std::system_category(), "GetModuleFileNameW");
  }
  return std::filesystem::path{p}.parent_path();
}

std::filesystem::path data_dir() {
  CComHeapPtr<WCHAR> path;
  HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &path);
  if (!(SUCCEEDED(hr))) {
    throw std::system_error(hr, std::system_category(), "SHGetFolderPathW");
  }
  return std::wstring{path};
}

} // namespace arkanerd
