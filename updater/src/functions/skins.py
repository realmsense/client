import xml.etree.ElementTree as ET
import threading

from classes import *
from functions import *

def dump_player_skins():

    logger.log(logging.INFO, "Dumping player skins...")
    IndentFilter.level += 1

    spritesheet_file = download_file(SPRITESHEET_URL, TEMP_DIR / "spritesheet.json")
    spritesheet_img = download_file(CHARACTERS_IMG_URL, TEMP_DIR / "characters.png")
    skins_xml = download_file(SKINS_XML_URL, TEMP_DIR / "skins.xml")

    spritesheet_json = read_json(spritesheet_file)

    cpp_skins = {}
    for class_name in CLASS_LIST.values():
        cpp_skins[class_name] = []

    logger.log(logging.INFO, "Outputting png files...")

    tree = ET.parse(skins_xml)
    for object in tree.getroot():
        name = object.get("id")
        type = parse_int(object.get("type"))
        class_id = parse_int(object.find("PlayerClassType").text)
        sprite_name = object.find("AnimatedTexture/File").text
        sprite_index = object.find("AnimatedTexture/Index").text

        class_name = CLASS_LIST[class_id]
        file_name = name.lower().replace("-", " ").replace(" ", "_") + ".png"
        output_file = ROOT_DIR / "../src/other/skins" / file_name
        
        # extract_animated_sprite(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index)
        thread = threading.Thread(target=extract_animated_sprite, args=(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index))
        thread.start()

        cpp_skin_file = str(output_file).replace("\\", "\\\\") # TODO: use resource to pack in dll
        cpp_skin_str = f'skin_list[ClassList::{class_name}].push_back(new Skin("{name}", "{cpp_skin_file}", {type}));'
        cpp_skins[class_name].append(cpp_skin_str)

    logger.log(logging.INFO, "Writing to skins.h...")

    lines = []
    for class_name, skins in cpp_skins.items():
        lines.append(f"// {class_name}")
        for skin in skins:
            lines.append(skin)
        lines.append("")

    skins_h = ROOT_DIR / "../src/other/skins.h"
    skins_h.write_text("\n".join(lines))

    logger.log(logging.INFO, "Done")
    IndentFilter.level -= 1


    pass