#!/bin/bash

input_file="commands.txt"
output_file="valgrind_output.txt"
clean_file="out.txt"

> "$output_file"
> "$clean_file"
make re

while IFS= read -r cmd; do
    echo "Running: valgrind <<< \"$cmd\""
    make leak <<< "$cmd" >> "$output_file" 2>&1
    echo -e "\n---\n" >> "$output_file"
done < "$input_file"

echo "Valgrind işlemleri tamamlandı. Çıkış dosyasına yazıldı: $output_file"

sed 's/^==[0-9]\{1,\}==//' "$output_file" > "$clean_file"
rm $output_file
