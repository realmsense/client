from classes import *
from functions import *

def main():

    delete_dir_contents(OUTPUT_DIR)
    delete_dir_contents(TEMP_DIR)

    logger.setup()

    # dump_offsets()
    # dump_player_skins()
    generate_il2cpp_header()


if __name__ == "__main__":
    main()