##
## Makefile for  in /home/mo_r//r-type/client
## 
## Made by renxiao mo
## Login   <mo_r@epitech.net>
## 
## Started on  Sat Oct 26 17:59:38 2013 renxiao mo
## Last update Sat Oct 26 18:29:02 2013 renxiao mo
##

NAME	=	rtype_client

SRC	=	./src/
SOCKET	=	./src/Socket/
CLOCKMANAGER = 	./src/ClockManager/
KEYMANAGER = 	./src/KeyManager/
SOUNDMANAGER =	./src/SoundManager/
MENU =		./src/Menu/
GAME =		./src/Game/
RENDER	=	./src/Render/
ENTITYRENDER = 	./src/Render/EntityRender/

DEFINES =	./src/Defines/
RESOURCES =	./Resources/

FUNC	=	$(SRC)main.cpp \
		$(SRC)Client.cpp \
		$(SRC)ResourcePath.cpp \
		$(SOCKET)SocketUnix.cpp \
		$(SOCKET)Message.cpp \
		$(CLOCKMANAGER)ClockManager.cpp \
		$(KEYMANAGER)KeyManager.cpp \
		$(SOUNDMANAGER)SoundManager.cpp \
		$(MENU)Menu.cpp \
		$(MENU)InRoom.cpp \
		$(MENU)RoomSelection.cpp \
		$(GAME)Entity.cpp \
		$(GAME)Game.cpp \
		$(GAME)GameEnd.cpp \
		$(GAME)GameTime.cpp \
		$(GAME)Player.cpp \
		$(RENDER)Render.cpp \
		$(RENDER)MenuRender.cpp \
		$(RENDER)RoomRender.cpp \
		$(RENDER)RoomSelectionRender.cpp \
		$(RENDER)GameRender.cpp \
		$(ENTITYRENDER)BulletRender.cpp \
		$(ENTITYRENDER)MinionRender.cpp \
		$(ENTITYRENDER)PlayerRender.cpp

OBJ	=	$(FUNC:.cpp=.o)

CC	=	g++

INCLUDE	+=	-Iinclude -I$(SRC) -I$(SOCKET) -I$(CLOCKMANAGER) -I$(KEYMANAGER) -I$(SOUNDMANAGER) \
		-I$(MENU) -I$(GAME) -I$(RENDER) -I$(ENTITYRENDER) -I$(DEFINES) -I$(RESOURCES)

CXXFLAGS	+= -W -Wall -Wextra
CXXFLAGS	+= $(INCLUDE)

RM	=	rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re

