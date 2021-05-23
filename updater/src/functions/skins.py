import xml.etree.ElementTree as ET
import threading

from functions.helpers import download_file, parse_int

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
        file_name = strip_non_ascii(name).lower().replace("-", " ").replace(" ", "_") + ".png"
        output_file = ROOT_DIR / "../src/other/player_skins" / file_name
        
        # extract_animated_sprite(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index)
        thread = threading.Thread(target=extract_animated_sprite, args=(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index))
        thread.start()

        cpp_skin_file = str(output_file).replace("\\", "\\\\") # TODO: use resource to pack in dll
        cpp_skin_str = f'player_skins[ClassList::{class_name}].push_back(new Skin("{name}", "{cpp_skin_file}", {type}));'
        cpp_skins[class_name].append(cpp_skin_str)

    logger.log(logging.INFO, "Writing to player_skins.h...")

    lines = []
    for class_name, skins in cpp_skins.items():
        lines.append(f"// {class_name}")
        for skin in skins:
            lines.append(skin)
        lines.append("")

    player_skins_h = ROOT_DIR / "../src/other/player_skins.h"
    player_skins_h.write_text("\n".join(lines))

    logger.log(logging.INFO, "Done")
    IndentFilter.level -= 1


def dump_pet_skins():

    logger.log(logging.INFO, "Dumping pet skins...")
    IndentFilter.level += 1

    spritesheet_file = download_file(SPRITESHEET_URL, TEMP_DIR / "spritesheet.json")
    spritesheet_img = download_file(CHARACTERS_IMG_URL, TEMP_DIR / "characters.png")
    pets_xml = download_file(PETS_XML_URL, TEMP_DIR / "pets.xml")

    spritesheet_json = read_json(spritesheet_file)

    cpp_skins = {} # [family]: { [rarity]: str[] }

    logger.log(logging.INFO, "Outputting png files...")
    tree = ET.parse(pets_xml)
    for object in tree.getroot():

        pet_skin = object.find("PetSkin") != None
        if not pet_skin:
            continue

        name = object.find("DisplayId").text
        type = parse_int(object.get("type"))
        rarity = object.find("Rarity")
        family = object.find("Family")
        sprite_name = object.find("AnimatedTexture/File").text
        sprite_index = object.find("AnimatedTexture/Index").text

        if rarity is None: rarity = "Common"
        else: rarity = rarity.text

        if family is None: family = "Any"
        elif family.text == "? ? ? ?": family = "Question"
        else: family = family.text

        file_name = strip_non_ascii(name).lower().replace("?", "").replace("'", "").replace(" ", "_") + ".png"
        output_file = ROOT_DIR / "../src/other/pet_skins" / file_name

        cpp_skin_file = str(output_file).replace("\\", "\\\\") # TODO: use resource to pack in dll

        # extract_animated_sprite(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index)
        thread = threading.Thread(target=extract_animated_sprite, args=(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index, 33))
        thread.start()

        if cpp_skins.get(family) is None:
            cpp_skins[family] = {}
        if cpp_skins[family].get(rarity) is None:
            cpp_skins[family][rarity] = []

        cpp_skin_str = f'pet_skins[PetFamily::{family}][PetRarity::{rarity}].push_back(new Skin("{name}", "{cpp_skin_file}", {type}));'
        cpp_skins[family][rarity].append(cpp_skin_str)

    logger.log(logging.INFO, "Writing to pet_skins.h")

    lines = []
    for family, rarity_list in cpp_skins.items():
        lines.append(f"// {family}")
        for rarity, skins in rarity_list.items():
            lines.append(f"/* {rarity} */")
            for skin in skins:
                lines.append(skin)
        lines.append("")

    pet_skins_h = ROOT_DIR / "../src/other/pet_skins.h"
    pet_skins_h.write_text("\n".join(lines))

    logger.log(logging.INFO, "Done")
    IndentFilter.level -= 1
