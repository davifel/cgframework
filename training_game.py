import pygame
from time import time, sleep
from random import choice
pygame.init()

keys = {'W': pygame.K_w, 'A': pygame.K_a, 'S': pygame.K_s, 'D': pygame.K_d}
times = []

infoObj = pygame.display.Info()
display_surface = pygame.display.set_mode((infoObj.current_w, infoObj.current_h))
 
pygame.display.set_caption('Calibração')
font = pygame.font.Font('freesansbold.ttf', 250)
font1 = pygame.font.Font('freesansbold.ttf', 50)
font2 = pygame.font.Font('freesansbold.ttf', 15)
display_surface.fill((255,255,255))
mistakes = 0
hits = 0
limiter = time()
inMenu = True

while (inMenu):
    text = font1.render("Aperte a tecla \"Espaço\" para iniciar:", True, (0,0,0))
    textRect = text.get_rect()
    textRect.center = (infoObj.current_w // 2, infoObj.current_h // 2)
    display_surface.blit(text, textRect)
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == pygame.KEYUP and event.key == pygame.K_ESCAPE):
            pygame.quit()
            quit()
        elif (event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE):
            for n in ["3","2","1"]:
                display_surface.fill((255,255,255))
                text = font.render(n, True, (0,0,0))
                textRect = text.get_rect()
                textRect.center = (infoObj.current_w // 2, infoObj.current_h // 2)
                display_surface.blit(text, textRect)
                pygame.display.update()
                sleep(1)
                inMenu = False
            break
        pygame.display.update()

key = choice(list(keys.keys()))
text = font.render(key, True, (0,0,0))
textRect = text.get_rect()
textRect.center = (infoObj.current_w // 2, infoObj.current_h // 2)
display_surface.blit(text, textRect)
startTime = time()
 
while (1):
    text = font.render(key, True, (0,0,0))
    textRect = text.get_rect()
    textRect.center = (infoObj.current_w // 2, infoObj.current_h // 2)
    textScores = font2.render(f"""Número de rodadas: {hits+mistakes}      Escore: {hits-mistakes}      Acertos: {hits}      Erros: {mistakes}      Tempo médio: {round(sum(times)/len(times), 2) if len(times) > 0 else 0}""", True, (0,0,0))
    textScoresRect = textScores.get_rect()
    textScoresRect.topleft = (10, 10)
    display_surface.fill((255,255,255))
    display_surface.blit(text, textRect)
    display_surface.blit(textScores, textScoresRect)
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == pygame.KEYUP and event.key == pygame.K_ESCAPE):
            pygame.quit()
            quit()
        elif (event.type == pygame.KEYDOWN and event.key == keys[key]):
            if (time()-limiter > 0.1): # limits bursts of keypresses
                endTime = time()-startTime
                times.append(round(endTime, 3))
                if (time()-limiter > 0.3): # limits screen flashing, as to avoid seizures
                    display_surface.fill((50,200,50))
                    limiter = time()
                del keys[key]
                key = choice(list(keys.keys()))
                keys = {'W': pygame.K_w, 'A': pygame.K_a, 'S': pygame.K_s, 'D': pygame.K_d}
                startTime = time()
                hits += 1
        elif (event.type == pygame.KEYDOWN and event.key == pygame.K_0):
            times = []
            del keys[key]
            key = choice(list(keys.keys()))
            keys = {'W': pygame.K_w, 'A': pygame.K_a, 'S': pygame.K_s, 'D': pygame.K_d}
            hits, mistakes = 0
        elif (event.type == pygame.KEYDOWN):
            if (time()-limiter > 0.1): # limits bursts of keypresses
                if (time()-limiter > 0.3):
                    display_surface.fill((200,50,50))
                    limiter = time()
                mistakes += 1
        pygame.display.update()