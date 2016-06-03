http_server: http_server.o daemon.o get_param.o log_proc.o http_html.o
	gcc -o http_server http_server.o daemon.o get_param.o log_proc.o http_html.o

http_server.o:http_server.c http_server.h
	gcc -c http_server.c

daemon.o:daemon.c daemon.h
	gcc -c daemon.c

get_param.o:get_param.c get_param.h
	gcc -c get_param.c

log_proc.o:log_proc.c log_proc.h
	gcc -c log_proc.c

http_html.o:http_html.h http_html.c
	gcc -c http_html.c

clean:
	rm -f http_server http_server.o daemon.o get_param.o log_proc.o

install:
	cp http_server /usr/bin/http_server

uninstall:
	rm /usr/bin/http_server
