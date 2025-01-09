# Résumé sujet
Mise sous tension : Activaton rapide de toutes les fonctionalitées hardware.

## Début du logiciel :
- 4 bips (1 bip par second)
Si appuis sur les boutons H, M ou S :
- Mode normal
Sinon :
- Mode test (Affichage 00.00.00)

## Mode test
Effectue un chenillard : chaque segment va êre allumé 200ms.
Il faut faire le chenillard 2 fois de suite par segment.
Il faut donc faire :
- 2 fois dizaine d'heure.
- 2 fois unité d'heure
- 2 fois dizaine des minutes.
- 2 fois unité de minutes
- 2 fois dizaine de secondes
- 2 fois unité de secondes

A la fin : On fait des bips toutes les secondes en attendant qu"une touche soit activé.

Quand on appuis sur une touche : joue un son.
Quand appuis sur le bouton des heures :
- Affiche H sur les 2 segments des heures.
- Affiche N sur les 2 segmentes des minutes quand appuyé sur le bouton des minutes GPIO : 1 2 3 5 6
- Affiche S sur les 2 segments des secondes quand appuis sur le bouton des secondes.
- Appuyer sur la touche + affiche des P sur tous les segments.
- Appuyer sur la touche - affiche le segments central.

Pour sortir du mode test, il faudra appuyer sur les touches + et - en même temps pendant 100ms
A la fin / sortie du mode test : le buzzer fera 2 bips et entre en mode test affichage jour / nuit

## Mode test affichage jour / nuit
### Mode jour
Mode jour :
alternativement pendant 2 secondes, sur tout les segments : on affichera un 'J' et puissance d'éclairage sera à 80% (càd, ON pendant 80% sur temps et OFF 20%)

### Mode nuit
Alternativement pendant 2 secondes, sur tous les digits, on affichera un N à 40% d'éclairage.

Pour sortir du mode test affichage jour / nuit, il faut appuyer sur les touches + et - pendant au moins 100ms.

### Signalisation du reveil
à la sortie du mode test : 
- Si tous est OK : affiche le point des 7 segments pendant 2 secondes, avec 1 bip toutes les secondes (2 bips).
- Si KO : affiche HS sur les segments pendant 2 secondes avec les mêmes bips que OK.

Fin des tests : entrée en mode normal.

## Mode normal