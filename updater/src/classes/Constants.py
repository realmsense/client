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

SPRITESHEET_URL = CURRENT_CLIENT_URL + "extracted_assets/TextAsset/spritesheet.json"
CHARACTERS_IMG_URL = CURRENT_CLIENT_URL + "extracted_assets/Texture2D/characters.png"
SKINS_XML_URL = CURRENT_CLIENT_URL + "extracted_assets/TextAsset/skins.xml"

# PlayerClassType
CLASS_LIST = {
    0xFFFF: "Any",
    0x300: "Rogue",
    0x307: "Archer",
    0x30e: "Wizard",
    0x310: "Priest",
    0x31d: "Warrior",
    0x31e: "Knight",
    0x31f: "Paladin",
    0x320: "Assassin",
    0x321: "Necromancer",
    0x322: "Huntress",
    0x323: "Mystic",
    0x324: "Trickster",
    0x325: "Sorcerer",
    0x326: "Ninja",
    0x311: "Samurai",
    0x31c: "Bard",
    0x331: "Summoner",
}