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

  string GetDataRefType(uint64_t ref);

  json GetDataRefValue(uint64_t ref);

  json SetDataRefValue(uint64_t ref, json newValue);

  // *private*

  int ReadDataRefInt(XPLMRef gDataRef);

  float ReadDataRefFloat(XPLMRef gDataRef);

  double ReadDataRefDouble(XPLMRef gDataRef);

  vector<int> ReadDataRefIntArray(XPLMRef gDataRef);

  vector<float> ReadDataRefFloatArray(XPLMRef gDataRef);

  string ReadDataRefByteArray(XPLMRef gDataRef);

  json WriteDataRefInt(XPLMRef gDataRef, json newValue);

  json WriteDataRefFloat(XPLMRef gDataRef, json newValue);

  json WriteDataRefDouble(XPLMRef gDataRef, json newValue);

  json WriteDataRefIntArray(XPLMRef gDataRef, json newValue);

  json WriteDataRefFloatArray(XPLMRef gDataRef, json newValue);

  json WriteDataRefByteArray(XPLMRef gDataRef, json newValue);

} // namespace manipulator
