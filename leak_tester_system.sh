
#!/bin/bash

# Komutların bulunduğu dosya
input_file="commands.txt"

# Çıkış dosyası
output_file="output.txt"

# Eğer çıkış dosyası varsa sıfırlayalım
> "$output_file"
> "$clean_file"
make re
# Komutları sırayla oku ve çalıştır
while IFS= read -r cmd; do
    echo "Running: valgrind <<< \"$cmd\""
    ./minishell <<< "$cmd" >> "$output_file"
    echo -e "\n---\n" >> "$output_file"
	sleep 1
done < "$input_file"

echo "İşlemleri tamamlandı. Çıkış dosyasına yazıldı: $output_file"

