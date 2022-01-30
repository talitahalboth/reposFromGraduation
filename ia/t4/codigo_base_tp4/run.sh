#!/bin/bash

#baseFileName="results/result"
#extension="-eps-decay"
#trainings=(1000 5000  10000 )
#epsilons=(0.5 0.9 0.98)
#for (( i = 0; i < 3; i++ )); do
#  for (( j = 0; j < 3; j++ )); do
#    for (( seed = 0; seed < 30; seed++ )); do
#      python frozen_lake.py --epsilon "${epsilons[i]}" -tr "${trainings[j]}" -s -r >> "$baseFileName-${trainings[j]}-${epsilons[i]}$extension.txt";
#    done
#  done
#done

for (( seed = 0; seed < 30; seed++ )); do
    python frozen_lake.py -e 0.446095 -g 0.99266 -a 0.51755984 -tr 10000 -s -r >> "results/bestDecay";
done