
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

cmd_args=""
while IFS= read -r cmd; do
    # Komutları valgrind'e zincirle
    cmd_args+=" <<< \"$cmd\""
done < "$input_file"
make re
# Komutları sırayla oku ve çalıştır

make leak <<< "$cmd_args" >> "$output_file" 2>&1

echo "Valgrind işlemleri tamamlandı. Çıkış dosyasına yazıldı: $output_file"

sed 's/^==[0-9]\{1,\}==//' "$output_file" > "$clean_file"
rm $output_file
