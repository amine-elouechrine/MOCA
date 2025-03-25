import re
import sys

def extraire_mots_et_positions(texte):
    # Dictionnaire pour stocker les mots et leurs positions
    dictionnaire = {}

    # Diviser le texte en lignes
    lignes = texte.split('\n')

    # Parcourir chaque ligne
    for num_ligne, ligne in enumerate(lignes, start=1):
        # Utiliser une expression régulière pour extraire les mots et les signes de ponctuation
        elements = re.findall(r'\b\w+[\w\'-]*\b|[\W_]', ligne)
        
        # Parcourir chaque élément et enregistrer sa position
        position = 0
        for element in elements:
            # Ignorer les espaces et les sauts de ligne
            if element.strip() == '':
                continue
            
            # Trouver la position de l'élément dans la ligne
            position = ligne.find(element, position)
            if position == -1:
                break  # Si l'élément n'est pas trouvé, passer au suivant
            
            # Enregistrer l'élément et sa position dans le dictionnaire
            if element not in dictionnaire:
                dictionnaire[element] = []
            dictionnaire[element].append((num_ligne, position + 1))  # +1 pour commencer à 1
            
            # Mettre à jour la position pour éviter de reprendre le même élément
            position += len(element)

    return dictionnaire

def enregistrer_dictionnaire(dictionnaire, fichier_sortie):
    # Ouvrir le fichier de sortie en mode écriture
    with open(fichier_sortie, 'w', encoding='utf-8') as f:
        # Trier les éléments par ordre alphabétique
        for element in sorted(dictionnaire.keys()):
            # Écrire l'élément et ses positions dans le fichier
            positions = ', '.join(f"({ligne},{pos})" for ligne, pos in dictionnaire[element])
            f.write(f"{element} {positions}\n")

def main(fichier_entree, fichier_sortie):
    # Lire le texte d'entrée depuis le fichier
    with open(fichier_entree, 'r', encoding='utf-8') as f:
        texte = f.read()

    # Extraire les mots et leurs positions
    dictionnaire = extraire_mots_et_positions(texte)

    # Enregistrer le résultat dans un fichier
    enregistrer_dictionnaire(dictionnaire, fichier_sortie)

    print(f"Le fichier résultat '{fichier_sortie}' a été généré avec succès.")

# Exemple d'utilisation
if __name__ == "__main__":
    # Vérifier que les arguments sont passés
    if len(sys.argv) != 3:
        print("Utilisation : python programme.py <fichier_entree.txt> <fichier_sortie.txt>")
        sys.exit(1)

    # Récupérer les noms des fichiers d'entrée et de sortie
    fichier_entree = sys.argv[1]
    fichier_sortie = sys.argv[2]

    # Exécuter le programme
    main(fichier_entree, fichier_sortie)