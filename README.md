ZenCrack
========

Free and open source hash cracker

 02/08/2012 :
  - Ajout de l'attaque par combinaisons.
  - Ajout de l'attaque par dictionnaire.

 01/08/2012 :
  - Correction de l'aide (merci coyotus)
  - Création de l'arborescence
  - Passage de map à unordered_map pour les hashs (gain de temps en accès)
  - Optimisation d'algo un peu partout.
  - Ajout d'OpenMP.

 31/07/2012 :
  - Création point d'entrée (main.cpp)
  - Création algo de parsing de règles (Rules.cpp)
  - Création algo d'attaque par règles (RulesCracker.cpp)
  - Support des fonctions de hashage suivantes : Md5, Sha1, Sha256, Sha512
