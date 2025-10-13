import pygame

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
        "2": pygame.image.load("assets/pieces/wP.png"),
        "4": pygame.image.load("assets/pieces/wR.png"),
        "6": pygame.image.load("assets/pieces/wN.png"),
        "8": pygame.image.load("assets/pieces/wB.png"),
        "10": pygame.image.load("assets/pieces/wQ.png"),
        "12": pygame.image.load("assets/pieces/wK.png"),

        "3": pygame.image.load("assets/pieces/bP.png"),
        "5": pygame.image.load("assets/pieces/bR.png"),
        "7": pygame.image.load("assets/pieces/bN.png"),
        "9": pygame.image.load("assets/pieces/bB.png"),
        "11": pygame.image.load("assets/pieces/bQ.png"),
        "13": pygame.image.load("assets/pieces/bK.png"),
    }

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Load and parse the board file
        with open("../../board.txt", "r") as f:
            content = [line.strip().split() for line in f.readlines()]

        screen.fill(backgroundcolor)

        # Draw the board and pieces
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

        pygame.display.flip()

    pygame.quit()
