import os
import pygame

def load_image_with_alpha(filename):
    # Initialize Pygame display
    pygame.init()
    screen = pygame.display.set_mode((640, 480))

    # Load the image
    loaded_image = pygame.image.load(os.path.join("/home/islem/mes_etudes/Tales-from-the-future", filename)).convert()

    # Set the alpha channel
    colorkey = (255, 0, 255)
    loaded_image.set_colorkey(colorkey)

    # Convert the surface to the screen's format
    surface = pygame.Surface((loaded_image.get_width(), loaded_image.get_height()), pygame.SRCALPHA)
    surface.blit(loaded_image, (0, 0))
    surface = pygame.display.get_surface()
    surface = surface.convert_alpha()
    pygame.display.quit()

    return surface

# Load the heart images with alpha
full_heart = load_image_with_alpha("heart1.png")
half_heart = load_image_with_alpha("heart2.png")
empty_heart = load_image_with_alpha("heart3.png")
