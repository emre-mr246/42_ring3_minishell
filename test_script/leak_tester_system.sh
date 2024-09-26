#!/bin/bash

input_file="commands.txt"
output_file="output.txt"

> "$output_file"
> "$clean_file"
make re

while IFS= read -r cmd; do
    echo "Running: valgrind <<< \"$cmd\""
    ./minishell <<< "$cmd" >> "$output_file"
    echo -e "\n---\n" >> "$output_file"
	sleep 1
done < "$input_file"

echo "İşlemleri tamamlandı. Çıkış dosyasına yazıldı: $output_file"
