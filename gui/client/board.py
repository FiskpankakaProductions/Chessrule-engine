import pygame

import os

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

def load_image(path):
    return pygame.image.load(os.path.join(BASE_DIR, path))

def load_board():
    path = os.path.join(BASE_DIR, "../../board.txt")
    path = os.path.normpath(path)  # cleans up ../

    with open(path, "r") as f:
        content = [line.strip().split() for line in f.readlines()]

    content.reverse()
    return content

def send_move(start, end):

    files = "abcdefgh"

    start_file = files[start[1]]
    end_file   = files[end[1]]

    start_rank = 8 - start[0]
    end_rank   = 8 - end[0]

    start_square = f"{start_file}{start_rank}"
    end_square = f"{end_file}{end_rank}"

    print(f"Move: {start_square} -> {end_square}")

    return start_square + end_square


def board():
    pygame.init()

    screenWidth, screenHeight = 900, 900
    screen = pygame.display.set_mode((screenWidth, screenHeight))
    pygame.display.set_caption("Chess")

    backgroundcolor = (115, 115, 115)
    light_square = (240, 217, 181)
    dark_square = (181, 136, 99)

    rows, cols = 8, 8
    square_size = screenWidth // cols

    pice_asset = {
        "2": load_image("assets/pieces/wP.png"),
        "4": load_image("assets/pieces/wN.png"),
        "6": load_image("assets/pieces/wB.png"),
        "8": load_image("assets/pieces/wR.png"),
        "10": load_image("assets/pieces/wQ.png"),
        "12": load_image("assets/pieces/wK.png"),

        "3": load_image("assets/pieces/bP.png"),
        "5": load_image("assets/pieces/bN.png"),
        "7": load_image("assets/pieces/bB.png"),
        "9": load_image("assets/pieces/bR.png"),
        "11": load_image("assets/pieces/bQ.png"),
        "13": load_image("assets/pieces/bK.png"),
    }
    selected = ""
    end = ""

    running = True
    while running:

        content = load_board()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            if event.type == pygame.MOUSEBUTTONDOWN:
                x, y = pygame.mouse.get_pos()
                col = x // square_size
                row = y // square_size
                  
                if selected != "":
                    end = row, col

                    send_move(selected, end) 
                    selected = ""
                    end = ""
                elif content[row][col] != "0":
                    selected = row, col
                
        screen.fill(backgroundcolor)

        for row in range(rows):
            for col in range(cols):
                color = light_square if (row + col) % 2 == 0 else dark_square
                pygame.draw.rect(screen, color, (col * square_size, row * square_size, square_size, square_size))

                piece_code = content[row][col]
                if piece_code != "0":
                    piece_img = pice_asset.get(piece_code)
                    if piece_img:
                        piece_img = pygame.transform.scale(piece_img, (square_size, square_size))
                        screen.blit(piece_img, (col * square_size, row * square_size))

        if selected != "":
            row, col = selected
            pygame.draw.rect(screen, (255, 0, 0), (col * square_size, row * square_size, square_size, square_size), 3)

        pygame.display.flip()

    pygame.quit()
