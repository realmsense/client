import shutil
import os
import json
import re as regex
import math
from xml.etree.ElementTree import parse
import requests
from time import sleep
from PIL import Image

from classes import *

def read_json(file_path):
    with open(file_path) as json_file:
        json_data = json.load(json_file)
        return json_data

def read_jsonc(file_path):
    with open(file_path) as json_file:
        lines = json_file.read()
        lines = regex.sub(r"\/\/.*", "", lines)
        lines = regex.sub(r"/\*.*", "", lines)
        json_data = json.loads(lines)
        return json_data

def delete_dir_contents(dir: Path):
    shutil.rmtree(dir, ignore_errors=True)
    sleep(5)
    if not dir.exists():
        os.mkdir(dir)

def parse_int(str):
    if type(str) is int:
        return str
    
    base = 10
    if "0x" in str:
        base = 0
    return int(str, base)


def generate_byte_arr(file_path: Path):
    with open(file_path, "rb") as file:
        data = file.read()
        bytes = [hex(i) for i in data]
        bytes_len = len(bytes)

        bytes_str = str(bytes)
        for char in ["[", "'", "]"]:
            bytes_str = bytes_str.replace(char, "")

        bytes_str = "{ " + bytes_str + " }"

        return (bytes_str, bytes_len)


def strip_non_ascii(string):
    stripped = (c for c in string if 0 < ord(c) < 127)
    return "".join(stripped)


def strip_non_alphabetic(string: str, replacement=""):
    stripped = regex.sub("[^a-zA-Z]", replacement, string)
    return stripped


def number_to_word(number: int, short=False):
    words = None
    if not short:
        words = { 0: "zero", 1: "one", 2: "two", 3: "three", 4: "four", 5: "five", 6: "six", 7: "seven", 8: "eight", 9: "nine" }
    else:
        words = { 0: "a", 1: "b", 2: "c", 3: "d", 4: "e", 5: "f", 6: "g", 7: "h", 8: "i", 9: "j" }

    return words[number]


def download_file(url, output_file: Path):
    if output_file.exists():
        return output_file

    logger.log(logging.INFO, f"Downloading {url}")
    response = requests.get(url)
    output_file.write_bytes(response.content)
    return output_file


def extract_sprite(output_file, spritesheet_json, spritesheet_img, spritesheet_name, sprite_index, scale=33):

    sprite_index = parse_int(sprite_index)
    for sprite in spritesheet_json["sprites"]:
        if sprite["index"] == sprite_index and sprite["spriteSheetName"] == spritesheet_name:
            extract_from_image(output_file, spritesheet_img, sprite["position"], scale)
            return


def extract_animated_sprite(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index, scale=33):

    sprite_index = parse_int(sprite_index)
    found_sprites = []

    for sprite in spritesheet_json["animatedSprites"]:
        if sprite["index"] == sprite_index and sprite["spriteData"]["spriteSheetName"] == sprite_name:
            found_sprites.append(sprite)

    chosen_sprite = None
    for sprite in found_sprites:
        if chosen_sprite == None:
            chosen_sprite = sprite

        if sprite["action"] < chosen_sprite["action"] and sprite["direction"] < chosen_sprite["direction"]:
            chosen_sprite = sprite

    extract_from_image(output_file, spritesheet_img, chosen_sprite["spriteData"]["position"], scale)


def extract_from_image(output_file, spritesheet_img, pos, scale=1):
    left    = pos["x"]
    top     = pos["y"]
    right   = pos["x"] + pos["w"]
    bottom  = pos["y"] + pos["h"]

    with Image.open(spritesheet_img) as img:
        img = img.crop((left, top, right, bottom))
        img.save(output_file)

    
    resize_image(output_file, scale)


def resize_image(image_file, scale):
    with Image.open(image_file) as img:
        width, height = img.size
        scaled_size = width * scale, height * scale
        img = img.resize(scaled_size, Image.NEAREST)
        img.save(image_file)


def resize_repeat_image(image_file, scale):

    with Image.open(image_file) as img:
        new_img = Image.new("RGB", (scale, scale))
        width, height = img.size
        repeat_width = math.ceil(scale / width)
        for x in range(0, scale, width):
            for y in range(0, scale, height):
                new_img.paste(img, (x, y))

        new_img.save(image_file)