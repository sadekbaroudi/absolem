#include "ReporterModule.h"
#include "../Interpreter.h"
#include "../../common/binary.h"

#if defined(DEBUG) && 1
#define DD(x) x
#else
#define DD(x)
#endif

namespace absolem {

    bool ReporterModule::onAfterTick() {
        DD(interpreter->getController()->debug("ReporterModule::onAfterTick runs");)
        if (dirty) {
            KeyCode arr[6] = {0,0,0,0,0,0};
            Byte i = 0;
            for (auto k : keys) {
                arr[i++] = k;
                if (i >= 5) break;
            }
            Modifiers m = currentMods | oneshotMods;
            oneshotMods = 0;
            interpreter->getController()->report(m, arr);
            DD(interpreter->getController()->debug("ReporterModule::onAfterTick: ["BINARY_PATTERN"] + [%d, %d, %d, %d, %d, %d]", BINARY(m), arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);)
            dirty = false;
        }
        return true;
    }

    Byte ReporterModule::onAfterTickPriority() {
        return defaultPriority;
    }

    void ReporterModule::press(KeyCode key) {
        DD(interpreter->getController()->debug("ReporterModule::press: %d", key);)
        keys.insert(key);
        dirty = true;
    }

    void ReporterModule::release(KeyCode key) {
        DD(interpreter->getController()->debug("ReporterModule::release: %d", key);)
        keys.erase(key);
        dirty = true;
    }

    void ReporterModule::modify(Modifiers mods) {
        currentMods |= mods;
        dirty = true;
    }

    void ReporterModule::unmodify(Modifiers mods) {
        currentMods &= ~mods;
        dirty = true;
    }

    
} // namespace absolem