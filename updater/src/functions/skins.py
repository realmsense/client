import xml.etree.ElementTree as ET
import threading
import shutil

from classes import *
from functions import *

def dump_player_skins():

    logger.log(logging.INFO, "Dumping player skins...")
    IndentFilter.level += 1

    PLAYER_SKINS_DIR = ROOT_DIR / "../src/other/player_skins"
    delete_dir_contents(PLAYER_SKINS_DIR)

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
        output_file = PLAYER_SKINS_DIR / file_name
        
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


def dump_player_outfits():

    # RotMG doesn't store dyes/textiles textures in the xml
    # For textiles we need to extract all the sprites in the "textileWxH" spritesheet. (w = width, h = height)
    # (see below how rotmg uses the <Tex1/2> attribute for textiles)
    # For Dyes, there's no sprite because it's just a solid color.
    # E.g.: 0x01F0F8FF = #f0f8ff (idk what the 0x01 is)

    PLAYER_OUTFITS_DIR = ROOT_DIR / "../src/other/player_outfits"
    delete_dir_contents(PLAYER_OUTFITS_DIR)

    spritesheet_file = download_file(SPRITESHEET_URL, TEMP_DIR / "spritesheet.json")
    spritesheet_img = download_file(MAPOBJECTS_IMG_URL, TEMP_DIR / "mapObjects.png")
    spritesheet_json = read_json(spritesheet_file)

    cpp_lines = []

    textiles_xml = download_file(TEXTILES_XML_URL, TEMP_DIR / "textiles.xml")
    textiles = []
    for object in ET.parse(textiles_xml).getroot():
        name = object.get("id")
        tex1 = object.find("Tex1")
        tex2 = object.find("Tex2")

        tex = ""
        if tex1 is not None:
            tex = tex1.text
        else:
            tex = tex2.text

        textiles.append({"name": name, "tex": tex})
        file = PLAYER_OUTFITS_DIR / (tex + ".png")
        cpp_file = str(file).replace("\\", "\\\\")
        cpp_str = f'player_outfits.push_back(new Skin("{name}", "{cpp_file}", {tex}));'
        cpp_lines.append(cpp_str)

    # Textiles - Extract images
    for sprite in spritesheet_json["sprites"]:
        if not sprite["spriteSheetName"].startswith("textile"):
            continue

        sprite_index = sprite["index"]
        pos = sprite["position"]
        spritesheet_name = sprite["spriteSheetName"]
        
        # build the tex1/tex2: 0x9000001
        # 0x9 is the width of the textile, last digit is the index of the file from the spritesheet.
        width = regex.search("textile(\d+)x", spritesheet_name).group(1)
        # name = "0x" + hex(int(width)) 
        name = hex(int(width))
        name = name.ljust(9, "0")   # 0x9000000
        name = int(name, 0)
        name += sprite["index"]     # add index
        name = hex(name)            # convert back to hex string, 0x9000001

        file_name = name + ".png"
        output_file = PLAYER_OUTFITS_DIR / file_name
        
        exists = any(x for x in textiles if x["tex"] == name)
        if not exists:
            continue

        # extract_textile_thread(spritesheet_img, output_file, pos)
        thread = threading.Thread(target=extract_textile_thread, args=(spritesheet_img, output_file, pos))
        thread.start()

    # Extract Dyes


        # large_outfits.push_back(new Skin(name, file, type))
        # cpp_skin_str = f'player_skins[ClassList::{class_name}].push_back(new Skin("{name}", "{cpp_skin_file}", {type}));'

    # Output Header
    outfits_h = ROOT_DIR / "../src/other/player_outfits.h"
    outfits_h.write_text("\n".join(cpp_lines))


def extract_textile_thread(spritesheet_img, output_file, pos):
    extract_from_image(output_file, spritesheet_img, pos)
    resize_repeat_image(output_file, pos["w"] * 4)
    resize_image(output_file, 4)


def dump_pet_skins():

    logger.log(logging.INFO, "Dumping pet skins...")
    IndentFilter.level += 1

    PET_SKINS_DIR = ROOT_DIR / "../src/other/pet_skins"
    delete_dir_contents(PET_SKINS_DIR)

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
        output_file = PET_SKINS_DIR / file_name

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
