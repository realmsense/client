import xml.etree.ElementTree as ET
import threading
import re as regex
from typing import TypedDict

from classes import *
from functions.helpers import delete_dir_contents, download_file, extract_animated_sprite, extract_from_image, generate_byte_arr, number_to_word, parse_int, read_json, resize_image, resize_repeat_image, strip_non_alphabetic

class Skin(TypedDict):
    name: str
    file: Path
    variable_name: str
    category: str
    category2: str
    skin_id: int


def dump_player_skins():

    logger.log(logging.INFO, "Dumping player skins...")
    IndentFilter.level += 1

    spritesheet_file = download_file(SPRITESHEET_URL, TEMP_DIR / "spritesheet.json")
    spritesheet_img = download_file(CHARACTERS_IMG_URL, TEMP_DIR / "characters.png")
    skins_xml = download_file(SKINS_XML_URL, TEMP_DIR / "skins.xml")
    spritesheet_json = read_json(spritesheet_file)

    PLAYER_SKINS_DIR = TEMP_DIR / "player_skins"
    delete_dir_contents(PLAYER_SKINS_DIR)

    skins: list[Skin] = []
    threads: list[threading.Thread] = []

    logger.log(logging.INFO, "Parsing xml")
    tree = ET.parse(skins_xml)
    for object in tree.getroot():
        name = object.get("id")
        type = parse_int(object.get("type"))
        class_id = parse_int(object.find("PlayerClassType").text)
        sprite_name = object.find("AnimatedTexture/File").text
        sprite_index = object.find("AnimatedTexture/Index").text

        variable_name = strip_non_alphabetic(name).lower()
        file_name = variable_name + ".png"
        output_file = PLAYER_SKINS_DIR / file_name

        class_name = CLASS_LIST[class_id]

        skin: Skin = {
            "name": name,
            "file": output_file,
            "category": class_name,
            "variable_name": variable_name,
            "skin_id": type
        }

        skins.append(skin)

        thread = threading.Thread(target=extract_animated_sprite, args=(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index))
        threads.append(thread)

    logger.log(logging.INFO, f"Dumping {len(threads)} png files")
    for thread in threads: # start all threads
        thread.start()
    for thread in threads: # wait for all threads to complete
        thread.join()

    logger.log(logging.INFO, "Generating header")
    bytes_lines = []
    init_lines = []
    for skin in skins:
        bytes_str, bytes_len = generate_byte_arr(skin["file"])

        bytes_line = f"unsigned char {skin['variable_name']}[] = {bytes_str};"
        if not bytes_line in bytes_lines:
            bytes_lines.append(bytes_line)
            
        init_lines.append(f'player_skins[ClassList::{skin["category"]}].push_back(new Skin("{skin["name"]}", {skin["variable_name"]}, {bytes_len}, {skin["skin_id"]}));')

    logger.log(logging.INFO, "Writing to player_skins_init.h...")
    init_h = ROOT_DIR / "../src/other/skins/player_skins_init.h"
    init_h.write_text("\n".join(init_lines))

    logger.log(logging.INFO, "Writing to player_skins_bytes.h...")
    bytes_h = ROOT_DIR / "../src/other/skins/player_skins_bytes.h"
    bytes_h.write_text("\n".join(bytes_lines))

    logger.log(logging.INFO, "Done")
    IndentFilter.level -= 1


def dump_player_textiles():

    # For textiles:
    # The same sprite is applied to multiple things,( player skin, small/large textile frames, etc) so it makes sense there isn't duplicate images for each of these things.
    # The Tex attribute is formatted like so: 0x9000001
    # Where 9 is the width of the sprite, and 1 is the index in the spritesheet.
    # So we must first parse textiles.xml to get a list of all textiles with their name + tex attribute
    # Then, we can iterate the textile spritesheets and create the Tex (sprite[width] + sprite[index]) to match the xml -> sprite

    # For dyes:
    # There's no sprite, because dyes are just a solid color
    # Tex: 0x01F0F8FF 
    # 0x01 + F0F8FF= #f0f8ff
    # no use extracting these, we can /probably/ just set the player's color to anything using a color picker

    logger.log(logging.INFO, "Dumping player textiles...")
    IndentFilter.level += 1

    PLAYER_TEXTILES_DIR = TEMP_DIR / "player_textiles"
    delete_dir_contents(PLAYER_TEXTILES_DIR)

    spritesheet_file = download_file(SPRITESHEET_URL, TEMP_DIR / "spritesheet.json")
    spritesheet_img = download_file(MAPOBJECTS_IMG_URL, TEMP_DIR / "mapObjects.png")
    textiles_xml = download_file(TEXTILES_XML_URL, TEMP_DIR / "textiles.xml")
    spritesheet_json = read_json(spritesheet_file)

    textiles: list[Skin] = []
    for object in ET.parse(textiles_xml).getroot():
        name = object.get("id")
        tex1 = object.find("Tex1")
        tex2 = object.find("Tex2")

        tex = ""
        if tex1 is not None:
            tex = tex1.text
        else:
            tex = tex2.text

        variable_name = ""
        for char in str(parse_int(tex)):
            variable_name += number_to_word(int(char), True)

        file_name = variable_name + ".png"
        output_file = PLAYER_TEXTILES_DIR / file_name

        textile: Skin = {
            "name": name,
            "file": output_file,
            # "category": "", # could do large/small, would allow us to change sizing in imgui 
            "variable_name": variable_name,
            "skin_id": tex
        }
        textiles.append(textile)

    threads: list[threading.Thread] = []
    for sprite in spritesheet_json["sprites"]:
        if not sprite["spriteSheetName"].startswith("textile"):
            continue

        pos = sprite["position"]
        spritesheet_name = sprite["spriteSheetName"]
        
        # build the Tex attribute, see top comment
        width = regex.search("textile(\d+)x", spritesheet_name).group(1)
        tex = hex(int(width))
        tex = tex.ljust(9, "0")     # 0x9000000
        tex = int(tex, 0)
        tex += sprite["index"]      # add index
        tex = hex(tex)              # convert back to hex string, 0x9000001

        exists = any(x for x in textiles if x["skin_id"] == tex)
        if not exists:
            continue

        variable_name = ""
        for char in str(parse_int(tex)):
            variable_name += number_to_word(int(char), True)

        file_name = variable_name + ".png"
        output_file = PLAYER_TEXTILES_DIR / file_name
        thread = threading.Thread(target=extract_textile_thread, args=(spritesheet_img, output_file, pos))
        threads.append(thread)

    logger.log(logging.INFO, f"Dumping {len(threads)} png files")
    for thread in threads: # start all threads
        thread.start()
    for thread in threads: # wait for all threads to complete
        thread.join()

    logger.log(logging.INFO, "Generating header")
    bytes_lines = []
    init_lines = []
    for textile in textiles:
        bytes_str, bytes_len = generate_byte_arr(textile["file"])

        bytes_line = f"unsigned char {textile['variable_name']}[] = {bytes_str};"
        if not bytes_line in bytes_lines:
            bytes_lines.append(f"unsigned char {textile['variable_name']}[] = {bytes_str};")

        init_lines.append(f'player_textiles.push_back(new Skin("{textile["name"]}", {textile["variable_name"]}, {bytes_len}, {textile["skin_id"]}));')

    logger.log(logging.INFO, "Writing to player_textiles_init.h...")
    init_h = ROOT_DIR / "../src/other/skins/player_textiles_init.h"
    init_h.write_text("\n".join(init_lines))

    logger.log(logging.INFO, "Writing to player_textiles_bytes.h...")
    bytes_h = ROOT_DIR / "../src/other/skins/player_textiles_bytes.h"
    bytes_h.write_text("\n".join(bytes_lines))

    logger.log(logging.INFO, "Done")
    IndentFilter.level -= 1


def extract_textile_thread(spritesheet_img, output_file, pos):
    extract_from_image(output_file, spritesheet_img, pos)
    resize_repeat_image(output_file, pos["w"] * 4)
    resize_image(output_file, 4)


def dump_pet_skins():

    logger.log(logging.INFO, "Dumping pet skins...")
    IndentFilter.level += 1

    PET_SKINS_DIR = TEMP_DIR / "pet_skins"
    delete_dir_contents(PET_SKINS_DIR)

    spritesheet_file = download_file(SPRITESHEET_URL, TEMP_DIR / "spritesheet.json")
    spritesheet_img = download_file(CHARACTERS_IMG_URL, TEMP_DIR / "characters.png")
    pets_xml = download_file(PETS_XML_URL, TEMP_DIR / "pets.xml")
    spritesheet_json = read_json(spritesheet_file)

    skins: list[Skin] = []
    threads: list[threading.Thread] = []

    logger.log(logging.INFO, "Parsing xml")
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

        variable_name = strip_non_alphabetic(name).lower()
        file_name = variable_name + ".png"
        output_file = PET_SKINS_DIR / file_name

        thread = threading.Thread(target=extract_animated_sprite, args=(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index, 33))
        threads.append(thread)

        skin: Skin = {
            "name": name,
            "file": output_file,
            "category": family,
            "category2": rarity,
            "variable_name": variable_name,
            "skin_id": type
        }

        skins.append(skin)

    logger.log(logging.INFO, f"Dumping {len(threads)} png files")
    for thread in threads: # start all threads
        thread.start()
    for thread in threads: # wait for all threads to complete
        thread.join()

    logger.log(logging.INFO, "Generating header")
    bytes_lines = []
    init_lines = []
    for skin in skins:
        bytes_str, bytes_len = generate_byte_arr(skin["file"])

        bytes_line = f"unsigned char {skin['variable_name']}[] = {bytes_str};"
        if not bytes_line in bytes_lines:
            bytes_lines.append(bytes_line)

        init_lines.append(f'pet_skins[PetFamily::{skin["category"]}][PetRarity::{skin["category2"]}].push_back(new Skin("{skin["name"]}", {skin["variable_name"]}, {bytes_len}, {skin["skin_id"]}));')

    logger.log(logging.INFO, "Writing to pet_skins_init.h...")
    init_h = ROOT_DIR / "../src/other/skins/pet_skins_init.h"
    init_h.write_text("\n".join(init_lines))

    logger.log(logging.INFO, "Writing to pet_skins_bytes.h...")
    bytes_h = ROOT_DIR / "../src/other/skins/pet_skins_bytes.h"
    bytes_h.write_text("\n".join(bytes_lines))

    logger.log(logging.INFO, "Done")
    IndentFilter.level -= 1
