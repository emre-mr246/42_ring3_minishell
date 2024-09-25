
#!/bin/bash

# Komutların bulunduğu dosya
input_file="commands.txt"

# Çıkış dosyası
output_file="valgrind_output.txt"
clean_file="out.txt"
# Valgrind ile çalıştırılacak program

# Eğer çıkış dosyası varsa sıfırlayalım
> "$output_file"
> "$clean_file"
make re
# Komutları sırayla oku ve çalıştır
while IFS= read -r cmd; do
    # Valgrind ile programı çalıştır ve sonuçları output_file'a ekle
    echo "Running: valgrind <<< \"$cmd\""
    make leak <<< "$cmd" >> "$output_file" 2>&1
    echo -e "\n---\n" >> "$output_file"
done < "$input_file"

echo "Valgrind işlemleri tamamlandı. Çıkış dosyasına yazıldı: $output_file"

sed 's/^==[0-9]\{1,\}==//' "$output_file" > "$clean_file"
rm $output_file
