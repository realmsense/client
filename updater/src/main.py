import sys
from classes import *
from functions import *

def parse_args():
    global CURRENT_CLIENT_URL
    if len(sys.argv) > 1:
        CURRENT_CLIENT_URL =  sys.argv[1]

def main():

    parse_args()

    # delete_dir_contents(OUTPUT_DIR)
    # delete_dir_contents(TEMP_DIR)

    logger.setup()

    # dump_player_skins()
    # dump_player_textiles()
    # dump_pet_skins()
    generate_il2cpp_types()
    generate_il2cpp_functions()


if __name__ == "__main__":
    main()