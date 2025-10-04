# 42 Minishell
---
### Proje Hakkında

42 Minishell, basit bir Unix shell uygulamasıdır. Bu proje, kullanıcıdan komut alıp parse ederek işletim sistemi üzerinde çalıştırmayı sağlar. Pipe, yönlendirme, built-in komutlar ve signal handling gibi temel shell fonksiyonlarını içerir.

Projenin amacı, shell’in temel mantığını anlamak ve C programlama becerilerini geliştirmektir.

### Özellikler

- Temel komutların çalıştırılması (ls, echo, cat, vb.)
- Pipe (|) desteği
- Input / output yönlendirme (>, >>, <)
- Built-in komutlar:
	cd
	exit
	export
	unset
	env
	pwd
- Signal handling:
	Ctrl+C → komutu iptal etme
	Ctrl+\ → ignore

### Proje Yapısı ve Modüller
```
includes/				→ Header dosyaları
libft/					→
srcs/					→ Kaynak kod dosyaları
│
├─ executer/			→ Komut çalıştırma ve process yönetimi
├─ parser/				→ Komut satırı parsing
├─ error/				→ Hata ve uyarı mesajları
├─ signal/				→ Signal handling fonksiyonları
├─ main/				→ main fonksiyonu ve shell loop
└─ cleanup_tools/		→ Bellek yönetimi ve cleanup fonksiyonları
```

### Kurulum ve Çalıştırma

1. Repository’i klonla:
```
git clone https://github.com/meryemyarenkunerr/42-minishell.git
cd 42-minishell
```

2. Projeyi derle:
```
make
```

3. Shell’i başlat:
```
./minishell
```

### Kullanım Örnekleri

#### Komutlar:
```
ls -la
echo Hello World
cat file.txt
```

#### Pipe ve yönlendirme:
```
ls | grep src
echo "Hello" > file.txt
cat < file.txt
```

#### Built-in komutlar:
```
cd ..
pwd
export VAR=value
unset VAR
env
exit
```

### Katkıda Bulunma

Bu proje [Meryem Yaren Küner](https://github.com/meryemyarenkunerr) ve [İbrahim Serhat Aktaş](https://github.com/IbrmSerhat) tarafından geliştirilmiştir.
Projeye katkıda bulunmak için repository’i fork’layabilir ve lokal olarak geliştirebilirsin.