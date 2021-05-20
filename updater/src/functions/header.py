from classes import *
from functions import *

header_config = read_json(CONFIG_DIR / "il2cpp_header.json")

def generate_il2cpp_header():
    generate_il2cpp_types()
    generate_il2cpp_functions()

def generate_il2cpp_functions():

    logger.log(logging.INFO, "Generating IL2CPP functions header...")
    IndentFilter.level += 1

    functions = header_config["functions"]
    functions_file = download_file(IL2CPP_FUNCTIONS_URL, TEMP_DIR / "il2cpp-functions.h")

    logger.log(logging.INFO, "Parsing header...")
    lines = []
    with open(functions_file) as file:
        for line in file.readlines():
            line = line.replace("\n", "")
            for function in functions:
                search = f", {function},"
                if search in line:
                    lines.append(line)
                    functions.remove(function)

    logger.log(logging.INFO, "Outputting...")
    output_functions = ROOT_DIR / "../src/il2cpp/appdata/il2cpp-functions.h"
    output_functions.write_text("\n".join(lines))

    logger.log(logging.INFO, "Done!")
    IndentFilter.level -= 1


def generate_il2cpp_types():

    logger.log(logging.INFO, "Generating IL2CPP types header...")
    IndentFilter.level += 1
    
    structs = []
    dependencies = []
    current_struct = ""

    structs = header_config["structs"]
    dependencies = header_config["dependencies"]

    types_file = download_file(IL2CPP_TYPES_URL, TEMP_DIR / "il2cpp-types.h")

    new_structs = [] 
    for struct in structs:
        for dependency in dependencies:
            new_structs.append(struct + dependency)
    structs += new_structs

    lines = []

    logger.log(logging.INFO, "Parsing header...")
    in_il2cpp = False
    in_struct = False
    with open(types_file) as file:
        for line in file.readlines():
            line = line.replace("\n", "")

            # Enter il2cpp lines
            if "// * IL2CPP internal types" in line:
                in_il2cpp = True

            # Exit il2cpp lines
            if in_il2cpp and "// * Application types from method calls" in line:
                in_il2cpp = False

            if in_il2cpp:
                lines.append(line)

            # Enter struct lines
            for struct in structs:
                search = "struct " + struct + " {"
                search2 = "struct __declspec(align(8)) " + struct + " {" # using regex is too slow lol
                if search in line or search2 in line:
                    if in_struct:
                        print(f"ERROR! {current_struct} did not end!")
                        return
                    
                    in_struct = True
                    current_struct = struct
                    structs.remove(struct)
                    break

            # Append lines to current struct
            if in_struct:
                lines.append(line)
                # find_struct_dependencies(line)

            # End current struct
            if "};" in line and in_struct:
                in_struct = False
                lines.append("")

    logger.log(logging.INFO, "Outputting...")
    output_types = ROOT_DIR / "../src/il2cpp/appdata/il2cpp-types.h"
    output_types.write_text("")
    with open(output_types, mode="a") as output_file:
        output_file.write("\n".join(lines))
        output_file.write("} // end namespace app")

    logger.log(logging.INFO, "Done!")
    IndentFilter.level -= 1