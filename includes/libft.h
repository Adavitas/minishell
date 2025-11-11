#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(const char *s1);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);

#endif
