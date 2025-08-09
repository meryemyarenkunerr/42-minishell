#include "../../includes/minishell.h"


//1. Girdi kontrolü ve yönlendirmeler denetlenir.
//2. Heredoc’lar işlenir ve geçici dosyalar hazırlanır.
//3. Basit veya pipeline komutları çalıştırılır.
//4. Çocuk işlemler içinde sinyal ve yönlendirmeler yapılır, komutlar çalıştırılır.
//5. Ana işlem çocuk işlemleri izler, sinyalleri yakalar ve çıkış kodlarını alır.
//6. Heredoc geçici dosyaları temizlenir, exit kontrolü yapılır.
//7. İşlem tamamlanır.

int	process_command(t_shell *shell, char *command)
{
	(void)shell;
	(void)command;
	return TRUE;
}