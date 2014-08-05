#BattleCore
#makefile for g++ linux

CC=g++
CFLAGS=-Wall

INCLUDE_PATH = -I/home/shrekshao/Downloads/lua-5.2.3/install/include/
LIB_PATH = -L/home/shrekshao/Downloads/lua-5.2.3/install/lib/
LIBS = -llua

SRC_DIR = .
VPATH = $(SRC_DIR)
VPATH += $(SRC_DIR)/Basic_Battle
VPATH += $(SRC_DIR)/Basic_Battle/Robot
VPATH += $(SRC_DIR)/Basic_Battle/Robot/Bullet
VPATH += $(SRC_DIR)/Basic_Battle/Robot/Engine
VPATH += $(SRC_DIR)/Basic_Battle/Robot/Weapon

SRC_FILES = $(foreach n, $(VPATH), $(wildcard $(n)/*.cpp))

OUTPUT_DIR = .



all:
	$(CC) -O2 -fPIC -shared -o $(OUTPUT_DIR)/libBattleCore.so $(INCLUDE_PATH) $(LIB_PATH) $(LIBS) $(SRC_FILES)


copylib: libBattleCore.so
	sudo rm /usr/lib/libBattleCore.so
	sudo cp libBattleCore.so /usr/lib/libBattleCore.so
