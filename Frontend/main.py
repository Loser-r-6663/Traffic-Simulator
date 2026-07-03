import loadMap
import loadTemplate
import render
import pygame
import socket
import struct

# Khởi tạo kết nối Socket tới Server C++
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ("localhost", 8080)
client_socket.connect(server_address)
print("Da ket noi server c++ thanh cong")

# Khởi tạo Pygame
pygame.init()
screen = pygame.display.set_mode((800, 600))
clock = pygame.time.Clock()

# Tải dữ liệu bản đồ và template
intersections = loadMap.getIntersections()
roads = loadMap.getRoads()
vehicles = loadTemplate.getVehiclesTemplate()

def recv_all(sock, length):
    
    data = b''
    while len(data) < length:
        more_data = sock.recv(length - len(data))
        if not more_data:
            return None 
        data += more_data
    return data

running = True
while running:
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    client_socket.send(b'1')
    
    header_bytes = recv_all(client_socket, 4)
    if not header_bytes:
        print("Server đã ngắt kết nối.")
        break
    payload_size = struct.unpack('<i', header_bytes)[0]
    
    
    count_bytes = recv_all(client_socket, 4)
    if not count_bytes:
        break
    update_count = struct.unpack('<i', count_bytes)[0]
    
    
    payload = recv_all(client_socket, payload_size)
    if not payload:
        break
    
    
    world_objects = []
    vehicle_struct_size = 12 # sizeof(vehiclePacked) = 4 (int) + 4 (float) + 4 (float)
    
    for i in range(0, payload_size, vehicle_struct_size):
        
        vehicle_bytes = payload[i:i + vehicle_struct_size]
        
        # Định dạng '<iff': Little-endian, 1 int, 2 float
        type_id, x, y = struct.unpack('<iff', vehicle_bytes)
        
        
        world_objects.append({
            "typeId": type_id,
            "x": x,
            "y": y
        })
    
    
    screen.fill((255,255,255)) 
    for intersection in intersections:
        render.render_intersetion(intersections, screen)
    for road in roads:
        render.render_road(roads, intersections, screen)
    for vehicle in world_objects:
        render.render_vehicle(vehicle, screen)
    
    pygame.display.flip()
    clock.tick(60) #60 fps
pygame.quit()
client_socket.close()