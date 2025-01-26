import pygame
import math
from PIL import Image

pygame.init()

WIDTH, HEIGHT = 2000, 1000
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Solar System Simulation")
clock = pygame.time.Clock()

BLACK = (0, 0, 0)
YELLOW = (255, 255, 0)

def remove_background(image_path):
    """Удаляет белый фон из изображения, делая его прозрачным."""
    img = Image.open(image_path).convert("RGBA")
    data = img.getdata()
    new_data = []
    for item in data:
        if item[:3] == (0, 0, 0): 
            new_data.append((255, 255, 255, 0))  
        else:
            new_data.append(item)
    img.putdata(new_data)
    return img

def circle_image(surface, padding=5):
    """Обрезает изображение в форму круга с уменьшением радиуса."""
    size = surface.get_size()
    mask = pygame.Surface(size, pygame.SRCALPHA)

    radius = min(size[0], size[1]) // 2 - padding
    pygame.draw.circle(mask, (255, 255, 255, 255), (size[0] // 2, size[1] // 2), radius)
    
    result = pygame.Surface(size, pygame.SRCALPHA)
    result.blit(surface, (0, 0))
    result.blit(mask, (0, 0), None, pygame.BLEND_RGBA_MIN)
    return result

planet_diameters = {
    "Mercury": 10879,
    "Venus": 12104,
    "Earth": 12742,
    "Mars": 10779,
    "Jupiter": 139820,
    "Saturn": 116460,
    "Uranus": 50724,
    "Neptune": 49244,
}

def scale_planet_image(image, planet_name, zoom_factor):
    """Масштабируем изображение планеты в зависимости от её диаметра и zoom_factor."""
    max_diameter = max(planet_diameters.values())  
    scaling_factor = planet_diameters[planet_name] / max_diameter * zoom_factor
    
    scaled_image = pygame.transform.scale(image, (int(40 * scaling_factor), int(40 * scaling_factor)))
    return scaled_image

planet_images = {
    "Mercury": scale_planet_image(circle_image(pygame.image.fromstring(
        remove_background("images/mercury.png").tobytes(), 
        remove_background("images/mercury.png").size, 
        "RGBA"
    ), padding=8), "Mercury", 1),
    "Venus": scale_planet_image(circle_image(pygame.image.fromstring(
        remove_background("images/venus.png").tobytes(), 
        remove_background("images/venus.png").size, 
        "RGBA"
    ), padding=8), "Venus", 1),
    "Earth": scale_planet_image(circle_image(pygame.image.fromstring(
        remove_background("images/earth.png").tobytes(), 
        remove_background("images/earth.png").size, 
        "RGBA"
    ), padding=8), "Earth", 1),
    "Mars": scale_planet_image(circle_image(pygame.image.fromstring(
        remove_background("images/mars.png").tobytes(), 
        remove_background("images/mars.png").size, 
        "RGBA"
    ), padding=8), "Mars", 1),
    "Jupiter": scale_planet_image(circle_image(pygame.image.fromstring(
        remove_background("images/jupiter.png").tobytes(), 
        remove_background("images/jupiter.png").size, 
        "RGBA"
    ), padding=8), "Jupiter", 1),
    "Saturn": scale_planet_image(circle_image(pygame.image.fromstring(
        remove_background("images/saturn.png").tobytes(), 
        remove_background("images/saturn.png").size, 
        "RGBA"
    ), padding=8), "Saturn", 1),
    "Uranus": scale_planet_image(circle_image(pygame.image.fromstring(
        remove_background("images/uranus.png").tobytes(), 
        remove_background("images/uranus.png").size, 
        "RGBA"
    ), padding=8), "Uranus", 1),
    "Neptune": scale_planet_image(circle_image(pygame.image.fromstring(
        remove_background("images/neptune.png").tobytes(), 
        remove_background("images/neptune.png").size, 
        "RGBA"
    ), padding=8), "Neptune", 1),
}

planets = [
    {"name": "Mercury", "distance": 50, "speed": 0.005, "info": "Mercury: smallest planet."},
    {"name": "Venus", "distance": 80, "speed": 0.0035, "info": "Venus: thick atmosphere."},
    {"name": "Earth", "distance": 110, "speed": 0.003, "info": "Earth: our home."},
    {"name": "Mars", "distance": 150, "speed": 0.0024, "info": "Mars: red planet."},
    {"name": "Jupiter", "distance": 200, "speed": 0.0013, "info": "Jupiter: largest planet."},
    {"name": "Saturn", "distance": 250, "speed": 0.0009, "info": "Saturn: rings system."},
    {"name": "Uranus", "distance": 300, "speed": 0.0007, "info": "Uranus: icy giant."},
    {"name": "Neptune", "distance": 350, "speed": 0.0006, "info": "Neptune: farthest planet."},
]

SUN_X, SUN_Y = WIDTH // 2, HEIGHT // 2

angles = [0 for _ in planets]

font = pygame.font.SysFont("Arial", 18)

zoom_factor = 1.0

def draw_orbit(distance):
    """Рисуем орбиту с учетом масштабирования."""
    pygame.draw.circle(screen, (100, 100, 100), (SUN_X, SUN_Y), distance * zoom_factor, 1)

def display_info(planet):
    """Отображение информации о планете на экране."""
    text_surface = font.render(f"{planet['name']}: {planet['info']}", True, (255, 255, 255))
    screen.blit(text_surface, (10, 10))

running = True
selected_planet = None

while running:
    screen.fill(BLACK)

    pygame.draw.circle(screen, YELLOW, (SUN_X, SUN_Y), 20)

    for i, planet in enumerate(planets):
        draw_orbit(planet["distance"])

        angles[i] += planet["speed"]
        x = SUN_X + planet["distance"] * math.cos(angles[i]) * zoom_factor
        y = SUN_Y + planet["distance"] * math.sin(angles[i]) * zoom_factor

        image = scale_planet_image(planet_images[planet["name"]], planet["name"], zoom_factor)
        screen.blit(image, (x - image.get_width() // 2, y - image.get_height() // 2))

        mouse_x, mouse_y = pygame.mouse.get_pos()
        if pygame.mouse.get_pressed()[0]:
            if math.sqrt((mouse_x - x) ** 2 + (mouse_y - y) ** 2) <= image.get_width() // 2:
                selected_planet = planet

    if selected_planet:
        display_info(selected_planet)

    pygame.display.flip()
    clock.tick(60)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 4:  
                zoom_factor *= 1.1
            elif event.button == 5:
                zoom_factor /= 1.1

pygame.quit()