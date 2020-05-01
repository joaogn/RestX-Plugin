// DataManipulator.cpp

#include "DataManipulator.h"
#include "XPLM/XPLMDataAccess.h"

namespace manipulator
{

  int ReadDataRefInt(uint64_t ref)
  {
    static XPLMDataRef gDataRef = NULL;
    gDataRef = XPLMFindDataRef("sim/cockpit/radios/nav1_freq_hz");
    const int value = XPLMGetDatai(gDataRef);
    return value;
  }

  float ReadDataRefFloat(uint64_t ref) {}

  double ReadDataRefDouble(uint64_t ref) {}

  vector<int> ReadDataRefIntArray(uint64_t ref) {}

  vector<float> ReadDataRefFloatArray(uint64_t ref) {}

  vector<uint8_t> ReadDataRefByteArray(uint64_t ref) {}

  void WriteDataRefInt(uint64_t ref, json newValue) {}

  void WriteDataRefFloat(uint64_t ref, json newValue) {}

  void WriteDataRefDouble(uint64_t ref, json newValue) {}

  void WriteDataRefIntArray(uint64_t ref, json newValue) {}

  void WriteDataRefFloatArray(uint64_t ref, json newValue) {}

  void WriteDataRefByteArray(uint64_t ref, json newValue) {}

  uint64_t GetDataRefReference(string data_ref) {}

  json GetDataRefValue(uint64_t ref)
  {
    json response;
    return response["value"] = ReadDataRefInt(ref);
  }

  json GetDataRefWitrable(uint64_t ref) {}

  json GetDataRefGood(uint64_t ref) {}

  json SetDataRefValue(uint64_t ref) {}
} // namespace manipulator