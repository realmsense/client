from classes import *
from functions import *

def main():

    delete_dir_contents(OUTPUT_DIR)
    delete_dir_contents(TEMP_DIR)

    logger.setup()

    dump_player_skins()
    dump_pet_skins()
    dump_player_outfits()
    dump_player_outfits()
    generate_il2cpp_types()
    generate_il2cpp_functions()


if __name__ == "__main__":
    main()