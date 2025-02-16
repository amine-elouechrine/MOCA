#!/bin/bash

TEST_dir = "test_file"
#RES_dic = "res_dict"
Res_attendu_dir = "res_attendu"

for txt in $TEST_dir/*.txt; do 
    base_name = $(base_name $txt)
    fichier_sortie = "$Res_attendu_dir/$base_name"

    #si ce fichier il existe pas 
    if [ ! -f "$fichier_sortie" ]; then
        touch "$fichier_sortie"
    fi

    ./../bin $txt //programme a tester 

    python3 $txt $fichier_sortie

    #comparaison
    diff ../ditionnaire.txt $fichier_sortie
done