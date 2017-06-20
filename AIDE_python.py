#################################################################################
#################################################################################
###                 AIDE
#################################################################################
#################################################################################



#################################################################################
#################################################################################
###     Argument & parametre
#################################################################################
#################################################################################
#       Recuperation des parametre et verification qu'il soit tous la!
#!/usr/bin/python

import sys, getopt

def main(argv):
   DossierMesure = 'b'
   FichierResultat = 'v'
   print (len(sys.argv))
   if len(sys.argv) < 5 :
      print("Il n'y a pas le bon nombre d'argument....")
      sys.exit()
   try:
      opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
   except getopt.GetoptError:
      print ("USAGE: test.py -i <DossierMesure> -o <FichierResultat>")
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         print ('test.py -i <DossierMesure> -o <FichierResultat>')
         sys.exit()
      elif opt in ("-i", "--ifile") and ("-o", "--ofile"):
         DossierMesure = arg
         FichierResultat = arg
      #elif opt in ("-o", "--ofile"):
         #FichierResultat = arg
   print ('le dossier de mesure est : '+ DossierMesure)
   print ('le fichier de resultat est : '+ FichierResultat)

if __name__ == '__main__':
   main(sys.argv[1:])


#################################################################################
#   Action sur argument de script?
import sys
if len(sys.argv) < 2:
    print("Précisez une action en paramètre")
    sys.exit(1)
action = sys.argv[1]
if action == "start":
    print("On démarre l'opération")
elif action == "stop":
    print("On arrête l'opération")
elif action == "restart":
    print("On redémarre l'opération")
elif action == "status":
    print("On affiche l'état (démarré ou arrêté ?) de l'opération")
else:
    print("Je ne connais pas cette action")




#################################################################################
#################################################################################
# permet d'executer un script bash dans python.
import subprocess
print "start"
subprocess.call("./sleep.sh", shell=True)
print "end"
#################################################################################
#################################################################################
###         Gestion de fichier:
#################################################################################
#################################################################################
#   equivalant au awk de bash
import sys

f = sys.stdin
# If you need to open a file instead:
#f = open('your.file')
for line in f:
    fields = line.strip().split()
    # Array indices start at 0 unlike AWK
    print(fields[0])
#################################################################################
import os 
os.listdir('c:/chemin/repertoire')   # retourne le nom des fichiers et répertoires present dans le dossier
import glob 
glob.glob('c:/python24/*')      # retourne le chemin complet des fichiers s et répertoires
print(os.listdir('/home/octopus/Desktop/JulesScript/python'))   #       Affiche la liste des fichiers present dans le dossier ciblé.
        ### equivalant à :
VAR = os.listdir('/home/octopus/Desktop/JulesScript/python')    
print(VAR)                                                      #       Affiche la même chose
#################################################################################
import csv
Resultat = csv.writer(open("Resultat.csv", "wb"))
Resultat.writerow(["NomFichier","Total","Heap","lib.","stack","Anon"])          #   ecrit une nouvelle ligne dans le fichier

with open(fichierchemincomplet, 'rb') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')        #
    for ligne in spamreader:
        Fichiercolonne =ligne.split(' ')
        print ', '.join(ligne) 
#################################################################################
fichier = open("fichier.txt","r")
for ligne in fichier:
    for chaine in chaines:
        if chaine in ligne:
            print ligne
fichier.close()
Fichierligne = open(fichierchemincomplet, 'r').read().split('\n')               #   liste ligne par ligne le fichier.
    #####   idem        #####
with open(fichierchemincomplet, 'r') as f:
    Fichierligne = f.read().split('\n')                                         #   liste ligne par ligne le fichier.

#################################################################################
for Fichier in os.listdir('c:/chemin/repertoire'):
    #   récupere le nom du fichier.   
    #   Somme des anon
    #   Somme des heap
#################################################################################
#################################################################################
########    Gestion des données dans liste:
#################################################################################
#################################################################################
chaines = ["coucou1",
           "coucou2",
           "coucou3"] # Texte à rechercher
#################################################################################
for texte in Fichier
fichierTEMP.split()
#for row in reader:
    print row[2], row[-2]
#################################################################################

values = map(float, data.splitlines())
   values2 = []
for s in data.splitlines():
     values.append(float(s))
print sum(values)
print sum(values2)

#################################################################################
with open('tonfichier.txt', 'r') as f:
    ma_liste = [fl.strip('\n') for fl in f.readlines()]

sum(liste)
liste = map(float, liste)

def somme(liste):
    liste = map(float, liste)
    return sum(liste)
 
ma_liste = [['1', '59.1719', '33.7628', '59.1717', '33.7621', '-6.38307e-06', '4.37423e-05', '-5.47665e-05', '-8.05611e-05', '1.94115e-05', '-1.03796', '3.25791e-05', '1', '0', '0', '0'], ['1', '61.9565', '33.7628', '61.9562', '33.7622', '-8.42891e-06', '-1.68337e-05', '-3.50265e-05', '-4.31808e-05', '-2.74669e-07', '1.1197', '-4.18484e-06', '1', '0', '0', '0'], ['1', '64.741', '33.7628', '64.7409', '33.7621', '6.78761e-05', '-6.77062e-05', '7.35626e-07', '-4.12659e-05', '0.000109878', '1.01554', '-5.91492e-06', '1', '0', '0', '0'], ['1', '67.5256', '33.7628', '67.5254', '33.7619', '-6.09481e-05', '-7.20047e-05', '-2.34684e-05', '-0.000116612', '3.21951e-05', '0.658118', '2.47959e-05', '1', '0', '0', '0'], ['1', '70.3101', '33.7628', '70.3099', '33.7621', '1.73855e-05', '5.38194e-05', '-2.49229e-05', '-6.15963e-05', '5.40589e-05', '-0.972511', '0.000141128', '1', '0', '0', '0'], ['1', '59.1719', '44.901', '59.1715', '44.9004', '-2.80354e-06', '-2.42085e-05', '6.61049e-05', '-1.04581e-05', '7.37594e-05', '0.306272', '2.7994e-05', '1', '0', '0', '0'], ['1', '61.9565', '44.901', '61.956', '44.9002', '-1.50369e-05', '-8.95777e-05', '-4.15848e-06', '-9.93404e-05', '8.0145e-05', '0.755015', '-6.05034e-05', '1', '0', '0', '0'], ['1', '64.741', '44.901', '64.7404', '44.9', '-6.76108e-05', '-2.26082e-05', '-6.12795e-05', '-8.72739e-05', '-4.16164e-05', '0.715832', '-7.13593e-06', '1', '0', '0', '0'], ['1', '67.5256', '44.901', '67.5249', '44.8998', '-2.47246e-05', '-4.98867e-05', '-3.79008e-05', '-8.16325e-05', '1.90071e-05', '0.851004', '-4.46166e-05', '1', '0', '0', '0'], ['1', '70.3101', '44.901', '70.3093', '44.8999', '-8.66542e-05', '6.15583e-05', '-5.82928e-05', '-0.000135644', '-9.30303e-06', '-0.672099', '9.33049e-05', '1', '0', '0', '0'], ['1', '59.1719', '56.0393', '59.1713', '56.0383', '0.000111875', '0.000188718', '-0.000135142', '-0.000237175', '0.000213908', '-1.07498', '0.000170884', '1', '0', '0', '0'], ['1', '61.9565', '56.0393', '61.956', '56.0383', '-3.60682e-06', '-0.000161949', '-2.59444e-05', '-0.00017711', '0.000147558', '0.819638', '-0.000188201', '1', '0', '0', '0']
print([somme(liste) for liste in ma_liste])


#################################################################################
#################################################################################
#Tkinter
    #http://apprendre-python.com/page-tkinter-interface-graphique-python-tutoriel
    #http://openclassrooms.com/courses/apprenez-a-programmer-en-python/des-interfaces-graphiques-avec-tkinter
    #http://sebsauvage.net/python/gui/index_fr.html#tkinter_or_wxpython
#################################################################################
#################################################################################
#!/usr/bin/env python
# -*- coding: utf-8 -*-
 
from tkinter import * 

fenetre = Tk()      

label = Label(fenetre, text="MEMTest")
label.pack()

fenetre.mainloop()

# bouton de sortie
bouton=Button(fenetre, text="Fermer", command=fenetre.quit)
bouton.pack()


#################################################################################
#################################################################################
######"Pygame
#################################################################################
#################################################################################
#Importation des bibliotheques necessaires
import pygame
from pygame.locals import *
#Initialisation de la bibliotheque Pygame
pygame.init()
#Creation de la fenetre
fenetre = pygame.display.set_mode((640, 480), RESIZABLE)
#Chargement et collage du fond
fond = pygame.image.load("background.jpg").convert()
fenetre.blit(fond, (0,0))

#Chargement et collage du personnage
perso = pygame.image.load("perso.png").convert_alpha()
position_perso = perso.get_rect()
fenetre.blit(perso, position_perso)
#Rafraichissement de l'ecran
pygame.display.flip() 

#permet(je crois) de faire un rafrechissement de des evenement Key
pygame.key.set_repeat(400, 30)#    Le delai avant de continuer les deplacements quand la touche reste enfoncee (en millisecondes) #   Le temps entre chaque deplacement. (en millisecondes)

#Variable qui continue la boucle si = 1, stoppe si = 0
continuer = 1
#Boucle infinie
while continuer:
    for event in pygame.event.get():   #On parcours la liste de tous les evenements recus
        if event.type == QUIT:     #Si un de ces evenements est de type QUIT
            continuer = 0  
        elif event.type == KEYDOWN:
            if event.key == K_SPACE:
                print("Espace")
            if event.key == K_RETURN:
                print("Entree")
            if event.key == K_DOWN:
                position_perso = position_perso.move(0,-3)# bouge en Y de 3 pixels.  
            if event.key == K_UP:
                position_perso = position_perso.move(0,3)# bouge en Y de 3 pixels. 
            if event.key == K_RIGHT:
                position_perso = position_perso.move(3,0)# bouge en X de 3 pixels.  
            if event.key == K_DOWN:
                position_perso = position_perso.move(-3,0)# bouge en X de 3 pixels.  
            if event.button == 1:   #Si clic gauche
                #On change les coordonnées du perso
                perso_x = event.pos[0]
                perso_y = event.pos[1]
    #Re-collage
    fenetre.blit(fond, (0,0))   
    fenetre.blit(perso, position_perso)
    #Rafraichissement
    pygame.display.flip() 


###########Pygame exemple fenetre:

import pygame, sys
from pygame.locals import *

pygame.init()
DISPLAYSURF = pygame.display.set_mode((400, 300))
pygame.display.set_caption('Hello Pygame World!')
while True: # main game loop
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
#################################################################################
#################################################################################