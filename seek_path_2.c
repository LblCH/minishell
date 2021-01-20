/*
 seek_path_2 - программа которая исполняет бинарники как если бы вводили их в bash.
 Является заготовкой для дальнейшего использования в minishell. Команда принимает
 только один аргумент командной строки (это может быть относительный, абсолютный путь 
 к бинарнику, а также по PATH (типа ./seek_path_2 ls))

 $ ./seek_path_2 ls
 PARENT: Let's wait for executing some process...
 CHILD: Hi, let's launch a program
 fork_2.c  kill.c     pipe_2    pipe.c     seek_path_2    seek_path.c  wait.c
 fork.c    leaks.txt  pipe_2.c  seek_path  seek_path_2.c  signal.c
 PARENT: child process is executed! Bye
  
 $ ./seek_path_2 ~/../../usr/bin/pwd
 PARENT: Let's wait for executing some process...
 CHILD: Hi, let's launch a program
 /home/lchantel/42-wildboar-git/minishell/train
 PARENT: child process is executed! Bye

 $ ./seek_path_2 ~/hello_world
 PARENT: Let's wait for executing some process...
 CHILD: Hi, let's launch a program
 Hello world!
 PARENT: child process is executed! Bye

 Что не доработано: в случае если пытаемся передать в качестве аргумента
 директорию то должна выскакивать ошибка Is a directory - в процессе доработкиiш
 для работы программы необходима статическая библиотека libft. Также не рассмотрен
 случай, когда процесс-потомок не смог создаться через fork(), т.е _idprog = -1.
 Программа тестилась в системе Ubuntu 20.04 LTS, на других дистрибутивах Linux и
 OS семейства Unix и Windows NT тесты не проводились
 * */

#include <sys/types.h>                  // для fork(), opendir(), readdir(), wait()
#include <stdio.h>                      // printf=)
#include <dirent.h>                     // для структуры dirent, opendir(), readdir()
#include <stdlib.h>                     // для malloc и exit
#include "../srcs/libft/libft.h"        // Заголовочный файл libft, ваш путь может отличаться=)
#include <unistd.h>                     // для write(), fork() и execve()
#include <sys/wait.h>                   // для wait()
#include <errno.h>                      // для errno
#include <string.h>                     // для strerror

/* addchar - добавляет символ в строку. Фукнция рабочая в рамках
 этой программы. ВНИМАНИЕ: освобождается память заалоцированная под s
 этот факт необходимо учитывать при использовании.
 */
char *addchar(char *s, char c)
{
	char *res;
	int len[2];

	if (!s)
		return (NULL);
	len[0] = ft_strlen(s) + 2;
	res = (char *)malloc(len[0]);
	len[1] = -1;
	while (s[++len[1]])
		res[len[1]] = s[len[1]];
	res[len[1]++] = c;
	res[len[1]] = 0;
	free(s);
	s = NULL;
	return (res);
}

// alloc_free_2 - освобождает память двумерного массива path_values
void alloc_free_2(void **mem)
{
	int i;

	i = -1;

	while (mem[++i] && mem)
	{
		free(mem[i]);
		mem[i] = NULL;
	}	
	free(mem);
	mem = NULL;
}

int main(int argc, char *argv[], char *envp[])
{
	int i;                        // счетчик
	char **path_values;           // для хранения директорий PATH
	pid_t _idprog;                // для работы с fork()
	int st;                       /* переменная состояний, необходимая для обработки раличных случаев вызова бинарника 
								  (относительный путь, абсолютный путь, по PATH) а также для обработки ошибок вызова 
								  (типа несуществующего файла или неверного бинарника по PATH)*/
	DIR *sh_dir;                  // Переменная типа директории - она нужна для поиска бинарника по PATH
	struct dirent *binary;        // Структура dirent - она нужна для поиска бинарника по PATH
	char *line;                   // Строка которая будет передаваться в execve
	int len;                      // Для работы по поиску бинарника в PATH
	char *alloc_free;             // Для освобожения старой памяти в ft_strjoin

	errno = 0;
	i = -1;
	st = 1;
	len = 1;
	line = NULL;
	/*Передаваться должен строго 1 аргумент!*/
	if (argc != 2)
	{
		write(1, "Error: wrong number of arguments: is should be two.\n", 
		ft_strlen("Error: wrong number of arguments: is should be two.\n"));
		return (1);
	}
	/*Если мы передаем бинарник, то здесь начинается обработка по PATH*/
	if (*argv[1] != '.' && *argv[1] != '/' && *argv[1] != '~')
	{
		st = 0;
		/*Ищем строку с переменной окружения PATH*/
		while (ft_strncmp(envp[++i], "PATH", 4))
			;
		/*Часть строки "PATH=" нам не нужна, целевые директории идут после знака '=' (сдвиг на 5-й байт)
		  Эти директорий разделены ':'. вывод PATH через env
		 $ env | grep PATH
		 ...
         PATH=/home/lchantel/.krew/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
		  */
		path_values = ft_split(envp[i] + 5, ':');
		/*Обнуляем i для следующей итерации*/
		i = -1;
		/*В итерации ниже производим поиск бинарника по директориям переменной PATH*/
		while (path_values[++i])
		{
			//len = ft_strlen(path_values[i]);
			/*Выход в случае ошибки открытия файла. ВНИМАНИЕ: не освобождается память
			 в случае ошибки открытия. Будут дальнейшие доработки =)*/	
			if (!(sh_dir = opendir(path_values[i])))
			{
				write(1, "minishell: ", ft_strlen("minishell: "));
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(1, "\n", 1);
				exit (1);
			}
			/*Читаем содержимое папки path_values[i], которая заложена выше в sh_dir*/
			while ((binary = readdir(sh_dir)))
			{
				/*Длина строки с учетом нуль-терминатора. Это нужно для того, чтобы например в случае cat
				  не проходил какой-нибудь неправильный бинарник вроде catchsegv*/
				len = ft_strlen(argv[1]) + 1;
				/*Ищем бинарник на точное совпадение. ОБЯЗАТЕЛЬНО преобразование binary->d_name в (char *)
				  иначе вместо нормальной строки будете в функцию передавать всякий сифилис (навроде 
				  /000/021/666/то_что_нужно_бл../000/037/000/021/ну_вы_п0няли/не_то_что_нужно). Такое
				  поведение binary->d_name наблюдается на ubuntu, насчет MacOSX хз*/
				if (!(len = ft_strncmp(argv[1], (char *)binary->d_name, len)))
				{
					/*Нашли совпадение теперь line присвоена директория*/
					line = ft_strdup(path_values[i]);
					len = ft_strlen(line);
					/*В случае отсутствия / на конце, необходимо добавить его. Иначе получится
					 что то вроде /usr/bincat*/
					if (line[len - 1] != '/')
						line = addchar(line, '/');
					/*Фиксируем старый участок памяти, который необходимо освободить*/
					alloc_free = line;
					/*Теперь добавляем бинарник*/
					line = ft_strjoin(line, binary->d_name);
					/*Для дальнейшего выхода из цикла*/
					len = 0;
					/*Освобождаем старую память*/
					free(alloc_free);	
					break ;
				}
			}
			/*Директорию необходимо закрывать, иначе в конце нас ждут утечки
			  от opendir*/
			closedir(sh_dir);
			/*Нашли бинарник, выходим из цикла*/
			if (!len)
				break ;
		}
	}
	/*Обрабатываем ситуацию когда искали именно бинарник через PATH*/
	if (!st)
	{
		/*!line - значит мы так и не нашли нужный бинарник в PATH. Тогда
		 в execve передает неправильный бинарник для дальнейшего 
		 вывода правильной ошибки */
		if (!line)
			line = ft_strdup(argv[1]);
		/*Освобождаем память, заалоцированную под директорию PATH*/
		alloc_free_2((void **)path_values);
	}
	/*В противном случае если мы имеем дело с относительным или
	  абсолютным путем то сразу присваваем line путь к бинарнику*/
	else 		
		line = ft_strdup(argv[1]);
	/*Обнуляем argv[1] - иначе execve сработает неправильно!*/
	alloc_free = argv[1];
	argv[1] = ft_strdup("../addchar.c");
	//free(alloc_free);
	//alloc_free = NULL;
	_idprog = fork(); // pid_t _idprog
	/*Переход в процесс-потомок*/
	if (!_idprog)
	{
		printf("CHILD: Hi, let's launch a program\n");
		/*В случае ошибки execve возвращает -1 и errno присваивается код,
		  в случае успеха ничего не возвращается, чем и воспользуемся*/
		st += execve(line, argv, envp);;
		if (st <= 0)
		{
			/*st = -1 - Случай ошибки бинарника*/
			if (st == -1)
			{
				write(1, line, ft_strlen(line));
				write(2, ": command not found\n", ft_strlen(": command not found\n"));
			}
			/*ОБработка ошибки директории*/
			else if (!st && (*line == '.' || *line == '/' || *line == '~'))
			{
				write(1, "minishell: ", ft_strlen("minishell: "));
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(1, "\n", 1);
			}
		}
		return (st);
	}
	else
	{
		printf("PARENT: Let's wait for executing some process...\n");
		/*Переход и ожидание когда закончится процесс-потомок*/
		wait(NULL);
		printf("PARENT: child process is executed! Bye\n");
		free(line);
		line = NULL;
	}
	return (0);
}
