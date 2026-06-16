import pygame

VEHICLE_COLORS = {
    1: (255, 0, 0),
    2: (0, 200, 0),
    3: (255, 165, 0)
}


def build_intersection_map(intersections):
    return {intersection['id']: intersection for intersection in intersections}


def render_intersetion(intersections, screen):
    for intersection in intersections:
        pygame.draw.circle(screen, (0, 0, 255), (int(intersection['x']), int(intersection['y'])), 6)


def render_road(roads, intersections, screen):
    intersection_map = build_intersection_map(intersections)
    for road in roads:
        start_node = road.get('start_node') or road.get('startNode') or road.get('start')
        end_node = road.get('end_node') or road.get('endNode') or road.get('end')
        intr1 = intersection_map.get(start_node)
        intr2 = intersection_map.get(end_node)
        if intr1 is None or intr2 is None:
            continue
        pygame.draw.line(screen, (0, 0, 0), (int(intr1['x']), int(intr1['y'])), (int(intr2['x']), int(intr2['y'])), 4)


def render_vehicle(vehicle, screen):
    x = int(vehicle.get('x', 0))
    y = int(vehicle.get('y', 0))
    type_id = vehicle.get('typeId', vehicle.get('type_id', 0))
    color = VEHICLE_COLORS.get(type_id, (128, 128, 128))
    size = 10
    rect = pygame.Rect(x - size // 2, y - size // 2, size, size)
    pygame.draw.rect(screen, color, rect)


def render_vehicles(vehicles, screen):
    for vehicle in vehicles:
        render_vehicle(vehicle, screen)