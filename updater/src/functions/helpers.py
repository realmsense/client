import shutil
import os
import json
from xml.etree.ElementTree import parse
import requests
from time import sleep
from PIL import Image

from classes import *

def read_json(file_path):
    with open(file_path) as json_file:
        json_data = json.load(json_file)
        return json_data


def delete_dir_contents(dir: Path):
    shutil.rmtree(dir, ignore_errors=True)
    sleep(5)
    os.mkdir(dir)

def parse_int(str):
    base = 10
    if "0x" in str:
        base = 0
    return int(str, base)


def download_file(url, output_file: Path):
    logger.log(logging.INFO, f"Downloading {url}")
    response = requests.get(url)
    output_file.write_bytes(response.content)
    return output_file


def extract_animated_sprite(output_file, spritesheet_json, spritesheet_img, sprite_name, sprite_index):

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

    extract_from_spritesheet(output_file, spritesheet_img, chosen_sprite["spriteData"]["position"], 33)


def extract_from_spritesheet(output_file, spritesheet_img, pos, scale=1):
    left    = pos["x"]
    top     = pos["y"]
    right   = pos["x"] + pos["w"]
    bottom  = pos["y"] + pos["h"]

    scaled_size = pos["w"] * scale, pos["h"] * scale

    with Image.open(spritesheet_img) as img:
        img = img.crop((left, top, right, bottom))
        img = img.resize(scaled_size, Image.NEAREST)
        img.save(output_file)