##
## Makefile for  in /home/zhou_f//c++/r-type/server
## 
## Made by fong zhou
## Login   <zhou_f@epitech.net>
## 
## Started on  Sat Nov  2 22:15:24 2013 fong zhou
## Last update Sat Nov  2 22:22:42 2013 fong zhou
##

NAME	=	rtype_server

SRC	=	./src/
ROOM	=	./src/Room/
ENTITY	=	./src/Entity/
SOCKET	=	./src/Socket/
THREAD	=	./src/Thread/

FUNC	=	$(SRC)main.cpp \
		$(SRC)Server.cpp \
		$(SRC)Exception.cpp \
		$(ROOM)Room.cpp \
		$(ROOM)Game.cpp \
		$(ROOM)Map.cpp \
		$(ROOM)GameTime.cpp \
		$(ROOM)QuadTree.cpp \
		$(SOCKET)SocketUnix.cpp \
		$(SOCKET)Message.cpp \
		$(ENTITY)Entity.cpp \
		$(ENTITY)Bullet.cpp \
		$(ENTITY)ShockWave.cpp \
		$(ENTITY)SpaceShip.cpp \
		$(ENTITY)Player.cpp \
		$(ENTITY)Weapon.cpp \
		$(ENTITY)Bonus.cpp \
		$(ENTITY)Boss.cpp \
		$(ENTITY)Asteroid.cpp \
		$(ENTITY)MegaAttack.cpp \
		$(THREAD)CondVar.cpp \
		$(THREAD)Task.cpp \
		$(THREAD)Mutex.cpp \
		$(THREAD)ThreadPool.cpp

OBJ	=	$(FUNC:.cpp=.o)

CC	=	g++

INCLUDE	+=	-Iinclude -I$(SRC) -I$(ROOM) -I$(SOCKET) -I$(ENTITY) -I$(THREAD)

CXXFLAGS	+= -W -Wall -Wextra
CXXFLAGS	+= $(INCLUDE)

RM	=	rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re

