import re as regex
from classes import *
from functions import *

header_config = read_jsonc(CONFIG_DIR / "il2cpp_header.jsonc")

def do_replace(line: str):
    for replacement in header_config["replacements"]:
        if replacement[0] in line:
            line = line.replace(replacement[0], replacement[1])
    return line

def generate_il2cpp_functions():

    logger.log(logging.INFO, "Extracting IL2CPP functions...")
    IndentFilter.level += 1

    functions_file = download_file(IL2CPP_FUNCTIONS_URL, TEMP_DIR / "il2cpp-functions.h")
    # functions_file = TEMP_DIR / "il2cpp-functions.h"

    api_functions_file = download_file(IL2CPP_API_FUNCTIONS_URL, TEMP_DIR / "il2cpp-api-functions-ptr.h")
    # api_functions_file = TEMP_DIR / "il2cpp-api-functions-ptr.h"

    remaining_functions = []
    logger.log(logging.INFO, "Initialising JSON Data")
    for function in header_config["functions"]:
        remaining_functions.append({
            "original": function["name"][0],
            "replace": function["name"][1],
            "typedef": function["typedef"],
            "methodinfo": False
        })

        if function["methodinfo"]:
            remaining_functions.append({
                "original": function["name"][0] + "__MethodInfo",
                "replace": function["name"][1] + "__MethodInfo",
                "methodinfo": True
            })
    
    logger.log(logging.INFO, "Parsing header")
    with open(functions_file) as file:
        output_lines = []
        for line in file.readlines():
            line = line.replace("\n", "")
            for function in remaining_functions:

                if function["methodinfo"]:
                    if function["original"] in line:
                        line = line.replace(function["original"], function["replace"])
                        output_lines.append(line)
                        remaining_functions.remove(function)
                        break

                if not function["methodinfo"]:
                    pattern = regex.compile(f"({function['original']}(?:_\d)?), " + regex.escape(function["typedef"]))
                    match = regex.search(pattern, line)
                    if match:
                        function_name = match.group(1)
                        line = line.replace(function_name, function["replace"])
                        line = do_replace(line)

                        # fix replaced function name if it was accidentally changed in do_replace
                        line = line.replace(do_replace(function["replace"]), function["replace"])

                        output_lines.append(line)
                        remaining_functions.remove(function)
                        break


        logger.log(logging.INFO, "Outputting")
        output_functions = ROOT_DIR / "../src/il2cpp/appdata/il2cpp-functions.h"
        output_functions.write_text("\n".join(output_lines))

    logger.log(logging.INFO, "Copying api functions ptr")
    with open(api_functions_file) as file:
        output_api_functions = ROOT_DIR / "../src/il2cpp/appdata/il2cpp-api-functions-ptr.h"
        output_api_functions.write_text(file.read())

    if len(remaining_functions) > 0:
        logger.log(logging.ERROR, "Failed to get the following functions:")
        IndentFilter.level += 1

        for function in remaining_functions:
            logger.log(logging.INFO, function)
        IndentFilter.level -= 1

    logger.log(logging.INFO, "Done!")
    IndentFilter.level -= 1


def generate_il2cpp_types():

    logger.log(logging.INFO, "Extracting IL2CPP Types")
    IndentFilter.level += 1

    types_file = download_file(IL2CPP_TYPES_URL, TEMP_DIR / "il2cpp-types.h")
    # types_file = TEMP_DIR / "il2cpp-types.h"

    typedefs_file = download_file(IL2CPP_TYPEDEFS_URL, TEMP_DIR / "il2cpp-types-ptr.h")
    # typedefs_file = TEMP_DIR / "il2cpp-types-ptr.h"

    remaining_structs = []
    remaining_enums = []
    remaining_typedefs = []
    logger.log(logging.INFO, "Initialising JSON Data")
    for il2cpp_class in header_config["structs"]:
        remaining_structs.append({
            "name": il2cpp_class["name"],
            "replacements": [ ]
        })

        for struct_name, replacements in il2cpp_class["props"].items():
            remaining_structs.append({
                "name": il2cpp_class["name"] + struct_name,
                "replacements": replacements
            })

            if struct_name == "__StaticFields":
                remaining_typedefs.append(il2cpp_class["name"])

    for enum in header_config["enums"]:
        remaining_enums.append({
            "original": enum[0] + "__Enum",
            "replace": enum[1]
        })

        header_config["replacements"].append([enum[0] + "__Enum", enum[1]])

    
    logger.log(logging.INFO, "Parsing types header...")
    IndentFilter.level += 1
    with open(types_file) as file:

        current_struct = None
        in_struct = False

        in_enum = False

        in_internal_types = True
        internal_lines = []

        output_lines = []
        output_lines.append('#include "il2cpp-internal-types.h"\n')
        # output_lines.append("namespace app {\n")

        for line in file.readlines():
            line = line.replace("\n", "")

            # Exit internal lines
            # if in_internal_types and line.startswith("// * Application types from method calls"):
            if in_internal_types and line.startswith("#pragma warning(disable : 4369)"):
                in_internal_types = False
                continue

            if in_internal_types:
                internal_lines.append(line)
                continue

            # Enter struct
            found_struct = False
            if not in_struct and line.startswith("struct") and line.endswith("{"):
                for struct in remaining_structs:
                    search_line = line.replace("__declspec(align(8)) ", "")
                    search = "struct " + struct["name"] + " {"
                    if search in search_line:
                        found_struct = True
                        in_struct = True
                        current_struct = struct
                        output_lines.append(do_replace(line))
                        remaining_structs.remove(struct)
                        break
            if found_struct: continue

            # Exit struct
            if in_struct and line == "};":
                in_struct = False
                current_struct = None
                output_lines.append(line)
                output_lines.append("")
                continue

            # Handle struct
            if in_struct:
                for replacement in current_struct["replacements"]:
                    if replacement[0] in line:
                        line = line.replace(replacement[0], replacement[1])
                        current_struct["replacements"].remove(replacement)
                
                output_lines.append(do_replace(line))
                continue

            # Enter enum
            found_enum = False
            if not in_enum and line.startswith("enum class"):
                for enum in remaining_enums:
                    search = "enum class " + enum["original"]
                    if search in line:
                        in_enum = True
                        found_enum = True
                        line = line.replace(enum["original"], enum["replace"])
                        output_lines.append(do_replace(line))
                        remaining_enums.remove(enum)
                        break
            if found_enum: continue

            # Exit enum
            if in_enum and line == "};":
                in_enum = False
                output_lines.append(line)
                output_lines.append("")

            # Handle enum
            if in_enum:
                output_lines.append(line)
                continue

        # output_lines.append("} // end namespace app")

        logger.log(logging.INFO, "Outputting")
        output_internal_types = ROOT_DIR / "../src/il2cpp/appdata/il2cpp-internal-types.h"
        output_internal_types.write_text("\n".join(internal_lines))

        output_types = ROOT_DIR / "../src/il2cpp/appdata/il2cpp-types.h"
        output_types.write_text("\n".join(output_lines))
        logger.log(logging.INFO, "Done!")
        IndentFilter.level -= 1

    logger.log(logging.INFO, "Parsing typedefs header...")
    IndentFilter.level += 1
    with open(typedefs_file) as file:
        output_lines = []
        for line in file.readlines():
            if len(remaining_typedefs) <= 0: break
            line = line.replace("\n", "")
            for typedef in remaining_typedefs:
                search = ", " + typedef + ");"
                if search in line:
                    line = do_replace(line)
                    output_lines.append(line)
                    remaining_typedefs.remove(typedef)
                    break

    output_typedefs = ROOT_DIR / "../src/il2cpp/appdata/il2cpp-types-ptr.h"
    output_typedefs.write_text("\n".join(output_lines))
    logger.log(logging.INFO, "Done!")
    IndentFilter.level -= 1

    if len(remaining_structs) > 0:
        logger.log(logging.ERROR, "Failed to get the following structs:")
        IndentFilter.level += 1

        for struct in remaining_structs:
            logger.log(logging.INFO, struct["name"])
        IndentFilter.level -= 1

    if len(remaining_enums) > 0:
        logger.log(logging.ERROR, "Failed to get the following enums:")
        IndentFilter.level += 1

        for enum in remaining_enums:
            logger.log(logging.INFO, enum["original"])
        IndentFilter.level -= 1

    if len(remaining_typedefs) > 0:
        logger.log(logging.ERROR, "Failed to get the following typedefs:")
        IndentFilter.level += 1

        for typedef in remaining_structs:
            logger.log(logging.INFO, typedef)
        IndentFilter.level -= 1
