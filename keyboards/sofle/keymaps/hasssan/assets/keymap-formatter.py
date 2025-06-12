#!/usr/bin/env -S uv run --script

# /// script
# requires-python = ">=3.10"
# dependencies = [
#     "pyyaml",
# ]
# ///

import yaml
import argparse
import shutil


class FlowStyleSafeDumper(yaml.SafeDumper):
    pass

class QuotedString(str): pass

def represent_quoted_str(dumper, value):
    return dumper.represent_scalar("tag:yaml.org,2002:str", value, style='"')

FlowStyleSafeDumper.add_representer(QuotedString, represent_quoted_str)

class FlowList(list): pass

def represent_flow_list(dumper, value):
    return dumper.represent_sequence('tag:yaml.org,2002:seq', value, flow_style=True)


FlowStyleSafeDumper.add_representer(FlowList, represent_flow_list)

def patch_layers_for_flow_style(layers):
    for _, layer_data in layers.items():
        for i, row in enumerate(layer_data):
            if isinstance(row, list):
                layer_data[i] = FlowList([QuotedString(str(v)) if isinstance(v, str) else v for v in row])


class FlowDict(dict): pass

def represent_flow_dict(dumper, value):
    return dumper.represent_mapping('tag:yaml.org,2002:map', value, flow_style=True)

FlowStyleSafeDumper.add_representer(FlowDict, represent_flow_dict)


def patch_combos_for_flow_style(combos):
    for i, combo in enumerate(combos):
        quoted = {
            k: (
                [QuotedString(str(vv)) if isinstance(vv, str) else vv for vv in v]
                if isinstance(v, list)
                else QuotedString(str(v)) if isinstance(v, str) else v
            )
            for k, v in combo.items()
        }
        combos[i] = FlowDict(quoted)


def read_keymap(file_path):
    try:
        with open(file_path, "r", encoding="utf-8") as file:
            keymap = yaml.safe_load(file)
        return keymap
    except FileNotFoundError:
        print(f"Error: The file {file_path} was not found.")
        return None
    except yaml.YAMLError as e:
        print(f"Error: Failed to parse YAML file {file_path}. {e}")
        return None


def flat_to_rows(flat_layout):
    """Convert a flat layout to row-based format.

    Row distribution:
    1. 12 keys
    2. 12 keys
    3. 12 keys
    4. 14 keys
    5. 10 keys
    """
    row_distribution = [12, 12, 12, 14, 10]
    total_keys = sum(row_distribution)

    # Check if we have enough keys
    if len(flat_layout) < total_keys:
        # Pad with empty keys if needed
        flat_layout.extend(
            [{"t": "▽", "type": "trans"}] * (total_keys - len(flat_layout))
        )
    elif len(flat_layout) > total_keys:
        print(
            f"Warning: Flat layout has {len(flat_layout)} keys, but expected {total_keys}. Truncating extra keys."
        )

    # Convert to rows
    rows = []
    start_idx = 0
    for row_size in row_distribution:
        rows.append(flat_layout[start_idx : start_idx + row_size])
        start_idx += row_size

    return rows


def process_layers(layers):
    """Process the layers data from the keymap and return as a map."""
    processed_layers = {}

    for layer_name, layer_data in layers.items():
        # Determine if this is a flat layout that needs conversion
        is_flat = not isinstance(layer_data, list) or (
            isinstance(layer_data, list)
            and len(layer_data) > 0
            and not isinstance(layer_data[0], list)
        )

        if is_flat:
            if not isinstance(layer_data, list):
                # If it's not even a list, convert to a list first
                flat_list = [layer_data]
            else:
                flat_list = layer_data

            processed_layers[layer_name] = flat_to_rows(flat_list)
        else:
            # Already in rows format
            processed_layers[layer_name] = layer_data

    return processed_layers


def backup_file(file_path):
    """Create a backup of the file with .bak suffix."""
    backup_path = file_path + ".bak"
    try:
        shutil.copy2(file_path, backup_path)
        print(f"Created backup at {backup_path}")
        return True
    except Exception as e:
        print(f"Error creating backup: {e}")
        return False


def write_keymap(file_path, keymap_data, processed_layers):
    """Write the processed layers back to the keymap file."""
    # Update the layers in the keymap data
    keymap_data["layers"] = processed_layers

    try:
        with open(file_path, "w", encoding="utf-8") as file:
            yaml.dump(
                keymap_data,
                file,
                Dumper=FlowStyleSafeDumper,
                default_flow_style=False,
                sort_keys=False,
                allow_unicode=True,
                indent=4,
                width=float("inf"),
            )
        print(f"Successfully wrote processed layers to {file_path}")
        return True
    except Exception as e:
        print(f"Error writing to file {file_path}: {e}")
        return False


def main():
    parser = argparse.ArgumentParser(description="Process a keyboard keymap YAML file.")
    parser.add_argument("filepath", help="Path to the YAML keymap file")

    args = parser.parse_args()
    keymap_path = args.filepath

    # Read the keymap
    keymap = read_keymap(keymap_path)

    if keymap and "layers" in keymap:
        # Create a backup of the original file
        if backup_file(keymap_path):
            # Process the layers
            processed_layers = process_layers(keymap["layers"])

            print(
                f"Successfully processed {len(processed_layers)} layers from {keymap_path}"
            )

            # Patch each row of each layer for flow-style lists
            patch_layers_for_flow_style(processed_layers)

            if "combos" in keymap:
                # Patch combos for flow-style dictionaries
                patch_combos_for_flow_style(keymap["combos"])

            # Write the processed layers back to the file
            write_keymap(keymap_path, keymap, processed_layers)
        else:
            print("Backup failed, aborting to avoid data loss.")
    elif keymap:
        print("No 'layers' section found in the keymap file.")
        print(f"Available sections: {', '.join(keymap.keys())}")
    else:
        print("Failed to read keymap data.")


if __name__ == "__main__":
    main()
