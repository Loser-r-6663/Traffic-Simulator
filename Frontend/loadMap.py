import json
from pathlib import Path

script_dir = Path(__file__).resolve().parent
possible_paths = [
    script_dir / 'map_config.json',
    script_dir.parent / 'map_config.json',
    script_dir.parent / 'data' / 'map_config.json',
    script_dir.parent.parent / 'data' / 'map_config.json',
]

template_path = None
for path in possible_paths:
    if path.is_file():
        template_path = path
        break

if template_path is None:
    raise FileNotFoundError(
        'Could not find templates.json. Checked: ' + ', '.join(str(p) for p in possible_paths)
    )

with open(template_path, 'r', encoding='utf-8') as f:
    data = json.load(f)

intersections = data.get('intersections', [])
roads = data.get('roads', [])


def getIntersections():
    return intersections

def getRoads():
    return roads
