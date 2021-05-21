import shutil
import os
import json
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