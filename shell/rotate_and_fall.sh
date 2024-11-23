#!/bin/bash

rotate_and_fall() {
    local matrix=()
    while IFS= read -r line || [[ -n "$line" ]]; do
        matrix+=("$line")
    done

    local rows=${#matrix[@]}
    local cols=${#matrix[0]}

    local rotated=()
    for ((i = 0; i < cols; i++)); do
        rotated[i]=$(printf '.%.0s' $(seq 1 $rows))
    done

    for ((i = 0; i < rows; i++)); do
        for ((j = 0; j < cols; j++)); do
            rotated[j]=${rotated[j]}${matrix[i]:j:1}
        done
    done

    for ((i = 0; i < cols; i++)); do
        local col=$(echo "${rotated[i]}" | tr -d ' ')
        local stones=$(echo "$col" | tr -cd '#')
        local obstacles=$(echo "$col" | tr -cd '*')
        local empty=$((${#col} - ${#stones} - ${#}))
}