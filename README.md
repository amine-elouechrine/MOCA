# Analyse de Texte - Génération de dictionnaire (ABR/JSON)

**Projet universitaire** | *Méthodes Outils pour la Conception d'Applications (MOCA)* | 2025

## 📝 Description
Application en C analysant un fichier texte pour générer un dictionnaire de mots (stocké dans un **Arbre Binaire de Recherche**), avec leurs positions (ligne, colonne).  
Fonctionnalités clés :
- **Modularisation** (découpage en sources/headers) et compilation via Makefile.
- **Débogage avancé** :  
  - Détection de fuites mémoire avec `Valgrind`.  
  - Analyse de corruption mémoire avec `ASan` (AddressSanitizer).  
- **Sérialisation** de l'ABR en JSON (bibliothèque `json-c`).  

## 🛠️ Compétences mobilisées
- **Langage** : C (structures de données, pointeurs).  
- **Outils** : Makefile, gdb, GitLab.  
- **Méthodes** : Tests unitaires, fuzzing, analyse statique/dynamique.  

## 🚀 Utilisation
```bash
make build    # Compilation (option FICJSON pour JSON)
make run      # Exécution avec valgrind
make clean    # Nettoyage

