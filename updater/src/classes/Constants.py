from pathlib import Path

### Directories
ROOT_DIR = Path(__file__).parent.parent.parent
CONFIG_DIR      = ROOT_DIR / "config"

OUTPUT_DIR      = ROOT_DIR / "output"
TEMP_DIR        = OUTPUT_DIR / "temp"


### Urls
CURRENT_CLIENT_URL = "https://rotmg.extacy.cc/production/client/current/"

IL2CPP_FUNCTIONS_URL = CURRENT_CLIENT_URL + "il2cpp_dump/cpp/appdata/il2cpp-functions.h"
IL2CPP_TYPES_URL = CURRENT_CLIENT_URL + "il2cpp_dump/cpp/appdata/il2cpp-types.h"