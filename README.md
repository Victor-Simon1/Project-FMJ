# Auteur
Fait par Victor SIMON

# Compilation 
Ce projet peut être compilé à l'aide d'un makefile avec les commandes
make all pour compiler tous les tests 
et make clean afin de nettoyer le répertoire 

Pour les test contenant la bibliothéques minwin,
il faut lancer la commande suivante :

    - export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:<minwin>/bin

Le(s) test(s) concerné(s) par cela sont :

    - test/test_window

# Rendu 
Toutes les fonctions ont été faites, mais pas toutes testés.
Cull retourne bien un objet contenant des faces et des vertex.
Mais il n'y a rien qui s'affiche car en sortie de clip l'objet est vide et je n'ai pas réussi à trouver 

