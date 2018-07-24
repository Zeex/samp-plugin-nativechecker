#include "plugin.h"

typedef void (*logprintf_t)(const char *fmt, ...);

static logprintf_t logprintf;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
  return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **pluginData) {
  logprintf = reinterpret_cast<logprintf_t>(pluginData[PLUGIN_DATA_LOGPRINTF]);
  return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
  return;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
  AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);

  AMX_FUNCSTUBNT *natives = reinterpret_cast<AMX_FUNCSTUBNT*>(hdr->natives + 
      reinterpret_cast<unsigned int>(amx->base));
  AMX_FUNCSTUBNT *libraries = reinterpret_cast<AMX_FUNCSTUBNT*>(hdr->libraries + 
      reinterpret_cast<unsigned int>(amx->base));

  for (AMX_FUNCSTUBNT *n = natives; n < libraries; n++) {
    if (n->address == 0) {
      char *name = reinterpret_cast<char*>(n->nameofs + 
          reinterpret_cast<unsigned int>(hdr));
      logprintf("   Error: Function not registered: '%s'", name);
    }
  }

  return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
  return AMX_ERR_NONE;
}

