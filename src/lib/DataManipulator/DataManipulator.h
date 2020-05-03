#include "XPLM/XPLMDataAccess.h"
#include <nlohmann/json.hpp>
#include <cstdlib>

using namespace std;
using json = nlohmann::json;

namespace manipulator
{
  typedef XPLMDataRef XPLMRef;

  uint64_t GetDataRefReference(string data_ref);

  bool GetDataRefWitrable(uint64_t ref);

  bool GetDataRefGood(uint64_t ref);

  json GetDataRefValue(uint64_t ref);

  json SetDataRefValue(uint64_t ref);

  // *private*

  int ReadDataRefInt(XPLMRef gDataRef);

  float ReadDataRefFloat(XPLMRef gDataRef);

  double ReadDataRefDouble(XPLMRef gDataRef);

  vector<int> ReadDataRefIntArray(XPLMRef gDataRef);

  vector<float> ReadDataRefFloatArray(XPLMRef gDataRef);

  string ReadDataRefByteArray(XPLMRef gDataRef);

  void WriteDataRefInt(uint64_t ref, json newValue);

  void WriteDataRefFloat(uint64_t ref, json newValue);

  void WriteDataRefDouble(uint64_t ref, json newValue);

  void WriteDataRefIntArray(uint64_t ref, json newValue);

  void WriteDataRefFloatArray(uint64_t ref, json newValue);

  void WriteDataRefByteArray(uint64_t ref, json newValue);

} // namespace manipulator
