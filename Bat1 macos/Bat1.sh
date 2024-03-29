#!/bin/bash

# Binários
prim=../Prim/prim
kruskal=../Kruskal/kruskal
dijkstra=../Dijkstra/dijkstra
kosaraju=../Kosaraju/kosaraju

echo "Testando algoritmo de Kruskal"
for i in instances/*.mtx
do
    echo -e "\033[1;33mInstância $i\033[0m"
    val=$($kruskal -f $i)
    correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2)
    [ $val -eq $correto ] && echo -e "Custo \033[1;32mOK\033[0m" || echo -e "\033[1;31mCusto incorreto\033[0m"

    $kruskal -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
    if [ $? -eq 0 ]; then
        echo -e "\033[1;32mOK\033[0m"
    else
        echo -e "\033[1;31mNão é um subgrafo\033[0m"
    fi
done


echo -e "\n\n"

echo "Testando algoritmo de Prim"
for i in instances/*.mtx
do
    echo -e "\033[1;33mInstância $i\033[0m"
    val=$($prim -f $i)
    correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2)
    [ $val -eq $correto ] && echo -e "Custo \033[1;32mOK\033[0m" || echo -e "\033[1;31mCusto incorreto\033[0m"

    $prim -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
    if [ $? -eq 0 ]; then
        echo -e "\033[1;32mOK\033[0m"
    else
        echo -e "\033[1;31mNão é um subgrafo\033[0m"
    fi
done


echo "Testando algoritmo de Dijkstra"
for i in instances/*.mtx
do
    echo -e "\033[1;33mInstância $i\033[0m"
    $dijkstra -f $i > temp

    j=$(basename $i)
    diff -w temp ./sp/$j > /dev/null
    if [ $? -eq 0 ]; then
        echo -e "\033[1;32mOK\033[0m"
    else
        echo -e "\033[1;31mErro\033[0m"
    fi
    rm temp
done

echo "Testando algoritmo de Kosaraju"
for i in instances_scc/*.dat
do
    echo -e "\033[1;33mInstância $i\033[0m"
    $kosaraju -f $i | ./ordena.sh > temp

    j=$(basename $i)
    diff -w temp ./scc/$j > /dev/null
    if [ $? -eq 0 ]; then
        echo -e "\033[1;32mOK\033[0m"
    else
        echo -e "\033[1;31mErro\033[0m"
    fi
    rm temp
done
